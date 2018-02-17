// Interstar Transport
// UVa ID: 1247
// Verdict: Accepted
// Submission Date: 2018-02-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 32, INF = 0x3f3f3f3f;

char from, to;
int n, m, q, u, v, vv, w, cnt;
int dist[MAXV][MAXV], path[MAXV][MAXV], step[MAXV][MAXV];
map<char, int> indexer;
map<int, char> letter;

void dfs(int i, int j)
{
    if (path[i][j] == -1) cout << letter[i] << ' ';
    else
    {
        dfs(i, path[i][j]);
        dfs(path[i][j], j);
    }
}

void dfs1(int i, int j, int topmost)
{
    if (topmost) cout << letter[i] << ' ';
    int k = path[i][j];
    if (k > 0)
    {
        if (i != k) dfs1(i, k, 0);
        if (i != k && j != k) cout << letter[k] << ' ';
        if (j != k) dfs1(k, j, 0);
    }
    if (topmost) cout << letter[j] << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        cnt = 1;
        indexer.clear();
        letter.clear();
        memset(dist, 0x3f, sizeof(dist));
        memset(step, 0x3f, sizeof(step));
        memset(path, -1, sizeof(path));

        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to >> w;
            if (indexer.find(from) == indexer.end())
            {
                letter[cnt] = from;
                indexer[from] = cnt++;
            }
            if (indexer.find(to) == indexer.end())
            {
                letter[cnt] = to;
                indexer[to] = cnt++;
            }
            u = indexer[from], v = indexer[to];
            dist[u][v] = dist[v][u] = w;
            step[u][v] = step[v][u] = 1;
        }
        for (int i = 1; i <= n; i++) dist[i][i] = step[i][i] = 0;

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        step[i][j] = step[i][k] + step[k][j];
                        path[i][j] = k;
                    }
                    else if (dist[i][j] == dist[i][k] + dist[k][j] && step[i][j] > step[i][k] + step[k][j])
                    {
                        step[i][j] = step[i][k] + step[k][j];
                        path[i][j] = k;
                    }

        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> from >> to;
            u = indexer[from], v = indexer[to];

            //dfs(u, v);
            //cout << to << '\n';

            dfs1(u, v, 1);
        }
    }

    return 0;
}