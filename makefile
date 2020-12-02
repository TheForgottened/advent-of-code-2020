FILES = $(sort $(patsubst %.c,%, $(wildcard ./*/*/*.c)))
CC = gcc

all: $(FILES)
	@ echo "Compilation of all puzzles finished successfully."
	@ echo "Merry Christmas and a Happy 2021!"

%: %.c
	@ $(CC) $< -o $@

clean:
	@ rm $(patsubst %,%.exe, $(FILES)) -f
	@ rm $(FILES) -f
	@ echo "Repository is now clean of executables!"