QuickStart - Using ADMB Docker Container for Windows
====================================================

Details container, requirements and procedures to download and use the ADMB Docker container for running and building ADMB models.

Container
---------

The ADMB Docker container uses the *Windows 10 LTSC 2019* as the operating system.

Below is the list of tools that are preinstalled with the container.

* Winlibs - GNU GCC version 13.2 
* ADMB - latest version

Requirements
------------

The Windows operating system of host computer is needed to use the ADMB Docker container for Windows.

* Download and install the [Docker Desktop](https://www.docker.com/products/docker-desktop/) for Windows.

Downloads
---------

* Using the Docker Desktop, pull the [ADMB container](https://hub.docker.com/r/johnoel/admb/).

       C:\> docker pull johnoel/admb:windows

Usage
-----

1. Open Command Prompt and change to the model local directory.

        C:\> cd C:\simple

2. Build simple.tpl into an executable using the ADMB Docker container.

        C:\simple> docker run -rm --volume C:\simple:C:\simple --workdir C:\simple admb simple.tpl

    **Options**

    * **-rm** automatically removes temporary files for a docker run.

    * **--volume C:\simple:C:\simple** mounts the local directory **C:\simple** onto the container filesystem at **C:\simple**.

    * **--workdir /simple** changes the container current directory to **/simple**. 

    * **admb** is the container name and **simple.tpl** is the file to build.

3. Run **simple.exe** locally.

        C:\simple> simple.exe

Console
-------

The procedure below shows how to use the container's interactive command line shell to build and run models.

1. Use docker to open container's interactive shell.

        C:\simple> docker run -it --entrypoint cmd --rm --volume C:\simple:C:\simple --workdir C:\simple admb:latest

    **Options**

    * **-it** opens the interactive shell.

    * **--entrypoint** uses **cmd** for the shell.

    * **-rm** automatically removes temporary files for a docker run.

    * **--volume** mounts the local directory **C:\simple** onto the container using the same directory **C:\simple**.

    * **--workdir** changes the container current directory to the work directory **C:\simple**. 

    * **admb:latest** is the container name.

2. Build and run simple model in the container's interactive shell.
    
      2.1 Build simple.tpl.

        C:\simple> admb simple.tpl

      2.2 Run simple executable.

        C:\simple> simple.exe

      2.3 Exit container shell.

        C:\simple> exit

Help
----

Below are links to documentation and online support for ADMB and Docker.

* [ADMB Manuals](https://www.admb-project.org/docs/manuals/)
* [ADMB Discussions(Support)](https://github.com/admb-project/admb/discussions)
* [Docker Documentation](https://docs.docker.com/)
* [Introduction to Containers and Docker](https://learn.microsoft.com/en-us/dotnet/architecture/microservices/container-docker-introduction/)
