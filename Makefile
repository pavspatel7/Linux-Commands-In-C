all: ls find tree

ls: ls.c
	gcc -g -fsanitize=address -o ls ls.c

find: find.c
	gcc -g -fsanitize=address -o find find.c

tree: tree.c
	gcc -g -fsanitize=address -o tree tree.c