	.equ parteHI, 0xBF88
	.equ TRISECLR, 0x6104
	.equ TRISBSET, 0x6048
	
	.equ PORTB, 0x6050
	.equ LATE, 0x6120
	.text
	.globl main
	
main:
	lui $t1, parteHI
	
	li $t2, 1
	
	sw $t2, TRISECLR($t1)
	sw $t2, TRISBSET($t1)
	
loop:
	lw $t3, PORTB($t1)
	andi $t3, $t3, 1
	
	
	sw $t3, LATE($t1)
	
	j loop
