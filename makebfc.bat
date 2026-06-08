@echo off 
rem Purpose:
rem 	Make the complete BFC set of libraries using make.

echo off
echo .
echo Making BFC...
cd BFC\win
echo on
make -k %1 2> err.out
type err.out
@echo off
cd ..\..

echo .
echo Making BFCData...
cd BFCData\win
make -k %1 2> err.out
type err.out | more
cd ..\..

echo .
echo Making BFCScript...
cd BFCScript\win
make -k %1 2> err.out
type err.out | more
cd ..\..


echo .
echo Making BFCGui...
cd BFCGUI\win
make -k %1 2> err.out
type err.out | more
cd ..\..


echo .
echo Making BFCOS...
cd BFCOS\win
make -k %1 2> err.out
type err.out | more
cd ..\..

echo .
echo Making BFCVector...
cd BFCVector
make -k %1 2> err.out
type err.out | more
cd ..

echo .
echo Making BFCImage...
cd BFCImage\win
make -k %1 2> err.out
type err.out | more
cd ..\..



