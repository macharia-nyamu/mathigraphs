# Mathigraphs

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build Status](https://img.shields.io/github/actions/workflow/status/macharia-nyamu/mathigraphs/build.yml)](https://github.com/macharia-nyamu/mathigraphs/actions)

Mathigraphs is a lightweight C project for generating and managing mathematical graphs and utilities.  
It is structured into modular components with clear separation of headers, source files, and compiled objects.  
The project is designed to be simple to build and extend.

---

## Project Structure

```bash
.
├── assets
│   ├── company.csv
│   └── examples.txt
├── headers
│   ├── bar.h
│   ├── help.h
│   ├── mathigraphs.h
│   └── starter.h
├── libmathi.a
├── Makefile
├── mathigraphs
├── mathigraphs.c
├── mathigraphs.o
├── mathi.h
├── README.md
└── src
    ├── bar.c
    ├── bar.o
    ├── help.c
    ├── help.o
    ├── starter.c
    └── starter.o
```

---

## Build Instructions

You can build Mathigraphs in two ways:

### 1. Using Makefile (recommended)

    make rebuild

This will:

* Clean old builds  
* Recompile all sources  
* Link everything into the `mathigraphs` executable  

### 2. Manual Build

If you want to compile manually:

```bash
gcc -c src/bar.c -o src/bar.o
gcc -c src/help.c -o src/help.o
gcc -c src/starter.c -o src/starter.o
ar rcs libmathi.a src/*.o
gcc mathigraphs.c libmathi.a -Iheaders -o mathigraphs
```	

---

## Running the Program

After building:

```bash
./mathigraphs
```

You can run commands interactively or pass them through a file such as `assets/examples.txt`.

---

## Example Commands

Inside `assets/examples.txt` you will find sample commands. For example:

```bash
bar file='assets/company.csv' x='year' y='salary' compute='sum' sort='x' title='Total Salaries by Year'
bar file='assets/company.csv' x='year' y='salary' compute='avg' sort='y' title='Highest Average Salary'
```

### Explanation of Parameters

- **bar** → Tells Mathigraphs to generate a bar chart.  
- **file** → Path to the CSV dataset.  
- **x** → The column name to use for the x-axis (here `year`).  
- **y** → The column name to use for the y-axis (here `salary`).  
- **compute** → The aggregation method:  
  - `sum` → Adds up all values of `y` for each `x`.  
  - `avg` → Calculates the average of `y` for each `x`.  
- **sort** → Sorts the results by a chosen key:  
  - `x` → Sort by the x-axis values.  
  - `y` → Sort by the y-axis values.  
- **title** → Custom title for the chart.  

---

## Features and Progress

### Core

* [x] Modular C code organization (`src/` + `headers/`)  
* [x] Static library (`libmathi.a`)  
* [x] Working Makefile (`make rebuild`)  
* [x] CLI entry point (`mathigraphs.c`)  
* [x] Example assets (`company.csv`, `examples.txt`)  

### Implemented Modules

* [x] bar → Handles bar graph logic  
* [x] starter → Starter/initialization routines  
* [x] help → CLI usage/help system  

### Planned / Work in Progress

* [ ] Colors in graphs (CLI output or ANSI)  
* [ ] Configurable themes  
* [ ] Extended graph types (line, scatter, etc.)  
* [ ] Interactive CLI mode  
* [ ] Export to CSV/PNG  

---

## Development Notes

* C standard: C99  
* Compiler: gcc  
* Tested on: Linux (Ubuntu/Debian environment)  

---

## Contribution

Pull requests and suggestions are welcome.  
Focus areas:

* Adding more graph types  
* Improving CLI interactivity  
* Enhancing output visualization (colors, styles)  

---

## License

This project is licensed under the [MIT License](LICENSE).