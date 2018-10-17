#pragma once

#include <iostream>
#include <string>
#include <exception>
#include "interfaces.h"

using namespace std;

class CValueStorage : public IValueStorage
{
public:
	explicit CValueStorage(const string& name, const string& value) : name_(name), value_(value) {}

	virtual string getName() const override 
	{
		return name_;
	}

	// Proxy interface
	virtual void setValue(const string& value) override
	{
		cout << "Setting " << getName() << "'s value as: " << value << "\n\n";
		value_ = value;
	};

	virtual const string& getValue() const override
	{
		cout << "Getting " << getName() << "'s value\n\n";
		return value_;
	};

	// Mediator Interface
	virtual void setMediator(IMediator* mediator) override
	{
		mediator_ = mediator;
	}

	virtual void sendValue() const override
	{
		if (mediator_ == NULL)
			return;

		cout << "Sending " << getName() << "'s value\n";
		mediator_->sendValue(value_, this);
	}

	virtual void receiveValue(const string& value) const override
	{
		cout << "Receiving value '" << value << "' in " << getName() << "\n\n";
	}

	// Observer interface
	virtual void setObserver(IObserver* observer) override
	{
		observer_ = observer;
	}

	virtual void trimValue()
	{
		if (observer_ == NULL)
			return;

		cout << "Trimming " << getName() << "'s value\n";
		observer_->onTrimValue(this);
	}

private:
	string name_;
	string value_;
	IMediator* mediator_;
	IObserver* observer_;
};

class Proxy : public IInteractor
{
public:
	Proxy(CValueStorage* foo, CValueStorage* bar) : foo_(foo), bar_(bar) {}

	virtual string getInteractorType() const override
	{
		return "Proxy";
	}

	void setFoo(string value)
	{
		cout << "Proxying setFoo call\n";
		foo_->setValue(value);
	}

	void getFoo()
	{
		cout << "Proxying getFoo call\n";
		foo_->getValue();
	}

	void setBar(string value)
	{
		cout << "Proxying setBar call\n";
		bar_->setValue(value);
	}

	void getBar()
	{
		cout << "Proxying getBar call\n";
		bar_->getValue();
	}

private:
	CValueStorage* foo_;
	CValueStorage* bar_;

	Proxy() = delete;
};

class Mediator : public IMediator, public IInteractor
{
public:
	Mediator(CValueStorage* foo, CValueStorage* bar) : foo_(foo), bar_(bar) {}

	virtual string getInteractorType() const override
	{
		return "Mediator";
	}

	virtual void sendValue(const string& value, const IValueStorage* sender) const override
	{
		IValueStorage* receiver = (sender == foo_ ? static_cast<IValueStorage*>(bar_)
												  : static_cast<IValueStorage*>(foo_));

		cout << "Passing value '" << value << "' from " << sender->getName() << " to " << receiver->getName() << "\n";
		receiver->receiveValue(value);
	}

private:
	CValueStorage* foo_;
	CValueStorage* bar_;

	Mediator() = delete;
};

class Observer : public IObserver, public IInteractor
{
public:
	Observer(CValueStorage* foo, CValueStorage* bar) {}

	virtual string getInteractorType() const override
	{
		return "Observer";
	}

	virtual void onTrimValue(IValueStorage* dependent) const override
	{
		cout << "Trimmed value in dependent '" << dependent->getName() << "'\n";
	}
};

class BadInteractorType : public exception
{
public:
	BadInteractorType(string InteractorType) : InteractorType_(InteractorType) {}

	virtual const char * what() const 
	{
		string msg = "Cannot recognize interactor type '" + InteractorType_ +"'";
		return msg.c_str(); 
	}

private:
	string InteractorType_;
};

template <class Interactor>
class Frankenstein
{
public:
	static IInteractor* get(CValueStorage* foo, CValueStorage* bar)
	{
		auto interactor = new Interactor(foo, bar);
		string InteractorType = interactor->getInteractorType();
		if (InteractorType == "Mediator")
		{
			foo->setMediator(dynamic_cast<IMediator*>(interactor));
			bar->setMediator(dynamic_cast<IMediator*>(interactor));
		}
		else if (InteractorType == "Observer")
		{
			foo->setObserver(dynamic_cast<IObserver*>(interactor));
			bar->setObserver(dynamic_cast<IObserver*>(interactor));
		}
		else if (InteractorType != "Proxy")
		{
			throw new BadInteractorType(InteractorType);
		}
		return interactor;
	}

private:
	Frankenstein() = delete;
};