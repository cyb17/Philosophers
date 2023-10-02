# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 10:56:05 by yachen            #+#    #+#              #
#    Updated: 2023/10/02 16:13:23 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g

RM = rm -rf

SRC = ./philo/srcs/philosophers.c ./philo/srcs/argument_parsing.c ./philo/srcs/utils1.c \
	  ./philo/srcs/struct_initialization.c ./philo/srcs/utils2.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo "\033[32m\n=============================="
		@echo "\033[32mCompiling $(NAME)---------------"
		@$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)
		@echo "\033[32m----created with success : $(NAME)"
		@echo "\033[32m==============================\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[32m\n=================="
	@echo "\033[32mCleaning $(NAME)----"
	@$(RM) $(OBJ)
	@echo "\033[32m------$(NAME) Cleaned"
	@echo "\033[32m==================\n"

fclean:
	@echo "\033[32m\n=================="
	@echo "\033[32mCleaning $(NAME)----"
	@$(RM) $(OBJ)
	@echo "\033[32m------$(NAME) Cleaned"
	@$(RM) $(NAME)
	@echo "\033[32m==================\n"

re: fclean all

.PHONY: clean fclean all re bonus
