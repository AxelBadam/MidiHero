NAME = MidiHero
CC = c++
CFLAGS = -std=c++17
SRC = main.cpp Note.cpp Game.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

SFML_INCLUDE_PATH = /Users/axel/Desktop/MidiHero/SFML-2.6.1-macOS-clang-arm64/include
SFML_LIB_PATH = /Users/axel/Desktop/MidiHero/SFML-2.6.1-macOS-clang-arm64/lib
MIDIFILE_LIB = /Users/axel/Desktop/MidiHero/midifile/lib/libmidifile.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(MIDIFILE_LIB) -L$(SFML_LIB_PATH) -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -Wl,-rpath,$(SFML_LIB_PATH)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -I$(SFML_INCLUDE_PATH) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all