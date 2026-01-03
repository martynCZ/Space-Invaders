# SPACE INVADERS v C/SDL2
Jednoduchá klasická hra **Space Invaders** v jazyce C s využitím knihovny SDL2.
Hra obsahuje menu, počítání skóre a životů, ničitelné bunkry, různé typy nepřátel.

## POUŽITÉ TECHNOLOGIE

### JAZYK
C
### Knihovny
#### SDL2
```bash
Vytvoření okna, vykreslování, zpracování vstupů, vypisování textů, načítání a renderování textur obrázků ve formátu PNG
```

## OVLÁDÁNÍ
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
## PRINCIP FUNGOVÁNÍ A STRUKTURA
### 1. Struktura
```bash
Space-Invaders/
├── build/                 # Kompilace (vytvoří se přes cmake)
├── src/                   # Složka s obrázky a fonty
│   ├── player.png
│   ├── enemy01.png
│   ├── space-invaders.ttf
│   └── ...
├── CMakeLists.txt         # Konfigurace pro CMake
├── main.c                 # Hlavní smyčka a menu
├── game.c                 # Logika hry
├── game.h                 # Hlavičkový soubor hry
├── end.c                  # Obrazovka konce hry
├── end.h                  # Hlavičkový soubor konce
└── README.md              # Tento soubor
```

