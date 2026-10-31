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
	
 	li $a0, 1000            # Exemplo: 1Hz (1000ms)
    	jal delay               

	addi $t0, $t0, 1        # counter++
 	j while                 # }
    
	jr $ra
 	

delay:
	li $v0,RESET_CORE_TIMER
	syscall
	
	li $t2, 20000			#K= 20000
	multu $a0, $t2			#ms*k
	mflo $t3			

 wait:
 	li $v0, READ_CORE_TIMER
 	syscall

 	bltu $v0, $t3, wait		#enquanto timer<limite, espera

 	 		 	
 	jr $ra # 
