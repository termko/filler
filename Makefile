all:
	gcc -Wall -Wextra -Werror main.c libft/libft.a -o ydavis.filler
debug:
	gcc -Wall -Wextra -Werror -g main.c libft/libft.a -o ydavis.filler
