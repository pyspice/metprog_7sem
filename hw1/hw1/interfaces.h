#pragma once

#include <string>
using std::string;

class IInteractor
{
public:
	virtual string getInteractorType() const
	{
		return "IInteractor";
	};
};

class IValueStorage;

class IMediator
{
public:
	virtual void sendValue(const string& value, const IValueStorage* sender) const = 0;
};

class IObserver
{
public:
	virtual void onTrimValue(IValueStorage* dependent) const = 0;
};

class IValueStorage
{
public:
	virtual string getName() const = 0;

	// Proxy interface
	virtual void setValue(const string& value) = 0;
	virtual const string& getValue() const = 0;

	// Mediator Interface
	virtual void setMediator(IMediator* mediator) = 0;
	virtual void sendValue() const = 0;
	virtual void receiveValue(const string& value) const = 0;

	// Observer interface
	virtual void setObserver(IObserver* observer) = 0;
	virtual void trimValue() = 0;
};