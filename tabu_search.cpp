#include "tabu_search.hpp"

void tabu_search::getInput(const std::string & inputFile){
    //std::vector<library> & lib, std::unordered_map<int, int> book_score_mapping, int num_days
   std::ifstream infile(inputFile);
   if (!infile.is_open()) {
       return;
   }
   std::string line;
   std::getline(infile, line);
   std::stringstream iss(line);
   iss >> this->num_books >> this->num_libraries >> this->num_days;
   std::getline(infile, line);
   iss.clear();
   iss.str(line);
   int temp;
   for(int i = 0; i < this->num_books; ++i){
     iss >> temp;
     this->book_score_mapping[i] = temp;
     this->considered_books[i]++;
   }
   this->libraries.resize(this->num_libraries);
   for(int i = 0; i < this->num_libraries; ++i){
     std::getline(infile, line);
     iss.clear();
     iss.str(line);
     int num_book, signup_process, library_rate;
     iss >> num_book >> signup_process >> library_rate;
     int temp2;
     std::getline(infile, line);
     iss.clear();
     iss.str(line);
     std::vector<int> book_state(num_book);
     for(int j = 0; j < num_book; ++j){
       iss >> temp2;
       book_state[j] = temp2;
     }
     // oh man im using raw pointers now....
     this->libraries[i] = std::make_shared<library>(book_state, book_score_mapping, signup_process, library_rate, i);
   }
   std::copy(this->libraries.begin(), this->libraries.end(), std::inserter(this->free_libraries, this->free_libraries.end()));
}

tabu_search::tabu_search(const int & tabu_list, const std::string & fileName){
    // std::cout << "starting schtuff" << std::endl;
    this->getInput(fileName);
    // first = true;
    numIter = 0;

    best_score = INT_MIN;
    current_state_score = INT_MIN;

    for(int i = 0; i < num_libraries; ++i){
        this->state.at(i) = libraries.at(i);
    }

    // this->state = {5, 11, 12, 16, 15, 17, 18, 2, 7, 10, 4, 8, 20, 3, 1, 13, 6, 19, 14, 9};

    this->tabu_list_size = tabu_list;

    this->recency_frequency_matrix[this->state] = this->tabu_list_size;
    this->frequency_matrix[this->state] = 1;

    // std::cout << "ending schtuff" << std::endl;
}

int tabu_search::find_cost(){
  int cost = 0;
  int day = 0;
  int lib_id = 0;
  while(day < this->num_days){
    if(lib_id == state.size()){
      break;
    }
    auto temp_lib = state.at(lib_id++);
    if(day + temp_lib->getTimeToSetup() < this->num_days){
      day += temp_lib->getTimeToSetup();
      int temper;
      for(int i = 0; i < temp_lib->getBookSize() || day <= this->num_days; ++i){
        for(int j = 0; j < temp_lib->getNumBookRate() || i + j < temp_lib->getBookSize(); ++j){
            if(considered_books[i] > 0){
              cost = cost + temp_lib->getBooks().at(i++)->cost;
            }
            else{
              j--;
            }
            temper = j;
        }
        i += temper;
        day++;
      }
    }
    else{
      break;
    }
  }

  best_score = std::max(cost, best_score);

  return cost;
}

int tabu_search::find_cost(const std::vector<std::shared_ptr<library> > & state){
  int cost = 0;
  int day = 0;
  int lib_id = 0;
  while(day < this->num_days){
    if(lib_id == state.size()){
      break;
    }
    auto temp_lib = state.at(lib_id++);
    if(day + temp_lib->getTimeToSetup() < this->num_days){
      day += temp_lib->getTimeToSetup();
      int temper;
      for(int i = 0; i < temp_lib->getBookSize() || day <= this->num_days; ++i){
        for(int j = 0; j < temp_lib->getNumBookRate() || i + j < temp_lib->getBookSize(); ++j){
            if(considered_books[i] > 0){
              cost = cost + temp_lib->getBooks().at(i++)->cost;
            }
            else{
              j--;
            }
            temper = j;
        }
        i += temper;
        day++;
      }
    }
    else{
      break;
    }
  }

  best_score = std::max(cost, best_score);

  return cost;
}

// void tabu_search::print_matrix(const std::vector<library>& matrix){
//     for(auto & row: matrix){
//         // std::cout << "whats up3" << std::endl;
//         std::cout << row << std::endl;
//     }
// }

void tabu_search::swap(std::vector<std::shared_ptr<library> > & state, const int & index1, const int & index2){
    auto temp = state.at(index1);
    state.at(index1) = state.at(index2);
    state.at(index2) = temp;
}

std::shared_ptr<library> tabu_search::remove(std::vector<std::shared_ptr<library> > & state, int index){
    auto temp = state.at(index);
    state.erase(state.begin() + index);
    return temp;
}

void tabu_search::add(std::vector<std::shared_ptr<library> > & state, const std::shared_ptr<library>  & lib){
    state.emplace_back(lib);
}

std::shared_ptr<library> tabu_search::findEmptyLibrary(int index){
    for(const auto &c: free_libraries){
      if(c->getID() == index){
        return c;
      }
    }
}

// void tabu_search::print_recency_matrix(){
//     std::cout << "Recency Matrix" << std::endl;
//     for(auto &i: this->recency_frequency_matrix){
//         print_matrix(i.first);
//         std::cout << "::::: " << i.second << std::endl;
//     }
// }

bool tabu_search::try_add_tabu(const std::vector<std::shared_ptr<library> >  & state){

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

    std::vector<std::shared_ptr<library> > state_copy = this->state;
    //std::cout << "Initial State:" << std::endl;
    //print_matrix(this->state);
    //std::cout << this->best_score << std::endl;

    std::priority_queue<neighbour, std::vector<neighbour>, compareNeighbours> pq;

    // determine neighbours
    for(int i = 0; i < this->state.size(); ++i){
        for(int j = i+1; j < this->state.size(); ++j){
            this->swap(state_copy, i, j);
            pq.emplace(neighbour(i,j,find_cost(state_copy)));
            this->swap(state_copy, j, i);
        }
    }
    //forgive me lord for i have sinned
    for(const auto & elem: free_libraries){
      this->add(state_copy, elem);
      pq.emplace(neighbour(-elem->getID(),-elem->getID(), find_cost(state_copy)));
      this->remove(state_copy, this->state.size() - 1);
    }
    for(int i = 0; i < this->state.size(); ++i){
      auto temp = this->remove(state_copy, i);
      pq.emplace(neighbour(i,i, find_cost(state_copy)));
      this->add(state_copy, temp);
    }
    // first = true;
    bool cancellation_token = false;
    while(!cancellation_token){
        neighbour x = pq.top();
        std::shared_ptr<library> temp;
        if(x.getIndex1() < 0){
            temp = this->findEmptyLibrary(x.getIndex1());
            this->add(state_copy, temp);
        }
        else if(x.getIndex1() == x.getIndex2()){
            temp = this->remove(state_copy, x.getIndex1());
        }
        else{
            this->swap(state_copy, x.getIndex1(), x.getIndex2());
        }

        // print_matrix(state_copy);
        if(!try_add_tabu(state_copy)){
          if(x.getIndex1() < 0){
              this->remove(state_copy, this->state.size() - 1);
          }
          else if(x.getIndex1() == x.getIndex2()){
              this->add(state_copy, temp);
          }
          else{
              this->swap(state_copy, x.getIndex1(), x.getIndex2());
          }
          pq.pop();
            // first = false;
        }
        else{
            this->state = state_copy; // move to new state
            if(x.getIndex1() < 0){
                free_libraries.erase(temp);
                for(const auto &c : temp->getBooks()){
                  considered_books[c->id]++;
                }
            }
            else if(x.getIndex1() == x.getIndex2()){
                free_libraries.insert(temp);
                for(const auto &c: temp->getBooks()){
                  considered_books[c->id]--;
                }
            }
            else{
                this->swap(state_copy, x.getIndex1(), x.getIndex2());
            }
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
    while(numIter < 10000){
        move();
        // test_cases();
        numIter++;
    }
    std::cout << "Final state:" << std::endl;
    // print_matrix(this->state);
    test_cases();
    std::cout << "Number of Iterations: " << std::to_string(numIter) << std::endl;
}

void tabu_search::test_cases(){
    std::cout << "Final Cost: " << std::to_string(this->find_cost()) << std::endl;
}
