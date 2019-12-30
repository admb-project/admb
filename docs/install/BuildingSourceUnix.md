# ADMB Building Source for Unix
*ADMB-12.1*  
*Released December 30, 2019*  

Describe building ADMB from source for Unix.

---

Prerequisites
-------------

The following tools should be installed on the local computer.

* C++ compiler

  Supported C++ Compilers for Unix

  * GNU C++
  * Apple Clang
    
* GNU make
* GNU stream editor (sed)
* GNU flex
* _**Optional**_ &mdash; Git client to download from version control.

_**Note** &mdash; For MacOS, install XCode with command line tools that includes all the prerequisites._

Building Source
---------------

1. **Download**

   Download ADMB source distribution [admb-12.1-src.zip](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-src.zip).

   Open a **Terminal** window

   Use the command below to extract contents of zip file to _~/admb/_. 

   ```
   [~]$ unzip admb-12.0-src.zip
   ```

   _**Alternative**_ &mdash; Use Git client (see command below) to get source from version control repository.

   ```
   [~]$ git clone https://github.com/admb-project/admb.git
   ```

   This will download latest source repository to _~/admb/_.


2. **Build**

   Change to admb directory.

   ```
   [~]$ cd admb
   ```

   To build ADMB, use the commands below.
   
   ```
   [~/admb/]$ make
   ```

   _**Note**_ &mdash; When the build is completed, **~/admb/build/admb/** is the binary distribution directory.

3. **Test**

   In the **Terminal** window, use the steps below to build and run the simple example.

   Build examples

   ```
   [~/admb/]$ make --directory=examples all
   ```

4. _**Optional**_ &mdash; Multi-User Installation    

   Installs binary distribution folder to /usr/local/ as super-user.

   ```
   [~/admb/]$ sudo make install
   ```

   Build and run the simple example without the directory prefix.

   ```
   [~/admb/]$ cd examples/admb/simple
   [~/admb/examples/admb/simple/]$ admb simple.tpl
   [~/admb/examples/admb/simple/]$ ./simple
   ```

   _If unable to build simple example, then use the Manual Installation below._

   _**Alternative**_ &mdash; Manual Installation    

   Copy binary distribution folder to /usr/local/ as super-user.

   ```
   [~/admb/]$ sudo cp -Rvf build/dist /usr/local/admb
   ```

   _**Note**_ &mdash; The dist folder can be copied to other computers with similar configurations.

   Create symlink to main admb script.  Directory **/usr/local/bin/** should already exist.

   ```
   [~/admb/]$ sudo ln -sf /usr/local/admb/admb /usr/local/bin/admb
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

---
For help and support, contact <users@admb-project.org>.
