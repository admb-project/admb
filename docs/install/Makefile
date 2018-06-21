all:\
  QuickStartWindows.html\
  QuickStartWindowsZip.html\
  QuickStartWindowsSource.html\
  QuickStartVisualC.html\
  QuickStartVisualCZip.html\
  QuickStartVisualCSource.html\
  QuickStartUnix.html\
  QuickStartUnixSource.html\
  QuickStartMacOS.html\
  QuickStartUbuntu14.html\
  CHANGES.html\
  INSTALL.html\
  LICENSE.html\
  README.html

htmls:\
	mkdir -p htmls
	mv QuickStartWindows.html htmls
	mv QuickStartWindowsZip.html htmls
	mv QuickStartWindowsSource.html htmls
	mv QuickStartVisualC.html htmls
	mv QuickStartVisualCZip.html htmls
	mv QuickStartVisualCSource.html htmls
	mv QuickStartUnix.html htmls
	mv QuickStartUnixSource.html htmls
	mv QuickStartMacOS.html htmls
	mv QuickStartUbuntu14.html htmls
	mv CHANGES.html htmls
	mv INSTALL.html htmls
	mv LICENSE.html htmls
	mv README.html htmls

QuickStartWindows.html: QuickStartWindows.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartWindowsZip.html: QuickStartWindowsZip.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartWindowsSource.html: QuickStartWindowsSource.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartVisualC.html: QuickStartVisualC.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartVisualCZip.html: QuickStartVisualCZip.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartVisualCSource.html: QuickStartVisualCSource.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartUnix.html: QuickStartUnix.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartUnixSource.html: QuickStartUnixSource.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartMacOS.html: ../../scripts/installers/packagemaker/README.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

QuickStartUbuntu14.html: ../../scripts/installers/dpkg/README.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

CHANGES.html: ../../CHANGES.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

INSTALL.html: ../../INSTALL.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

README.html: ../../README.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

LICENSE.html: ../../LICENSE.txt
	cat begin.html>$@
	cat admarkdown.css>>$@
	cat begin2.html>>$@
	markdown_py $^>>$@
	cat end.html>>$@

clean:
	rm -rvf htmls
	rm -vf QuickStartWindows.html QuickStartVisualC.html QuickStartUnix.html
	rm -vf QuickStartVisualCZip.html
	rm -vf CHANGES.html INSTALL.html README.html LICENSE.html
	rm -vf QuickStartMacOS.html
	rm -vf QuickStartUbuntu14.html QuickStartUnixSource.html
	rm -vf QuickStartVisualCSource.html QuickStartWindowsSource.html
	rm -vf QuickStartWindowsZip.html
