CC = gcc
CFLAGS = -Wall -Wextra -Werror libft/libft.a
SRC = best.c fill_heatmap.c init.c init_field.c init_heatmap.c init_piece.c\
	  init_player.c main.c reset.c try_put.c utils.c
NAME = ydavis.filler
LIBMAKE = libft

all:		$(NAME)

$(NAME):	$(LIBMAKE) $(SRC)
	@make --directory=$(LIBMAKE)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@make --directory=$(LIBMAKE) clean

fclean:		clean
	@rm -rf $(NAME)
	@make --directory=$(LIBMAKE) fclean

re:			fclean all

debug:		$(LIBMAKE) $(SRC)
	@make --directory=$(LIBMAKE)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
