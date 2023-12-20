program:
	clang++ thing.cpp location.cpp colour.cpp area.cpp button.cpp window.cpp log.cpp image.cpp -lSDL2 -lSDL2_image -Wno-writable-strings -Wno-switch -Wno-sizeof-pointer-div -Wno-return-stack-address
	./a.out -x 1920 -y 1080 -o ./test.png