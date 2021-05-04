RabinCrypto: RabinCrypto.o BigNumber.o ptest.o
	g++ RabinCrypto.o BigNumber.o ptest.o -o RabinCrypto
	./RabinCrypto
RabinCrypto.o: RabinCrypto.cpp BigNumber.h ptest.h
	g++ -c RabinCrypto.cpp -o RabinCrypto.o
BigNumber.o: BigNumber.cpp BigNumber.h
	g++ -c BigNumber.cpp -o BigNumber.o
ptest.o: ptest.cpp BigNumber.h ptest.h
	g++ -c ptest.cpp -o ptest.o
clean:
	rm *.o RabinCrypto
run:
	./RabinCrypto