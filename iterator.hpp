#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft{
    /*5 type d'iterators迭代器按功能分成五类:
    InputIterator：输入迭代器。支持对容器元素的逐个遍历，以及对元素的读取（input);
    OutputIterator：输出迭代器。支持对容器元素的逐个遍历，以及对元素的写入（output);
    forwardIterator：前向迭代器。向前逐个遍历元素。可以对元素读取;
    BidirectionalIterator：双向迭代器。支持向前向后逐个遍历元素，可以对元素读取;
    RandomAccessIterator：随机访问迭代器。支持O(1)时间复杂度对元素的随机位置访问，支持对元素的读取*/
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    //std::iterator_traits
    //迭代器类型萃取可以提取迭代器的各个类型
    template< class Iter >
    struct iterator_traits{
        /*迭代器要求五个类型定义
        value_type:迭代器所指对象的类型
        difference_type:两个迭代器之间距离的类型
        pointer:迭代器所指对象的原生指针类型
        reference:迭代器所指对象的原生引用类型
        iterator_category:迭代器的类型。*/
        typedef typename Iter::iterator_category    iterator_category;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
    }
    //Specializations
    template <class T> 
    class iterator_traits<T*> {
        public:
            typedef random_access_iterator_tag          iterator_category;
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef T*                                  pointer;
            typedef T&                                  reference;
      
    };
    template <class T> 
    class iterator_traits<const T*> {
        public:
            typedef random_access_iterator_tag          iterator_category;
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef T*                                  pointer;
            typedef T&                                  reference;
    };
    //std::iterator
    //std::iterator is the base class provided to simplify definitions of the required types for iterators.
    template<class Category,
                class T,
                class Distance = std::ptrdiff_t,
                class Pointer = T*,
                class Reference = T&> 
    struct iterator{
        typedef typename Category   iterator_category;
        typedef typename T          value_type;
        typedef typename Distance   difference_type;
        typedef typename Pointer    pointer;
        typedef typename Reference  reference;
    }
    //std::reverse_iterator
    template<class Iter>
    class reverse_iterator{
        public:
            //Member types
            typedef typename iterator_traits<Iterator>::iterator_category    iterator_category;
            typedef typename iterator_traits<Iterator>::value_type           value_type;
            typedef typename iterator_traits<Iterator>::difference_type      difference_type;
            typedef typename iterator_traits<Iterator>::pointer              pointer;
            typedef typename iterator_traits<Iterator>::reference            reference;
            typedef Iterator                                                 iterator_type;
        public:
            reverse_iterator(void){}
            explicit reverse_iterator (iterator_type it) :_it(it){}
            template <class Iter>  
            reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it._it){} //??reverse_iterator::base
            virtual ~reverse_iterator(void){}
            //Member functions
            //++ and -- has two modeles
            iterator_type base()const {return this->_it;}
            //Returns a reference to the element pointed to by the iterator
            reference& operator*()const	{
                iterator_type tmp = _it;
                return *(--tmp);
            }

            reverse_iterator operator+(difference_type n) const{
                return (reverse_iterator(_it - n));
            }	
            reverse_iterator& operator++(){
                --_it;
                return (*this);
            }
            reverse_iterator  operator++(int){
                reverse_iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            reverse_iterator& operator+=(difference_type n){
                _it -= n;
                return (*this);
            }
            reverse_iterator operator-(difference_type n) const{
                return (reverse_iterator(_it + n));
            }	
            reverse_iterator& operator--(){
                ++_it;
                return (*this);
            }
            reverse_iterator  operator--(int){
                reverse_iterator tmp = *this;
                --(*this);
                return tmp;
            }	
            reverse_iterator& operator-= (difference_type n){
                _it += n;
                return (*this);
            }	
            pointer operator->() const{
                return &(operator*());
            }	
            reference operator[] (difference_type n) const{
                return (base()[-n-1]);
            }	  
        private:
            iterator_type _it;
    };
    //Non-member function overloads
    relational operators??
    
    //std::operator+
    template <class Iterator>  
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it){
        return (rev_it + n);
    }
    //std::operator-
    template <class Iterator>  
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
        return (lhs.base() - rhs.base());
    }
}

#endif