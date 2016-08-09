#include <tuple>
#include <iostream>

/* Helper struct that is needed to iterate over an std tuple of arrays in order to initialize a stack array. */
template<typename Lambda, std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
execute_lambda_on_tuple(std::tuple<Tp...> const& t, Lambda const& l) { }

template<typename Lambda, std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
execute_lambda_on_tuple(std::tuple<Tp...> const& t, Lambda const& l) { 
    l(std::get<I>(t));
    execute_lambda_on_tuple<Lambda, I+1, Tp...>(t, l);
}

struct S {
    void print(int i) {
        std::cout << "S: " << i << std::endl; 
    }
};

int main() {
    std::tuple< std::array< S, 3>, std::array<S, 2>, std::array<S, 1> > some_tuple;
    unsigned i=0;
    execute_lambda_on_tuple(some_tuple, [&](auto& tuple_elem) { 
        for(auto e : tuple_elem) {
            e.print(i++);
        }
    });
    return 0;    
}
