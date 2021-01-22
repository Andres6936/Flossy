```asm
flossy::format_error::~format_error() [base object destructor]:
        mov     QWORD PTR [rdi], OFFSET FLAT:vtable for flossy::format_error+16
        jmp     std::invalid_argument::~invalid_argument() [base object destructor]
flossy::format_error::~format_error() [deleting destructor]:
        push    rbp
        mov     rbp, rdi
        mov     QWORD PTR [rdi], OFFSET FLAT:vtable for flossy::format_error+16
        call    std::invalid_argument::~invalid_argument() [base object destructor]
        mov     rdi, rbp
        mov     esi, 16
        pop     rbp
        jmp     operator delete(void*, unsigned long)
std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::(anonymous namespace)::output_sign<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, flossy::(anonymous namespace)::sign_character):
        push    rbp
        mov     rax, rdi
        push    rbx
        sub     rsp, 24
        cmp     esi, 1
        je      .L19
        cmp     esi, 2
        je      .L20
        cmp     esi, 3
        je      .L21
        add     rsp, 24
        pop     rbx
        pop     rbp
        ret
.L19:
        mov     rbx, QWORD PTR [rdi+8]
        mov     rdx, QWORD PTR [rdi]
        lea     rcx, [rdi+16]
        lea     rbp, [rbx+1]
        cmp     rdx, rcx
        je      .L15
        mov     rcx, QWORD PTR [rdi+16]
.L7:
        cmp     rbp, rcx
        ja      .L22
.L8:
        mov     BYTE PTR [rdx+rbx], 32
        mov     rdx, QWORD PTR [rax]
        mov     QWORD PTR [rax+8], rbp
        mov     BYTE PTR [rdx+1+rbx], 0
        add     rsp, 24
        pop     rbx
        pop     rbp
        ret
.L20:
        mov     rbx, QWORD PTR [rdi+8]
        mov     rdx, QWORD PTR [rdi]
        lea     rcx, [rdi+16]
        lea     rbp, [rbx+1]
        cmp     rdx, rcx
        je      .L16
        mov     rcx, QWORD PTR [rdi+16]
.L11:
        cmp     rbp, rcx
        ja      .L23
.L12:
        mov     BYTE PTR [rdx+rbx], 43
        mov     rdx, QWORD PTR [rax]
        mov     QWORD PTR [rax+8], rbp
        mov     BYTE PTR [rdx+1+rbx], 0
        add     rsp, 24
        pop     rbx
        pop     rbp
        ret
.L21:
        mov     rbx, QWORD PTR [rdi+8]
        mov     rdx, QWORD PTR [rdi]
        lea     rcx, [rdi+16]
        lea     rbp, [rbx+1]
        cmp     rdx, rcx
        je      .L17
        mov     rcx, QWORD PTR [rdi+16]
.L13:
        cmp     rbp, rcx
        ja      .L24
.L14:
        mov     BYTE PTR [rdx+rbx], 45
        mov     rdx, QWORD PTR [rax]
        mov     QWORD PTR [rax+8], rbp
        mov     BYTE PTR [rdx+1+rbx], 0
        add     rsp, 24
        pop     rbx
        pop     rbp
        ret
.L22:
        xor     edx, edx
        mov     rdi, rax
        mov     r8d, 1
        xor     ecx, ecx
        mov     rsi, rbx
        mov     QWORD PTR [rsp+8], rax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [rsp+8]
        mov     rdx, QWORD PTR [rax]
        jmp     .L8
.L23:
        xor     edx, edx
        mov     rdi, rax
        mov     r8d, 1
        xor     ecx, ecx
        mov     rsi, rbx
        mov     QWORD PTR [rsp+8], rax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [rsp+8]
        mov     rdx, QWORD PTR [rax]
        jmp     .L12
.L15:
        mov     ecx, 15
        jmp     .L7
.L24:
        xor     edx, edx
        mov     rdi, rax
        mov     r8d, 1
        xor     ecx, ecx
        mov     rsi, rbx
        mov     QWORD PTR [rsp+8], rax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [rsp+8]
        mov     rdx, QWORD PTR [rax]
        jmp     .L14
.L16:
        mov     ecx, 15
        jmp     .L11
.L17:
        mov     ecx, 15
        jmp     .L13
std::enable_if<std::is_integral<unsigned int>::value&&std::is_unsigned<unsigned int>::value, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::type flossy::(anonymous namespace)::format_integer_unchecked<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int, bool, flossy::conversion_options const&):
        push    r15
        push    r14
        push    r13
        push    r12
        mov     r12, rdi
        push    rbp
        push    rbx
        mov     ebx, esi
        sub     rsp, 120
        mov     eax, DWORD PTR [rcx]
        cmp     eax, 8
        je      .L125
        mov     r10d, edx
        mov     r9, rcx
        mov     edi, 10
        cmp     eax, 3
        jbe     .L126
.L30:
        mov     eax, ebx
        xor     edx, edx
        mov     DWORD PTR [rsp+96], 1
        div     edi
        movzx   edx, BYTE PTR flossy::(anonymous namespace)::digit_chars<char>[rdx]
        mov     esi, eax
        mov     BYTE PTR [rsp+32], dl
        cmp     ebx, edi
        jb      .L31
.L32:
        mov     eax, esi
        xor     edx, edx
        movsx   rcx, DWORD PTR [rsp+96]
        div     edi
        lea     r8d, [rcx+1]
        mov     DWORD PTR [rsp+96], r8d
        movzx   edx, BYTE PTR flossy::(anonymous namespace)::digit_chars<char>[rdx]
        mov     BYTE PTR [rsp+32+rcx], dl
        mov     edx, esi
        mov     esi, eax
        cmp     edi, edx
        jbe     .L32
.L31:
        mov     r11d, DWORD PTR [r9+16]
        test    r10b, r10b
        jne     .L83
        test    r11d, r11d
        je      .L84
        mov     edx, 1
        cmp     r11d, 1
        jne     .L127
.L33:
        movsx   r13, DWORD PTR [rsp+96]
        mov     eax, DWORD PTR [r9+4]
        mov     ebx, 0
        mov     ecx, DWORD PTR [r9+12]
        sub     eax, r13d
        sub     eax, edx
        cmovns  ebx, eax
        cmp     BYTE PTR [r9+20], 1
        mov     ebp, eax
        sbb     r15d, r15d
        and     r15d, -16
        add     r15d, 48
        test    ecx, ecx
        jne     .L35
        lea     r9, [r12+16]
        test    eax, eax
        jle     .L41
.L43:
        mov     rbp, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        lea     r14, [rbp+1]
        cmp     rax, r9
        je      .L87
        mov     rdx, QWORD PTR [r12+16]
.L39:
        cmp     r14, rdx
        ja      .L128
        mov     BYTE PTR [rax+rbp], r15b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], r14
        mov     BYTE PTR [rax+1+rbp], 0
        sub     ebx, 1
        jne     .L43
.L41:
        cmp     r11d, 1
        je      .L129
        cmp     r11d, 2
        je      .L130
        cmp     r11d, 3
        je      .L131
.L46:
        lea     r15, [r12+16]
        movsx   rbp, r13d
        lea     r9, [rsp+31]
        test    r13d, r13d
        jle     .L29
.L57:
        mov     rbx, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        movzx   r14d, BYTE PTR [r9+rbp]
        lea     r13, [rbx+1]
        cmp     r15, rax
        je      .L91
        mov     rdx, QWORD PTR [r12+16]
.L53:
        cmp     r13, rdx
        ja      .L132
        mov     BYTE PTR [rax+rbx], r14b
        mov     rax, QWORD PTR [r12]
        sub     rbp, 1
        mov     QWORD PTR [r12+8], r13
        mov     BYTE PTR [rax+1+rbx], 0
        test    ebp, ebp
        jg      .L57
        jmp     .L29
.L35:
        cmp     ecx, 1
        je      .L133
        cmp     ecx, 2
        je      .L134
.L29:
        add     rsp, 120
        mov     rax, r12
        pop     rbx
        pop     rbp
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        ret
.L126:
        mov     edi, DWORD PTR CSWTCH.77[0+rax*4]
        jmp     .L30
.L127:
        xor     edx, edx
        xor     r11d, r11d
        jmp     .L33
.L84:
        mov     edx, 1
        mov     r11d, 2
        jmp     .L33
.L128:
        xor     ecx, ecx
        xor     edx, edx
        mov     r8d, 1
        mov     rsi, rbp
        mov     rdi, r12
        mov     QWORD PTR [rsp+8], r9
        mov     DWORD PTR [rsp], r11d
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        sub     ebx, 1
        mov     r11d, DWORD PTR [rsp]
        mov     r9, QWORD PTR [rsp+8]
        mov     BYTE PTR [rax+rbp], r15b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], r14
        mov     BYTE PTR [rax+1+rbp], 0
        jne     .L43
        jmp     .L41
.L132:
        xor     ecx, ecx
        xor     edx, edx
        mov     r8d, 1
        mov     rsi, rbx
        mov     rdi, r12
        mov     QWORD PTR [rsp], r9
        sub     rbp, 1
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        test    ebp, ebp
        mov     r9, QWORD PTR [rsp]
        mov     BYTE PTR [rax+rbx], r14b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], r13
        mov     BYTE PTR [rax+1+rbx], 0
        jg      .L57
        jmp     .L29
.L91:
        mov     edx, 15
        jmp     .L53
.L87:
        mov     edx, 15
        jmp     .L39
.L125:
        mov     rbp, QWORD PTR [rdi+8]
        mov     rax, QWORD PTR [rdi]
        lea     rdx, [rdi+16]
        lea     r13, [rbp+1]
        cmp     rax, rdx
        je      .L81
        mov     rdx, QWORD PTR [rdi+16]
.L27:
        cmp     r13, rdx
        ja      .L135
.L28:
        mov     BYTE PTR [rax+rbp], bl
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], r13
        mov     BYTE PTR [rax+1+rbp], 0
        jmp     .L29
.L83:
        mov     edx, 1
        mov     r11d, 3
        jmp     .L33
.L133:
        mov     esi, r11d
        mov     rdi, r12
        call    std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::(anonymous namespace)::output_sign<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, flossy::(anonymous namespace)::sign_character)
        mov     r14, rax
        lea     r9, [rax+16]
        test    ebp, ebp
        jle     .L63
.L65:
        mov     rbp, QWORD PTR [r14+8]
        mov     rdx, QWORD PTR [r14]
        lea     rax, [rbp+1]
        cmp     rdx, r9
        je      .L92
.L138:
        mov     rcx, QWORD PTR [r14+16]
.L61:
        cmp     rax, rcx
        ja      .L136
        mov     BYTE PTR [rdx+rbp], r15b
        mov     QWORD PTR [r14+8], rax
        mov     rax, QWORD PTR [r14]
        mov     BYTE PTR [rax+1+rbp], 0
        sub     ebx, 1
        jne     .L65
.L63:
        lea     r15, [r12+16]
        lea     r9, [rsp+31]
        test    r13d, r13d
        jle     .L29
.L69:
        mov     rbx, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        movzx   r14d, BYTE PTR [r9+r13]
        lea     rbp, [rbx+1]
        cmp     r15, rax
        je      .L93
        mov     rdx, QWORD PTR [r12+16]
.L66:
        cmp     rbp, rdx
        ja      .L137
        mov     BYTE PTR [rax+rbx], r14b
        mov     rax, QWORD PTR [r12]
        sub     r13, 1
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        test    r13d, r13d
        jg      .L69
        jmp     .L29
.L136:
        xor     edx, edx
        xor     ecx, ecx
        mov     r8d, 1
        mov     rsi, rbp
        mov     rdi, r14
        mov     QWORD PTR [rsp+8], r9
        mov     QWORD PTR [rsp], rax
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rdx, QWORD PTR [r14]
        mov     rax, QWORD PTR [rsp]
        sub     ebx, 1
        mov     r9, QWORD PTR [rsp+8]
        mov     BYTE PTR [rdx+rbp], r15b
        mov     QWORD PTR [r14+8], rax
        mov     rax, QWORD PTR [r14]
        mov     BYTE PTR [rax+1+rbp], 0
        je      .L63
        mov     rbp, QWORD PTR [r14+8]
        mov     rdx, QWORD PTR [r14]
        lea     rax, [rbp+1]
        cmp     rdx, r9
        jne     .L138
.L92:
        mov     ecx, 15
        jmp     .L61
.L137:
        xor     ecx, ecx
        xor     edx, edx
        mov     r8d, 1
        mov     rsi, rbx
        mov     rdi, r12
        mov     QWORD PTR [rsp], r9
        sub     r13, 1
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        test    r13d, r13d
        mov     r9, QWORD PTR [rsp]
        mov     BYTE PTR [rax+rbx], r14b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        jg      .L69
        jmp     .L29
.L93:
        mov     edx, 15
        jmp     .L66
.L129:
        mov     rbx, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        lea     rdx, [r12+16]
        lea     rbp, [rbx+1]
        cmp     rax, rdx
        je      .L88
        mov     rdx, QWORD PTR [r12+16]
.L44:
        cmp     rbp, rdx
        ja      .L139
.L45:
        mov     BYTE PTR [rax+rbx], 32
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        jmp     .L46
.L135:
        mov     r8d, 1
        xor     ecx, ecx
        xor     edx, edx
        mov     rsi, rbp
        mov     rdi, r12
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        jmp     .L28
.L134:
        mov     esi, r11d
        mov     rdi, r12
        movsx   r14, r13d
        call    std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::(anonymous namespace)::output_sign<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, flossy::(anonymous namespace)::sign_character)
        lea     r10, [r12+16]
        lea     r9, [rsp+31]
        test    r13d, r13d
        jle     .L74
.L76:
        mov     r13, QWORD PTR [r12+8]
        mov     rdx, QWORD PTR [r12]
        movzx   r11d, BYTE PTR [r9+r14]
        lea     rax, [r13+1]
        cmp     rdx, r10
        je      .L94
        mov     rcx, QWORD PTR [r12+16]
.L72:
        cmp     rax, rcx
        ja      .L140
        mov     BYTE PTR [rdx+r13], r11b
        sub     r14, 1
        mov     QWORD PTR [r12+8], rax
        mov     rax, QWORD PTR [r12]
        mov     BYTE PTR [rax+1+r13], 0
        test    r14d, r14d
        jg      .L76
.L74:
        lea     r14, [r12+16]
        test    ebp, ebp
        jg      .L80
        jmp     .L29
.L78:
        mov     BYTE PTR [rax+rbp], r15b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], r13
        mov     BYTE PTR [rax+1+rbp], 0
        sub     ebx, 1
        je      .L29
.L80:
        mov     rbp, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        lea     r13, [rbp+1]
        cmp     r14, rax
        je      .L95
        mov     rdx, QWORD PTR [r12+16]
.L77:
        cmp     r13, rdx
        jbe     .L78
        mov     r8d, 1
        xor     ecx, ecx
        xor     edx, edx
        mov     rsi, rbp
        mov     rdi, r12
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        jmp     .L78
.L140:
        xor     edx, edx
        xor     ecx, ecx
        mov     r8d, 1
        mov     rsi, r13
        mov     rdi, r12
        mov     QWORD PTR [rsp+24], r9
        sub     r14, 1
        mov     QWORD PTR [rsp+16], r10
        mov     QWORD PTR [rsp+8], rax
        mov     BYTE PTR [rsp], r11b
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rdx, QWORD PTR [r12]
        mov     rax, QWORD PTR [rsp+8]
        test    r14d, r14d
        movzx   r11d, BYTE PTR [rsp]
        mov     r10, QWORD PTR [rsp+16]
        mov     r9, QWORD PTR [rsp+24]
        mov     BYTE PTR [rdx+r13], r11b
        mov     QWORD PTR [r12+8], rax
        mov     rax, QWORD PTR [r12]
        mov     BYTE PTR [rax+1+r13], 0
        jg      .L76
        jmp     .L74
.L95:
        mov     edx, 15
        jmp     .L77
.L94:
        mov     ecx, 15
        jmp     .L72
.L130:
        mov     rbx, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        lea     rdx, [r12+16]
        lea     rbp, [rbx+1]
        cmp     rax, rdx
        je      .L89
        mov     rdx, QWORD PTR [r12+16]
.L48:
        cmp     rbp, rdx
        ja      .L141
.L49:
        mov     BYTE PTR [rax+rbx], 43
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        jmp     .L46
.L131:
        mov     rbx, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        lea     rdx, [r12+16]
        lea     rbp, [rbx+1]
        cmp     rax, rdx
        je      .L90
        mov     rdx, QWORD PTR [r12+16]
.L50:
        cmp     rbp, rdx
        ja      .L142
.L51:
        mov     BYTE PTR [rax+rbx], 45
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        jmp     .L46
.L81:
        mov     edx, 15
        jmp     .L27
.L141:
        mov     r8d, 1
        xor     ecx, ecx
        xor     edx, edx
        mov     rsi, rbx
        mov     rdi, r12
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        jmp     .L49
.L90:
        mov     edx, 15
        jmp     .L50
.L139:
        mov     r8d, 1
        xor     ecx, ecx
        xor     edx, edx
        mov     rsi, rbx
        mov     rdi, r12
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        jmp     .L45
.L142:
        mov     r8d, 1
        xor     ecx, ecx
        xor     edx, edx
        mov     rsi, rbx
        mov     rdi, r12
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        jmp     .L51
.L88:
        mov     edx, 15
        jmp     .L44
.L89:
        mov     edx, 15
        jmp     .L48
.LC0:
        .string "unterminated {"
.LC1:
        .string "Invalid character in format string"
std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::format_it<std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, int const&):
        push    r15
        lea     r9, [rdi+16]
        push    r14
        push    r13
        push    r12
        mov     r12, rdi
        push    rbp
        mov     rbp, rdx
        push    rbx
        mov     rbx, rsi
        sub     rsp, 104
        mov     QWORD PTR [rsp+16], rcx
        cmp     rdx, rsi
        je      .L231
.L144:
        movzx   r14d, BYTE PTR [rbx]
        cmp     r14b, 123
        je      .L240
.L146:
        mov     r13, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        lea     r15, [r13+1]
        cmp     rax, r9
        je      .L215
        mov     rdx, QWORD PTR [r12+16]
.L199:
        cmp     r15, rdx
        ja      .L241
        mov     BYTE PTR [rax+r13], r14b
        mov     rax, QWORD PTR [r12]
        add     rbx, 1
        mov     QWORD PTR [r12+8], r15
        mov     BYTE PTR [rax+1+r13], 0
        cmp     rbx, rbp
        jne     .L144
.L231:
        add     rsp, 104
        mov     rax, r12
        pop     rbx
        pop     rbp
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        ret
.L240:
        lea     r13, [rbx+1]
        cmp     r13, rbp
        je      .L242
        movzx   r14d, BYTE PTR [rbx+1]
        cmp     r14b, 123
        jne     .L243
        mov     rbx, r13
        jmp     .L146
.L241:
        xor     ecx, ecx
        xor     edx, edx
        mov     r8d, 1
        mov     rsi, r13
        mov     rdi, r12
        mov     QWORD PTR [rsp+8], r9
        add     rbx, 1
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        cmp     rbx, rbp
        mov     r9, QWORD PTR [rsp+8]
        mov     BYTE PTR [rax+r13], r14b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], r15
        mov     BYTE PTR [rax+1+r13], 0
        jne     .L144
        jmp     .L231
.L215:
        mov     edx, 15
        jmp     .L199
.L243:
        mov     edi, 24
        call    operator new(unsigned long)
        movdqa  xmm2, XMMWORD PTR C.14.0[rip]
        mov     edi, 24
        mov     rcx, rax
        movups  XMMWORD PTR [rax], xmm2
        mov     rax, QWORD PTR C.14.0[rip+16]
        mov     QWORD PTR [rsp+8], rcx
        mov     QWORD PTR [rcx+16], rax
        lea     rax, [rcx+24]
        mov     QWORD PTR [rsp+32], rax
        call    operator new(unsigned long)
        movdqa  xmm3, XMMWORD PTR C.15.1[rip]
        mov     rsi, rax
        mov     QWORD PTR [rsp+24], rax
        mov     edi, 64
        lea     r14, [rsi+24]
        movups  XMMWORD PTR [rax], xmm3
        mov     rax, QWORD PTR C.15.1[rip+16]
        mov     QWORD PTR [rsi+16], rax
        call    operator new(unsigned long)
        movdqa  xmm4, XMMWORD PTR C.16.2[rip]
        mov     rcx, QWORD PTR [rsp+8]
        mov     r15, rax
        lea     rsi, [rax+64]
        movdqa  xmm5, XMMWORD PTR C.16.2[rip+16]
        movdqa  xmm6, XMMWORD PTR C.16.2[rip+32]
        movdqa  xmm7, XMMWORD PTR C.16.2[rip+48]
        movups  XMMWORD PTR [rax], xmm4
        movups  XMMWORD PTR [rax+16], xmm5
        movups  XMMWORD PTR [rax+32], xmm6
        movups  XMMWORD PTR [rax+48], xmm7
        movzx   eax, BYTE PTR [rbx+1]
        cmp     al, BYTE PTR [rcx]
        je      .L208
        lea     rdx, [rcx+8]
        cmp     al, BYTE PTR [rcx+8]
        je      .L149
        lea     rdx, [rcx+16]
        cmp     al, BYTE PTR [rcx+16]
        je      .L149
.L150:
        mov     DWORD PTR [rsp+32], 0
        jmp     .L206
.L208:
        mov     rdx, rcx
.L149:
        cmp     QWORD PTR [rsp+32], rdx
        je      .L150
        mov     eax, DWORD PTR [rdx+4]
        lea     r13, [rbx+2]
        mov     DWORD PTR [rsp+32], eax
        cmp     r13, rbp
        je      .L244
        movzx   eax, BYTE PTR [rbx+2]
.L206:
        mov     rcx, QWORD PTR [rsp+24]
        cmp     BYTE PTR [rcx], al
        je      .L209
        lea     rdx, [rcx+8]
        cmp     BYTE PTR [rcx+8], al
        je      .L154
        lea     rdx, [rcx+16]
        cmp     BYTE PTR [rcx+16], al
        je      .L154
.L155:
        mov     rcx, r13
        mov     r8d, 2
        jmp     .L205
.L209:
        mov     rdx, rcx
.L154:
        cmp     rdx, r14
        je      .L155
        lea     rcx, [r13+1]
        mov     r8d, DWORD PTR [rdx+4]
        cmp     rcx, rbp
        je      .L245
        movzx   eax, BYTE PTR [r13+1]
.L205:
        mov     BYTE PTR [rsp+47], 0
        cmp     al, 48
        je      .L246
.L158:
        mov     rdx, rcx
        xor     r10d, r10d
        xor     r9d, r9d
        jmp     .L162
.L247:
        lea     edi, [r9+r9*4]
        movsx   eax, al
        add     rdx, 1
        mov     r10d, 1
        lea     r9d, [rax+rdi*2]
        cmp     rdx, rbp
        je      .L161
.L162:
        movzx   edi, BYTE PTR [rdx]
        lea     eax, [rdi-48]
        cmp     al, 9
        jbe     .L247
        test    r10b, r10b
        mov     r13d, 6
        cmovne  rcx, rdx
        cmp     dil, 46
        je      .L248
.L164:
        cmp     rcx, rbp
        je      .L249
.L170:
        movzx   edx, BYTE PTR [rcx]
        mov     rax, r15
        jmp     .L176
.L253:
        cmp     dl, BYTE PTR [rax+8]
        je      .L250
        cmp     dl, BYTE PTR [rax+16]
        je      .L251
        cmp     dl, BYTE PTR [rax+24]
        je      .L252
        add     rax, 32
        cmp     rax, rsi
        je      .L177
.L176:
        cmp     dl, BYTE PTR [rax]
        jne     .L253
.L172:
        cmp     rax, rsi
        je      .L177
        lea     rbx, [rcx+1]
        mov     eax, DWORD PTR [rax+4]
        cmp     rbx, rbp
        je      .L254
        cmp     BYTE PTR [rcx+1], 125
        jne     .L203
        mov     esi, 64
        mov     rdi, r15
        mov     DWORD PTR [rsp+56], eax
        lea     r14, [rcx+2]
        mov     DWORD PTR [rsp+60], r9d
        mov     DWORD PTR [rsp+48], r8d
        call    operator delete(void*, unsigned long)
        mov     rdi, QWORD PTR [rsp+24]
        mov     esi, 24
        call    operator delete(void*, unsigned long)
        mov     rdi, QWORD PTR [rsp+8]
        mov     esi, 24
        call    operator delete(void*, unsigned long)
        mov     rax, QWORD PTR [rsp+16]
        mov     r8d, DWORD PTR [rsp+48]
        mov     r9d, DWORD PTR [rsp+60]
        mov     esi, DWORD PTR [rax]
        mov     eax, DWORD PTR [rsp+56]
        cmp     eax, 1
        je      .L183
        cmp     eax, 6
        je      .L183
        movd    xmm4, DWORD PTR [rsp+32]
        movd    xmm1, r13d
        movd    xmm0, eax
        movd    xmm5, r9d
        punpckldq       xmm0, xmm5
        cmp     DWORD PTR [rsp+32], 1
        mov     DWORD PTR [rsp+80], r8d
        punpckldq       xmm1, xmm4
        punpcklqdq      xmm0, xmm1
        movaps  XMMWORD PTR [rsp+64], xmm0
        je      .L255
        mov     BYTE PTR [rsp+84], 0
.L188:
        lea     rcx, [rsp+64]
        xor     edx, edx
        mov     rdi, r12
        call    std::enable_if<std::is_integral<unsigned int>::value&&std::is_unsigned<unsigned int>::value, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::type flossy::(anonymous namespace)::format_integer_unchecked<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int, bool, flossy::conversion_options const&)
.L189:
        sub     rbp, r14
        lea     r15, [r12+16]
        lea     r9, [rbx+1+rbp]
        test    rbp, rbp
        jle     .L231
.L198:
        mov     rbx, QWORD PTR [r12+8]
        mov     rax, QWORD PTR [r12]
        movzx   r13d, BYTE PTR [r14]
        lea     rbp, [rbx+1]
        cmp     rax, r15
        je      .L214
        mov     rdx, QWORD PTR [r12+16]
.L194:
        cmp     rbp, rdx
        ja      .L256
        mov     BYTE PTR [rax+rbx], r13b
        mov     rax, QWORD PTR [r12]
        add     r14, 1
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        cmp     r14, r9
        jne     .L198
        jmp     .L231
.L256:
        mov     r8d, 1
        xor     ecx, ecx
        xor     edx, edx
        mov     rsi, rbx
        mov     rdi, r12
        mov     QWORD PTR [rsp+8], r9
        add     r14, 1
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
        mov     rax, QWORD PTR [r12]
        mov     r9, QWORD PTR [rsp+8]
        mov     BYTE PTR [rax+rbx], r13b
        mov     rax, QWORD PTR [r12]
        mov     QWORD PTR [r12+8], rbp
        mov     BYTE PTR [rax+1+rbx], 0
        cmp     r14, r9
        jne     .L198
        jmp     .L231
.L214:
        mov     edx, 15
        jmp     .L194
.L177:
        cmp     dl, 125
        jne     .L203
        mov     esi, 64
        mov     rdi, r15
        mov     DWORD PTR [rsp+60], r9d
        lea     r14, [rcx+1]
        mov     DWORD PTR [rsp+56], r8d
        mov     QWORD PTR [rsp+48], rcx
        call    operator delete(void*, unsigned long)
        mov     rdi, QWORD PTR [rsp+24]
        mov     esi, 24
        call    operator delete(void*, unsigned long)
        mov     rdi, QWORD PTR [rsp+8]
        mov     esi, 24
        call    operator delete(void*, unsigned long)
        mov     rax, QWORD PTR [rsp+16]
        mov     rcx, QWORD PTR [rsp+48]
        mov     r8d, DWORD PTR [rsp+56]
        mov     r9d, DWORD PTR [rsp+60]
        mov     esi, DWORD PTR [rax]
        mov     rbx, rcx
        mov     eax, 6
.L183:
        mov     ecx, esi
        movd    xmm2, DWORD PTR [rsp+32]
        movd    xmm1, r13d
        mov     edx, esi
        sar     ecx, 31
        movd    xmm0, eax
        movd    xmm3, r9d
        shr     edx, 31
        xor     esi, ecx
        punpckldq       xmm1, xmm2
        punpckldq       xmm0, xmm3
        mov     DWORD PTR [rsp+80], r8d
        sub     esi, ecx
        punpcklqdq      xmm0, xmm1
        cmp     DWORD PTR [rsp+32], 1
        movaps  XMMWORD PTR [rsp+64], xmm0
        je      .L257
        mov     BYTE PTR [rsp+84], 0
.L192:
        lea     rcx, [rsp+64]
        mov     rdi, r12
        call    std::enable_if<std::is_integral<unsigned int>::value&&std::is_unsigned<unsigned int>::value, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::type flossy::(anonymous namespace)::format_integer_unchecked<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int, bool, flossy::conversion_options const&)
        jmp     .L189
.L246:
        add     rcx, 1
        cmp     rcx, rbp
        je      .L161
        mov     BYTE PTR [rsp+47], 1
        jmp     .L158
.L248:
        add     rdx, 1
        cmp     rdx, rbp
        je      .L168
        mov     rdi, rdx
        xor     r11d, r11d
        xor     r13d, r13d
        jmp     .L169
.L258:
        lea     ecx, [r13+0+r13*4]
        movsx   eax, al
        add     rdi, 1
        mov     r11d, 1
        lea     r13d, [rax+rcx*2]
        cmp     rbp, rdi
        je      .L168
.L169:
        movzx   eax, BYTE PTR [rdi]
        mov     rcx, rdi
        sub     eax, 48
        cmp     al, 9
        jbe     .L258
        test    r11b, r11b
        jne     .L164
        mov     rcx, rdx
        jmp     .L170
.L250:
        add     rax, 8
        jmp     .L172
.L251:
        add     rax, 16
        jmp     .L172
.L257:
        movzx   eax, BYTE PTR [rsp+47]
        mov     BYTE PTR [rsp+84], al
        jmp     .L192
.L252:
        add     rax, 24
        jmp     .L172
.L255:
        movzx   eax, BYTE PTR [rsp+47]
        mov     BYTE PTR [rsp+84], al
        jmp     .L188
.L254:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
.L203:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC1
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
        mov     rbx, rax
        jmp     .L153
.L239:
        mov     rbx, rax
        jmp     .L184
        jmp     .L239
.L184:
        mov     rdi, rbp
        call    __cxa_free_exception
.L153:
        mov     esi, 64
        mov     rdi, r15
        call    operator delete(void*, unsigned long)
.L185:
        mov     rdi, QWORD PTR [rsp+24]
        mov     esi, 24
        mov     rbp, rbx
        call    operator delete(void*, unsigned long)
.L186:
        mov     rdi, QWORD PTR [rsp+8]
        mov     esi, 24
        call    operator delete(void*, unsigned long)
        mov     rdi, rbp
        call    _Unwind_Resume
.L161:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
.L245:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
        jmp     .L239
        jmp     .L239
.L244:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
.L249:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
        jmp     .L239
        jmp     .L239
.L168:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
        mov     rbx, rax
        jmp     .L185
        jmp     .L239
.L242:
        mov     edi, 16
        call    __cxa_allocate_exception
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        mov     rbp, rax
        call    std::invalid_argument::invalid_argument(char const*)
        mov     QWORD PTR [rbp+0], OFFSET FLAT:vtable for flossy::format_error+16
        mov     edx, OFFSET FLAT:flossy::format_error::~format_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for flossy::format_error
        mov     rdi, rbp
        call    __cxa_throw
        mov     rbp, rax
        jmp     .L186
        mov     r12, rax
        mov     rdi, rbp
        call    __cxa_free_exception
        mov     rdi, r12
        call    _Unwind_Resume
main:
        movabs  rax, 8022916924116329800
        push    r12
        push    rbp
        push    rbx
        sub     rsp, 80
        lea     rbx, [rsp+64]
        mov     QWORD PTR [rsp+64], rax
        lea     rbp, [rsp+32]
        mov     eax, 32123
        lea     rcx, [rsp+12]
        lea     rdx, [rsp+79]
        mov     rsi, rbx
        mov     DWORD PTR [rsp+12], 42
        lea     rdi, [rsp+16]
        mov     QWORD PTR [rsp+48], rbx
        mov     DWORD PTR [rsp+72], 543452274
        mov     WORD PTR [rsp+76], ax
        mov     BYTE PTR [rsp+78], 46
        mov     QWORD PTR [rsp+56], 15
        mov     BYTE PTR [rsp+79], 0
        mov     QWORD PTR [rsp+16], rbp
        mov     QWORD PTR [rsp+24], 0
        mov     BYTE PTR [rsp+32], 0
        call    std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::format_it<std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, int const&)
        mov     rdi, QWORD PTR [rsp+48]
        cmp     rdi, rbx
        je      .L265
        mov     rax, QWORD PTR [rsp+64]
        lea     rsi, [rax+1]
        call    operator delete(void*, unsigned long)
.L265:
        mov     rdi, QWORD PTR [rsp+16]
        cmp     rdi, rbp
        je      .L267
        mov     rax, QWORD PTR [rsp+32]
        lea     rsi, [rax+1]
        call    operator delete(void*, unsigned long)
.L267:
        add     rsp, 80
        xor     eax, eax
        pop     rbx
        pop     rbp
        pop     r12
        ret
        mov     r12, rax
        jmp     .L261
main.cold:
CSWTCH.77:
        .long   2
        .long   10
        .long   8
        .long   16
C.16.2:
        .byte   98
        .zero   3
        .long   0
        .byte   100
        .zero   3
        .long   1
        .byte   111
        .zero   3
        .long   2
        .byte   120
        .zero   3
        .long   3
        .byte   101
        .zero   3
        .long   5
        .byte   102
        .zero   3
        .long   4
        .byte   115
        .zero   3
        .long   7
        .byte   99
        .zero   3
        .long   8
C.15.1:
        .byte   43
        .zero   3
        .long   0
        .byte   32
        .zero   3
        .long   1
        .byte   45
        .zero   3
        .long   2
C.14.0:
        .byte   62
        .zero   3
        .long   0
        .byte   95
        .zero   3
        .long   1
        .byte   60
        .zero   3
        .long   2
flossy::(anonymous namespace)::digit_chars<char>:
        .ascii  "0123456789abcdef"
typeinfo name for flossy::format_error:
        .string "N6flossy12format_errorE"
typeinfo for flossy::format_error:
        .quad   vtable for __cxxabiv1::__si_class_type_info+16
        .quad   typeinfo name for flossy::format_error
        .quad   typeinfo for std::invalid_argument
vtable for flossy::format_error:
        .quad   0
        .quad   typeinfo for flossy::format_error
        .quad   flossy::format_error::~format_error() [complete object destructor]
        .quad   flossy::format_error::~format_error() [deleting destructor]
        .quad   std::logic_error::what() const
```