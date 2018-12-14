 CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

all: main.o Textparsing.o linkedlist.o buildrepr.o buildgraph.o progexe.o
	$(CC) -g -o $(EXE) main.o Textparsing.o linkedlist.o buildrepr.o buildgraph.o progexe.o

main.o: main.c Textparsing.h linkedlist.h buildrepr.h buildgraph.h progexe.h
	$(CC) -g $(WARNING_FLAGS) -c main.c

buildgraph.o: buildgraph.c buildgraph.h linkedlist.h buildrepr.h
	$(CC) -g $(WARNING_FLAGS) -c buildgraph.c

buildrepr.o: buildrepr.c buildrepr.h linkedlist.h Textparsing.h
	$(CC) -g $(WARNING_FLAGS) -c buildrepr.c

Textparsing.o: Textparsing.c Textparsing.h
	$(CC) -g $(WARNING_FLAGS) -c Textparsing.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) -g $(WARNING_FLAGS) -c linkedlist.c

progexe.o: progexe.c progexe.h linkedlist.h buildrepr.h
	$(CC) -g $(WARNING_FLAGS) -c progexe.c

clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
