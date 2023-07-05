#!/bin/bash
# sudo sysctl -w kernel.yama.ptrace_scope=0
gcc -fPIC -shared loop.c -o libloop.so -lpthread
gcc main.c -o main -ldl -lpthread -g
