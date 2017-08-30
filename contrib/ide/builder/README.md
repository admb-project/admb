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

Checklist and workflow for official ADMB-IDE release:

## 1 BUILD PIPELINE

### 1a. `admb-project.github.io/tools/admb-ide/components`

Check if anything should be updated or removed, including `index.md`

### 1b. admb/contrib/ide/builder/ide-components.bat

Check if any components have been updated

### 1c. `admb/contrib/ide/builder/ide-installer.iss`

Version

## 2 EMACS LISP

### 2a. admb/contrib/emacs/admb.el

Copyright year, version, history entry

### 2b. admb/contrib/ide/dot/.emacs

Copyright year, version, history entry

## 3 MANUAL

### 3a. admb/contrib/ide/manual/intro-installer.png

Current screenshot

### 3b. admb/contrib/ide/manual/admb-ide.texi

Version and date variables, version numbers on copyright page

### 3c. admb-project.github.io/tools/admb-ide

Compile and upload new manual

## 4 FINISHING TOUCH

### 4a. admb/contrib/ide/NEWS

News entry listing all user-visible changes in ADMB-IDE since last formal
release
