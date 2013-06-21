include config.mk

SRC = ext/array.c ext/buffer.c ext/markdown.c ext/renderers.c luasoldout.c
OBJ = ${SRC:.c=.o}

all: soldout.so

.c.o:
	${CC} -c -o $@ ${CFLAGS} $<

${OBJ}: config.mk

soldout.so: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f soldout.so ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/lib/lua/${LUA}
	cp -f soldout.so ${DESTDIR}${PREFIX}/lib/lua/${LUA}/

.PHONY: all clean install
