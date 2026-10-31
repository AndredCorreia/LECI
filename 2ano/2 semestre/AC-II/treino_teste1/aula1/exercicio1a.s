	.text
	.globl main
	
main:
	li $t0,0 	#int cnt=0:	
	
do:
	li $v0, 2
	syscall
	move $t1, $v0
	
	
	move $a0, $t1
	li $v0, 3
	syscall
	
	addi $t0, $t0,1
	
	li $t2, '\n'
	bne $t0, $t2,do
	
end:
	move $a0, $t0
	li $a1, 10
	li $v0,6
	syscall
	
	li $v0, 0
	
