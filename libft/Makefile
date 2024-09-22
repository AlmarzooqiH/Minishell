# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hamad <hamad@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 17:00:34 by hamalmar          #+#    #+#              #
#    Updated: 2024/09/19 15:16:17 by hamad            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PART_ONE_AND_TWO = ft_isdigit.c ft_memset.c ft_isprint.c \
                   ft_strrchr.c ft_atoi.c ft_strlcat.c \
                   ft_bzero.c ft_strlcpy.c ft_tolower.c \
                   ft_calloc.c ft_memchr.c ft_strlen.c \
                   ft_toupper.c ft_isalnum.c ft_memcmp.c \
                   ft_split.c ft_isalpha.c ft_memcpy.c \
                   ft_strchr.c ft_strncmp.c ft_isascii.c \
                   ft_memmove.c ft_strdup.c ft_strnstr.c \
				   ft_substr.c ft_strjoin.c ft_strtrim.c \
         		   ft_split.c ft_itoa.c ft_strmapi.c \
              	   ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
              	   ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c \
				   ft_print_address.c ft_print_str.c ft_print_number.c \
				   ft_print_num_n_hex.c ft_print_unsigned_num.c ft_isspace.c \
				   free_split.c ft_strcmp.c ft_atol.c ft_atod.c ft_skipspace.c \
				   ft_isonlyspace.c

OBJECTS = $(PART_ONE_AND_TWO:.c=.o)

BONUS_PART = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
              ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
              ft_lstclear.c ft_lstiter.c ft_lstmap.c \
              
BONUS_OBJECTS = $(BONUS_PART:.c=.o)

COMPILER = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

bonus: $(BONUS_OBJECTS)
	ar -rcs $(NAME) $(BONUS_OBJECTS)

%.o: %.c 
	$(COMPILER) $(FLAGS) -c $^ -o $@
clean:
	rm -rf *.o *.out *.gch .vscode

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean res