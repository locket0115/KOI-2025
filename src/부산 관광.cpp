#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MX = 2005;
const int INF = 1234567890;

int dp[MX][MX];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N;
    cin >> N;

    string A, B;
    cin >> A;
    cin >> B;

    // int p1, p3, p5, pa;
    
    int p[4];
    cin >> p[0] >> p[1] >> p[2] >> p[3];
    int d[3] = {1, 3, 5};

    for(int i = 1; i <= N; i++) {
        dp[i][0] = INF;

        if(A[i-1] == '1')
            for(int ii = 0; ii < 3; ii++) {
                dp[i][0] = min(dp[i][0], dp[max(0, i-d[ii])][0]+p[ii]);
            }
        else {
            dp[i][0] = dp[i-1][0];
        }
    }

    for(int j = 1; j <= N; j++) {
        dp[0][j] = INF;

        if(B[j-1] == '1')
            for(int jj = 0; jj < 3; jj++) {
                dp[0][j] = min(dp[0][j], dp[0][max(0, j-d[jj])]+p[jj]);
            }
        else {
            dp[0][j] = dp[0][j-1];
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            dp[i][j] = INF;
            
            if(A[i-1] == '1' && B[j-1] == '1') {
                for(int ii = 0; ii < 3; ii++) {
                    for(int jj = 0; jj < 3; jj++) {
                        dp[i][j] = min(dp[i][j], dp[max(0, i-d[ii])][max(0, j-d[jj])]+p[ii]+p[jj]);
                    }
                }
            } else if(A[i-1] == '1') {
                for(int ii = 0; ii < 3; ii++) {
                    dp[i][j] = min(dp[i][j], dp[max(0, i-d[ii])][j-1]+p[ii]);
                }
                dp[i][j] = min(dp[i][j], dp[i][j-1]);
            } else if(B[j-1] == '1') {
                for(int jj = 0; jj < 3; jj++) {
                    dp[i][j] = min(dp[i][j], dp[i-1][max(0, j-d[jj])]+p[jj]);
                }
                dp[i][j] = min(dp[i][j], dp[i-1][j]);
            } else {
                dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
            }

            if(i == j) {
                dp[i][j] = min(dp[i][j], dp[max(0, i-4)][max(0, j-4)]+p[3]);
            }
        }
    }

    cout << dp[N][N];
    return 0;
}
