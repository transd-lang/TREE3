# FREND
### The shell for Transd programming language 

The shell serves for two purposes: to serve as a companion tool in studying
the language and for executing Transd programs.

The shell allows you to evaluate Transd expressions by simply typing them in
the command line:

```
D : (+ 1 1)
2
```

Also the shell can be used for running Transd programs. This can be done in
two ways:

1. Start the shell and at the command prompt type "run" and the name of a
Transd assembly file:

`D : run C:\path\to\assembly\asm.td`

2. To run Transd programs without starting interactive shell, you can start
them from the OS's command line:

`C:>frend C:\path\to\assembly\asm.td`

To quit the shell, type 'q' + Return.
