# sixy
for analysis of sixy sudoku

Instructions to get the answers to the third question in
https://mathoverflow.net/questions/343345/
number-of-solutions-and-minimal-clues-in-sixy-sudoku/

Evaluate the Mathematica notebook 
	sixy7.nb 
(JUST ONCE) to create

inputcoresize2.txt
inputcoresize3.txt
inputcoresize4.txt
inputstutter2.txt
inputstutter3.txt
counts.txt

Put them in the same directory as sixy7.c

Next compile sixy7.c

	bash-3.2$ gcc -o sixy7 sixy7.c

Feed inputcoresize2.txt to sixy7 and append the result to counts.txt like this:

	bash-3.2$ date
	bash-3.2$ (./sixy7<inputcoresize2.txt)>>counts.txt
	date

This may take a few minutes.
	
Repeat with

	bash-3.2$ date
	bash-3.2$ (./sixy7<inputcoresize3.txt)>>counts.txt
	date

(a few minutes)	and with

	bash-3.2$ date
	bash-3.2$ (./sixy7<inputcoresize4.txt)>>counts.txt
	date

(ten minutes)

The file counts.txt should now contain about 55 KB.
Move counts.txt inputcoresize2.txt inputcoresize3.txt inputcoresize4.txt
to a directory seen by Mathematica.
You can now use the notebook
	accumulate.nb
to get the answers.

_________________________

For the first question we used sixy.c

________________________

For the second question one may use sixy5.c or feed
	inputstutter2.txt
	inputstutter3.txt
to sixy7 

__________________________    

