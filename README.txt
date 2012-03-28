ADMB Project
Version trunk
Release date

Overview
========
The ADMB (Automatic Differentiation Model Builder) software suite is an
environment for nonlinear statistical modeling enabling rapid model
development, numerical stability, fast and efficient computation, and high
accuracy parameter estimates. AD Model Builder is a high level language built
around the AUTODIF Library, a C++ language extension which transparently
implements reverse mode automatic differentiation. A closely related software
package, ADMB-RE, implements random effects in nonlinear models.

Donations
=========
ADMB is an open source project that is freely available for download. If you
would like to contribute or donate funds, please contact users@admb-project.org.
Cool ADMB T-shirts are also available for purchase.

How to Cite ADMB
================
Fournier, D.A., H.J. Skaug, J. Ancheta, J. Ianelli, A. Magnusson, M.N. Maunder,
A. Nielsen, and J. Sibert. 2012. AD Model Builder: using automatic
differentiation for statistical inference of highly parameterized complex
nonlinear models. Optim. Methods Softw. 27:233-249.

It can be downloaded for free from the publisher:
http://tandfonline.com/doi/abs/10.1080/10556788.2011.597854

Table of Contents
=================
 * Release Notes
   - Changes
 * Requirements
 * Downloading
 * Installation from Binary Distribution
   - Linux and GCC
   - MacOS and XCode
   - Windows and GCC
 * Installation from Source Code
   - Linux and GCC
   - Linux and Intel Compiler
   - Linux and Solaris Studio
   - MacOS and Clang
   - Windows and GCC using MSYS Linux emulation
   - Windows and MSVC
 * Documentation
 * Developing AD Model Builder
   - Version Control
   - Developer documentation
 * Help and Support
 * Contributors

Release Notes
=============
The goal for this release was to improve algorithms, add new requested features,
correct defects (bugs), and streamline installation and build process.

Changes
-------
 * Fixed gammln functions
 * Fixed configure script
 * Fixed atan2 functions
 * Documentation changes
 * Script changes
 * Various bug fixes

Thanks to the following people for providing fixes and suggestions.
 * Dave Fournier
 * Jan Jaap
 * Gareth Williams
 * Weihai Liu
 * Barak A. Pearlmutter

Requirements
============
ADMB has been tested and used on Windows and Linux operating systems in both 32
and 64 bit versions. A C/C++ compiler must be be installed on the local
computer.

Several compilers are supported, including
 * GCC 3.4 or newer
 * Microsoft Visual C++ 2003 or newer
 * MacOS XCode 3.2 and 4.x
 * Clang 3.0
 * Intel C++ Compiler 11
 * Solaris Studio 12

If the compiler is not listed, build the source distribution or email
users@admb-project.org for help.

Downloading
===========
Precompiled binaries and the source distribution can be downloaded from
http://www.admb-project.org/downloads/.

Installation from Binary Distributions
======================================
Note: illustrated instructions for installation from binary distributions are
      available at http://admb-project.org/documentation/installation/

Linux and GCC
-------------
Note: additional information about running ADMB in linux, especially for
   linux beginners, is available at 
   http://admb-project.org/community/tutorials-and-examples/using-admb-on-linux

1. Download and extract ADMB Linux binaries from 
   http://admb-project.org/downloads. 

2. Open a bash shell, change to extracted Linux ADMB Home directory, then type
   the following commands.

      #Change to ADMB folder.
      $ cd ~/admb
      # Sets ADMB Home directory.
      $ export ADMB_HOME=~/admb
      # Adds ADMB bin to $PATH
      $ export PATH=$ADMB_HOME/bin:$PATH

3. Change into ADMB Home directory, then run examples for verification.
      $ cd $ADMB_HOME
      $ chmod -R u+w examples
      $ cd examples
      $ make


MacOS and XCode
---------------
1. Download admb-'version'.dmg
2. Double click admb-'version'.dmg file
3. Double click the admb-'version'.pkg
4. Follow the installation instructions

If successful, the wizard will have installed admb directory (/usr/local/admb)
and script (/usr/local/bin/admb).

Windows and GCC
---------------
1. Download the executable installer for Windows GCC from 
   http://admb-project.org/downloads. The GCC compiler is included with 
   this installer.

2. Double click the installer and follow the instructions. If you have 
   administrative privileges, the default installation in Program Files should
   be fine. If you DO NOT have administrative privileges, choose a location 
   like c:\ADMB. This might be preferable regardless.

3. Once the installer is Finished, open the ADMB Command Prompt located in 
   Start -> All Programs -> ADMB (MinGW GCC-4.5.2)
     -> ADMB Command Prompt (MinGW GCC-4.5.2)

4. In the Command prompt, type the command below to build and run the 
   simple example.

     c:\ADMB> cd examples\admb\simple
     c:\ADMB\examples\admb\simple> admb simple
     c:\ADMB\examples\admb\simple> simple

   Those commands should compile and run the simple model, producing output 
   ending with the line "Estimating row 2 out of 2 for hessian".

Windows and MSVC
----------------
1. Download and install the following software, install them in their default
   locations:
   A. Microsoft .NET 4
   B. Microsoft Windows SDK 7.1
   C. Microsoft Visual Studio 2010

2. Download the executable installer for Windows MSVC from 
   http://admb-project.org/downloads and run it.  Make sure to choose the
   install location as C:\admb.

3. Add the following to the PATH, in the order given, the second path must
   reflect which architecture you want to compile for, this example is for 
   Intel 64-bit processors:

   C:\Program Files\Microsoft SDKs\Windows\v7.1
   C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\x86_ia64
   C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin
   C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE
   C:\admb\bin

4. Add the following environment variable:
   ADMB_HOME = C:\admb

5. You must use the Windows SDK 7.1 command prompt to compile your code.  This
   should be a shortcut in the Start menu but the shortcut is this:

   C:\Windows\System32\cmd.exe /E:ON /V:ON /T:0E /K 
   "C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\SetEnv.cmd"

Installation from Source Code
=============================
Below are procedures for installing ADMB from source code.

Linux and GCC
-------------
1. Extract source distribution

   $ unzip admb-'version'.zip

   where 'version' is the distribution version.

2. Change to distribution directory

   $ cd admb-'version'

3. Create configure script

   $ make --directory=scripts/configure/

4. Configure the build files

   $ ./configure

   To check options

   $ ./configure --help

5. Build binaries

   $ make

6. [Optional] Test build by running examples

   $ make verify

7. Install binaries to default location /usr/local.

   $ make install

Linux and Intel Compiler
------------------------
1. Extract source distribution

   $ unzip admb-'version'.zip

   where 'version' is the distribution version.

2. Change to distribution directory

   $ cd admb-'version'

3. Configure the build files for Intel C++ Compiler

   $ ./configure CC=icc CXX=icpc

4. Build binaries

   $ make

4. [Optional] Test build by running examples

   $ make verify

5. Install binaries to default location /usr/local.

   $ make install

Linux and Solaris Studio
------------------------
1. Extract source distribution

   $ unzip admb-'version'.zip

   where 'version' is the distribution version.

2. Change to source directory

   $ cd admb-'version'/src

3. Build binaries

   $ make --file=sunstudio.mak

4. [Optional] Test build by running examples

   $ make verify

5. Install binaries to default location /usr/local.

   $ make install

MacOS and Clang
---------------
1. Extract source distribution

   $ unzip admb-'version'.zip

   where 'version' is the distribution version.

2. Change to distribution directory

   $ cd admb-'version'

3. Configure the build files for Clang

   $ ./configure CC=clang CXX=clang++

4. Build binaries

   $ make

4. [Optional] Test build by running examples

   $ make verify

5. Install binaries to default location /usr/local.

   $ make install

Windows and MSVC
----------------
Prerequisites (Install all of these in their default locations):
1. Microsoft .NET 4
2. Microsoft Windows SDK 7.1
3. Microsoft Visual Studio 2010

Add the following to the PATH, in the order given, the second path must
reflect which architecture you want to compile for, here it is for Intel 64:

C:\Program Files\Microsoft SDKs\Windows\v7.1
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\x86_ia64
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin
C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE

Steps:
1. Extract source distribution.

2. Open Visual C++ Command Prompt.

3. Change directory to the "src" folder.

   > cd admb-'version'\src

   where 'version' is the distribution version.

4. Build binaries

   > nmake /fvc.mak

5. [Optional] Test build by running examples

   > nmake /fvc.mak verify

Documentation
=============
User manuals for AD Model Builder, the AUTODIF library and the ADMB-RE nonlinear
random effects module can be downloaded from
http://www.admb-project.org/downloads/.

More documentation is also available on the main ADMB homepage
http://www.admb-project.org/.

Developing AD Model Builder
===========================
If you are interested in contributing to the further development of AD Model
Builder please contact users@admb-project.org.

Version Control
---------------
ADMB source version control URL is http://www.admb-project.org/svn/trunk/.

To download source files, use the command

$ svn checkout http://www.admb-project.org/svn/trunk admb-trunk-readonly

If you would like to write access, please email users@admb-project.org to
request an account.

Developer Documentation
-----------------------
Developer documentation such as "ADMB Coding Standards" are available at

http://www.admb-project.org/developers/

Help and Support
================
For help and support, email users@admb-project.org.

Contributors
============
This software was originally developed by David Fournier of Otter Research Ltd.

Several other folks have contributed to the ADMB Project:

David Fournier <davef@otter-rsch.com>
John Sibert <sibert@hawaii.edu>
Hans Skaug <Hans.Skaug@mi.uib.no>
Mark Maunder <mmaunder@iattc.org>
Anders Nielsen <anders@nielsensweb.org>
Arni Magnusson <arnima@hafro.is>
Derek Seiple <dseiple@hawaii.edu>
Johnoel Ancheta <johnoel@hawaii.edu>
