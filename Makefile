CC=gcc
NASM=nasm

CC_FLAGS=-Wall -Wextra -pedantic

OBJS=main.o graphics.o input.o

graphics.exe: $(OBJS)
#	$(CC) $(CC_FLAGS) -o graphics.exe $(OBJS)
	$(CC) -o graphics.exe $(OBJS)

input.o: input.asm
	$(NASM) -f coff -o input.o input.asm

%.o: %.c
#	$(CC) $(CC_FLAGS) -c -o $@ $<
	$(CC) -c -o $@ $<
	
%.o: %.asm
	$(NASM) -f coff -o $@ $<
	
clean:
	del *.o

deps: graphics.h input.h
