CC=gcc
OBJDIR = obj
CFLAGS=-Wall -ansi -pedantic -g -pg
LDFLAGS= -g -pg -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lm
EXEC=exo


SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

all: $(EXEC)

exo: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c constante.h
	$(CC) $(CFLAGS) -o $@ -c $< 
clean:
	rm $(EXEC)
	rm $(OBJDIR)/*.o
