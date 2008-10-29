MAKEFILENAME=optbor55.mak
MAKEFILENAMES=safbor55.mak

.PHONY: nh99  tools99 df1b2 linad99

all: nh99  tools99 df1b2 linad99 

nh99:
	$(MAKE) -C nh99 -f $(MAKEFILENAME)

tools99:
	$(MAKE) -C tools99 -f $(MAKEFILENAME)

df1b2:
	$(MAKE) -C df1b2 -f $(MAKEFILENAME)
	$(MAKE) -C df1b2 -f $(MAKEFILENAMES)

linad99:
	$(MAKE) -C linad99 -f $(MAKEFILENAMES)
	$(MAKE) -C linad99 -f $(MAKEFILENAME)

