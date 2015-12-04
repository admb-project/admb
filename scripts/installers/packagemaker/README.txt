#ADMB Project
*ADMB-11.5*  
*Released December 1, 2015*  

The installation procedure for installing ADMBTerminal app for the MacOS.

---

Installation
============

**Prerequisite** &mdash; [Apple Developer Tools (XCode)](https://developer.apple.com/xcode/) must be installed.

1. Download ADMB installer

       For 64Bit, download [admb-11.5-ADMBTerminal-macos10-xcode7-64bit](https://github.com/admb-project/admb/releases/download/admb-11.5/admb-11.5-ADMBTerminal-macos10-xcode7-64bit.dmg).


       For 32Bit, download [admb-11.5-ADMBTerminal-macos10-xcode7-32bit](https://github.com/admb-project/admb/releases/download/admb-11.5/admb-11.5-ADMBTerminal-macos10-xcode7-32bit.dmg).  

2. Double click downloaded ADMB dmg file. 

3. In the ADMBTerminal mounted disk image, copy **ADMBTerminal**
   into the **/Applications** folder.
  
     **Note** &mdash; ADMBTerminal will set *ADMB_HOME* to **/Applications/ADMBTerminal.app/admb/ **.

Quick Start
===========

Build and run the simple example.

1. Open **ADMBTerminal** located in **/Applications**,
   then type **admb** for Usage options.

        [~]$ admb

        Builds AD Model Builder executable or library.

        Usage: admb [-c] [-d] [-g] [-r] [-f] model [src(s)]

        Options:
         -c     Build only object file(s) (.obj).
         -d     Build a shared library (.so).
         -g     Build with debug symbols.
         -r     Build with Random effects library (ADMB-RE).
         -f     Build with Fast optimized mode library (no bounds checking).
                By default, admb script builds with bounds checking.
         model  TPL file (ie simple.tpl or the filename simple with no .tpl
                extension)
         src(s) C/C++ Source file(s) containing classes, methods and variables that
                are used in model.

2. Copy simple example from ADMB_HOME.

        [~]$ cp -R $ADMB_HOME/examples/admb/simple .

3. Change to the simple example directory .

        [~]$ cd simple

4. Build the simple example.

        [~/simple/]$ admb simple

        *** Parse tpl: simple.tpl
        tpl2cpp simple

        *** Compile: simple.cpp
        c++ -c -O3 -I. -I"/Applications/ADMBTerminal.app/include" -I"/Applications/ADMBTerminal.app/contrib/include" -osimple.obj simple.cpp

        *** Linking: simple.obj 
        c++ -O3 -osimple simple.obj "/Applications/ADMBTerminal.app/contrib/lib/libadmb-contrib.a"

        Successfully built executable.

5. Run the simple example.

        [~/simple/]$ ./simple 

        Initial statistics: 2 variables; iteration 0; function evaluation 0; phase 1
        Function value   3.6493579e+01; maximum gradient component mag  -3.6127e+00
        Var   Value    Gradient   |Var   Value    Gradient   |Var   Value    Gradient   
          1  0.00000 -3.61269e+00 |  2  0.00000 -7.27814e-01 |

         - final statistics:
        2 variables; iteration 7; function evaluation 19
        Function value   1.4964e+01; maximum gradient component mag  -7.0014e-05
        Exit code = 1;  converg criter   1.0000e-04
        Var   Value    Gradient   |Var   Value    Gradient   |Var   Value    Gradient   
          1  1.90909 -7.00140e-05 |  2  4.07818 -2.08982e-05 |
        Estimating row 1 out of 2 for hessian
        Estimating row 2 out of 2 for hessian

    Read [manuals](https://github.com/admb-project/admb/releases/tag/admb-11.5/) for more information.

---
For help and support, contact <users@admb-project.org>.
