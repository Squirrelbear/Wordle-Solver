#pragma once
#include <vector>
#include <map>

/*
Wordle Solver

A reductive database that loads all possible options and then removes them based on rules.

@author Peter Mitchell
@version 2022.1
*/
class Database
{
public:
	// Initialise the database resetting it to a default state with all words loaded.
	Database();
	virtual ~Database() = default;

	// Removes all words that do not fit with the entered rule.
	void filterByRule(const std::string& rule);
	
	// Resets by clearing all rules and then loading them from the word input file.
	void reset();

	/* Outputs a suggestion by always showing the number of possible options.
		If the remaining options is less than 30 words all are shown. Then the 
		distribution of letters is shown to highlight letters to focus on. */
	void outputSuggestion() const;

	// Shows the full list of remaining words with 10 per line.
	void showAll() const;

	// Checks every remaining word to count the number of words containing each letter.
	void showLetterChance() const;

	// Shows a message to explain entering of rules.
	void showHelp() const;

	// Prints out all the rules that have been applied so far.
	void showRules() const;

	// Returns true if a rule contains 5 letters with max of 1 modifier before each.
	bool isRuleValid(const std::string& rule) const;

private:
	// The remaining words in the database.
	std::vector < std::string > _data;

	// The rules that have been entered so far.
	std::vector < std::string > _rules;

	// Iterates over the rule and validates the content of word. 
	bool wordFitsRule(const std::string& rule, const std::string& word) const;
	
	// Increases result by a max of 1 for each unique letter occuring in the word.
	void countLetterOccurrence(const std::string& word, std::map<char, int>& result) const;
};

