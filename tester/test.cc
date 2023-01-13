#include <iostream>
#include "map.hpp"
#include "iterator.hpp"
#include "mapIterator.hpp"
#include "AVL.hpp"
#include <algorithm>

//void resize(int, int, ft::vector<int>& );

/*int	main()
{
	ft::vector<int>		V(5, 10);
	ft::vectIterator<ft::vector<int> >	it;
	it = V.begin();
	while (it != V.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	
	vector<int>	v;
	ft::vectIterator	i(v);
	
	cout << v.size() << endl;
	resize(10, 9, v);
	cout << v.size() << endl;
	
	ft::vectIterator<random_access_iterator_tag>	i;
	i = v.begin();
	for(; i->pointer != v.end(); i->pointer++){ cout << *(i->pointer) << " " << endl; }
	cout << endl;
	
}*/

/*void resize(int n, int val, ft::vector<int>& V)
{
	if (n < (int)V.size())
		V.erase(V.begin() + n, V.end());
	else
		V.insert(V.end(), n - (int)V.size(), val);
}*/

template < class Key, class T>
void  printmap(std::string string, ft::map<Key, T> map) {
   std::cout << string << std::endl;
   for (typename ft::map<Key, T>::iterator it = map.begin(); it != map.end(); ++it)
      std::cout << it->first << " => " << it->second << std::endl;
}

template < class Key, class T>
void  printmap_val(std::string string, ft::map<Key, T> map)
{
      std::cout << string;
  for (typename ft::map<Key, T>::iterator it = map.begin(); it != map.end(); ++it)
      std::cout << it->second << ' ';
  std::cout << "\n";
}

template < class Key, class T>
void  printmap_key(std::string string, ft::map<Key, T> map)
{
  std::cout << string;
  for (typename ft::map<Key, T>::iterator it = map.begin(); it != map.end(); ++it)
      std::cout << it->first << ' ';
  std::cout << "\n";
}

void map_constructor_test(void){

  //printstr("---------Test constructor, destructor, operaror= ----------");
  //printstr("[ info]");
  ft::map<char,int> first;
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  first['a']=42;
  first['b']=-42;
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  /*test  with as many elements as the range [first,last)*/
  ft::map<char,int> second (first.begin(),first.end());
  printmap_val("map second val is: ", second);
  printmap_key("map second key is: ", second);
  /*test copy*/
  ft::map<char,int> third (second);
  printmap_val("map third val is: ", third);
  printmap_key("map third key is: ", third);
  /*test operator = */
  third['c'] = 0;
  first = third;
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  std::cout << std::endl;
}

void _map(){
	map_constructor_test();
}

int main(){
	_map();
}
