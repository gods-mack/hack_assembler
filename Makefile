
output: assembler.o pass1.o 
	g++ assembler.o pass1.o -o output



assembler.o: assembler.cpp code.h 
	g++ -c assembler.cpp

pass1.o: pass1.cpp pass1.h
	g++ -c pass1.cpp

clean:
	rm *.o output			
