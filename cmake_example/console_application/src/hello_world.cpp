#include <iostream>

int main() 
{
    std::cout << "Hello World!";

	// temporary solution -> bug in VS2017 present console window closes automatically 
	// https://developercommunity.visualstudio.com/t/start-without-debugging-does-not-keep-the-console/111915
	getchar();
	return 1;
}