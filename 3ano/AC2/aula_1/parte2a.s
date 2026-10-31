	.text
    	.globl main

main:
    #Prologo
    addiu $sp, $sp, -4    # Reserva espaço na pilha para o $ra
    sw    $ra, 0($sp)      # Salva $ra (boa prática, mesmo com syscalls)

    li    $s0, 0           # cnt = 0

loop:

    li    $v0, 2           # Código da syscall getChar na DETPIC32
    syscall                # O caractere lido retorna em $v0
    move  $s1, $v0         # c = $v0


    move  $a0, $s1         # Coloca o char em $a0
    li    $v0, 3           # Código da syscall putChar na DETPIC32
    syscall


    addiu $s0, $s0, 1      # Incrementa o contador


    li    $t0, '\n'        # O montador entende '\n' ou 10
    bne   $s1, $t0, loop   # Se c != '\n', repete


    move  $a0, $s0         # $a0 = cnt
    li    $a1, 10          # $a1 = base 10
    li    $v0, 6           # Código da syscall printInt na DETPIC32
    syscall


    #Epilogo
    li    $v0, 0           # return 0
    lw    $ra, 0($sp)      # Restaura $ra
    addiu $sp, $sp, 4      # Libera a pilha
    jr    $ra              # Volta para o monitor da placa
