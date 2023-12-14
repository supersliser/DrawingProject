program:
	clang++ thing.cpp location.cpp colour.cpp area.cpp button.cpp window.cpp log.cpp image.cpp -lSDL2 -lSDL2_image -Wno-writable-strings -Wno-switch
	./a.out