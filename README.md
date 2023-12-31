# Galois Field

## Software requirements
CMake and at least C++17 

## Overview
Implementation of the Galois field GF(2^293) in a polynomial basis using a polynomial generator: x^293 + x^11 + x^6 + x^1 + 1

## Features
- **Adding operation**
- **Multiplication operation**
- **Trace calculation**
- **Inverse calculation**
- **Power calculation**
- **Square calculation**

## Build and Usage

Follow these steps to build and run:

1. Clone the GaloisField repository to your local machine:
```bash
https://github.com/avept/GaloisField.git
```

2. Navigate to the project directory:
```bash 
cd GaloisField
```

3. Create a build directory:
```bash
mkdir build
cd build
```
   
4. Generate the build system using CMake:
```bash
cmake ..
```

5. Build the library:
```bash
make -j4
```
