	# Direcionar o código para a memória de programa
	.data
# Constantes (exemplo de endereços comuns no PIC32)
	.equ SFR_BASE, 0xBF88       # Base dos registos SFR
	.equ TRISE,    0x6100       # Offset TRISE
	.equ LATE,     0x6120       # Offset LATE
	.equ TRISB,    0x6040       # Offset TRISB
	.equ PORTB,    0x6050       # Offset PORTB

# Syscalls Core Timer
	.equ RESET_CORE_TIMER, 12
	.equ READ_CORE_TIMER,  11

	.text
	.globl main

main:
    	lui  $t0, SFR_BASE      # Inicializar $t0 com a base dos SFRs

    # 1. Configurar Portos (RE4-RE1 como saídas)
    	lw   $t1, TRISE($t0)
    	andi $t1, $t1, 0xFFE1   # Limpar bits 4, 3, 2, 1 (0 = Output)
    	sw   $t1, TRISE($t0)
    	lw $t1, TRISB($t0)
    	ori $t1,$t1,0x000E
	sw $t1, TRISB($t0)
    # 2. Inicializar Variável de Contagem
    	li   $t2, 0             # Contador começa em 0

loop:
    # 3. Atualizar Portos de Saída (RE4-RE1)
    	lw   $t1, LATE($t0)
    	andi $t1, $t1, 0xFFE1   # Preservar outros bits, limpar RE4-RE1
    
    # Alinhamento: O contador de 4 bits (0-15) deve ir para RE1, RE2, RE3, RE4
    # Como o bit menos significativo do contador está na pos 0, fazemos shift 1
    	sll  $t3, $t2, 1        # $t3 = $t2 << 1
    	or   $t1, $t1, $t3      # "Fundir" o contador com o estado atual do LATE
    	sw   $t1, LATE($t0)     # Escrever no porto

    # 4. Esperar t segundos (f = 2Hz -> T = 0.5s)
    # No PIC32, o Core Timer conta à metade da freq. do CPU (ex: 20MHz se CPU=40MHz)
    # 0.5s * 20,000,000 = 10,000,000 (10^7)
    	li   $v0, RESET_CORE_TIMER
    	syscall
wait:
    	li   $v0, READ_CORE_TIMER
    	syscall
    	blt  $v0, 20000000, wait # Ajustar este valor conforme a frequência do seu clock

    # 5. Atualizar Variável de Contagem
    	addi $t2, $t2, 1        # Incrementar
    	andi $t2, $t2, 0x000F   # Manter apenas 4 bits (MOD 16)

   	j    loop               # Repetir infinitamente
