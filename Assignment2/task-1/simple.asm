%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY
   
    ;; Your code starts here

while_loop:
    ;; copies in al register current character from plain string
    mov al, byte [esi]

    ;; adds the step to the current character
    add al, dl

    ;; verifies if the new character exceeds letter 'Z'
    cmp al, 90
    jg change_al ;; if true, changes it
    jmp modify_string


change_al:
    ;; decreses the current character (ascii code) with 26 to return it
    ;; to the alphabet
    sub al, 26
    jmp modify_string

modify_string:
    ;; puts the correct new character in the encrypted string
    mov byte [edi], al

    ;; passes to the next character in both plain and encrypted strings
    inc esi
    inc edi

    ;; verifies if the string has reached the end
    cmp byte [esi], 0
    je stop ;;  if it is true, jumps to the end of program
    jne while_loop

stop:
    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
