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
mov     edi, DWORD PTR CSWTCH.71[0+rax*4]
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
std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::format_it<std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, char const*, int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, char const*, char const*, int const&):
push    r15
push    r14
push    r13
push    r12
mov     r12, rdi
push    rbp
push    rbx
sub     rsp, 104
mov     QWORD PTR [rsp+16], rcx
cmp     rsi, rdx
je      .L226
mov     rbx, rsi
mov     r13, rdx
lea     r9, [rdi+16]
jmp     .L144
.L146:
mov     rbx, QWORD PTR [r12+8]
mov     rax, QWORD PTR [r12]
lea     r15, [rbx+1]
cmp     rax, r9
je      .L212
mov     rdx, QWORD PTR [r12+16]
.L198:
cmp     r15, rdx
ja      .L238
mov     BYTE PTR [rax+rbx], r14b
mov     rax, QWORD PTR [r12]
mov     QWORD PTR [r12+8], r15
mov     BYTE PTR [rax+1+rbx], 0
cmp     rbp, r13
je      .L226
.L201:
mov     rbx, rbp
.L144:
movzx   r14d, BYTE PTR [rbx]
lea     rbp, [rbx+1]
cmp     r14b, 123
jne     .L146
cmp     rbp, r13
je      .L239
movzx   r14d, BYTE PTR [rbx+1]
cmp     r14b, 123
jne     .L149
lea     rbp, [rbx+2]
jmp     .L146
.L238:
xor     ecx, ecx
xor     edx, edx
mov     r8d, 1
mov     rsi, rbx
mov     rdi, r12
mov     QWORD PTR [rsp+8], r9
call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_mutate(unsigned long, unsigned long, char const*, unsigned long)
mov     rax, QWORD PTR [r12]
cmp     rbp, r13
mov     r9, QWORD PTR [rsp+8]
mov     BYTE PTR [rax+rbx], r14b
mov     rax, QWORD PTR [r12]
mov     QWORD PTR [r12+8], r15
mov     BYTE PTR [rax+1+rbx], 0
jne     .L201
.L226:
add     rsp, 104
mov     rax, r12
pop     rbx
pop     rbp
pop     r12
pop     r13
pop     r14
pop     r15
ret
.L212:
mov     edx, 15
jmp     .L198
.L149:
mov     edi, 24
call    operator new(unsigned long)
movdqa  xmm2, XMMWORD PTR C.12.0[rip]
mov     rdi, rax
movups  XMMWORD PTR [rax], xmm2
mov     rax, QWORD PTR C.12.0[rip+16]
mov     QWORD PTR [rsp+8], rdi
mov     QWORD PTR [rdi+16], rax
lea     rax, [rdi+24]
mov     edi, 24
mov     QWORD PTR [rsp+32], rax
call    operator new(unsigned long)
movdqa  xmm3, XMMWORD PTR C.13.1[rip]
mov     rsi, rax
mov     QWORD PTR [rsp+24], rax
mov     edi, 64
lea     r14, [rsi+24]
movups  XMMWORD PTR [rax], xmm3
mov     rax, QWORD PTR C.13.1[rip+16]
mov     QWORD PTR [rsi+16], rax
call    operator new(unsigned long)
movdqa  xmm4, XMMWORD PTR C.14.2[rip]
mov     rdi, QWORD PTR [rsp+8]
mov     r15, rax
lea     rsi, [rax+64]
movdqa  xmm5, XMMWORD PTR C.14.2[rip+16]
movdqa  xmm6, XMMWORD PTR C.14.2[rip+32]
movdqa  xmm7, XMMWORD PTR C.14.2[rip+48]
movzx   edx, BYTE PTR [rbx+1]
movups  XMMWORD PTR [rax], xmm4
movups  XMMWORD PTR [rax+16], xmm5
movups  XMMWORD PTR [rax+32], xmm6
movups  XMMWORD PTR [rax+48], xmm7
cmp     dl, BYTE PTR [rdi]
je      .L206
lea     rax, [rdi+8]
cmp     dl, BYTE PTR [rdi+8]
je      .L150
lea     rax, [rdi+16]
cmp     dl, BYTE PTR [rdi+16]
je      .L150
.L151:
mov     DWORD PTR [rsp+32], 0
jmp     .L205
.L206:
mov     rax, rdi
.L150:
cmp     QWORD PTR [rsp+32], rax
je      .L151
mov     eax, DWORD PTR [rax+4]
lea     rbp, [rbx+2]
mov     DWORD PTR [rsp+32], eax
cmp     rbp, r13
je      .L240
movzx   edx, BYTE PTR [rbx+2]
.L205:
mov     rdi, QWORD PTR [rsp+24]
cmp     BYTE PTR [rdi], dl
je      .L207
lea     rax, [rdi+8]
cmp     BYTE PTR [rdi+8], dl
je      .L155
lea     rax, [rdi+16]
cmp     BYTE PTR [rdi+16], dl
je      .L155
.L156:
mov     rax, rbp
mov     r10d, 2
jmp     .L204
.L207:
mov     rax, rdi
.L155:
cmp     r14, rax
je      .L156
mov     r10d, DWORD PTR [rax+4]
lea     rax, [rbp+1]
cmp     rax, r13
je      .L241
movzx   edx, BYTE PTR [rbp+1]
.L204:
mov     BYTE PTR [rsp+47], 0
cmp     dl, 48
je      .L242
.L159:
xor     ebp, ebp
jmp     .L164
.L243:
lea     edx, [rbp+0+rbp*4]
movsx   ecx, cl
add     rax, 1
lea     ebp, [rcx+rdx*2]
cmp     rax, r13
je      .L163
movzx   edx, BYTE PTR [rax]
.L164:
lea     ecx, [rdx-48]
mov     r8, rax
cmp     cl, 9
jbe     .L243
mov     r9d, 6
cmp     dl, 46
je      .L244
.L165:
cmp     r8, r13
je      .L245
mov     rax, r15
jmp     .L170
.L249:
cmp     BYTE PTR [rax+8], dl
je      .L246
cmp     BYTE PTR [rax+16], dl
je      .L247
cmp     BYTE PTR [rax+24], dl
je      .L248
add     rax, 32
cmp     rax, rsi
je      .L176
.L170:
cmp     BYTE PTR [rax], dl
jne     .L249
.L172:
cmp     rax, rsi
je      .L176
lea     rbx, [r8+1]
mov     eax, DWORD PTR [rax+4]
cmp     rbx, r13
je      .L250
cmp     BYTE PTR [r8+1], 125
jne     .L202
mov     esi, 64
mov     rdi, r15
mov     DWORD PTR [rsp+60], eax
lea     r14, [r8+2]
mov     DWORD PTR [rsp+56], r9d
mov     DWORD PTR [rsp+48], r10d
call    operator delete(void*, unsigned long)
mov     rdi, QWORD PTR [rsp+24]
mov     esi, 24
call    operator delete(void*, unsigned long)
mov     rdi, QWORD PTR [rsp+8]
mov     esi, 24
call    operator delete(void*, unsigned long)
mov     rax, QWORD PTR [rsp+16]
mov     r10d, DWORD PTR [rsp+48]
mov     r9d, DWORD PTR [rsp+56]
mov     esi, DWORD PTR [rax]
mov     eax, DWORD PTR [rsp+60]
cmp     eax, 6
je      .L182
cmp     eax, 1
je      .L182
movd    xmm4, DWORD PTR [rsp+32]
movd    xmm1, r9d
movd    xmm0, eax
movd    xmm5, ebp
punpckldq       xmm0, xmm5
cmp     DWORD PTR [rsp+32], 1
mov     DWORD PTR [rsp+80], r10d
punpckldq       xmm1, xmm4
punpcklqdq      xmm0, xmm1
movaps  XMMWORD PTR [rsp+64], xmm0
je      .L251
mov     BYTE PTR [rsp+84], 0
.L187:
lea     rcx, [rsp+64]
xor     edx, edx
mov     rdi, r12
call    std::enable_if<std::is_integral<unsigned int>::value&&std::is_unsigned<unsigned int>::value, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::type flossy::(anonymous namespace)::format_integer_unchecked<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int, bool, flossy::conversion_options const&)
.L188:
sub     r13, r14
lea     r15, [r12+16]
lea     r9, [rbx+1+r13]
test    r13, r13
jle     .L226
.L197:
mov     rbx, QWORD PTR [r12+8]
mov     rax, QWORD PTR [r12]
movzx   r13d, BYTE PTR [r14]
lea     rbp, [rbx+1]
cmp     rax, r15
je      .L211
mov     rdx, QWORD PTR [r12+16]
.L193:
cmp     rbp, rdx
ja      .L252
mov     BYTE PTR [rax+rbx], r13b
mov     rax, QWORD PTR [r12]
add     r14, 1
mov     QWORD PTR [r12+8], rbp
mov     BYTE PTR [rax+1+rbx], 0
cmp     r14, r9
jne     .L197
jmp     .L226
.L242:
lea     rcx, [rax+1]
cmp     rcx, r13
je      .L163
movzx   edx, BYTE PTR [rax+1]
mov     BYTE PTR [rsp+47], 1
mov     rax, rcx
jmp     .L159
.L252:
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
cmp     r9, r14
jne     .L197
jmp     .L226
.L211:
mov     edx, 15
jmp     .L193
.L176:
cmp     dl, 125
jne     .L202
mov     esi, 64
mov     rdi, r15
mov     DWORD PTR [rsp+60], r9d
lea     r14, [r8+1]
mov     DWORD PTR [rsp+56], r10d
mov     QWORD PTR [rsp+48], r8
call    operator delete(void*, unsigned long)
mov     rdi, QWORD PTR [rsp+24]
mov     esi, 24
call    operator delete(void*, unsigned long)
mov     rdi, QWORD PTR [rsp+8]
mov     esi, 24
call    operator delete(void*, unsigned long)
mov     rax, QWORD PTR [rsp+16]
mov     r8, QWORD PTR [rsp+48]
mov     r10d, DWORD PTR [rsp+56]
mov     r9d, DWORD PTR [rsp+60]
mov     esi, DWORD PTR [rax]
mov     rbx, r8
mov     eax, 6
.L182:
mov     edi, esi
movd    xmm2, DWORD PTR [rsp+32]
movd    xmm1, r9d
mov     edx, esi
sar     edi, 31
movd    xmm0, eax
movd    xmm3, ebp
shr     edx, 31
xor     esi, edi
punpckldq       xmm1, xmm2
punpckldq       xmm0, xmm3
mov     DWORD PTR [rsp+80], r10d
sub     esi, edi
punpcklqdq      xmm0, xmm1
cmp     DWORD PTR [rsp+32], 1
movaps  XMMWORD PTR [rsp+64], xmm0
je      .L253
mov     BYTE PTR [rsp+84], 0
.L191:
lea     rcx, [rsp+64]
mov     rdi, r12
call    std::enable_if<std::is_integral<unsigned int>::value&&std::is_unsigned<unsigned int>::value, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::type flossy::(anonymous namespace)::format_integer_unchecked<char, std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, unsigned int, bool, flossy::conversion_options const&)
jmp     .L188
.L244:
add     rax, 1
cmp     rax, r13
je      .L168
xor     r9d, r9d
.L169:
movzx   edx, BYTE PTR [rax]
mov     r8, rax
lea     ecx, [rdx-48]
cmp     cl, 9
ja      .L165
lea     edx, [r9+r9*4]
movsx   ecx, cl
add     rax, 1
lea     r9d, [rcx+rdx*2]
cmp     r13, rax
jne     .L169
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
.L246:
add     rax, 8
jmp     .L172
.L247:
add     rax, 16
jmp     .L172
.L253:
movzx   eax, BYTE PTR [rsp+47]
mov     BYTE PTR [rsp+84], al
jmp     .L191
.L248:
add     rax, 24
jmp     .L172
.L251:
movzx   eax, BYTE PTR [rsp+47]
mov     BYTE PTR [rsp+84], al
jmp     .L187
.L250:
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
.L202:
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
jmp     .L154
.L237:
mov     rbx, rax
jmp     .L183
jmp     .L237
.L183:
mov     rdi, rbp
call    __cxa_free_exception
.L154:
mov     esi, 64
mov     rdi, r15
call    operator delete(void*, unsigned long)
.L184:
mov     rdi, QWORD PTR [rsp+24]
mov     esi, 24
mov     rbp, rbx
call    operator delete(void*, unsigned long)
.L185:
mov     rdi, QWORD PTR [rsp+8]
mov     esi, 24
call    operator delete(void*, unsigned long)
mov     rdi, rbp
call    _Unwind_Resume
.L163:
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
.L241:
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
jmp     .L237
jmp     .L237
.L240:
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
jmp     .L237
jmp     .L237
mov     rbx, rax
jmp     .L184
jmp     .L237
.L239:
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
jmp     .L185
mov     r12, rax
mov     rdi, rbp
call    __cxa_free_exception
mov     rdi, r12
call    _Unwind_Resume
.LC2:
.string "Hello World {}."
main:
push    rbp
mov     edx, OFFSET FLAT:.LC2+15
mov     esi, OFFSET FLAT:.LC2
push    rbx
sub     rsp, 56
lea     rbx, [rsp+32]
lea     rcx, [rsp+12]
mov     DWORD PTR [rsp+12], 42
lea     rdi, [rsp+16]
mov     QWORD PTR [rsp+16], rbx
mov     QWORD PTR [rsp+24], 0
mov     BYTE PTR [rsp+32], 0
call    std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > flossy::format_it<std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, char const*, int>(std::back_insert_iterator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, char const*, char const*, int const&)
mov     rdi, QWORD PTR [rsp+16]
cmp     rdi, rbx
je      .L258
mov     rax, QWORD PTR [rsp+32]
lea     rsi, [rax+1]
call    operator delete(void*, unsigned long)
.L258:
add     rsp, 56
xor     eax, eax
pop     rbx
pop     rbp
ret
mov     rbp, rax
jmp     .L256
main.cold:
CSWTCH.71:
.long   2
.long   10
.long   8
.long   16
C.14.2:
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
C.13.1:
.byte   43
.zero   3
.long   0
.byte   32
.zero   3
.long   1
.byte   45
.zero   3
.long   2
C.12.0:
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