rootcint -f Dict.cxx -c SySalROOT.h LinkDef.h
g++ SySalROOT.cpp Dict.cxx -I/bin/root/root/include/ -L/bin/root/root/lib/ -ldl -lCore -lCint -lTree -lRFIO -fPIC -shared -o SySalROOT.so


