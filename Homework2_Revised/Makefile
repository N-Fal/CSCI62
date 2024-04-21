COMP=g++
FLAGS=-std=c++11
output: social_network.o user.o network.o
	$(COMP) $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	rm *.o output