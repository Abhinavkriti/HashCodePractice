#include <algorithm>
#include <vector>
#include <queue>

namespace sorting{

  template<typename T, typename P>
  class sorts {
    T internal_data_store;
    P comparator;
  public:
    sorts(const P(*compar)(const T &, const T &));
    void sort(T&)
  };

}
