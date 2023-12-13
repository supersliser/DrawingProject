program:
	clang++ thing.cpp location.cpp colour.cpp area.cpp button.cpp window.cpp log.cpp -lSDL2 -Wno-writable-strings -Wno-switch
	./a.out 1280 860