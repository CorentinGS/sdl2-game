OUT = bin
PROG = game_engine

SEARCHPATH += src src/logger
vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += defs.h structs.h

_OBJS += draw.o map.o camera.o entities.o pizza.o
_OBJS += textures.o io.o init.o util.o menu.o input.o
_OBJS += main.o sound.o text.o stage.o player.o



OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
$(OUT)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<
	
# cleaning everything that can be automatically recreated with "make".
clean:
	$(RM) -rf $(OUT) $(PROG) && echo "Cleaned..."
