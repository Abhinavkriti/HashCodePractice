#include "tabu_search.hpp"

int main( int argc, const char* argv[] )
{
	std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
	std::string testFile = "testFile.txt";
	std::unique_ptr<tabu_search> x(new tabu_search(2, testFile));
	x->solve();
	return 0;
}
