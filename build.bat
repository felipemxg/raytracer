@echo off

clang++ -g -DWITH_AVX -march=native -Lextlibs -o raytracer.exe  -lSDL2main -lSDL2 -lUser32 -lShell32 src/main.cpp -Xlinker /subsystem:console
