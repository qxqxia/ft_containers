#include "../vector.hpp"
#include "../map.hpp"
#include "../stack.hpp"
#include <iostream>
#include <memory>

void printstr(std::string string) {
  std::cout << string << std::endl;
}

template<class T>
void print_size(ft::vector<T> vec)
{
  std::cout << "size: " << vec.size() << std::endl;
  std::cout << "max_size: " << vec.max_size() << std::endl;
  std::cout << "capacity: " << vec.capacity() << std::endl;
}

template<class T>
void  printvec(ft::vector<T> vec)
{
  for (typename ft::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
     std::cout << *it << ' ';
  std::cout << "\n";
}

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

void vec_constructor_test(void){
 
  printstr("---------Test constructor-----------\n");
  printstr("[ vector info]");
  ft::vector<int> first(4);                                // empty vector of ints
  ft::vector<int> second(4, 42);                       // four ints with value 100
  ft::vector<int> third (second.begin(),second.end());  // iterating through second
  ft::vector<int> fourth (third);
  int ints[] = {0,-42,42,1,442}; 
  ft::vector<int> fifth (ints,ints + sizeof(ints) / sizeof(int));
  printvec(first);
  printvec(second);
  printvec(third);
  printvec(fourth);
  printvec(fifth);
  first = second;
  std::cout << "test opearator " << std::endl;
  std::cout << "first vector: ";
  printvec(first);
  std::cout << std::endl;
}

/*
** iterator test
*/
void vec_iterator_test(void)
{
  printstr("---------Test iterator-----------\n");
  printstr("[ vector info]");
  ft::vector<int> vec;
  for(int i = 1; i < 6; i++)
    vec.push_back(i);
  printvec(vec);
  ft::vector<int>::iterator it = vec.begin();
  std::cout << "iterator begin(it) is: "<< *it << std::endl;
  ft::vector<int>::iterator ite = vec.end();
  std::cout << "iterator end(ite) is: "<< *(ite - 1) << std::endl;
  it++;
  std::cout << "begin++(it++) is: "<< *it << std::endl;
  ite--;
  std::cout << "end--(ite--) is: "<< *(ite - 1) << std::endl;
  it += 1;
  std::cout << "it + 1 is: "<< *it << std::endl;
  ite -= 1;
  std::cout << "ite - 1  is: "<< *(ite - 1) << std::endl;
  
  ft::vector<int>::const_iterator cit = vec.begin();
  std::cout << "const_iterator begin is: " << *cit << std::endl;
  ft::vector<int>::const_iterator cite = vec.end();
  std::cout << "const_iterator end is: " <<*(cite - 1) << std::endl;
  
  ft::vector<int>::reverse_iterator rit = vec.rbegin();
  std::cout << "reverse_iterator rbegin is: " << *rit << std::endl;
  ft::vector<int>::reverse_iterator rite = vec.rend();
  std::cout <<  "reverse_iterator rend is: " << *(rite - 1) << std::endl;
  
  ft::vector<int>::const_reverse_iterator crit = vec.rbegin();
  std::cout << "const_reverse_iterator rbegin is: " << *crit << std::endl;
  ft::vector<int>::const_reverse_iterator crite = vec.rend();
  std::cout << "const_rend is: " << *(crite - 1) << std::endl << std::endl;
  
}
/*
** test size , max_size, capatity, empty
*/
void vec_size_test()
{
  printstr("---------Test size/max_size/empty/capatity-----------\n");
  printstr("[ vector info]");
  ft::vector<int> vec;
  std::cout << "int: " << (vec.empty() == true ? "vec is empty" : "vec is not empt" )<< std::endl;
  vec.push_back(1);
  std::cout << "int: " << (vec.empty() == true ? "vec is empty" : "vec is not empt" )<< std::endl;
  print_size(vec);
  std::cout << std::endl;
  ft::vector<char> vecchar;
  std::cout << "char: " << (vecchar.empty() == true ? "vecchar is empty" : "vechar is not empt" )<< std::endl;
  vecchar.push_back('a');
  vecchar.push_back('b');
  std::cout << "char: " << (vecchar.empty() == true ? "vecchar is empty" : "vechar is not empt" )<< std::endl;
  printvec(vecchar);
  print_size(vecchar);
  std::cout << std::endl;
  
}
/*
** test resize reserve
*/
void vec_resize_test()
{
  printstr("---------Test resize / reserve-----------\n");
  printstr("[ vector info]");
  ft::vector<int> vec;
  vec.push_back(42);
  printvec(vec);
  vec.resize(4, 1);
  printvec(vec);
  vec.resize(2);
  printvec(vec);
  vec.resize(4, 10);
  printvec(vec);
  vec.reserve(5);
  print_size(vec);
  std::cout << std::endl;
  
}
/*
** Element access test
*/
void vec_element_test()
{
  printstr("---------Test Element acces(at , [], front. back-----------\n");
  printstr("[ vector info]");
  ft::vector<int> vec;
  for(int i = 1; i <= 10; i++)
    vec.push_back(i);
  printvec(vec);
  std::cout << "at(0) is: " << vec.at(0) << std::endl;
  std::cout << "operator[9] is: " << vec[9] << std::endl;
  std::cout << "operator[10] is: " << vec[10] << std::endl;
  std::cout << "front is: " << vec.front() << std::endl;
  std::cout << "back is: " << vec.back() << std::endl;
  std::cout << std::endl;
  
}
/*
** assign test
*/
void vec_assign_test()
{
  printstr("---------Test  assign-----------\n");
  printstr("[ vector info]");
  ft::vector<int> first;
  ft::vector<int> second;
  ft::vector<int> third;
  first.assign (7,100);             // 7 ints with a value of 100
  printvec(first);
  ft::vector<int>::iterator it;
  it=first.begin() + 1;
  second.assign (it, first.end() - 1); // the 5 central values of first
  printvec(second);
  int ints[] = {1776,7,4};
  third.assign (ints,ints+3);   // assigning from array.
  printvec(third);
  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
 std::cout << std::endl;
  
}
/*
** insert test
*/
void vec_insert_test()
{
  printstr("---------Test  insert-----------\n");
  printstr("[ vector info]");
  ft::vector<int> vector (3,100); //100 100 100
  printvec(vector);
  
  ft::vector<int>::iterator it;
  it = vector.begin();
  it = vector.insert (it , 200 ); // 200 100 100 100
  printvec(vector);
  // second insert
  vector.insert (it,2,300); //300 300 200 100 100 100 
  printvec(vector);
  // third insert with another vector
  it = vector.begin(); //it在第一位
  ft::vector<int> anothervector (2,400);
  vector.insert (it+2,anothervector.begin(),anothervector.end()); //300 300 400 400 200 100 100 100 第三位插入两个400
  printvec(vector);
  // fourth insert with a tab
  int array [] = { 501,502,503 };
  vector.insert (vector.begin(), array, array+3);  // 501 502 503 300 300 400 400 200 100 100 100begin位插入一个数组
  printvec(vector);
  std::cout << std::endl;
  
}
/*
** test push_back pop_back 
*/
void vec_push_pop_test()
{
  printstr("---------Test  push_back / pop_back -----------\n");
  printstr("[ vector info]");
  ft::vector<std::string> vec;
  vec.push_back("hello");
  vec.push_back("42");
  printvec(vec);
  vec.pop_back();
  printvec(vec);
  std::cout << std::endl;

}
/*
** erase test
*/
void vec_erase_test()
{
  printstr("---------Test erase-----------\n");
  printstr("[ vector info]");
  ft::vector<int> vector;
  for (int i=1; i<=10; i++) vector.push_back(i);
  printvec(vector);
  // erase the 6th element
  vector.erase (vector.begin()+5);
  printvec(vector);
  // erase the first 3 elements:
  vector.erase (vector.begin(),vector.begin()+3);
  printvec(vector);
  std::cout << std::endl;

}
/*
** swap clear test
*/
void vec_swap_clear_test()
{
  printstr("---------Test swap / clear-----------\n");
  printstr("[ vector info]");
  ft::vector<int> foo (3,100);   // three ints with a value of 100
  ft::vector<int> bar (5,200);   // five ints with a value of 200
  foo.swap(bar);
  std::cout << "foo contains:";
  printvec(foo);
  std::cout << "bar contains:";
  printvec(bar);
  foo.clear();
  print_size(foo);
  std::cout << std::endl;
  
}
/*
**function overloads test
*/
void vec_overloads_test()
{
  printstr("---------Test overloads-----------\n");
  printstr("[ vector info]");
  ft::vector<int> foo (3,100);
  std::cout << "foo vec is: ";
  printvec(foo);
  ft::vector<int> bar (5,200);
  std::cout << "bar vec is: ";
  printvec(bar);
  /* operator != */
  if (foo != bar) std::cout << "foo and bar is not same" << std::endl;
   /* operator < */
  if (foo < bar) std::cout << "foo is smaller then bar" << std::endl;
  /* operator > */
  if (foo > bar) std::cout << "foo is biger then bar" << std::endl;
  /*operator == , <= ,>= */
  foo = bar;
  std::cout << "foo vec is: ";
  printvec(foo);
  if (foo == bar) std::cout << "foo and bar is same" << std::endl;
  if (foo >= bar) std::cout << "foo is biger or same then bar" << std::endl;
  if (foo <= bar) std::cout << "foo is smaller or same then bar" << std::endl << std::endl;
  
}


void _vector()
{
  vec_constructor_test();
  vec_iterator_test();
  vec_size_test();
  vec_resize_test();
  vec_element_test();
  vec_assign_test();
  vec_insert_test();
  vec_push_pop_test();
  vec_erase_test();
  vec_swap_clear_test();
  vec_overloads_test();
}

void map_constructor_test(void){

  printstr("---------Test constructor, destructor, operaror= ----------");
  printstr("[ info]");
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

void map_iterator_test(){
  printstr("---------Test  iterator ----------");
  printstr("[ map info]");
  ft::map<int,int> first;
  first[1] = 0;
  first[2] = 42;
  first[3] = -42;
  ft::map<int, int>::iterator it = first.begin();
  ft::map<int, int>::iterator ite = first.end();
  for(; it != ite; ++it)
      std::cout << it->first << " => " << it->second << std::endl;
  ft::map<int, int>::const_iterator cit = first.begin();
  ft::map<int, int>::const_iterator cite = first.end();
  for(; cit != cite; ++cit)
      std::cout << cit->first << " => " << cit->second << std::endl;
  std::cout << std::endl;
  /*test reverse iterator*/
  ft::map<int, int>::reverse_iterator rit = first.rbegin();
  ft::map<int, int>::reverse_iterator rite = first.rend();
  for(; rit != rite; ++rit)
      std::cout << rit->first << " => " << rit->second << std::endl;
  ft::map<int, int>::const_reverse_iterator crit = first.rbegin();
  ft::map<int, int>::const_reverse_iterator crite = first.rend();
  for(; crit != crite; ++crit)
      std::cout << crit->first << " => " << crit->second << std::endl;
  std::cout << std::endl;
}

void map_size_test(){
  
  printstr("---------Test size /empty-----------");
  printstr("[ map info]");
  ft::map<int,int> first;
  std::cout << (first.empty() == 1? "first is empty": "first is not empty") << std::endl;
  std::cout << "first size is: " << first.size() << std::endl;
  
  first[1] = 2;
  std::cout << (first.empty() == 1? "first is empty": "first is not empty") << std::endl;
  std::cout << "first size is: " << first.size() << std::endl;
  
  
  ft::map<char,std::string> second;
  std::cout << (second.empty() == 1? "second is empty": "second is not empty") << std::endl;
  std::cout <<  "second size is: " << second.size() << std::endl;
 
  second[1] = 2;
  std::cout << (second.empty() == 1? "second is empty": "second is not empty") << std::endl;
  std::cout <<  "second size is: " << second.size() << std::endl << std::endl;
}

void map_element_test() {
  printstr("---------Test element-----------");
  printstr("[ map info]");
  ft::map<char, std::string> first;
  first['a']= "hello";
  first['b']= "world";
  std::cout << "first['a'] is : " << first['a'] << std::endl;
  std::cout << "first['b'] is : " << first['b'] << std::endl << std::endl;
}

void map_insert_test(){
  printstr("---------Test insert-----------");
  printstr("[ map info]");
  printstr("(1)insert value_type& val: ");
  ft::map<char,int> first;
  first.insert(ft::pair<char, int>('a', 100));
  first.insert(ft::pair<char, int>('b', 200));
  first.insert(ft::pair<char, int>('c', 300));
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  ft::map<char,int>::iterator it = first.begin();
  ft::map<char, int>::iterator ite = first.end();
  for(; it != ite; ++it)
      std::cout << it->first << " => " << it->second << std::endl;
  printstr("(2)insert one iterator");
  ft::map<char,int> anothermap;
  anothermap.insert(first.begin(),first.find('c'));
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  printstr("(3)insert same key: ");
  ft::pair<ft::map<char,int>::iterator, bool> ret;
  ret = first.insert ( ft::pair<char, int>('a' ,400));
  if (ret.second==false) {
    std::cout << "element 'a' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }
  ft::map<char,int>::iterator iit = first.begin();
  ft::map<char, int>::iterator iite = first.end();
  for(; iit != iite; ++iit)
      std::cout << iit->first << " => " << iit->second << std::endl;
  std::cout << std::endl;
}


void map_erase_test(){
  
  printstr("---------Test erase-----------");
  printstr("[ map info]");
  ft::map<char,int> first;
  first.insert(ft::pair<char, int>('a', 100));
  first.insert(ft::pair<char, int>('b', 200));
  first.insert(ft::pair<char, int>('c', 300));
  first.insert(ft::pair<char, int>('d', 400));
  ft::map<char,int>::iterator it = first.begin();
  ft::map<char,int>::iterator ite = first.end();
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  first.erase(it);
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  first.erase('b');
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  it = first.begin();
  ite = first.end();
  first.erase(it, ite);
  printmap_val("map first val is: ", first);
  printmap_key("map first key is: ", first);
  std::cout << std::endl;
}

void map_swap_clear_test(){
  printstr("---------Test  swap, clear-----------");
  printstr("[ map info]");
  ft::map<char,int> first;
  first['a'] = 42;
  first['b'] = 0;
  printmap("first is:", first);
  ft::map<char,int> second;
  second['1'] = 100;
  second['2'] = 200;
  printmap("second is:", second);
  first.swap(second);
  printstr("---aftre swap: ");
  printmap("first is:", first);
  printmap("second is:", second); 
  printstr("---aftre clear: ");
  first.clear();
  printmap("first is:", first);
  second.clear();
  printmap("second is:", second); 
  std::cout << std::endl;
}

void map_keyComp_valComp_test(){
  /*test key_comp*/
  printstr("---------Test  keyComp valComp-----------");
  printstr("[ map info]");
  ft::map<char,int> first;
  ft::map<char,int>::key_compare firstcomp = first.key_comp();
  first['a']=100;
  first['b']=200;
  first['c']=300;
  std::cout << "first contains:\n";
  char highest = first.rbegin()->first;     // key value of last element
  ft::map<char,int>::iterator it = first.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( firstcomp((*it++).first, highest) );
  /*test value_comp*/
  ft::map<char,int> second;
  second['x']=1001;
  second['y']=2002;
  second['z']=3003;
  std::cout << "second contains:\n";
  ft::pair<char,int> sechighest = *second.rbegin();          // last element
  ft::map<char,int>::iterator secit = second.begin();
  do {
    std::cout << secit->first << " => " << secit->second << '\n';
  } while (second.value_comp()(*secit++, sechighest) );
  std::cout << std::endl;
}

void	map_find_test() {
  printstr("---------Test find-----------");
  printstr("[ map info]");
  ft::map<char, int> first;
  first['a'] = 100;
  first['b'] = 200;
  first['c'] = 300;
  printmap("first is:", first);
  ft::map<char, int>::iterator it;
  printstr("find 'a': ");
  it = first.find('a');
  std::cout << it->first << " => " << it->second << std::endl;
  printstr("find 'b': ");
  it = first.find('b');
  std::cout << it->first << " => " << it->second << std::endl;
  ft::map<char, int>::const_iterator cit;
  printstr("find const 'c': ");
  cit = first.find('c');
  std::cout << cit->first << " => " << cit->second << std::endl << std::endl;
}

void map_count_test() {
  printstr("---------Test count-----------");
  printstr("[ map info]");
  ft::map<char, int> first;
  first['a'] = 100;
  first['b'] = 200;
  first['c'] = 300;
  std::cout << (first.count('b') == 1? "'b' is exist": "'b' is not exist")<< std::endl;
  std::cout << (first.count('e') == 1? "'a' is exist": "'e' is not exist")<< std::endl;
  std::cout << std::endl;
}

void map_bound_test() {
  printstr("---------Test bound-----------");
  printstr("[ map info]");
  ft::map<int, char> first;
  first[1] = 'a';
  first[2] = 'b';
  first[3] = 'c';
  ft::map<int, char>::iterator it;
  printstr("to find node >= 1");
  it = first.lower_bound(1);
  std::cout << it->first << " => " << it->second << std::endl;
  printstr("to find node > 1");
  it = first.upper_bound(1);
  std::cout << it->first << " => " << it->second << std::endl;
  printstr("to find node > 2");
  it = first.upper_bound(2);
  std::cout << it->first << " => " << it->second << std::endl << std::endl;
}

void map_equal_test() {
  printstr("---------Test equal_Range-----------");
  printstr("[ map info]");
  ft::map<int, char> first;
  first[1] = 'a';
  first[2] = 'b';
  first[3] = 'c';
  ft::pair<ft::map<int, char>::iterator, ft::map<int, char>::iterator> ret;
  ret = first.equal_range(1); //ret = <lower_bound , upp_bound>
  std::cout << ret.first->first << " => " << ret.first->second << std::endl;
  std::cout << ret.second->first << " => " << ret.second->second << std::endl << std::endl;
  
  ret = first.equal_range(2); //ret = <lower_bound , upp_bound>
  std::cout << ret.first->first << " => " << ret.first->second << std::endl;
  std::cout << ret.second->first << " => " << ret.second->second << std::endl << std::endl;
}

void _map()
{
  map_constructor_test();
  map_iterator_test();
  map_size_test();
  map_element_test();
  map_insert_test();
  map_erase_test(); 
  map_swap_clear_test();
  map_keyComp_valComp_test();
  map_find_test();
  map_count_test();
  map_bound_test();
  map_equal_test();
}

void stack_constructor_test(void){
  
    printstr("---------Test constructor-----------\n");
    printstr("[ stack info]");
    ft::vector<int> vec (2,200); 
    ft::stack<int, ft::vector<int> > stack (vec);
    std::cout << stack.size() << std::endl;

    ft::vector<char> vecchar (3, 'a');
    ft::stack<char, ft::vector<char> > stackchar (vecchar);
    std::cout << stackchar.size() << std::endl;

    ft::vector<std::string> vecstr (4, "42");
    ft::stack<std::string, ft::vector<std::string> > stackstr (vecstr);
    std::cout << stackstr.size() << std::endl << std::endl;
}

void stack_modifier_test() {

    printstr("---------Test empty push top pop-----------\n");
    printstr("[ stack info]");
    ft::stack<int> stack;
    std::cout << "int: " << (stack.empty() == true ? "stack is empty" : "stack is not empt" )<< std::endl;

    stack.push(1);
    std::cout << "int: " << (stack.empty() == true ? "stack is empty" : "stack is not empt" )<< std::endl;
    std::cout << "size is: " << stack.size() << std::endl;
    std::cout << "top element is: " << stack.top() << std::endl;
    
    stack.push(2);
    std::cout << "size is: " << stack.size() << std::endl;
    std::cout << "top element is: " << stack.top() << std::endl;

    stack.pop();
    stack.pop();
    std::cout << "int: " << (stack.empty() == true ? "stack is empty" : "stack is not empt" )<< std::endl;
    std::cout << std::endl;
}

void stack_operators_test()
{
    printstr("---------Test relational operators-----------\n");
    printstr("[ stack info]");
    ft::stack<int, ft::vector<int> > stack1;
    std::cout << "stack1 size is: " << stack1.size() << std::endl;
    ft::stack<int, ft::vector<int> > stack2;
    std::cout << "stack2 size is: " << stack2.size() << std::endl;
    if (stack1 == stack2) std::cout << "stdack1 and stack2 is same" << std::endl;
    
    ft::vector<int> vec (2,200);
    ft::stack<int, ft::vector<int> >stack3(vec);
    std::cout << "stack1 size is: " << stack1.size() << std::endl;
    std::cout << "stack3 size is: " << stack3.size() << std::endl;
    if (stack1 != stack3) std::cout << "stdack1 and stack3 is not same" << std::endl;
    if (stack1 < stack3) std::cout << "stdack1 is smaller then stack3" << std::endl;
    if (!(stack1 > stack3)) std::cout << "stdack1 is smaller then stack3" << std::endl;
    if (stack1 <= stack3) std::cout << "stdack1 is smaller or same then stack3" << std::endl<< std::endl;
    if (stack1 >= stack3) std::cout << "stdack1 is bigger or same then stack3" << std::endl; //not show
}


void _stack()
{
    stack_constructor_test();
    stack_modifier_test();
    stack_operators_test();
}

int main()
{
  _vector();
  _map();
  _stack();
  return (0);
}
