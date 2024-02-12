Question5: bin/Question5

Question7: bin/Question7

bin/Question5: bin/func.o bin/Question2.o bin/Question3.o bin/Question4.o bin/Question5.o
	g++ bin/func.o bin/Question2.o bin/Question3.o bin/Question4.o bin/Question5.o -o bin/Question5 -g

bin/Question7: bin/func.o bin/Question2.o bin/Question3.o bin/Question4.o bin/Question5.o bin/Question6.o bin/Question7.o
	g++ -L/lib bin/func.o bin/Question2.o bin/Question3.o bin/Question4.o bin/Question5.o bin/Question6.o bin/Question7.o -o bin/Question7 -g -l:libglpk.a

bin/func.o: src/func.cpp
	g++ src/func.cpp -c -o bin/func.o -g

bin/Question2.o: src/Question2.cpp
	g++ src/Question2.cpp -c -o bin/Question2.o -g

bin/Question3.o: src/Question3.cpp
	g++ src/Question3.cpp -c -o bin/Question3.o -g

bin/Question4.o: src/Question4.cpp
	g++ src/Question4.cpp -c -o bin/Question4.o -g

bin/Question5.o: src/Question5.cpp
	g++ src/Question5.cpp -c -o bin/Question5.o -g

bin/Question6.o: src/Question6.cpp
	g++ src/Question6.cpp -c -o bin/Question6.o -g

bin/Question7.o: src/Question7.cpp
	g++ -I/lib src/Question7.cpp -c -o bin/Question7.o -g

bin/Question8.o: src/Question8.cpp
	g++ src/Question8.cpp -c -o bin/Question8.o -g

bin/Question9.o: src/Question9.cpp
	g++ src/Question9.cpp -c -o bin/Question9.o -g

bin/Question10.o: src/Question10.cpp
	g++ src/Question10.cpp -c -o bin/Question10.o -g

bin/Question11.o: src/Question11.cpp
	g++ src/Question11.cpp -c -o bin/Question11.o -g

bin/Question12.o: src/Question12.cpp
	g++ src/Question12.cpp -c -o bin/Question12.o -g

bin/Question13.o: src/Question13.cpp
	g++ src/Question13.cpp -c -o bin/Question13.o -g

clear:
	rm -rf bin
	mkdir bin