# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 15:52:34 by jsaarine          #+#    #+#              #
#    Updated: 2022/08/01 14:26:49 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = $Smain.c \
	$Sinit.c \
	$Spixel_put_color.c \
	$Sft_memcpy.c \
	$Sft_memset.c \
	$Stests.c

CC = clang

S = src/
O = obj/
I = inc/ dep/libsdl2/include/
D = dep/

OBJ = $(SRC:$S%=$O%.o)
DEP = $(SRC:$S%=$D%.d)

SDL2_MK = libsdl2/Makefile
SDL2_LIB = $Dlibsdl2/lib/libSDL2.a
SDL2_CFLAGS = `$Dlibsdl2/bin/sdl2-config --cflags`
SDL2_LDFLAGS = `$Dlibsdl2/bin/sdl2-config --libs`

CFLAGS += -c -Wall -Wextra -Werror
CFLAGS += -Wconversion -Wuninitialized
CFLAGS += $(SDL2_CFLAGS)
CFLAGS += $(addprefix -I, $I)

#LDFLAGS += -g -fsanitize=address
LDFLAGS += $(SDL2_LDFLAGS)

OBJ = $(SRC:$S%=$O%.o)
DEP = $(SRC:$S%=$D%.d)

RM = /bin/rm -f
RMDIR = /bin/rmdir

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$O:
	@mkdir $@

$(OBJ): $(SDL2_LIB) | $O

$(OBJ): $O%.o: $S%
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir $@

$(DEP): | $D

$(DEP): $D%.d: $S%
	$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(SDL2_MK):
	cd libsdl2 && ./configure --prefix=$(abspath $Dlibsdl2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(SDL2_LIB): $(SDL2_MK) | $D
	$(MAKE) --directory=libsdl2 install

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
