# SPACE INVADERS v C/SDL2
Jednoduchá klasická hra **Space Invaders** v jazyce C s využitím knihovny SDL2.
Hra obsahuje menu, počítání skóre a životů, ničitelné bunkry, různé typy nepřátel.

## POUŽITÉ TECHNOLOGIE

### JAZYK
C
### Knihovny
#### SDL2
Vytvoření okna, vykreslování, zpracování vstupů, vypisování textů, načítání a renderování textur obrázků ve formátu PNG

## Ovládání
```bash
Šipka doprava: Pohyb vpravo
Šipka doleva: Pohyb vlevo
Spacebar: Střelba
Escape: Ukončení hry
Enter: Restart hry po konci
```

## SESTAVENÍ A SPUŠTĚNÍ PROGRAMU (Linux)
Pro snadné spuštění a sestavení lze použít CMake
### 1. Instalace knihoven
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

### 2. Sestavení projektu
V kořenové složce projektu (tam, kde je **main.c a CMakeLists.txt**) zadejte tyto příkazy:
```bash
1. vytvoření složky a přechod do ní
mkdir build
cd build

2. spuštění CMake inicializace a sestavení projektu
cmake ..
make
```
### 3. Spuštění projektu
Aby hra správně načetla obrázky a fonty ze složky src/, musíte ji spouštět z hlavní složky projektu.
```bash
cd ..
./build/game
```


