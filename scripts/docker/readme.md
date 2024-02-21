ADMB Docker Images
==================

Describe Docker and quickstarts to use the ADMB Docker Images.

Docker
------

Using a Docker simplifies installation and usage of the ADMB software.  A container is similar to a virtual machine running on a local computer, but it is scaled down to mainly to provide command line programs and limited services.  One of the main benefits of using a Docker container is that all the tools and dependencies for the ADMB software are already preinstalled into the container.  Once the ADMB Docker Image is downloaded, it is ready to start building and running models.

Images
------

Please read the quickstart for the host computer.

* [Quickstart for Unix](quickstart-unix.md)

* [Quickstart for Windows](quickstart-windows.md)

Upload
------

To upload images, use the commands below.

    $ docker login
    $ docker tag admb:linux johnoel/admb-13.2:linux
    $ docker push johnoel/admb-13.2:linux

Help
----

Below are links to documentation and online support for ADMB and Docker.

* [ADMB Manuals](https://www.admb-project.org/docs/manuals/)
* [ADMB Discussions(Support)](https://github.com/admb-project/admb/discussions)
* [Docker Documentation](https://docs.docker.com/)
* [Introduction to Containers and Docker](https://learn.microsoft.com/en-us/dotnet/architecture/microservices/container-docker-introduction/)
