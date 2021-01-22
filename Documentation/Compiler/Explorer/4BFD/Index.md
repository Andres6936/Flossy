The current revision number: 4bfdd0c7b817f660e0a9daf83ba777f74dd8db13 (See 4BFD)

- Version Base (Original).

With the compiler explorer (Godbolt)[https://godbolt.org/].

```cpp
int main()
{
    flossy::format("Hello World {}.", 42);
}
```

Produce with the options: x86-64 gcc 10.2 - -std=c++17 -O3

```asm
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
```