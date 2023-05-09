#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11 -w

_BLUE=\e[34m
_PURPLE=\e[35m
_CYAN=\e[36m
_END=\e[0m
OBJ_COLOR   = \033[0;36m
COM_COLOR   = \033[0;34m
OK_COLOR    = \033[0;32m


all: $(NOM)

%.o: %.c
			@printf "$(COM_COLOR)MLX object : $(OBJ_COLOR)    %-33.33s\r$(_END)" $@
			@${CC} ${CFLAGS} -c $< -o $@

$(NOM):	$(OBJ)
	@printf "$(COM_COLOR)compiling MLX				      $(OK_COLOR)[✓]$(_END)\n"
	@ar rc $(NOM) $(OBJ)
	@ranlib -s $(NOM)
#	@printf "$(COM_COLOR)MLX				  	      $(OK_COLOR)[✓]$(_END)\n"

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all
