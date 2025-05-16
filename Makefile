aod:aod.cpp util.hpp data.hpp server.hpp
	g++ -std=c++11 $^ -o $@ -L/usr/lib64/mysql -ljsoncpp -lmysqlclient -lpthread

.PHONY: clean run db_init install

clean:
	rm -f aod *.o

run:
	./aod

db_init:
	chmod +x setup_db.sh
	./setup_db.sh

install:
	mkdir -p ./www/video ./www/image
	$(MAKE) db_init
