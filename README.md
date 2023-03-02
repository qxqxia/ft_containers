# ft_containers
## recode the STL containers with the C++98 standard
### vector
  - std::allocator
  - the inner data structure
  - The difference between vector and map iterator
  ```
      vector: random_access_iterator;
      map: bidirectional_iterator;
  ```
  
  - use of friend keyword
### map
  - the inner data structure -> RBT or AVL...
  - pair and make_pair
  - map is ordered
  - allocator::rebind
  - swap function
  - use of friend keyword
  - insert or delete iterators
  
### set

### stack
  - use your own vector class as default underlying container

### std::iterator_traits
  - 5 main types of iterators
  ```
      input_iterator;
      output_iterator;
      forward_iterator: public input_iterator;
      bidirectional_iterator : public forward_iterator;
      random_access_iterator : public bidirectional_iterator; 
  ```
  - 5 properities from an iterator
  ```
      iterator_category;
      difference_type;
      value_type;
      pointer;
      reference;
  ```
### std::reverse_iterator
### others
```
    std::enable_if (implement it in a C++98 manner)
    std::is_integral
+ std::equal and/or std::lexicographical_compare
+ std::pair
+ std::make_pair
