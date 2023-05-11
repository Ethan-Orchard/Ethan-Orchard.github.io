echo hello
source ~/emsdk/emsdk_env.sh
em++ -Icontrib/emscripten/include -ofec.html *.cpp -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets