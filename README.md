# Microbit_HTTP_Proxy
This application is designed for use in embedded devices like raspberry PIs, the application will poll for serialdata from a connected device, if it receives any it will then check if the period of time is correct and then if both those conditions are met it will send an HTTP response to a webserver. 

The app will also be able to update it's active time period from an HTTP request too

## Configuration
I've used three external libraries:

## * [boost](https://github.com/boostorg/boost) 

## * [poco](https://github.com/pocoproject/poco) 

## * [CPR](https://github.com/libcpr/cpr)


You will need to edit the device in `Microbit_HTTP_Proxy/ConsoleApplication1/ConsoleApplication1.cpp` to the port that that the device is connected to


