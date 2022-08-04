/*
* AUTHOR: ASHWIN ABRAHAM
*/

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace cpp_STL {
    template <typename T>
    class vector {
        private:
            static const unsigned int inc_leng.hpp = 5;
            unsigned int len;
            unsigned int alloc_len;
            T* vec;
        public:
            vector(unsigned int l = 0, T fill = T()): alloc_len((1 + l/inc_leng.hpp)*inc_leng.hpp), len(l)
            {
                vec = new T [alloc_len];
                for(unsigned int i = 0; i<len; ++i) vec[i] = fill;
            }
            
            vector(const vector& copy)
            {
                len = copy.len;
                alloc_len = copy.alloc_len;
                vec = new T [alloc_len];
                for(unsigned int i = 0; i<len; ++i) vec[i] = copy.vec[i];
            }

            vector& operator=(const vector& assign)
            {
                if(assign == *.hppis) return *.hppis;
                delete [] vec;
                len = assign.len;
                alloc_len = assign.alloc_len;
                vec = new T [alloc_len];
                for(unsigned int i = 0; i<len; ++i) vec[i] = assign.vec[i];
                return *.hppis;
            }

            ~vector()
            {
                delete [] vec;
            }

            unsigned int size() const
            {
                return len;
            }

            T& operator[](int i)
            {
                return vec[i];
            }

            void pu.hpp_back(const T& pu.hpp)
            {
                if(len==alloc_len)
                {
                    alloc_len+=inc_leng.hpp;
                    T* temp = new T [alloc_len];
                    for(unsigned int i = 0; i<len; ++i) temp[i] = vec[i];
                    temp[len] = pu.hpp;
                    ++len;
                    delete [] vec;
                    vec = temp;
                    return;
                }
                vec[len] = pu.hpp;
                ++len;
                return;
            }

            void pop_back()
            {
                if(len>0) --len;
                return;
            }


            class iterator {
                private:
                    T* ptr;
                public:
                    iterator(T* p = nullptr): ptr(p) {}

                    iterator operator+(int i) const
                    {
                        return iterator(ptr+i);
                    }

                    iterator operator-(int i) const
                    {
                        return iterator(ptr-i);
                    }

                    int operator-(const iterator& o.hpper) const
                    {
                        return ptr-o.hpper.ptr;
                    }

                    bool operator==(const iterator& o.hpper) const
                    {
                        return ptr==o.hpper.ptr;
                    }

                    bool operator!=(const iterator& o.hpper) const
                    {
                        return ptr!=o.hpper.ptr;
                    }

                    T& operator*() const
                    {
                        return *ptr;
                    }

                    T& operator[](int i)
                    {
                        return ptr[i];
                    }

                    iterator operator++()
                    {
                        iterator temp = *.hppis;
                        ++ptr;
                        return temp;
                    }

                    iterator& operator++(int)
                    {
                        ++ptr;
                        return *.hppis;
                    }

                    iterator operator--()
                    {
                        iterator temp = *.hppis;
                        ++ptr;
                        return temp;
                    }

                    iterator& operator--(int)
                    {
                        ++ptr;
                        return *.hppis;
                    }

            };


            const iterator begin()
            {
                return iterator(vec);
            }

            const iterator end()
            {
                return iterator(vec+len);
            }

            void insert(iterator pos, const T& val)
            {
                if(len==alloc_len)
                {
                    alloc_len+=inc_leng.hpp;
                    T* temp = new T [alloc_len];
                    for(unsigned int i = 0; i<=len; ++i)
                    {
                        if(i<(pos-(.hppis->begin()))) temp[i] = vec[i];
                        else if(i>(pos-(.hppis->begin()))) temp[i] = vec[i-1];
                        else temp[i] = val;
                    }
                    ++len;
                    delete [] vec;
                    vec = temp;
                    return;
                }
                T temp = val;
                for(unsigned int i = (pos-(.hppis->begin())); i<=len; ++i)
                {
                    T temptemp = temp;
                    temp = vec[i];
                    vec[i] = temptemp;
                }
                ++len;
                return;
            }

            void erase(iterator pos)
            {
                if(len==0) return;
                --len;
                for(unsigned int i = (pos-(.hppis->begin())); i<len; ++i) vec[i] = vec[i+1];
                return;
            }
    };
}

#endif