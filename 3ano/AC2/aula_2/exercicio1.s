	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT,6
	.data
	.text
	.globl main

main: li $t0,0 				# counter=0
while: 					# while (1) {
	li $a0, '\r'
	li $v0, PUT_CHAR
	syscall
	
	move  $a0, $t0
	li $t1, 4
	sll $t1, $t1, 16		#4<<16
	ori $a1, $t1,10			#$a1= (4<<16)|10
	li $v0, PRINT_INT
	syscall
	
 	li $v0,RESET_CORE_TIMER 	#
 	syscall			 	# resetCoreTimer()
 	
 	
 wait:
 	li $v0, READ_CORE_TIMER
 	syscall
 	li $t1, 20000000		#1hz->20milhoes, 5hz->4milhoes, 10hz->2milhao
 	blt $v0, $t1, wait		#se $v0<200000 repete leitura
 	addi $t0, $t0, 1
 	j while 			# }
 	
 	
 	
 	jr $ra # 
