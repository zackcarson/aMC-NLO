# Kacey Price krp9da
# Prelab 6
# Lab 2pm

CXX=clang++ -O2
OFILES = hashTable.o timer.o wordPuzzle.o

.SUFFIXES: .o .cpp

a.out: $(OFILES)
	$(CXX) $(OFILES) -o a.out

clean:
	-rm *.o a.out *~

hashTable.o: hashTable.cpp hashTable.h
timer.o: timer.cpp timer.h
wordPuzzle.o: wordPuzzle.cpp hashTable.h timer.h
