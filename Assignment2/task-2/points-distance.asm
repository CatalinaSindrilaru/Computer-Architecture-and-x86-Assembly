%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    global points_distance
    extern printf

points_distance:
    ;; DO NOT MODIFY
    
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; points
    mov eax, [ebp + 12]     ; distance
    ;; DO NOT MODIFY
   
    ;; Your code starts here

    xor edx, edx
    xor ecx, ecx

    ;; retains in dx first coordinate x
    mov dx, word [ebx]
    ;; retains in cx second coordinate x
    mov cx, word [ebx + point_size]

    ;; verifies which value is greater
    cmp dx, cx
    jg diff1
    jl diff2

    xor edx, edx
    xor ecx, ecx

    ;; retains in dx first coordinate y
    mov dx, word [ebx + 2]
    ;; retains in cx first coordinate y
    mov cx, word [ebx + point_size + 2]

    ;; verifies which value is greater
    cmp dx, cx
    jg diff1
    jl diff2


diff1:
    ;; decreases from higher value lower value
    sub dx, cx
    ;; puts in the eax register the final result
    mov [eax], edx
    jmp stop

diff2:
    ;; decreases from higher value lower value
    sub cx, dx
    ;; puts in the eax register the final result
    mov [eax], ecx
    jmp stop

    ;; Your code ends here

stop:  
    ;; DO NOT MODIFY
    popa
    leave
    ret

    ;; DO NOT MODIFY