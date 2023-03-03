#include <iostream>
#include <cstddef> //std::ptrdiff_t
#include <iterator> //std::random_access_iterator_tag

#define size 100

class Integers{
    public:
        //default constructor
        Integers() { for (int i = 0; i < size; i++) m_data[i] = 1; }

        class Iterator{       
            public:
                typedef typename std::random_access_iterator_tag iterator_category;
                typedef typename std::ptrdiff_t                  difference_type;
                typedef int                                      value_type;
                typedef int*                                     pointer;
                typedef int&                                     reference;

                Iterator(pointer ptr) : m_ptr(ptr) {}

                reference operator*() const { return *m_ptr;}
                pointer operator->() { return m_ptr;}
                Iterator& operator++(){
                    m_ptr++;
                    return *this;
                }
                Iterator operator++(int){
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                //nom-member == and !=
                friend bool operator==(const Iterator& a, const Iterator& b){
                    return a.m_ptr == b.m_ptr;
                }

                friend bool operator!=(const Iterator& a, const Iterator& b){
                    return a.m_ptr != b.m_ptr;
                } 
            private:
                pointer m_ptr;
        };

         Iterator begin(){return Iterator( &m_data[0] );}
         Iterator end(){return Iterator( &m_data[size] );}
    
    private:
        int m_data[size];
};

int main(){
    Integers    nums;

    for (auto it = nums.begin(), end = nums.end(); it != end; ++it){
        const auto i = *it;
        std::cout << i << '\n';
    }
}

