# AD Studio Builder

## Overview

This directory implements an automated build procedure for AD Studio. The
automation serves two purposes: (a) continuous integration, and (b) streamlining
the work required for an official AD Studio release. It consists of four
scripts:

```
            adstudio-components.bat       ->  [components]
                    |
            adstudio-distribution.bat     ->  [distribution]
                    |
        +-----------+-----------+
        |                       |
adstudio-installer.iss  adstudio-zip.bat  ->  adstudio.exe, adstudio.zip
```

## Checklist for official release

### 1 Pipeline

1a. [components](https://github.com/admb-project/admb-project.github.io/tree/master/tools/adstudio/components)
> Update components, including `index.md`

**1b. [adstudio-components.bat](https://github.com/admb-project/admb/blob/master/contrib/adstudio/builder/adstudio-components.bat)
> Update components

1c. [adstudio-installer.iss](https://github.com/admb-project/admb/blob/master/contrib/adstudio/builder/adstudio-installer.iss)
> Version

### 2 Lisp

2a. [admb.el](https://github.com/admb-project/admb/blob/master/contrib/emacs/admb.el)
> Copyright year, version, history entry

2b. [.emacs](https://github.com/admb-project/admb/blob/master/contrib/adstudio/dot/.emacs)
> Copyright year, version, history entry

### 3 Manual

3a. [intro-install.png](https://github.com/admb-project/admb/blob/master/contrib/adstudio/manual/intro-install.png)
> Current screenshot

3b. [adstudio.texi](https://github.com/admb-project/admb/blob/master/contrib/adstudio/manual/adstudio.texi)
> Version and date variables, version numbers on copyright page

3c. [adstudio.pdf](https://github.com/admb-project/admb-project.github.io/tree/master/tools/adstudio/adstudio.pdf)
> Compile and upload new manual

### 4 News

4a. [NEWS](https://github.com/admb-project/admb/blob/master/contrib/adstudio/NEWS)
> News entry listing all user-visible changes in AD Studio since last formal release
