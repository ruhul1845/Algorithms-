/*
 * Backtracking - Challenging Problems
 * Latin Square, Crossword Puzzle, Match Sticks to Square, etc.
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Latin Square (Each row and column contains unique elements 1 to n)
bool isSafeLatinSquare(vector<vector<int>>& square, int row, int col, int num, int n) {
    // Check row
    for (int j = 0; j < n; j++) {
        if (square[row][j] == num) return false;
    }
    
    // Check column
    for (int i = 0; i < n; i++) {
        if (square[i][col] == num) return false;
    }
    
    return true;
}

bool solveLatinSquareHelper(vector<vector<int>>& square, int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (square[row][col] == 0) {
                for (int num = 1; num <= n; num++) {
                    if (isSafeLatinSquare(square, row, col, num, n)) {
                        square[row][col] = num;
                        
                        if (solveLatinSquareHelper(square, n)) {
                            return true;
                        }
                        
                        square[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void solveLatinSquare(int n) {
    vector<vector<int>> square(n, vector<int>(n, 0));
    
    if (solveLatinSquareHelper(square, n)) {
        cout << "Latin Square of size " << n << ":" << endl;
        for (auto& row : square) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists" << endl;
    }
}

// 2. Match Sticks to Square
bool makesquareHelper(vector<int>& matchsticks, vector<int>& sides, int idx, int target) {
    if (idx == matchsticks.size()) {
        return sides[0] == target && sides[1] == target && 
               sides[2] == target && sides[3] == target;
    }
    
    for (int i = 0; i < 4; i++) {
        if (sides[i] + matchsticks[idx] <= target) {
            sides[i] += matchsticks[idx];
            
            if (makesquareHelper(matchsticks, sides, idx + 1, target)) {
                return true;
            }
            
            sides[i] -= matchsticks[idx];
        }
        
        // Optimization: if this side is empty, no point trying other sides
        if (sides[i] == 0) break;
    }
    
    return false;
}

bool makesquare(vector<int>& matchsticks) {
    if (matchsticks.size() < 4) return false;
    
    int sum = 0;
    for (int stick : matchsticks) sum += stick;
    
    if (sum % 4 != 0) return false;
    
    int target = sum / 4;
    sort(matchsticks.rbegin(), matchsticks.rend()); // Sort in descending order
    
    vector<int> sides(4, 0);
    return makesquareHelper(matchsticks, sides, 0, target);
}

// 3. Beautiful Arrangement
int countArrangementHelper(int n, int pos, vector<bool>& used) {
    if (pos > n) return 1;
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i] && (i % pos == 0 || pos % i == 0)) {
            used[i] = true;
            count += countArrangementHelper(n, pos + 1, used);
            used[i] = false;
        }
    }
    
    return count;
}

int countArrangement(int n) {
    vector<bool> used(n + 1, false);
    return countArrangementHelper(n, 1, used);
}

// 4. Partition to K Equal Sum Subsets
bool canPartitionKSubsetsHelper(vector<int>& nums, vector<int>& groups, int idx, int k, int target) {
    if (idx == nums.size()) {
        for (int i = 0; i < k; i++) {
            if (groups[i] != target) return false;
        }
        return true;
    }
    
    for (int i = 0; i < k; i++) {
        if (groups[i] + nums[idx] <= target) {
            groups[i] += nums[idx];
            
            if (canPartitionKSubsetsHelper(nums, groups, idx + 1, k, target)) {
                return true;
            }
            
            groups[i] -= nums[idx];
        }
        
        if (groups[i] == 0) break;
    }
    
    return false;
}

bool canPartitionKSubsets(vector<int>& nums, int k) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    if (sum % k != 0) return false;
    
    int target = sum / k;
    sort(nums.rbegin(), nums.rend());
    
    if (nums[0] > target) return false;
    
    vector<int> groups(k, 0);
    return canPartitionKSubsetsHelper(nums, groups, 0, k, target);
}

// 5. Letter Case Permutation
void letterCasePermutationHelper(string& s, int idx, string current, vector<string>& result) {
    if (idx == s.length()) {
        result.push_back(current);
        return;
    }
    
    if (isalpha(s[idx])) {
        // Convert to lowercase
        letterCasePermutationHelper(s, idx + 1, current + (char)tolower(s[idx]), result);
        // Convert to uppercase
        letterCasePermutationHelper(s, idx + 1, current + (char)toupper(s[idx]), result);
    } else {
        letterCasePermutationHelper(s, idx + 1, current + s[idx], result);
    }
}

vector<string> letterCasePermutation(string s) {
    vector<string> result;
    letterCasePermutationHelper(s, 0, "", result);
    return result;
}

// 6. Find Unique Binary String
string findDifferentBinaryStringHelper(vector<string>& nums, int idx, string current, set<string>& numSet) {
    if (idx == nums[0].length()) {
        if (numSet.find(current) == numSet.end()) {
            return current;
        }
        return "";
    }
    
    // Try '0'
    string result = findDifferentBinaryStringHelper(nums, idx + 1, current + "0", numSet);
    if (!result.empty()) return result;
    
    // Try '1'
    return findDifferentBinaryStringHelper(nums, idx + 1, current + "1", numSet);
}

string findDifferentBinaryString(vector<string>& nums) {
    set<string> numSet(nums.begin(), nums.end());
    return findDifferentBinaryStringHelper(nums, 0, "", numSet);
}

// 7. Maximum Length of a Concatenated String with Unique Characters
bool hasUniqueChars(string s) {
    unordered_set<char> chars(s.begin(), s.end());
    return chars.size() == s.length();
}

bool hasOverlap(string s1, string s2) {
    unordered_set<char> chars(s1.begin(), s1.end());
    for (char c : s2) {
        if (chars.count(c)) return true;
    }
    return false;
}

int maxLengthHelper(vector<string>& arr, int idx, string current) {
    if (!hasUniqueChars(current)) return 0;
    
    int maxLen = current.length();
    
    for (int i = idx; i < arr.size(); i++) {
        if (!hasOverlap(current, arr[i])) {
            maxLen = max(maxLen, maxLengthHelper(arr, i + 1, current + arr[i]));
        }
    }
    
    return maxLen;
}

int maxLength(vector<string>& arr) {
    return maxLengthHelper(arr, 0, "");
}

// 8. Splitting a String Into Descending Consecutive Values
bool splitStringHelper(string& s, int idx, long long prevValue, int count) {
    if (idx == s.length()) {
        return count >= 2;
    }
    
    for (int len = 1; len <= s.length() - idx; len++) {
        string part = s.substr(idx, len);
        
        // Skip leading zeros (except for "0" itself)
        if (part.length() > 1 && part[0] == '0') break;
        
        long long value = stoll(part);
        
        if (count == 0 || value == prevValue - 1) {
            if (splitStringHelper(s, idx + len, value, count + 1)) {
                return true;
            }
        }
    }
    
    return false;
}

bool splitString(string s) {
    return splitStringHelper(s, 0, 0, 0);
}

// 9. Maximum Score Words Formed by Letters
int maxScoreWordsHelper(vector<string>& words, vector<char>& letters, vector<int>& score, 
                        int idx, vector<int>& freq) {
    if (idx == words.size()) {
        return 0;
    }
    
    // Skip current word
    int maxScore = maxScoreWordsHelper(words, letters, score, idx + 1, freq);
    
    // Try to include current word
    vector<int> wordFreq(26, 0);
    bool canForm = true;
    int wordScore = 0;
    
    for (char c : words[idx]) {
        wordFreq[c - 'a']++;
        wordScore += score[c - 'a'];
        if (wordFreq[c - 'a'] > freq[c - 'a']) {
            canForm = false;
            break;
        }
    }
    
    if (canForm) {
        // Update frequency
        for (int i = 0; i < 26; i++) {
            freq[i] -= wordFreq[i];
        }
        
        maxScore = max(maxScore, wordScore + maxScoreWordsHelper(words, letters, score, idx + 1, freq));
        
        // Restore frequency
        for (int i = 0; i < 26; i++) {
            freq[i] += wordFreq[i];
        }
    }
    
    return maxScore;
}

int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
    vector<int> freq(26, 0);
    for (char c : letters) {
        freq[c - 'a']++;
    }
    
    return maxScoreWordsHelper(words, letters, score, 0, freq);
}

// 10. Verbal Arithmetic Puzzle (Generalized)
bool verbalArithmeticHelper(vector<string>& words, string& result, unordered_map<char, int>& charToDigit,
                           vector<char>& chars, vector<bool>& used, int idx) {
    if (idx == chars.size()) {
        // Check if equation is valid
        long long sum = 0;
        for (string& word : words) {
            // Leading zero check
            if (word.length() > 1 && charToDigit[word[0]] == 0) return false;
            
            long long num = 0;
            for (char c : word) {
                num = num * 10 + charToDigit[c];
            }
            sum += num;
        }
        
        // Leading zero check for result
        if (result.length() > 1 && charToDigit[result[0]] == 0) return false;
        
        long long resultNum = 0;
        for (char c : result) {
            resultNum = resultNum * 10 + charToDigit[c];
        }
        
        return sum == resultNum;
    }
    
    for (int digit = 0; digit <= 9; digit++) {
        if (!used[digit]) {
            charToDigit[chars[idx]] = digit;
            used[digit] = true;
            
            if (verbalArithmeticHelper(words, result, charToDigit, chars, used, idx + 1)) {
                return true;
            }
            
            used[digit] = false;
        }
    }
    
    return false;
}

bool isSolvable(vector<string>& words, string result) {
    set<char> uniqueChars;
    for (string& word : words) {
        for (char c : word) uniqueChars.insert(c);
    }
    for (char c : result) uniqueChars.insert(c);
    
    if (uniqueChars.size() > 10) return false;
    
    vector<char> chars(uniqueChars.begin(), uniqueChars.end());
    vector<bool> used(10, false);
    unordered_map<char, int> charToDigit;
    
    return verbalArithmeticHelper(words, result, charToDigit, chars, used, 0);
}

// 11. All Paths From Source Lead to Destination
bool allPathsLeadToDestHelper(vector<vector<int>>& graph, int node, int destination, 
                              vector<int>& state) {
    // state: 0 = unvisited, 1 = visiting, 2 = visited
    if (state[node] != 0) {
        return state[node] == 2;
    }
    
    // If this is a leaf node
    if (graph[node].empty()) {
        return node == destination;
    }
    
    state[node] = 1; // Mark as visiting
    
    for (int neighbor : graph[node]) {
        if (!allPathsLeadToDestHelper(graph, neighbor, destination, state)) {
            return false;
        }
    }
    
    state[node] = 2; // Mark as visited
    return true;
}

bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
    }
    
    vector<int> state(n, 0);
    return allPathsLeadToDestHelper(graph, source, destination, state);
}

// 12. Unique Paths III (Walk over every non-obstacle square exactly once)
int uniquePathsIIIHelper(vector<vector<int>>& grid, int x, int y, int remaining) {
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == -1) {
        return 0;
    }
    
    if (grid[x][y] == 2) {
        return remaining == 0 ? 1 : 0;
    }
    
    int temp = grid[x][y];
    grid[x][y] = -1; // Mark as visited
    
    int paths = uniquePathsIIIHelper(grid, x + 1, y, remaining - 1) +
                uniquePathsIIIHelper(grid, x - 1, y, remaining - 1) +
                uniquePathsIIIHelper(grid, x, y + 1, remaining - 1) +
                uniquePathsIIIHelper(grid, x, y - 1, remaining - 1);
    
    grid[x][y] = temp; // Restore
    return paths;
}

int uniquePathsIII(vector<vector<int>>& grid) {
    int startX, startY, empty = 1;
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1) {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 0) {
                empty++;
            }
        }
    }
    
    return uniquePathsIIIHelper(grid, startX, startY, empty);
}

int main() {
    // Test Latin Square
    cout << "=== Latin Square ===" << endl;
    solveLatinSquare(4);
    cout << "\n";
    
    // Test Matchsticks to Square
    cout << "=== Matchsticks to Square ===" << endl;
    vector<int> matchsticks = {1, 1, 2, 2, 2};
    cout << "Can make square: " << (makesquare(matchsticks) ? "Yes" : "No") << "\n\n";
    
    // Test Beautiful Arrangement
    cout << "=== Beautiful Arrangement ===" << endl;
    cout << "Count for n=2: " << countArrangement(2) << endl;
    cout << "Count for n=3: " << countArrangement(3) << "\n\n";
    
    // Test Partition to K Equal Sum Subsets
    cout << "=== Partition to K Equal Sum Subsets ===" << endl;
    vector<int> nums1 = {4, 3, 2, 3, 5, 2, 1};
    cout << "Can partition into 4 subsets: " << (canPartitionKSubsets(nums1, 4) ? "Yes" : "No") << "\n\n";
    
    // Test Letter Case Permutation
    cout << "=== Letter Case Permutation ===" << endl;
    vector<string> perms = letterCasePermutation("a1b2");
    cout << "Permutations: ";
    for (string& s : perms) cout << s << " ";
    cout << "\n\n";
    
    // Test Find Different Binary String
    cout << "=== Find Different Binary String ===" << endl;
    vector<string> nums2 = {"01", "10"};
    cout << "Different binary string: " << findDifferentBinaryString(nums2) << "\n\n";
    
    // Test Maximum Length
    cout << "=== Maximum Length of Concatenated String ===" << endl;
    vector<string> arr1 = {"un", "iq", "ue"};
    cout << "Max length: " << maxLength(arr1) << "\n\n";
    
    // Test Splitting String
    cout << "=== Splitting String Into Descending Values ===" << endl;
    cout << "Can split '1234': " << (splitString("1234") ? "Yes" : "No") << "\n\n";
    
    // Test Verbal Arithmetic Puzzle
    cout << "=== Verbal Arithmetic Puzzle ===" << endl;
    vector<string> words = {"SEND", "MORE"};
    cout << "Is solvable: " << (isSolvable(words, "MONEY") ? "Yes" : "No") << "\n\n";
    
    // Test Unique Paths III
    cout << "=== Unique Paths III ===" << endl;
    vector<vector<int>> grid = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, -1}
    };
    cout << "Number of unique paths: " << uniquePathsIII(grid) << endl;
    
    return 0;
}

