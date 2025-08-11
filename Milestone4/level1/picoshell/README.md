Assignment name  : picoshell  
Expected files   : picoshell.c  
Allowed functions: close, fork, wait, exit, execvp, dup2, pipe  

--------------------------------------------------------------------------------

Write the following function:

```c
int picoshell(char **cmds[]);
```

The goal of this function is to execute a pipeline. It must execute each command of `cmds` and connect the output of one to the input of the next command (just like a shell).

- `cmds` contains a null-terminated list of valid commands.
- Each row of `cmds` is an argv array directly usable for a call to `execvp`.
- The first argument of each command is the command name or path and can be passed directly as the first argument of `execvp`.

Error handling:

- If any error occurs, the function must return `1` (you must of course close all open file descriptors before returning).
- Otherwise, the function must wait for all child processes and return `0`.

> You will find in this directory a file `main.c` which contains something to help you test your function.

Examples:

```
./picoshell /bin/ls "|" /usr/bin/grep picoshell  
out: picoshell

./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'  
out: squblblb
```
