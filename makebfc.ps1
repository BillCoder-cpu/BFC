#rem Purpose:
#rem 	Make the complete BFC set of libraries using make.

echo .
echo Making BFC...
cd BFC\win
make -k $args[0] 2> err.out
type err.out
cd ..\..

echo .
echo Making BFCScript...
cd BFCScript\win
make -k $args[0] 2> err.out
type err.out | more
cd ..\..

echo .
echo Making BFCGui...
cd BFCGUI\win
make -k $args[0] 2> err.out
type err.out | more
cd ..\..

echo .
echo Making BFCOS...
cd BFCOS\win
make -k $args[0] 2> err.out
type err.out | more
cd ..\..

#rem echo .
#rem echo Making BFCImage...
#rem cd BFCImage\win
#rem make -k $1 2> err.out
#rem type err.out | more
#rem cd ..\..



