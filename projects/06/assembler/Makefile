build/assembler: build input output build/Assembler.o build/Parse.o build/Translate.o build/FileIO.o build/Preprocess.o
	g++ -o build/assembler build/Assembler.o build/Parse.o build/Translate.o build/FileIO.o build/Preprocess.o -std=c++20 -g -pedantic-errors -Wall -Weffc++ -Wsign-conversion -Wextra -Werror

build/Assembler.o: Assembler.cpp Instruction.h SyntaxError.h CodeLine.h
	g++ -o build/Assembler.o -c Assembler.cpp

build/Parse.o: Parse.cpp Parse.h Instruction.h SyntaxError.h CodeLine.h
	g++ -o build/Parse.o -c Parse.cpp

build/Translate.o: Translate.cpp Translate.h Instruction.h SyntaxError.h
	g++ -o build/Translate.o -c Translate.cpp

build/FileIO.o: FileIO.cpp FileIO.h CodeLine.h
	g++ -o build/FileIO.o -c FileIO.cpp

build/Preprocess.o: Preprocess.cpp Preprocess.h CodeLine.h
	g++ -o build/Preprocess.o -c Preprocess.cpp

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
