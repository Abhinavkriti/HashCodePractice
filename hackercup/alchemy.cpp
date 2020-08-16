#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <utility>

bool solution(const int & N, const std::string & stones){
    std::queue<std::string> bfs_queue;
    bfs_queue.emplace(stones);
    while(!bfs_queue.empty()){
        auto x = bfs_queue.front();
        bfs_queue.pop();
        for(int i = 1; i < x.size() - 1; ++i){
            if(x.at(i - 1) == x.at(i) && x.at(i) == x.at(i+1) && x.at(i-1) == x.at(i+1)){
                continue;
            }
            else{
                int B = 0;
                int A = 0;
                for(int y = -1; y <= 1; ++y){
                    if(x.at(i+y) == 'B'){
                        B++;
                    }
                    else{
                        A++;
                    }
                }
                auto cpy = x;
                if(B>A){
                    cpy.replace(i-1, 3, "B");
                }
                else{
                    cpy.replace(i-1, 3, "A");
                }
                if(cpy.size() == 1){
                    // std::cout << "returning true: " << cpy << std::endl;
                    return true;
                }
                bfs_queue.emplace(cpy);
            }
        }
    }
    return false;
}

int main(int argc, char * argv[]){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::string stones;
    //assuming that input txt doc is argv[1]
    std::string inputTxt = argv[1];
    // output txt doc is argv[2]
    std::string outputTxt = argv[2];

    std::ifstream inputFile(inputTxt);
    std::ofstream outputFile(outputTxt);

    std::string T;
    std::getline(inputFile,T);
    int shards = stoi(T);
    for(int i = 0; i < shards; ++i){
        std::getline(inputFile, T);
        N = stoi(T);
        stones.clear();
        std::getline(inputFile, stones);
        // std::cout << stones << std::endl;
        bool sol = true;
        if(stones.size() != 1){
            sol = solution(N, stones);
        }
        std::string case_num = "Case #";
        case_num.append(std::to_string(i+1));
        case_num.append(": ");
        outputFile.write(case_num.c_str(), sizeof(char)*case_num.size());
        std::string x = "Y\n";
        if(!sol){
            x = "N\n";
        }
        outputFile.write(x.c_str(), sizeof(char)*x.size());
    }
    outputFile.close();
    inputFile.close();
}