#include <iostream>
#include "BSTFCI.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


class Index {
private:
	BSTFCI<string> bst;
	map<string, vector<int>> word_lines;
public:
	Index(string text) {
		// Remove punctuation
		for (int i = 0; i < text.length(); i++)
			if (!isalnum(text[i]) && text[i] != ' ' && text[i] != '\n')
				text.erase(text.begin() + i);

		// Get words
		int lastSpaceIndex = -1, cur_line = 1;
		for (int i = 0; i < text.length(); i++) {
			while (i < text.length() && text[i] != ' ' && text[i] != '\n')
				i++;

			string word = text.substr(lastSpaceIndex + 1, i - lastSpaceIndex - 1);
			// If not found before
			if (word_lines.find(word) == word_lines.end())
				bst.insert(word);
			word_lines[word].push_back(cur_line);

			// If the end of the line reached
			if (i < text.length() && text[i] == '\n')
				cur_line++;
			lastSpaceIndex = i;
		}
	}

	void print() {
		vector<string> words = bst.getAll();
		for (auto word : words) {
			cout << word << "\t";
			for (int i = 0; i < word_lines[word].size(); i++)
				cout << word_lines[word][i] << (i == word_lines[word].size() - 1 ? "\n" : ",");
		}
	}
};

int main() {
	string s = "I am for truth,\nno matter who tells it.\nI am for justice,\nno matter who it is for or against.\nMalcolm X";
	//getline(cin, s, '$');
	Index x(s);
	x.print();
	cin.ignore(), cin.get();
	system("pause");
}
