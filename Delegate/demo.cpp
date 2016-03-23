
//#include "Delegate.h"
#include "DelegateList.h"
#include <iostream>

using namespace std::placeholders;

//class to test delegates on
class Car{
public:
	void addSpeed(int amount){
		speed += amount;

		if (speed > maxSpeed)
			maxSpeed = speed;

		if (speed < 0)
			speed = 0;
	}

	int getSpeed(){
		return speed;
	}

	int getMaxSpeed(){
		return maxSpeed;
	}

private:
	int speed = 0, maxSpeed = 0;
};

//some more functions for the examples
void helloWorld(){
	std::cout << "Hello World" << std::endl;
}

void goodByeWorld(){
	std::cout << "GoodBye World" << std::endl;
}

float sum(int a , float b, char c){
	return a + b + c;
}


//prin a heading so console text is easier to read
void printHeading(std::string head){
	std::cout << std::endl
 << head << std::endl
		<< "==========================" << std::endl;
}

int main()
{
	//static void function
	printHeading("Basic delegate");
	ultimate::Delegate<void> myDel_1;
	myDel_1.set(&helloWorld);
	myDel_1.run();


	//calling a function within an object and passing an argument
	printHeading("Calling a function within an object with arguments");
	Car *car = new Car();
	ultimate::Delegate<void, int> myDel_2;
	myDel_2.set(std::bind(&Car::addSpeed, car, _1));
	myDel_2.run(10);
	std::cout << "Car speed: " << car->getSpeed() << std::endl;

	int sign=1;
	for (unsigned int i = 0; i < 5; i++)
	{
		sign *= -1;
		myDel_2.run(10*i*sign);
		std::cout << "Car speed: " << car->getSpeed() << std::endl;
	}


	//delegate return a value
	printHeading("Delegate returning a value");
	ultimate::Delegate<int> myDel_3;
	myDel_3.set(std::bind(&Car::getMaxSpeed, car));
	int max = myDel_3.run();
	std::cout << "Max Car speed: " << max << std::endl;


	printHeading("Multiple argument types");
	ultimate::Delegate<float, int, float, char> myDel_4;
	myDel_4.set(&sum);
	float total = myDel_4.run(10, 2.5f, 'a');
	std::cout << "total sum:" << total << std::endl;


	//basic use of delegate list
	printHeading("Use of delegate list");

	ultimate::DelegateList<void> delList;
	delList.add(myDel_1, "hello-world");
	delList.add(myDel_1, "hello-world");
	delList.add(myDel_1, "something-else");
	delList.runAll();


	printHeading("Remove from delegate list");

	ultimate::Delegate<void> myDel_5;
	myDel_5.set(&goodByeWorld);
	delList.add(myDel_5, "goodbye");
	delList.removeWithTag("hello-world");
	delList.runAll();



	printHeading("Run with tag");

	delList.runWithTag("goodbye");
	delList.clear();

	return 0;
}

