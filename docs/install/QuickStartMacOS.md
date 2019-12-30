# ADMB Quick Start MacOS

*ADMB-12.1*  
*Released December 30, 2019*  

Describe downloading, installing and using ADMB from binary release for MacOS.

---

**Prerequisite** &mdash; [Apple Developer Tools (XCode)](https://developer.apple.com/xcode/) must be installed.

Quick Start
-----------

1. **Download**

   For MacOS 64-bit, download [admb-12.1-macos-64bit](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-macos-64bit.zip).

2. **Install**

   Open a Terminal, then use the command below to extract contents of zip file to **~/admb/**. 

   ```
   [~]$ unzip admb-12.1-macos-64bit.zip
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
