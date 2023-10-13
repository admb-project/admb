ADMB Changes
============

Describe new features, changes and improvements for each release.

**Release Goals**
 
* Continually improve algorithms
* Add new requested features
* Correct defects (bugs)
* Continually streamline installation and build process
* Continually improve and update documentation

ADMB-13.2-dev
-------------

#### Changes and Improvements

* Fixed set_multinomial_weights error in binomial_w2 example (See [Changes ce9f4c8](https://github.com/admb-project/admb/commit/ce9f4c8ed0d7b8891f88f8b192f6d14db03ca361)).

* Added ADMB Docker Image scripts to automate building uploads.

ADMB-13.1
---------
*Released December 23, 2022*  

#### Changes and Improvements

* Fixed build files for building arm64 processor (See [Issue 277](https://github.com/admb-project/admb/issues/277)). Thanks to @jonrh for contributing changes. 

* Fixed build for building with Visual Studio compiler (See [Issue 274](https://github.com/admb-project/admb/issues/274)). Reported by @Ash12H.

* Allow build to use compiler which includes version (ie g++-12) (See [Issue 270](https://github.com/admb-project/admb/issues/270)). Thanks to @yukio-takeuchi for contributing changes. 

* Improve the runtime performance (See [Issue 267](https://github.com/admb-project/admb/issues/267)).

ADMB-13.0
---------
*Released August 8, 2022*  

#### New Supported Compilers

* Microsoft Visual C++ 2022

#### Changes and Improvements

*  Major update to the program display outputs (See [Issue #221](https://github.com/admb-project/admb/issues/221)).  To change display use the command line option -display N with the ADMB program. To the quiet display set N to 0.  To use the new concise display set N to 1 (default).  To use older legacy display set N to 2.

*  Change all exit statements to ad_exit as recommended by Dr. Dave Fournier (See [Issue #216](https://github.com/admb-project/admb/issues/216)).

*  Ported source code to build and run with the ISO/IEC C++20 standard (See [Issue #223](https://github.com/admb-project/admb/issues/223)).

*  Simplify linking of static library files with .lib or .a extension using the admb script (See [Changes 3fbfd6e](https://github.com/admb-project/admb/commit/3fbfd6edcf5a953a160ef54dcbee0397405519c0)).

  For Microsoft Visual Studio,
  ```
  > admb.bat myfile.tpl mylibrary.lib
  ```

  For Unix,
  ```
  > admb myfile.tpl mylibrary.a
  ```

* Profiling diagnostic option -time has been disabled for releases.
  To develop and use the -time option, rebuild ADMB libraries with 
  compiler macro DIAG_TIMER defined (See [Changes a1667e3](https://github.com/admb-project/admb/commit/a1667e31cb862355932609a839e5962fa04823c4)).

  For Microsoft Visual Studio,
  ```
  > nmake CXXFLAGS=/DDIAG_TIMER
  ```

  For Unix,
  ```
  $ make CXXFLAGS=-DDIAG_TIMER
  ```
  
* Defined DEBUG macro in build files.

* Defined DEBUG=diag in main Makefile to build ADMB with diagnostic outputs.

* Copy sparse headers to distribution includes.

* Fixed typo bug in df1b2matrix& df1b2matrix::operator=(const df1b2variable&).
  df1b2variable should be assign assigned to all elements in f1b2matrix if not empty
  (See [Changes 463db83](https://github.com/admb-project/admb/commit/463db839675fa17f2aa3852422d89e1a51f8715d)).

* Replaced ad_printf pointer to printf with ad_printf function for outputs.

* Added new function feature **dtweedie** (See [Issue #234](https://github.com/admb-project/admb/issues/234)).

* Renamed VERSION file to VERSION.txt to avoid compiler errors (See [Issue #240](https://github.com/admb-project/admb/issues/240)).

* The default value for -iprint for printing function minimizer report is every 20 iterations instead of 10
  (See [Changes 581d46c0](https://github.com/admb-project/admb/commit/581d46c0ba066e1ee2548048bc1683888f18b76d)).

* Added new feature to code admb programs directly into C++ code instead of using a TPL.  
  _Note &mdash; does not work for random effect models._

ADMB-12.3
---------
*Released March 7, 2021*  

#### New Supported Processor

* Apple M1 Processor (arm64)
  Alejandro Yáñez contributed to testing and porting of ADMB-12.3 using a local computer with the Apple M1 processor.

#### New Features

* Add **hess_step()** function for the capability to do single Newton steps using the inverse Hessian
  developed by @Cole-Monnahan-NOAA (See [Issue #160](https://github.com/admb-project/admb/issues/160) and
  [Pull #179](https://github.com/admb-project/admb/pull/179)).

* Added function hessian_phase() which will return true if the hessian is being computed
  ([See Issue #158](https://github.com/admb-project/admb/issues/158)).

* Increased static allocation size of initial_params::max_num_initial_params to 4000 using -mip option.
  If -mip is not used, the program will dynamically allocate memory for any amount of initial_params
  ([See Issue #157](https://github.com/admb-project/admb/issues/157)).

#### Changes and Improvements

* Fixed compiler boolean warnings in hmc functions
  ([See Pull #188](https://github.com/admb-project/admb/pull/186)).

* Fix bug in labels and cleanup hess_step outputs in hmc functions
  ([See Pull #185](https://github.com/admb-project/admb/pull/185)).

* Use 'make verify' to run all unit and program testing.  All the testing outputs are combined into 
  a single outputs.txt file
  ([See Issue #188](https://github.com/admb-project/admb/issues/188)).

  Also, added output file option -o to the admb script to rename and build to a specific directory.

  For example, the admb script will build the executable for mymodel.tpl to ~/bin/myprogram. 

  ```
  $ admb -o ~/bin/myprogram mymodel.tpl
  ```

* Yukio Takeuchi updated the docs for the natural cubic spline
  ([See Issue #180](https://github.com/admb-project/admb/issues/180)).

* C++14 is the default C++ compiler standard for ADMB. C++11 is still supported for older compilers
  ([See Issue #166](https://github.com/admb-project/admb/issues/166)).

* Able to use absolute path with ADMB program from any run directory with the data files
  ([See Issue #165](https://github.com/admb-project/admb/issues/165)).

  For example, use the absolute path of myprogram to run in a different directory.

  ```
  myrundirectory$ ~/bin/myprogram
  ```

* If the hessian is not positive definite, the ADMB program will NOT exit.  It will instead stop
  computing the hessian, then call the the FINAL_SECTION
  ([See Issue #164](https://github.com/admb-project/admb/issues/164)).

* Updated Git Ignore with more files to avoid displaying as unmodified list
  ([See Issue #162](https://github.com/admb-project/admb/issues/162)).

* Use CodeQL recommendations for setting size of input reads
  ([See Issue #159](https://github.com/admb-project/admb/issues/159)).

* Improved data file parser to work with different line ending including for older MacOS9 files
  ([See Issue #155](https://github.com/admb-project/admb/issues/155)).

* Added missing i5_array::initialize() function
  ([See Issue #155](https://github.com/admb-project/admb/issues/155)).

* Reverted to back to faster version of vector shape pooling code
  ([See Issue #152](https://github.com/admb-project/admb/issues/152)).

* Added a REPORT_SECTION section to the ADMB Manual
  ([See Issue #97](https://github.com/admb-project/admb/issues/97)).

* Fixed input stream for adstring to check if the buffer was exceeded
  ([See Changes 7237a6a](https://github.com/admb-project/admb/commit/7237a6a1eb3e1ddee6195db4cf6bf080b0acc665)).

* Fixed file input stream for dvector and dvar_vector to read in values from file
  ([See Changes d3be66a](https://github.com/admb-project/admb/commit/d3be66a632b28c412cc84161cc5c3725c0ae06b4)).

* The build files and outputs scripts were simplified.

* Update banner string to include Apple Clang builds.

#### Counts and Statistics

* Total Code Coverage is ~ 49.16%.  Total lines tested is 31605 out of 62160
  in the src directory
  ([See ADMB Code Coverage](https://app.codecov.io/gh/admb-project/admb)).

* Synopsys static code analyzer detected 223 outstanding defects in ADMB.  The
  total defects that have been resolved is 193
  ([See ADMB Static Analysis](https://scan.coverity.com/project/admb-project/)).

* Total Unit Tests is 933.

ADMB-12.2
---------

*Released July 31, 2020*  

#### New Supported Compilers
* GNU C++ 10 

#### New Features

* New user compilation option `-p` to build a portable (statically linked) model
  executable, which runs independently of underlying system libraries. For
  example, if one Linux machine has system library GLIBC 2.29 and another has
  GLIBC 2.28, users can now compile with

  ```
  admb -p simple
  ```

  to produce an executable that can run on both machines.  [See Issue #127](https://github.com/admb-project/admb/issues/127)

* Added access functions for ln_det, hessian and hessian inverse which should only be used in the FINAL_SECTION. [See Issue #132](https://github.com/admb-project/admb/issues/132)

  ```
  FINAL_SECTION
  cout << "\nln_det:\n" << get_ln_det_value() << endl;
  cout << "\nhessian:\n" << get_hessian() << endl;
  cout << "\nhessian inverse:\n" << get_hessian_inverse() << endl;
  ```

* Added code to do mass matrix adaptation in the NUTS routine.
  This can be initiated with the flag
  `-adapt_mass_dense` when calling the NUTS routine with
  `-nuts`. It is an experimental feature.
  
#### Changes and Improvements

* Fixed GNUmakefile and admb script when building for MacOS and clang.  [See Issue #128](https://github.com/admb-project/admb/issues/128)
* Function sqr should compute the square of a variable not the square root.  [See Issue #129](https://github.com/admb-project/admb/issues/129)
* Add batch file create-admb-command-prompt.bat to create shortcut with full instead of relative path.  [See Issue #135](https://github.com/admb-project/admb/issues/135)
* Able to use FINAL_SECTION without REPORT_SECTION. [See Issue #133](https://github.com/admb-project/admb/issues/133)
* Fixed core dump when deallocating already freed memory from xpools.  [See Issue #138](https://github.com/admb-project/admb/issues/138)   
  *Note: USE_VECTOR_SHAPE_POOL for memory pool is now disabled by default.*   
* Support adstring_array in DATA_SECTION.  [See Issue #143](https://github.com/admb-project/admb/issues/143)
* Merged adnuts improvements developed by @Cole-Monnahan-NOAA.  [See Pull #146](https://github.com/admb-project/admb/pull/146)
  - Several bugs in the NUTS MCMC routine were fixed, adaptation schemes altered, and console output improved.
  - Validity testing of all MCMC algorithms against known statistical distributions give strong evidence of the robustness of them.  
* Applied fixes from @yukio-takeuchi.
  * [Issue #122](https://github.com/admb-project/admb/issues/122)
  * [Issue #125](https://github.com/admb-project/admb/issues/125)
  * [Issue #126](https://github.com/admb-project/admb/issues/126)
  * [Issue #120](https://github.com/admb-project/admb/issues/120)
* Fixed Windows build issue reported by Jon Schnute.  [See Issue #130](https://github.com/admb-project/admb/issues/130)
* Added api documentation for functions.
* Fixed windows admb building with invalid /32 character. [See commit](https://github.com/admb-project/admb/commit/7bf1f308cad12c9c2fda0fa9dc844768691b156d) 
* Windows Innosetup installer includes mingw-w64 compiler used in Rtools 4.0.
* Updated make.exe and sed.exe in utilities from Rtools 4.0.
* Improvements to GNUmakefile files to build with GNU Make 4.3.

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
