txts: main.o stringview.o
	cc main.o stringview.o -Wall -Wextra -o txts

main.o: src/main.c
	cc src/main.c -Wall -Wextra -c -o main.o

stringview.o: src/stringView.c src/stringView.h
	cc src/stringView.c -Wall -Wextra -c -o stringview.o