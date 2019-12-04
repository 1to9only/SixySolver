//                                  //
// /* sixy sudokusolver.c */        // /* solver.c - modified from sixy.c */
//                                  //
// #include <stdio.h>               //
// #include <ctype.h>               //
//                                  //
// /* Example of input              // grid:  ....43.....1......2.....35....1...54
//  0 0  0 0  4 3                   //
//  0 0  0 0  0 1                   // grid:  000043000001000000200000350000100054
//  0 0  0 0  0 0                   //
//  2 0  0 0  0 0                   // block: 111222111222333444333444555666555666
//  3 5  0 0  0 0                   //
//  1 0  0 0  5 4                   // cage:  112233112233112233445566445566445566
// */                               //
//                                  //
// /* The shaded rectangles are     // int sudblock[6][6] = {
// aaa bbb                          //    {  0,  1,  2,  6,  7,  8 },
// aaa bbb                          //    {  3,  4,  5,  9, 10, 11 },
//                                  //    { 12, 13, 14, 18, 19, 20 },
// ccc ddd                          //    { 15, 16, 17, 21, 22, 23 },
// ccc ddd                          //    { 24, 25, 26, 30, 31, 32 },
//                                  //    { 27, 28, 29, 33, 34, 35 }
// eee fff                          // };
// eee fff                          //
//                                  //
// */                               //
//                                  //
// /* The outlined rectangles are   // int sudcage[6][6] = {
// 11 22 33                         //    {  0,  1,  6,  7, 12, 13 },
// 11 22 33                         //    {  2,  3,  8,  9, 14, 15 },
// 11 22 33                         //    {  4,  5, 10, 11, 16, 17 },
//                                  //    { 18, 19, 24, 25, 30, 31 },
// 44 55 66                         //    { 20, 21, 26, 27, 32, 33 },
// 44 55 66                         //    { 22, 23, 28, 29, 34, 35 }
// 44 55 66                         // };
//                                  //
// */                               //
//
//
// int z;
//
// char r;
//
// char matrix[6][6];
//
// void getmatrix ( ) {
//   char i , j , c ;
//   printf(" Insert 6 sudoku rows top-to-bottom\n taking 0 for blanks : \n" ) ;
//   for ( i = 0 ; i < 6 ; i++) {
//     for ( j = 0 ; j < 6 ; j++) {
//       while ( ( c = getchar ( ) ) != EOF ) {
//         if ( !isdigit( c ) ) continue ;
//         else {
//           matrix [ i ] [ j ] = c - '0' ;
//           break ;
//         }
//       }
//     }
//   }
//   return ;
// }
//
// void output ( ) {
//   int i , j ;
//   for ( i = 0 ; i <= 5 ; i++ ) {
//     for ( j = 0 ; j <= 5 ; j++ ) {
//       printf ( "%d " ,matrix [ i ] [ j ] ) ;
//       if ( j % 2 == 1) printf ( " " ) ;
//     }
//     printf ( "\n" ) ;
//     if ( i%3 == 2 ) printf ( "\n" ) ;
//   }
//   if (z>0){
//   printf ( "-- solution %d ---------\n",z ) ;
//   } else { printf ( "-----------\n" ) ; }
// }
//
// char check ( char a , char b , char u) {
// /* Assuming matrix[a][b] is 0, check if value u fits. */
//   int i , j ;
//   for ( i = 0 ; i < 6 ; i++) {
//     if (u == matrix [ a ] [ i ] ) return 1 ;
//   }
//   for ( i = 0 ; i < 6 ; i++) {
//     if (u == matrix [ i ] [ b ] ) return 2 ;
//   }
//   for ( i = a - a%3 ; i < a - a%3 + 3 ; i++) {
//     for ( j = b - b%2 ; j < b - b%2 + 2 ; j++)
//       if (u == matrix [ i ] [ j ] ) return 3 ;
//   }
//   for ( i = a - a%2 ; i < a - a%2 + 2 ; i++) {
//     for ( j = b - b%3 ; j < b - b%3 + 3 ; j++)
//       if (u == matrix [ i ] [ j ] ) return 4 ;
//   }
//   return 0 ;
// }

#define VALUE_IS_NOT_USED     0
#define VALUE_USED_IN_ROW     1
#define VALUE_USED_IN_COLUMN  2
#define VALUE_USED_IN_BLOCK   3
#define VALUE_USED_IN_CAGE    4

int check( int row, int column, int value)
{
   for (int x=0; x<6; x++ ) {
      if ( value == grid[ row*6 + x] ) return VALUE_USED_IN_ROW;
   }

   for (int y=0; y<6; y++ ) {
      if ( value == grid[ y*6 + column] ) return VALUE_USED_IN_COLUMN;
   }

   int block = getblock[ row*6 + column];
   for (int index=0; index<6; index++ ) {
      int cell = sudblock[ block][ index];
      if ( value == grid[ cell] ) return VALUE_USED_IN_BLOCK;
   }

   int cage = getcage[ row*6 + column];
   for (int index=0; index<6; index++ ) {
      int cell = sudcage[ cage][ index];
      if ( value == grid[ cell] ) return VALUE_USED_IN_CAGE;
   }

   return VALUE_IS_NOT_USED;
}

// char initcheck ( char k ) {
//   char u ;
//   while ( matrix [ k / 6 ] [ k%6] == 0 && k <= 35 ) k++;
//   if ( k == 36 ) return r ;
//   u = matrix [ k / 6 ] [ k%6] ;
//   matrix [ k / 6 ] [ k%6] = 0 ;
//   if ( u > 6 ) {
//       printf( " entry at (%d,%d) is too large \n",  k/6+1,k%6+1);
//       r = 5;
//   }
//   if ( check ( k /6 , k%6,u) == 1 ) {
//     printf ( "Your puzzle contains a contradiction in row %d . \n" , k/6+1);
//     r = 1 ;
//   }
//   if ( check ( k /6 , k%6,u) == 2 ) {
//     printf ( "Your puzzle contains a contradiction in column %d . \n" , k%6+1);
//     r = 2 ;
//   }
//   if ( check ( k /6 , k%6,u) == 3 ) {
//     printf ( "Your puzzle contains a contradiction in outlined rectangle at (%d,%d) \n",  k/6+1,k%6+1);
//     r = 3 ;
//   }
//   if ( check ( k /6 , k%6,u) == 4 ) {
//     printf (
//     "Your puzzle contains a contradiction in shaded rectangle at (%d,%d) \n",  k/6+1,k%6+1);
//     r = 4 ;
//   }
//   matrix [ k / 6 ] [ k%6] = u ;
//   initcheck ( k+1);
//   return r ;
// }
//
// void search ( char k ) {
//   char i ;
//   while ( k <= 35 && matrix [ k / 6 ] [ k%6] ) k++;
//   if ( k == 36 ) {
//     z++;
//     if ( z == 1) {
//       printf ( " First solution found : \n" ) ;
//     }
//     output ( ) ;
//   }
//   for ( i = 1 ; i <= 6  ; i++) {
//     if ( check ( k /6 , k%6, i ) == 0) {
//       matrix [ k / 6 ] [ k%6] = i ;
//       if ( k == 35) {
//         z++;
//         output();
//         matrix [ 5 ] [ 5 ] = 0 ;
//         break ;
//       }
//       else {
//         search ( k+1);
//         matrix [ k / 6 ] [ k%6] = 0 ;
//       }
//     }
//   }
// }

int solutions = 0;
int solve( int cell)
{
   while ( grid[ cell] != 0 && cell < 36 ) { cell++; }
   if ( cell == 36 ) {
      solutions++;
      if ( solutions == 1 ) {
         for (int c=0; c<36; c++ ) { solution[ c] = grid[ c]; }   // save 1st solution
      }
   }

   for (int value=1; value<=6; value++ ) {
      if ( check( cell/6, cell%6, value) == 0 ) {
         grid[ cell] = value;
         if ( cell == 35 ) {
            solutions++;
            break;
         }
         else {
            solve( cell+1);
            grid[ cell] = 0;
         }
      }
   }

   return solutions;
}

// int main ( ) {
//   char i , j ;
//   getmatrix ( ) ;
//   printf("-----------\n");
//   output ( ) ;
//   if ( initcheck ( 0 ) == 0 ) {
//     search ( 0 ) ;
//     if ( z == 0) printf ( "There is no solution to your puzzle .\n" ) ;
//     if ( z == 1) printf ( "This solution is unique ! \n" ) ;
//     if ( z > 1) printf ( "This solution is not unique ! \n" ) ;
//       printf("Result: %d\n", z);
//       return 0;
//   }
// }
//
