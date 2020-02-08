#include "sort.hpp"

namespace sorting{

  template<typename T, typename P>
  sorts<T>::sorts(const P(*compar)(const T &, const T &), T data_to_sort){
    this.internal_data_store = data_to_sort;
    this.comparator = compar;
  }

  template<typename T>
  void sorts<T>::sort(){
    std::sort(this.internal_data_store.begin(), this.internal_data_store.end(), this.comparator);
  }

}
