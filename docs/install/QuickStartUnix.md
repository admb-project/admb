# ADMB Quick Start Unix

*ADMB-13.2*  
*Released March 15, 2024*  

Describe downloading, installing and using ADMB from binary release for Linux.

---

Prerequisites
-------------

The following tools are required to be installed on the local Linux computer.

* GNU C++
* GNU stream editor (sed)

Below are the operating systems supported for linux. 

* Fedora 36
* Ubuntu 20.04
* Centos 7

Quick Start
-----------

1. **Download**

   Download linux ZIP file [admb-13.2-linux.zip](https://github.com/admb-project/admb/releases/download/admb-13.2/admb-13.2-linux.zip).

2. **Install**

   Open a **Terminal**, then use the command below to extract contents of downloaded zip file to _~/admb/_. 

   ```
   [~]$ unzip admb-13.2-linux.zip
   ```

3. **Use** ADMB

   In the **Terminal** window, use the commands below to build and run the simple example.

   Change to simple example directory.       

   ```
   [~]$ cd ~/admb/examples/admb/simple
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

Help
----

For help and support, please post on the [ADMB Discussions](https://github.com/admb-project/admb/discussions).
