# ADMB Project
*ADMB-12.1*  
*Released December 27, 2019*  

Installing and using ADMB from binary zip distributions for Unix operating systems such as Linux and MacOS.

---

Prerequisites
-------------

The following programs are required to be installed on the local computer.

For Linux,

* GNU C++
* GNU stream editor (sed)

Quick Start
-----------

1. **Download**

  Download [admb-12.1-linux-64bit](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-linux-64bit.zip).

2. **Extract**

  Open a Terminal, then use the command below to extract contents of zip file to _~/admb/_. 

   For Linux (64Bit),

           [~]$ unzip admb-12.1-linux-64bit.zip

3. **Use**

  In the **Terminal** window, use the steps below to build and run the simple example.

  Change to simple example directory.       

           [~]$ cd admb/examples/admb/simple

  Build simple example.

           [~/admb/examples/admb/simple/]$ ~/admb/admb simple.tpl

  For building with Msys2 shell, use the **'admb.sh'** script.

           [~/admb/examples/admb/simple/]$ ~/admb/admb.sh simple.tpl

  Run simple example.

           [~/admb/examples/admb/simple/]$ ./simple

Read [manuals](https://github.com/admb-project/admb/releases/tag/admb-12.1/) for more information.

--------------------------------------------------------------------------------
For help and support, contact <users@admb-project.org>.
