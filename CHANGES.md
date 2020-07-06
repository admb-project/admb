ADMB Changes
============

Describe changes and features for each release.

---

Release Goals
-------------
 
* Continually improve algorithms
* Add new requested features
* Correct defects (bugs)
* Continually streamline installation and build process
* Continually improve and update documentation

Development Version
-------------------

#### New Features

* New user compilation option `-p` to build a portable (statically linked) model
  executable, which runs independently of underlying system libraries. For
  example, if one Linux machine has system library GLIBC 2.29 and another has
  GLIBC 2.28, users can now compile with

  ```
  admb -p simple
  ```

  to produce an executable that can run on both machines.

* Added access functions for ln_det, hessian and hessian inverse which should only be used in the FINAL_SECTION. [See Issue #132](https://github.com/admb-project/admb/issues/132)

  ```
  FINAL_SECTION
  cout << "\nln_det:\n" << get_ln_det_value() << endl;
  cout << "\nhessian:\n" << get_hessian() << endl;
  cout << "\nhessian inverse:\n" << get_hessian_inverse() << endl;
  ```

#### Changes and Improvements

* Fixed GNUmakefile and admb script when building for MacOS and clang.  [See Issue #128](https://github.com/admb-project/admb/issues/128)
* Function sqr should compute the square of a variable not the square root.  [See Issue #129](https://github.com/admb-project/admb/issues/129)
* Add batch file create-admb-command-prompt.bat to create shortcut with full instead of relative path.  [See Issue #135](https://github.com/admb-project/admb/issues/135)
* Able to use FINAL_SECTION without REPORT_SECTION. [See Issue #133](https://github.com/admb-project/admb/issues/133)
* Fixed core dump when deallocating already freed memory from xpools.  [See Issue #138](https://github.com/admb-project/admb/issues/138)

ADMB-12.1
---------

*Released January 17, 2020*  

#### New Supported Compilers
* GNU C++ 9
* Microsoft Visual Studio 2019

#### Changes and Improvements

* Build both the debug and dist into build/admb to simplify packaging.
* Avoid default .dat error. [See Issue #117](https://github.com/admb-project/admb/issues/117)
* Fixed forest example for Visual Studio.  Replaced function pointer in adromb with std::function.
* Include debug symbols with release binary zip distributions.
* Simplified build.

  Default will only build static libraries.

  ```
  $ make
  ```

  To build shared libraries, use target all

  ```
  $ make all
  ```

* Corrected mfexp derivative computation. [See Issue #113](https://github.com/admb-project/admb/issues/113)

* Added missing init_6darray and init_7darray. [See Issue #108](https://github.com/admb-project/admb/issues/108)

* Fixed valgrind reported memory leaks.

* Added Automated Builds for building and testing of ADMB.

  Travis CI
  
  https://travis-ci.org/admb-project/admb/

  Microsoft Azure DevOps

  https://dev.azure.com/johnoel/admb-project/_build

  GitHub Actions

  https://github.com/admb-project/admb/actions

  Buildbot

  http://buildbot.admb-project.org/

* Fixed parsers to avoid needing to add extra line at the end to the tpl file.
* Added target dist to Makefile to skip building shared libraries for faster builds.

  For unix,

  ```
  $ make dist
  ```

  For Microsoft Visual Studio,

  ```
  > nmake dist
  ```

* Able to build only shared targets.

  For unix,

  $ make shared 

ADMB-12.0
---------

*Released December 21, 2017*  

#### New Supported Compilers

* GNU C++ 7
* Intel C++ Compiler 2018
* Microsoft Visual Studio 2017 (MSVC++ 14.1)

  __Note__ Microsoft Visual C++ 2013 is no longer supported.

#### New Feature

* Dr. Cole Monnahan has developed a new MCMC functionality into ADMB. The
  current Metropolis algorithm was updated to have more meaningful console
  output and not require an sdreport object. The old method remains, and
  the new one is accessible with argument '-rwm'. A new algorithm, the
  no-U-turn sampler (a self-tuning extension of the existing 'hybrid'
  method was also added, and available with '-nuts'. The functionality
  matches the software platform Stan closely. The user can specify whether
  to use the MLE covariance, an arbitrary matrix, or adapt one during the
  warmup phase (recommended). Both these additions work much with the R
  package adnuts, which streamlines workflow, including parallel chains,
  diagnostic checking, and inference. See adnuts package vignette for more
  information.

#### Changes and Improvements

There were approximately 900 commits to improve ADMB.
Below are some of the changes.

* Fixed many signed and unsigned conversion warnings.
* Reverted change to gradcalc wrapper which caused incorrect outputs in profiler (see https://github.com/admb-project/admb/commit/6ffe1a00cc308dec52a271fa0cc088bfadfe6061).
* Fixed 2gb limitation for file i/o using MSVC compiler.
* Improved and simplified DF_FILE functions.
* Added and updated function documentation.
* Increased testing code coverage.
* Updated tiny_ad.
* Fixed issue #86.  Increased max initial parameters from 250 to 4000.

ADMB-11.6
---------

#### New Supported Compilers

* GNU C++ 6.2 and 5.3
* Rtools 3.4
* Oracle Developer Studio 12.5
* Intel C++ Compiler 2017

#### Changes and Improvements

* Added floating point checking into tpl2cpp and tpl2rem.

  To check for floating point errors, build executable with -g option.

  ```
  $ admb -g "model.tpl"
  ```

  Run executable with debugger (such as gdb) to locate file and line number
  where error occured.

  ```
  $ gdb ./model
  ```

* Configured and automated builds for ADMB-IDE.
* Merged Kasper Kristensen and Anders Nielsen bug fixes.
* Added new features such as tiny_ad.hpp and vectorize developed by DTU. See the report [Extending TMB and ADMB functionality jointly](http://www.admb-project.org/developers/workshops/seattle-2016/Kristensen_Anders_Report.pdf).
* Able to use Rtools\bin\make to build admb from source.
* Replaced rgamma function.
* Fixed numerous bugs and added various improvements.
* Compilers should support C++11 standard to build ADMB.
* Added experimental Hybrid Monte Carlo function by Cole Monnahan.
* Added experimental JSON data structure for data input.
* Added support for C++11 standard into admb script and build files.
* Added support for C++14 standard into admb script and build files if supported by compiler.
* Added release version into admb scripts -h option to help troubleshooting installation conflicts.

  The new output include **Release Version** info.

  ```
  $ admb -h
  ```

  Builds AD Model Builder executable or library.

  ```
  Usage: admb [-c] [-d] [-g] [-r] [-f] model [src(s)]

  **Release Version: 11.6**

  Options:
  -c     Build only object file(s) (.obj).
  -d     Build a shared library (.so).
  -g     Build with debug symbols.
  -r     Build with Random effects library (ADMB-RE).
  -f     Build with Fast optimized mode library (no bounds checking).
         By default, admb script builds with bounds checking.
  model  TPL file (ie 'simple.tpl' or the filename 'simple' with no .tpl
         extension)
  src(s) C/C++ Source file(s) containing classes, methods and variables that
         are used in model.
  ```
  
* MinGW-w64 Windows installers now include GNU GCC 6.2 compiler.
* Other bug fixes and improvements

#### Developers changes

* Added tool for checking for [testing code coverage](https://codecov.io/gh/admb-project/admb).

#### Website changes

* Moved website to GitHub pages (see [repository](https://github.com/admb-project/admb-project.github.io)).

ADMB-11.5
---------

#### New Supported Compilers
* Microsoft Visual C++ 14.0
* Intel C++ 2016
* GNU C++ 5.1

#### Compilers no longer supported
* Microsoft Visual C++ 11.0

#### Changes and Improvements
* Change to Dave Fournier's version of cspline.cpp.
* Added Dave Fournier's memory leak patches.
* Fixed memory leaks reported by Valgrind and XCode.
* Added more api documentation.
* mfexp will call ad_exit if computed result is not in range.
* Added more unit tests for better code coverage.
* Fixed MacOS ADMBTerminal from opening two terminals.
* Other bug fixes and improvements

ADMB-11.4
---------

#### Changes and Improvements
* Fixed unix shared builds. 
* Other bug fixes and improvements

ADMB-11.3
---------

#### Changes and Improvements
* Steve Martell's changes to gamma function.
* Other bug fixes and improvements

ADMB-11.2
---------

#### Changes and Improvements
* Default safe libs include overflows checks.
* Changes to derivative checker prompts.
* Added description documentation to the programming interface.
* Improvements to admb scripts (see New Features).
* Added more unit tests for improved code coverage. 
* Fixed reported and found bugs.
* Fixed compilers warnings.
* Add more checks in admb scripts to test for errors.
* Added Quickstart*.txt markup documentation for building and using ADMB.
* User interface: Windows admb bash script has a .sh extension to avoid 
  conflict with batch file.  So in MinGW or Cygwin shell, user will need
  to use 

  ```
  [~/admb/examples/admb/simple/]$ ~/admb/admb.sh simple
  ```

* Fixed 'admb -d' for unix, mingw and cygwin shells.
* Able to use Rtools for building, but will need to use the utilities\make.exe
  for building.
* Improved the build by restructuring and reworking the GNUmakefiles file.
* Able to use parallel build option (-j) with verify and contrib targets for 
  faster builds.
* To build with optimized libraries use fast option (-f) instead of (-o). 

  ```
  $ admb -f model.tpl
  ```

* Fix shared (libadmb.so) and dynamic (admb.dll) builds.

  ```
  [~/admb/]$ make shared

  C:\admb\> utilities\make shared
  ```

  Note &mdash; This is great for testing linker errors.

* Added contributed method to save gradient values to a file.
  Contributed by Jiashen Tang and David Fournier.

  ```
  REPORT_SECTION
    save_gradients(gradients);
  ```

* Added back the MacOS binary ADMBTerminal app.
* Packaged mingw compilers (32 and 64 bit) with windows installers.
* admb scripts can determine which parser (tpl2cpp or tpl2rem) to use.

  ```
  [~/admb/examples/admb-re/union/]$ ~/admb/admb union
  ```

  _Note: Option *-r* is no longer needed to build the random effects model._

* Separate build/dist and build/debug for easily switching between the both.
* Allow > 2GB buffers for MinGW-w64 builds.

#### New Supported Compilers

* GNU C++ 4.8 compiler
* Apple XCode 6
* MinGW 64 Bit
* Microsoft C++ 2013

 _Note: Borland 5.5 compiler is no longer supported._

#### New Features

* Add debug target to build files.

  ```
  $ make debug
  ```

* Add shared target to build files (Unix only).

  ```
  $ make shared
  ```

* admb scripts can be called directly and do not require setting enviromental variables
  ADMB_HOME and PATH.

    For Unix,  
   
        [~/admb/example/admb/simple/]$ ~/admb/admb simple

    For Windows, 
  
        C:\admb\example\admb\simple\> C:\admb\admb simple

* admb scripts can build C++ source files and link.

    For Unix, 
  
        [~/admb/example/admb/simple/]$ ~/admb/admb simple.tpl mysource.cpp

    For Windows, 
  
        C:\admb\example\admb\simple\> C:\admb\admb simple.tpl mysource.cpp

* admb scripts have a new option -f for optimized library "OPT_LIB".

    For Unix, 
  
        [~/admb/example/admb/simple/]$ ~/admb/admb -f simple.tpl mysource.cpp

    For Windows, 
  
        C:\admb\example\admb\simple\> C:\admb\admb -f simple.tpl mysource.cpp

* admb scripts have a new option -c for only building object files.

    Both commands below will only build simple.o and mysource.o compiled object files.  
    The model application will not be built. 

    For Unix, 
      
        [~/admb/example/admb/simple/]$ ~/admb/admb -c simple.tpl mysource.cpp

    For Windows, 
  
        C:\admb\example\admb\simple\> C:\admb\admb -c simple.tpl mysource.cpp

    _Note: This is the almost the same as using 'adcomp mysource'._

#### Priorities: Next Release

The following are planned or requested features for the next release.

- [ ] Add Threading Support (High)
- [ ] Write Design Documentation (High)
- [ ] Write Developer Documentation (High)
- [ ] Atan2

ADMB-11.1
---------

*ADMB-11.1*  
*Released May 10, 2013*  

#### Changes

* Updated Visual Studio nmake build files.

* Improved Unix build files.
 
  * Only outdated files are rebuilt.
  * Fast parallel building with source distribution
        
        [~/admb/]$ make -j
        
  * Building from source will create distribution folder in 'build/dist' instead of 'build/os-compiler-arch'.

* Combined mulitple libraries to a single library 'libadmb.a'. 

* Reverted some algorithms to previous version-9 code.

* The compilation scripts (adcomp, adlink, admb) compile in "safe" mode by 
  default.

* added 's' option with the Ctrl^C

* contributed libraries are built with the main libraries.
 
* flex is not needed to build ADMB, but it is needed to develop the tpl2cpp.lex 
  and tpl2rem.lex files.
  
* Improved documentation.

#### New Features
* admb script can now build tpl models without the need to set ADMB_HOME
  or PATH. For example, 

        [~/admb-11.1/examples/admb/simple/]$ ~/admb-11.1/admb simple

* Functions from user-contributed packages can be loaded from
  directory 'contrib'. Read 'contrib/README.txt'.

* New class 'init_table' to read input data into a matrix.

* New function sumsq() to calculate sum of squared values,
  equivalent to norm2().

* New constant PI for 3.141593... Makes models more portable
  than using M_PI or other compiler-specific constants.

* New shell command 'ad2csv' to write binary files to screen 
  or to a file.

* admb is now able to handle .obj, .cpp and .tpl files on
  the commandline.

    For example,

        $ admb model.tpl supportcode.cpp anotherfile.cpp

    Output is executable 'model'.

#### Bug Fixes

* Catch exit errors for adlink and adcomp.
* Watch out for spaces in admb scripts
* Fix memory leaks.

Changes 9.2 to 11.0
-------------------
* Fixed gammln functions
* Fixed configure script
* Fixed atan2 functions
* Documentation changes
* Script changes
* Various bug fixes

---
For help and support, email <users@admb-project.org>.
