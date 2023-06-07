compile:
	clang++ -o gen/spelunkie src/**.c++ -lSDL -lSDL2
run:
	gen/spelunkie