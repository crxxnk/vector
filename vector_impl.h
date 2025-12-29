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
    auto empty() noexcept -> bool const { return _size == 0; }
    auto push_back(const T& val) -> void;
    auto reserve(size_t n) -> void;
    auto front() const -> T& { return buffer[0]; }
    auto back() const -> T& { return buffer[_size-1]; }
    auto begin() const -> T* { return buffer; }
    auto end() const -> T* { return buffer + _size; /*or &buffer[_size]*/ }
    auto cbegin() const -> const T* { return buffer; }
    auto cend() const -> const T* { return buffer + _size; /*or &buffer[_size]*/ }
    auto operator=(vector&& other) -> vector&;
    auto at(size_t index) -> T&;
    auto assign(size_t count, const T& val) -> void;
    auto assign(T* first, T* last) -> void;
    auto operator[](size_t n) -> T&;
    auto const data() -> const T*;
    auto clear() -> void;
    auto pop_back() -> void;
    auto insert(const T* pos, const T& val) -> T*;
    auto erase(const T* pos) -> T*;
    auto erase(const T* first, const T* last) -> T*;
    vector(size_t n, const T &val);
    vector();
    ~vector() noexcept;
};

template <typename T>
vector<T>::vector(size_t n, const T &val)
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
auto vector<T>::assign(T* first, T* last) -> void
{
    size_t i = 0;
    for(T* it = first; it != last; it++) {
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
auto vector<T>::operator[](size_t n) -> T&
{
    return buffer[n];
}

template <typename T>
auto const vector<T>::data() -> const T*
{
    if(*this)
        return buffer;
    return nullptr;
}

template <typename T>
auto vector<T>::clear() -> void
{
    buffer = nullptr;
}

template <typename T>
auto vector<T>::pop_back() -> void
{
    if(!empty())
        _size--;
}

template <typename T>
auto vector<T>::insert(const T* pos, const T& val) -> T*
{
    if(!pos)
        throw std::invalid_argument("Insert position can't be null");

    while(_size >= _capacity) {
        size_t cap = _capacity ? _capacity * 2 : 1;
        reserve(cap);
    }
    
    size_t index = pos - begin();

    if(index > _size)
        throw std::out_of_range("Insert position out of range");
    
    for(size_t i = _size; i > index; i--)
        buffer[i] = buffer[i-1];

    _size++;
    buffer[index] = val;

    return begin() + index;
}

template <typename T>
auto vector<T>::erase(const T* pos) -> T*
{
    if(!pos)
        throw std::invalid_argument("Erase position can't be null");

    size_t index = pos - begin();

    if(index > _size)
        throw std::out_of_range("Erase position out of range");

    for(size_t i = index; i < _size; i++)
        buffer[i] = buffer[i+1];
    
    _size--;

    return begin() + index;
}

template <typename T>
auto vector<T>::erase(const T* first, const T* last) -> T*
{
    if(!first || !last)
        throw std::invalid_argument("Erase position can't be null");

    size_t index_beg = first - begin();
    size_t index_end = last - begin();

    if(index_beg > _size || index_end > _size)
        throw std::out_of_range("Erase position out of range");

    std::cout << "dqwu" << last-first << std::endl;

    for(size_t j = 0; j < last-first; j++) {
        for(size_t i = index_beg; i < _size; i++)
            buffer[i] = buffer[i+1];
    }
    
    _size -= last-first;

    return buffer;
}

template <typename T>
vector<T>::~vector() noexcept
{
    delete[] buffer;
    buffer = nullptr;
    _size = 0;
    _capacity = 0;
}