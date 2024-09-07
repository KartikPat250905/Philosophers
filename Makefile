# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:05:34 by karpatel          #+#    #+#              #
#    Updated: 2024/08/24 16:24:32 by karpatel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c init.c
OBJECTS = $(SOURCES:.c=.o)
LIBDIR = ./libft

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $(CFLAGS) $^ ./libft/libft.a

$(SOURCE_DIR)/%.o: %.c
	$(CC) -I -c $(CFLAGS) $< -o $@

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(NAME)

re: fclean all

debug: re

.PHONY: debug all clean fclean re
