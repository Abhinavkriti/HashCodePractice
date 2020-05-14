#include <iostream>
//#include <stack>

using namespace std;

int main(int argc, char * argv[]) {
    int n,q;
    scanf("%d", &n);
    int f[n]{0};
    int fCheck[n]{0};
    int numPos[2]{0};
    for ( int i = 0; i < n; i ++ ) {
        scanf("%d", &f[i]);
        fCheck[f[i]] += 1;
        int checkVal = fCheck[f[i]];
        if ( checkVal >= 2) numPos[0] -= 1;
        else numPos[0] += 1;
    }
    int g[n]{0};
    int gCheck[n]{0};
    for ( int i = 0; i < n; i ++ ) {
        scanf("%d", &g[i]);
        gCheck[g[i]] += 1;
        int checkVal = gCheck[g[i]];
        if ( checkVal >= 2) numPos[1] -= 1;
        else numPos[1] += 1;
    }
    //cout << "Numpos: " << numPos[0] << " " << numPos[1] << endl;
    scanf("%d", &q);
    bool saidYes[2];
    saidYes[0] = saidYes[1] = false;
    bool shareValues = false;
    bool init[2];
    init[0] = init[1] = true;
    for ( int i = 0; i < q; i ++ ) {
        shareValues = shareValues || ((fCheck[i] == 1) && (gCheck[i] == 1));
        char* c[3];
        scanf("%s", c[0]);
        if ( init[i%2] ) {
            saidYes[i%2] = (*c[0] == 'Y');
            init[i%2] = false;
        }
        if (saidYes[i%2] != (*c[0] == 'Y') ) {
            //cout << "Bad said yes. i, yes, c: " << i << " " << saidYes[i%2] << " " << *c[0] << endl;
            cout << -1 << endl;
            return 0;
        }
    }

    if ( ( saidYes[0] && !numPos[0] ) || ( saidYes[1] && !numPos[1] ) || ( !saidYes[0] && (numPos[0] == n)) || (!saidYes[1] && (numPos[1] == n ) ) ) {
        //cout << "Contra check1" << endl;
        cout << -1 << endl;
        return 0;
    }
    bool init2 = true;
    if ( saidYes[0] && saidYes[1] ) {
        //cout << "Entered both yes case" << endl;
        if ( !shareValues || !numPos[0] || !numPos[1]) {
            cout << -1 << endl; return 0;
        }
        for ( int i = 0; i < n; i ++ ) {
            if ( ( fCheck[f[i]] == 1 ) && ( gCheck[g[i]] == 1 ) ) {
                if (!init2) cout << " ";
                cout << i+1;
                init2 = false;
            }
        }
    } else {
        //cout << "Entered 1 yes case" << endl;
        for ( int i = 0; i < n; i++ ) {
            // cout << "3 check: " << fCheck[f[2]] << " c2: " << gCheck[g[2]] << endl;
             if ( ( (fCheck[f[i]] == 1) && saidYes[0] ) || ( fCheck[f[i]] > 1 && !saidYes[0]) || ( ( gCheck[g[i]] == 1 ) && saidYes[1] ) || ( gCheck[g[i]] > 1 && !saidYes[1]) ) {
                if (!init2) cout << " ";
                cout << i+1;
                init2 = false;
            } else {
                fCheck[f[i]] -= 1;
                gCheck[g[i]] -= 1;
            }
        }
    }
    cout << endl;
}