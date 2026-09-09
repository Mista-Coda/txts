INSTALLPATH = /bin/txts

.PHONY: install uninstall clean

txts: main.o stringview.o
	cc main.o stringview.o -Wall -Wextra -o txts

install: txts
	install -Dm755 txts $(INSTALLPATH)

uninstall:
	rm -f $(INSTALLPATH)

clean:
	rm -f main.o
	rm -f stringview.o
	rm -f ./txts

main.o: src/main.c
	cc src/main.c -Wall -Wextra -c -o main.o

stringview.o: src/stringView.c src/stringView.h
	cc src/stringView.c -Wall -Wextra -c -o stringview.o