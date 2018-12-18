# Cpp-Interface-Example
Reduce interface-implemented class size
- Native syntax    : class size grow along with the amount of implemented interface
- This repo syntax : +4 byte for x86 or +8byte for x64
```cpp
class IA {
public:
	virtual void f() = 0;
};

template<typename T>
class IB {
public:
	virtual T g() = 0;
};

// x86 : sizeof(A_Native) = 12
// x64 : sizeof(A_Native) = 24
class A_Native : public IA, public IB<void> {
protected:
	int i;
public:
	inline A_Native(int i) : i(i) {};

	virtual void f();
	virtual void g();
};

// x86 : sizeof(B_Native<int>) = 16
// x64 : sizeof(B_Native<int>) = 32
template<typename T>
class B_Native : public A_Native {
protected:
	int j;
public:
	inline B_Native(int i, T j) : A_Native(i), j(j) {};

	void f() override;
	void g() override;
};

// x86 : sizeof(A) = 8  // sizeof(A_Native) - sizeof(A) = 4
// x64 : sizeof(A) = 16 // sizeof(A_Native) - sizeof(A) = 8
class A {
	INTERFACES_BEGIN
		INTERFACE(IA)
		INTERFACE(IB<void>)
	INTERFACES_END
	int i;
public:
	inline A(int i) : i(i) {};
};

// x86 : sizeof(B<int>) = 12 // sizeof(B_Native<int>) - sizeof(B<int>) = 4
// x64 : sizeof(B<int>) = 24 // sizeof(B_Native<int>) - sizeof(B<int>) = 8
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
```
