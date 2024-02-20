# ADMB Quick Start Windows

*ADMB-13.2*  
*Released March 5, 2024*  

Describe downloading, installing and using ADMB from binary release for Windows.

---

Quick Start
-----------

1. **Download**

   Download installer [admb-13.2-windows.exe](https://github.com/admb-project/admb/releases/download/admb-13.2/admb-13.2-windows.exe).

   _**Note**_ &mdash; Installer includes MinGW-w64 C++ compiler.

2. **Install**

   Double click downloaded installer file and follow prompts.

3. **Use** ADMB

   To use ADMB, locate and double click **ADMB-13.2 Command Prompt** in the Windows Start Menu.

   In the **ADMB-13.2 Command Prompt** window, use the commands below to build and run the simple example.

   Change to simple example directory.

   ```
   C:\> cd \admb-13.2\examples\admb\simple
   ```

   Build simple example.

   ```
   C:\admb-13.2\examples\admb\simple> admb simple.tpl
   ```

   Run simple example.

   ```
   C:\admb-13.2\examples\admb\simple> simple.exe
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

4. **Configure PATH** Optional

   An alternative to using the **ADMB-13.2 Command Prompt** is to add the ADMB installation directory **C:\admb-13.2\bin** to the system enviroment **PATH** variable.  This will allow admb to be used in the **Windows Command Prompt**.

AD Studio
---------

Alternatively, install [AD Studio](https://github.com/admb-project/adstudio), a
dedicated environment for developing ADMB and TMB models. It uses the C++
compiler from Rtools and has especially good support for R, LaTeX, Markdown,
GDB, and Git.

AD Studio 1.0 comes with ADMB 12.0, which is one version older than 12.1.

Help
----

For help and support, please post on the [ADMB Discussions](https://github.com/admb-project/admb/discussions).
