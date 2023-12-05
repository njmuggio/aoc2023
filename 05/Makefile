a: a.c
	gcc -ggdb3 a.c -o a
b: b.c
	gcc -ggdb3 b.c -o b
b-fast: b.c
	gcc -O3 -march=native -o b-fast b.c
