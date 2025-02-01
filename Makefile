PROGRAM_NAME = minishell
COMPILER = cc
FLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -fsanitize=address,undefined -Werror=address -Wnull-dereference -g
READLINE_FLAG = -lreadline -L/opt/vagrant/embedded/lib/ -Iopt/vagrant/embedded/include/readline 
LIBFT_A = libft/libft.a
MANDATORY = main.c processing.c utils.c utils2.c utils3.c utils4.c utils5.c utils6.c pipes.c execute.c \
			 bash.c redirections.c redirections2.c redirections3.c init.c validate.c builtin_cd.c \
			 builtin_export.c builtin_exit.c builtin_signal.c builtin_unset.c builtin_pwd.c \
			 builtin_echo.c builtin_env.c export_utils.c validate_utils.c validate_utils2.c validate_utils3.c \
			 echo_utils.c export_utils2.c
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
	rm -rf *.o *.out *.gch .vscode *.txt *.log

fclean: clean libft_fclean
	rm -rf $(PROGRAM_NAME)

re: fclean all

.PHONY: all mandatory libft libft_clean libft_fclean clean fclean
