#include <algorithm>
#include <vector>
#include <functional>

namespace sorting{

  template<typename T, typename P>
  class sorts {
    T internal_data_store;
    std::function<P(T, T)> comparator;
  public:
    sorts(const P(*compar)(const T &, const T &));
    void sort(T&)
  };

}
