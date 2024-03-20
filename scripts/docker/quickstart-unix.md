QuickStart - Using ADMB Docker Image for Linux
==========================================

*ADMB-13.2*  
*Released March 15, 2024*  

Details, prerequisites, and procedures to use the ADMB Docker Image for Linux for building and running ADMB models with the [simple example](https://github.com/admb-project/admb/tree/main/examples/admb/simple).

ADMB Docker Image for Linux
-----------------------

The ADMB Docker Image for Linux uses the *Debian 12.1 (Bookwork)* as the base container.

Below is the list of tools that are preinstalled.

* Compiler - GNU GCC version 13.2
* ADMB - latest version

Prerequisites
-------------

To use the ADMB Docker Image for Linux, the operating system of host computer must be either Linux, MacOS or Windows.

* Download and install the [Docker Desktop](https://www.docker.com/products/docker-desktop/).

For MacOS or Windows computers, click the Docker Desktop to run the Docker services on the local host computer.

Alternative to using Docker Desktop - GitHub Codespaces
------------------------------------------------------
If you are a GitHub user and have your model on GitHub, you can take advantage of [GitHub Codespaces](https://github.com/features/codespaces) which start up an Ubuntu Linux dev environment from your repository in your browser with VSCode as the default editor and already has Docker installed and you can use Docker through the terminal commands (see below under Downloads and Usage). Windows and macOS are not supported on Codespaces.

You can customize the [Codespace startup configuration](https://docs.github.com/en/codespaces/setting-up-your-project-for-codespaces/adding-a-dev-container-configuration/introduction-to-dev-containers) by creating a .devcontainer/devcontainer.json file (instructions in the Codespace startup configuration link). The customizations include adding R and R packages upon startup, adding VSCode extensions, changing the image from which the Codespace is built, and much more.  

You get up to 60 hours per month for free on Codespaces, after which you will be prompted to pay in order to continue using Codespaces. Generally, 60 hours is plenty of time, though if you need time beyond this, the pricing is pretty affordable. 


Downloads
---------

Using the Docker Desktop, download the [ADMB Docker Image](https://hub.docker.com/r/johnoel/admb/) by typing "admb-13.2" in the Docker Desktop search bar or use the command below from the terminal.

       docker pull johnoel/admb-13.2:linux

Usage
-----

1. Open a Terminal (or Command Prompt for Windows) and change to the model local directory. In this example we will be navigating to the simple directory under examples/admb/simple.

        cd examples/admb/simple

2. Builds simple.tpl into a Linux executable using the ADMB Docker Image for Linux and the mounted current local directory.

   For Windows host,
   
        docker run --env LDFLAGS=-static --rm --volume %CD%:/simple --workdir /simple johnoel/admb-13.2:linux simple.tpl

   For Unix host,

        docker run --env LDFLAGS=-static --rm --volume $PWD:/simple --workdir /simple johnoel/admb-13.2:linux simple.tpl

   _*Note*: A warning will be displayed for running AMD64 image on the Apple processor, but it will build and run model._

4. Run **simple** Linux executable.

   The Linux executable is incompatible for MacOS and Windows platforms, but the ADMB Docker Image for Linux can be used to run the program.  See the Docker commands below.

   For Windows host,

        docker run --env LDFLAGS=-static --rm --volume %CD%:/simple --workdir /simple --entrypoint ./simple johnoel/admb-13.2:linux
        
   For Unix host,

        docker run --env LDFLAGS=-static --rm --volume $PWD:/simple --workdir /simple --entrypoint ./simple johnoel/admb-13.2:linux

   For Linux host, executable could be run locally.
   
        ./simple

Console
-------

The procedure below shows how to use the container's interactive command line shell to build and run models.

1. Use Docker to open container's interactive shell and mount current local directory to the container.

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

* **--env LDFLAGS=-static** builds a static executable (ie admb -p).

* **--entrypoint** resets the default program to run.

* **--rm** automatically removes temporary files from a docker run.

* **--volume** mounts the current local directory **$PWD** onto the container filesystem at **:/simple**.

* **--workdir** changes the container current directory to **/simple**. 

* **johnoel/admb-13.2:linux** is the name of the Docker Image and **simple.tpl** is the file to build.

Help
----

Below are links to documentation and online support for ADMB and Docker.

* [ADMB Manuals](https://www.admb-project.org/docs/manuals/)
* [ADMB Discussions (Support)](https://github.com/admb-project/admb/discussions)
* [Docker Documentation](https://docs.docker.com/)
* [Introduction to Containers and Docker](https://learn.microsoft.com/en-us/dotnet/architecture/microservices/container-docker-introduction/)
