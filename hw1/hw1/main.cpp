#include <iostream>
#include <string>
#include "classes.h"

using namespace std;

int main()
{
	CValueStorage* foo = new CValueStorage("Foo", "Foo value");
	CValueStorage* bar = new CValueStorage("Bar", "Bar value");

	Proxy* proxy = dynamic_cast<Proxy*>(Frankenstein<Proxy>::get(foo, bar));
	proxy->getFoo();
	proxy->getBar();
	proxy->setFoo("   New foo value ");
	proxy->setBar("	New bar value    ");

	Mediator* mediator = dynamic_cast<Mediator*>(Frankenstein<Mediator>::get(foo, bar));
	foo->sendValue();
	bar->sendValue();

	Observer* observer = dynamic_cast<Observer*>(Frankenstein<Observer>::get(foo, bar));
	foo->trimValue();
	foo->getValue();
	bar->trimValue();
	bar->getValue();

	system("pause");
}