all: mygrep.o
	gcc $^ -o mygrep

%.o: %.c
	gcc -c $< -o $@
clean:
	rm mygrep.o mygrep
