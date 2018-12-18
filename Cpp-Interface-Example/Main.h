#pragma once

#include "Interface.h"

class IA {
public:
	virtual void f() = 0;
};

template<typename T>
class IB {
public:
	virtual T g() = 0;
};

class A_Native : public IA, public IB<void> {
protected:
	int i;
public:
	inline A_Native(int i) : i(i) {};

	virtual void f();
	virtual void g();
};

template<typename T>
class B_Native : public A_Native {
protected:
	int j;
public:
	inline B_Native(int i, T j) : A_Native(i), j(j) {};

	void f() override;
	void g() override;
};

class A {
	INTERFACES_BEGIN
		INTERFACE(IA)
		INTERFACE(IB<void>)
	INTERFACES_END
	int i;
public:
	inline A(int i) : i(i) {};
};

template<typename T>
class B : public A {
	INTERFACES_BEGIN
		INTERFACE(IA)
		INTERFACE(IB<void>)
	INTERFACES_END
	T j;
public:
	inline B(int i, T j) : A(i), j(j) {};
};