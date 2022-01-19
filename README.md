# Wordle-Solver

 A solver built to help determine the best guess based on rules.
 
 Designed for solving puzzles on: https://www.powerlanguage.co.uk/wordle/

Word data source: https://www-cs-faculty.stanford.edu/~knuth/sgb.html

You may need to change the file path of the word file that is loaded in. See: Database::reset().

# Input commands

Entering one of the following as a rule will trigger the described result.

- "show": Shows all words that are possible still.
- "resetdb": Resets the database to the original dataset.
- "letters": Shows the number of words in the remaining set that contain at least one of each letter.
- "help": Shows output describing how to enter the rules.
- "quit": Terminates the program.
- "showrules": Shows all rules that have been entered so far.

Anything else is interpretted to be a rule. Letters should be entered for the result of a guess. The following is how you set the interpretation of the input.

- \* before a letter means that letter is in the correct position and must appear there for any valid word.
- \# before a letter means that letter is in the wrong position, but should appear at least once in the word.
- Neither before a letter means the letter should not appear anywhere in the word.
- _ acts as a wild card to ignore that position. Can be used instead of having to write \*T for example.

For example inputting the rule \#YE\*AST
- Y should appear somewhere in the word but NOT at the start.
- E, S, and T should NOT appear anywhere in the word.
- A should appear in the middle position.

This example would tell the user there are 14 words remaining. The most common unused letters are r and o with 9 and 5 occurrences respectively. Then if you were to guess "ovary" and the rule was O#V\*A#R\*Y you could enter it as:

* O#V_#R\*Y
	- O does not appear.
	- V and R appear but are in different places.
	- \*Y is required to be written explicitely because this is the first time the rule for that position is specified.
	- _ can be written instead of \*A because that rule was already applied as a specified position.

After entering the rule the result back from the program would be a single word for the final result:

* gravy