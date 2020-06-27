#ifndef C_PRIMER_5TH_VECTOR_H
#define C_PRIMER_5TH_VECTOR_H

#include <memory>
#include <iterator>
#include <type_traits>
#include <functional>
#include <limits>
#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <algorithm>

namespace primer {
    // should follow C++11 specs other than the explicit specialisation for bool

    /* exception safety if any of the insert() and emplace() like functions throw
     *
     * constructor throwing while constructing new element -
     * the vector is resized so that either the argument corresponding to the const_iterator pos parameter
     * equals cend() afterwards, or one past the last successfully constructed object equals cend() afterwards.
     * In any case, all elements in the new (begin(), end()] range are valid.
     *
     * a throw during reallocation -
     * read the comments in _reallocate().
     */
    template<typename T, typename Allocator = std::allocator<T>>
    class vector {
        static_assert(!std::is_reference<T>::value && !std::is_array<T>::value
                      && std::is_nothrow_destructible<T>::value, "T must satisfy [destructible]");
        static_assert(std::is_same<typename std::allocator_traits<Allocator>::value_type, T>::value,
                      "Allocator's value type must be T");
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
        public: // [iterator.traits] - required by [iterator.requirements.general] paragraph 11
            using difference_type = vector::difference_type;
            using value_type = vector::value_type;
            using iterator_category = std::random_access_iterator_tag;
            using reference = typename std::conditional<mutability, vector::reference, vector::const_reference>::type;
            using pointer = typename std::conditional<mutability, vector::pointer, vector::const_pointer>::type;
        public: // [iterator.iterators]
            friend void swap(_iterator_templ &lhs, _iterator_templ &rhs) {
                auto temp = lhs.location;
                lhs.location = rhs.location;
                rhs.location = temp;
            }

        public: // [input.iterators]
            friend bool operator==(const _iterator_templ &lhs, const _iterator_templ &rhs) {
                return std::equal_to<pointer>()(lhs.location, rhs.location);
            }

            friend bool operator!=(const _iterator_templ &lhs, const _iterator_templ &rhs) { return !(lhs == rhs); }

            pointer operator->() const { return std::addressof(*(*this)); }

            _iterator_templ &operator++() { return *this += 1; }

        public: // [forward.iterators]
            _iterator_templ() = default;

            _iterator_templ operator++(int) &{
                auto prev = *this;
                ++*this;
                return prev;
            }

            reference operator*() const { return *location; }

        public: // [bidirectional.iterators]
            _iterator_templ &operator--() { return *this -= 1; }

            _iterator_templ operator--(int) &{
                auto prev = *this;
                --*this;
                return prev;
            }

        public: // [random.access.iterators]
            _iterator_templ &operator+=(difference_type n) {
                std::advance(location, n);
                return *this;
            }

            friend _iterator_templ operator+(_iterator_templ a, difference_type n) { return a += n; }

            friend _iterator_templ operator+(difference_type n, _iterator_templ a) { return a + n; }

            _iterator_templ &operator-=(difference_type n) { return *this += -n; }

            friend _iterator_templ operator-(_iterator_templ a, difference_type n) { return a -= n; }

            friend difference_type operator-(const _iterator_templ &a, const _iterator_templ &b) {
                return std::distance(b.location, a.location);
            }

            reference operator[](difference_type n) { return *(*this + n); }

            friend bool operator<(const _iterator_templ &a, const _iterator_templ &b) {
                return std::less<pointer>()(a.location, b.location);
            }

            friend bool operator<=(const _iterator_templ &a, const _iterator_templ &b) { return !(a > b); }

            friend bool operator>(const _iterator_templ &a, const _iterator_templ &b) { return b < a; }

            friend bool operator>=(const _iterator_templ &a, const _iterator_templ &b) { return !(a < b); }

        public: // conversion from iterator to const_iterator - [containers.requirements.general]
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

        vector(vector &&other, const Allocator &alloc) : __alloc(alloc) {
            if (alloc == other.get_allocator()) {
                __first_location = other.__first_location;
                __first_free = other.__first_free;
                __one_past_capacity = other.__one_past_capacity;
                other.__one_past_capacity = other.__first_free = other.__first_location = nullptr;
            } else {
                auto new_cap = other.size();
                _reallocate(new_cap);
                __first_free += new_cap;
                try {
                    _move_to_vect(__alloc, other.begin(), other.end(), __first_location);
                } catch (...) {
                    _cleaner(__alloc, {}, {{__first_location, new_cap}});
                    std::rethrow_exception(std::current_exception());
                }
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
            if (__alloc == other.get_allocator()) {
                resize(other.size());
                _copy_assign_to_vect(__alloc, other.begin(), other.end());
            } else {
                vector new_vector(other);
                clear();
                __first_location = new_vector.__first_location;
                __first_free = new_vector.__first_free;
                __one_past_capacity = new_vector.__one_past_capacity;
                new_vector.__one_past_capacity = new_vector.__first_free = new_vector.__first_location = nullptr;
            }
            __alloc = other.get_allocator();
            return *this;
        }

        template<typename U = T, typename std::enable_if<std::is_same<T, U>::value &&
                                                         std::is_base_of<std::false_type,
                                                                 typename std::allocator_traits<allocator_type>::
                                                                 propagate_on_container_copy_assignment>::value,
                bool>::type = true>
        vector &operator=(const vector &other) {
            resize(other.size());
            _copy_assign_to_vect(__alloc, other.begin(), other.end());
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
                resize(other.size());
                _move_assign_to_vect(__alloc, other.begin(), other.end());
            }
            return *this;
        }

        vector &operator=(std::initializer_list<T> ilist) {
            resize(ilist.size());
            _copy_assign_to_vect(__alloc, ilist.begin(), ilist.end());
            return *this;
        }

        void assign(size_type count, const T &value) {
            erase(begin(), end());
            insert(end(), count, value);
        }

        template<class InputIt, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
                typename std::iterator_traits<InputIt>::iterator_category>::value, bool>::type = true>
        void assign(InputIt first, InputIt last) {
            erase(begin(), end());
            insert(end(), first, last);
        }

        void assign(std::initializer_list<T> ilist) { assign(ilist.begin(), ilist.end()); }

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

        void reserve(size_type new_cap) {
            if (new_cap > capacity()) { _reallocate(new_cap); }
        }

        size_type capacity() const noexcept { return std::distance(__first_location, __one_past_capacity); }

        void shrink_to_fit() {
            if (capacity() != size()) { _reallocate(size()); }
        }

    public: // modifiers
        void clear() noexcept {
            if (__first_location != nullptr) {
                _cleaner(__alloc, {{__first_location, __first_free}}, {{__first_location, capacity()}});
                __first_location = __first_free = __one_past_capacity = nullptr;
            }
        }

        iterator insert(const_iterator pos, const T &value) { return emplace(pos, value); }

        iterator insert(const_iterator pos, T &&value) { return emplace(pos, std::move_if_noexcept(value)); }

        iterator insert(const_iterator pos, size_type count, const T &value) {
            // prevent undefined behaviour from conversion to difference_type
            if (count > max_size()) { throw std::length_error("requested allocation of more than max_size() items."); }
            auto start_distance = std::distance(cbegin(), pos);
            pointer location = _make_space_middle(const_cast<pointer>(pos.location),
                                                  static_cast<difference_type>(count));
            try {
                for (; count != 0; --count, ++location) {
                    std::allocator_traits<allocator_type>::construct(__alloc, location, value);
                }
            } catch (...) {
                _cleaner(__alloc, {{location + 1, __first_free}});
                __first_free = location;
                std::rethrow_exception(std::current_exception());
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
                _copy_to_vect(__alloc, first, last, location);
            } catch (...) {
                _cleaner(__alloc, {{location + count, __first_free}});
                __first_free = location;
                std::rethrow_exception(std::current_exception());
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
                _cleaner(__alloc, {{location + 1, __first_free}});
                __first_free = location;
                std::rethrow_exception(std::current_exception());
            }
            return begin() + start_distance;
        }

        iterator erase(const_iterator pos) { erase(pos, pos + 1); }

        iterator erase(const_iterator first, const_iterator last) {
            _cleaner(__alloc, {{const_cast<pointer>(first.location), const_cast<pointer>(last.location)}});
            try {
                _move_to_vect(__alloc, const_cast<pointer>(last.location), __first_free,
                              const_cast<pointer>(first.location));
            } catch (...) {
                _cleaner(__alloc, {{const_cast<pointer>(last.location), __first_free}});
                __first_free = const_cast<pointer>(first.location);
                std::rethrow_exception(std::current_exception());
            }
            _cleaner(__alloc, {{const_cast<pointer>(last.location), __first_free}});
            __first_free -= std::distance(first, last);
            return const_cast<pointer>(first.location);
        }

        void push_back(const T &value) { insert(end(), value); }

        void push_back(T &&value) { insert(end(), std::move_if_noexcept(value)); }

        template<class... Args>
        void emplace_back(Args &&... args) { emplace(end(), std::forward<Args>(args)...); }

        void pop_back() { erase(end() - 1); }

        void resize(size_type count) { resize(count, value_type()); }

        void resize(size_type count, const value_type &value) {
            if (count < size()) {
                erase(begin() + count, end());
            } else if (count > size()) {
                insert(end(), count - size(), value);
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
        /* copy constructs the elements in (first, last] to where_to (uses the given allocator to do so)
         *
         * parameters -
         * [where_to, where_to + std::distance(first, last)) must exist. the function doesn't allocate memory
         * the storage must be uninitialised or T must be trivially destructible
         *
         * exceptions -
         * this function only throws if the copy constructor of T throws
         * on throw, any objects it constructed are destructed
         */
        template<typename InputIt>
        void _copy_to_vect(allocator_type &alloc, InputIt first, InputIt last, pointer where_to) {
            pointer where_to_backup = where_to;
            try {
                for (; first != last; ++where_to, ++first) {
                    std::allocator_traits<allocator_type>::construct(alloc, where_to, *first);
                }
            } catch (...) {
                _cleaner(alloc, {{where_to_backup, where_to}});
                std::rethrow_exception(std::current_exception());
            }
        }

        /* move constructs the elements in (first, last] to where_to (uses the given allocator to do so)
         *
         * parameters -
         * [where_to, where_to + std::distance(first, last)) must exist. the function doesn't allocate memory
         * the storage must be uninitialised or T must be trivially destructible
         *
         * exceptions -
         * this function only throws if the selected constructor of T throws
         * on throw, any objects it constructed are destructed
         *
         * note - copy constructor is used if it exists and move constructor is throwing
         */
        template<typename InputIt>
        void _move_to_vect(allocator_type &alloc, InputIt first, InputIt last, pointer where_to) {
            using Iter = typename std::conditional<!std::is_nothrow_move_constructible<T>::value &&
                                                   std::is_copy_constructible<T>::value,
                    InputIt, std::move_iterator<InputIt>>::type;
            _copy_to_vect(alloc, Iter(first), Iter(last), where_to);
        }


        /* copy assigns the elements in (first, last] to the elements in this vector
         *
         * parameters -
         * size() must be at least std::distance(first, last)
         * alloc is used for exception handling only
         *
         * exceptions -
         * this function only throws if the copy assignment operator of T throws
         * on throw, all elements in the vector are destructed and size() turns 0
         */
        template<typename InputIt>
        void _copy_assign_to_vect(allocator_type &alloc, InputIt first, InputIt last) {
            pointer curr = __first_location;
            try {
                for (; first != last; ++first, ++curr) { *curr = *first; }
            } catch (...) {
                _cleaner(alloc, {{__first_location, __first_free}});
                __first_free = __first_location;
                std::rethrow_exception(std::current_exception());
            }
        }

        /* move assigns the elements in (first, last] to the elements in this vector
         *
         * parameters - size() must be at least std::distance(first, last)
         * alloc is used for exception handling only
         *
         * exceptions -
         * this function only throws if the selected assignment operator of T throws
         * on throw, all elements in the vector are destructed and size() turns 0
         *
         * note - copy assignment is used if it exists and move assignment is throwing
         */
        template<typename InputIt>
        void _move_assign_to_vect(allocator_type &alloc, InputIt first, InputIt last) {
            using Iter = typename std::conditional<!std::is_nothrow_move_assignable<T>::value &&
                                                   std::is_copy_constructible<T>::value,
                    InputIt, std::move_iterator<InputIt>>::type;
            _copy_assign_to_vect(alloc, Iter(first), Iter(last));
        }

        /* makes uninitialised holes in the vector by moving around elements
         *
         * parameters - location must be reachable from begin().location
         *
         * returns -
         * a pointer corresponding to the pointer sent as argument. this is returned as reallocation in this
         * function can invalidate the previous pointer.
         *
         * exceptions -
         * other than length error for requesting allocation of absurd sizes, this function only throws from
         * a call to _reallocate(). check the comments there for more details.
         */
        pointer _make_space_middle(pointer location, difference_type count) {
            // prevent unsigned overflow and endless new_cap *= 2 loop
            if (size() + count > max_size()) {
                throw std::length_error("requested allocation of more than max_size() items.");
            }
            auto new_cap = capacity();
            if (new_cap < size() + count) {
                new_cap = std::max(capacity() * 2, static_cast<size_type>(1));
                while (new_cap < size() + count) { new_cap *= 2; }
            }
            if (new_cap != capacity() || location != __first_free) {
                auto position = std::distance(__first_location, location);
                _reallocate(new_cap, position, count);
                location = __first_location + position;
            } else {
                __first_free += count;
            }
            return location;
        }

        /* reallocates memory.
         * capacity() is new_cap post reallocation.
         * all iterators, pointers, references are invalidated
         *
         * parameters -
         * skip_pos and skip_count are only used by _make_space_middle, second and third argument to _reallocate
         * anywhere else in this file is an error.
         *
         * exceptions -
         * can throw length_error if absurd sizes are requested. no changes to the vector.
         * allocation of new memory can throw. no changes to the vector.
         *
         * exceptions can be thrown while the new memory is filled -
         * if T is move-only, all elements in the vector are destructed and size() becomes 0.
         * no changes to the vector otherwise.
         */
        void _reallocate(size_type new_cap, size_type skip_pos = 0, difference_type skip_count = 0) {
            if (new_cap > max_size()) {
                throw std::length_error("requested allocation of more than max_size() items.");
            }
            pointer new_first_location = std::allocator_traits<allocator_type>::allocate(__alloc, new_cap);
            pointer new_first_free = new_first_location + size() + skip_count;
            try {
                _move_to_vect(__alloc, __first_location, __first_location + skip_pos, new_first_location);
            } catch (...) {
                _cleaner(__alloc, {}, {{new_first_location, new_cap}});
                if (!std::is_copy_constructible<T>::value) { erase(begin(), end()); }
                std::rethrow_exception(std::current_exception());
            }
            try {
                _move_to_vect(__alloc, __first_location + skip_pos, __first_free,
                              new_first_location + skip_pos + skip_count);
            } catch (...) {
                _cleaner(__alloc, {{new_first_location, new_first_location + skip_pos}},
                         {{new_first_location, new_cap}});
                if (!std::is_copy_constructible<T>::value) { erase(begin(), end()); }
                std::rethrow_exception(std::current_exception());
            }
            clear();
            __first_location = new_first_location;
            __first_free = new_first_free;
            __one_past_capacity = new_first_location + new_cap;
        }

        /* uses alloc to destroy each element in each (first, second] pair in the list destroy
         * uses alloc to deallocate first in each pair in the list deallocate
         *
         * Note: destroy (but not deallocate) happens in reverse. the initializer_list is read from
         * last to first and each element in the iterator range (first, second] is destroyed from
         * last to first.
         */
        template<typename U = T, typename std::enable_if<
                std::is_same<T, U>::value && std::is_trivially_destructible<T>::value, bool>::type = true>
        void _cleaner(allocator_type &alloc, std::initializer_list<std::pair<pointer, pointer>> destroy,
                      std::initializer_list<std::pair<pointer, size_type>> deallocate = {}) {
            for (auto p = destroy.end(); p-- != destroy.begin();) {
                for (auto iter = p->second; iter-- != p->first;) {
                    std::allocator_traits<allocator_type>::destroy(alloc, iter);
                }
            }
            for (const auto &p : deallocate) {
                std::allocator_traits<allocator_type>::deallocate(alloc, p.first, p.second);
            }
        }

        // SFINAE, skips destroy list if T is trivially destructible
        template<typename U = T, typename std::enable_if<
                std::is_same<T, U>::value && !std::is_trivially_destructible<T>::value, bool>::type = true>
        void _cleaner(allocator_type &alloc, std::initializer_list<std::pair<pointer, pointer>> destroy,
                      std::initializer_list<std::pair<pointer, size_type>> deallocate = {}) {
            for (const auto &p : deallocate) {
                std::allocator_traits<allocator_type>::deallocate(alloc, p.first, p.second);
            }
        }

    private: // data members
        allocator_type __alloc; // = allocator_type();
        pointer __first_location = nullptr;
        pointer __first_free = nullptr;
        pointer __one_past_capacity = nullptr;
    };
}

#endif //C_PRIMER_5TH_VECTOR_H
