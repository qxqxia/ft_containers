# Ft_containers
## Recode part of the C++ STL with the C++98 standard
## 1. Containers
### *Sequence Containers*:
> implement data structures that can be accessed in a sequential way 
- #### Vector
  - std::allocator
  - the inner data structure -> dynamic array
  - capacity is automatically expanded by the container
  - copy and swap
  - the difference between vector and map iterator
  ```
      vector: random_access_iterator;
      map:    bidirectional_iterator;
  ```
  
  - use of friend keyword
### *Associative Containers*:
>  implement sorted data structures that can be quickly searched (O(log n) complexity)
- #### Map
  - the inner data structure -> RBT or AVL...
  - pair and make_pair
  - map is ordered
  - allocator::rebind
  - swap function
  - use of friend keyword
  - insert or delete iterators
  
- #### Set (in bonus)

### *Container Adaptors*:
>  provide a different interface for sequential containers
- #### Stack
  - use your own vector class as default underlying container

## 2. Iterators
### *std::iterator_traits*
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

### *Iterator Adaptors*:
- ### reverse_iterator
### utils
```
    std::enable_if (implement it in a C++98 manner)
    std::is_integral
    std::equal and/or std::lexicographical_compare
    std::pair
    std::make_pair
```

