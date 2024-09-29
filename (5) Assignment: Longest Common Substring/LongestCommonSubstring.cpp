#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printTable(const vector<vector<int>>& table) {
    for (const auto& row : table) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

string longestCommonSubstring(const string& str1, const string& str2) {
    int n = str1.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    int maxLength = 0;
    int endIndex = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    printTable(dp);

    return str1.substr(endIndex - maxLength + 1, maxLength);
}

int main() {
    string str1, str2;
    cout << "Enter the first string: ";
    cin >> str1;
    cout << "Enter the second string: ";
    cin >> str2;

    if (str1.length() != str2.length()) {
        cout << "Strings must be of the same length." << endl;
        return 1;
    }

    string result = longestCommonSubstring(str1, str2);
    cout << "Longest Common Substring: " << result << endl;
    cout << "Length: " << result.length() << endl;

    return 0;
}
