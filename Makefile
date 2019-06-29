#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dengstra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 16:49:11 by dengstra          #+#    #+#              #
#    Updated: 2018/12/14 16:09:44 by dengstra         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so
FLAGS = -Wextra -Wall -Werror

SRC = malloc.c realloc.c show_alloc_mem.c free.c creator.c is_valid_mem.c

SRCO = $(SRC:.c=.o)

CC = gcc

all: $(NAME)

$(NAME): $(SRCO)
	@$(CC) -shared $(FLAGS) $(SRCO) -o $(NAME)
	@ln -sf $(NAME) $(LINK_NAME)

%.o: %.c
	@$(CC) -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINK_NAME)

re: fclean all

.PHONY: clean fclean re all
