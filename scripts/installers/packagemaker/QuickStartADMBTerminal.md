# ADMB Quick Start for ADMBTerminal

*ADMB-12.1*  
*Released January 16, 2020*  

Describe downloading, installing and using ADMBTerminal from binary release for MacOS.

---

**Prerequisite** &mdash; [Apple Developer Tools (XCode)](https://developer.apple.com/xcode/) must be installed.

Quick Start
-----------

1. **Download**

   For MacOS 64-bit, download [admb-12.1-ADMBTerminal-macos-clang11-64bit.dmg](https://github.com/admb-project/admb/releases/download/admb-12.1/admb-12.1-ADMBTerminal-macos-clang11-64bit.dmg).

2. **Install**

   Double click downloaded dmg file.

   In the mounted disk image, drag **ADMBTerminal** into the **/Applications** folder.

   _**Note**_ &mdash; To allow ADMBTerminal to open in MacOS, open **Security & Privacy** in the **System Preferences**, then click **Open Anyway** for the ADMBTerminal.

3. **Use** ADMB

   Drag examples folder from mounted disk image to home directory.

   Change to the simple example directory.

   ```
   [~]% cd examples\admb\simple
   ```

   Build the simple example.

   ```
   [~/examples/admb/simple/]% admb simple
   ```

   Run the simple example.

   ```
   [~/examples/admb/simple/]% ./simple
   ```

   Read [manuals](http://www.admb-project.org/docs/manuals/) for more information.

---
For help and support, contact <users@admb-project.org>.
