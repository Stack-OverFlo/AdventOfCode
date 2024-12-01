CC = gcc
CFLAGS = -Wall -Werror -Wextra
EXEC = day01
SRC = day01.c
OBJ =	$(SRC:.c=.o)

all:	$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(EXEC)

re:	fclean all

.phony: all clean fclean all
