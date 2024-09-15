#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to sort the characters of a string
string sortString(const string &str) {
    string sorted_str = str;
    sort(sorted_str.begin(), sorted_str.end());
    return sorted_str;
}

// Function to check if two words are anagrams
bool areAnagrams(const string &word1, const string &word2) {
    return sortString(word1) == sortString(word2);
}

// Function to check if word1 is a sub-anagram of word2
bool isSubAnagram(const string &word1, const string &word2) {
    unordered_map<char, int> charCount;
    
    // Count characters in word1
    for (char c : word1) {
        charCount[c]++;
    }
    
    // Check if word2 contains all characters in word1 with the required frequency
    for (char c : word2) {
        if (charCount.find(c) != charCount.end()) {
            charCount[c]--;
            if (charCount[c] == 0) {
                charCount.erase(c);
            }
        }
    }
    
    return charCount.empty();
}

// Function to find and return all anagrams or sub-anagrams in the file
vector<string> findMatches(const string &word, const string &filename, bool findAnagrams) {
    ifstream file(filename);
    vector<string> matches;
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return matches;
    }

    while (getline(file, line)) {
        if ((findAnagrams && areAnagrams(word, line)) ||
            (!findAnagrams && isSubAnagram(word, line))) {
            matches.push_back(line);
        }
    }

    file.close();
    return matches;
}

int main() {
    string word, filename;
    int choice;

    // Get the choice from the user
    cout << "Choose an option:" << endl;
    cout << "1. Find anagrams" << endl;
    cout << "2. Find sub-anagrams" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    // Validate choice
    if (choice != 1 && choice != 2) {
        cerr << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    // Get the word from the user
    cout << "Enter a word: ";
    cin >> word;

    // Get the filename from the user
    cout << "Enter the filename containing the list of words: ";
    cin >> filename;

    // Find matches in the file based on the user's choice
    bool findAnagrams = (choice == 1);
    vector<string> matches = findMatches(word, filename, findAnagrams);

    // Output the results
    if (matches.empty()) {
        cout << "No matches found for the word '" << word << "' in the file." << endl;
    } else {
        cout << (findAnagrams ? "Anagrams" : "Sub-anagrams") << " found for the word '" << word << "':" << endl;

        // Introduce a counter variable
        int count = 1;

        // Loop through the matches and print each one with its number
        for (const string &match : matches) {
            cout << count << ". " << match << endl; // Output with number
            ++count; // Increment counter
        }
    }

    return 0;
}
