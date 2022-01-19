#include "Database.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

Database::Database()
{
	reset();
}

void Database::filterByRule(const std::string& rule)
{
	_rules.push_back(rule);
	_data.erase(std::remove_if(_data.begin(), _data.end(), [&](std::string& word) {
		return !wordFitsRule(rule, word);
		}) , _data.end());
}

void Database::reset()
{
	_data.clear();
	_rules.clear();
	std::ifstream file("../words.txt");
	if (!file.is_open()) {
		std::cerr << "Failed to load words..." << std::endl;
		return;
	}

	std::string word;
	while (std::getline(file, word)) {
		_data.emplace_back(word);
	}

	std::cout << "Word list successfully loaded with " << _data.size() << " words." << std::endl;

	file.close();

	std::sort(_data.begin(), _data.end());
}

void Database::outputSuggestion() const
{
	std::cout << "Count remaining: " << _data.size() << std::endl;
	if (_data.size() <= 80) {
		showAll();
	}
	showLetterChance();
}

void Database::showAll() const
{
	std::cout << "Word list remaining:" << std::endl;
	int rowCounter = 0;
	for (const auto& word : _data) {
		std::cout << word << " ";
		++rowCounter;
		if (rowCounter == 10) {
			std::cout << std::endl;
			rowCounter = 0;
		}
	}
	std::cout << std::endl << std::endl;
}

void Database::showLetterChance() const
{
	std::map<char, int> letterCounts;
	// initialise all counts to 0
	for (char letter = 'a'; letter <= 'z'; ++letter) {
		letterCounts.insert_or_assign(letter, 0);
	}

	// Count every word for number of letter occurrences
	for (const auto& word : _data) {
		countLetterOccurrence(word, letterCounts);
	}

	// Collect results and sort with largest at start.
	std::vector<std::pair<char, int>> orderedResult;
	for (auto& it : letterCounts) {
		orderedResult.push_back(it);
	}

	auto cmp = [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
		return a.second > b.second;
	};
	std::sort(orderedResult.begin(), orderedResult.end(), cmp);

	// Print all out that are non-zero.
	for (const auto& letterFreq : orderedResult) {
		if (letterFreq.second > 0) {
			std::cout << letterFreq.first << ": " << letterFreq.second << " ";
		}
	}
	std::cout << std::endl;

	// If there is at least one rule, show the up to 5 most common unused letters.
	if (!_rules.empty()) {
		std::cout << "Most unused common: ";

		int outputCount = 0;
		for (const auto& letterFreq : orderedResult) {
			if (letterFreq.second > 0 && _rules.at(_rules.size()-1).find(letterFreq.first) == std::string::npos) {
				std::cout << letterFreq.first << " ";
				++outputCount;
			}

			if (outputCount == 5) break;
		}
		if (outputCount == 0) {
			std::cout << "none found...";
		}

		std::cout << std::endl;
	}
}

void Database::showHelp() const
{
	std::cout << "#letter for any letter that should exist at least once, but not there." << std::endl
		<< "*letter for any letter that should exist at exactly that position." << std::endl
		<< "letter by itself for any letter that should exist nowhere." << std::endl
		<< "Example: #YE*AST would mean at least one Y not at the first letter, " << std::endl
		<< "nowhere any E, S, or T, and A should appear at the middle." << std::endl;
}

void Database::showRules() const
{
	std::cout << "Rules entered so far:" << std::endl;
	for (const auto& rule : _rules) {
		std::cout << rule << std::endl;
	}
	std::cout << std::endl;
}

bool Database::isRuleValid(const std::string & rule) const
{
	int letterCount = 0;
	for (int i = 0; i < rule.length(); i++) {
		// Skip one forward if special character
		if (rule.at(i) == '#' || rule.at(i) == '*') {
			i++;
		}
		if ((rule.at(i) >= 'a' && rule.at(i) <= 'z') || rule.at(i) == '_') {
			letterCount++;
		}
		else {
			// This means the character is either an invalid double special character
			// or some irrelevant other character.
			return false;
		}
	}

	return letterCount == 5;
}

bool Database::wordFitsRule(const std::string & rule, const std::string & word) const
{
	for (int i = 0, pos = 0; i < rule.length(); ++i, ++pos) {
		// Wild card to ignore this position.
		if (rule.at(i) == '_') {
			continue;
		}
		// Exists at position with exact match
		else if (rule.at(i) == '*') { 
			i++;
			if (rule.at(i) != word.at(pos)) {
				return false;
			}
		}
		// One or more in string but not at pos
		else if (rule.at(i) == '#') { 
			i++;
			bool foundOne = false;
			for (int j = 0; j < word.length(); j++) {
				if (word.at(j) == rule.at(i) && j != pos) {
					foundOne = true;
				}
			}
			if (!foundOne) {
				return false;
			}
		}
		// Should not appear anywhere in the word
		else { 
			for (int j = 0; j < word.length(); j++) {
				if (word.at(j) == rule.at(i)) {
					return false;
				}
			}
		}
	}

	return true;
}

void Database::countLetterOccurrence(const std::string & word, std::map<char, int>& result) const
{
	for (int i = 0; i < word.size(); i++) {
		if (word.find_first_of(word.at(i)) == i) {
			result.insert_or_assign(word.at(i), result.at(word.at(i)) + 1);
		}
	}
}
