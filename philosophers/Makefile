# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 10:56:05 by yachen            #+#    #+#              #
#    Updated: 2023/10/05 17:26:50 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g #-fsanitize=thread

RM = rm -rf

SRC = philosophers.c argument_parsing.c utils1.c utils2.c \
	  struct_initialization.c monitor.c routine.c \

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
