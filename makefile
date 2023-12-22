program:
	clang++ thing.cpp location.cpp colour.cpp area.cpp button.cpp window.cpp log.cpp image.cpp -lSDL2 -lSDL2_image -Wno-writable-strings -Wno-switch -Wno-sizeof-pointer-div -Wno-return-stack-address
	./a.out -x 800 -y 800 -i ./Lenna.png -o ./test.png