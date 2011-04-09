Installation
============
  Describes the installation procedure for installing ADMB
  from the binary installation file.

  Prerequistes
  ------------
  * Apple Developer Tools (XCode) must be installed
    from http://www.apple.com/xcode/.

  Procedure
  ---------
  1. Open ADMB dmg file. 
  2. In the mounted disk image (ADMB 10.0), double click the 
     pkg installer and follow the installation instructions.
  3. Once the installation is "Finished", follow the "Quick Start" 
     procedure below to build and run the simple example.

Quick Start
===========
  Describes the procedure for building and running the
  ADMB simple example.

  1. Open Terminal located in /Applications/Utilities,
     then type admb for Usage options.

     $ admb
     Usage: admb [-d] [-g] [-r] [-s] model

     Build AD Model Builder executable from TPL.

       -d     Create DLL
       -g     Insert debugging symbols
       -r     Create ADMB-RE
       -s     Enforce safe bounds
       model  Filename prefix, e.g. simple

  2. Copy simple from examples.

     $ cp -R /usr/local/admb/examples/admb/simple .

  3. Must change to the copied simple directory .

     $ cd simple

  4. Build the simple example.

     $ admb simple

     *** Parsing: tpl2cpp simple

     *** Compiling: adcomp simple
     g++ -c -O3 -Wno-deprecated  -DOPT_LIB -D__GNUDOS__ -Dlinux -DUSE_LAPLACE -fpermissive -I. -I/usr/local/admb/include simple.cpp

     *** Linking: adlink simple
     g++ -O3 -L/usr/local/admb/lib simple.o -ldf1b2o -ladmod -ladt -lado -ldf1b2o -ladmod -ladt -lado -o simple

     Successful build of executable: simple

   5. Run the simple example.

      $ ./simple

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
