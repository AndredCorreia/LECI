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
    lui  $t0, 0xBF88       # Base SFR
    # 1. Configurar Portos
    lw   $t1, 0x6100($t0)  # TRISE
    andi $t1, $t1, 0xFFE1  # RE4-RE1 como saídas
    sw   $t1, 0x6100($t0)
    lw   $t1, 0x6040($t0)  # TRISB
    ori  $t1, $t1, 0x0008  # RB3 como entrada (bit 3)
    sw   $t1, 0x6040($t0)

    # 2. Inicializar
    li   $t2, 0             # Contador

loop:
    # 3. Atualizar Saídas
    lw   $t1, LATE($t0)  # LATE
    andi $t1, $t1, 0xFFE1
    sll  $t3, $t2, 1        # Alinhar com RE1
    or   $t1, $t1, $t3
    sw   $t1, 0x6120($t0)

    # 4. Esperar 0.5s (2 Hz)
    li   $v0, 12            # RESET_CORE_TIMER
    syscall
wait:
    li   $v0, 11            # READ_CORE_TIMER
    syscall
    blt  $v0, 10000000, wait

    # 5. Atualizar Contagem
    lw   $t5, 0x6050($t0)  # PORTB
    andi $t5, $t5, 0x0008  # Isolar RB3
    beq  $t5, $zero, decr

incr:
    addi $t2, $t2, 1
    j    end_cnt
decr:
    addi $t2, $t2, -1
end_cnt:
    andi $t2, $t2, 0x000F  # MOD 16
    j    loop
