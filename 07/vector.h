template <class T>
class Allocator {
public:
    T* allocate(size_t count) {
        return static_cast<T*>(operator new[](sizeof(T) * count));
    }
    void deallocate(T* ptr, size_t count) {
        operator delete[](ptr, sizeof(T) * count);
    }
};


template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T> {
    T* ptr_;
public:
    explicit Iterator(T* ptr): ptr_(ptr) {}

    T& operator*() const {
        return *ptr_;
    }
    Iterator& operator++() {
        ++ptr_;
        return *this;
    }
    Iterator& operator--() {
        --ptr_;
        return *this;
    }
    Iterator& operator+=(size_t n) {
        ptr_ += n;
        return *this;
    }
    Iterator& operator-=(size_t n) {
        ptr_ -= n;
        return *this;
    }
    Iterator operator+(size_t n) const {
        return Iterator(ptr_ + n);
    }
    Iterator operator-(size_t n) const {
        return Iterator(ptr_ - n);
    }
    Iterator& operator[](int n) {
        return ptr_[n];
    }
    bool operator==(const Iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }
    bool operator<(const Iterator<T> &other) {
        return (operator-(other) > 0);
    }
    bool operator>(const Iterator<T> &other) {
        return other < *this;
    }
    bool operator>=(const Iterator<T> &other) {
        return !(*this < other);
    }
    bool operator<=(const Iterator<T> &other) {
        return !(*this > other);
    }
};


template<class T, class Alloc = Allocator<T>>
class Vector {
private:
    Alloc alloc_;
    T* data_;
    size_t size_;
    size_t max_size_;
public:

    Vector(size_t size = 0) : size_(size), max_size_(size + 5) {
        data_ = alloc_.allocate(max_size_);
        for (size_t i = 0; i < size; ++i) {
            new(data_ + i) T();
        }
    }

    T& operator[](size_t idx) {
        if (idx < size_) {
            return data_[idx];
        } else {
            throw std::out_of_range("Error");
        }
    }

    void reserve(size_t new_size) {
        if (new_size > max_size_) {
            T* tmp = alloc_.allocate(new_size);
            for (size_t i = 0; i < size_; ++i) {
                new(tmp + i) T(data_[i]);
                (data_ + i) -> ~T();
            }
            alloc_.deallocate(data_, max_size_);
            max_size_ = new_size;
            data_ = tmp;
        }
    }

    void push_back(const T &elem) {
        if (size_ >= max_size_)
            reserve(max_size_ + max_size_);
        new(data_ + size_) T(elem);
        ++size_;
    }

    void pop_back() {
        if (size_) {
            --size_;
            (data_ + size_) -> ~T();
        }
    }

    bool empty() const {
        return !size_;
    }

    size_t size() const {
        return size_;
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            (data_ + i) -> ~T();
        }
        size_ = 0;
    }

    Iterator<T> begin() {
        return Iterator<T>(data_);
    }

    Iterator<T> end() {
        return Iterator<T>(data_ + size_);
    }

    std::reverse_iterator <Iterator<T>> rbegin() {
        return std::reverse_iterator<Iterator<T>>(Iterator<T>(data_ + size_));
    }

    std::reverse_iterator <Iterator<T>> rend() {
        return std::reverse_iterator<Iterator<T>>(Iterator<T>(data_));
    }

    size_t capacity() const {
        return max_size_;
    }

    void resize(size_t new_size) {
        if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i) {
                (data_ + i) -> ~T();
            }
        } else {
            if (new_size > max_size_) {
                reserve(new_size);
            }
            for (size_t i = size_; i < new_size; ++i) {
                new(data_ + i) T();
            }
        }
        size_ = new_size;
    }

    ~Vector() {
        for (size_t i = 0; i < size_; ++i) {
            (data_ + i) -> ~T();
        }
        alloc_.deallocate(data_, max_size_);
    }
};
