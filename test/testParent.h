#pragma once
class testParent {
    // make virtual functions for all functions to test (Eg: getSPO2)
    public:
        virtual int getSpO2()=0;
        virtual int getHR()=0;
};
