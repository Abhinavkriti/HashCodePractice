#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <utility>

template <typename T>
void printArray(const std::vector<T> & array){
    for(const T & c: array){
        std::cout << std::to_string(c) << " ";
    }
    std::cout << "\n";
}

void printMatrix(const std::vector<std::vector<char> > & result){
    for(const auto &c : result){
        for(const auto &d: c ){
            std::cout << d;
        }
        std::cout << "\n";
    }
}

void bfs(std::vector<std::vector<char> > & adj_matrix, const int & i, const std::string &I, const std::string &O){
    std::vector<bool> explored(adj_matrix.size(), false);
    std::queue<std::pair<int, int> > bfs_queue;
    bfs_queue.emplace(std::make_pair<int,int>(static_cast<int>(i), static_cast<int>(i)));
    if(O.at(i) == 'N'){
        adj_matrix[i][i] = 'Y';
        return;
    }
    while(!bfs_queue.empty()){
        auto x = bfs_queue.front();
        bfs_queue.pop();
        if(explored.at(x.second) == false){
            if(O.at(x.first) == 'Y'){
                adj_matrix[x.first][x.second] = 'Y';
            }
            else{
                adj_matrix[x.first][x.second] = 'N';
            }
            if(O.at(x.second) == 'Y'){
                if(x.second+1 < I.size()){
                    if(I.at(x.second+1) == 'Y'){
                        bfs_queue.emplace(std::make_pair<int, int>(static_cast<int>(x.second), static_cast<int>(x.second+1)));
                    }
                }
                if(x.second-1 >= 0){
                    if(I.at(x.second-1) == 'Y'){
                        bfs_queue.emplace(std::make_pair<int, int>(static_cast<int>(x.second), static_cast<int>(x.second-1)));
                    }
                }
            }
        }
        // printArray<bool>(explored);
        explored[x.second] = true;
        // printArray<bool>(explored);
        adj_matrix[i][x.second] = 'Y';
    }
}


std::vector<std::vector<char> > solution(const int & N, const std::string &I, const std::string &O){
    std::vector<std::vector<char> > adj_matrix(N, std::vector<char>(N, 'X'));

    for(int i = 0; i < N; ++i){
        bfs(adj_matrix, i, I, O);
    }

    for(auto &c : adj_matrix){
        for(auto &d: c ){
            if(d == 'X'){
                d = 'N';
            }
        }
    }

    return adj_matrix;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::string I;
    std::string O;
    int cases;
    std::cin >> cases;
    std::cin.ignore();
    for(int i = 0; i < cases; ++i){
        I.clear();
        O.clear();
        // readInput(N, I, O);
        std::cin >> N;
        std::cin.ignore();
        std::getline(std::cin, I);
        std::getline(std::cin, O);
        auto x = solution(N, I, O);
        std::cout << "Case #" << std::to_string(i+1) << ": \n";
        printMatrix(x);
    }
}