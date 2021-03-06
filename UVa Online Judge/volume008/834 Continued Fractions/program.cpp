// Continued Fractions
// UVa ID: 834
// Verdict: Accepted
// Submission Date: 2016-12-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int numerator, denominator;
    while (cin >> numerator >> denominator)
    {
        cout << '[' << numerator / denominator;
        numerator %= denominator;
        
        bool printComma = false;
        while (numerator > 0)
        {
            if (printComma)
                cout << ',';
            else
            {
                cout << ';';
                printComma = true;
            }

            swap(numerator, denominator);
            cout << numerator / denominator;
            numerator %= denominator;
        }
        cout << "]\n";
    }

    return 0;
}
