####	C	O	L	O	R	S	####
black 				=	"[1;30m"
red 				=	"[1;31m"
green 				=	"[1;32m"
yellow 				=	"[1;33m"
blue 				=	"[1;34m"
magenta 			=	"[1;35m"
cyan 				=	"[1;36m"
white 				=	"[1;37m"
####	C	O	L	O	R	S	####

all: compile student run

compile: main.c
	@gcc main.c -o test

run: test
	@echo $(green)
	@./test
	
clean:
	@rm -f test

student:
	@echo $(yellow)
	@echo "------------------------------------------"
	@sleep 0.4
	@echo "|The homework is done by Omer Faruk Olkay|"
	@sleep 0.4
	@echo "|mail: o.olkay2021@gtu.edu.tr            |"
	@sleep 0.4
	@echo "|student number: 210104004039            |"
	@sleep 0.4
	@echo "------------------------------------------"
	@sleep 0.4
	@echo $(blue)
	@echo "Compilation is done... The program will be executed in one second"
	@echo "\n\n"
	@sleep 3
	@clear
