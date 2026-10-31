	.equ SFR_BASE, 0xBF880000
    
    # Offsets dos registos (Base + Offset)
    	.equ TRISD, 0x60C0
    	.equ TRISE, 0x6100
    	.equ PORTD, 0x60D0
    	.equ LATE,  0x6110


    	.data
    	.text
    	.globl main

main:
    	lui   $t0, 0xBF88       # Endereço base dos periféricos

    # 1. Configurar RE0 como saída (TRISE bit 0 = 0)
    	lw    $t1, TRISE($t0)
    	ins   $t1, $zero, 0, 1
    	sw    $t1, TRISE($t0)

    # 2. Configurar RD8 como entrada (TRISD bit 8 = 1)
    	lw    $t1, TRISD($t0)
    	ori   $t1, $t1, 0x0100    # 0x0100 corresponde ao bit 8 (2^8)
    	sw    $t1, TRISD($t0)

loop:
    # 3. Ler o estado de RD8
    	lw    $t1, PORTD($t0)
    	not   $t1, $t1		#negacao dos bits
    	ext   $t1, $t1, 8, 1      # EXT (Extract): extrai 1 bit da posição 8 para a posição 0 de $t1

    # 4. Escrever no LED (RE0)
    	lw    $t2, LATE($t0)
   	ins   $t2, $t1, 0, 1      # Insere o bit extraído no bit 0 do LED
    	sw    $t2, LATE($t0)

    	j     loop
    	nop
