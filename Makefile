NAME = brot
CFLAGS = -I./Include -O3 -mavx2
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
HEADERS = $(wildcard Include/*.h)
SOURCES = $(wildcard Src/*.cpp)
OBJ = $(patsubst %.cpp, Src_o/%.o, $(notdir $(SOURCES)))

.PHONY: all clean createDir

all: createDir $(NAME)

$(NAME): $(OBJ)
	g++ $^ -o $@ $(CFLAGS) $(LDFLAGS)

Src_o/%.o: Src/%.cpp $(HEADERS)
	g++ -c $< -o $@ $(CFLAGS)

createDir:
	mkdir -p Src_o

# NoGraphics version
$(NAME)_NoGraph: CFLAGS += -DDisableGraphics
$(NAME)_NoGraph: createDir $(NAME)

clean:
	rm -rf Src_o $(NAME) $(NAME)_NoGraph