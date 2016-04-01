/* SSCANF.C: This program uses sscanf to read data items
 * from a string named tokenstring, then displays them.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main( void )
{
   char  tokenstring[] = "15 12 14...";
   char  s[81];
   char  c;
   int   i;
   float fp;

   /* Input various data from tokenstring: */
   sscanf( tokenstring, "%s", s );
   sscanf( tokenstring, "%c", &c );
   sscanf( tokenstring, "%d", &i );
   sscanf( tokenstring, "%f", &fp );

   /* Output the data read */
   printf( "String    = %s\n", s );
   printf( "Character = %c\n", c );
   printf( "Integer:  = %d\n", i );
   printf( "Real:     = %f\n", fp );
 
}


/*Output

String    = 15
Character = 1
Integer:  = 15
Real:     = 15.000000

*/
