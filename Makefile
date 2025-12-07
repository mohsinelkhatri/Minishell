# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 14:41:13 by nafarid           #+#    #+#              #
#    Updated: 2025/08/30 14:21:21 by melkhatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = build_env.c garbage.c pars.c utils_ex11.c utils_ex1.c utils_ex6.c utils_path1.c \
      builtins.c getenv.c utils_ex12.c utils_ex20.c utils_ex7.c utils_pip.c \
      check_dolar.c handle_meta_char.c skip_qouts.c utils_ex13.c utils_ex21.c utils_ex8.c utils_tok1.c \
      cheking_lexer.c heredoc.c split_tokens.c utils_ex14.c utils_ex9.c \
      expand3.c expand4.c utils1.c utils_ex16.c utils_her.c utilis_ma.c utils_ex2.c utils_ftexit.c \
      export.c utils.c utils_ex17.c utils_ex4.c utils_parc1.c utils_ex3.c utils_ex22.c main.c \
      exuction.c utils_ex10.c utils_ex18.c utils_ex5.c utils_parc.c

OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS = -lreadline
LIBFT_DIR = libft
LIB = $(LIBFT_DIR)/libft.a
all: $(NAME)

$(NAME) : $(OBJS)
	@cd $(LIBFT_DIR) && $(MAKE) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(FLAGS)

%.o :%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	cd $(LIBFT_DIR) && $(MAKE) clean
	rm -f $(OBJS)

fclean: clean
	cd $(LIBFT_DIR) && $(MAKE) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
