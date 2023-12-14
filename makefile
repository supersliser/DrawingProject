program:
	clang++ thing.cpp location.cpp colour.cpp area.cpp button.cpp window.cpp log.cpp image.cpp -lSDL2 -lSDL2_image -Wno-writable-strings -Wno-switch -Wno-sizeof-pointer-div
	./a.out 1920 1080 /home/s5605187/DrawingProject/Lenna.png