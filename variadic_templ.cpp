#include <iostream>

template<typename T>
void print (const std::string&& prefix, T arg)
{
    std::cout << "PRINT ONE "  << prefix << arg << "\n";
}

template<typename T, typename... Args>
void print(const std::string&& prefix, T& arg, Args&... args)
{
    std::cout << "PRINT MANY " << prefix << arg << " args size: " << sizeof...(args) << "\n";
    print(std::move(prefix), args...);
}

template<typename T>
auto sum(T arg1, T arg2)
{
    print<T>(std::move("SUM 2 argument template"), arg1, arg2);
    return arg1 + arg2;
}

// requires - add -fconcepts flague to the compiler
template<typename... Args>
auto sum(Args... args) requires (std::conjunction_v<std::is_integral<Args>...>)
{
    print<Args...>(std::move("SUM Variadic All-Int "), args...);
    return (args + ...);
}

template<typename... Args>
auto sum(Args... args)
{
    print<Args...>(std::move("SUM Variadic General "), args...);
    return (args + ...);
}

int main()
{
    const auto sum1 = sum(1, 2, 3, 4, 5);
    std::cout << "Sum1: " << sum1 << typeid(sum1).name() << std::endl;
    const auto sum2 = sum(1.5, 2.5, 3.5);
    std::cout << "Sum2: " << sum2 << typeid(sum2).name() << std::endl;
    const auto sum3 = sum(1, 2.5);
    std::cout << "Sum3: " << sum3 << typeid(sum3).name() << std::endl; // Cause of diffrent arg types calls variadic
    const auto sum4 = sum(1.2, 2.5);
    std::cout << "Sum4: " << sum4 << typeid(sum4).name() << std::endl; // same arg types calls Normal

    return 0;
}
