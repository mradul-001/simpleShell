## Shell

This repository contains a basic implementation of `shell` using C programming language.

### Usage:  
1. Compile the code using Makefile:  
```bash
        make
```
    

2. The shell has two modes - interactive and batch mode.
    - In interactive mode the shell asks for user input, and executes the command given.
    - In batch mode user passes the name of a batchfile containing commands as runtime argument, the shell runs all the commands present in the batchfile.  

    Example of how to use batch mode is as follows: 
```bash
    ./shell example.txt
```    

3. To clean the working directory, run:
```bash
    make clean
```
