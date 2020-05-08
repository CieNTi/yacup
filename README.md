# yacup: Yet Another C Utilities Package

## Brief

Set of utilities ready to be used in C projects. Originally located at [GitHub](https://github.com/CieNTi/yacup).

## Folder/File organization

The file arrangement selected for this project tries to met various topics:

- Each util will only depend on itself or some other util, but not higher level code in this project (so a module can depend on another, but not on code contained in `src` folder). This allows to freely include the utils in any other software.
- As an standalone entity, but belonging to a project, each module will self-contain all the required files and headers, but headers will be inside a `yacup` folder. Module 1st level header will be there so `#include "yacup/mod_ab.h"` will work, but any other header purely related with the module, will be available inside a subfolder in a way that `#include "yacup/mod_ab/something.h"`
- Looking from a project point of view, each util and dependencies will be found without a problem (still needed to check wheter it fails or not when a module depends on another, building it from the module folder).

The following text block summarizes how the files are arranged inside this folder/repository:

```
├── .gitignore
├── Doxyfile
├── LICENSE
├── Makefile
├── README.md
├── yacup.sublime-project
├── util/
│   ├── mod_ab/
│   │   ├── file_a.c
│   │   ├── file_b.c
│   │   ├── yacup/
│   │   │   ├── mod_ab.h
│   │   │   └── mod_ab/
│   │   │       ├── file_a.h
│   │   │       ├── file_b.h
│   │   │       └── types.h
│   │   ├── private.h
│   │   └── tests/
│   │       ├── test_ab_a.c
│   │       └── test_ab_b.c
│   └── mod_xy/
│       ├── file_x.c
│       ├── file_y.c
│       ├── yacup/
│       │   ├── mod_xy.h
│       │   └── mod_xy/
│       │       ├── file_x.h
│       │       ├── file_y.h
│       │       └── types.h
│       ├── private.h
│       └── tests/
│           ├── test_ab_x.c
│           └── test_ab_y.c
├── src/
│   ├── yacup/
│   │   ├── include_1.h
│   │   └── include_2.h
│   └── main.c
└── out/
    ├── bin/
    ├── lib/
    └── obj/
```

## Installation

```bash
$ echo "Still need an explanation of this :D"
```

## Usage

```bash
$ echo "Still need an explanation of this :D"
```

## Documentation

Online version of Doxygen-generated documentation can be found at [GitHub Pages](https://cienti.github.io/yacup/).

## Credits

- [CieNTi](https://github.com/CieNTi): `yacup`
