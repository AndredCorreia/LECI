	.text
	.globl main
	
main:
	# --- Prólogo ---
    	addiu $sp, $sp, -8
    	sw    $ra, 0($sp)      # Guarda o $ra por causa do "jal wait"
    	sw    $s0, 4($sp)      # Guarda o $s0 que vamos usar para o "cnt"
    
    	li    $s0, 0           # cnt = 0;

	
while:	
	# --- c = inkey() ---
    	li    $v0, 1           # Syscall 1 (inkey)
    	syscall
    	move  $t2, $v0         # Guarda o carater lido ('c') em $t2 temporariamente
	
	li $t1, 'R'
	bne $t2, $t1, condition 
	li $s0, 0
	
	
condition:
	li $a0, '\r'
	li $v0, 3
	syscall
	
	move $a0, $s0
	li $a1, 0x0003000A
	li $v0, 6
	syscall
	
	addi $s0, $s0, 1
	andi $s0, $s0, 0xFF
	
	li $a0,4
	jal wait
	
	j while
	
	# --- Epílogo (nunca é atingido devido ao ciclo infinito, mas é boa prática) ---
    	lw    $s0, 4($sp)
    	lw    $ra, 0($sp)
    	addiu $sp, $sp, 8
    	li    $v0, 0
    	jr    $ra	
	

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
