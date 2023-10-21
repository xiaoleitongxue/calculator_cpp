#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// convert c style string to number

long double string2number(char *s)
{

   char *end;
   const long double d = strtold(s, &end);
   if (*end == '\0')
   {
      // It's a long double
      return d;
   }
   else
   {
      printf("The input cannot be interpret as numbers!\n");
      abort();
   }

   return 0;
}
int main(int argc, char *argv[])
{
   if (argc != 4)
   {

      printf("No enough arguments\n");
      return 0;
   }
   char *left = argv[1];
   char *op = argv[2];
   char *right = argv[3];

   long double a = string2number(left);
   long double b = string2number(right);
   long double res = 0;
   if (strcmp(op, "+") == 0)
   {
      res = a + b;
   }
   else if (strcmp(op, "-") == 0)
   {
      res = a - b;
   }
   else if (strcmp(op, "*") == 0)
   {
      res = a * b;
   }
   else if (strcmp(op, "/") == 0)
   {
      if (b != 0)
      {
         res = a / b;
      }
      else
      {
         printf("A number cannot be divied by zero.\n");
         return 0;
      }
   }

   if (res - (long)res == 0)
   {
      printf("%Lf %s %Lf = %ld\n", a, op, b, (long)res);
   }
   else
   {
      printf("%Lf %s %Lf = %Lf\n", a, op, b, res);
   }

   return 0;
}
