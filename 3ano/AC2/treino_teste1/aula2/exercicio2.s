	.text
	.globl main
	
main:
	li $t0, 0		#counter = 0;

while:
	li $a0, '\r'
	li $v0, 3
	syscall
	
	move $a0, $t0
	li $a1, 0x0004000A
	li $v0, 6
	syscall
	
	li $a0, 10
	jal delay
	
	addi $t0, $t0, 1
	
	j while
delay:
	li $t2, 20000
	mult $a0, $t2
	mflo $t4
	
	li $v0, 12
	syscall
	
	
wait:
	li $v0, 11
	syscall
	

	blt $v0, $t4, wait
	
	
	jr $ra
