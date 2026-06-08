@echo off
rem Purpose:
rem 	Make the complete BFC set of libraries using make.

echo .
echo Making BFC...
cd BFC\MinGw
make -k %1 2> err.out
type err.out
cd ..\..

echo .
echo Making BFCData...
cd BFCData\MinGW
make -k %1 2> err.out
type err.out | more
cd ..\..

echo .
echo Making BFCScript...
cd BFCScript\MinGW
make -k %1 2> err.out
type err.out | more
cd ..\..


