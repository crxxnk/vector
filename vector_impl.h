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
    auto begin() const -> T* { return buffer; }
    auto end() const -> T* { return buffer + _size; /*or &buffer[_size]*/ }
    auto operator=(vector&& other) -> vector&;
    auto at(size_t index) -> T&;
    auto assign(size_t count, const T& val) -> void;
    auto assign(T* begin, T* end) -> void;
    vector(size_t n, const T &&val);
    vector();
    ~vector() noexcept;
};

template <typename T>
vector<T>::vector(size_t n, const T &&val)
{
    _size = 0;
    _capacity = 0;
    buffer = nullptr;
    assign(n, val);
}

template <typename T>
vector<T>::vector()
{
    _size = 0;
    buffer = nullptr;
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
    std::cout << "pushed" << std::endl;
}

template <typename T>
auto vector<T>::reserve(size_t n) -> void
{
    if(n <= _capacity)
        return;

    T* old_buf = buffer;
    buffer = new T[n];
    _capacity = n;

    for(size_t i = 0; i < _size; i++)
        buffer[i] = old_buf[i];

    delete[] old_buf;
}

template <typename T>
auto vector<T>::operator=(vector &&other) -> vector&
{
    delete[] buffer;
    _size = other._size;
    _capacity = other._capacity;
    buffer = new T[_size];
    for(size_t i = 0; i < _capacity; i++)
        buffer[i] = other[i];
    buffer = other.buffer;
    other.buffer = nullptr;
    return *this;
}

template <typename T>
auto vector<T>::at(size_t index) -> T&
{
    if(index > _size-1)
        throw std::out_of_range("Tried to access vector element at index " + std::to_string(index));
    
    return buffer[index];
}

template <typename T>
auto vector<T>::assign(size_t count, const T& val) -> void
{
    while(count > _capacity) {
        size_t cap = _capacity ? _capacity * 2 : 1;
        reserve(cap);
    }

    for(size_t i = 0; i < count; i++)
        buffer[i] = val;

    _size = count;
}

template <typename T>
auto vector<T>::assign(T* begin, T* end) -> void
{
    size_t i = 0;
    for(T* it = begin; it != end; it++) {
        if(i >= _capacity) {
            size_t cap = _capacity ? _capacity * 2 : 1;
            reserve(cap);
        }
        buffer[i] = *it;
        i++;
    }
    _size = i;
}

template <typename T>
vector<T>::~vector() noexcept
{
    delete[] buffer;
    buffer = nullptr;
    _size = 0;
    _capacity = 0;
}