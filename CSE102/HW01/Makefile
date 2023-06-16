all: student clean compile run 

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "!! You need to give input on each part !!"
	@sleep 0.5
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

compile: main.c utils.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc main.c utils.c -o test
	@echo "Succesfully Compiled..."
	@echo "-------------------------------------------"
	@sleep 1

student:
	@echo "------------------------------------------"
	@echo "|The homework is done by Omer Faruk Olkay|"
	@echo "|mail: o.olkay2021@gtu.edu.tr            |"
	@echo "|student number: 210104004039            |"
	@echo "------------------------------------------"
	@sleep 1

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
	@sleep 1
	@echo "Succesfully Cleaned"
	@echo "-------------------------------------------"
	@sleep 1
