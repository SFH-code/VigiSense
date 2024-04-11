#include "DeviceSubscriber.cpp"

int main(
        int,
        char**)
{
    std::cout << "Starting subscriber. Press any key to stop it." << std::endl;

    DeviceSubscriber mysub;
    if(!mysub.init())
    {
	std::cerr << "Could not init the subscriber." << std::endl;
	return -1;
    }

    // do nothing here
    getchar();

    return 0;
}
