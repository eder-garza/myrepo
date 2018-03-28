all: mygrep.o
	gcc $^ -o mygrep

%.o: %.c
	gcc -c $< -o $@
