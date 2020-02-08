template<typename T>
class compareNeighbours{
    public:
        int operator() (const T& p1, const T& p2)
        {
            return p1.getCost() > p2.getCost();
        }
};



template<typename T, typename P>
class sorts {
  T internal_data_store;
  P comparator;
public:
  sorts(const P(*compar)(const T &, const T &));
  void sort(T&)
};
