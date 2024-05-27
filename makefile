all :build

build:
	g++ *.cpp -O2 -g -o main -Wall -Wextra -Werror

dbg:
	g++ *.cpp -O0 -g -o dbg -Wall -Wextra -Werror

run: build
	./main