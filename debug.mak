project_debug: user_interface_debug.o llist_debug.o
	g++ -o project_debug user_interface_debug.o llist_debug.o

llist_debug.o: llist.cpp record.h llist.h
	g++ -ansi -pedantic-errors -Wall -o llist_debug.o -DDEBUG -c llist.cpp

user_interface_debug.o: user_interface.cpp record.h llist.h
	g++ -ansi -pedantic-errors -Wall -o user_interface_debug.o -DDEBUG -c user_interface.cpp
