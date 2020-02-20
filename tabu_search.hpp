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
#include <map>

class CSVReader
{
	std::string fileName;
    char delimiter;

    public:
        CSVReader(std::string filename, char delimiter=',') :
                fileName(filename),
                delimiter(delimiter)
        { }

        std::vector<std::vector<int>> get();
        void set(std::string & fileName);
};

void CSVReader::set(std::string & fileName){
    this->fileName = fileName;
}

std::vector<std::vector<int>> CSVReader::get()
{
    std::vector<std::vector<int>> dataList;
	std::cout << fileName <<std::endl;
    std::ifstream file(fileName);
    if (file) {
        std::cout << "read file" <<std::endl;
    }
	std::string line;

	while(std::getline(file,line))
    {
        std::cout << "csvreader::get::whileGetLine" << std::endl;
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<int> parsedRow;
        while(std::getline(lineStream,cell, this->delimiter))
        {
            parsedRow.emplace_back(std::stoi(cell));
        }

        dataList.emplace_back(parsedRow);
    }
	// Close the File
	file.close();

    return dataList;
}

class library{
	std::vector<int> & state;
	int time_to_setup;
	int num_books;
	int cost;
	int id;

	void calcCost(const std::unordered_map<int> & bookMapping){
		int cost = 0;
		for(const auto & c: state){
			cost += bookMapping.at(c);
		}
		this.cost = cost;
	}

public:
	library(std::vector<int> & state, int time_to_setup, int num_books, int id){
		this.state = std::sort(state.begin(), state.end(), greater<int>());
		this.time_to_setup = time_to_setup;
		this.num_books = num_books;
		this.id = id;
		calcCost();
	}

	int getCost(){
		return this.cost;
	}

	std::vector<int> getBooks(){
		return this.state;
	}

	int getTimeToSetup(){
		return this.time_to_setup;
	}

	int getNumBooks(){
		return this.num_books;
	}

	ostream& operator<<(ostream& os, const library& dt)
	{
	  os << dt.id << '/' << dt.num_books << '/' << dt.time_to_setup;
	  return os;
	}

}

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

    CSVReader libaryRead = CSVReader("/home/batman/Documents/hashcode_comp/libraries.csv");
		CSVReader bookMapping = CSVReader("/home/batman/Documents/hashcode_comp/bookMapping.csv");
		CSVReader otherInfo = CSVReader("/home/batman/Documents/hashcode_comp/otherInfo.csv");

    std::vector<library> libraries;
		std::unordered_set<int> considered_books;
		std::unordered_map<int> book_score_mapping;

    int tabu_list_size;
    std::vector<int> state;

    std::map<library, int> recency_frequency_matrix;
    std::map<library, int> frequency_matrix;

    int best_score;
    int current_state_score;
    int numIter;
		int num_books;
		int num_libraries;
		int num_days;

    int find_cost();
    int find_cost(const std::vector<library> &);
    void swap(std::vector<library> & state, const int & index1, const int & index2);
		void remove(std::vector<library> &, int index);
		void add(std::vector<library> &, const library & lib )
    bool try_add_tabu(const std::vector<int> &);
    void print_recency_matrix();

    public:
        tabu_search(const int & tabu_list, int num_books, int num_libraries, int num_days );
        void move();
        void solve();
        void print_matrix(const std::vector<std::vector<int>> & matrix);
        void print_matrix(const std::vector<int> & matrix);

        void test_cases();
};