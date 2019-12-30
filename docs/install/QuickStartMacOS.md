# ADMB Quick Start MacOS

*ADMB-12.1*  
*Released December 27, 2019*  

Describe downloading, installing and using ADMB from binary release for MacOS.

---

Prerequisites
-------------

For MacOS, XCode must be installed on the local computer.


Quick Start
-----------

1. **Download**

   For MacOS 64-bit, download [admb-12.1-macos-64bit](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-macos-64bit.zip).

2. **Install**

   Open a Terminal, then use the command below to extract contents of zip file to _~/admb/_. 

           [~]$ unzip admb-12.1-macos-64bit.zip

3. **Use** ADMB

   In the **Terminal** window, use the steps below to build and run the simple example.

   Change to simple example directory.       

           [~]$ cd admb/examples/admb/simple

   Build simple example.

           [~/admb/examples/admb/simple/]$ ~/admb/admb simple.tpl

   For building with Msys2 shell, use the **'admb.sh'** script.

           [~/admb/examples/admb/simple/]$ ~/admb/admb.sh simple.tpl

   Run simple example.

           [~/admb/examples/admb/simple/]$ ./simple

Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

--------------------------------------------------------------------------------
For help and support, contact <users@admb-project.org>.
