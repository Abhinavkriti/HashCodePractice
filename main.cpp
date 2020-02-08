
#include "tabu_search.hpp"





// int main(){
//     std::srand(std::time(NULL));
//     int tabu_tenure = rand() % 10 + 300;
//     std::cout << "Tabu Tenure: " << std::to_string(tabu_tenure) << std::endl;
//     tabu_search ts(tabu_tenure);
//     ts.solve();
// }


int main(int argc, char **argv) {
    CSVReader a_example = CSVReader("a_example.in", ' ');


    std::vector<std::vector<int>> input = a_example.get();
    std::cout << input.size()  << std::endl;

    for (int i = 0; i < input.size(); ++i) {

        for (int j = 0; j < input[i].size(); ++j) {
            std::cout << input[i][j] << " ";
        }
        std::cout << input[i].size() << std::endl;
    }

    return 0;
}