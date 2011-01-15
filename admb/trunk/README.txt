ADMB Project
Version 10.0
Released January 17, 2011

Overview
========
The ADMB(Automatic Differentiation Model Builder) software suite 
is an environment for non-linear statistical modeling enabling
rapid model development, numerical stability, fast and efficient 
computation, and high accuracy parameter estimates.  ADModel Builder
is a high level language built around the AUTODIF Library, a C++
language extension which transparently implements reverse mode 
automatic differentiation.  A closely related software package, 
ADMB-RE, implements random effects in non-linear models.

Donations
=========
ADMB is an open source project that is freely available for download.
If you would like to contribute or donate funds, please contact 
<users@admb-project.org>.  Cool ADMB T-shirts are also available 
for purchase.

Table of Contents
=================
 * Release Notes
   - Changes
 * Requirements
 * Downloading
 * Installation
 * Installation from Source Distribution
 * Installation from Binary Distribution
 * Documentation
 * Developing ADModel Builder
   - Version Control
 * Help and Support
 * Contributors

Release Notes
=============
The goal for this release was to improve algorithms, add new 
requested features, correct defects (bugs), and streamline 
installation and build process.

Below lists some of the changes.

Changes
-------
 * Fixed MCMC issue
 * Fixed configure script
 * Updated Manuals 
 * Fixed min and max functions
 * Updated API documentation
 * Improved algorithms
 * Matrix exponential
 * Hybrid MCMC
 * Sparse Hessian
 * Added more examples
 * Added support for Intel C++ compiler
 * Added Autoconf script
 * Streamlined source builds
 * Various bug fixes

Requirements
============
ADMB has been tested and used on Windows and UNIX operating 
systems in both 32 and 64 bit versions.  A C/C++ compiler 
must be be installed on the local computer. Below lists some 
tested compilers.

Several compilers are supported including 
 * GNU g++ 3.4 or newer
 * Microsoft Visual C++ 2003 or newer
 * MacOS XCode 3.2
 * Intel C++ Compiler 11
 * Sun Studio 12
 * Borland 5.5

If the compiler is not listed, build the source distribution or 
email user group <users@admb-project.org> for help.

Downloading
===========
Precompiled binaries and the source distribution can be downloaded
from "http://www.admb-project.org/downloads/".

Installation from Source Code
=============================
Below are procedures for installing ADMB from source code.

Unix and GNU g++
----------------
1. Extract source distribution
   
   $ unzip admb-10.0.zip

2. Change to distribution directory

   $ cd admb-10.0

3. Configure the build files for 32-bit

   $ ./configure

   or configure the build files for 64-bit.

   $ ./configure BUILD_64BIT=yes

4. Build libraries 
  
   $ make

5. [Optional] Test build by running examples

   $ make verify

6. Install libraries to default location /usr/local.

   $ make install

Unix and Sun Studio 12
----------------------
1. Extract source distribution
   
   $ unzip admb-10.0.zip

2. Change to source directory

   $ cd admb-10.0/src

3. Build libraries 
  
   $ make --file=sunstudio.mak

4. [Optional] Test build by running examples

   $ make verify

5. Install libraries to default location /usr/local.

   $ make install

Unix and Intel C++ Compiler
---------------------------
1. Extract source distribution
   
   $ unzip admb-10.0.zip

2. Change to source directory

   $ cd admb-10.0/src

3. Build libraries 
  
   $ make --file=icc.mak

4. [Optional] Test build by running examples

   $ make verify

5. Install libraries to default location /usr/local.

   $ make install

Microsoft Windows and Visual C++
--------------------------------
1. Extract source distribution.

2. Open Visual C++ Command Prompt. 

3. Change directory to the "src" folder. 

   > cd admb-10.0\src

4. Build libraries

   > nmake /fvc.mak

5. [Optional] Test build by running examples

   > nmake /fvc.mak verify

6. Install libraries to default location %ProgramFiles%\ADMB
   and adds ADMB shortcuts in the Start menu.

   > nmake /fvc.mak install

Microsoft Windows and Borland C++ 5.5
-------------------------------------
1. Extract source distribution.

2. Open Windows Command Prompt in Start->All Programs->Accessories.

3. Set BCC55_HOME variable to location of BCC55 folder.

   > set BCC55_HOME=c:\Borland\BCC55

4. Add BCC55_HOME to system PATH variable.

   > set PATH=c:\Borland\BCC55\Bin;%PATH%

5. Change directory to the "src" folder. 

   > cd admb-10.0\src

6. Build 32-bit libraries

   > make /fbcc.mak

7. [Optional] Test build by running examples

   > make /fbcc.mak verify

8. Install libraries to default location %ProgramFiles%\ADMB
   and adds ADMB shortcuts in the Start menu.

   > make /fbcc.mak install

Microsoft Windows and MinGW (msys and gcc-4.5)
----------------------------------------------
1. Open MinGW Shell located in Start->MinGW->MinGW Shell.

2. Extract source distribution.
   
   $ unzip admb-10.0.zip

2. Change to distribution directory

   $ cd admb-10.0

3. Configure the build files for 32-bit

   $ ./configure

4. Build libraries 
  
   $ make

5. [Optional] Test build by running examples

   $ make verify

6. Install libraries to default location /usr/local.

   $ make install

Installation from Binary Distributions
======================================
Binary installation instructions can be found at 
"http://www.admb-project.org/documentation/".

Documentation
=============
User manuals for ADModel Builder, the AUTODIF library and the ADMB-RE
Nonlinear random effects module can be downloaded from 
"http://www.admb-project.org/downloads/".

More documentation is also available on the main ADMB homepage 
"http://www.admb-project.org/".

Developing ADModel Builder
==========================
If you are interested in contributing to the further development of
ADModel Builder please contact <users@admb-project.org>.

Version Control
---------------
ADMB source version control is hosted at Code Google
"http://code.google.com/p/admb-project/".  

The instructions for checking out source trunk is at 
"http://code.google.com/p/admb-project/source/checkout".  

If you would like to write access, please email <users@admb-project.org>
to request an account.

Help and Support
================
For help and support, email the ADMB users group <users@admb-project.org>.

Contributors
============
This software was originally developed by David Fournier of Otter Research, Ltd. 

Several other folks have contributed to the ADMB Project:

David Fournier <davef@otter-rsch.com>
John Sibert <sibert@hawaii.edu>
Hans Skaug <Hans.Skaug@mi.uib.no>
Mark Maunder <mmaunder@iattc.org> 
Anders Nielsen <anders@nielsensweb.org>
Arni Magnusson <arnima@hafro.is> 
Derek Seiple <dseiple@hawaii.edu>
Johnoel Ancheta <johnoel@hawaii.edu>
