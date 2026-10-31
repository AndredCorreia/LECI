.equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        .equ PRINT_INT, 6
        .equ PUT_CHAR, 3
        
        .data
        .text
        .globl main
        
main:
    li $s0, 0           # cnt1 (1 Hz)
    li $s1, 0           # cnt3.33 (3.3333 Hz)
    li $s2, 0           # cnt5 (5 Hz)
    li $s3, 0           # i = 0

while:
    li $a0, '\r'
    li $v0, PUT_CHAR
    syscall
    
    # Imprimir cnt1 (1Hz)
    move $a0, $s0
    li $a1, 0x0005000A  
    li $v0, PRINT_INT
    syscall
    
    li $a0, ' '
    li $v0, PUT_CHAR    
    syscall
    
    # Imprimir cnt3.33 (3.3333Hz)
    move $a0, $s1
    li $a1, 0x0005000A  
    li $v0, PRINT_INT
    syscall
    
    li $a0, ' '
    li $v0, PUT_CHAR    
    syscall
    
    # Imprimir cnt5 (5Hz)
    move $a0, $s2      
    li $a1, 0x0005000A  
    li $v0, PRINT_INT
    syscall
    
    # Delay base de 100ms (MDC entre 1000, 300 e 200)
    li $a0, 100
    jal delay
    
    addi $s3, $s3, 1    # i++
    
    # Lógica para 5Hz (1000/5 = 200ms -> i % 2 == 0)
    li $t0, 2
    rem $t1, $s3, $t0
    bne $t1, $zero, check_3
    addi $s2, $s2, 1
    
check_3:
    # Lógica para 3.3333Hz (1000/3.3333 = 300ms -> i % 3 == 0)
    li $t0, 3
    rem $t1, $s3, $t0
    bne $t1, $zero, check_cnt1 # Corrigido: label coincidente com a de baixo
    addi $s1, $s1, 1
    
check_cnt1:
    # Lógica para 1Hz (1000/1 = 1000ms -> i % 10 == 0)
    li   $t0, 10
    rem  $t1, $s3, $t0  
    bne  $t1, $zero, end_loop
    addi $s0, $s0, 1    # cnt1++


end_loop:
    j while

delay:
    li $v0, RESET_CORE_TIMER
    syscall
    li $t6, 20000       # K = 20000 para 1ms @ 20MHz
    multu $a0, $t6
    mflo $t7
wait_loop:
    li $v0, READ_CORE_TIMER
    syscall
    bltu $v0, $t7, wait_loop
    jr $ra
