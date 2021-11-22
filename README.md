# TREE3
### The Transd Expression Evaluator (3rd revision)

This program is an implementation of Transd programming language. It can be used for two purposes: 
 
 1. For running Transd programs from the command line;
 2. For evaluating Transd expressions from the command line.

## Usage

### Evaluating Transd expressions (REPL mode)

The TREE3 allows you to evaluate Transd expressions by simply typing them in the command line. Which is called REPL or "Read-Evaluate-Print-Loop" mode. This can be useful in studying Tranѕd language, for testing purposes, or for practical applications (e.g. as a command line calculator).

```
D-: (+ 1 1)
2
D-: (sqrt (* (+ 17 15) 2))
8
```

To use TREE3 in REPL mode, do the following:

 1. Start TREE3 from the command line of your OS by typing the `tree3` (possibly with
 the full path to the 'tree3' executable) and press `Return`.
 2. Type your Transd expression on the command line and press `Return`.
 3. To quit, type `q` and press `Return`.

### Running Transd programs (Launcher mode)

TREE3 can also be used as a launcher and executor of Transd programs. Starting a Transd program with the help of TREE3 can be done in one of two ways: from TREE3's command line or from your OS's command line.

#### Starting Transd program from TREE3

Transd programs can be started during interactive REPL sessions:

 1. Start TREE3 from the command line of your OS by typing the `tree3` (possibly with
 the full path to the 'tree3' executable) and press `Return`.
 2. At the TREE3's command prompt type "run", followed by the name of a Transd program file:

`D-: run C:\path\to\program\someprog.td`

#### Starting Transd program from OS's command line

To run Transd programs without starting interactive REPL session, you can start
them right from the OS's command line:

 At the OS command prompt type "tree3", followed by the name of a Transd program file:

`$ tree3 C:\path\to\program\someprog.td`


## Obtaining TREE3

### Windows

Windows users can choose from two options: either download a binary executable file
of TREE3 interpreter or download the source code and compile it in Visual Studio.

##### Downloading TREE3 executable

Choose the latest release here: [TREE3 Releases](https://github.com/transd-lang/TREE3/releases) and download the `tree3.exe` file. After downloading the executable you can use it right away, without an additional installation procedure.

##### Compiling TREE3 from source code

Obtain the TREE3's source code either by cloning the repo or by downloading an archive from GitHub repository. Open the `tree3.sln` solution file in Visual Studio (2017 and above) and build the solution. After building, the `tree3.exe` file contains the compiled TREE3 program and is ready to use.


### Linux

1. Obtain the TREE3's source code either by downloading from GitHub an archive or 
by cloning the git project onto your computer.

2. On the command line go to the directory of the downloaded project and run the 'make'
command:

`$ make`

After compiling, the `tree3` executable contains the compiled TREE3 program and is
ready to use.
