build/assembler: build input output Assembler.cpp Parser.cpp
	g++ -o build/assembler Assembler.cpp Parser.cpp -std=c++20 -g -pedantic-errors -Wall -Weffc++ -Wsign-conversion -Wextra -Werror

build:
	@mkdir build

input:
	$(error No input folder)

output:
	@mkdir output

.PHONY: run
run: build/assembler
	@build/assembler

.PHONY: clean
clean:
	@rm -r build
