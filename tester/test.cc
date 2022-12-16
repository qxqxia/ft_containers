#include "iostream"
#include "vector"
#include "iterator.hpp"
#include "vecIterator.hpp"

using	namespace std;

void resize(int, int, vector<int>& );

int	main()
{
	vector<int>		V(5, 10);
	ft::vectIterator<vector<int>>	it;
	it = V.begin();
	while (it != V.end())
	{
		cout << *it << endl;
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

void resize(int n, int val, vector<int>& V)
{
	if (n < (int)V.size())
		V.erase(V.begin() + n, V.end());
	else
		V.insert(V.end(), n - (int)V.size(), val);
}


