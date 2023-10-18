QuickStart - Using ADMB Docker Image for Windows
================================================

Details requirements and procedures to download and use the ADMB Docker Image for running and building ADMB models.

Image
-----

The ADMB Docker image uses the *Windows 10 LTSC 2019* as the operating system.

Below is the list of tools that are preinstalled.

* Winlibs - GNU GCC version 13.2 
* ADMB - latest version

Requirements
------------

The Windows operating system is needed on the host computer to use the ADMB Docker Image for Windows.

* Download and install the [Docker Desktop](https://www.docker.com/products/docker-desktop/) for Windows.
* Set the default type to Windows Containers [read documentation](https://learn.microsoft.com/en-us/virtualization/windowscontainers/quick-start/set-up-environment?tabs=dockerce#install-the-container-runtime).

Downloads
---------

* Using the Docker Desktop, pull the [ADMB Docker Image](https://hub.docker.com/r/johnoel/admb/) or use the command below in them command prompt.

       docker pull johnoel/admb:windows

Usage
-----

1. Open Command Prompt and change to the model local directory.

        cd C:\simple

2. Build simple.tpl into an executable using the ADMB Docker Image.

        docker run --rm --volume %CD%:C:\simple --workdir C:\simple johnoel/admb:windows simple.tpl

    **Options**

    * **--rm** automatically removes temporary files for a docker run.

    * **--volume C:\simple:C:\simple** mounts the local directory **C:\simple** onto the container filesystem at **C:\simple**.

    * **--workdir /simple** changes the container current directory to **/simple**. 

    * **johnoel/admb:windows** is the ADMB Docker Image name and **simple.tpl** is the file to build.

3. Run **simple.exe** locally.

        simple.exe

Console
-------

The procedure below shows how to use the interactive command line shell to build and run models.

1. Use docker to open container's interactive shell.

        docker run -it --entrypoint cmd --rm --volume %CD%:C:\simple --workdir C:\simple admb:latest

    **Options**

    * **-it** opens the interactive shell.

    * **--entrypoint** uses **cmd** for the shell.

    * **--rm** automatically removes temporary files for a docker run.

    * **--volume** mounts the local directory **C:\simple** onto the container using the same directory **C:\simple**.

    * **--workdir** changes the container current directory to the work directory **C:\simple**. 

    * **johnoel/admb:windows** is the ADMB Docker image name.

2. Build and run simple model in the container's interactive shell.
    
      2.1 Build simple.tpl.

        admb simple.tpl

      2.2 Run simple executable.

        simple.exe

      2.3 Exit container shell.

        exit

Help
----

Below are links to documentation and online support for ADMB and Docker.

* [ADMB Manuals](https://www.admb-project.org/docs/manuals/)
* [ADMB Discussions(Support)](https://github.com/admb-project/admb/discussions)
* [Docker Documentation](https://docs.docker.com/)
* [Introduction to Containers and Docker](https://learn.microsoft.com/en-us/dotnet/architecture/microservices/container-docker-introduction/)
