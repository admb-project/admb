ifeq ($(OS),Windows_NT)
  ifndef TERM
    ISCMDSHELL=yes
  endif
endif

ifndef MODEL_TPL
  ifeq ($(ISCMDSHELL),yes)
    MODEL_TPL=..\..\..\examples\admb\simple\simple.tpl
  else
    MODEL_TPL=../../../examples/admb/simple/simple.tpl
  endif
endif


VERSION=-13.2
IMAGE=admb$(VERSION)

ifdef BASE
  OS=linux-$(BASE)
else
  BASE=gcc
  OS=linux
endif

CONTAINER=$(IMAGE)

MODEL_DIR=$(dir $(MODEL_TPL))
MODEL_EXT=$(suffix $(MODEL_TPL))
MODEL_NAME=$(basename $(notdir $(MODEL_TPL)))
ifeq ($(ISCMDSHELL),yes)
  MOUNT_DIR=$(shell echo %CD%)\\$(MODEL_NAME)
else
  MOUNT_DIR=$(subst /,//,$(CURDIR)/$(MODEL_NAME))
endif

all:
	$(MAKE) $(BASE)

gcc:
	docker build --no-cache --file Dockerfile-gcc -t $(CONTAINER):$(OS) .

ubuntu:
	docker build --no-cache --file Dockerfile-ubuntu -t $(CONTAINER):$(OS) .

debian:
	docker build --no-cache --file Dockerfile-debian -t $(CONTAINER):$(OS) .

run: $(MODEL_NAME)
	docker run -e ADMB_OPTIONS=-s --rm --volume $(MOUNT_DIR)://$(MODEL_NAME) --workdir //$(MODEL_NAME) $(CONTAINER):$(OS) $(MODEL_NAME)$(MODEL_EXT)
ifneq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),Linux)
	cd $(MODEL_NAME) && ./$(MODEL_NAME)
  endif
endif

console: $(MODEL_NAME)
	docker run -it --hostname container --rm --entrypoint //bin//bash --volume $(MOUNT_DIR)://$(MODEL_NAME) --workdir //$(MODEL_NAME) $(CONTAINER):$(OS)

$(MODEL_NAME):
ifeq ($(ISCMDSHELL),yes)
	xcopy /I $(MODEL_DIR) $(MODEL_NAME)
else
  ifeq ($(OS),Windows_NT)
	cp -R $(MODEL_DIR) .
  else
	mkdir $(MODEL_NAME) && cp -R $(MODEL_DIR) $(MODEL_NAME)
  endif
endif

clean:
ifeq ($(ISCMDSHELL),yes)
	if exist $(MODEL_NAME) rmdir /S /Q $(MODEL_NAME)
else
	@rm -rvf $(MODEL_NAME)
endif
