	.equ ADDR_BASE_HI, 0xBF88
    
    # Offsets dos registos (Base + Offset)
    	.equ TRISB, 0x6040
    	.equ TRISE, 0x6100
    	.equ PORTB, 0x6050
    	.equ LATE,  0x6110
    	.equ AD1PCFG, 0x9060    # Registo para configurar pinos como Digitais

    	.data
    	.text
    	.globl main

main:
    	lui   $t0, ADDR_BASE_HI       # Endereço base dos periféricos

    # 1. Configurar RB0 como Digital (Muito importante no Porto B!)
    	lw    $t1, AD1PCFG($t0)
    	ori   $t1, $t1, 0x0001  # Define bit 0 como digital (1 = digital)
    	sw    $t1, AD1PCFG($t0)

    # 2. Configurar Direções (TRIS)
    	lw    $t1, TRISE($t0)
    	ins   $t1, $zero, 0, 1  # RE0 como saída (0)
    	sw    $t1, TRISE($t0)

    	lw    $t1, TRISB($t0)
    	ori   $t1, $t1, 0x0001  # RB0 como entrada (1)
    	sw    $t1, TRISB($t0)

loop:
    # 3. Ler o estado do Switch (RB0)
    	lw    $t1, PORTB($t0)   # Lê todo o Porto B
    	
    	not $t1, $t1		# Inverte os bits
    	andi  $t1, $t1, 0x0001  # Isola o bit 0 (RB0)

    # 4. Escrever no LED (RE0)
    	lw    $t2, LATE($t0)    # Lê o estado atual do Latch E
    	ins   $t2, $t1, 0, 1    # Insere o valor lido de RB0 no bit 0 de LATE
    	sw    $t2, LATE($t0)    # Atualiza o hardware

    	j     loop              # Salto incondicional para o início do ciclo
    	nop                     # Branch delay slot
