rem # Name: makescript.bat
rem #
rem # Purpose:
rem #	Make a partial BFC set of libraries using make.
rem #
rem ########################################################


echo .
echo Making BFCScript...
cd BFCScript\win
make -k %1 2> err.out
type err.out
cd ..\..

echo .
echo Making BFCGui...
cd BFCGUI\win
make -k %1 2> err.out
type err.out
cd ..\..

echo .
echo Making BFCOS...
cd BFCOS\win
make -k %1 2> err.out
type err.out
cd ..\..

echo .
echo Making BFCImage...
cd BFCImage\win
make -k %1 2> err.out
type err.out
cd ..\..



