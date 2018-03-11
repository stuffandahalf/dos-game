CC=gcc
NASM=nasm

CC_FLAGS=-Wall -Wextra -pedantic

MAIN_OBJS=main.o input.o
GRAPH_OBJS=graphics.o setvideo.o bmp.o
OBJS=$(MAIN_OBJS) $(GRAPH_OBJS)

graphics.exe: $(OBJS) deps
	$(CC) -o graphics.exe $(OBJS)

%.o: %.c lib/%.h
	$(CC) -c -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $<
	
%.o: %.asm lib/%.h
	$(NASM) -f coff -o $@ $<

%.o: %.asm
	$(NASM) -f coff -o $@ $<
	
clean:
	del *.o
	del *.exe

deps: lib/graphics.h lib/input.h lib/bmp.h
