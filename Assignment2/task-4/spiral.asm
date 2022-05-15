%include "../include/io.mac"

section .data
    row dd 0
    col dd 0
    last_row dd 0
    last_col dd 0
    n dd 0
    pos dd 0

section .text
    global spiral
    extern printf

; void spiral(int N, char *plain, int key[N][N], char *enc_string);

spiral:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; N (size of key line)
    mov ebx, [ebp + 12] ; plain (address of first element in string)
    mov ecx, [ebp + 16] ; key (address of first element in matrix)
    mov edx, [ebp + 20] ; enc_string (address of first element in string)
    ;; DO NOT MODIFY
    ;; TODO: Implement spiral encryption
    ;; FREESTYLE STARTS HERE

    mov dword [row], 0
    mov dword [col], 0
    ;; saves the size of the matrix
    mov dword [last_row], eax 
    sub dword [last_row], 1
    mov dword [last_col], eax
    sub dword [last_col], 1
    mov dword [n], eax
    mov dword [pos], 0
    
    xor esi, esi

    ;; copy the plain string into the encypted string
copy_string:
    cmp byte [ebx], 0
    je already_copied
    mov al, byte [ebx]
    mov byte [edx + esi], al
    inc ebx
    inc esi
    jmp copy_string


already_copied:
    xor eax, eax
    xor edi, edi 
    xor esi, esi
    xor ebx, ebx

    ;; goes through the spiral matrix and when finds a new element,
    ;; adds it to the current character from the encrypted string
matrix:
    ;; checks if there are more elements in the matrix
    mov eax, dword [row]
    mov edi, dword [last_row]
    cmp eax, edi
    jg stop
    mov eax, dword [col]
    mov edi, dword [last_col]
    cmp eax, edi
    jg stop

    ;; saves the current col in edi
    mov edi, dword [col]

up:
    xor esi, esi
    ;; saves the last column in esi register
    mov esi, dword [last_col]

    cmp edi, esi
    jg after_up
   
    xor esi, esi
    ;; where the current element in the matrix is
    mov esi, dword [row]
    imul esi, dword [n]
    add esi, edi
    imul esi, 4
   
    xor eax, eax
    ;; saves in eax the current element
    mov eax, dword [ecx + esi]

    xor esi, esi
    ;; adds the element from the matrix to the current character to
    ;; obtain the encrypted string
    mov esi, dword [pos]
    add byte [edx + esi], al
    add dword [pos], 1
    ;; continue
    inc edi
    jmp up

after_up:
    ;; increase the row
    add dword [row], 1
    xor edi, edi

    ;; saves the current row in edi register
    mov edi, dword [row]

right:
    xor esi, esi
    ;; saves the last row in esi register
    mov esi, dword [last_row]

    cmp edi, esi
    jg after_right

    xor esi, esi
    ;; where the current element in the matrix is
    mov esi, dword [last_col]
    xor ebx, ebx
    mov ebx, edi
    imul ebx, dword [n]
    add ebx, esi
    imul ebx, 4

    xor eax, eax
    ;; saves in eax the current element
    mov eax, dword [ecx + ebx]

    xor esi, esi
    ;; adds the element from the matrix to the current character to
    ;; obtain the encrypted string
    mov esi, dword [pos]
    add byte [edx + esi], al
    add dword [pos], 1
    ;; continue
    inc edi
    jmp right


after_right:
    ;; decreses the last column
    sub dword [last_col], 1
    xor edi, edi

    ;; compare the current row and last row to verify (check for more lines)
    mov edi, dword [row]
    xor esi, esi
    mov esi, dword [last_row]
    cmp edi, esi
    jg before_left

    ;; saves the last column in edi register
    mov edi, dword [last_col]

down:
    xor esi, esi
    ;; saves the last row in esi register
    mov esi, dword [col]
    cmp edi, esi
    jl after_down

    xor esi, esi
    ;; where the current element in the matrix is
    mov esi, dword [last_row]
    imul esi, dword [n]
    add esi, edi
    imul esi, 4

    xor eax, eax
    ;; adds the element from the matrix to the current character to
    ;; obtain the encrypted string
    mov eax, dword [ecx + esi]
    mov esi, dword [pos]
    add byte [edx + esi], al
    add dword [pos], 1
    dec edi
    jmp down


after_down:
    ;; decrease the last row
    sub dword [last_row], 1

before_left:
    xor edi, edi
;; compare the current col and last col to verify (check for more columns)
    mov edi, dword [col]
    xor esi, esi
    mov esi, dword [last_col]
    cmp edi, esi
    jg matrix

    xor edi, edi
    ;; saves the last row in edi register
    mov edi, dword [last_row]
 
left:
    xor esi, esi
    ;; saves the current row in esi register
    mov esi, dword [row]
    cmp edi, esi
    jl after_left

    xor esi, esi
    ;; where the current element in the matrix is
    mov esi, dword [col]
    xor ebx, ebx
    mov ebx, edi
    imul ebx, dword [n]
    add ebx, esi
    imul ebx, 4

    xor eax, eax
    ;; adds the element from the matrix to the current character to
    ;; obtain the encrypted string
    mov eax, dword [ecx + ebx]
    mov esi, dword [pos] 
    add byte [edx + esi], al
    add dword [pos], 1
    dec edi
    jmp left

after_left:
    ;; increase current col by one
    add dword [col], 1
    ;; return to the begining
    jmp matrix

stop:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
