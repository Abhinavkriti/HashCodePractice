#include "tabu_search.hpp"

tabu_search::tabu_search(const int & tabu_list, int num_books, int num_libraries, int num_days){
    // std::cout << "starting schtuff" << std::endl;

    // first = true;
    numIter = 0;

    best_score = INT_MIN;
    current_state_score = INT_MIN;
    this.num_days = num_days;

    libraryRead.get(libraries);
    // bookMapping.get(book_score_mapping);

    for(const auto & c: book_score_mapping){ // I'll take the time cost here
      considered_books[c.first]++;
    }

    for(int i = 0; i < num_libraries; ++i){
        this->state.at(i) = libraries.at(i);
    }



    // this->state = {5, 11, 12, 16, 15, 17, 18, 2, 7, 10, 4, 8, 20, 3, 1, 13, 6, 19, 14, 9};

    this->tabu_list_size = tabu_list;

    this->recency_frequency_matrix[this->state] = this->tabu_list_size;
    this->frequency_matrix[state] = 1;

    // std::cout << "ending schtuff" << std::endl;
}

int tabu_search::find_cost(){
    int cost = 0;
    int day = 0;
    int lib_id = 0;
    while(day < this.num_days){
      auto temp_lib = this.state.at(lib_id++);
      if(day + temp_lib.getTimeToSetup() < this.num_days){
        day += temp_lib.getTimeToSetup();
        if(day + std::ceil(temp_lib.getBookSize()/temp_lib.getNumBookRate()) < this.num_days){
          cost += temp_lib.getCost();
        }
        else{
          cost += temp_lib.getCumSumCost.at((this.num_days - day)*temp_lib.getNumBookRate());
        }
      }
    }

    best_score = std::max(cost, best_score);

    return cost;
}

void tabu_search::print_matrix(const std::vector<library>& matrix){
    for(auto & row: matrix){
        // std::cout << "whats up3" << std::endl;
        std::cout << row << std::endl;
    }
}

void tabu_search::swap(std::vector<library> & state, const int & index1, const int & index2){
    int temp = state.at(index1);
    state.at(index1) = state.at(index2);
    state.at(index2) = temp;
}

library tabu_search::remove(std::vector<library> & state, int index){
    auto temp = state.at(index);
    state.erase(state.begin() + index);
    return temp;
}

void tabu_search::add(std::vector<library> & state, const library & lib){
    state.emplace_back(lib);
}

library tabu_search::findEmptyLibrary(){
    if(this.considered_libraries.empty()){
      return null;
    }
    return *this.considered_libraries.begin();
}

void tabu_search::print_recency_matrix(){
    std::cout << "Recency Matrix" << std::endl;
    for(auto &i: this->recency_frequency_matrix){
        print_matrix(i.first);
        std::cout << "::::: " << i.second << std::endl;
    }
}

bool tabu_search::try_add_tabu(const library & state){

    if(this->recency_frequency_matrix.find(state) == this->recency_frequency_matrix.end()){
        this->recency_frequency_matrix[state] = this->tabu_list_size + 1;
        for(auto &i: this->recency_frequency_matrix){
            i.second = i.second - 1;
        }
        return true;
    }
    else{
        if(this->recency_frequency_matrix[state] <= 0 && this->frequency_matrix[state] <= 3){
            // was previously in tabu list but outlasted its tenure
            this->recency_frequency_matrix[state] = this->tabu_list_size + 1;
            this->frequency_matrix[state]++;
            for(auto &i: this->recency_frequency_matrix){
                i.second = i.second - 1;
            }
            return true;
        }
        else{
            // print_recency_matrix();
            // if(first){ //if best among immediate neighbours available
            //     this->recency_frequency_matrix[state] = this->tabu_list_size + 1;
            //     for(auto &i: this->recency_frequency_matrix){
            //         i.second = i.second - 1;
            //     }
            //     return true;
            // }
            return false;
        }
    }
}

void tabu_search::move(){

    std::vector<int> state_copy = this->state;
    //std::cout << "Initial State:" << std::endl;
    //print_matrix(this->state);
    //std::cout << this->best_score << std::endl;

    std::priority_queue<neighbour, std::vector<neighbour>, compareNeighbours> pq;

    // determine neighbours
    for(int i = 0; i < this.state.size(); ++i){
        for(int j = i+1; j < this.state.size(); ++j){
            this->swap(state_copy, i, j);
            pq.emplace(neighbour(i,j,find_cost(state_copy)));
            this->swap(state_copy, j, i);
        }
    }
    //forgive me lord for i have sinned
    for(int i = 0; i < this.state.size(); ++i){
      if(this->findEmptyLibrary() == null){
        break;
      }
      this->add(state_copy, this->findEmptyLibrary());
      pq.emplace(neighbour(-1,-1, find_cost(state_copy)));
      this->remove(state_copy, this.state.size() - 1);
    }
    for(int i = 0; i < this.state.size(); ++i){
      auto temp = this->remove(state_copy, i);
      pq.emplace(neighbour(-1,-1, find_cost(state_copy)));
      this->add(state_copy, temp);
    }
    // first = true;
    bool cancellation_token = false;
    while(!cancellation_token){
        neighbour x = pq.top();
        this->swap(state_copy, x.getIndex1(), x.getIndex2());
        // print_matrix(state_copy);
        if(!try_add_tabu(state_copy)){
            this->swap(state_copy, x.getIndex1(), x.getIndex2());
            pq.pop();
            // first = false;
        }
        else{
            this->state = state_copy; // move to new state
            // this->current_state_score = x.getCost();
            // std::cout << "COST" << std::to_string(x.getCost()) << std::endl;
            pq.pop();
            cancellation_token = true;
        }
    }
    //std::cout << "Moved to new state:" << std::endl;
    //print_matrix(this->state);
    // std::cout << this->current_state_score << std::endl;
}

void tabu_search::solve(){
    while(this->find_cost() > 1286){
        move();
        // test_cases();
        numIter++;
    }
    std::cout << "Final state:" << std::endl;
    print_matrix(this->state);
    test_cases();
    std::cout << "Number of Iterations: " << std::to_string(numIter) << std::endl;
}

void tabu_search::test_cases(){
    std::cout << "Final Cost: " << std::to_string(this->find_cost()) << std::endl;
}
