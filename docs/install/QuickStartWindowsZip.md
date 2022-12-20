# ADMB Quick Start Windows

*ADMB-13.1*  
*Released December 23, 2022*  

Describe downloading, installing and using ADMB from binary release for Windows.

---

Quick Start
-----------

1. **Download**

   Download installer [admb-13.1-windows.zip](https://github.com/admb-project/admb/releases/download/admb-13.1/admb-13.1-windows.zip).

2. **Install**

   Double click downloaded zip, then extact **admb-13.1** folder to the **C:\**.

3. **Use** ADMB

   To use ADMB, locate and double click **ADMB Command Prompt** in **C:\admb-13.1** folder.

   In the **ADMB Command Prompt** window, use the steps below to build and run the simple example.

   Change to simple example directory.

   ```
   C:\> cd \admb-13.1\examples\admb\simple
   ```

   Build simple example.

   ```
   C:\admb-13.1\examples\admb\simple> admb simple.tpl
   ```

   Run simple example.

   ```
   C:\admb-13.1\examples\admb\simple> simple.exe
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

4. **Configure PATH** Optional

   An alternative to using the **ADMB Command Prompt** is to add the ADMB installation directory **C:\admb-13.1\bin** to the system enviroment **PATH** variable.  This will allow admb to be used in the **Windows Command Prompt**.

AD Studio
---------

Alternatively, install [AD Studio](https://github.com/admb-project/adstudio), a
dedicated environment for developing ADMB and TMB models. It uses the C++
compiler from Rtools and has especially good support for R, LaTeX, Markdown,
GDB, and Git.

AD Studio 1.0 comes with ADMB 12.0, which is one version older than 12.1.

---
For help and support, contact <users@admb-project.org>.
