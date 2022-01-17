#include <iostream>
#include "Database.h"
#include <string>
#include <algorithm>
#include <cctype>

int main() {

	std::cout << "Wordle Solver by Peter Mitchell" << std::endl;
	Database wordDatabase;
	std::cout << "To enter rules use:" << std::endl;
	wordDatabase.showHelp();

	std::string input;
	do {
		std::cout << std::endl << "Enter rule: ";
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (input == "show") {
			wordDatabase.showAll();
		}
		else if (input == "resetdb") {
			wordDatabase.reset();
		}
		else if (input == "letters") {
			wordDatabase.showLetterChance();
		}
		else if (input == "help") {
			wordDatabase.showHelp();
		}
		else if (input == "quit") {
			break;
		}
		else if (input == "showrules") {
			wordDatabase.showRules();
		}
		else if (!wordDatabase.isRuleValid(input)) {
			std::cout << "The rule you entered was not valid. Enter help for help." << std::endl;
		}
		else {
			wordDatabase.filterByRule(input);
			wordDatabase.outputSuggestion();
		}
	} while (true);


	return 0;
}