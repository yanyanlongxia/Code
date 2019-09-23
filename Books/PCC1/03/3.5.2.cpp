#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10240, CHARSET = 128, FAIL = -1;

class AhoCorasick
{
private:
    int cnt, root, go[MAXN][CHARSET], fail[MAXN];
    vector<string> keywords;
    vector<int> output[MAXN];

    void buildGotoFunction()
    {
        for (int i = 0; i < keywords.size(); i++) {
            int *current = &root;
            for (auto c : keywords[i]) {
                current = &go[*current][c];
                if (*current == FAIL) {
                    *current = ++cnt;
                    memset(go[cnt], FAIL, sizeof(go[cnt]));
                    output[cnt].clear();
                }
            }
            output[*current].push_back(i);
        }
        for (int i = 0; i < CHARSET; i++)
            if (go[0][i] == FAIL)
                go[0][i] = 0;
    }

    void buildFailureFunction()
    {
        queue<int> q;
        for (int i = 0; i < CHARSET; i++)
            if (go[0][i] != 0) {
                q.push(go[0][i]);
                fail[go[0][i]] = 0;
            }
        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int i = 0; i < CHARSET; i++)
                if (go[r][i] != FAIL) {
                    int s = go[r][i], f = fail[r];
                    q.push(s);
                    while (go[f][i] == FAIL) f = fail[f];
                    fail[s] = go[f][i];
                    output[s].insert(output[s].end(),
                        output[fail[s]].begin(), output[fail[s]].end());
                }
        }
    }

public:
    void initialize()
    {
        memset(go[0], FAIL, sizeof(go[0]));
        keywords.clear();
        root = cnt = 0;
    }

    void add(string s) { keywords.push_back(s); }

    void match(string &s)
    {
        buildGotoFunction();
        buildFailureFunction();

        int current = root;
        for (auto c : s) {
            while (go[current][c] == FAIL) current = fail[current];
            current = go[current][c];
            if (output[current].size() > 0) {
                for (auto i : output[current])
                    cout << keywords[i] << ' ';
                cout << '\n';
            }
        }
    }
};

int main(int argc, char *argv[])
{
    int n;
    string key, line;
    AhoCorasick ac;

    while(cin >> n) {
        ac.initialize();
        for (int i = 0; i < n; i++) {
            cin >> key;
            ac.add(key);
        }
        cin.ignore(256, '\n');
        string text;
        while (getline(cin, line), line.length() > 0) text += line;
        ac.match(text);
    }

    return 0;
}
