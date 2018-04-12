TARGETS = serial openmp

all:	$(TARGETS)

 
openmp: TSPGAOpenmp.cpp
	g++ -std=c++11 -o $@ TSPGAOpenmp.cpp -fopenmp

serial: TSPGASerial.cpp
	g++ -std=c++11 -o $@ TSPGASerial.cpp
clean: 
	rm serial openmp
