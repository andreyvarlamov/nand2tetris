build/assembler: build main.cpp
	g++ -o build/assembler main.cpp -std=c++20 -g -pedantic-errors -Wall -Weffc++ -Wsign-conversion -Wextra -Werror

build:
	@mkdir build

.PHONY: run
run: build/assembler
	@build/assembler

.PHONY: clean
clean:
	@rm -r build
