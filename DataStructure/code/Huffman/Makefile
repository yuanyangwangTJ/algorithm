
output: main.o Huffman.o Operate.o
	g++ main.o Huffman.o Operate.o -o output

main.o: main.cpp
	g++ -c main.cpp

Huffman.o: Huffman.cpp Huffman.h 
	g++ -c Huffman.cpp

Operate.o: Operate.cpp Operate.h 
	g++ -c Operate.cpp
	
clean:
	rm *.o output