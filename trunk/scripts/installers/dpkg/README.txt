Desribes the ADMB installation procedure for Ubuntu operating system.

Installation
============

1. Download ADMB debian package

       [ADMB Ubuntu14LTS (64 Bit).deb](http://www.admb-project.org/buildbot/snapshots/admb-latest-ubuntu14-64bit_11.1.deb)

2. Install ADMB
       __Note &mdash; Remove any existing admb package $ sudo dpkg -r admb__

       $ sudo dpkg -i admb-latest-ubuntu14-64bit_11.1.deb

Quick Start
===========
Describe the procedure for building and running the ADMB simple example.

1. Open "Terminal", then type admb for Usage options.

        ~$ admb

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

        ~$ cp -R /usr/local/admb/examples/admb/simple .

3. Must change to the copied simple directory .

        ~$ cd simple

4. Build the simple example.

        ~/simple$ admb simple

        *** Parse tpl: simple.tpl
        tpl2cpp simple

        *** Compile: simple.cpp
        g++ -c -O3 -I. -I"/usr/local/admb/include" -I"/usr/local/admb/contrib/include" -osimple.obj simple.cpp

        *** Linking: simple.obj 
        g++ -O3 -osimple simple.obj "/usr/local/admb/contrib/lib/libcontrib.a" "/usr/local/admb/lib/libadmb.a"

        Successfully built executable.

5. Run the simple example.

        ~/simple$ ./simple 

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

6. Consult the ADMB manual for description of the simple output files.

Help
====
If help is needed, please email the ADMB users group <users@admb-project.org>.
