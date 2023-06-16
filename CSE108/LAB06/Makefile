all: part1 part2 run

part1: part1.c
	gcc part1.c -o part1

part2: part2.c
	gcc part2.c -o part2

run: part1 part2
	@./part1
	@echo "\n\n"
	@./part2

clean:
	rm -f part1
	rm -f part2