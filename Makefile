NAME = MidiHero
CC = c++
CFLAGS = -std=c++11
SRC =  main.cpp Note.cpp Game.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) 				#replace paths
	$(CC) -o $(NAME) $(CFLAGS) /Users/laatu/Desktop/repo/midifile/lib/libmidifile.a -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system $(OBJ)

$(OBJ): $(SRC) 			#replace path
	$(CC) -c $(CFLAGS) -I/usr/local/Cellar/sfml/2.6.1/include $(SRC)


clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

