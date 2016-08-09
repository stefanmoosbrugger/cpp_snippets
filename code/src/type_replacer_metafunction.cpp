#include <typeinfo>
#include <iostream>

template <typename Replacement, typename ToReplace, typename C>
struct type_replace;

template <typename T>
struct type_replace<T,T,T> {
	using type = T;
};

template <typename T, typename V>
struct type_replace<T,V,T> {
	using type = V;
};

template <typename T, typename V>
struct type_replace<T,V,V> {
	using type = V;
};

template <typename T, typename V, typename C>
struct type_replace<T,V,C*> {
	using type = typename type_replace<T,V,C>::type*;
};

template <typename T, typename V, typename C>
struct type_replace<T,V,C&> {
	using type = typename type_replace<T,V,C>::type&;
};

template <typename T, typename V, typename C>
struct type_replace<T,V,C const> {
	using type = typename type_replace<T,V,C>::type const;
};

template <typename T, typename V, typename R, typename... Args>
struct type_replace<T,V,R (Args...)> {
	using type = typename type_replace<T,V,R>::type (typename type_replace<T,V,Args>::type...); 
};

template <typename T, typename V, typename R, typename Base, typename... Args>
struct type_replace<T,V,R (Base::*) (Args...)> {
	using type = typename type_replace<T,V,R>::type (Base::*) (typename type_replace<T,V,Args>::type...); 
};

template <typename T, typename V, typename C>
using type_replace_t = typename type_replace<T,V,C>::type;

int f(int a, float b) {
	return 0;	
}

struct S {
	int mf(int a, float b) { return 0; } 
};

template <typename T>
struct Error {
	typename T::Error v;
};

int main() {
	std::cout << "i2f: " << typeid(type_replace_t<int,float,int>).name() << std::endl;
	std::cout << "i2d: " << typeid(type_replace_t<int,double,int>).name() << std::endl;
	std::cout << "i2c: " << typeid(type_replace_t<int,char,int>).name() << std::endl;

	std::cout << "ip2fp: " << typeid(type_replace_t<int,float,int*>).name() << std::endl;
	std::cout << "ip2dp: " << typeid(type_replace_t<int,double,int*>).name() << std::endl;
	std::cout << "ip2cp: " << typeid(type_replace_t<int,char,int*>).name() << std::endl;

	std::cout << "ir2fr: " << typeid(type_replace_t<int,float,int&>).name() << std::endl;
	std::cout << "ir2dr: " << typeid(type_replace_t<int,double,int&>).name() << std::endl;
	std::cout << "ir2cr: " << typeid(type_replace_t<int,char,int&>).name() << std::endl;

	std::cout << "icr2fcr: " << typeid(type_replace_t<int,float,int const&>).name() << std::endl;
	std::cout << "icr2dcr: " << typeid(type_replace_t<int,double,int const&>).name() << std::endl;
	std::cout << "icr2ccr: " << typeid(type_replace_t<int,char,int const&>).name() << std::endl;
	
	std::cout << "fti2ftf: " << typeid(type_replace_t<int, float, decltype(f)>).name() << std::endl;
	std::cout << "mfti2mftf: " << typeid(type_replace_t<int, float, decltype(&S::mf)>).name() << std::endl;
	Error<std::remove_pointer<decltype(&S::mf)>::type> e;
	return 0;
}
