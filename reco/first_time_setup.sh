setupATLAS
lsetup git
git atlas init-workdir https://:@gitlab.cern.ch:8443/atlas/athena.git
mkdir build run
cd athena

asetup Athena,23.0.15,here
#asetup --restore

git atlas addpkg TrkiPatFitter
git atlas addpkg TrkiPatFitterUtils 

# you can add any Athena pkg

git fetch upstream
# git links of the above packages
#https://gitlab.cern.ch/atlas/athena/-/tree/master/Tracking/TrkFitter/TrkiPatFitter
#https://gitlab.cern.ch/atlas/athena/-/tree/master/Tracking/TrkFitter/TrkiPatFitterUtils

git checkout -b my-dev_some_name upstream/23.0.15 --no-track

cd ../build/
#source x86_64-*/setup.sh
cmake ../athena/Projects/WorkDir && make

cd ../
