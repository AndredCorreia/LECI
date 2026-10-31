.equ SFR_BASE,   0xBF880000 
.equ TRISE,      0x6100
.equ LATE,       0x6120

.text
.globl main
main:
    lui  $t0, %hi(SFR_BASE)
    
    # 1. Configurar RE4-RE1 como saídas
    lw   $t1, TRISE($t0)
    andi $t1, $t1, 0xFFE1
    sw   $t1, TRISE($t0)

    # 2. Inicializar
    li   $t2, 0

loop:
    # 3. Atualizar Saídas
    lw   $t1, LATE($t0)
    andi $t1, $t1, 0xFFE1
    sll  $t3, $t2, 1
    or   $t1, $t1, $t3
    sw   $t1, LATE($t0)

    # 4. Esperar 1.5 Hz -> 13.333.333 tics
    li   $v0, 12
    syscall
wait:
    li   $v0, 11
    syscall
    li   $t4, 13333333
    blt  $v0, $t4, wait

    # 5. Lógica Johnson Esquerda: Inverte o que sai da esquerda e mete à direita
    andi $t6, $t2, 0x0008   # Pega no bit 3
    srl  $t6, $t6, 3        # Move para pos 0
    xori $t6, $t6, 1        # Inverte (NOT)
    sll  $t2, $t2, 1        # Desloca tudo para a esquerda
    or   $t2, $t2, $t6      # Insere o novo bit no LSB
    andi $t2, $t2, 0x000F   # Máscara 4 bits
    j    loop
