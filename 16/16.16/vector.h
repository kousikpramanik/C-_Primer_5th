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
    // TODO
    // 1) exception handling needs to be simplified. also, figure out what shouldn't throw (e.g. erase).
    //    _exceptional_cleaner(allocator_type &alloc,
    //      std::initializer_list<std::pair<pointer, pointer>> destroy,
    //      std::initializer_list<std::pair<pointer, size_type>> deallocate = {});
    // 2) allocator::value_type not matching T could be trouble
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
                return std::distance(b.location, a.location);
            }

            reference operator[](difference_type n) { return *(location + n); }

            friend bool operator<(const _iterator_templ &a, const _iterator_templ &b) {
                return a.location < b.location;
            }

            friend bool operator<=(const _iterator_templ &a, const _iterator_templ &b) { return !(a > b); }

            friend bool operator>(const _iterator_templ &a, const _iterator_templ &b) { return b < a; }

            friend bool operator>=(const _iterator_templ &a, const _iterator_templ &b) { return !(a < b); }

        public: // conversion from iterator to const_iterator
            template<bool B, typename std::enable_if<B, bool>::type = true>
            _iterator_templ(const _iterator_templ<B> &other) : location(other.location) {}

            template<bool B, typename std::enable_if<B, bool>::type = true>
            _iterator_templ &operator=(const _iterator_templ<B> &other) {
                location = other.location;
                return *this;
            }

        private: // constructor only vector can access
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

        vector(size_type count, const T &value, const Allocator &alloc = Allocator()) : __alloc(alloc) {
            insert(end(), count, value);
        }

        explicit vector(size_type count) : vector(count, value_type()) {}

        template<typename Iter, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<Iter>::iterator_category>::value, bool>::type = true>
        vector(Iter first, Iter last, const Allocator &alloc = Allocator()) : __alloc(alloc) {
            insert(end(), first, last);
        }

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
                auto new_cap = other.size();
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

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::true_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_copy_assignment>::value,
                bool>::type = true>
        vector &operator=(const vector &other) {
            auto new_cap = other.size();
            allocator_type new_allocator = __alloc;
            if (__alloc != other.get_allocator()) {
                new_allocator = other.get_allocator();
            }
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

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::false_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_copy_assignment>::value,
                bool>::type = true>
        vector &operator=(const vector &other) {
            auto new_cap = other.size();
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

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::true_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_move_assignment>::value,
                bool>::type = true>
        vector &operator=(vector &&other) {
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

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::false_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_move_assignment>::value,
                bool>::type = true>
        vector &operator=(vector &&other) {
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
                auto new_cap = other.size();
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

        vector &operator=(std::initializer_list<T> ilist) {
            vector new_vector(ilist);
            *this = std::move(new_vector);
            return *this;
        }

        void assign(size_type count, const T &value) {
            vector new_vector(count, value);
            *this = std::move(new_vector);
        }

        template<class InputIt, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<InputIt>::iterator_category>::value, bool>::type = true>
        void assign(InputIt first, InputIt last) {
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

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    public: // capacity
        bool empty() const noexcept { return size(); }

        size_type size() const noexcept { return std::distance(__first_location, __first_free); }

        size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }

        void reserve(size_type new_cap) { if (new_cap > capacity()) { _reallocate(new_cap); }}

        size_type capacity() const noexcept { return std::distance(__first_location, __one_past_capacity); }

        void shrink_to_fit() { if (capacity() != size()) { _reallocate(size()); }}

    public: // modifiers
        void clear() noexcept {
            if (__first_location != nullptr) {
                for (auto location = __first_free; location-- != __first_location;) {
                    // T has to satisfy [destructible] which means this won't throw
                    std::allocator_traits<allocator_type>::destroy(__alloc, location);
                }
                std::allocator_traits<allocator_type>::deallocate(__alloc, __first_location, capacity());
                __first_location = __first_free = __one_past_capacity = nullptr;
            }
        }

        iterator insert(const_iterator pos, const T &value) { return emplace(pos, value); }

        iterator insert(const_iterator pos, T &&value) {
            return emplace(pos, std::move_if_noexcept(value));
        }

        iterator insert(const_iterator pos, size_type count, const T &value) {
            if (count > max_size()) {
                throw std::length_error("requested allocation of more than max_size() items.");
            }
            auto start_distance = std::distance(cbegin(), pos);
            pointer location = _make_space_middle(const_cast<pointer>(pos.location),
                                                  static_cast<difference_type>(count));
            try {
                for (; count != 0; --count, ++location) {
                    std::allocator_traits<allocator_type>::construct(__alloc, location, value);
                }
            } catch (...) {
                auto eptr = std::current_exception();
                auto destroy_rest = location;
                destroy_rest += count;
                while (destroy_rest++ != __first_free) {
                    std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                }
                __first_free = location;
                std::rethrow_exception(eptr);
            }
            return begin() + start_distance;
        }

        template<class Iter, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<Iter>::iterator_category>::value, bool>::type = true>
        iterator insert(const_iterator pos, Iter first, Iter last) {
            return insert(pos, first, last, typename std::iterator_traits<Iter>::iterator_category());
        }

    private: // tag dispatch for previous function
        template<class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last, std::input_iterator_tag) {
            auto start_distance = std::distance(cbegin(), pos);
            for (; first != last; ++first) { pos = insert(pos, *first); }
            return begin() + start_distance;
        }

        template<class ForwardIt>
        iterator insert(const_iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
            auto start_distance = std::distance(cbegin(), pos);
            auto count = std::distance(first, last);
            pointer location = _make_space_middle(const_cast<pointer>(pos.location), count);
            try {
                for (; count != 0; --count, ++location, ++first) {
                    std::allocator_traits<allocator_type>::construct(__alloc, location, *first);
                }
            } catch (...) {
                auto eptr = std::current_exception();
                auto destroy_rest = location;
                destroy_rest += count;
                while (destroy_rest++ != __first_free) {
                    std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                }
                __first_free = location;
                std::rethrow_exception(eptr);
            }
            return begin() + start_distance;
        }

    public: // modifiers continued
        iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
            return insert(pos, ilist.begin(), ilist.end());
        }

        template<class... Args>
        iterator emplace(const_iterator pos, Args &&... args) {
            auto start_distance = std::distance(cbegin(), pos);
            pointer location = _make_space_middle(const_cast<pointer>(pos.location), 1);
            try {
                std::allocator_traits<allocator_type>::construct(__alloc, location, std::forward<Args>(args)...);
            } catch (...) {
                auto eptr = std::current_exception();
                auto destroy_rest = location;
                while (destroy_rest++ != __first_free) {
                    std::allocator_traits<allocator_type>::destroy(__alloc, destroy_rest);
                }
                __first_free = location;
                std::rethrow_exception(eptr);
            }
            return begin() + start_distance;
        }

        iterator erase(const_iterator pos) { erase(pos, pos + 1); }

        iterator erase(const_iterator first, const_iterator last) {
            auto count = std::distance(first, last);
            auto curr = const_cast<pointer>(first.location);
            auto last_cache = const_cast<pointer>(last.location);
            for (; curr != last_cache; ++curr) {
                std::allocator_traits<allocator_type>::destroy(__alloc, curr);
            }
            _move_to_vect(last_cache, __first_free, const_cast<pointer>(first.location), __alloc);
            while (count-- != 0) {
                std::allocator_traits<allocator_type>::destroy(__alloc, --__first_free);
            }
            return const_cast<pointer>(first.location);
        }

        void push_back(const T &value) { insert(end(), value); }

        void push_back(T &&value) { insert(end(), std::move(value)); }

        template<class... Args>
        void emplace_back(Args &&... args) { emplace(end(), std::forward<Args>(args)...); }

        void pop_back() { erase(end() - 1); }

        void resize(size_type count) { resize(count, value_type()); }

        void resize(size_type count, const value_type &value) {
            if (count < size()) {
                erase(begin() + count, end());
            } else {
                insert(end(), size() - count, value_type());
            }
        }

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::true_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_swap>::value,
                bool>::type = true>
        void swap(vector &other) {
            using std::swap;
            swap(__alloc, other.__alloc);
            swap(__first_location, other.__first_location);
            swap(__first_free, other.__first_free);
            swap(__one_past_capacity, other.__one_past_capacity);
        }

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::false_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_swap>::value,
                bool>::type = true>
        void swap(vector &other) {
            using std::swap;
            swap(__first_location, other.__first_location);
            swap(__first_free, other.__first_free);
            swap(__one_past_capacity, other.__one_past_capacity);
        }

    public: // non-member functions
        friend bool operator==(const vector &lhs, const vector &rhs) {
            if (lhs.size() != rhs.size()) { return false; }
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        friend bool operator!=(const vector &lhs, const vector &rhs) { return !(lhs == rhs); }

        friend bool operator<(const vector &lhs, const vector &rhs) {
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator<=(const vector &lhs, const vector &rhs) { return !(lhs > rhs); }

        friend bool operator>(const vector &lhs, const vector &rhs) { return rhs < lhs; }

        friend bool operator>=(const vector &lhs, const vector &rhs) { return !(lhs < rhs); }

        friend void swap(vector &lhs, vector &rhs) { lhs.swap(rhs); }

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
            using Iter = typename std::conditional<std::is_nothrow_move_constructible<T>::value ||
                                                   !std::is_nothrow_copy_constructible<T>::value,
                    std::move_iterator<InputIt>, InputIt>::type;
            _copy_to_vect(Iter(first), Iter(last), where_to, alloc);
        }

        pointer _make_space_middle(pointer location, difference_type count) {
            if (count != 0) {
                auto new_cap = capacity();
                if (new_cap < size() + count) {
                    new_cap = std::max(capacity() * 2, static_cast<size_type>(1));
                    while (new_cap < size() + count) { new_cap *= 2; }
                }
                if (new_cap > capacity() || location != __first_free) {
                    auto position = std::distance(__first_location, location);
                    _reallocate(new_cap, position, count);
                    location = __first_location + position;
                }
            }
            return location;
        }

        void _reallocate(size_type new_cap, size_type skip_pos = 0, difference_type skip_count = 0) {
            if (new_cap > max_size()) {
                throw std::length_error("requested allocation of more than max_size() items.");
            }
            pointer new_first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
            pointer new_first_free = new_first_location;
            try {
                auto location = __first_location;
                size_type curr_pos = 0;
                while (curr_pos != size() + skip_count) {
                    if (curr_pos == skip_pos) {
                        new_first_free += skip_count;
                        curr_pos += skip_count;
                        continue;
                    }
                    std::allocator_traits<allocator_type>::construct(__alloc, new_first_free,
                                                                     std::move_if_noexcept(*location));
                    ++curr_pos;
                    ++location;
                    ++new_first_free;
                }
            } catch (...) {
                auto eptr = std::current_exception();
                while (new_first_location != new_first_free--) {
                    if (std::distance(new_first_location, new_first_free) ==
                        static_cast<difference_type>(skip_pos + skip_count - 1)) {
                        new_first_free -= skip_count - 1;
                        continue;
                    }
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

    private: // data members
        allocator_type __alloc; // = allocator_type();
        pointer __first_location = nullptr;
        pointer __first_free = nullptr;
        pointer __one_past_capacity = nullptr;
    };
}

#endif //C_PRIMER_5TH_VEC_H
