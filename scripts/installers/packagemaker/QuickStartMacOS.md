# ADMB Quick Start for MacOS

*ADMB-13.0*  
*Released May 31, 2022*  

Describe downloading, installing and using ADMBTerminal from binary release for MacOS.

---

**Prerequisite** &mdash; [Apple Developer Tools (XCode)](https://developer.apple.com/xcode/) and the command line tools must be installed.

To install or update command line tools, use the command below in the MacOS Terminal, then click "Install" button in the window.

```
[~]% xcode-select --install
```

Quick Start
-----------

1. **Download**

   Download [admb-13.0-macos.dmg](https://github.com/admb-project/admb/releases/download/admb-13.0/admb-10.0-macos.dmg).

2. **Install**

   Double click downloaded dmg file.

   In the mounted disk image, move **ADMBTerminal** into the **/Applications** folder or preferred folder.

   _**Note**_ &mdash; To allow ADMBTerminal to open in MacOS, open **Security & Privacy** in the **System Preferences**, then click **Open Anyway** for the ADMBTerminal.

3. **Use** ADMB

   Drag examples folder from mounted disk image to home directory.

   Change to the simple example directory.

   ```
   [~]% cd examples/admb/simple
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
