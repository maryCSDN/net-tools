sinclude ./include/config.mk

build:_config
	@echo "start"
	gcc srcs/clog/clog.c -c -o clog.o -I/usr/local/include/ -L/usr/local/lib/ -lzlog
	gcc clog.o -o clog  -I/usr/local/include/ -L/usr/local/lib/ -lzlog
 
