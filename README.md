# FREND
### The FRont END (command line interpreter) for Transd programming language

This interpreter serves for two purposes: to serve as a companion tool in studying
the Transd language, and for executing Transd programs.

The interpreter allows you to evaluate Transd expressions by simply typing them in
the command line:

```
D : (+ 1 1)
2
```

Frend can also be used for running Transd programs. This can be done in
two ways:

1. Start the interpreter and at the command prompt type "run" and the name of a
Transd assembly file:

`D : run C:\path\to\assembly\asm.td`

2. To run Transd programs without starting interactive interpreter session, you can start
them from the OS's command line:

`C:>frend C:\path\to\assembly\asm.td`

To quit the shell, type 'q' + Return.

## Obtaining FREND

### Windows

Windows users can choose from two options: either download a binary executable file
of Frend interpreter or download the source code and compile it in Visual Studio.

##### Downloading Frend's executable

Choose the latest release here: https://github.com/transd-lang/frend/releases and
download the `frend.exe` file. After downloading the executable you can use it 
right away, without an additional installation procedure.

##### Compiling Frend from source code

Obtain the Frend's source code (either by downloading an archive or by cloning the
project with git onto your computer), open the `frend.sln` solution file in Visual
Studio (2017 and above) and build the solution. After building, the `frend.exe`
file contains the compiled interpreter and is ready to use.


### Linux

1. Obtain the Frend's source code (either by downloading an archive or by cloning the
project with git onto your computer).

2. In the shell go to the `src` directory of the downloaded project and run the
following command, with replacing `<YOUR_COMPILER>` with the name of your compiler,
e.g. `g++`:

`<YOU_COMPILER> -O3 transd.cpp main.cpp -D__LINUX__ -o frend`

After compiling, the `frend` executable contains the compiled interpreter and is
ready to use.
