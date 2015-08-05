LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../DigitalScope/qwt-6.1/lib/:./DigitalScope/qwt-6.1/lib/
rm DigitalScope
make;
#./DigitalScope SERIAL=/dev/ttyUSB0
./DigitalScope SIMULATION=100
