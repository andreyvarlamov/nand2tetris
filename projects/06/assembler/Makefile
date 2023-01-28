build/assembler: build input output build/Assembler.o build/Parser.o
	g++ -o build/assembler build/Assembler.o build/Parser.o build/SyntaxError.o -std=c++20 -g -pedantic-errors -Wall -Weffc++ -Wsign-conversion -Wextra -Werror

build/Assembler.o: Assembler.cpp Instruction.h SyntaxError.h
	g++ -o build/Assembler.o -c Assembler.cpp

build/Parser.o: Parser.cpp Parser.h Instruction.h SyntaxError.h
	g++ -o build/Parser.o -c Parser.cpp

build:
	@mkdir build

input:
	$(error No input folder)

output:
	@mkdir output

.PHONY: run
run: build/assembler
	@build/assembler $(ARGS)

.PHONY: clean
clean:
	@rm -r build
