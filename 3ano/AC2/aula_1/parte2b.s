	.text
	.globl main
	
main:
	addiu $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	
	li $s0, 0
	
main_loop:
    # --- c = inkey() (Syscall 1) ---
    li    $v0, 1           
    syscall
    move  $s1, $v0         # c = inkey()

    # --- if( c == 'R' ) cnt = 0 ---
    li    $t0, 'R'
    bne   $s1, $t0, skip_reset
    li    $s0, 0           # cnt = 0
skip_reset:

    # --- putChar('\r') (Syscall 3) ---
    li    $v0, 3
    li    $a0, '\r'        # Carriage return
    syscall

   # --- printInt(cnt, 10 | 3 << 16) ---
    # Nota: O valor 0x0003000A junta a base 10 (0x0A) e o padding de 3 (0x0003 na parte alta)
    move  $a0, $s0         # $a0 = cnt (supondo que "cnt" reside em $s0)
    li    $a1, 0x0003000A  # Carrega imediatamente o valor calculado (3 << 16 | 10)
    li    $v0, 6           # Código da Syscall printInt
    syscall

    # --- cnt = (cnt + 1) & 0xFF ---
    addi  $s0, $s0, 1      # cnt + 1
    andi  $s0, $s0, 0xFF   # & 0xFF (mantém entre 0 e 255)

    # --- wait(4) ---
    li    $a0, 4
    jal   wait

    j     main_loop        # while(1)

# ---------------------------------------------------------
# wait(int ts)
# ---------------------------------------------------------
wait:
    li    $t0, 0           # i = 0
    li    $t1, 515000
    mult  $a0, $t1         # ts * 515000
    mflo  $t1              # limite = ts * 515000

wait_loop:
    bge   $t0, $t1, wait_end # if i >= limite, sai
    addi  $t0, $t0, 1      # i++
    j     wait_loop
wait_end:
    jr    $ra              # Volta para quem chamou
