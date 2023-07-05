#!/bin/bash

gcc -fPIC -shared loop.c -o libloop.so -lpthread
gcc main.c -o main -ldl -lpthread
