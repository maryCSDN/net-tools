sinclude ./include/config.mk
sinclude ./include/compile.mk

build:pre _config _compile
	@echo "End building"

pre:
	@echo "Start building..."

clean:
	rm $(NET_TOOLS_BIN)
