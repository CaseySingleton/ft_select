# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csinglet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 18:59:57 by csinglet          #+#    #+#              #
#    Updated: 2018/11/09 23:25:49 by csinglet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_select

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -O3
FLAGS	= $(CFLAGS)

FILES	= main.c print_formatting.c list_functions.c signals.c \
		  input_commands.c argument_functions.c config.c utils.c 

OBJ	= $(addprefix build/, $(FILES:.c=.o))

INC_FT	= -I libft/includes
LINK_FT	= -L libft -lft
FT	= $(INC_FT) $(LINK_FT)

INC_PF	= -I ft_printf/includes
LINK_PF	= -L ft_printf -lftprintf
PF	= $(INC_PF) $(LINK_PF)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating libft.a"
	@make -C libft
	@echo "Creating ftprintf.a"
	@make -C ft_printf
	@echo "Creating: $(NAME)"
	@$(CC) $(FLAGS) $(FT) $(PF) -I includes $(OBJ) -o $@ -ltermcap

build:
	@echo "Creating build directory"
	@mkdir build

build/%.o: srcs/%.c | build
	@echo "  Building $@"
	@$(CC) $(INC_FT) $(INC_PF) -I includes -c $< -o $@

clean:
	@rm -fr build
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all
