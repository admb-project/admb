all: admb-seqdiag.png admb-blockdiag.png

admb-seqdiag.png: admb-seqdiag
	seqdiag admb-seqdiag

admb-blockdiag.png: admb-blockdiag
	blockdiag -f /Library/Fonts/AppleGothic.ttf admb-blockdiag

clean:
	@rm -vf admb-blockdiag.png
	@rm -vf admb-seqdiag.png
