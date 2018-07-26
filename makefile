

SRCS = tests.c kdtree.c lista.c dac/closest.c dac/sorts.c
OBJS = $(SRCS:%.c=%.o)

kdtree:	$(OBJS) pontos.h
	gcc -Wall -lm -g -o $@ $(OBJS)

%.o: %.c
	gcc -c -Wall -lm -g -o $@ $<

.PHONY: remove
remove:
	rm -rf $(OBJS) kdtree