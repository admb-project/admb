all:\
  QuickStartWindows.html\
  QuickStartWindowsSource.html\
  QuickStartVisualC++.html\
  QuickStartUnix.html\
  QuickStartUnixSource.html\
  QuickStartMacOS.html\
  QuickStartUbuntu14.html\
  CHANGES.html\
  INSTALL.html\
  LICENSE.html\
  README.html

QuickStartWindows.html: QuickStartWindowsSource.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartWindowsSource.html: QuickStartWindows.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartVisualC++.html: QuickStartVisualC++.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartUnix.html: QuickStartUnix.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartUnixSource.html: QuickStartUnixSource.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartMacOS.html: ../../scripts/installers/packagemaker/README.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartUbuntu14.html: ../../scripts/installers/dpkg/README.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

CHANGES.html: ../../CHANGES.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

INSTALL.html: ../../INSTALL.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

README.html: ../../README.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

LICENSE.html: ../../LICENSE.txt
	cat begin.html>$@
	markdown_py $^>>$@
	cat end.html>>$@

clean:
	rm -vf QuickStartWindows.html QuickStartVisualC++.html QuickStartUnix.html
	rm -vf CHANGES.html INSTALL.html README.html LICENSE.html
	rm -vf QuickStartMacOS.html
