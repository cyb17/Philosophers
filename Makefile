# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 10:56:05 by yachen            #+#    #+#              #
#    Updated: 2023/09/13 14:28:15 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

NAME_B = philo_bonus

CC = gcc

CFLAGS =  -Wall -Wextra -Werror -g

RM = rm -rf

SRC = ./philo/srcs/philosophers.c ./philo/srcs/argument_parsing.c \

SRC_B = 

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

bonus: $(NAME_B)

$(NAME): $(OBJ)
		@echo "\033[32m\n=============================="
		@echo "\033[32mCompiling $(NAME)---------------"
		@$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)
		@echo "\033[32m----created with success : $(NAME)"
		@echo "\033[32m==============================\n"

$(NAME_B): $(OBJ_B)
		@echo "\033[32m\n=============================="
		@make -C ./libft
		@echo "\033[32mCompiling $(NAME_B)---------------"
		@$(CC) $(CFLAGS) $(OBJ_B) -lpthread -o $(NAME_B)
		@echo "\033[32m----Created with success : $(NAME_B)"
		@echo "\033[32m==============================\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[32m\n=================="
	@echo "\033[32mCleaning $(NAME)----"
	@$(RM) $(OBJ) $(OBJ_B)
	@echo "\033[32m------$(NAME) Cleaned"
	@echo "\033[32m==================\n"

fclean:
	@echo "\033[32m\n=================="
	@echo "\033[32mCleaning $(NAME)----"
	@$(RM) $(OBJ) $(OBJ_B)
	@echo "\033[32m------$(NAME) Cleaned"
	@$(RM) $(NAME) $(NAME_B)
	@echo "\033[32m==================\n"

re: fclean all

.PHONY: clean fclean all re bonus
