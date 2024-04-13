# Real-Time-Project

Welcome to the Wiki page for VigiSense. VigiSense is a real-time embedded system that helps in the detection of anomalies in human conditions and provides an interface for appropriate action. This Wiki covers software and hardware design decisions and considerations made when implementing each function.

For more detailed structure on code, please read the files in the doc folder.~

Sensor used: MAX30102 for SP02 and Heart rate tracking.

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.teachmemicro.com%2Fwp-content%2Fuploads%2F2021%2F07%2Frcwl-0531-max30102-black.png&f=1&nofb=1&ipt=9ff3e6a089094f3931a784f4827127560ea252566191e61f5f050404fc3fe3a1&ipo=images" width="50%">

To run:
```
git clone [repo URL]
cd src
mkdir build
cd build
cmake ..
make
```

The repo contains code for:
MAX30102 library (edited from: https://github.com/garrettluu/max30102-rpi/tree/08b8e2aa917817f8e57aca7f04da4b7b1180f17a)

Added real time functionalities such as interrupt calls instead of using polling as shown in the MAX30102 library
> TODO add implementation specific code

SPO2 class
> TODO add implementation specific code

HR class
> TODO add implementation specific code

