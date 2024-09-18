# MINISHELL

<img src="https://media.licdn.com/dms/image/v2/D5605AQF4p3RRu85y2Q/feedshare-thumbnail_720_1280/feedshare-thumbnail_720_1280/0/1701954290874?e=2147483647&v=beta&t=KZT3ggeH_XFDeUNnvCzm9uMBCm8_GTJ9AURlmvbnKsY" alt="drawing" width="500"/>

__Minishell__ is a my first team project in 42 that mimics the behavior of bash. This project aiming to deepen your understanding of system calls, process management, and signal handling in C.

## Table of Contents

- [Introduction](#introduction)
- [Project Requirements](#project-requirements)
- [Built-in Commands](#built-in-commands)

## Introduction

..

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
