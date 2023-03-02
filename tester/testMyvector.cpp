#include <iostream>
#include <vector>
#include <cstddef>

class Myvector{
    public:
        Myvector(){ std::cout << "default.\n"; }
        
        typedef typename std::vector<int>   VectorType;

        VectorType::iterator begin() { return m_v.begin(); }
        VectorType::iterator end() { return m_v.end(); }
        
        bool empty() const
        {
            if (_size != 0)
            {
                return false;
            }
            return true;
        }
   
    private:
        VectorType m_v;
        size_t     _size;
};

int main(){
    Myvector v1;

    if (v1.empty()){
        std::cout << "size is 0.\n"; 
    }
    std::cout << "myvector contains: ";
    for (auto it = v1.begin(), end = v1.end(); it != end; ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << "test compile.\n";
}
   