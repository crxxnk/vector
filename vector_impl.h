#include <iostream>

template<typename T>
class vector
{
private:
    size_t _size;
    size_t _capacity;
    T* buffer;
public:
    auto size() noexcept -> size_t const { return _size; }
    auto capacity() noexcept -> size_t const { return _capacity; }
    auto empty() noexcept -> bool const { return size() == 0; }
    auto push_back(const T& val) -> void;
    auto reserve(size_t n) -> void;
    auto front() const -> T& { return buffer[0]; }
    auto back() const -> T& { return buffer[_size-1]; }
    T* operator=(const T& other);
    vector(size_t n, const T &val);
    vector();
    ~vector() noexcept;
};

template <typename T>
vector<T>::vector(size_t n, const T &val)
{
    _size = n;
    buffer = new T[n];
    // _capacity = 
}

template <typename T>
vector<T>::vector()
{
    _size = 0;
    buffer = 0;
    _capacity = 0;
}

template <typename T>
auto vector<T>::push_back(const T& val) -> void
{
    if(_size >= _capacity) {
        std::cout << "Difference: " << _size - _capacity << std::endl;
        size_t cap = _capacity ? _capacity * 2 : 1;
        reserve(cap);
    }
    // buffer[_size] = val;
    // size++;
    buffer[_size++] = val; // same as above
}

template <typename T>
auto vector<T>::reserve(size_t n) -> void
{
    if(n <= _capacity)
        return;

    T* buf = new T[n];
    buffer = buf;
    _capacity = n;

    for(size_t i = 0; i < _size; i++)
        buf[i] = buffer[i];

    delete[] buffer;
    buffer = buf;    
}

template <typename T>
T *vector<T>::operator=(const T &other)
{
    
}

template <typename T>
vector<T>::~vector() noexcept
{
    delete buffer;
    buffer = nullptr;
    _size = 0;
    _capacity = 0;
}