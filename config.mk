# lua version
LUA = 5.2

# paths
PREFIX = /usr/local

LUAINC = -I/usr/local/include -I/usr/local/include/lua-${LUA}
LUALIB = -L/usr/local/lib

# flags
CFLAGS = -fPIC -Wall -Os ${LUAINC}
LDFLAGS = -shared ${LUALIB}

# compiler and linker
CC = cc
