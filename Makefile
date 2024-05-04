# configuration
CC = gcc				# the compiler
EX = imageminer_driver			# main executable outputted by compiler
IMFILES = main.c imageminer.c		# files of the imagemaker software
HLOCS = quirc/lib/			# additional header locations for the compiler
DEPS = -lm -ljpeg -lpng -lSDL_gfx	# dependencies
# quirc library
QUIRC = quirc/lib/quirc.c quirc/lib/decode.c quirc/lib/identify.c quirc/lib/version_db.c quirc/tests/dbgutil.c

# compilation
all: $(IMFILES) $(QUIRC)
	$(CC) -o $(EX) $(IMFILES) $(QUIRC) -I $(HLOCS) $(DEPS)

# cleanup
clean:
	rm $(EX)
