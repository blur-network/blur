PREFIX ?= /usr/local
WFLAGS ?= -Wall -Wextra -Wmissing-prototypes -Wdiv-by-zero -Wbad-function-cast -Wcast-align -Wcast-qual -Wfloat-equal -Wmissing-declarations -Wnested-externs -Wno-unknown-pragmas -Wpointer-arith -Wredundant-decls -Wstrict-prototypes -Wswitch-enum -Wno-type-limits
CFLAGS ?= -Os -march=native -fno-exceptions $(WFLAGS)
CFLAGS += -I.
OBJ = bitcoin.o
AR ?= ar
RANLIB ?= ranlib

SRC = \
	src/arith_uint256.cpp \
	src/arith_uint256.h \
	src/attributes.h \
        src/base58.cpp \
	src/base58.h \
	src/strencodings.cpp \
	src/strencodings.h \
	src/tinyformat.h \
	src/uint256.cpp \
        src/uint256.h

all: lib

lib: libbitcoin.a

install: lib
	mkdir -p $(PREFIX)/lib
	install -o 0 -g 0 -m 0755 libbitcoin.a $(PREFIX)/lib 2> /dev/null || install -m 0755 libbitcoin.a $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	install -o 0 -g 0 -m 0644 bitcoin.h $(PREFIX)/include 2> /dev/null || install -m 0644 bitcoin.h $(PREFIX)/include
	ldconfig 2> /dev/null || true

uninstall:
	rm -f $(PREFIX)/lib/libbitcoin.a
	rm -f $(PREFIX)/include/bitcoin.h

$(OBJ): $(SRC)

libbitcoin.a: $(OBJ)
	$(AR) -r $@ $^
	$(RANLIB) $@

.PHONY: clean

clean:
	rm -rf libbitcoin.a $(OBJ) CMakeCache.txt CMakeFiles bitcoin-config.cmake bitcoin-targets.cmake bitcoin.o

distclean: clean
