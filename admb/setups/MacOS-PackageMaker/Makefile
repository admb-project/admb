.PHONY: all

VERSION=9.1
DISTRIBUTION_NAME=ADMB-$(VERSION)

TIGER=10.4
LEOPARD=10.5
SNOW_LEOPARD=10.6
TARGET=$(LEOPARD)

CC=/Developer/Applications/Utilities/PackageMaker.app/Contents/MacOS/PackageMaker

all:
	rm -rvf admbinstaller
	mkdir -p admbinstaller/Applications 
	cp -Rvf ../../trunk/build/dists/admb_gcc411_fedora8 admbinstaller/Applications/admb
	cp admbinstaller/Applications/admb/README Resources/Welcome.txt
	cp admbinstaller/Applications/admb/LICENSE Resources/License.txt
	-$(CC) --verbose --title $(DISTRIBUTION_NAME) --root admbinstaller --id www.admb-project.org --resources Resources
