# ADMB Quick Start Windows

*ADMB-12.1*
*Released January 17, 2020*

Describe downloading, installing and using ADMB from binary release for Windows.

---

Quick Start
-----------

1. **Download**

   For Windows 64Bit, download zip file [admb-12.1-windows.zip](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-windows.zip).

   For Windows 64Bit, download self extracting file [admb-12.1-windows.exe](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-windows.exe).

   _**Note**_ &mdash; Release includes MinGW-w64 C++ compiler.

2. **Install**

   For zip file, Double click downloaded file, then extract zip file to **C:\ADMB**.

   For self extracting file , Double click downloaded file, then follow prompts.

3. **Use** ADMB

   For zip file, Use **File Explorer** and open folder **C:\ADMB**, then double click **ADMB Command Prompt** shortcut to open command line window.

   For self extracting exe file, Use **File Explorer** and open folder **C:\Program Files(x86)\ADMB-12.1**, then double click **ADMB Command Prompt** shortcut to open command line window.

   In the **ADMB Command Prompt** window, use the steps below to build and run the simple example.

   Change to simple example directory.

   ```
   C:\> cd ADMB\examples\admb\simple
   ```

   Build simple example.

   ```
   C:\ADMB\examples\admb\simple> admb simple.tpl
   ```

   Run simple example.

   ```
   C:\ADMB\examples\admb\simple> simple.exe
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

4. **Configure PATH** Optional

   An alternative to using the ADMB Command Prompt is to add the ADMB installation directory **C:\ADMB\bin** to the system enviroment PATH variable.  This will allow admb to be used in the Windows Command Prompt.

AD Studio
---------

Alternatively, install [AD Studio](https://github.com/admb-project/adstudio), a
dedicated environment for developing ADMB and TMB models. It uses the C++
compiler from Rtools and has especially good support for R, LaTeX, Markdown,
GDB, and Git.

AD Studio 1.0 comes with ADMB 12.0, which is one version older than 12.1.

---
For help and support, contact <users@admb-project.org>.
