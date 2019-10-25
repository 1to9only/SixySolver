
/* sixy7 sudokusolver.c */

#include <stdio.h>
#include <ctype.h>

/* examples of input 
    1233550 
    233550 
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

int z, count, tails;

char r, coresize, cell, verbose;

char matrix[6][6];

char startmatrix[6][6];

int pairs[2][2];

char fivek[6];

char getdigit (){
char c;
while ( ( c = getchar ( ) ) != EOF ) {
        if ( !isdigit( c ) ) continue ;
        else {
          c = c - '0' ;
          break ;
        }
      }
return c;
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
  printf ( " has unique solution %d \n\n",z ) ;
  } else { printf ( "-----------\n----------\n" ) ; }
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
/*    if ( z == 1) {
      printf ( " First solution found : \n" ) ;
    }
    output ( ) ;*/
  }
  for ( i = 1 ; i <= 6 && z <= 1  ; i++) {
    if ( check ( k /6 , k%6, i ) == 0) {
      matrix [ k / 6 ] [ k%6] = i ;
      if ( k == 35) {
        z++;
    /*    output(); */
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

char check5 () {
    char i ,j;
    for (i=0; i<=35;i++) {matrix[i/6][i%6]=startmatrix[i/6][i%6];}
    for (j=0;j<=4;j++){i=fivek[j];matrix[i/6][i%6]=j+1;}
    r=0;
    z=0;
    tails++;
    search ( 0 ) ;
    if ( z==1) {
        count++;z=count;
        if (verbose==1){output ( ) ;}
    }
    return 0;
}

char check4 () {
    char i ,j;
    for (i=0; i<=35;i++) {matrix[i/6][i%6]=startmatrix[i/6][i%6];}
    for (j=0;j<=3;j++){i=fivek[j];matrix[i/6][i%6]=j+1;}
    r=0;
    z=0;
    tails++;
    search ( 0 ) ;
    if ( z==1) {
        count++;z=count;
        if (verbose==1){output ( ) ;}
    }
    return 0;
}

char check3 () {
    char i ,j;
    for (i=0; i<=35;i++) {matrix[i/6][i%6]=startmatrix[i/6][i%6];}
    for (j=0;j<=2;j++){i=fivek[j];matrix[i/6][i%6]=j+1;}
    r=0;
    z=0;
    tails++;
    search ( 0 ) ;
    if ( z==1) {
        count++;z=count;
        if (verbose==1){output ( ) ;}
    }
    return 0;
}

char tail5(){
  char i , j , a, b, c;
  tails=0;
if (!(initcheck(0)==0)){return 1;};
    for (i=0; i<=35;i++) {startmatrix[i/6][i%6]=matrix[i/6][i%6];}
    for (i=0;i<=31;i++){
        for(j=i+1;j<=32;j++){
            for(a=j+1;a<=33;a++){
                for(b=a+1;b<=34;b++){
                    for(c=b+1;c<=35;c++){
                        fivek[0]=i;fivek[1]=j;fivek[2]=a;fivek[3]=b;fivek[4]=c;
                        if (c<=35) {check5();};
                    }
                }
            }
        }
    }
    if(verbose==1){printf("tails=376992 ? tails=%d\ncount=",tails);}
    printf("=%d\n",count);
    return 0;
}

char tail4(){
  char i , j , a, b, c;
  tails=0;
if (!(initcheck(0)==0)){return 1;};
    for (i=0; i<=35;i++) {startmatrix[i/6][i%6]=matrix[i/6][i%6];}
        for(j=0;j<=32;j++){
            for(a=j+1;a<=33;a++){
                for(b=a+1;b<=34;b++){
                    for(c=b+1;c<=35;c++){
                        fivek[0]=j;fivek[1]=a;fivek[2]=b;fivek[3]=c;
                        if (c<=35) {check4();};
                    }
                }
            }
        }
    if(verbose==1){printf("tails=58905 ? tails=%d\ncount=",tails);}
    printf("=%d\n",count);
    return 0;
}

char tail3(){
  char i , j , a, b, c;  
  tails=0;
if (!(initcheck(0)==0)){return 1;};
    for (i=0; i<=35;i++) {startmatrix[i/6][i%6]=matrix[i/6][i%6];}
            for(a=0;a<=33;a++){
                for(b=a+1;b<=34;b++){
                    for(c=b+1;c<=35;c++){
                        fivek[0]=a;fivek[1]=b;fivek[2]=c;
                        if (c<=35) {check3();};
                    }
                }
            }
    if(verbose==1){printf("tails=7140 ? tails=%d\ncount=",tails);}
    printf("=%d\n",count);
    return 0;
}

char getcell ( ) {
  char i , b, c ;
  b=getdigit();
  r=0;
  z=0;
  if ((6 < b )||(b==0)) {return 1;};c= getdigit() ;
  if ((6 < c )||(c==0)) {return 1;};
  if (cell==0){for (i=0; i<=35;i++){matrix[i/6][i%6]=0;};printf("\ncount[\{");}
  matrix [ b -1] [ c-1 ] = ((29-cell)-coresize)/4 ;
  printf("\{%d,%d}",b,c);
  if(verbose==1){printf("\n"); output();}
  if (cell<(coresize-1)){printf(",");}else {
  printf("}]");count=0;
  for (i=0; i<=35;i++) {startmatrix[i/6][i%6]=matrix[i/6][i%6];}
  if(verbose==1){printf("\n"); output();}
  if(coresize==2){tail5();}
  if(coresize==3){tail4();}
  if(coresize==4){tail3();}
  }
  if (verbose==1){printf("\n%d\n",matrix [ b ] [ c ]);}
  return 0;
}

int main ( ) {
  char i , j , a, b, c;
  printf("\nverbose=1;stop=0;\n");
  i = getdigit();
  if (i == 1){
     verbose =1 ; printf("give core size (2, 3 or 4)\n");coresize = getdigit();} 
     else {coresize = i;}
  if ((coresize<2)||(coresize>4)) {printf("wrong coresize\n");return 1;}
  while (getcell(  ) == 0) {
  if (verbose==1){printf("cell=%d\n",cell);}
  cell = (cell+1)%coresize;};
    return 0;
}

