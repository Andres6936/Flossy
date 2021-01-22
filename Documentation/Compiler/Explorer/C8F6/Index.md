The current revision number: c8f6baaeabb5f048eca321eab2eca0f247fc8d7a (See C8F6)

- This revision use basic_string_view instead of basic_string.

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
```