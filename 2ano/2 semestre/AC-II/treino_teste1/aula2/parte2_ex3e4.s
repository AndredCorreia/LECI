.equ PRINT_INT, 6
    .equ PUT_CHAR, 3
    .equ INKEY, 1

    # ==========================================
    # Secção de Memória
    # ==========================================
    .data
cnt1:     .word 0
cnt5:     .word 0
cnt10:    .word 0
speed:    .word 2    # 2 = Normal (100ms), 1 = Acelerado (50ms)
run_flag: .word 1    # 1 = A contar, 0 = Suspenso

    # ==========================================
    .text
    .globl main

main:
    addiu $sp, $sp, -4
    sw    $ra, 0($sp)

while_loop:
    # --- Leitura do Teclado (inkey) ---
    li    $v0, 1
    syscall
    move  $t0, $v0           # Guarda o carater lido em $t0

    # Verifica 'A' ou 'a' (Acelerar)
    li    $t1, 'A'
    beq   $t0, $t1, set_A
    li    $t1, 'a'
    beq   $t0, $t1, set_A

    # Verifica 'N' ou 'n' (Normal)
    li    $t1, 'N'
    beq   $t0, $t1, set_N
    li    $t1, 'n'
    beq   $t0, $t1, set_N

    # Verifica 'S' ou 's' (Suspender)
    li    $t1, 'S'
    beq   $t0, $t1, set_S
    li    $t1, 's'
    beq   $t0, $t1, set_S

    # Verifica 'R' ou 'r' (Retomar)
    li    $t1, 'R'
    beq   $t0, $t1, set_R
    li    $t1, 'r'
    beq   $t0, $t1, set_R

    j     print_display      # Se nenhuma tecla útil foi premida, salta para o ecrã

set_A:
    li    $t1, 1             # speed = 1 (Espera 50ms)
    sw    $t1, speed
    j     print_display
set_N:
    li    $t1, 2             # speed = 2 (Espera 100ms)
    sw    $t1, speed
    j     print_display
set_S:
    li    $t1, 0             # run_flag = 0 (Suspenso)
    sw    $t1, run_flag
    j     print_display
set_R:
    li    $t1, 1             # run_flag = 1 (A contar)
    sw    $t1, run_flag

print_display:
    # putChar('\r') -> Volta ao início da linha
    li    $a0, '\r'
    li    $v0, 3
    syscall

    # printInt(cnt1)
    lw    $a0, cnt1
    li    $a1, 0x0005000A
    li    $v0, 6
    syscall

    # putChar(' ')
    li    $a0, ' '
    li    $v0, 3
    syscall

    # printInt(cnt5)
    lw    $a0, cnt5
    li    $a1, 0x0005000A
    li    $v0, 6
    syscall

    # putChar(' ')
    li    $a0, ' '
    li    $v0, 3
    syscall

    # printInt(cnt10)
    lw    $a0, cnt10
    li    $a1, 0x0005000A
    li    $v0, 6
    syscall

    # --- Espera Dinâmica (Baseada na tecla premida) ---
    lw    $a0, speed         # Passa 1 (50ms) ou 2 (100ms)
    jal   wait


    
    # Verifica se estamos suspensos antes de incrementar!
    lw    $t0, run_flag
    beqz  $t0, loop_end      # Se run_flag == 0, salta os incrementos e volta ao início

    # cnt10++
    lw    $t0, cnt10         
    addi  $t0, $t0, 1        
    sw    $t0, cnt10         

    # if (cnt10 % 2 == 0) cnt5++
    andi  $t1, $t0, 1        
    bnez  $t1, check_cnt1    
    lw    $t2, cnt5          
    addi  $t2, $t2, 1        
    sw    $t2, cnt5          

check_cnt1:
    # if (cnt10 % 10 == 0) cnt1++
    li    $t1, 10
    div   $t0, $t1           
    mfhi  $t2                
    bnez  $t2, loop_end      
    lw    $t3, cnt1          
    addi  $t3, $t3, 1        
    sw    $t3, cnt1          

loop_end:
    j     while_loop

    lw    $ra, 0($sp)
    addiu $sp, $sp, 4
    jr    $ra

wait:
    li    $t0, 0             
    li    $t1, 257500        # METADE DE 515000 (Assim ts=1 são 50ms)
    mult  $a0, $t1           
    mflo  $t1                

wait_loop:
    bge   $t0, $t1, wait_end 
    addi  $t0, $t0, 1        
    j     wait_loop

wait_end:
    jr    $ra
