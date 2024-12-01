CC = gcc
CFLAGS = -Wall -Werror -Wextra
PART1 = day01_part1
PART2 = day01_part2
SRC = day01_part1.c \
      day01_part2.c
OBJ =	$(SRC:.c=.o)

all:	$(PART1) $(PART2)

$(EXEC):$(OBJ)
	$(CC) -o $(PART1) $(PART2) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(PART1) $(PART2)

re:	fclean all

.phony: all clean fclean all
