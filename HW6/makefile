CXX=g++
CXXFLAGS=-g -Wall -std=c++11
CXXLINK=$(CXX)
CLASSOBJS=ip.o port.o string.o
LIBRARYS_MAIN=main.o libfirewall.so libinput.so
EXE=firewall.exe
RM=rm -rf

$(EXE): $(LIBRARYS_MAIN)
	$(CXXLINK) $(CXXFLAGS) $(LIBRARYS_MAIN) -o $(EXE) -lfirewall -linput -L.

libfirewall.so: $(CLASSOBJS)
	$(CXX) $(CXXFLAGS) -shared $(CLASSOBJS) -o libfirewall.so -L.
	
main.o: main.cpp ip.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

ip.o: ip.cpp ip.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp
	
port.o: port.cpp port.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp
	
string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

clean:
	$(RM) *.o libfirewall.so