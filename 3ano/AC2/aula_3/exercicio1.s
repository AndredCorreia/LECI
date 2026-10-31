.equ SFR_BASE_HI, 0xBF88

    # Usamos os registos mágicos SET e CLR para a configuração
    .equ TRISBSET, 0x6048       # Offset para forçar bits a 1 no TRISB
    .equ TRISECLR, 0x6104       # Offset para forçar bits a 0 no TRISE
    
    .equ PORTB, 0x6050          # Offset para ler Porto B
    .equ LATE,  0x6120          # Offset para escrever no Porto E

    .text
    .globl main

main:
    lui  $t1, SFR_BASE_HI       # $t1 = 0xBF880000
    
    li   $t2, 1                 # Máscara com o bit 0 a '1' (0x0001)

    # 1. Configurar Entradas e Saídas diretamente!
    sw   $t2, TRISBSET($t1)     # TRISB[0] = 1 (RB0 como entrada)
    sw   $t2, TRISECLR($t1)     # TRISE[0] = 0 (RE0 como saída)

loop:
    # 2. Ler o interruptor
    lw   $t3, PORTB($t1)        # Lê o Porto B
    andi $t3, $t3, 1            # Isola o bit 0 (fica com 1 ou 0)

    # 3. Escrever no LED
    sw   $t3, LATE($t1)         

    j    loop
