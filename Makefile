BIN	= dstring
SRC	= $(BIN).c
MAN	= $(BIN).1

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

CC	= cc
CFLAGS	= -std=c99 -pedantic -Wall -Wextra -Werror -O2

all: $(BIN)

$(BIN):
	$(CC) -o $@ $(SRC)

clean:
	rm -f $(BIN)

install: $(BIN)
	install -m0755 $(BIN) $(BINDIR)
	install -m0644 $(MAN) $(MANDIR)

uninstall:
	rm -f $(BINDIR)/$(BIN)
	rm -f $(MANDIR)/$(MAN)

.PHONY: all clean install uninstall
