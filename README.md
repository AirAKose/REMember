# REMember
 Class member access wrapper utility for getting members from member pointers, primarily for nested members of composed objects

# Usage
    struct A { int i; }
    struct B { A a; }
    
    using i_indirect = member<&B::a, &A::i>; // same as B{}.a.i
    
    B elem{24};
    auto& i = i_indirect::get_ref(elem);
    
    std::cout << i << "\n"; // output: 24
    
    i = 54;
    
    std::cout << elem.a.i << "\n"; // output: 54
