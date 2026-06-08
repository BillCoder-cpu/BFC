
#!/bin/bash
#
# Name: makebfc.sh
#
# Purpose:
#		Make the complete BFC set of libraries using make.
#
# Notes:
#
# Return codes:
#  0 = All commands were successful
#  1 = At least one command failed, see the output file
#      and search for the keyword "ERROR".
#
########################################################



cd BFC
make 2> err.out
cat err.our | more
cd ..

cd Local
make 2> err.out
cat err.our | more
cd ..

cd BCImage
make 2> err.out
cat err.our | more
cd ..

cd BCUtil
make 2> err.out
cat err.our | more
cd ..

cd UI
make 2> err.out
cat err.our | more
cd ..



