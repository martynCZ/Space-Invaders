# SPACE INVADERS
Jednoduchá klasická hra **Space Invaders** v jazyce C s využitím knihovny SDL2.
Hra obsahuje menu, počítání skóre a životů, ničitelné bunkry, různé typy nepřátel.

## SESTAVENÍ A SPUŠTĚNÍ PROGRAMU

### 1. Instalace knihoven
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

### 2. Sestavení projektu
V kořenové složce projektu (tam, kde je **main.c a CMakeLists.txt**) zadejte tyto příkazy:
```bash
mkdir build
cd build
cmake ..
make
```
### 3. Spuštění projektu
Aby hra správně načetla obrázky a fonty ze složky src/, musíte ji spouštět z hlavní složky projektu.
```bash
cd ..
./build/game
```


