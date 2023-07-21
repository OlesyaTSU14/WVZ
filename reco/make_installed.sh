
setupATLAS
cd athena
asetup --restore
cd ../build
source x86_64-*/setup.sh
cmake ../athena/Projects/WorkDir && make

cd ../run/
