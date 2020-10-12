work_with_array:
        mov     edx, DWORD PTR [rsi]
        mov     r8, rdi
        sub     edx, 1
        test    edx, edx
        jle     .L1
        lea     r9, [rdi+8]
.L3:
        sub     edx, 1
        mov     rax, r8
        mov     rdi, rdx
        lea     rsi, [r9+rdx*8]
.L5:
        mov     rdx, QWORD PTR [rax]
        mov     rcx, QWORD PTR [rax+8]
        cmp     rdx, rcx
        jbe     .L4
        movsx   rdx, edx
        mov     QWORD PTR [rax], rcx
        mov     QWORD PTR [rax+8], rdx
.L4:
        add     rax, 8
        cmp     rsi, rax
        jne     .L5
        mov     edx, edi
        test    edi, edi
        jne     .L3
.L1:
        ret