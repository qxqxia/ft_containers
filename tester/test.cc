#include "iostream"
#include "vector.hpp"
#include "iterator.hpp"
#include "vecIterator.hpp"
#include <algorithm>

void resize(int, int, ft::vector<int>& );

int	main()
{
	ft::vector<int>		V(5, 10);
	ft::vectIterator<ft::vector<int> >	it;
	it = V.begin();
	while (it != V.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	/*
	vector<int>	v;
	// ft::vectIterator	i(v);
	
	cout << v.size() << endl;
	resize(10, 9, v);
	cout << v.size() << endl;
	
	ft::vectIterator<random_access_iterator_tag>	i;
	i = v.begin();
	//for(; i->pointer != v.end(); i->pointer++){ cout << *(i->pointer) << " " << endl; }
	cout << endl;
	*/
}

void resize(int n, int val, ft::vector<int>& V)
{
	if (n < (int)V.size())
		V.erase(V.begin() + n, V.end());
	else
		V.insert(V.end(), n - (int)V.size(), val);
}


