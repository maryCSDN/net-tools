sinclude ./include/config.mk
sinclude ./include/compile.mk

build:pre _config _compile _clear
	@echo "End building"


pre:
	@echo "Start building..."

_clear:
	rm --force ./*.o