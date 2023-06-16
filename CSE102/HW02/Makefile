all: compile run

compile: main.c
	@gcc -Wall -Werror -Wextra main.c -lm -o test

run:
	@./test
	
clean:
	@rm -f test
