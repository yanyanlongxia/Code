// Rare Order
// UVa IDs: 200
// Verdict: Accepted
// Submission Date: 2016-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int map[26][26] = { 0 }, letters[26] =

{
0}, degree[26];

int main(int argc, char *argv[])
{
    string line;
    vector < string > words;
    while (getline(cin, line))
    {
        if (line != "#")
        {
            words.push_back(line);
            continue;
        }

        memset(letters, 0, sizeof(letters));
        memset(map, 0, sizeof(map));

        for (int i = 0; i < words.size() - 1; i++)
        {
            string first = words[i], second = words[i + 1];
            int index = 0;
            while (index < first.length() && index < second.length())
            {
                if (first[index] != second[index])
                {
                    letters[first[index] - 'A'] = 1;
                    letters[second[index] - 'A'] = 1;
                    map[first[index] - 'A'][second[index] - 'A'] = 1;
                    break;
                }
                index++;
            }
        }

        while (true)
        {
            memset(degree, 0, sizeof(degree));

            for (int i = 0; i < 26; i++)
                for (int j = 0; j < 26; j++)
                    if (map[i][j] == 1)
                        degree[j]++;

            bool outputed = false;
            for (int i = 0; i < 26; i++)
                if (letters[i] == 1 && degree[i] == 0)
                {
                    letters[i] = 0;
                    cout << (char)(i + 'A');
                    for (int m = 0; m < 26; m++)
                        map[i][m] = 0;
                    outputed = true;
                    break;
                }

            if (outputed == false)
                break;
        }
        cout << endl;

        words.clear();
    }

    return 0;
}
