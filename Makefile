NAME = test
CC = c++
CFLAGS = -std=c++11
SRC =  main.cpp Note.cpp Game.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) /Users/atuliara/reorg/midifile/lib/libmidifile.a -L/Users/atuliara/.brew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system $(OBJ)

$(OBJ): $(SRC)
	$(CC) -c $(CFLAGS) -I/Users/atuliara/.brew/Cellar/sfml/2.6.0/include $(SRC)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

