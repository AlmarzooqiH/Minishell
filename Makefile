PROGRAM_NAME = minishell
COMPILER = cc
FLAGS = -Wall -Wextra -Werror
READLINE_FLAG = -lreadline
LIBFT_A = libft/libft.a
MANDATORY = main.c processing.c utils.c utils2.c utils3.c commands_utils1.c
MANDATORY_OBJS = $(MANDATORY:.c=.o)

all: libft mandatory

mandatory: $(MANDATORY_OBJS)
	$(COMPILER) $(FLAGS) $(MANDATORY_OBJS) $(LIBFT_A) $(READLINE_FLAG) -o $(PROGRAM_NAME)

$(MANDATORY_OBJS): $(MANDATORY)
	$(COMPILER) $(FLAGS) -c $(MANDATORY)

libft:
	cd libft ; make

libft_clean:
	cd libft ; make clean

libft_fclean:
	cd libft ; make fclean

clean: libft_clean
	rm -rf *.o *.out *.gch .vscode *.txt

fclean: clean libft_fclean
	rm -rf $(PROGRAM_NAME)

re: fclean all

.PHONY: all mandatory libft libft_clean libft_fclean clean fclean
