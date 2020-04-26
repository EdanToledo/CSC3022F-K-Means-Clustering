EXECUTABLE_NAME=clusterer
PROGRAM_Driver=clustererDriver
PREFILE1=Clusterer
PREFILE2=Cluster
PREFILE3=ImageFeature



CC=g++
COMPILE=-c -o
LINK=-o

FLAGS=-std=c++11 -g

$(PROGRAM_Driver): $(PROGRAM_Driver).o
	$(CC) $(FLAGS) $(LINK) $(EXECUTABLE_NAME) $(PROGRAM_Driver).o $(PREFILE1).o $(PREFILE2).o $(PREFILE3).o

$(PROGRAM_Driver).o: $(PREFILE1).o $(PREFILE1).h $(PREFILE2).o $(PREFILE2).h $(PREFILE3).o $(PREFILE3).h
	$(CC) $(FLAGS) $(COMPILE) $(PROGRAM_Driver).o $(PROGRAM_Driver).cpp

$(PREFILE1).o: $(PREFILE1).h $(PREFILE2).o $(PREFILE2).h $(PREFILE3).o $(PREFILE3).h
	$(CC) $(FLAGS) $(COMPILE) $(PREFILE1).o $(PREFILE1).cpp

$(PREFILE2).o: $(PREFILE2).h $(PREFILE3).o $(PREFILE3).h
	$(CC) $(FLAGS) $(COMPILE) $(PREFILE2).o $(PREFILE2).cpp

$(PREFILE3).o: $(PREFILE3).h
	$(CC) $(FLAGS) $(COMPILE) $(PREFILE3).o $(PREFILE3).cpp

clean:
	rm -f *.o
	rm -f $(EXECUTABLE_NAME)
