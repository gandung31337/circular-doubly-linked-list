all:
	gcc -D CONFIG_PRINT_NODE -o list list.c
clean:
	rm -f list
