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
	
	li $v0, 12
	syscall
	
wait:
	li $v0, 11
	syscall
	li $t1, 20000000
	blt $v0, $t1, wait
	addi $t0, $t0, 1
	
	j while
	
	jr $ra
