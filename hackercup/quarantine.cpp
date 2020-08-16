#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <utility>

struct rabbit {
    int x;
    int y;
};

int nChoosek( int n, int k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

rabbit solution(const int & N, const int & K, const int & A, const int & B, const int & C, std::vector<int> & e, const std::string & stones){
    rabbit x;
    // construct the entire N vector
    for(int i = K + 2; i <= N; ++i){
        e.emplace_back(((A*e.at(i-2) + B*e.at(i-1) + C)%(i-1)) + 1);
    }

    // find the number of uninfected 
    int uninfect_to_infect = 0;
    int uninfect_to_uninfect = 0;
    
    int num_uninfected = 0;
    int num_infected = 0;

    for(int i = 0; i <= N; ++i ){
        if(stones.at(i) == '#'){
            num_infected++;
        }
        else{
            num_infected++;
        }

        if(stones.at(i) == '#' || stones.at(e[i]) == '#'){
            uninfect_to_infect++;
        }
        else{
            uninfect_to_uninfect++;
        }
    }

    if(num_uninfected - 1 > uninfect_to_uninfect){
        
    }

    return x;
}

int main(int argc, char * argv[]){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, K, A, B, C;
    std::string stones;
    //assuming that input txt doc is argv[1]
    std::string inputTxt = argv[1];
    // output txt doc is argv[2]
    std::string outputTxt = argv[2];

    std::ifstream inputFile(inputTxt);
    std::ofstream outputFile(outputTxt);

    std::string T;
    std::getline(inputFile,T);
    int testcases = stoi(T);
    for(int i = 0; i < testcases; ++i){
        std::getline(inputFile, T);
        std::istringstream iss(T);
        iss >> N;
        iss >> K;
        stones.clear();
        std::getline(inputFile, stones);
        std::string K_val;
        std::getline(inputFile, K_val);
        std::istringstream iss2(K_val);
        std::vector<int> e(std::istream_iterator<int>(iss2), {});
        e.insert(e.begin(), 1);
        std::getline(inputFile, T);
        std::istringstream iss3(T);
        iss3 >> A;
        iss3 >> B;
        iss3 >> C;
        rabbit sol = solution(N, K, A, B, C, e, stones);
        std::string case_num = "Case #";
        case_num.append(std::to_string(i+1));
        case_num.append(": ");
        outputFile.write(case_num.c_str(), sizeof(char)*case_num.size());
        std::string x;
        x.append(std::to_string(sol.x));
        x.append(" ");
        x.append(std::to_string(sol.y));
        x.append("\n");
        outputFile.write(x.c_str(), sizeof(char)*x.size());
    }
    outputFile.close();
    inputFile.close();

    return 0;
}