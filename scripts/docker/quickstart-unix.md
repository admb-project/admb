QuickStart - Using ADMB Docker Image for Unix
=============================================

Details container, requirements and procedures to download and use the ADMB Docker container for running and building ADMB models.

Image
-----

The ADMB Docker image uses the *Debian 12.1 (Bookwork)* as the operating system.

Below is the list of tools that are preinstalled with the container.

* Compiler - GNU GCC version 13.2 
* ADMB - latest version

Requirements
------------

To use ADMB Docker container for Linux, the operating system of host computer must be either Linux, MacOS or Windows.

* Download and install the [Docker Desktop](https://www.docker.com/products/docker-desktop/).

Downloads
---------

* Using the Docker Desktop, download the [ADMB Docker Image](https://hub.docker.com/r/johnoel/admb/) or use the command below from the terminal.

       ~$ docker pull johnoel/admb:linux

Usage
-----

1. Open a Terminal and change to the model local directory.

        ~$ cd simple

2. Build simple.tpl into an executable using the ADMB Docker container.

        ~/simple$ docker run -rm --volume ~/simple:/simple --workdir /simple johnoel/admb:linux simple.tpl

    **Options**

    * **--rm** automatically removes temporary files for a docker run.

    * **--volume** mounts the local directory **~/simple** onto the container filesystem at **/simple**.

    * **--workdir** changes the container current directory to **/simple**. 

    * **johnoel/admb:linx** is the container name and **simple.tpl** is the file to build.

3. Run **simple** locally.

        ~/simple$ ./simple

Console
-------

The procedure below shows how to use the container's interactive command line shell to build and run models.

1. Use docker to open container's interactive shell.

        ~/simple$ docker run -it --entrypoint /bin/bash -rm --volume ~/simple:/simple --workdir /simple admb:latest

    **Options**

    * **-it** opens an interactive shell.

    * **--entrypoint** uses **/bin/bash** for the shell.

    * **--rm** automatically removes temporary files for a docker run.

    * **--volume** mounts the local directory **~/simple** onto the container using the same directory **/simple**.

    * **--workdir** changes the container current directory to the work directory **/simple**. 

    * **johnoel/admb:linux** is the container name.

2. Build and run simple model in the container's interactive shell.
    
      2.1 Build simple.tpl.

        admb:/simple$ admb simple.tpl

      2.2 Run simple executable.

        admb:/simple$ ./simple

      2.3 Exit container shell.

        admb:/simple$ exit

Help
----

Below are links to documentation and online support for ADMB and Docker.

* [ADMB Manuals](https://www.admb-project.org/docs/manuals/)
* [ADMB Discussions(Support)](https://github.com/admb-project/admb/discussions)
* [Docker Documentation](https://docs.docker.com/)
* [Introduction to Containers and Docker](https://learn.microsoft.com/en-us/dotnet/architecture/microservices/container-docker-introduction/)
