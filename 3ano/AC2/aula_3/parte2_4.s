.equ SFR_BASE,   0xBF880000 
.equ TRISE,      0x6100
.equ LATE,       0x6120
.equ TRISB,      0x6040
.equ PORTB,      0x6050

.text
.globl main
main:
    lui  $t0, %hi(SFR_BASE)
    
    # 1. Configurar RE4-RE1 como saídas e RB1 como entrada
    lw   $t1, TRISE($t0)
    andi $t1, $t1, 0xFFE1
    sw   $t1, TRISE($t0)
    lw   $t1, TRISB($t0)
    ori  $t1, $t1, 0x0002   # RB1 = Input
    sw   $t1, TRISB($t0)

    # 2. Inicializar (Um LED aceso)
    li   $t2, 1             # 0001

loop:
    # 3. Atualizar Saídas
    lw   $t1, LATE($t0)
    andi $t1, $t1, 0xFFE1
    sll  $t3, $t2, 1
    or   $t1, $t1, $t3
    sw   $t1, LATE($t0)

    # 4. Esperar 3 Hz -> 6.666.667 tics
    li   $v0, 12
    syscall
wait:
    li   $v0, 11
    syscall
    li   $t4, 6666667
    blt  $v0, $t4, wait

    # 5. Lógica Ring (RB1 controla sentido)
    lw   $t5, PORTB($t0)
    andi $t5, $t5, 0x0002
    beq  $t5, $zero, shift_r

    # Esquerda: 0001 -> 0010 -> 0100 -> 1000 -> 0001
    sll  $t2, $t2, 1
    andi $t6, $t2, 0x0010   # Passou do bit 3?
    beq  $t6, $zero, done
    li   $t2, 1
    j    done

shift_r:
    # Direita: 1000 -> 0100 -> 0010 -> 0001 -> 1000
    andi $t6, $t2, 0x0001   # Está no bit 0?
    beq  $t6, $zero, move_r
    li   $t2, 8
    j    done
move_r:
    srl  $t2, $t2, 1

done:
    andi $t2, $t2, 0x000F
    j    loop
