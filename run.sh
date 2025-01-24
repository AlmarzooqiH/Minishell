#!/bin/bash
make ; clear ; valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-fds=all --trace-children=yes -s --suppressions=readline.supp --log-file="out.log" ./minishell