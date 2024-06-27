CC=gcc
CFLAGS=-Wall -Wextra

traceroute: 
	$(CC) $(CFLAGS) -c traceroute.c # tymczasowy plik .o
	${CC} -o traceroute traceroute.o # wykonywalny
	

clean:
	rm -f *.o

distclean: clean
	rm -f traceroute
