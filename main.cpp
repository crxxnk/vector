#include "vector_impl.h"

int main()
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    auto pos = vec.insert(vec.begin() + 1, 123);

    for(size_t i = 0; i < vec.size(); i++)
        std::cout << vec.at(i) << std::endl;

    std::cout << std::endl;

    vec.erase(vec.begin(), vec.begin() + 2);

    for(size_t i = 0; i < vec.size(); i++)
        std::cout << vec.at(i) << std::endl;
    
    return 0;
}