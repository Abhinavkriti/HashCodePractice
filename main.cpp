#include "tabu_search.hpp"
#include <memory>

int main( int argc, const char* argv[] )
{
	auto x = std::make_unique<tabu_search>(2, 3, 4, 5);
	x->solve();
}
