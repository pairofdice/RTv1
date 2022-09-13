# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 15:52:34 by jsaarine          #+#    #+#              #
#    Updated: 2022/09/13 15:26:47 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1


CC = clang

S = src/
O = obj/
I = inc/ dep/libsdl2/include/ libft/
D = dep/

SRC = $Smain.c \
	$Sinit.c \
	$Sdraw.c \
	$Spixel_put_color.c \
	$Sget_shading.c \
	$Slight_new.c \
	$Shit_record_new.c \
	$Sintersects.c \
	$Squadratic.c \
	$Stests.c \
	$Svec3_add.c \
	$Svec3_cross.c \
	$Svec3_dot.c \
	$Svec3_mag.c \
	$Svec3_neg.c \
	$Svec3_scalar_mult.c \
	$Svec3_sqr.c \
	$Svec3_sub.c \
	$Svec3_new.c \
	$Svec3_ray_at.c \
	$Svec3_unit.c \
	$Sobj_sphere.c \
	$Sobj_plane.c \
	$Sobj_cone.c \
	$Sobj_cylinder.c \
	$Sload.c \
	$Sparse.c \
	$Scamera.c \
	$Scurrent_ray.c \
	
#	$Sft_memcpy.c \
#	$Sft_memset.c \

OBJ = $(SRC:$S%=$O%.o)
DEP = $(SRC:$S%=$D%.d)

SDL2_MK = libsdl2/Makefile
SDL2_LIB = $Dlibsdl2/lib/libSDL2.a
SDL2_CFLAGS = `$Dlibsdl2/bin/sdl2-config --cflags`
SDL2_LDFLAGS = `$Dlibsdl2/bin/sdl2-config --libs`

LIBFT = libft/
LIBA = libft/libft.a

CFLAGS += -c -Wall -Wextra #-Werror
#CFLAGS += -Wconversion -Wuninitialized
CFLAGS += $(SDL2_CFLAGS)
CFLAGS += $(addprefix -I, $I)

LDFLAGS += -g -fsanitize=address
LDFLAGS += $(SDL2_LDFLAGS)

OBJ = $(SRC:$S%=$O%.o)
DEP = $(SRC:$S%=$D%.d)

RM = /bin/rm -f
RMDIR = /bin/rm -fr

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIBA)
	$(CC) $(LDFLAGS) $(LIBA) $^ -o $@

$O:
	@mkdir $@

$(OBJ): $(SDL2_LIB) | $O
$(OBJ):| $O

$(OBJ): $O%.o: $S% $(LIBA) | $O
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir $@

$(DEP): | $D

#INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
#FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

$(DEP): $D%.d: $S%
	$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(SDL2_MK):
	cd libsdl2 && ./configure --prefix=$(abspath $Dlibsdl2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(SDL2_LIB): $(SDL2_MK) | $D
	$(MAKE) --directory=libsdl2 install

$(LIBA):
	make -C $(LIBFT)

cleanobj:
	$(RM) $(wildcard $(OBJ))

cleanobjdir: cleanobj
	$(RMDIR) $O

cleandep:
	$(RM) $(wildcard $(DEP))

cleandepdir: cleandep
	$(RMDIR) $D

clean: cleanobjdir cleandepdir
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

-include $(DEP)
