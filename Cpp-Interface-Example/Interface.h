#pragma once

#define INTERFACES_BEGIN public:

#define INTERFACE(t) virtual operator Interface<t>();

#define INTERFACE_CAST(i, t, v) *reinterpret_cast<Interface<i>*>(&Implement<i, t>(v))

#define INTERFACES_END										\
	private:												\
	template<typename, typename> friend class Implement;

#define IMPLEMENT_BEGIN(i, t)								\
	template<>												\
	class Implement<i, t> : public ImplementBase<i, t> {	\
	public:													\
		using ImplementBase::ImplementBase;

#define IMPLEMENT_END(i, t)					\
	};										\
											\
	t::operator Interface<i>() {			\
		return INTERFACE_CAST(i, t, this);	\
	}

template<typename I>
class Interface {
protected:
	void *_vtable;
	void *_data;
public:
	inline I* operator->() {
		return reinterpret_cast<I*>(this);
	}
};

template<typename I, typename T>
class ImplementBase : public I {
protected:
	T *self;
public:
	ImplementBase(T *self) : self(self) {}
};

template<typename, typename>
class Implement;