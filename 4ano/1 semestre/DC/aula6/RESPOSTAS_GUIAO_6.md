# Dispositivos Conectados — Guião 6: Conectividade Bluetooth Low Energy (BLE)
**Universidade de Aveiro — Mestrado em Engenharia de Computadores e Telemática / LEI**  
**Ano Letivo 2026/2027**  
**Autor:** Paulo C. Bartolomeu | **Resolução e Implementação:** Grupo 07 (DC-P2-G07, Node ID: 1022)

---

## Estrutura dos Projetos Desenvolvidos

Para responder integralmente a todos os requisitos práticos do guião sem sobreposições de código, foram estruturados e compilados no workspace do VSCode os seguintes projetos para o SoC **ESP32-C6**:

1. **`NimBLE_Beacon`** (Questões 1, 2 e 3):
   - Configurado como Broadcaster (anúncios não conectáveis `ADV_SCAN_IND`).
   - `DEVICE_NAME`: `"DC-P2-G07"`.
   - Implementa a leitura periódica (2 s) do sensor de temperatura **TC74** via `driver/i2c_master.h` (SDA=GPIO 6, SCL=GPIO 7, barramento 100 kHz, endereço `0x4D`).
   - Publica a temperatura no campo **Service Data** (UUID `0x181A`) dos pacotes de anúncio em tempo real após sincronização do host (`ble_hs_synced()`).

2. **`NimBLE_Connection`** (Questões 4, 5 e 6):
   - Configurado como Peripheral com anúncios conectáveis (`ADV_IND`, 500 ms) e scan response com intervalo de anúncio.
   - Trata os eventos GAP de ligação (`BLE_GAP_EVENT_CONNECT`), desconexão (`BLE_GAP_EVENT_DISCONNECT`) e atualização de parâmetros (`BLE_GAP_EVENT_CONN_UPDATE`).
   - Controlo do LED on-board (GPIO 8).
   - Suporta a negociação de parâmetros da Questão 4 (latência 3) e da Questão 6 (intervalo 500–1000 ms, latência 0, timeout 6 s).

3. **`NimBLE_GATT_Server`** (Questões 7 e 8):
   - Implementa o servidor GATT com os serviços **Heart Rate** (`0x180D`, característica `0x2A37` com leitura e indicação) e **Automation IO** (`0x1815`, característica do LED proprietária de 128 bits só de escrita).
   - Nível de registo alterado de `ESP_LOGD` para `ESP_LOGI` em `gatt_svr_register_cb()` para auditoria da tabela de atributos e handles.

4. **`NimBLE_ESS_Security`** (Questões 9 e 10 — Projeto Final Integrado):
   - Substitui o Heart Rate pelo **Environmental Sensing Service (ESS - `0x181A`)** com as características normalizadas **Temperature (`0x2A6E`)** e **Humidity (`0x2A6F`)**.
   - Integração com o sensor **DHT20** via I2C (`driver/i2c_master.h`) numa tarefa assíncrona de aquisição dedicada (`acquisition_task`), com proteção por **Mutex FreeRTOS**.
   - Notificações de GATT disparadas após libertação do Mutex via `ble_gatts_chr_updated()`.
   - Adiciona o **Serviço Proprietário de Configuração** (UUID base `E0C0DE00-0000-4000-8000-0000000003FE` para o `node_id = 1022`):
     - Característica de período de amostragem (`E0C0DE01-...`, uint16, leitura e escrita, cifrada e autenticada, validação de dimensão e intervalo [1, 3600]).
     - Característica de código de acesso (`E0C0DE02-...`, escrita exclusiva autenticada, até 32 bytes, conteúdo protegido nunca impresso).
   - Configuração do **Security Manager (SMP)** com modelo **Passkey Entry** (`BLE_HS_IO_DISPLAY_ONLY`), cifragem **LE Secure Connections (ECDH)**, autenticação MITM e persistência de emparelhamentos (Bonds) na NVS (`CONFIG_BT_NIMBLE_NVS_PERSIST=y`).

---

## 3.1 Descoberta: o ESP32-C6 como Beacon

### QUESTÃO 1

#### a) Comparação de endereços na consola vs aplicação; Ordem dos bytes; Tipo de endereço
- **Endereço na consola do ESP-IDF:** `BE:C0:3B:81:8C:58`
- **Endereço nas ferramentas de scanning (nRF Connect / bleak):** `58:8C:81:3B:C0:BE`
- **Por que os bytes surgem por ordem inversa?**
  Na pilha NimBLE (`main/src/gap.c`), o endereço é copiado para um vetor de 6 bytes (`addr_val[6]`) através de `ble_hs_id_copy_addr()`. No padrão BLE, os dados numéricos e endereços são representados em **little-endian**, em que `addr_val[0]` armazena o byte menos significativo (LSB) e `addr_val[5]` armazena o byte mais significativo (MSB).
  A função `format_addr()` formata o texto imprimindo linearmente de `addr[0]` a `addr[5]`:
  ```c
  sprintf(addr_str, "%02X:%02X:%02X:%02X:%02X:%02X", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
  ```
  Por outro lado, o padrão Bluetooth (IEEE 802 / BD_ADDR) e as aplicações como o nRF Connect apresentam os endereços MAC em **big-endian** (formato humano convencional: MSB primeiro até ao LSB). Logo, `addr_val[5] = 0x58` surge em primeiro lugar e `addr_val[0] = 0xBE` em último.
- **Que tipo de endereço é usado (`own_addr_type = 0`)?**
  O valor `own_addr_type = 0` corresponde a **`BLE_ADDR_PUBLIC`** (endereço público fixo, atribuído pelo IEEE e gravado nos eFuses de fábrica da Espressif).

#### b) Relação entre este endereço e o MAC STA obtido na aula de Wi-Fi
No ESP32-C6, a Espressif deriva os endereços de rede a partir de um MAC base de 48 bits gravado nos eFuses do chip:
- Wi-Fi STA: $\text{MAC}_{\text{base}}$
- Wi-Fi SoftAP: $\text{MAC}_{\text{base}} + 1$
- **Bluetooth LE:** $\text{MAC}_{\text{base}} + 2$
Portanto, o endereço BLE público da placa é exatamente o endereço MAC da interface Wi-Fi STA com o último byte incrementado em 2 unidades ($\text{MAC}_{\text{STA}} + 2$).

#### c) Por que não há botão CONNECT, mas mostra o URI e o endereço da scan response?
- O exemplo configura o anúncio com `adv_params.conn_mode = BLE_GAP_CONN_MODE_NON` (anúncio não conectável) e `adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN`.
- No standard BLE (Tabela 3), esta combinação utiliza o PDU **`ADV_SCAN_IND`** (*Scannable Undirected Advertising*).
- Como o tipo de PDU declara que o dispositivo **não aceita ligações** (`Aceita ligação: não`), o nRF Connect não disponibiliza a opção/botão **CONNECT**.
- No entanto, o PDU `ADV_SCAN_IND` **aceita scan requests** (`Aceita scan request: sim`). Quando o smartphone ou PC opera em pesquisa ativa (*active scanning*), envia um `SCAN_REQ` após detetar o anúncio. O ESP32-C6 responde de imediato com um pacote **`SCAN_RSP`** (scan response) de até 31 bytes, contendo as estruturas AD do endereço local (`0x1B`) e do URI (`0x24`, `https://espressif.com`), permitindo à aplicação exibi-los.

---

### QUESTÃO 2

#### a) Decomposição dos dados de anúncio e scan response nas estruturas AD
Cada estrutura AD (*Advertising Data*) é codificada no formato: `[Comprimento] [Tipo AD] [Dados...]`.

**Pacote de Anúncio (`ADV_SCAN_IND`):**
1. **Flags (`0x01`):**
   - Comprimento: `0x02` (1 byte tipo + 1 byte dado)
   - Tipo: `0x01`
   - Dados: `0x06` (`BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP` $\rightarrow$ General Discoverable + BR/EDR Not Supported).
2. **Complete Local Name (`0x09`):**
   - Comprimento: `0x0A` (10 bytes para `"DC-P2-G07"`)
   - Tipo: `0x09`
   - Dados: `44 43 2D 50 32 2D 47 30 37` (ASCII de `"DC-P2-G07"`).
3. **TX Power Level (`0x0A`):**
   - Comprimento: `0x02`
   - Tipo: `0x0A`
   - Dados: `0x09` (+9 dBm, potência máxima de transmissão do rádio).
4. **Appearance (`0x19`):**
   - Comprimento: `0x03`
   - Tipo: `0x19`
   - Dados: `00 02` (Valor little-endian da macro `BLE_GAP_APPEARANCE_GENERIC_TAG = 0x0200`).
5. **LE Role (`0x1C`):**
   - Comprimento: `0x02`
   - Tipo: `0x1C`
   - Dados: `0x00` (`BLE_GAP_LE_ROLE_PERIPHERAL` $\rightarrow$ apenas suporta o papel Peripheral).

**Explicação da representação:**
- **Aparência (`0x0200`):** No Bluetooth SIG Assigned Numbers, `0x0200` (512 decimal) codifica a categoria *Generic Tag*. Como todos os campos inteiros de 16 bits no BLE são transmitidos em **little-endian**, o LSB (`0x00`) é enviado primeiro, seguido do MSB (`0x02`), resultando na sequência de bytes `00 02`.
- **Endereço (`0x1B`):** O endereço Bluetooth de 48 bits (6 bytes) é igualmente transmitido em little-endian, com o byte menos significativo primeiro (`BE C0 3B 81 8C 58`).

**Pacote de Scan Response (`SCAN_RSP`):**
1. **LE Bluetooth Device Address (`0x1B`):**
   - Comprimento: `0x07` (1 byte tipo + 6 bytes endereço)
   - Tipo: `0x1B`
   - Dados: `BE C0 3B 81 8C 58`
2. **URI (`0x24`):**
   - Comprimento: `0x12` (18 bytes = 1 byte tipo + 1 byte prefixo + 16 bytes URL)
   - Tipo: `0x24`
   - Dados: `17 2F 2F 65 73 70 72 65 73 73 69 66 2E 63 6F 6D` (`0x17` codifica o esquema `https://`, seguido da string `"//espressif.com"`).

#### b) Cálculo dos bytes ocupados; Por que o endereço e URI vão para a scan response; Limite do nome
- **Bytes no Bloco de Anúncio:**
  - Flags: $1 + 2 = 3\text{ bytes}$
  - Nome: $1 + 1 + 9 = 11\text{ bytes}$ (para nome de 9 caracteres)
  - TX Power: $1 + 2 = 3\text{ bytes}$
  - Appearance: $1 + 3 = 4\text{ bytes}$
  - LE Role: $1 + 2 = 3\text{ bytes}$
  - **Total no Anúncio:** $3 + 11 + 3 + 4 + 3 = 24\text{ bytes}$ (dentro do limite máximo de 31 bytes).
- **Bytes no Bloco de Scan Response:**
  - Device Address: $1 + 7 = 8\text{ bytes}$
  - URI: $1 + 18 = 19\text{ bytes}$
  - **Total na Scan Response:** $8 + 19 = 27\text{ bytes}$ (dentro do limite máximo de 31 bytes).

- **Por que o endereço e o URI estão na Scan Response?**
  O limite absoluto de um pacote legacy advertising no BLE é de **31 bytes**. Se tentássemos incluir o endereço (8 bytes) e o URI (19 bytes) no pacote principal de anúncio, o tamanho total seria $24 + 8 + 19 = 51\text{ bytes}$, ultrapassando os 31 bytes permitidos. A especificação contorna esta limitação descarregando campos informativos secundários para a scan response.
- **Comprimento máximo do nome neste exemplo:**
  Os campos fixos do anúncio ocupam $3 + 3 + 4 + 3 = 13\text{ bytes}$. O cabeçalho do nome (comprimento + tipo) ocupa 2 bytes. Logo, restam:
  $$31 - 13 - 2 = 16\text{ caracteres}$$
  Se o nome tiver 20 caracteres, a dimensão total seria $15 + 20 = 35\text{ bytes} > 31$, resultando no erro reportado pelo NimBLE:
  `failed to set advertising data, error code: 4` (`BLE_HS_EMSGSIZE`).
  A preparação recomenda no máximo 10 caracteres para que ainda sobre espaço livre para inserir o campo **Service Data (5 bytes)** na Questão 3 e a lista de **UUIDs de 16 bits (4 bytes)** na Questão 9.

#### c) Intervalo de anúncio de 1 s; Medições de RSSI; Compromissos de projeto
- **Intervalo de 1 s:** Ao configurar `adv_params.itvl_min = BLE_GAP_ADV_ITVL_MS(1000)` e `itvl_max = BLE_GAP_ADV_ITVL_MS(1000)`:
  - O intervalo observado passa de ~100–150 ms para ~1000 ms (1 segundo).
  - O **tempo de descoberta** aumenta visivelmente: enquanto a 100 ms o scanner captura o pacote quase instantaneamente (< 200 ms), a 1000 ms o telemóvel pode demorar entre 1 a 4 segundos a detetar o periférico (dependendo da coincidência entre a janela de escuta do scanner e o instante de emissão nos 3 canais de anúncio 37, 38 e 39).
- **Medições de RSSI (valores típicos de laboratório):**
  - **+9 dBm (potência máxima):**
    - $0.5\text{ m}$: $\approx -45\text{ dBm}$ a $-50\text{ dBm}$
    - $2.0\text{ m}$: $\approx -62\text{ dBm}$ a $-67\text{ dBm}$
    - $5.0\text{ m}$: $\approx -74\text{ dBm}$ a $-80\text{ dBm}$
  - **0 dBm:**
    - $0.5\text{ m}$: $\approx -55\text{ dBm}$ a $-60\text{ dBm}$
    - $2.0\text{ m}$: $\approx -72\text{ dBm}$ a $-78\text{ dBm}$
    - $5.0\text{ m}$: $\approx -85\text{ dBm}$ a $-92\text{ dBm}$ (maior taxa de pacotes perdidos)
- **Compromissos de engenharia:**
  - **Intervalo vs Consumo:** Aumentar o intervalo de anúncio desliga o emissor a maior parte do tempo, reduzindo o consumo de energia em dezenas de vezes (essencial para nós alimentados a bateria), ao custo de aumentar a latência de descoberta pelo utilizador.
  - **Potência vs Alcance vs Consumo:** Reduzir a potência de transmissão (de +9 dBm para 0 dBm ou inferior) reduz a corrente de pico do rádio durante o anúncio, mas encurta a distância útil de deteção e torna o sinal mais suscetível a desvanecimento por obstáculos e atenuação no espaço livre ($FSPL \propto 20\log_{10}(d)$).

---

### QUESTÃO 3

#### Implementação no projeto `NimBLE_Beacon`
- Foi adicionado o módulo `tc74.c`/`tc74.h` que inicializa o periférico I2C (`driver/i2c_master.h`) no barramento `I2C_NUM_0` (SDA=GPIO 6, SCL=GPIO 7, pull-ups internos e externos de 4,7 kΩ, relógio de 100 kHz) e adiciona o dispositivo TC74 no endereço `0x4D`.
- A tarefa FreeRTOS `tc74_task` executa periodicamente a cada 2 segundos (`vTaskDelay(pdMS_TO_TICKS(2000))`). Em cada iteração:
  1. Lê o registo `0x00` do TC74 através de `i2c_master_transmit_receive()`.
  2. Em caso de sucesso, atualiza o valor de temperatura e imprime no log (`TC74 read successful: XX C`).
  3. Se a leitura falhar (ex: sensor desligado), imprime `ESP_LOGW` e retém o último valor válido anunciado.
  4. Verifica se o host sincronizou (`ble_hs_synced()`) e invoca `gap_update_temperature()`, que preenche a estrutura `svc_data_uuid16` com o UUID `0x181A` (`0x1A, 0x18`) e o byte com sinal de temperatura (`int8_t`), chamando `ble_gap_adv_set_fields()`.
- **Verificação do tamanho:** O campo Service Data ocupa 5 bytes ($1\text{ byte len} + 1\text{ byte tipo 0x16} + 2\text{ bytes UUID} + 1\text{ byte temperatura}$). A dimensão total do pacote de anúncio é:
  $$3\text{ (Flags)} + 11\text{ (Nome)} + 3\text{ (TX Pwr)} + 4\text{ (Appearance)} + 3\text{ (Role)} + 5\text{ (Service Data)} = 29\text{ bytes} \le 31\text{ bytes}$$
  Coube sem necessidade de suprimir nenhum campo pré-existente.

#### Vantagens e limitações face a uma ligação GATT
- **Vantagens:**
  - **Comunicação 1-para-muitos (Broadcast):** Um número infinito de telemóveis e coletores (*observers*) em redor pode ler a temperatura simultaneamente sem estabelecer qualquer sessão.
  - **Consumo energético mínimo:** O periférico não necessita de manter janelas de escuta de rádio para sincronização de ligação nem de trocar pacotes CONNECT / LLACK.
  - **Latência zero de acesso:** O observador obtém a medição no primeiro anúncio captado, sem passar pelo handshake de ligação e descoberta GATT.
- **Limitações:**
  - **Sem confirmação de entrega (Unacknowledged):** O emissor nunca sabe se algum dispositivo recebeu a telemetria.
  - **Sem segurança / Cifragem:** Os dados de anúncio viajam sempre em claro pelo ar, visíveis a qualquer recetor rádio nas imediações.
  - **Capacidade extremamente restrita:** O limite de 31 bytes apenas permite transmitir grandezas pontuais simples.
  - **Comunicação estritamente unidirecional:** O coletor não pode alterar configurações nem enviar comandos de volta ao sensor sem estabelecer ligação.

---

## 3.2 Ligação: o ESP32-C6 como Periférico

### QUESTÃO 4

#### a) Identificação do connection handle e parâmetros antes e depois da atualização
Com base nos logs de execução do `NimBLE_Connection`:
- **Connection handle:** `0` (primeira ligação ativa atribuída pelo controller local).
- **Antes da atualização:**
  - `conn_itvl = 36`: em milissegundos, $36 \times 1.25\text{ ms} = \mathbf{45.0\text{ ms}}$.
  - `conn_latency = 0`: o periférico é obrigado a responder em todos os eventos de ligação.
  - `supervision_timeout = 500`: em milissegundos, $500 \times 10\text{ ms} = \mathbf{5000\text{ ms} = 5.0\text{ s}}$.
- **Depois da atualização (`ble_gap_update_params`):**
  - `conn_itvl = 36`: $36 \times 1.25\text{ ms} = \mathbf{45.0\text{ ms}}$.
  - `conn_latency = 3`: o periférico tem autorização para ignorar até 3 eventos de ligação consecutivos se não tiver dados ATT para transmitir. Na ausência de tráfego, o ESP32 só acorda a cada $(1 + 3) \times 45\text{ ms} = \mathbf{180.0\text{ ms}}$.
  - `supervision_timeout = 500`: $\mathbf{5000\text{ ms} = 5.0\text{ s}}$.

#### b) Tipo de endereço do smartphone; Bits mais significativos; Renovação periódica
- No log: `peer id address: type=1, value=7F:BE:AD:66:6F:45`.
  - `type = 1`: Trata-se de um endereço **Random** (`BLE_ADDR_RANDOM`).
  - Analisando o byte mais significativo (`0x7F = 01111111_b`): os dois bits mais significativos (bits 47 e 46) são **`01`**.
  - De acordo com a especificação BLE:
    - `00`: Non-resolvable private address
    - **`01`: Resolvable Private Address (RPA)**
    - `11`: Static device address
- O smartphone utiliza um **RPA**, gerado dinamicamente através de criptografia simétrica com base na *Identity Resolving Key* (IRK).
- **O endereço mantém-se se desligar e voltar a ligar?**
  Mantém-se caso a religação ocorra dentro do período de validade do endereço privado (tipicamente renovado a cada **15 minutos** pelo sistema operativo Android/iOS para mitigar ataques de rastreio de localização). Após esse intervalo, o smartphone gera um novo RPA com prefixo `01`.

#### c) Encontro por um segundo telemóvel e suporte a múltiplas ligações
- **Um segundo telemóvel encontra o dispositivo?**
  **Não.** No exemplo `NimBLE_Connection`, a pilha interrompe o anúncio rádio legacy assim que uma ligação CONNECT_IND é estabelecida. No código de `gap.c`, a função `start_advertising()` só é invocada aquando da desconexão (`BLE_GAP_EVENT_DISCONNECT`) ou em caso de falha de conexão. Como o rádio não está a emitir pacotes de anúncio, nenhum outro scanner consegue detetar a placa.
- **Alteração para permitir até 3 ligações simultâneas:**
  1. No evento `BLE_GAP_EVENT_CONNECT`, após a ligação ser estabelecida com sucesso (`event->connect.status == 0`), verificar se o número de ligações ativas é inferior a `CONFIG_BT_NIMBLE_MAX_CONNECTIONS` (definido como 3 no sdkconfig). Caso seja inferior, chamar imediatamente `start_advertising()` para manter o dispositivo visível e conectável.
  2. No evento `BLE_GAP_EVENT_DISCONNECT`, garantir que os anúncios são reiniciados se ainda não estiverem ativos.

---

### QUESTÃO 5

#### a) Descodificação dos erros HCI (`erro - 0x200`)
Na pilha NimBLE, os erros da interface HCI são somados à base `BLE_HS_ERR_HCI_BASE = 0x200 = 512`. Consultando a *Bluetooth Core Specification* (Vol. 1, Parte F, secção 1.3):
- **Causa 531:**
  $$531 - 512 = 19 = \mathbf{0x13} \rightarrow \textbf{Remote User Terminated Connection}$$
  Indica que o utilizador do central (smartphone) clicou no botão DISCONNECT da aplicação, enviando um pacote `LL_TERMINATE_IND` com código de término voluntário.
- **Causa 520:**
  $$520 - 512 = 8 = \mathbf{0x08} \rightarrow \textbf{Connection Timeout / Supervision Timeout}$$
  Indica que os dispositivos deixaram de receber pacotes mútuos nos eventos de ligação programados e o temporizador de supervisão expirou sem que qualquer pacote de rádio válido fosse recebido.
- **Causa 534:**
  $$534 - 512 = 22 = \mathbf{0x16} \rightarrow \textbf{Connection Terminated by Local Host}$$
  Indica término originado pelo próprio anfitrião local.

#### b) Tempo decorrido entre a perda de comunicação e o evento `BLE_GAP_EVENT_DISCONNECT`
- Decorre exatamente o tempo configurado pelo **`supervision_timeout`** ($\mathbf{5.0\text{ s}}$ para o valor 500).
- Enquanto o tempo decorrido desde o último pacote de dados recebido for inferior a 5 segundos, a Link Layer tenta comunicar nos canais de salto previstos. Ao fim de 5 segundos contínuos sem resposta, a camada Link Layer gera um evento HCI Disconnection Complete com razão `0x08`, disparando o callback `BLE_GAP_EVENT_DISCONNECT` na aplicação.

#### c) Comparação com o Wi-Fi (bcn_timeout, Maximum retry)
- **Quem toma a iniciativa de restabelecer a ligação?**
  - No **Wi-Fi** (modo Station): É o **ESP32-C6 (cliente/STA)** que monitoriza as balizas do AP e, ao detetar `bcn_timeout`, inicia proativamente o processo de reconexão (varrimento de canais, autenticação e associação).
  - No **Bluetooth LE** (papel Peripheral): O **ESP32-C6 NUNCA toma a iniciativa de restabelecer a ligação**. O periférico limita-se a voltar a emitir anúncios passivos (`start_advertising()`). A iniciativa e responsabilidade de iniciar a nova ligação recai exclusivamente sobre o **Central (smartphone)** através de um novo pacote `CONNECT_IND`.
- **O ESP32-C6 deixa de estar disponível?**
  No BLE, o ESP32-C6 nunca deixa de estar disponível: no exato milissegundo em que processa a desconexão, reinicia os anúncios e fica imediatamente apto a aceitar ligações de qualquer central.

---

### QUESTÃO 6

#### Parâmetros de ligação solicitados (500–1000 ms, latência 0, timeout 6 s)
- **Parâmetros configurados:**
  ```c
  struct ble_gap_upd_params params = {
      .itvl_min = BLE_GAP_CONN_ITVL_MS(500),
      .itvl_max = BLE_GAP_CONN_ITVL_MS(1000),
      .latency = 0,
      .supervision_timeout = BLE_GAP_SUPERVISION_TIMEOUT_MS(6000),
  };
  ble_gap_update_params(conn_handle, &params);
  ```
- **Parâmetros efetivamente aplicados:**
  O central tem a palavra final. Se o central for um telemóvel Android/iOS, este valida o pedido face às suas regras internas de conectividade. Caso o pedido seja aceite, o evento `BLE_GAP_EVENT_CONN_UPDATE` regista `status = 0` com um intervalo dentro da gama $[500, 1000]\text{ ms}$. No entanto, em vários sistemas Android, o central pode rejeitar parâmetros com intervalos tão dilatados ou impor valores mais baixos (ex: status 571 $\rightarrow 571 - 512 = 59 = \mathbf{0x3B}$: `Unacceptable Connection Parameters`).
- **Impacto no consumo e tempo de resposta:**
  - **Consumo:** Com $itvl = 1000\text{ ms}$ e latência 0, o rádio apenas acorda uma vez por segundo em vez de acordar a cada 45 ms (uma redução de frequência de rádio superior a **22 vezes**), diminuindo drasticamente o consumo médio de corrente (de ~15 mA para frações de miliampere quando combinado com light sleep).
  - **Tempo de resposta a uma leitura (latência ATT):** A latência de ida e volta (*round-trip*) de qualquer operação ATT (leitura/escrita com resposta) passa a ter um pior caso de **1 segundo**, pois o cliente tem de aguardar pelo próximo evento de ligação para que o pacote seja despachado e respondido.

---

## 3.3 Troca de Dados: Servidor GATT

### QUESTÃO 7

#### a) Tabela de atributos dos serviços da aplicação; Handle do CCCD; Serviços 0x1800 e 0x1801
Ao substituir `ESP_LOGD` por `ESP_LOGI` em `gatt_svr_register_cb()`, a pilha imprime os atributos registados:

| Handle | UUID | Tipo de Atributo | Significado | Permissões / Flags |
|---|---|---|---|---|
| *1* | `0x2800` | Declaração de Serviço | **Generic Access (`0x1800`)** | Read |
| *2* | `0x2803` | Declaração de Característica | Device Name (`0x2A00`) | Read |
| *3* | `0x2A00` | Valor de Característica | Nome ("DC-P2-G07") | Read |
| *4* | `0x2803` | Declaração de Característica | Appearance (`0x2A01`) | Read |
| *5* | `0x2A01` | Valor de Característica | Categoria Tag (`0x0200`) | Read |
| *6* | `0x2800` | Declaração de Serviço | **Generic Attribute (`0x1801`)** | Read |
| *7* | `0x2803` | Declaração de Característica | Service Changed (`0x2A05`) | Indicate |
| *8* | `0x2A05` | Valor de Característica | Intervalo de handles alterados | Indicate |
| *9* | `0x2902` | Descritor CCCD | CCCD do Service Changed | Read / Write |
| **`def_handle`** | `0x2800` | Declaração de Serviço | **Heart Rate Service (`0x180D`)** | Read |
| **`chr_def`** | `0x2803` | Declaração de Característica | Heart Rate Measurement (`0x2A37`)| Read / Indicate |
| **`val_handle`** | `0x2A37` | Valor de Característica | Flags (1 byte) + BPM (1 byte) | Read |
| **`val_handle + 1`** | `0x2902` | Descritor CCCD | **CCCD do Heart Rate Measurement** | Read / Write |
| **`led_svc`** | `0x2800` | Declaração de Serviço | **Automation IO (`0x1815`)** | Read |
| **`led_chr_def`** | `0x2803` | Declaração de Característica | Declaração LED 128-bit | Write |
| **`led_val_handle`** | `...d123` | Valor de Característica | Estado do LED (01 / 00) | Write |

- **Dedução do handle do CCCD:**
  Como a característica `0x2A37` tem a flag `BLE_GATT_CHR_F_INDICATE`, a pilha NimBLE gera internamente o descritor CCCD (`0x2902`) no handle imediatamente seguinte ao valor da característica: $\mathbf{\text{handle}_{\text{CCCD}} = \text{val\_handle} + 1}$.
- **Por que a característica do LED não tem CCCD?**
  O descritor CCCD (*Client Characteristic Configuration Descriptor*) existe unicamente para que os clientes ativem ou desativem **notificações** ou **indicações**. A característica do LED possui unicamente permissão de escrita (`BLE_GATT_CHR_F_WRITE`), não emitindo notificações assíncronas do servidor para o cliente. Logo, um CCCD seria supérfluo.
- **De onde surgem os serviços `0x1800` e `0x1801`?**
  São serviços mandatórios do protocolo Bluetooth core, criados automaticamente pela pilha NimBLE aquando da chamada de `ble_svc_gap_init()` (Generic Access Profile: nome, aparência e parâmetros) e `ble_svc_gatt_init()` (Generic Attribute Profile: robustez de cache e serviço alterado).

#### b) Interpretação dos bytes lidos e do evento subscribe
- **Dois bytes lidos:** `0x00, 0x47` (ou similar)
  - Primeiro byte (`0x00`): **Flags**. O bit 0 igual a `0` indica que o formato do valor de frequência cardíaca é `UINT8` (1 byte). Os restantes bits a 0 indicam que o sensor contact status, energy expended e intervalos RR não estão presentes.
  - Segundo byte (`0x47` = 71 decimal): O ritmo cardíaco atual em **bpm** (71 bpm).
- **Evento Subscribe (`reason = 1, curi = 1`):**
  - O central escreveu no CCCD para subscrever **indicações** (`cur_indicate = 1`).
  - **Valor escrito no CCCD:** $\mathbf{0x0002}$ (o bit 0 activa notificações `0x0001`; o bit 1 activa indicações `0x0002`).

#### c) Por que a função de acesso é invocada "by nimble stack" antes de cada indicação e em que tarefa corre?
- Quando a aplicação chama `ble_gatts_indicate()`, o NimBLE tem de construir a PDU `ATT_HANDLE_VALUE_IND` para enviar pelo rádio. Para extrair os dados atuais do atributo, a pilha invoca o callback de acesso `heart_rate_chr_access()` com a flag `ctxt->op = BLE_GATT_ACCESS_OP_READ_CHR` e `conn_handle = BLE_HS_CONN_HANDLE_NONE` (daí a mensagem no log `"characteristic read by nimble stack"`).
- **Em que tarefa corre?**
  Excecionalmente, quando a aplicação invoca `ble_gatts_indicate()` ou `ble_gatts_notify()`, a função de acesso corre **na tarefa da aplicação que fez a chamada** (neste caso, a `heart_rate_task`), e **não** na tarefa do host NimBLE. Por esta razão, se a tarefa da aplicação mantiver um mutex que a função de acesso também tente obter, o sistema entra em *deadlock*!

#### d) Vantagens e custos de Indicações vs Notificações num sensor de 1 Hz
- **Vantagens de Indicações:** Garantia formal de entrega na camada ATT. O periférico recebe uma confirmação explícita (`ATT_HANDLE_VALUE_CONFIRMATION`) do cliente para cada amostra enviada.
- **Custos / Desvantagens:**
  - **Maior consumo de energia e ocupação do canal:** Cada medição exige duas transmissões de rádio (Indicação + Confirmação).
  - **Bloqueio de débito:** O servidor não pode enviar uma nova indicação enquanto a anterior não for confirmada.
  - Num sensor contínuo a 1 Hz (1 medição por segundo), a perda ocasional de um pacote por ruído é desprezável face ao custo de overhead e latência. Por este motivo, o Bluetooth SIG prevê **Notificações** para telemetria de sensores de alta frequência.

---

### QUESTÃO 8

#### a) Escrita de 01 e 00 no LED; Escrita de 0101; Erros devolvidos
- **Escrita de 01 e 00:**
  - Escrever `01` acende o LED de status (GPIO 8).
  - Escrever `00` apaga o LED.
- **Escrita de `0101` (2 bytes):**
  - O telemóvel recebe o erro **`0x0E` (`BLE_ATT_ERR_UNLIKELY`)**.
  - **Quem gera o erro?** É gerado pela própria **aplicação** na função `led_chr_access()`, que valida estritamente a dimensão do buffer com `if (ctxt->om->om_len == 1)` e salta para o rótulo de erro `return BLE_ATT_ERR_UNLIKELY;` quando recebe 2 bytes.
- **Por que a aplicação não oferece leitura e que erro a pilha devolveria?**
  - A característica foi registada exclusivamente com a flag `BLE_GATT_CHR_F_WRITE` (não inclui `BLE_GATT_CHR_F_READ`).
  - Se um cliente GATT tentar ler o atributo, a função interna `ble_att_svr_check_perms()` do NimBLE valida as permissões e rejeita imediatamente o pedido devolvendo o erro ATT padrão:
    $$\mathbf{\text{BLE\_ATT\_ERR\_READ\_NOT\_PERMITTED}}\text{ (código }0x02\text{, definido em host/ble_att.h)}$$

#### b) Ordem dos bytes na declaração `BLE_UUID128_INIT`
- UUID textual da característica: `00001525-1212-EFDE-1523-785FEABCD123`
- Declaração em código C:
  ```c
  BLE_UUID128_INIT(0x23, 0xd1, 0xbc, 0xea, 0x5f, 0x78, 0x23, 0x15, 0xde, 0xef, 0x12, 0x12, 0x25, 0x15, 0x00, 0x00)
  ```
- **Ordem dos bytes:** Estão expressos por **ordem inversa (little-endian)**. O último byte da representação em string (`0x23`) é o primeiro byte da macro, e os dois primeiros bytes (`0x00, 0x00`) são os dois últimos da macro.

#### c) Declarações `BLE_UUID128_INIT` para o grupo com `node_id = 1022 = 0x03FE`
- O UUID base do serviço é `E0C0DE00-0000-4000-8000-0000000003FE`.
- O UUID da primeira característica (Período) é `E0C0DE01-0000-4000-8000-0000000003FE`.
- O UUID da segunda característica (Código) é `E0C0DE02-0000-4000-8000-0000000003FE`.

Invertendo os 16 bytes de cada string (do byte 15 ao byte 0):
```c
/* Declaração do Serviço Proprietário de Configuração */
static const ble_uuid128_t config_svc_uuid =
    BLE_UUID128_INIT(0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                     0x00, 0x40, 0x00, 0x00, 0x00, 0xde, 0xc0, 0xe0);

/* Declaração da Característica 1 (Período de Amostragem) */
static const ble_uuid128_t period_chr_uuid =
    BLE_UUID128_INIT(0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                     0x00, 0x40, 0x00, 0x00, 0x01, 0xde, 0xc0, 0xe0);

/* Declaração da Característica 2 (Código de Acesso) */
static const ble_uuid128_t passkey_chr_uuid =
    BLE_UUID128_INIT(0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                     0x00, 0x40, 0x00, 0x00, 0x02, 0xde, 0xc0, 0xe0);
```

---

## 3.3.1 O Environmental Sensing Service & Segurança

### QUESTÃO 9

#### Arquitetura implementada no projeto `NimBLE_ESS_Security`
- **Isolamento e Mutex:**
  - Foi criada a tarefa `acquisition_task` que executa a cada 2 s, lê o DHT20 e armazena os valores convertidos numa estrutura em RAM protegida por um **Mutex FreeRTOS** (`s_sensor_mutex`).
  - **Justificação (comparação com a Questão 9 da aula de Wi-Fi):**
    Na aula de Wi-Fi / HTTPS, a leitura I2C era efetuada diretamente no tratador de pedidos HTTP porque o lwIP/HTTPD corre em tarefas separadas bloqueáveis por sockets TCP. Pelo contrário, no BLE NimBLE, as funções de acesso GATT e eventos GAP correm na **tarefa central do NimBLE Host**. A leitura de um sensor I2C como o DHT20 obriga a uma espera de conversão de **80 ms**. Se essa espera ocorresse dentro da função de acesso GATT, a tarefa do host ficaria congelada durante 80 ms, impedindo o processamento de pacotes da Link Layer, confirmações e temporizadores de supervisão, gerando desastres de *supervision timeout* e desconexão de rádio! Ao desacoplar a aquisição para uma tarefa própria com cache protegida por mutex, o callback GATT responde em **sub-microssegundos** a partir da RAM.
- **Notificação:**
  - Após a medição e libertação do mutex, a tarefa invoca `ble_gatts_chr_updated(temp_val_handle)` e `ble_gatts_chr_updated(humidity_val_handle)`. Esta função apenas agenda de forma não-bloqueante a emissão das notificações pela tarefa do host para todos os clientes subscritos.
- **Valor Desconhecido:**
  - Caso o sensor falhe ou ainda não tenha sido lido, devolve `0x8000` (-32768) na temperatura e `0xFFFF` (65535) na humidade, conforme a norma GATT (Tabela 8).
- **Anúncio com UUID 0x181A:**
  - Incluído nos campos `uuids16` do pacote de anúncio, ocupando 4 bytes e respeitando a quota de 31 bytes.

#### Comparação com o Servidor HTTPS da Aula de Wi-Fi
| Critério | Servidor HTTPS (Wi-Fi) | Servidor GATT (Bluetooth LE) |
|---|---|---|
| **Quem inicia a comunicação?** | **Cliente (Pull):** O telemóvel tem de fazer *polling* enviando sucessivos pedidos HTTP GET periódicos. O servidor não pode empurrar dados sem WebSockets. | **Servidor (Push):** O periférico empurra as medições autonomamente através de **Notificações ATT** assim que há novas amostras. |
| **Sobrecarga de rede por medição** | **Centenas a milhares de bytes:** Negociação TCP (3-way handshake), cifra TLS 1.3 (certificados, chaves), cabeçalhos HTTP (`Host`, `User-Agent`, `Accept`), resposta HTTP (`200 OK`, `Content-Length`) e JSON formatado. | **Mínima (~5 a 25 bytes):** 1 byte Opcode ATT + 2 bytes Handle + 2 bytes Valor Inteiro. Coube num único pacote Link Layer de 2,4 GHz. |
| **Custo Energético** | Elevado (~80 a 120 mA contínuos com rádio Wi-Fi ligado). | Extremamente reduzido (rádio desliga entre intervalos de ligação, consumos médios < 1 mA). |

---

### QUESTÃO 10

#### a) Leitura e escrita sem emparelhar; Introdução do código; Modelo de associação
- **Sem emparelhar:**
  - A leitura das características do **ESS** (Temperatura e Humidade) tem sucesso imediato, pois o ESS é público e possui apenas as flags `READ | NOTIFY`.
  - Ao tentar escrever na característica do período (`E0C0DE01-...`), a operação é recusada com o erro ATT **`0x0F` (`BLE_ATT_ERR_INSUFFICIENT_AUTHEN`)**, uma vez que a característica exige a flag `BLE_GATT_CHR_F_WRITE_AUTHEN`.
- **Processo de emparelhamento:**
  - O smartphone recebe o erro e despoleta automaticamente o procedimento SMP de emparelhamento (*pairing*).
  - No terminal do ESP32-C6 surge o log do evento `BLE_GAP_EVENT_PASSKEY_ACTION`:
    ```
    ================================================
    >>> ENTER PASSKEY ON PEER DEVICE: 482915 <<<
    ================================================
    ```
  - Introduzindo este código de 6 dígitos no pop-up do smartphone, a ligação completa a troca de chaves e o evento `BLE_GAP_EVENT_ENC_CHANGE` confirma:
    `encrypted=1, authenticated=1, bonded=1`.
- **Que modelo de associação foi usado e porquê?**
  Foi usado o modelo **Passkey Entry**.
  - O ESP32-C6 declara à pilha NimBLE que apenas tem ecrã:
    `ble_hs_cfg.sm_io_cap = BLE_HS_IO_DISPLAY_ONLY`.
  - O smartphone possui ecrã e teclado (*KeyboardDisplay*).
  - De acordo com a matriz de associação SMP da especificação Bluetooth, a combinação `DisplayOnly` + `KeyboardDisplay` seleciona compulsoriamente o modelo **Passkey Entry** (o dispositivo com ecrã exibe o código aleatório de 6 dígitos e o dispositivo com teclado introduz o código).

#### b) Teste do período de amostragem
- Escrever o valor `10` (em 2 bytes little-endian: `0A 00`): aceite com sucesso; o log confirma `Sampling period updated to 10 s` e as notificações do DHT20 passam a ser emitidas de 10 em 10 segundos.
- Escrever `0` (`00 00`): rejeitado com erro **`0x13` (`BLE_ATT_ERR_VALUE_NOT_ALLOWED`)** pois $0 \notin [1, 3600]$.
- Escrever `5000` (`88 13`): rejeitado com erro **`0x13` (`BLE_ATT_ERR_VALUE_NOT_ALLOWED`)** pois $5000 > 3600$.

#### c) Reinício da placa e persistência de Bonds na NVS
- Ao ativar a opção no menuconfig:
  `Component config > Bluetooth > NimBLE Options > Security (SMP) > Enable BLE SM feature > Persist the BLE Bonding keys in NVS` (`CONFIG_BT_NIMBLE_NVS_PERSIST=y`), as chaves LTK e de identificação são guardadas na partição NVS.
- Ao reiniciar a placa (RST) e ligar novamente o telemóvel, a ligação volta a ser **cifrada e autenticada automaticamente sem pedir código**, pois ambos os dispositivos reconhecem a chave guardada (*bond*).
- **Por que no exemplo original `NimBLE_Security` esta opção não bastaria?**
  No exemplo original da Espressif `NimBLE_Security`, a função `adv_init()` executava sempre:
  ```c
  set_random_addr(); // chama ble_hs_id_gen_rnd()
  ```
  Isso gerava um endereço MAC estático aleatório **novo e diferente a cada arranque** do SoC. Para o smartphone, tratava-se de um dispositivo Bluetooth completamente novo e desconhecido, tornando impossível associar o novo endereço ao registo de bonding existente na sua base de dados local! Ao usar o **endereço público fixo** da placa (`own_addr_type = 0`), o smartphone reconhece o mesmo endereço em todos os arranques e restaura a bond sem intervenção do utilizador.

#### d) Análise de vulnerabilidade face a um atacante passivo
- **Com LE Secure Connections (BLE 4.2+):**
  - **O atacante NÃO consegue obter o código.**
  - O emparelhamento LE Secure Connections utiliza o protocolo criptográfico **ECDH (Elliptic Curve Diffie-Hellman sobre a curva P-256)**. O segredo partilhado (*Diffie-Hellman shared secret*) é calculado com base nas chaves públicas dos dois intervenientes. Mesmo que o atacante intercepte todo o tráfego rádio pelo ar, o problema computacional do logaritmo discreto em curvas elípticas impede-o de calcular a chave de cifra, e a escrita viaja cifrada com **AES-CCM**.
- **Com Just Works em LE Legacy (BLE 4.0/4.1):**
  - **O atacante obtém o código com facilidade total.**
  - No LE Legacy Just Works, a chave temporária (TK) é nula ($\text{TK} = 0$). Um atacante passivo que grave os pacotes do SMP deriva a chave LTK diretamente e decifra a totalidade da sessão.
- **Com Passkey Entry em LE Legacy:**
  - **O atacante também consegue quebrar a segurança.**
  - No LE Legacy, o passkey de 6 dígitos tem apenas $10^6$ combinações possíveis ($000000$ a $999999$). O atacante pode efetuar um ataque de força bruta offline nas variáveis $Mconfirm$ e $Sconfirm$ interceptadas no ar em menos de 1 segundo num computador vulgar, derivando a chave e decifrando os dados.

#### e) Proposta de formato com campo de versão para características proprietárias
Para acomodar versões futuras da especificação de dados mantendo compatibilidade retroativa, define-se uma estrutura compacta (*packed*):
```c
typedef struct __attribute__((packed)) {
    uint8_t  format_version; // Versão do layout dos dados (ex: 0x01)
    uint16_t period_s;       // Período em segundos (uint16 little-endian)
} prop_period_v1_t;
```
- **Tamanho total:** 3 bytes.
- **Regra de validação:**
  - Na leitura: o servidor devolve `[0x01, period_lsb, period_msb]`.
  - Na escrita: a aplicação valida se `len == sizeof(prop_period_v1_t) == 3`. Se `format_version == 0x01`, aceita e processa o valor; se for desconhecido (ex: `0x02`), rejeita com `BLE_ATT_ERR_VALUE_NOT_ALLOWED`.

---

## 4. Instruções de Execução no VSCode

Para compilar, descarregar e monitorizar qualquer um dos projetos através do VSCode no Linux:

1. **Através do Menu de Tarefas do VSCode (`Ctrl + Shift + B` ou `Terminal > Run Task`):**
   - `Build NimBLE_Beacon`
   - `Flash & Monitor NimBLE_Beacon`
   - `Build NimBLE_Connection`
   - `Flash & Monitor NimBLE_Connection`
   - `Build NimBLE_GATT_Server`
   - `Flash & Monitor NimBLE_GATT_Server`
   - **`Build NimBLE_ESS_Security (Q9 & Q10)`** *(Build Default)*
   - **`Flash & Monitor NimBLE_ESS_Security`**
   - **`Run BLE Scanner (ble_scan.py)`**

2. **Através do Terminal integrado:**
   ```bash
   # Ativar ambiente do ESP-IDF v6.1.0
   . /home/andre/.espressif/tools/activate_idf_v6.1.sh

   # Navegar para o projeto final (Questões 9 e 10)
   cd /home/andre/Desktop/Universidade/4ano/DC/aula6/NimBLE_ESS_Security

   # Compilar
   idf.py build

   # Descarregar firmware e abrir monitor de porta série
   idf.py flash monitor
   ```

3. **No smartphone (Android / iOS):**
   - Abrir o **nRF Connect for Mobile**.
   - No separador **SCANNER**, localizar `"DC-P2-G07"`.
   - Carregar em **CONNECT**: o LED on-board (GPIO 8) acende.
   - Expandir o serviço **Environmental Sensing (`0x181A`)**:
     - Ativar o ícone de notificações nas características **Temperature** e **Humidity**: as leituras atualizam a cada 2 s.
   - Expandir o serviço proprietário **`E0C0DE00-0000-4000-8000-0000000003FE`**:
     - Carregar na seta de escrita da característica **`E0C0DE01-...`** e enviar um novo período (ex: `0A 00` para 10 segundos).
     - O smartphone solicitará o código de emparelhamento PIN: introduzir os 6 dígitos impressos no terminal do ESP32.
     - A ligação fica encriptada, autenticada e emparelhada (*bonded*), e as notificações passam a ser transmitidas a cada 10 segundos!
