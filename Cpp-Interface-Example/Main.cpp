#include <iostream>
#include "Main.h"

void A_Native::f() {
	std::cout << "A(" << i << ")" << ".f()" << std::endl;
}

void A_Native::g() {
	std::cout << "A(" << i << ")" << ".g()" << std::endl;
}

void A_Native::h() {
	std::cout << "A(" << i << ")" << ".h()" << std::endl;
}

void B_Native<int>::f() {
	std::cout << "B(" << i << ", " << j << ")" << ".f()" << std::endl;
}

void B_Native<int>::g() {
	std::cout << "B(" << i << ", " << j << ")" << ".g()" << std::endl;
}

void B_Native<int>::h() {
	std::cout << "B(" << i << ", " << j << ")" << ".h()" << std::endl;
}

void f_ia_native(IA *ia) {
	ia->f();
}

void f_ic(IC *ic) {
	ic->h();
}

void f_ib_native(IB_Native<void> *ib) {
	ib->g();
	f_ic(ib);
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
	void f() {
		std::cout << "A(" << self->i << ")" << ".f()" << std::endl;
	}
IMPLEMENT_END(IA, A)

IMPLEMENT_BEGIN(IC, A)
void h() {
	std::cout << "A(" << self->i << ")" << ".h()" << std::endl;
}
IMPLEMENT_END(IC, A)

IMPLEMENT_BEGIN(IB<void>, A)
	void g() {
		std::cout << "A(" << self->i << ")" << ".g()" << std::endl;
	}

	Interface<IC> as_IC() {
		return INTERFACE_CAST(IC, A, self);
	}
IMPLEMENT_END(IB<void>, A)

IMPLEMENT_BEGIN(IA, B<int>)
	void f() {
		std::cout << "B(" << self->i << ", " << self->j << ")" << ".f()" << std::endl;
	}
IMPLEMENT_END(IA, B<int>)

IMPLEMENT_BEGIN(IC, B<int>)
void h() {
	std::cout << "B(" << self->i << ", " << self->j << ")" << ".h()" << std::endl;
}
IMPLEMENT_END(IC, B<int>)

IMPLEMENT_BEGIN(IB<void>, B<int>)
	void g() {
		std::cout << "B(" << self->i << ", " << self->j << ")" << ".g()" << std::endl;
	}

	Interface<IC> as_IC() {
		return INTERFACE_CAST(IC, B<int>, self);
	}
IMPLEMENT_END(IB<void>, B<int>)

void f_ia(Interface<IA> ia) {
	ia->f();
}

void f_ic(Interface<IC> ic) {
	ic->h();
}

void f_ib(Interface<IB<void>> ib) {
	ib->g();
	f_ic(ib->as_IC());
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