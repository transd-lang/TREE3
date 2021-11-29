# TREE3
### Transd Expression Evaluator (3rd revision)

This program is an implementation of Transd programming language. It can be used for two purposes: 
 
 1. For running Transd programs from the command line;
 2. For evaluating Transd expressions from the command line.

## Obtaining TREE3

### Windows

Windows users can choose from two options: 
* download a binary executable file of TREE3 compiler;
* download the TREE3's source code and compile it in Visual Studio or with Clang.

##### Downloading TREE3 executable

Choose the latest release here: [TREE3 Releases](https://github.com/transd-lang/TREE3/releases) and download the `tree3.exe` file. After downloading the executable you can use it right away, without an installation procedure.

##### Building TREE3 from source code

For building TREE3 on Windows OS you need to have on your computer one of the two building tools: MS Visual Studio 2017 and newer, or Clang compiler v6.0 and newer.

Obtain the TREE3's source code either by cloning the repo or by downloading an archive from the GitHub repository. Unpack the archive and open the `TREE3` directory in the console or in Windows Explorer. Then do one of the following: 

* Open the `tree3.sln` solution file in Visual Studio and build the solution.
* Issue the following command on the command line of your console:

```
clang++ -std=c++14 -O3 src/transd.cpp src/main.cpp -DWIN32 -o tree3.exe
```

After building, the `tree3.exe` file contains the TREE3 compiler and is ready to use.


### Linux

1. Obtain the TREE3's source code either by downloading from GitHub an archive or 
by cloning the git project onto your computer.

2. On the command line go to the directory of the downloaded project and run the 'make'
command:

`$ make`

Alternatively, you can do the building with the following command:

```
clang++ -std=c++14 -O3 src/transd.cpp src/main.cpp -D__LINUX__ -lpthread -o tree3
```

After compiling, the `tree3` executable contains the TREE3 compiler and is
ready to use.


## Usage

### Evaluating Transd expressions (REPL mode)

The TREE3 allows you to evaluate Transd expressions by simply typing them on the command line. Which is called REPL or "Read-Evaluate-Print-Loop" mode. This can be useful in studying Tranѕd language, for testing purposes, or for practical applications (e.g. as a command line calculator).

```
_) (+ 1 1)
2
_) (sqrt (* (+ 17 15) 2))
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

`_) run C:\path\to\program\someprog.td`

#### Starting Transd program from OS's command line

To run Transd programs without starting interactive REPL session, you can start
them right from the OS's command line:

 At the OS command prompt type "tree3", followed by the name of a Transd program file:

`$ tree3 C:\path\to\program\someprog.td`


