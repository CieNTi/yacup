# yacup: Yet Another C Utilities Package

Set of utilities ready to be used in C projects. Originally located at [GitHub](https://github.com/CieNTi/yacup).

## Getting Started

These instructions make you build the project and/or its utilities successfully.

### Prerequisites

```bash
$ echo "Still need an explanation of this :D"
```

### Installation

```bash
$ echo "Still need an explanation of this :D"
```

## Usage

```bash
$ echo "Still need an explanation of this :D"
```

## Development

The following information will try to tie everything up in order to make it clear how the things works.

### Documentation

Online version of Doxygen-generated documentation can be found at this [yacup GitHub Pages](https://cienti.github.io/yacup/).

It is generated automatically by using the following GitHub actions:

- [mattnotmitt/doxygen-action](https://github.com/marketplace/actions/doxygen-action)
- [peaceiris/actions-gh-pages](https://github.com/marketplace/actions/github-pages-action)

### How folders and files are organized

The file arrangement selected for this project tries to met various topics:

- Each util will only depend on itself or some other util, but not higher level code in this project. Ex.: A module can depend on another, but not on code contained in `src` folder.
    - This allows to freely include the utils in any other software.
- As an standalone entity, but belonging to a project, each module will self-contain all the required files and headers, but headers will be inside a `yacup` folder.
    - Module 1st level header will be there so `#include "yacup/mod_ab.h"` will work
    - Any other header purely related with the module, will be available inside a subfolder in a way that `#include "yacup/mod_ab/something.h"` works
- Looking from a project point of view, each util and dependencies will be found without a problem (*still needed to check wheter it fails or not when a module depends on another, building it from the module folder*).
- A set of template files are provided as a template/guideline for future files, fully Doxygened and ready to work

The following text block summarizes how the files are arranged inside this folder/repository:

```
├── .gitignore
├── Doxyfile
├── LICENSE.txt
├── Makefile
├── README.md
├── yacup.sublime-project
├── template/
│   ├── source.c
│   └── header.h
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
├── out/
│   ├── bin/
│   ├── lib/
│   └── obj/
└── .github/
    └── workflows/
        └── make-and-doxygen.yml
```

### Running the tests

```bash
$ echo "Still need an explanation of this :D"
```

## Built using

- [GNU Make](https://www.gnu.org/software/make/)
- [Doxygen](http://www.doxygen.nl/)
- [GitHub](https://github.com/)
- [GitHub Pages](https://pages.github.com/)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/CieNTi/yacup/tags). 

## Authors

- **CieNTi** - *Initial work* - [CieNTi](https://github.com/CieNTi)

## License

This project is licensed under the AGPL-3.0 License:

```
 README.md - README for yacup project
 Copyright (C) 2020 CieNTi <cienti@cienti.com>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.
 
 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
```

See the [LICENSE.txt](LICENSE.txt) file for full details.
