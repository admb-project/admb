# ADMB Building Source with Visual Studio

*ADMB-13.1*  
*Released December 23, 2022*  

Describe building ADMB from source for Windows and Visual C++ compilers.

---

Building Source
---------------

**Prerequisite** &mdash; Visual Studio C++ is installed on the local computer.

1. **Download**

   Download source distribution [admb-13.1-src.zip](https://github.com/admb-project/admb/releases/download/admb-13.1/admb-13.1-src.zip).

   Double click downloaded zip file and extract admb directory to **C:\\admb\\>**.

2. **Build**

   Double click Visual Studio **Developer Command Prompt** in **Visual Studio Tools**.

   In the Visual Studio **Developer Command Prompt** window, use the steps below to build ADMB.

   Change to admb directory.

   ```
   C:\> cd admb
   ```

   To build ADMB, use the command below.

   ```
   C:\admb\> nmake
   ```

3. **Test**

   In the **Developer Command Prompt** window, use the steps below to build and run the examples.

   Build examples

   ```
   C:\admb\> cd examples
   C:\admb\examples\> nmake all
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

---
For help and support, contact <users@admb-project.org>.
