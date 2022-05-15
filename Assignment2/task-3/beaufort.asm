%include "../include/io.mac"

section .text
    global beaufort
    extern printf

; void beaufort(int len_plain, char *plain, int len_key, char *key, char tabula_recta[26][26], char *enc) ;
beaufort:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; len_plain
    mov ebx, [ebp + 12] ; plain (address of first element in string)
    mov ecx, [ebp + 16] ; len_key
    mov edx, [ebp + 20] ; key (address of first element in matrix)
    mov edi, [ebp + 24] ; tabula_recta
    mov esi, [ebp + 28] ; enc
    ;; DO NOT MODIFY
    ;; TODO: Implement spiral encryption
    ;; FREESTYLE STARTS HERE
    xor edi, edi
    xor eax, eax

while_loop:
    ;; checks if the plain string has reached the end
    cmp byte [ebx], 0
    je stop

    ;; checks if the key string hash reached the end and if so, start over
    cmp edi, ecx
    je start_over_key

continue1:
    ;; retains the current character from key
    mov al, byte [edx + edi]
    ;; substract from the value in al the current character from plain string
    sub al, byte [ebx]
    ;; if al is negative, returns it to the correct value
    cmp al, 0
    jl change_eax

continue2:
    ;; find the letter in alphabet
    add al, 65
    ;; puts the character in encrypted string
    mov byte [esi], al
    ;; passes to the next character in plain string and encrypted string
    inc esi
    inc ebx
    ;; increments the position in key string
    add edi, 1
    jmp while_loop

change_eax:
    ;; adds 26 to find the position in the alphabet
    add al, 26
    jmp continue2

start_over_key:
    ;; makes edi 0
    xor edi, edi
    jmp continue1

stop:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
