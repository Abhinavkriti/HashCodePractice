#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DanceFloor 
{
public:
    vector<string> findSolution(int N, int C, int D, int S, vector<vector<string>> &tileColors, vector<vector<int>> marks) 
    {
        vector<string> ret(S);
        vector<int> x(D);
        vector<int> y(D);
        for (int i = 0; i < D; i++) 
        {
            x[i] = marks[i][0];
            y[i] = marks[i][1];
        }
        for (int i = 1; i <= S; i++) 
        {
            string cmd = "";
            for (int j = 0; j < D; j++) 
            {
                int k = 2;
                for (; k < marks[j].size(); k += 3) 
                {
                    if (marks[j][k] >= i) break;
                }
                int xd = marks[j][k - 2];
                int yd = marks[j][k - 1];
                if (xd > x[j]) 
                {
                    x[j]++;
                    cmd += 'R';
                } else if (xd < x[j]) 
                {
                    x[j]--;
                    cmd += 'L';
                } else if (yd > y[j]) 
                {
                    y[j]++;
                    cmd += 'D';
                } else if (yd < y[j]) 
                {
                    y[j]--;
                    cmd += 'U';
                } else 
                {
                    cmd += '-';
                }
            }
            ret[i - 1] = cmd;
        }
        return ret;
    }
};

int main() 
{
    int N, C, D, S;
    cin >> N >> C >> D >> S;

    vector<vector<string>> tileColors(N, vector<string>(N));
    for (int y = 0; y < N; y++) 
    {
        for (int x = 0; x < N; x++) 
        {
            cin >> tileColors[y][x];
        }
    }

    vector<vector<int>> marks(D);
    for (int i = 0; i < D; i++) 
    {
        int numMarks;
        cin >> numMarks;
        marks[i].resize(3 * numMarks);
        for (int j = 0; j < 3 * numMarks; j++) 
        {
            cin >> marks[i][j];
        }
    }

    DanceFloor sol;
    vector<string> ret = sol.findSolution(N, C, D, S, tileColors, marks);

    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++) 
    {
        cout << ret[i] << endl;
    }
    cout.flush();
    return 0;
}
