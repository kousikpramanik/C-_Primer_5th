#ifndef C_PRIMER_5TH_VEC_H
#define C_PRIMER_5TH_VEC_H

#include <memory>
#include <iterator>
#include <type_traits>
#include <limits>
#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <algorithm>

namespace primer {
    // should follow C++11 specs other than the explicit specialisation for bool
    template<typename T, typename Allocator = std::allocator<T>>
    class vector {
    public: // types
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = typename std::allocator_traits<Allocator>::size_type;
        using difference_type = typename std::allocator_traits<Allocator>::difference_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    private: // handle iterator and const_iterator as a single template
        template<bool mutability>
        class _iterator_templ {
            // Iterator
        public:
            using value_type = vector::value_type;
            using difference_type = vector::difference_type;
            using reference = typename std::conditional<mutability, vector::reference, vector::const_reference>::type;
            using pointer = typename std::conditional<mutability, vector::pointer, vector::const_pointer>::type;
            using iterator_category = std::random_access_iterator_tag;
        public:
            _iterator_templ(const _iterator_templ &other) : location(other.location) {}

            _iterator_templ &operator=(const _iterator_templ &other) {
                location = other.location;
                return *this;
            }

            friend void swap(_iterator_templ &lhs, _iterator_templ &rhs) {
                auto temp = lhs.location;
                lhs.location = rhs.location;
                rhs.location = temp;
            }

            reference operator*() const { return *location; }

            _iterator_templ &operator++() {
                ++location;
                return *this;
            }

            // InputIterator
            friend bool operator==(const _iterator_templ &lhs, const _iterator_templ &rhs) {
                return lhs.location == rhs.location;
            }

            friend bool operator!=(const _iterator_templ &lhs, const _iterator_templ &rhs) { return !(lhs == rhs); }

            pointer operator->() const { return &operator*(); }

            _iterator_templ operator++(int) &{
                auto prev = *this;
                ++*this;
                return prev;
            }

            // ForwardIterator
            _iterator_templ() = default;

            // BidirectionalIterator
            _iterator_templ &operator--() {
                --location;
                return *this;
            }

            _iterator_templ operator--(int) &{
                auto prev = *this;
                --*this;
                return prev;
            }

            // RandomAccessIterator
            _iterator_templ &operator+=(difference_type n) {
                location += n;
                return *this;
            }

            friend _iterator_templ operator+(_iterator_templ a, difference_type n) { return a += n; }

            friend _iterator_templ operator+(difference_type n, _iterator_templ a) { return a + n; }

            _iterator_templ &operator-=(difference_type n) { return operator+=(-n); }

            friend _iterator_templ operator-(_iterator_templ a, difference_type n) { return a -= n; }

            friend difference_type operator-(const _iterator_templ &a, const _iterator_templ &b) {
                return a.location - b.location;
            }

            reference operator[](difference_type n) { return *(location + n); }

            friend bool operator<(const _iterator_templ &a, const _iterator_templ &b) {
                return a.location < b.location;
            }

            friend bool operator<=(const _iterator_templ &a, const _iterator_templ &b) {
                return a.location <= b.location;
            }

            friend bool operator>(const _iterator_templ &a, const _iterator_templ &b) {
                return a.location > b.location;
            }

            friend bool operator>=(const _iterator_templ &a, const _iterator_templ &b) {
                return a.location >= b.location;
            }

        public: // conversion from iterator to const_iterator
            template<bool B = mutability, typename std::enable_if<!B>::type>
            _iterator_templ(const _iterator_templ<!B> &other) : location(other.location) {}

            template<bool B = mutability, typename std::enable_if<!B>::type>
            _iterator_templ &operator=(const _iterator_templ<!B> &other) {
                location = other.location;
                return *this;
            }

        private: // constructor only vector can create
            friend class vector;

            _iterator_templ(pointer from_vector) : location(from_vector) {}

        private: // data members
            pointer location = nullptr;
        };

    public: // types continued
        using iterator = _iterator_templ<true>;
        using const_iterator = _iterator_templ<false>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    public: // member functions
        vector() = default;

        explicit vector(const Allocator &alloc) : __alloc(alloc) {}

        vector(size_type count, const T &value, const Allocator &alloc = Allocator()) :
                __alloc(alloc),
                __first_location(std::allocator_traits<allocator_type>::allocate(__alloc, count)),
                __first_free(__first_location),
                __one_past_capacity(__first_location + count) {
            try {
                for (; __first_free != __one_past_capacity; ++__first_free) {
                    std::allocator_traits<allocator_type>::construct(__alloc, __first_free, value);
                }
            } catch (...) {
                auto eptr = std::current_exception();
                while (__first_location != __first_free--) {
                    std::allocator_traits<allocator_type>::destroy(__alloc, __first_free);
                }
                std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, count);
                std::rethrow_exception(eptr);
            }
        }

        explicit vector(size_type count) : vector(count, value_type()) {}

        template<typename Iter>
        vector(Iter first, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<Iter>::iterator_category>::value, Iter>::type last,
               const Allocator &alloc = Allocator()) :
                vector(first, last, alloc, typename std::iterator_traits<Iter>::iterator_category()) {}

    private: // tag dispatch for previous function
        template<typename InputIt>
        vector(InputIt first, InputIt last, const Allocator &alloc, std::input_iterator_tag) : __alloc(alloc) {
            for (; first != last; ++first) { push_back(*first); }
        }

        template<typename ForwardIt>
        vector(ForwardIt first, ForwardIt last, const Allocator &alloc, std::forward_iterator_tag)
                : __alloc(alloc) {
            size_type count = 0;
            for (auto curr = first; curr != last; ++curr) { ++count; }
            __first_location = std::allocator_traits<allocator_type>::allocate(__alloc, count);
            try {
                _copy_to_vect(first, last, __first_location, __alloc);
            } catch (...) {
                auto eptr = std::current_exception();
                std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, count);
                std::rethrow_exception(eptr);
            }
            __one_past_capacity = __first_free = __first_location + count;
        }

        template<typename RAIt>
        vector(RAIt first, RAIt last, const Allocator &alloc, std::random_access_iterator_tag) :
                __alloc(alloc),
                __first_location(std::allocator_traits<allocator_type>::allocate(__alloc, last - first)),
                __one_past_capacity(__first_free = __first_location + (last - first)) {
            try {
                _copy_to_vect(first, last, __first_location, __alloc);
            } catch (...) {
                auto eptr = std::current_exception();
                std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, last - first);
                std::rethrow_exception(eptr);
            }
        }

    public: // member functions continued
        vector(const vector &other) :
                vector(other, std::allocator_traits<allocator_type>::select_on_container_copy_construction(
                        other.get_allocator())) {}

        vector(const vector &other, const Allocator &alloc) : vector(other.begin(), other.end(), alloc) {}

        vector(vector &&other) : __first_location(other.__first_location),
                                 __first_free(other.__first_free),
                                 __one_past_capacity(other.__one_past_capacity),
                                 __alloc(std::move(other.__alloc)) {
            other.__one_past_capacity = other.__first_free = other.__first_location = nullptr;
        }

        vector(vector &&other, const Allocator &alloc) : __first_location(other.__first_location),
                                                         __first_free(other.__first_free),
                                                         __one_past_capacity(other.__one_past_capacity),
                                                         __alloc(alloc) {
            if (alloc == other.get_allocator()) {
                other.__one_past_capacity = other.__first_free = other.__first_location = nullptr;
            } else {
                size_type new_cap = other.size();
                __first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
                try {
                    _move_to_vect(other.begin(), other.end(), __first_location, __alloc);
                } catch (...) {
                    auto eptr = std::current_exception();
                    std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, new_cap);
                    std::rethrow_exception(eptr);
                }
                __one_past_capacity = __first_free = __first_location + new_cap;
            }
        }

        vector(std::initializer_list<T> init, const Allocator &alloc = Allocator()) : vector(init.begin(), init.end(),
                                                                                             alloc) {}

        ~vector() { clear(); }

        vector &operator=(const vector &other) {
            return _copy_assign_helper(other,
                                       typename std::allocator_traits<allocator_type>::
                                       propagate_on_container_copy_assignment());
        }

    private: // tag dispatch for previous function
        vector &_copy_assign_helper(const vector &other, std::true_type) {
            if (__alloc == other.get_allocator()) {
                return _copy_assign_helper(other, std::false_type());
            } else {
                size_type new_cap = other.size();
                allocator_type new_allocator = other.get_allocator();
                pointer new_first_location = std::allocator_traits<allocator_type>::allocate(new_allocator, new_cap);
                try {
                    _copy_to_vect(other.begin(), other.end(), new_first_location, new_allocator);
                } catch (...) {
                    auto eptr = std::current_exception();
                    std::allocator_traits<allocator_type>::deallocate(new_allocator, new_first_location, new_cap);
                    std::rethrow_exception(eptr);
                }
                clear();
                __alloc = std::move(new_allocator);
                __first_location = new_first_location;
                __one_past_capacity = __first_free = new_first_location + new_cap;
                return *this;
            }
        }

        vector &_copy_assign_helper(const vector &other, std::false_type) {
            size_type new_cap = other.size();
            pointer new_first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
            try {
                _copy_to_vect(other.begin(), other.end(), new_first_location, __alloc);
            } catch (...) {
                auto eptr = std::current_exception();
                std::allocator_traits<allocator_type>::deallocate(__alloc, new_first_location, new_cap);
                std::rethrow_exception(eptr);
            }
            clear();
            __first_location = new_first_location;
            __one_past_capacity = __first_free = new_first_location + new_cap;
            return *this;
        }

    public: // member functions continued
        vector &operator=(vector &&other) {
            return _move_assign_helper(std::move(other),
                                       typename std::allocator_traits<allocator_type>::
                                       propagate_on_container_move_assignment());
        }

    private: // tag dispatch for previous function
        vector &_move_assign_helper(vector &&other, std::true_type) {
            pointer new_first_location = other.__first_location;
            pointer new_first_free = other.__first_free;
            pointer new_one_past_capacity = other.__one_past_capacity;
            other.__first_location = nullptr;
            other.__first_free = nullptr;
            other.__one_past_capacity = nullptr;
            clear();
            __alloc = other.get_allocator();
            __first_location = new_first_location;
            __first_free = new_first_free;
            __one_past_capacity = new_one_past_capacity;
            return *this;
        }

        vector &_move_assign_helper(vector &&other, std::false_type) {
            if (__alloc == other.get_allocator()) {
                pointer new_first_location = other.__first_location;
                pointer new_first_free = other.__first_free;
                pointer new_one_past_capacity = other.__one_past_capacity;
                other.__first_location = nullptr;
                other.__first_free = nullptr;
                other.__one_past_capacity = nullptr;
                clear();
                __first_location = new_first_location;
                __first_free = new_first_free;
                __one_past_capacity = new_one_past_capacity;
            } else {
                size_type new_cap = other.size();
                pointer new_first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
                try {
                    _move_to_vect(other.begin(), other.end(), new_first_location, __alloc);
                } catch (...) {
                    auto eptr = std::current_exception();
                    std::allocator_traits<allocator_type>::deallocate(__alloc, new_first_location, new_cap);
                    std::rethrow_exception(eptr);
                }
                clear();
                __first_location = new_first_location;
                __one_past_capacity = __first_free = new_first_location + new_cap;
            }
            return *this;
        }

    public: // member functions continued
        vector &operator=(std::initializer_list<T> ilist) {
            vector new_vector(ilist);
            *this = std::move(new_vector);
            return *this;
        }

        void assign(size_type count, const T &value) {
            vector new_vector(count, value);
            *this = std::move(new_vector);
        }

        template<class InputIt>
        void assign(InputIt first, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<InputIt>::iterator_category>::value, InputIt>::type last) {
            vector new_vector(first, last);
            *this = std::move(new_vector);
        }

        void assign(std::initializer_list<T> ilist) { operator=(ilist); }

        allocator_type get_allocator() const noexcept { return __alloc; }

    public: // element access
        reference at(size_type pos) {
            if (pos >= size()) { throw std::out_of_range("requested access beyond vector bounds"); }
            return __first_location[pos];
        }

        const_reference at(size_type pos) const {
            if (pos >= size()) { throw std::out_of_range("requested access beyond vector bounds"); }
            return __first_location[pos];
        }

        reference operator[](size_type pos) { return __first_location[pos]; }

        const_reference operator[](size_type pos) const { return __first_location[pos]; }

        reference front() { return __first_location[0]; }

        const_reference front() const { return __first_location[0]; }

        reference back() { return __first_free[-1]; }

        const_reference back() const { return __first_free[-1]; }

        T *data() noexcept { return __first_location; }

        const T *data() const noexcept { return __first_location; }

    public: // iterators
        iterator begin() noexcept { return __first_location; }

        const_iterator begin() const noexcept { return __first_location; }

        const_iterator cbegin() const noexcept { return __first_location; }

        iterator end() noexcept { return __first_free; }

        const_iterator end() const noexcept { return __first_free; }

        const_iterator cend() const noexcept { return __first_free; }

        reverse_iterator rbegin() noexcept { return end(); }

        const_reverse_iterator rbegin() const noexcept { return end(); }

        const_reverse_iterator crbegin() const noexcept { return cend(); }

        reverse_iterator rend() noexcept { return begin(); }

        const_reverse_iterator rend() const noexcept { return begin(); }

        const_reverse_iterator crend() const noexcept { return cbegin(); }

    public: // capacity
        bool empty() const noexcept { return __first_location == nullptr; }

        size_type size() const noexcept { return __first_free - __first_location; }

        size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }

        void reserve(size_type new_cap) {
            if (new_cap > capacity()) { _reallocate(new_cap); }
        }

        size_type capacity() const noexcept { return __one_past_capacity - __first_location; }

        void shrink_to_fit() {
            if (capacity() != size()) { _reallocate(size()); }
        }

    public: // modifiers
        void clear() noexcept { clear(std::is_trivially_destructible<T>()); }

    private: // tag dispatch for previous function
        void clear(std::true_type) noexcept {
            if (__first_location != nullptr) {
                std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, capacity());
                __first_location = __first_free = __one_past_capacity = nullptr;
            }
        }

        void clear(std::false_type) noexcept {
            if (__first_location != nullptr) {
                for (auto location = __first_location; location != __first_free; ++location) {
                    std::allocator_traits<allocator_type>::destroy(__alloc, location);
                }
                std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, capacity());
                __first_location = __first_free = __one_past_capacity = nullptr;
            }
        }

    public: // modifiers continued
        iterator insert(const_iterator pos, const T &value) {
            auto start_distance = pos - begin();
            if (pos == end()) {
                push_back(value);
            } else {
                _handle_out_of_space();
                pointer new_pos = _make_space_middle(const_cast<pointer>(pos.location), 1);
                try {
                    std::allocator_traits<allocator_type>::construct(__alloc, new_pos, value);
                } catch (...) {
                    auto eptr = std::current_exception();
                    auto destroy_rest = new_pos;
                    while (destroy_rest++ != __first_free) {
                        std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                    }
                    __first_free = new_pos;
                    std::rethrow_exception(eptr);
                }
            }
            return begin() + start_distance;
        }

        iterator insert(const_iterator pos, T &&value) {
            auto start_distance = pos - begin();
            if (pos == end()) {
                push_back(std::move(value));
            } else {
                pointer new_pos = _make_space_middle(const_cast<pointer>(pos.location), 1);
                try {
                    std::allocator_traits<allocator_type>::construct(__alloc, new_pos, value);
                } catch (...) {
                    auto eptr = std::current_exception();
                    auto destroy_rest = new_pos;
                    while (destroy_rest++ != __first_free) {
                        std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                    }
                    __first_free = new_pos;
                    std::rethrow_exception(eptr);
                }
            }
            return begin() + start_distance;
        }

        iterator insert(const_iterator pos, size_type count, const T &value) {
            auto start_distance = pos - begin();
            if (count == 1) {
                return insert(pos, value);
            } else if (count != 0) {
                pointer new_pos = _make_space_middle(const_cast<pointer>(pos.location), count);
                try {
                    for (; count != 0; --count, ++new_pos) {
                        std::allocator_traits<allocator_type>::construct(__alloc, new_pos, value);
                    }
                } catch (...) {
                    auto eptr = std::current_exception();
                    auto destroy_rest = new_pos;
                    destroy_rest += count;
                    while (destroy_rest++ != __first_free) {
                        std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                    }
                    __first_free = new_pos;
                    std::rethrow_exception(eptr);
                }
            }
            return begin() + start_distance;
        }

        template<class Iter>
        iterator insert(const_iterator pos, Iter first, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<Iter>::iterator_category>::value, Iter>::type last) {
            return insert(pos, first, last, typename std::iterator_traits<Iter>::iterator_category());
        }

    private: // tag dispatch for previous function
        template<class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last, std::input_iterator_tag) {
            auto start_distance = pos - begin();
            for (; first != last; ++first) { pos = insert(pos, *first); }
            return begin() + start_distance;
        }

        template<class ForwardIt>
        iterator insert(const_iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
            auto start_distance = pos - begin();
            size_type count = 0;
            for (auto count_iter = first; count_iter != last; ++count_iter) { ++count; }
            if (count == 1) {
                return insert(pos, *first);
            } else if (count != 0) {
                pointer new_pos = _make_space_middle(const_cast<pointer>(pos.location), count);
                try {
                    for (; count != 0; --count, ++new_pos, ++first) {
                        std::allocator_traits<allocator_type>::construct(__alloc, new_pos, *first);
                    }
                } catch (...) {
                    auto eptr = std::current_exception();
                    auto destroy_rest = new_pos;
                    destroy_rest += count;
                    while (destroy_rest++ != __first_free) {
                        std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                    }
                    __first_free = new_pos;
                    std::rethrow_exception(eptr);
                }
            }
            return begin() + start_distance;
        }

        template<class RAIt>
        iterator insert(const_iterator pos, RAIt first, RAIt last, std::random_access_iterator_tag) {
            auto start_distance = pos - begin();
            size_type count = last - first;
            if (count == 1) {
                return insert(pos, *first);
            } else if (count != 0) {
                pointer new_pos = _make_space_middle(const_cast<pointer>(pos.location), count);
                try {
                    for (; count != 0; --count, ++new_pos, ++first) {
                        std::allocator_traits<allocator_type>::construct(__alloc, new_pos, *first);
                    }
                } catch (...) {
                    auto eptr = std::current_exception();
                    auto destroy_rest = new_pos;
                    destroy_rest += count;
                    while (destroy_rest++ != __first_free) {
                        std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                    }
                    __first_free = new_pos;
                    std::rethrow_exception(eptr);
                }
            }
            return begin() + start_distance;
        }

    public: // modifiers continued
        iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
            return insert(pos, ilist.begin(), ilist.end());
        }

        void push_back(const T &value) {
            _handle_out_of_space();
            std::allocator_traits<allocator_type>::construct(__alloc, __first_free++, value);
        }

        void push_back(T &&value) {
            _handle_out_of_space();
            std::allocator_traits<allocator_type>::construct(__alloc, __first_free++, std::move(value));
        }

    private: // internal usage
        template<typename InputIt>
        void _copy_to_vect(InputIt first, InputIt last, pointer where_to, allocator_type &alloc) {
            pointer where_to_backup = where_to;
            try {
                for (; first != last; ++where_to, ++first) {
                    std::allocator_traits<allocator_type>::construct(alloc, where_to, *first);
                }
            } catch (...) {
                auto eptr = std::current_exception();
                while (where_to_backup != where_to--) {
                    std::allocator_traits<allocator_type>::destroy(alloc, where_to);
                }
                std::rethrow_exception(eptr);
            }
        }

        template<typename InputIt>
        void _move_to_vect(InputIt first, InputIt last, pointer where_to, allocator_type &alloc) {
            _copy_to_vect(std::make_move_iterator(first), std::make_move_iterator(last), where_to, alloc);
        }

        void _reallocate(size_type new_cap) {
            _reallocate(new_cap, std::integral_constant<bool,
                    std::is_nothrow_move_constructible<T>::value || !std::is_nothrow_copy_constructible<T>::value>());
        }

    private: // tag dispatch for previous function
        void _reallocate(size_type new_cap, std::true_type) {
            if (new_cap > max_size()) {
                throw std::length_error("requested allocation of more than max_size() items.");
            }
            pointer new_first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
            pointer new_first_free = new_first_location;
            try {
                for (auto location = __first_location; location != __first_free; ++location, ++new_first_free) {
                    std::allocator_traits<allocator_type>::construct(__alloc, new_first_free, std::move(*location));
                }
            } catch (...) {
                auto eptr = std::current_exception();
                while (new_first_location != new_first_free--) {
                    std::allocator_traits<allocator_type>::destroy(__alloc, new_first_free);
                }
                std::allocator_traits<allocator_type>::deallocate(__alloc, new_first_location, new_cap);
                std::rethrow_exception(eptr);
            }
            clear();
            __first_location = new_first_location;
            __first_free = new_first_free;
            __one_past_capacity = __first_location + new_cap;
        }

        void _reallocate(size_type new_cap, std::false_type) {
            if (new_cap > max_size()) {
                throw std::length_error("requested allocation of more than max_size() items.");
            }
            pointer new_first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
            pointer new_first_free = new_first_location;
            for (auto location = __first_location; location != __first_free; ++location, ++new_first_free) {
                std::allocator_traits<allocator_type>::construct(__alloc, new_first_free, *location);
            }
            clear();
            __first_location = new_first_location;
            __first_free = new_first_free;
            __one_past_capacity = __first_location + new_cap;
        }

    private: // continued from before
        void _handle_out_of_space() {
            if (size() == capacity()) { _reallocate(std::max(capacity() * 2, static_cast<size_type>(1))); }
        }

    private: // data members
        allocator_type __alloc; // = allocator_type();
        pointer __first_location = nullptr;
        pointer __first_free = nullptr;
        pointer __one_past_capacity = nullptr;
    };
}

#endif //C_PRIMER_5TH_VEC_H
