	.equ SFR_BASE,   0xBF88
	.equ TRISE,      0x6100
	.equ LATE,       0x6120
	.equ TRISB,      0x6040
	.equ PORTB,      0x6050

	.equ RESET_CORE_TIMER, 12	
	.equ READ_CORE_TIMER,  11

	.text
	.globl main

main:
    lui  $t0, SFR_BASE

    # 1. Configurar Portos
    # RE4-RE1 como saídas (LEDs)
    lw   $t1, TRISE($t0)
    andi $t1, $t1, 0xFFE1
    sw   $t1, TRISE($t0)
    
    # RB2 como entrada (Dip-switch)
    lw   $t1, TRISB($t0)
    ori  $t1, $t1, 0x0004   # Bit 2 = 1 (Entrada)
    sw   $t1, TRISB($t0)

    # 2. Inicializar Variável de Contagem (4 bits)
    li   $t2, 0             # Valor inicial: 0000

loop:
    # 3. Atualizar Saídas (RE4-RE1)
    lw   $t1, LATE($t0)
    andi $t1, $t1, 0xFFE1   # Limpa bits 4-1
    sll  $t3, $t2, 1        # Alinha contador com RE1
    or   $t1, $t1, $t3
    sw   $t1, LATE($t0)

    # 4. Esperar 1.5 Hz (13.333.333 tics)
    li   $v0, RESET_CORE_TIMER
    syscall
wait:
    li   $v0, READ_CORE_TIMER
    syscall
    li   $t4, 13333333
    blt  $v0, $t4, wait

    # 5. Atualizar Variável (Lógica Johnson)
    lw   $t5, PORTB($t0)    # Ler porto de entrada
    andi $t5, $t5, 0x0004   # Isolar bit RB2

    beq  $t5, $zero, shift_right # Se RB2 == 0, vai para direita

shift_left:                 # RB2 = 1: Desloca à esquerda
    # Novo bit = NOT(bit 3)
    andi $t6, $t2, 0x0008   # Isola o bit 3 (MSB)
    srl  $t6, $t6, 3        # Move para a posição 0
    xori $t6, $t6, 0x0001   # Inverte o bit (NOT)
    
    sll  $t2, $t2, 1        # Shift left do contador
    or   $t2, $t2, $t6      # Insere o novo bit na posição 0
    andi $t2, $t2, 0x000F   # Garante 4 bits apenas
    j    end_update

shift_right:                # RB2 = 0: Desloca à direita
    # Novo bit = NOT(bit 0)
    andi $t6, $t2, 0x0001   # Isola o bit 0 (LSB)
    xori $t6, $t6, 0x0001   # Inverte o bit (NOT)
    sll  $t6, $t6, 3        # Move para a posição 3 (MSB)
    
    srl  $t2, $t2, 1        # Shift right do contador
    or   $t2, $t2, $t6      # Insere o novo bit na posição 3
    andi $t2, $t2, 0x000F   # Garante 4 bits apenas

end_update:
    j    loop
