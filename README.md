# Wordle-Solver

 A solver built to help determine the best guess based on rules.

Word data source: https://www-cs-faculty.stanford.edu/~knuth/sgb.html

# Input commands

Entering one of the following as a rule will trigger the described result.

- "show": Shows all words that are possible still.
- "resetdb": Resets the database to the original dataset.
- "letters": Shows the number of words in the remaining set that contain at least one of each letter.
- "help": Shows output describing how to enter the rules.
- "quit": Terminates the program.
- "showrules": Shows all rules that have been entered so far.

Anything else is interpretted to be a rule. Letters should be entered for the result of a guess. The following is how you set the interpretation of the input.

- * before a letter means that letter is in the correct position and must appear there for any valid word.
- # before a letter means that letter is in the wrong position, but should appear at least once in the word.
- Neither before a letter means the letter should not appear anywhere in the word.

For example inputting the rule #YE*AST
- Y should appear somewhere in the word but NOT at the start.
- E, S, and T should NOT appear anywhere in the word.
- A should appear in the middle position.