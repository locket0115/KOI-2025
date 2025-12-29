#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int MX = 2005;
const ll INF = 1e18;

vector<pll> graph[MX];
vector<pll> rev[MX];

bool hasWindow[MX];

int N, M;
ll a, b;

vector<ll> calc(int st) {
    vector<ll> dist(N+1, a+1);
    
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, st});
    dist[st] = 0;

    while(!pq.empty()) {
        auto [t, cur] = pq.top();
        pq.pop();

        if(dist[cur] < t) continue;

        for(auto [nx, w] : graph[cur]) {
            if(w > a) continue;

            if(dist[nx] > t+w) {
                dist[nx] = t+w;
                pq.push({dist[nx], nx});
            }
        }
    }

    return dist;
}

ll dp[MX];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    
    for(int i = 0; i < M; i++) {
        ll x, y, t;
        cin >> x >> y >> t;
        graph[x].push_back({y, t});
        rev[y].push_back({x, t});
    }

    for(int i = 1; i <= N; i++) cin >> hasWindow[i];
    
    cin >> a >> b;

    for(int i = 2; i <= N; i++) dp[i] = INF;

    queue<int> q;
    q.push(1);
    dp[1] = 0;

    while(!q.empty()) {
        auto cur = q.front();
        q.pop();

        auto d = calc(cur);

        for(int i = 1; i <= N; i++) {
            if(i == cur) continue;

            if(dp[i] == INF && d[i] <= a && (!hasWindow[i] || i == N)) {
                dp[i] = dp[cur] + a+b;
                q.push(i);
            }
        }
    }


    ll ans = INF;
    
    vector<ll> dist(N+1, a+1);
    
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, N});
    dist[N] = 0;

    while(!pq.empty()) {
        auto [t, cur] = pq.top();
        pq.pop();

        if(dist[cur] < t) continue;

        if(dp[cur] != INF) {
            ans = min(ans, dp[cur]+t);
        }

        for(auto [nx, w] : rev[cur]) {
            if(dist[nx] > t+w) {
                dist[nx] = t+w;
                pq.push({dist[nx], nx});
            }
        }
    }

    cout << (ans==INF ? -1 : ans);
    return 0;
}
