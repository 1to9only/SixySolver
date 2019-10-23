
/* sixy sudokusolver.c */

#include <stdio.h>
#include <ctype.h>
  
/* Example of input
 0 0  0 0  4 3
 0 0  0 0  0 1
 0 0  0 0  0 0
 2 0  0 0  0 0
 3 5  0 0  0 0
 1 0  0 0  5 4
*/

/* The outlined rectangles are
11 22 33
11 22 33
11 22 33

44 55 66
44 55 66
44 55 66

*/


/* The shaded rectangles are

aaa bbb
aaa bbb
ccc ddd
ccc ddd
eee fff
eee fff

*/

int z;

char r;

char matrix[6][6];

void getmatrix ( ) {
  char i , j , c ;
  printf(" Insert 6 sudoku rows top-to-bottom\n taking 0 for blanks : \n" ) ;
  for ( i = 0 ; i < 6 ; i++) {
    for ( j = 0 ; j < 6 ; j++) {
      while ( ( c = getchar ( ) ) != EOF ) {
        if ( !isdigit( c ) ) continue ;
        else {
          matrix [ i ] [ j ] = c - '0' ;
          break ;
        }
      }
    }
  }
  return ;
}

void output ( ) {
  int i , j ;
  for ( i = 0 ; i <= 5 ; i++ ) {
    for ( j = 0 ; j <= 5 ; j++ ) {
      printf ( "%d " ,matrix [ i ] [ j ] ) ;
      if ( j % 2 == 1) printf ( " " ) ;
    }
    printf ( "\n" ) ;
    if ( i%3 == 2 ) printf ( "\n" ) ;
  }
  if (z>0){
  printf ( "-- solution %d ---------\n",z ) ;
  } else { printf ( "-----------\n" ) ; }
}

char check ( char a , char b , char u) {
/* Assuming matrix[a][b] is 0, check if value u fits. */
  int i , j ;
  for ( i = 0 ; i < 6 ; i++) {
    if (u == matrix [ a ] [ i ] ) return 1 ;
  }
  for ( i = 0 ; i < 6 ; i++) {
    if (u == matrix [ i ] [ b ] ) return 2 ;
  }
  for ( i = a - a%3 ; i < a - a%3 + 3 ; i++) {
    for ( j = b - b%2 ; j < b - b%2 + 2 ; j++)
      if (u == matrix [ i ] [ j ] ) return 3 ;
  }
  for ( i = a - a%2 ; i < a - a%2 + 2 ; i++) {
    for ( j = b - b%3 ; j < b - b%3 + 3 ; j++)
      if (u == matrix [ i ] [ j ] ) return 4 ;
  }
  return 0 ;
}


char initcheck ( char k ) {
  char u ;
  while ( matrix [ k / 6 ] [ k%6] == 0 && k <= 35 ) k++;
  if ( k == 36 ) return r ;
  u = matrix [ k / 6 ] [ k%6] ;
  matrix [ k / 6 ] [ k%6] = 0 ;
  if ( u > 6 ) {
      printf( " entry at (%d,%d) is too large \n",  k/6+1,k%6+1);
      r = 5;
  }
  if ( check ( k /6 , k%6,u) == 1 ) {
    printf ( "Your puzzle contains a contradiction in row %d . \n" , k/6+1);
    r = 1 ;
  }
  if ( check ( k /6 , k%6,u) == 2 ) {
    printf ( "Your puzzle contains a contradiction in column %d . \n" , k%6+1);
    r = 2 ;
  }
  if ( check ( k /6 , k%6,u) == 3 ) {
    printf ( "Your puzzle contains a contradiction in outlined rectangle at (%d,%d) \n",  k/6+1,k%6+1);
    r = 3 ;
  }
  if ( check ( k /6 , k%6,u) == 4 ) {
    printf ( 
    "Your puzzle contains a contradiction in shaded rectangle at (%d,%d) \n",  k/6+1,k%6+1);
    r = 4 ;
  }
  matrix [ k / 6 ] [ k%6] = u ;
  initcheck ( k+1);
  return r ;
}

void search ( char k ) {
  char i ;
  while ( k <= 35 && matrix [ k / 6 ] [ k%6] ) k++;
  if ( k == 36 ) {
    z++;
    if ( z == 1) {
      printf ( " First solution found : \n" ) ;
    }
    output ( ) ;
  }
  for ( i = 1 ; i <= 6  ; i++) {
    if ( check ( k /6 , k%6, i ) == 0) {
      matrix [ k / 6 ] [ k%6] = i ;
      if ( k == 35) {
        z++;
        output();
        matrix [ 5 ] [ 5 ] = 0 ;
        break ;
      }
      else {
        search ( k+1);
        matrix [ k / 6 ] [ k%6] = 0 ;
      }
    }
  }
}

int main ( ) {
  char i , j ;
  getmatrix ( ) ;
  printf("-----------\n");
  output ( ) ;
  if ( initcheck ( 0 ) == 0 ) {
    search ( 0 ) ;
    if ( z == 0) printf ( "There is no solution to your puzzle .\n" ) ;
    if ( z == 1) printf ( "This solution is unique ! \n" ) ;
    if ( z > 1) printf ( "This solution is not unique ! \n" ) ;
      printf("Result: %d\n", z);
      return 0;
  }
}

