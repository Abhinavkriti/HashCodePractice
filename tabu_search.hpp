#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <type_traits>
#include <map>
#include <queue>
#include <ctime>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

#define INT_MIN -100000

struct book{
	int id;
	int cost;
	book(int id, int cost){
		id = id;
		cost = cost;
	}
};

class library{
	std::vector<std::shared_ptr<book> > bookcase;
	int time_to_setup;
	int num_books;
	int cost;
	int id;

	// friend std::ostream& operator<<(std::ostream& os, const library& dt);

	public:
		library() = default;

		library(const std::vector<int> & state, const std::unordered_map<int, int> & book_score_mapping, const int time_to_setup, const int num_books, const int id){
			for(auto & c: state){
				bookcase.emplace_back(std::make_shared<book>(c, book_score_mapping.at(c)));
			}
			std::sort(bookcase.begin(), bookcase.end(), [](const std::shared_ptr<book>&x, const std::shared_ptr<book>&y){
				return x->cost >= y->cost;
			});
			this->time_to_setup = time_to_setup;
			this->num_books = num_books;
			this->id = id;
		}

		int getCost(){
			return this->cost;
		}

		std::vector<std::shared_ptr<book>> getBooks(){
			return this->bookcase;
		}

		int getBookSize(){
			return this->bookcase.size();
		}

		int getTimeToSetup(){
			return this->time_to_setup;
		}

		int getNumBookRate(){
			return this->num_books;
		}

		int getID(){
			return this->id;
		}

};

// std::ostream& operator<<(std::ostream& os, const library& dt)
// {
// 	os << dt.id << '/' << dt.num_books << '/' << dt.time_to_setup;
// 	return os;
// }

class neighbour{

    int index1;
    int index2;
    int spcost;

    public:
        neighbour(int i, int j, int cost){
            index1 = i;
            spcost = cost;
            index2 = j;
        }

        neighbour() = default;

        int getCost() const {
            return this->spcost;
        }

        int getIndex1(){
            return this->index1;
        }

        int getIndex2(){
            return this->index2;
        }
};

class compareNeighbours{
    public:
        int operator() (const neighbour& p1, const neighbour& p2)
        {
            return p1.getCost() > p2.getCost();
        }
};

class tabu_search{

    std::vector<std::shared_ptr<library> > libraries;
		std::unordered_map<int, int> considered_books;
		std::set<std::shared_ptr<library> > free_libraries;

    int tabu_list_size;
    std::vector<std::shared_ptr<library> > state;

    std::map<std::vector<std::shared_ptr<library>>, int> recency_frequency_matrix;
    std::map<std::vector<std::shared_ptr<library>>, int> frequency_matrix;

    int best_score;
    int current_state_score;
    int numIter;
		int num_books;
		int num_libraries;
		int num_days;

    int find_cost();
    int find_cost(const std::vector<std::shared_ptr<library> > &);
    void swap(std::vector<std::shared_ptr<library> > & state, const int & index1, const int & index2);
		std::shared_ptr<library> remove(std::vector<std::shared_ptr<library> > &, int index);
		void add(std::vector<std::shared_ptr<library> > &, const std::shared_ptr<library> & lib );
    bool try_add_tabu(const std::vector<std::shared_ptr<library> >  &);
    void print_recency_matrix();
		std::shared_ptr<library> findEmptyLibrary(int index);
		void getInput(const std::string & inputFile);

    public:
				std::unordered_map<int, int> book_score_mapping;

        tabu_search(const int & tabu_list, const std::string & );
        void move();
        void solve();
        void print_matrix(const std::vector<std::vector<int>> & matrix);
        void print_matrix(const std::vector<int> & matrix);
				~tabu_search() = default;
        void test_cases();
};
