#include <iostream>
#include "../inc/type_traits.hpp"
#include "../inc/member.hpp"

struct A { int i{ 25 }; };
struct B { A a{}; };
struct C : public B { int i; };

struct D { A* a{ nullptr }; };

int main()
{
    using i_indirect = member<&B::a, &A::i>;

    B elem{ 32 };
    auto& i = i_indirect::get_ref(elem);
    std::cout << i << std::endl;                            // output: 32
    std::cout << typeid(decltype(i)).name() << std::endl;   // output: int

    i = 54;

    std::cout << elem.a.i << std::endl;                     // output: 54

    C c{ 24 };
    auto& ci = i_indirect::get_ref(c);

    std::cout << ci << std::endl;                           // outputs: 24

    return 0;
}