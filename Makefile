# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 15:52:34 by jsaarine          #+#    #+#              #
#    Updated: 2022/07/25 20:09:09 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

CC = clang
S = src/
O = obj/
I = include/

SRCS = $Smain.c \
	   $Stests.c
OBJS = $(patsubst $S%.c,$O%.o, $(SRCS))
INCLS = $IRTv1.h


CFLAGS = -Wall -Wextra -Werror -Wconversion -Wuninitialized

RM = /bin/rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(INCLS) $(LDFLAGS) 

$O%.o: $S%.c $(INCLS)
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $I

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
