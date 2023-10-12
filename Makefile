
obj = ${patsubst %.c, %.o, ${wildcard *.c}}
%.o : %.c
	gcc -I. $? -c -o $@

all : $(obj)
	gcc $(obj) -o main
list.o : list.h
	gcc -I. list.c list.h -c
list.a(list.o) : list.o
	ar -r 

.PHONY: clean
clean :
	rm -fr main $(obj) *.gch