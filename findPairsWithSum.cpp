include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> findPairsWithSum(vector<int>& nums, int targetSum) {
    unordered_map<int, int> valueToIndexMap;

    for (int currentIndex = 0; currentIndex < nums.size(); currentIndex++) {
        int requiredValue = targetSum - nums[currentIndex];

        if (valueToIndexMap.find(requiredValue) != valueToIndexMap.end()) {
            return { valueToIndexMap[requiredValue], currentIndex };
        }

        valueToIndexMap[nums[currentIndex]] = currentIndex;
    }

    return {};
}

int main() {
    vector<int> sampleNumbers1 = { 2, 7, 11, 15 };
    int target1 = 9;
    vector<int> result1 = findPairsWithSum(sampleNumbers1, target1);
    cout << "[" << result1[0] << ", " << result1[1] << "]" << endl;

    vector<int> sampleNumbers2 = { 3, 2, 4 };
    int target2 = 6;
    vector<int> result2 = findPairsWithSum(sampleNumbers2, target2);
    cout << "[" << result2[0] << ", " << result2[1] << "]" << endl;

    vector<int> sampleNumbers3 = { 3, 3 };
    int target3 = 6;
    vector<int> result3 = findPairsWithSum(sampleNumbers3, target3);
    cout << "[" << result3[0] << ", " << result3[1] << "]" << endl;

    return 0;
}
