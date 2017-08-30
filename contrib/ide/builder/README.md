# ADMB-IDE Builder

## Overview

This directory implements an automated build procedure for ADMB-IDE. The
automation serves two purposes: (a) continuous integration, and (b) streamlining
the work required for an official ADMB-IDE release. It consists of four scripts:

```
        ide-components.bat      ->  [components]
                |
       ide-distribution.bat     ->  [distribution]
                |
        +-------+-------+
        |               |
ide-installer.iss  ide-zip.bat  ->  admb-ide.exe, admb-ide.zip
```

## Checklist for official release

### 1 Pipeline

1a. [components](https://github.com/admb-project/admb-project.github.io/tree/master/tools/admb-ide/components)
> Update components, including `index.md`

**1b. [components.bat](https://github.com/admb-project/admb/blob/master/contrib/ide/builder/ide-components.bat)
> Update components

1c. [ide-installer.iss](https://github.com/admb-project/admb/blob/master/contrib/ide/builder/ide-installer.iss)
> Version

### 2 Lisp

2a. [admb.el](https://github.com/admb-project/admb/blob/master/contrib/emacs/admb.el)
> Copyright year, version, history entry

2b. [.emacs](https://github.com/admb-project/admb/blob/master/contrib/ide/dot/.emacs)
> Copyright year, version, history entry

### 3 Manual

3a. [intro-installer.png](https://github.com/admb-project/admb/blob/master/contrib/ide/manual/intro-installer.png)
> Current screenshot

3b. [admb-ide.texi](https://github.com/admb-project/admb/blob/master/contrib/ide/manual/admb-ide.texi)
> Version and date variables, version numbers on copyright page

3c. [admb-ide.pdf](https://github.com/admb-project/admb-project.github.io/tree/master/tools/admb-ide/admb-ide.pdf)
> Compile and upload new manual

### 4 News

4a. [NEWS](https://github.com/admb-project/admb/blob/master/contrib/ide/NEWS)
> News entry listing all user-visible changes in ADMB-IDE since last formal release
