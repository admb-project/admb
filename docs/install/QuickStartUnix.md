# ADMB Quick Start Linux

*ADMB-12.1*  
*Released January 17, 2020*  

Describe downloading, installing and using ADMB from binary release for Linux.

---

Prerequisites
-------------

The following tools are required to be installed on the local Linux computer.

* GNU C++
* GNU stream editor (sed)

Quick Start
-----------

1. **Download**

   For Linux 64-bit, download [admb-12.1-linux-64bit](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-linux-64bit.zip).

2. **Install**

   Open a Terminal, then use the command below to extract contents of zip file to _~/admb/_. 

   ```
   [~]$ unzip admb-12.1-linux-64bit.zip
   ```

3. **Use** ADMB

   In the **Terminal** window, use the steps below to build and run the simple example.

   Change to simple example directory.       

   ```
   [~]$ cd admb/examples/admb/simple
   ```

   Build simple example.

   ```
   [~/admb/examples/admb/simple/]$ ~/admb/admb simple.tpl
   ```

   Run simple example.

   ```
   [~/admb/examples/admb/simple/]$ ./simple
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

---
For help and support, contact <users@admb-project.org>.
