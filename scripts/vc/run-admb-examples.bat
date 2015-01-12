set ADMB_PROJECTS=%HOMEDRIVE%%HOMEPATH%\My Documents\ADMB Projects
mkdir "%ADMB_PROJECTS%\examples"
xcopy "%ADMB_HOME%\examples\admb" "%ADMB_PROJECTS%\examples" /s /i
cd "%ADMB_PROJECTS%\examples"
nmake
