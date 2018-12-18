#include <iostream>
#include "Main.h"

void A_Native::f() {
	std::cout << "A(" << i << ")" << ".f()" << std::endl;
}

void A_Native::g() {
	std::cout << "A(" << i << ")" << ".g()" << std::endl;
}


void B_Native<int>::f() {
	std::cout << "B(" << i << ", " << j << ")" << ".f()" << std::endl;
}

void B_Native<int>::g() {
	std::cout << "B(" << i << ", " << j << ")" << ".g()" << std::endl;
}

void f_ia_native(IA *ia) {
	ia->f();
}

void f_ib_native(IB<void> *ib) {
	ib->g();
}

void f_a_native(A_Native *a) {
	f_ia_native(a);
	f_ib_native(a);
}

void f_b_native(B_Native<int> *b) {
	f_ia_native(b);
	f_ib_native(b);
}

// ------------------------------------------------------------------------------------

IMPLEMENT_BEGIN(IA, A)
	void f() override {
		std::cout << "A(" << self->i << ")" << ".f()" << std::endl;
	}
IMPLEMENT_END(IA, A)

IMPLEMENT_BEGIN(IB<void>, A)
	void g() override {
		std::cout << "A(" << self->i << ")" << ".g()" << std::endl;
	}
IMPLEMENT_END(IB<void>, A)

IMPLEMENT_BEGIN(IA, B<int>)
	void f() override {
		std::cout << "B(" << self->i << ", " << self->j << ")" << ".f()" << std::endl;
	}
IMPLEMENT_END(IA, B<int>)

IMPLEMENT_BEGIN(IB<void>, B<int>)
	void g() override {
		std::cout << "B(" << self->i << ", " << self->j << ")" << ".g()" << std::endl;
	}
IMPLEMENT_END(IB<void>, B<int>)

void f_ia(Interface<IA> ia) {
	ia->f();
}

void f_ib(Interface<IB<void>> ib) {
	ib->g();
}

void f_a(A *a) {
	f_ia(*a);
	f_ib(*a);
}

void f_b(B<int> *b) {
	f_ia(*b);
	f_ib(*b);
}

int main() {
	A_Native a_native(1);
	B_Native<int> b_native(2, 3);
	std::cout << "sizeof(A_Native)      = " << sizeof(A_Native) << std::endl;
	std::cout << "sizeof(B_Native<int>) = " << sizeof(B_Native<int>) << std::endl;
	std::cout << "--------------------" << std::endl;
	f_a_native(&a_native);
	std::cout << "--------------------" << std::endl;
	f_b_native(&b_native);
	std::cout << "--------------------" << std::endl;
	f_a_native(&b_native);
	//-------------------------------------
	std::cout << "\n\n" << std::endl;
	A a(1);
	B<int> b(2, 3);
	std::cout << "sizeof(A)      = " << sizeof(A) << std::endl;
	std::cout << "sizeof(B<int>) = " << sizeof(B<int>) << std::endl;
	std::cout << "--------------------" << std::endl;
	f_a(&a);
	std::cout << "--------------------" << std::endl;
	f_b(&b);
	std::cout << "--------------------" << std::endl;
	f_a(&b);
	return 0;
}