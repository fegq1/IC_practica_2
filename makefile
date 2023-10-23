make:
	g++ imagen.cpp -o imagen
make_O1:
	g++ imagen.cpp -o imagen -O1
make_O2:
	g++ imagen.cpp -o imagen -O2
make_O3:
	g++ imagen.cpp -o imagen -O3
make_Ofast:
	g++ imagen.cpp -o imagen -Ofast
make_Os:
	g++ imagen.cpp -o imagen -Os 
make_Og:	
	g++ imagen.cpp -o imagen -Og
run:
	./imagen 1920 1080
run_500:
	./imagen 500 500
run_1000:
	./imagen 1000 1000
run_1500:
	./imagen 1500 1500
run_2000:
	./imagen 2000 2000
run_2500:
	./imagen 2500 2500
run_3000:
	./imagen 3000 3000
run_3500:
	./imagen 3500 3500
run_4000:	
	./imagen 4000 4000
run_4500:
	./imagen 4500 4500
run_5000:	
	./imagen 5000 5000
run_5500:	
	./imagen 5500 5500
run_6000:
	./imagen 6000 6000

run_8gb: run_500 run_1000 run_1500 run_2000 run_2500 run_3000 run_3500 run_4000 

run_all: run_8gb run_4500 run_5000 run_5500 run_6000
all:
	make make_O1
	make run_all
	make make_O2
	make run_all
	make make_O3
	make run_all
	make make_Ofast
	make run_all
	make make_Os
	make run_all
	make make_Og
	make run_all

clean:
	rm imagen

