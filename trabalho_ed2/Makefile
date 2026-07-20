CC = gcc
CFLAGS = -Wall -O2

FONTES = $(wildcard q*.c)
BINARIOS = $(FONTES:.c=)

all: $(BINARIOS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	@for prog in $(BINARIOS); do \
		echo "==================== $$prog ===================="; \
		./$$prog; \
		echo; \
	done

clean:
	rm -f $(BINARIOS)

.PHONY: all run clean
