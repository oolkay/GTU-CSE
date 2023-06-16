all: compile run

compile: main.c
	@gcc -Wall -Werror -Wextra main.c -o main 

run: main
	@./main

clean:
	@rm -f main