	.equ parteHI, 0xBF88
	.equ TRISECLR, 0x6104
	.equ TRISDSET, 0x60C8
	
	.equ PORTD, 0x60D0
	.equ LATE, 0x6120
	.text
	.globl main
	
main:
	lui $t1, parteHI
	li $t2, 1
	
	sw $t2, TRISECLR($t1)
	sw $t2, TRISDSET($t1)
	
loop:
	lw $t3, PORTD($t1)
	
	andi $t3, $t3, 256
	srl $t3, $t3, 8
	not $t3, $t3
	sw $t3, LATE($t1)
	
	j loop
	
	
