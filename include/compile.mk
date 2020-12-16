# net-tools 
NET_TOOLS_BIN		= net-tools
SRCS_ROOT_FDIR		= srcs
SRCS_CHILD_DIRS 	= $(shell find $(SRCS_ROOT_FDIR) -maxdepth 3 -type d) 
SRCS			   	= $(foreach DIR, $(SRCS_CHILD_DIRS), $(wildcard $(DIR)/*.c))
OBJS				= $(SRCS:.c=.o)

# opensource extern file directory
OPENSOURCE			= opensource
OPENSOURCE_IMPORT	= /usr/local


# compile environment
CC					= gcc
CFLAGS				+= -g -Wall -I$(OPENSOURCE_IMPORT)/include/ -I$(SRCS_ROOT_FDIR)/clog/ -I$(SRCS_ROOT_FDIR)/common/
DFLAGS				+= -L$(OPENSOURCE_IMPORT)/lib/
LIB_LINK			+= -lzlog


# opensource install (zlog)
_install_opensource:
	cd $(OPENSOURCE)/zlog && $(MAKE) PREFIX=/usr/local install

# opensource clear
_clear_opensource:
	cd $(OPENSOURCE)/zlog && $(MAKE) clean

# enter
_compile:_clear_opensource _install_opensource $(NET_TOOLS_BIN) _clear
	cp -a $(NET_TOOLS_BIN) /usr/local/bin/

# clear
_clear:_clear_opensource
	rm --force $(OBJS)

$(NET_TOOLS_BIN):$(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $^ -o $@ $(LIB_LINK)

# *.c -> *.o
%.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@