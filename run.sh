#!/bin/bash
make re ; clear ; valgrind --leak-check=full --leak-resolution=high --track-fds=all --trace-children=yes -s --log-file="out.log" ./minishell
