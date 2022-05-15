%include "../include/io.mac"

section .text
    global is_square
    extern printf

is_square:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; dist
    mov eax, [ebp + 12]     ; nr
    mov ecx, [ebp + 16]     ; sq
    ;; DO NOT MODIFY
   
    ;; Your code starts here

while_loop:
    cmp eax, 0
    je stop

    ;; puts in edx the current value from vector of distances
    mov edx, [ebx + (eax - 1) * 4]
    ;; if a value is 0, it is considered perfect square
    cmp edx, 0
    je square

    mov esi, 1

    ;; verify if the number is a perfect square
verif_ps:
    mov edi, 1
    ;; retains in edi all the perfect squares one by one
    imul edi, esi
    imul edi, esi
    
    ;; compares the perfect square with the value from vector of distances
    cmp edi, edx
    je square
    ;; if the current perfect square is greater then my value
    jg not_square

    inc esi ;; pass to the next perfect square
    jmp verif_ps

continue:
    dec eax
    jmp while_loop

square:
    ;; puts 1 in sq vector
    mov [ecx + (eax - 1) * 4], dword 1
    jmp continue

not_square:
    ;; puts 0 in sq vector
    mov [ecx + (eax - 1) * 4], dword 0
    jmp continue

stop:
    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY