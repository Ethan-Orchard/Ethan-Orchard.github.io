all:
	echo c++ -I/Library/Frameworks/SDL2.framework/Headers -ofec main.cpp -framework SDL2
	c++ -Icontrib/mac/include -ofec *.cpp -Lcontrib/mac/lib -lSDL2 -lSDL2_image
	sh embuild.sh
