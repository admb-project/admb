ifneq ($(OS),Windows_NT)
error:
	@echo "Error: OS is not Windows_NT"
endif

ifndef TERM
  ISCMDSHELL=yes
endif

ifndef MODEL_TPL
  ifeq ($(ISCMDSHELL),yes)
    MODEL_TPL=..\..\..\examples\admb\simple\simple.tpl
  else
    MODEL_TPL=../../../examples/admb/simple/simple.tpl
  endif
endif

IMAGE=admb
VERSION=windows

MODEL_DIR=$(dir $(MODEL_TPL))
MODEL_EXT=$(suffix $(MODEL_TPL))
MODEL_NAME=$(basename $(subst $(MODEL_DIR),,$(MODEL_TPL)))
ifeq ($(ISCMDSHELL),yes)
  MOUNT_DIR=$(shell echo %CD%)\\$(MODEL_NAME)
else
  MOUNT_DIR=$(shell cygpath --windows --absolute $(CURDIR)/$(MODEL_NAME))
endif

all: $(clean)
	$(MAKE) winlibs

msys2: msys2-x86_64.exe
	docker build --file Dockerfile-msys2-ltsc2022 -t $(IMAGE):$(VERSION)-ltsc2022-msys2 .
	docker build --file Dockerfile-msys2-ltsc2019 -t $(IMAGE):$(VERSION)-ltsc2019-msys2 .

winlibs: admb-main.zip winlibs.zip
	docker build --file Dockerfile-winlibs-ltsc2022 -t $(IMAGE):$(VERSION)-ltsc2022-winlibs .
	docker build --file Dockerfile-winlibs-ltsc2019 -t $(IMAGE):$(VERSION)-ltsc2019-winlibs .

msys2-x86_64.exe:
	powershell Invoke-WebRequest -Uri https://github.com/msys2/msys2-installer/releases/download/2023-07-18/msys2-x86_64-20230718.exe -OutFile msys2-x86_64.exe

admb-main.zip:
	powershell Invoke-WebRequest -Uri https://github.com/admb-project/admb/archive/refs/heads/main.zip -OutFile admb-main.zip

winlibs.zip:
	powershell Invoke-WebRequest -Uri https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0mcf-16.0.6-11.0.1-ucrt-r2/winlibs-x86_64-mcf-seh-gcc-13.2.0-mingw-w64ucrt-11.0.1-r2.zip -OutFile winlibs.zip

run: $(MODEL_NAME)
	docker run --rm --volume $(MOUNT_DIR):c:\\$(MODEL_NAME) --workdir c:\\$(MODEL_NAME) $(IMAGE):$(VERSION) $(MODEL_NAME)$(MODEL_EXT)
ifeq ($(ISCMDSHELL),yes)
	cd $(MODEL_NAME) && $(MODEL_NAME)
else
	cd $(MODEL_NAME) && ./$(MODEL_NAME)
endif

console: $(MODEL_NAME)
	docker run -it --entrypoint cmd --rm --volume $(MOUNT_DIR):C:\\$(MODEL_NAME) --workdir C:\\$(MODEL_NAME) $(IMAGE):$(VERSION)

$(MODEL_NAME):
ifeq ($(ISCMDSHELL),yes)
	xcopy /I $(MODEL_DIR) $(MODEL_NAME)
else
	cp -R $(MODEL_DIR) .
endif

clean:
ifeq ($(ISCMDSHELL),yes)
	@if exist msys2-x86_64.exe del msys2-x86_64.exe
	@if exist admb-main.zip del admb-main.zip
	@if exist winlibs.zip del winlibs.zip
	@if exist rmdir /S /Q simple
else
	@rm -vf msys2-x86_64.exe
	@rm -vf admb-main.zip
	@rm -vf winlibs.zip
	@rm -vrf simple
endif
