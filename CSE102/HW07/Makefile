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


all: student compile


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
	@echo "\n"
	@echo $(red)
	@echo "!!!!!!!WARNING!!!!!!!"
	@echo "run the program as ./test word1 word2 word3"
	@echo "\n\n"

compile:
	@gcc main.c utils.c -lm -o test

clean:
	@rm -f test
	
