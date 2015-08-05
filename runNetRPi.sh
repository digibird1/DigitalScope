LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../DigitalScope/qwt-6.1/lib/:./qwt-6.1/lib/
rm DigitalScope
make;
./DigitalScope NETWORK=192.168.1.111:12345
