CC = g++
CFLAGS = -Wall -Werror -Wextra
PART1 = day02_part1
PART2 = day02_part2
SRC = day02_part1.cpp \
#      day01_part2.c
OBJ =	$(SRC:.cpp=.o)

all:	$(PART1)

$(EXEC):$(OBJ)
	$(CC) -o $(PART1) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(PART1)

re:	fclean all

.phony: all clean fclean all
