PROGRAM_NAME = minishell
COMPILER = cc
FLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -fsanitize=address,undefined -Werror=address -Wnull-dereference -g
READLINE_FLAG = -lreadline
LIBFT_A = libft/libft.a
MANDATORY = main.c processing.c utils.c utils2.c pipes.c command_utils.c command_utils2.c \
			redirections.c redirections2.c command_utils3.c
MANDATORY_OBJS = $(MANDATORY:.c=.o)

all: libft mandatory

mandatory: $(MANDATORY_OBJS)
	$(COMPILER) $(FLAGS) $(MANDATORY_OBJS) $(LIBFT_A) $(READLINE_FLAG) -o $(PROGRAM_NAME)

$(MANDATORY_OBJS): $(MANDATORY)
	$(COMPILER) $(FLAGS) -c $(MANDATORY)

debug: re libft $(MANDATORY_OBJS)
	$(COMPILER) $(FLAGS) $(DEBUG_FLAGS) $(MANDATORY_OBJS) $(LIBFT_A) $(READLINE_FLAG) -o $(PROGRAM_NAME)

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
