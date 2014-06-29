#include <iostream>
#include <tuple>

template<class T, class ...U>
struct Tuple
{
    std::tuple<T, U...> operator()(T && a, U &&...b){
        return std::tuple<T, U...> { a, b... };
    }
};

int main()
{
    Tuple<std::st
}
