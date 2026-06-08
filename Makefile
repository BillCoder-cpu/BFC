
# all: BFC BFCGUI BFCOS BFCData BFCVector BFCImage BFCScript

all: BFC install

BFC: 
	./makebfc

install:
	./makebfc install	


