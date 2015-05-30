hw6: hw6.o tablecheck.o modprod.o keyexpand.o encrypt.o decrypt.o inverse.o utilities.o
	gcc -g -Wall hw6.o tablecheck.o modprod.o keyexpand.o encrypt.o decrypt.o inverse.o utilities.o -o hw6

hw6.o: hw6.c
	gcc -g -Wall -c hw6.c

tablecheck.o: tablecheck.c
	gcc -g -Wall -c tablecheck.c

modprod.o: modprod.c
	gcc -g -Wall -c modprod.c

keyexpand.o: keyexpand.c
	gcc -g -Wall -c keyexpand.c

encrypt.o: encrypt.c
	gcc -g -Wall -c encrypt.c

decrypt.o: decrypt.c
	gcc -g -Wall -c decrypt.c

inverse.o: inverse.c
	gcc -g -Wall -c inverse.c

utilities.o: utilities.c
	gcc -g -Wall -c utilities.c

clean:
	rm -f *.o hw6
