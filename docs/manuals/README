Making the ADMB manuals with LaTeX

1. read http://en.wikibooks.org/wiki/LaTeX/Packages/Installing_Extra_Packages

2. determine where the "right" place is for your LaTeX instalation. It 
will be something like /usr/share/texmf/tex/latex

3. determine the name of the LaTeX indexing utility for your installation.

4. edit admbmanual/Makefile and change the varibles as required
LATEX_PATH=
INDEXER=

5. run make INSTALLATION as superuser. 
This step will install the Dangerous Curve ADMB style package in the "right" 
place. You should only have to this step once (unless there are some 
changes to the package).

6. run make clean to get rid of various files that don't matter much.

7. run make to make the standard admb manuals

8. or run make ALL to make the manuals for manual writers as well as 
the standard admb manuals.
