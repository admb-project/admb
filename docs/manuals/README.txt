Install smallcap.sty

1. Download the package from CTAN using link below.

   https://ctan.org/tex-archive/macros/latex/contrib/smallcap

2. Extract the files and place them in an appropriate directory.

   $ mkdir -p  /usr/local/share/texmf/tex/latex/misc
   $ cd /usr/local/share/texmf/tex/latex/misc
   $ unzip ~/Downloads/smallcap.zip

3. Update the ls-R file in this source tree to make system aware of new package.

   $ cd /usr/local/share/texmf
   $ sudo mktexlsr

Making the ADMB manuals with LaTeX

1. Read http://en.wikibooks.org/wiki/LaTeX/Packages/Installing_Extra_Packages

2. Determine where the "right" place is for your LaTeX installation. It will be
   something like /usr/share/texmf/tex/latex

3. Determine the name of the LaTeX indexing utility for your installation.

4. Edit admbmanual/Makefile and change the varibles as required.

   LATEX_PATH=
   INDEXER=

5. Run make INSTALLATION as superuser. This step will install the Dangerous
   Curve ADMB style package in the "right" place. You should only have to this
   step once (unless there are some changes to the package).

6. Run make clean to get rid of various files that don't matter much.

7. Run make to make the standard ADMB manuals.

8. Or run make ALL to make the manuals for manual writers as well as the
   standard ADMB manuals.
