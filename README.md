# SixySolver

SixySolver is cloned from [here](https://github.com/wilberdk/sixy).

SixySudoku is a 6x6 Sudoku with row, column and 2Rx3C block constraints, with a fourth constraint of usually rectangular 3Rx2C blocks. The 4th constraint can be irregular jigsaw cages.

The solver.c is modified from sixy.c - to solve a SixySudoku puzzle, and return the number of solutions.

The SixySolver source is not available.

## Usage
```
SixySolver.exe filename

SixySolver.exe SixySudokuPuzzle [JigsawCagesDefinition]
```

where:
```
filename - contains SixySudokuPuzzle and JigsawCagesDefinition on 2 separate lines.

SixySudokuPuzzle - is a 36-character string of the SixySudoku, 1-6 for givens, 0 or . for empty cells.

JigsawCagesDefinition - is a 36-character string representing the jigsaw cages, 1-6 for the cage numbers.
```

If no JigsawCagesDefinition is provided, the default 4th constraint of  3Rx2C blocks is used.

## Examples
```
SixySolver.exe ...3.2........2..4..5.......6..2....

SixySolver.exe 034000200000000100000000020060500001

SixySolver.exe .34...2........1.........2..6.5....1 112233112233112233445566445566445566

SixySolver.exe ...................1..24.3.....21.36 111222133442135642135642335644555666
```

The SixySudoku in the last example is the first puzzle taken from [here](http://sites.math.rutgers.edu/~zeilberg/Sixy/Problems.html).
```
+-----------+-----------+
| .   .   . | .   .   . |
|   +-------+-------+   |
| . | .   . | .   . | . |
|   |   +---+---+   |   |
| . | . | . | . | . | . |
|   |   |   |   |   |   |
| . | 1 | . | . | 2 | 4 |
+---+   |   |   |   +---+
| .   3 | . | . | .   . |
+-------+   |   +-------+
| .   2   1 | .   3   6 |
+-----------+-----------+
```

## Example sample.txt
```
...................1..24.3.....21.36
111222133442135642135642335644555666
```

.

