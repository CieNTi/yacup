# Yet Another C Utilities Package

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
│   │   └── test/
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
│       └── test/
│           ├── test_ab_x.c
│           └── test_ab_y.c
├── src/
│   ├── test/
│   │   └── test_some.c
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

The provided `Makefile` is designed in a way that creating and executing test will be easy.

#### Create tests: Coding the sources

In order to take advantage of our `Makefile` features:

- Source file have to be named like the test, ex: `test_about_something.c`
- A function named like the test have to be defined inside the source file, and have to follow the same structure than a common `main()`, ex: `int test_about_something(int argc, const char* argv[])`. This will be valid as a `main()` at the very end of the building process, without any extra user intervention (it is further explained).
- This function will return `0` for success and any other value for error
- Test name have to be unique, therefore, both file and function names have to be unique along the project, as at some point it will converge in a single call if a tests batch is executed.
- Location of this file depends on the user, but following the file arrangement proposed, it should be one of the following:
    - For a utility test: `util/util_name/test/test_about_something.c`
    - For a project app test: `src/test/test_about_something.c`

All of this is summarized in the following project app test example:

> **File**: `src/test/test_about_something.c`

```c
#include <stdio.h>

/**
 * @brief      The main of the mains
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 *
 * @ingroup    app_test
 * @version    v1.0.0
 */
int test_about_something(int argc, const char* argv[])
{
  printf("Hi! from "__FILE__"\n");
  return 0;
}
```

Once this file is correctly created and defined, it is time to declare the test inside the `Makefile`.

#### Declare tests: Changing the `Makefile`

The provided `Makefile` contains a set of targets and *phony* targets to ease the development process without the need of tweaking too much the compiling process.

The developer will only have to define a target recipe as described below, adjusting the test name and object prerequisites (simply by replacing the `.c` extension with `.o`). It is recommended to follow both the proposed encoding and the location, as this is how it was shown to work perfectly.

Assuming the previous `test_about_something` example, would be as follows for an utility test:

```Makefile
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'util' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Test to check `util_name` driver_v1 functionality
test_about_something_objs=util/util_name/test/test_about_something.o
test_about_something: $(addprefix $(ODIR)/, $(test_about_something_objs))
    @echo "-----"
    @make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
    @echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

Or, as stated previously, for a project app test:

```Makefile
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'src' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Test to check some app functionality
test_about_something_objs=src/test/test_about_something.o
test_about_something: $(addprefix $(ODIR)/, $(test_about_something_objs))
    @echo "-----"
    @make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
    @echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

#### Preparing the building environment

Two targets are provided for that purpose: `make clean` and `make prepare`.

The following output is obtained if we execute both in a single call:

```bash
$ make clean prepare
-----
Cleaning environment ...
rm -rf *~ /yacup/out/bin /yacup/out/lib /yacup/out/obj /yacup/out /yacup/util/util_name/yacup/*~
-----
-----
Preparing environment ...
Creating | '/yacup/out/bin'
         | '/yacup/out/lib'
         | '/yacup/out/obj'
-----
```

#### Debugging `make` calls

A debugging target is also provided, just to show what `make` sees at execution time, and shows as follows:

```bash
$ make debug
-----
Variables:
  MFDIR ....: /yacup
  IDIR .....: /yacup/util/util_name/yacup
  SDIR .....: /yacup
  BDIR .....: /yacup/out/bin
  LDIR .....: /yacup/out/lib
  ODIR .....: /yacup/out/obj
  MKDIR ....: mkdir
  LS .......: ls -al
  CP .......: cp
  RM .......: rm -rf
  CC .......: gcc
  CFLAGS ...: -I/yacup/util/util_name/yacup -Wall -pedantic-errors -DYACUP_DEBUG
  LDLIBS ...: -lm
-----
```

#### Execute tests: Command line and CI/CD

The previously created tests already include an execution step, so calling them will triggers compile, link and execution tasks.

Assuming the proposed example, if `make test_about_something` is executed, the following output is shown:

```bash
$ make test_about_something
-----
Compiling | << /yacup/util/util_name/test/test_about_something.c
          | >> /yacup/out/obj/util/util_name/test/test_about_something.o
mkdir -p /yacup/out/obj/util/util_name/test
gcc -c /yacup/util/util_name/test/test_about_something.c -I/yacup/util/util_name/yacup -Wall -pedantic-errors -o /yacup/out/obj/util/util_name/test/test_about_something.o
-----
-----
make[1]: Entering directory '/yacup'
-----
Setting 'test_about_something()' as the new 'main()'
objcopy --redefine-sym test_about_something=main /yacup/out/obj/util/util_name/test/test_about_something.o

Linking | << /yacup/out/obj/util/util_name/test/test_about_something.o
        | >> /yacup/out/bin/test_about_something
gcc /yacup/out/obj/util/util_name/test/test_about_something.o -I/yacup/util/util_name/yacup -Wall -pedantic-errors -lm -o /yacup/out/bin/test_about_something

Executing 'test_about_something': /yacup/out/bin/test_about_something
-----
Hi! from /yacup/util/util_name/test/test_about_something.c
-----
make[1]: Leaving directory '/yacup'
-----
```

Generated binaries, if apply, are found inside `bin` folder after a successful make call. Each executable is already tweaked so the original `test_about_something` function of each test source, is now mapped to a `main` one, allowing a direct, error-free execution.

> **TO-DO**: CI/CD

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
