
# MakeFile for restChat
# server using C++ Microservice
# sudo mkdir /var/www/html/restChatDB
# sudo chown ubuntu /var/www/html/restChatDB
CC=g++
CFLAGS= -std=c++17 -Wno-deprecated-declarations
RM= /bin/rm -f

all: restChat PutHTML

restEntry.o: restEntry.cpp restEntry.h
	$(CC) -c $(CFLAGS) restEntry.cpp

restDB.o: restDB.cpp restDB.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn chatDB.cpp



restChat.o: restChat.cpp httplib.h
	$(CC) -c $(CFLAGS) restChat.cpp 

restChat: restChat.o chatDB.o chatEntry.o 
	$(CC) restChat.o chatDB.o chatEntry.o -o restChat -L/usr/local/lib -lmariadbcpp
PutHTML:
	cp restChat.html /var/www/html/chatDB/
	cp restChat.css /var/www/html/chatDB/
	cp restChat.js /var/www/html/chatDB/

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/chatDB/

clean:
	rm restChat *.o
