QuickStart - Using ADMB Docker Linux Image
==========================================

*ADMB-13.2*  
*Released March 15, 2024*  

Details prerequisites and procedures to use the ADMB Docker Linux image for building and running ADMB models with the [simple example](https://github.com/admb-project/admb/tree/main/examples/admb/simple).

ADMB Docker Linux Image
-----------------------

The ADMB Docker image uses the *Debian 12.1 (Bookwork)* as the base container.

Below is the list of tools that are preinstalled.

* Compiler - GNU GCC version 13.2 
* ADMB - latest version

Prerequisites
-------------

To use ADMB Docker Image for Linux, the operating system of host computer must be either Linux, MacOS or Windows.

* Download and install the [Docker Desktop](https://www.docker.com/products/docker-desktop/).

For MacOS or Windows computers, click the Docker Desktop to run the Docker services on the local host computer.

Downloads
---------

Using the Docker Desktop, download the [ADMB Docker Image](https://hub.docker.com/r/johnoel/admb/) or use the command below from the terminal.

       docker pull johnoel/admb-13.2:linux

For MacOS with ARM64 CPU host computers, download the docker image with the command below.

       docker pull johnoel/admb-13.2:linux-arm64

Usage
-----

1. Open a Terminal (or Command Prompt for Windows) and change to the model local directory.

        cd simple

2. Builds simple.tpl into a Linux executable using the ADMB Docker Linux Image and the mounted current local directory.

   For Windows host,
   
        docker run --rm --volume %CD%:/simple --workdir /simple johnoel/admb-13.2:linux simple.tpl

   For Unix host,

        docker run --rm --volume $PWD:/simple --workdir /simple johnoel/admb-13.2:linux simple.tpl

   _*Note*: A warning will be displayed for running AMD64 image on the Apple processor, but it will build and run model._

4. Run **simple** Linux executable.

   The Linux executable is incompatible for MacOS and Windows platforms, but the Docker Linux Image can be used to run the program.  See the Docker commands below.

   For Windows host,

        docker run --rm --volume %CD%:/simple --workdir /simple --entrypoint ./simple johnoel/admb-13.2:linux
        
   For Unix host,

        docker run --rm --volume $PWD:/simple --workdir /simple --entrypoint ./simple johnoel/admb-13.2:linux

   For Linux host, executable could be run locally.
   
        ./simple

Console
-------

The procedure below shows how to use the container's interactive command line shell to build and run models.

1. Use docker to open container's interactive shell and mount current local directory to the container.

   For Windows host,
   
       docker run -it --entrypoint /bin/bash --rm --volume %CD%:/simple --workdir /simple johnoel/admb-13.2:linux

   For Unix host,
   
       docker run -it --entrypoint /bin/bash --rm --volume $PWD:/simple --workdir /simple johnoel/admb-13.2:linux

2. Build and run simple model within the container's interactive shell.
    
      Build simple.tpl.

        admb simple.tpl

      Run simple executable.

        ./simple

      Exit container shell.

        exit

Docker run options
------------------

Below details the options for **docker run**:

**Options**

* **-it** opens an interactive shell.

* **--entrypoint** resets the default program to run.

* **--rm** automatically removes temporary files from a docker run.

* **--volume** mounts the current local directory **$PWD** onto the container filesystem at **:/simple**.

* **--workdir** changes the container current directory to **/simple**. 

* **johnoel/admb-13.2:linx** is the name of the Docker Image and **simple.tpl** is the file to build.

Help
----

Below are links to documentation and online support for ADMB and Docker.

* [ADMB Manuals](https://www.admb-project.org/docs/manuals/)
* [ADMB Discussions(Support)](https://github.com/admb-project/admb/discussions)
* [Docker Documentation](https://docs.docker.com/)
* [Introduction to Containers and Docker](https://learn.microsoft.com/en-us/dotnet/architecture/microservices/container-docker-introduction/)
