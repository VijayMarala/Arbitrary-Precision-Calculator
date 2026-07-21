var:=$(patsubst %.c, %.o, $(wildcard *.c))
apc.out:$(var)
	gcc -o apc.out $(var)
clean:
	rm *.out *.o
