%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    global road
    extern printf

road:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]      ; points
    mov ecx, [ebp + 12]     ; len
    mov ebx, [ebp + 16]     ; distances
    ;; DO NOT MODIFY
   
    ;; Your code starts here

    xor edi, edi
    xor esi, esi ;; In esi I stored at which point I am
    xor edx, edx

while_loop:
    cmp ecx, 1
    je stop

    ;; retains in dx and di coordinates x for 2 consecutive points
    mov dx, word [eax + esi * point_size] 
    mov di, word [eax + esi * point_size + point_size]

    ;; verifies which value is greater
    cmp dx, di
    jg diff1
    jl diff2

    ;; retains in dx and di coordinates y for 2 consecutive points
    mov dx, word [eax + esi * point_size + 2]
    mov di, word [eax + esi * point_size + point_size + 2] 

    ;; verifies which value is greater
    cmp dx, di
    jg diff1
    jl diff2
    je equal

continue:
    inc esi
    dec ecx
    jmp while_loop

diff1:
    ;; decreases from higher value lower value
    sub dx, di
    ;; puts in the vector of distances the final distances
    ;; between two consecutive points
    mov [ebx + esi * 4], edx
    jmp continue

diff2:
    ;; decreases from higher value lower value
    sub di, dx
    ;; puts in the vector of distances the final distances
    ;; between two consecutive points
    mov [ebx + esi * 4], edi
    jmp continue

equal:
    ;; if the points have all the coordinates equal, the distance 
    ;; between them is 0
    mov [ebx + esi * 4], dword 0
    jmp continue
    
stop:  
    ;; Your code ends here
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY