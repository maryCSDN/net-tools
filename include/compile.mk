NET_TOOLS_BIN		= net-tools
SRCS_ROOT_FDIR		= srcs
SRCS_CHILD_DIRS 	= $(shell find $(SRCS_ROOT_FDIR) -maxdepth 3 -type d) 
SRCS			   	= $(foreach DIR, $(SRCS_CHILD_DIRS), $(wildcard $(DIR)/*.c))
OBJS				= $(SRCS:.c=.o)

# compile environment
CC					= gcc
CFLAGS				+= -g -Wall -I/usr/local/include/ -I$(SRCS_ROOT_FDIR)/clog/ -I$(SRCS_ROOT_FDIR)/common/
DFLAGS				+= -L/usr/local/bin/
LIB_LINK			+= -lzlog

_compile:$(NET_TOOLS_BIN) _clear

_clear:
	rm --force $(OBJS)

$(NET_TOOLS_BIN):$(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $^ -o $@ $(LIB_LINK)


# *.c -> *.o
%.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@