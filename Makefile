# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 15:52:34 by jsaarine          #+#    #+#              #
#    Updated: 2022/07/26 15:53:15 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = $Smain.c \
	  $Stests.c

CC = clang

S = src/
O = obj/
I = inc/
D = dep/

OBJ = $(SRC:$S%=$O%.o)
DEP = $(SRC:$S%=$D%.d)

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -Wconversion -Wuninitialized
CFLAGS += -I$I
LDFLAGS += -g -fsanitize=address

OBJ = $(SRC:$S%=$O%.o)
DEP = $(SRC:$S%=$D%.d)

RM = /bin/rm -f
RMDIR = /bin/rmdir

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir $@

$(DEP): | $D

$(DEP): $D%.d: $S%
	$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

cleanobj:
	$(RM) $(wildcard $(OBJ))

cleanobjdir: cleanobj
	$(RMDIR) $O

cleandep:
	$(RM) $(wildcard $(DEP))

cleandepdir: cleandep
	$(RMDIR) $D

clean: cleanobjdir cleandepdir

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)
