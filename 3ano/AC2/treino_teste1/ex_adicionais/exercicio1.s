# Definição dos endereços dos registos
.equ TRISB,  0xBF886040
.equ PORTB,  0xBF886050
.equ TRISE,  0xBF886100
.equ LATE,   0xBF886120

# Endereços UART2 (assumidos para envio para o PC - U2TXREG e U2STA)
.equ U2STA,   0xBF806210
.equ U2TXREG, 0xBF806220

.data
.text
.globl main

main:
    # 1. Configurar RE7 como saída e RB3-RB0 como entradas
    li $t0, TRISE
    lw $t1, 0($t0)
    andi $t1, $t1, 0xFF7F     # Limpar bit 7 (RE7 = Output)
    sw $t1, 0($t0)

    li $t0, TRISB
    lw $t1, 0($t0)
    ori $t1, $t1, 0x000F      # Setar bits 3 a 0 (RB3-RB0 = Input)
    sw $t1, 0($t0)

    # 2. Valor inicial de RE7 a '1'
    li $t0, LATE
    lw $t1, 0($t0)
    ori $t1, $t1, 0x0080      # Setar bit 7 a '1'
    sw $t1, 0($t0)

loop_infinito:
    # Ler dip-switches (RB3 a RB0)
    li $t0, PORTB
    lw $t1, 0($t0)
    andi $t1, $t1, 0x000F     # Isolar os 4 bits menos significativos

    # Complemento lógico do valor lido
    not $t1, $t1
    andi $t1, $t1, 0x000F     # Manter apenas os 4 bits após o NOT

    # Converter para ASCII ('0'-'9', 'A'-'F')
    li $t2, 9
    ble $t1, $t2, eh_numero
    nop
    # Se for maior que 9 (A-F), somar 7 extra para saltar os caracteres entre '9' e 'A'
    addi $t1, $t1, 7
eh_numero:
    addi $t1, $t1, 48         # Somar 48 (código ASCII do '0')

    # Enviar caracter (em $t1) para o PC (UART2)
    jal putc
    nop

    # Complementar o valor do LED no porto RE7
    li $t0, LATE
    lw $t2, 0($t0)
    xori $t2, $t2, 0x0080     # Toggle no bit 7
    sw $t2, 0($t0)

    # Esperar 250ms (4 vezes por segundo)
    # 250ms = 125 * 2ms. Logo, argumento = 125
    li $a0, 125
    jal delay
    nop

    j loop_infinito
    nop

#---------------------------------------------------------
# Função delay
# Argumento: $a0 (número de blocos de 2ms)
#---------------------------------------------------------
delay:
    li $t4, 40000             # Ciclos do Core Timer para 2ms (assumindo relógio a 20MHz)
delay_loop:
    beq $a0, $zero, end_delay
    nop
    mfc0 $t5, $9              # Ler Core Timer inicial
wait_2ms:
    mfc0 $t6, $9              # Ler Core Timer atual
    sub $t6, $t6, $t5         # Diferença
    bltu $t6, $t4, wait_2ms   # Se diferença < 40000, continua a esperar
    nop
    
    addi $a0, $a0, -1         # Decrementar blocos de 2ms a esperar
    j delay_loop
    nop
end_delay:
    jr $ra
    nop

#---------------------------------------------------------
# Função putc (UART2 Polling)
# Envia o byte em $t1 para o PC
#---------------------------------------------------------
putc:
    li $t8, U2STA
wait_tx:
    lw $t9, 0($t8)
    andi $t9, $t9, 0x0200     # Verificar bit UTXBF (Transmit Buffer Full)
    bne $t9, $zero, wait_tx   # Se cheio, espera
    nop
    li $t8, U2TXREG
    sw $t1, 0($t8)            # Escrever caracter
    jr $ra
    nop
