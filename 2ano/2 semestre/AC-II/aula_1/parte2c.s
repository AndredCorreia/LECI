# Definição dos códigos das System Calls para facilitar a leitura
.equ READ_INT10, 5
.equ PRINT_INT, 6
.equ PRINT_INT10, 7
.equ PRINT_STR, 8

    .data
str1: .asciiz "\nIntroduza um inteiro (sinal e modulo): "
str2: .asciiz "\nValor em base 10 (signed): "
str3: .asciiz "\nValor em base 2: "
str4: .asciiz "\nValor em base 2, formatado: "
str5: .asciiz "\nValor em base 16: "
str6: .asciiz "\nValor em base 10 (unsigned): "
str7: .asciiz "\nValor em base 10 (unsigned), formatado: "

    .text
    .globl main

main:
    # Prólogo
    addiu $sp, $sp, -8      # Reserva espaço na pilha
    sw    $ra, 0($sp)       # Guarda o endereço de retorno
    sw    $s0, 4($sp)       # Guarda o $s0 (vamos usá-lo para a variável 'value')

loop_c:
    # --- printStr("\nIntroduza um inteiro..."); ---
    la    $a0, str1
    li    $v0, PRINT_STR
    syscall

    # --- value = readInt10(); ---
    li    $v0, READ_INT10
    syscall
    move  $s0, $v0          # Guarda o inteiro lido em $s0

    # --- printStr("\nValor em base 10 (signed): "); ---
    la    $a0, str2
    li    $v0, PRINT_STR
    syscall

    # --- printInt10(value); ---
    move  $a0, $s0
    li    $v0, PRINT_INT10
    syscall

    # --- printStr("\nValor em base 2: "); ---
    la    $a0, str3
    li    $v0, PRINT_STR
    syscall

    # --- printInt(value, 2); ---
    move  $a0, $s0
    li    $a1, 2            # Base 2
    li    $v0, PRINT_INT
    syscall

    # --- printStr("\nValor em base 2, formatado: "); ---
    la    $a0, str4
    li    $v0, PRINT_STR
    syscall

    # --- printInt(value, 2 | 32 << 16); ---
    move  $a0, $s0
    li    $t0, 32           # 32 dígitos de formatação
    sll   $t0, $t0, 16      # Faz o shift left logico (32 << 16)
    ori   $a1, $t0, 2       # Junta a base 2 com a formatação
    li    $v0, PRINT_INT
    syscall

    # --- printStr("\nValor em base 16: "); ---
    la    $a0, str5
    li    $v0, PRINT_STR
    syscall

    # --- printInt(value, 16); ---
    move  $a0, $s0
    li    $a1, 16           # Base 16
    li    $v0, PRINT_INT
    syscall

    # --- printStr("\nValor em base 10 (unsigned): "); ---
    la    $a0, str6
    li    $v0, PRINT_STR
    syscall

    # --- printInt(value, 10); ---
    move  $a0, $s0
    li    $a1, 10           # Base 10
    li    $v0, PRINT_INT
    syscall

    # --- printStr("\nValor em base 10 (unsigned), formatado: "); ---
    la    $a0, str7
    li    $v0, PRINT_STR
    syscall

    # --- printInt(value, 10 | 5 << 16); ---
    move  $a0, $s0
    li    $t0, 5            # 5 dígitos de formatação
    sll   $t0, $t0, 16      # (5 << 16)
    ori   $a1, $t0, 10      # Junta a base 10
    li    $v0, PRINT_INT
    syscall

    j     loop_c            # while(1)

    # Epílogo (embora tenha um loop infinito, é boa prática colocar)
    lw    $s0, 4($sp)
    lw    $ra, 0($sp)
    addiu $sp, $sp, 8
    li    $v0, 0
    jr    $ra
