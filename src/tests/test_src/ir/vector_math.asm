add(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     ecx, DWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-16]
        add     edx, ecx
        mov     edx, edx
        movabs  rcx, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     ecx, DWORD PTR [rbp-4]
        mov     edx, DWORD PTR [rbp-12]
        add     edx, ecx
        mov     edx, edx
        sal     rdx, 32
        mov     eax, eax
        or      rax, rdx
        pop     rbp
        ret
sub(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     ecx, DWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-16]
        sub     ecx, edx
        mov     edx, ecx
        movabs  rcx, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     ecx, DWORD PTR [rbp-4]
        mov     edx, DWORD PTR [rbp-12]
        sub     ecx, edx
        mov     edx, ecx
        sal     rdx, 32
        mov     eax, eax
        or      rax, rdx
        pop     rbp
        ret
mul(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     ecx, DWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-16]
        imul    edx, ecx
        mov     edx, edx
        movabs  rcx, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     ecx, DWORD PTR [rbp-4]
        mov     edx, DWORD PTR [rbp-12]
        imul    edx, ecx
        mov     edx, edx
        sal     rdx, 32
        mov     eax, eax
        or      rax, rdx
        pop     rbp
        ret
div(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     eax, DWORD PTR [rbp-8]
        mov     esi, DWORD PTR [rbp-16]
        cdq
        idiv    esi
        mov     edx, eax
        movabs  rax, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     rcx, rax
        mov     eax, DWORD PTR [rbp-4]
        mov     edi, DWORD PTR [rbp-12]
        cdq
        idiv    edi
        mov     eax, eax
        sal     rax, 32
        mov     edx, ecx
        or      rax, rdx
        mov     rcx, rax
        mov     rax, rcx
        pop     rbp
        ret
mod(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     eax, DWORD PTR [rbp-8]
        mov     esi, DWORD PTR [rbp-16]
        cdq
        idiv    esi
        mov     eax, edx
        mov     edx, eax
        movabs  rax, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     rcx, rax
        mov     eax, DWORD PTR [rbp-4]
        mov     esi, DWORD PTR [rbp-12]
        cdq
        idiv    esi
        mov     eax, edx
        mov     eax, eax
        sal     rax, 32
        mov     edx, ecx
        or      rax, rdx
        mov     rcx, rax
        mov     rax, rcx
        pop     rbp
        ret
bsl(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     esi, DWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-16]
        mov     ecx, edx
        sal     esi, cl
        mov     edx, esi
        mov     edx, edx
        movabs  rcx, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     esi, DWORD PTR [rbp-4]
        mov     edx, DWORD PTR [rbp-12]
        mov     ecx, edx
        sal     esi, cl
        mov     edx, esi
        mov     edx, edx
        sal     rdx, 32
        mov     eax, eax
        or      rax, rdx
        pop     rbp
        ret
bsr(v2i, v2i):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     esi, DWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-16]
        mov     ecx, edx
        sar     esi, cl
        mov     edx, esi
        mov     edx, edx
        movabs  rcx, -4294967296
        and     rax, rcx
        or      rax, rdx
        mov     esi, DWORD PTR [rbp-4]
        mov     edx, DWORD PTR [rbp-12]
        mov     ecx, edx
        sar     esi, cl
        mov     edx, esi
        mov     edx, edx
        sal     rdx, 32
        mov     eax, eax
        or      rax, rdx
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 80
        mov     DWORD PTR [rbp-8], 1
        mov     DWORD PTR [rbp-4], 2
        mov     DWORD PTR [rbp-16], 3
        mov     DWORD PTR [rbp-12], 4
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    add(v2i, v2i)
        mov     QWORD PTR [rbp-24], rax
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    sub(v2i, v2i)
        mov     QWORD PTR [rbp-32], rax
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    mul(v2i, v2i)
        mov     QWORD PTR [rbp-40], rax
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    div(v2i, v2i)
        mov     QWORD PTR [rbp-48], rax
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    mod(v2i, v2i)
        mov     QWORD PTR [rbp-56], rax
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    bsr(v2i, v2i)
        mov     QWORD PTR [rbp-64], rax
        mov     rdx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rdx
        mov     rdi, rax
        call    bsl(v2i, v2i)
        mov     QWORD PTR [rbp-72], rax
        mov     eax, 0
        leave
        ret