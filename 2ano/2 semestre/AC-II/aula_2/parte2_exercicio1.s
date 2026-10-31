.equ PRINT_INT, 6
    .equ PUT_CHAR, 3

    # ==========================================
    # Secção de Memória (À prova de bugs do monitor!)
    # ==========================================
    .data
cnt1:   .word 0
cnt5:   .word 0
cnt10:  .word 0

    # ==========================================
    .text
    .globl main

main:
    addiu $sp, $sp, -4
    sw    $ra, 0($sp)

while_loop:
    # putChar('\r') -> Volta ao início da linha
    li    $a0, '\r'
    li    $v0, PUT_CHAR
    syscall

    # printInt(cnt1)
    lw    $a0, cnt1          # Lê o valor atual da memória
    li    $a1, 0x0005000A
    li    $v0, PRINT_INT
    syscall

    # putChar(' ')
    li    $a0, ' '
    li    $v0, PUT_CHAR
    syscall

    # printInt(cnt5)
    lw    $a0, cnt5
    li    $a1, 0x0005000A
    li    $v0, PRINT_INT
    syscall

    # putChar(' ')
    li    $a0, ' '
    li    $v0, PUT_CHAR
    syscall

    # printInt(cnt10)
    lw    $a0, cnt10
    li    $a1, 0x0005000A
    li    $v0, PRINT_INT
    syscall

    # wait(1) -> Espera 100 ms
    li    $a0, 1
    jal   wait

    # ==========================================
    # Lógica de Incremento (Usando a Memória)
    # ==========================================
    
    # cnt10++
    lw    $t0, cnt10         # Lê cnt10
    addi  $t0, $t0, 1        # Incrementa
    sw    $t0, cnt10         # Guarda de volta na memória

    # if (cnt10 % 2 == 0) cnt5++
    andi  $t1, $t0, 1        # Verifica se é ímpar
    bnez  $t1, check_cnt1    # Se for ímpar, salta
    lw    $t2, cnt5          # Se for par, lê cnt5
    addi  $t2, $t2, 1        # Incrementa
    sw    $t2, cnt5          # Guarda cnt5

check_cnt1:
    # if (cnt10 % 10 == 0) cnt1++
    li    $t1, 10
    div   $t0, $t1           # Divide cnt10 por 10
    mfhi  $t2                # Vai buscar o resto
    bnez  $t2, loop_end      # Se o resto != 0, salta
    lw    $t3, cnt1          # Se == 0, lê cnt1
    addi  $t3, $t3, 1        # Incrementa
    sw    $t3, cnt1          # Guarda cnt1

loop_end:
    j     while_loop

    lw    $ra, 0($sp)
    addiu $sp, $sp, 4
    jr    $ra

# ==========================================================
# void wait(int ts) -> Ciclo de espera (software)
# ==========================================================
wait:
    li    $t0, 0             
    li    $t1, 515000
    mult  $a0, $t1           
    mflo  $t1                

wait_loop:
    bge   $t0, $t1, wait_end 
    addi  $t0, $t0, 1        
    j     wait_loop

wait_end:
    jr    $ra
