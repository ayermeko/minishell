<img src="https://github.com/user-attachments/assets/4f10606b-20d6-4d06-a33d-e4b2e1fc6c7f" width="1000"/>

__Minishell__ is a my first team project in 42 that mimics the behavior of bash. This project aiming to deepen your understanding of system calls, process management, and signal handling in C.

## Table of Contents

- [Introduction](#introduction)
- [Project Requirements](#project-requirements)
- [Built-in Commands](#built-in-commands)
- [How to Run Program](#how-to-run-program)

## Introduction

This project marked my first team collaboration at 42, where we developed a basic shell, called minishell. The primary objective was to create a simplified version of a Unix shell that could execute commands, manage processes, and handle basic input/output redirection. Working on this project allowed us to dive deep into the internal workings of a shell, and it sharpened our understanding of system calls, process control, and inter-process communication. Collaborating with my teammate was a valuable experience, as we learned to merge ideas, troubleshoot effectively, and tackle complex problems together.

## Project Requirements

-    Display a prompt while waiting for user input.
-    Execute commands by searching the right executable using the PATH environment variable or absolute/relative paths.
-    Handle:
    
    0.0)Redirections (<, >, >>, <<).
    0.1)Piping between commands (|).
    0.2)Environment variables.
    0.3)History of executed commands.

Custom signal handling (e.g., ctrl-C, ctrl-D, ctrl-\).
Robust memory management (except for readline() memory leaks).

## Built-in Commands

The shell includes the following built-in commands:

    echo [-n]: Display a line of text.
    cd [directory]: Change the current directory.
    pwd: Print the current working directory.
    export: Set environment variables.
    unset: Remove environment variables.
    env: Display the environment variables.
    exit: Exit the shell.

## External functs.

readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

__Let's break down the each function.__

void rl_clear_history(void) - clears the entire command history list, freeing all memory associated with the stored commands. This function removes all entries from the history list that the user has entered during the current session.

int rl_on_new_line(void) - is used to manage the display of the command line prompt when interacting with users in a terminal. It prepares the Readline library to handle a new input line after some output has been written to the terminal, ensuring the prompt is correctly positioned.

int access(const char *pathname, int mode) - function is used to check the accessibility of a file (or a path) for certain types of operations. It checks whether the calling process has permission to read, write, or execute a specified file, or simply if the file exists.

pid_t fork(void) - for creating a child process, where they have different memory spaces, instead of a threads.

## How to Run Program

To compile and run the minishell program, follow these steps:

1. First, you need to clone the repository:
   ```git status
git status
git add
git commit
```
