When decompiled this binary file reveals itself. It copies byte per byte to a backup file that must be stored in a relative path `./backups`

If we pass it `/home/users/level09/.pass` when executing the binary from the level08 home folder, it won't work :
    
    1. Because there are no folder called /home/users/level09
    2. We don't have permissions to mkdir ~/backups/home/users/level09

In order to copy the .pass file we must do these commands :
```
cd /tmp 
mkdir -p backups/home/users/level09
/home/users/level08/level08 /home/users/level09/.pass
```

We have the flag `fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S`