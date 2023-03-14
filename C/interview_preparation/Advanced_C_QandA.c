// Disclaimer:
// This Q&A list is not my original work.
// It is compiled from the internet.
// Few sources are listed below:
// 1. https://engineeringstudentshub.wordpress.com/interview-questions/advanced-c-interview-questions-and-answers-for-experienced/
// 2. 

1) How to free a block of memory previously allocated without using free?
A) If the pointer holding that memory address is passed to realloc with size argument as zero (like realloc(ptr, 0)) the the memory will be released.

2) How can you print a string containing ‘%’ in printf?
A) There are no escape sequence provided for ‘%’ in C. To print ‘%’ one should use ‘%%’, like - printf(“He got 90%% marks in math”);


3) What is use of %n in printf()?
A) According to man page “the number of characters written so far is stored into the integer. indicated by the int * (or variant) pointer argument.“. Meaning if we use it in printf, it will get the number of characters already written until %n is encountered and this number will stored in the variable provided. The variable must be an integer pointer.
#include<stdio.h>
int main ()
{
  int c;
  printf ("ABCDEXYZ%n world \n", &c);
  printf ("%d ", c);
}

4) Swap two variables without using any control statement ?
A) We can swap variable using two ways.

#include <stdio.h>
int
main ()
{
  int a = 6;
  int b = 10;
  a = a + b;
  b = a - b;
  a = a - b;
  printf ("a: %d, b: %d\n", a, b);
}

#include <stdio.h>
int main ()
{
  int a = 6;
  int b = 10;
  a ^= b;
  b ^= a;
  a ^= b;
  printf ("a: %d, b: %d\n", a, b);
}

5) How to convert a string to integer value?
A) We can convert a string to integer in two ways. 
Method 1:
int i = atoi(str);

Method 2:
sscanf(str, “%d”, &i);

6) What is the output of following switch-case?
#include <stdio.h>
int main() {
  int i = 2;
  switch(i) {
    default: printf("default\n"); break; // Default condition is not satisfied in spite of it being before 'case 2'
    case 1: printf("one\n"); break;
    case 2: printf("two\n"); break; // This is the output.
    case 3: printf("three\n"); break;
  } 
}

7) Print the output of this pointer program?
#include<stdio.h>
int main()
{
  char *p = "Pointers";
  p[2] = 'z';
  printf("%s", p);
}
The program MAY crash depending on compiler.
The pointer p points to string “Pointers”. 
But the string in constant and C will not allow to change its values. 
Forcibly doing so, like we did it, will cause crash of the program.

8) What is the difference between const char* p and char const* p?
In const char* p, the character pointed by pointer variable p is constant. 
This value can not be changed but we can initialize p with other memory location. 
It means the character pointed by p is constant but not p. 
In char const* p, the pointer p is constant not the character referenced by it. 
So we can’t assign p with other location but we can change the value of the character pointed by p.

9) What is the point of using malloc(0)?
A) Depends on compiler. Either a null pointer is returned, or the behavior is as if the size were some nonzero value, except that the returned pointer shall not be used to access an object.

10) What is Function Pointer?
A)
Function Signature:
void Hello(int);

Function Pointer:
void (*ptr)(int);

11) Declare a function pointer that points to a function which returns a function pointer ?
A) From 10 above,
  typedef void (*FP)(int);
  FP get_function_ptr(int a);

12) Write a C program to find out if the underlying architecture is little endian or big endian?
#include <stdio.h>
int
main ()
{
  unsigned int x = 0x76543210;
  char *c = (char *) &x;

  printf ("*c is: 0x%x\n", *c);

  if (*c == 0x10)
    {
      printf ("Underlying architecture is little endian. \n");
    }
  else
    {
      printf ("Underlying architecture is big endian. \n");
    }
  return 0;
}

13) Write a program to get the higher and lower nibble of a byte without using shift operator?
A)
#include <stdio.h>
struct full_byte
{
  unsigned char first:4;
  unsigned char second:4;
};

union A
{
  char x;
  struct full_byte by;
};

int
main ()
{
  char c = 0x39;
  union A a;
  a.x = c;
  printf ("the two nibbles are: %x and %x\n", a.by.first, a.by.second);
}

14) Guess the output or error.
#include<stdio.h>
#define SQUARE(x) (x)*(x)
int main ()
{
  int i = 5;
  printf ("Ans: %d\n", SQUARE(++i));
  // Equivalent to -
  // printf ("Ans: %d\n", ((++i) * (++i)));
}
A) Ans: 49

15) Can math operations be performed on a void pointer?
A) No. 
Pointer addition and subtraction means advancing the pointer by a number of elements.
But in case of a void pointer, we don’t know fpr sure what it’s pointing to, so we don’t know the size of what it’s pointing to.
That is why pointer arithmetic can not be used on void pointers.

16) Use of #line num.
#include<stdio.h>
int main ()
{
  printf ("First: %d\n", __LINE__);
#line 0

  printf ("Second: %d\n", __LINE__);
  printf ("Third: %d\n", __LINE__);
}
A)
First: 4
Second: 1
Third: 2

17) What is the output?
#include <stdio.h>
int main (void)
{
  int a[5] = { 1, 2, 3, 4, 5 };
  int *ptr = (int *) (&a + 1);
  printf ("%d %d\n", *(a + 1), *(ptr - 1));
  return 0;
}
A) Output of this program – 2 5
Here a has type array[5] of int, and &a has type pointer to array[5] of int.
So, ptr will yield a pointer to the array[5] of int that comes after a.
Subtracting 1 from ptr will point to the last element of a which is 5.
Remember, here &a and &a[0] both will point to starting address of the array or the address of the first element.
But (&a + 1) points block of memory of size 5 times the sizeof(int) that comes after the memory block of a, while (&a[0] + 1) return the address of the second element.

18) What is the output of this C program on operator precedence?
#include <stdio.h>
int main (void)
{
  int a, b, c, d;

  a = 3;
  b = 5;

  c = a, b;
  d = (a, b);

  printf ("c=%d ", c);
  printf ("d=%d\n", d);

  return 0;
}
A) Output – 3 5
Comma operator has the least precedence.
In the assignment operation of c, the comma has less priority that assignment operator. So, c = a, b actually evaluates to (c = a), b.
In the assignment of variable d, the comma operator evaluates both of its operands and returns the value of the second. So, d = (a, b) is equivalent to d = b.

19) Print the output of value assignment to a C constant program?
#include<stdio.h>
void main ()
{
  int const *p = 5;
  printf ("%d", ++(*p));
}
A) This program will give a compiler error because 'p' is a pointer to a “constant integer”.

20) What is the output of this data comparison C program?
#include<stdio.h>
void main ()
{
  float me = 1.1;
  double you = 1.1;
  if (me == you)
    printf ("I love U");
  else
    printf ("I hate U");
}
A) Output is “I hate U”
For floating point numbers (float, double, long double) the values cannot be predicted exactly.
Depending on the number of bytes, the precession with of the value represented varies.

21) Guess the output of the backspace and carriage return C program?
#include<stdio.h>
void main ()
{
  printf ("\nab");
  printf ("\bsi");
  printf ("\rha");
}
A) Output is “
              hai”

The “\b” in C represents backspace and \r carriage return. The “\b” will erase the last character printed in the output.
So, the first printf feed a newline character and then prints ab. 
The second printf first erases b from ab and then prints si. Until now the output is asi. 
The third printf encounters the “\r” and move the cursor back to the beginning of the line and then prints ha overwriting the as of the asi.
So, the final output will be hai.

22) Print the output of this format specifier C Program? 
#include<stdio.h>
void main ()
{
  char s[] = "Hello World";
  int i = 7;
  printf ("%20.*s", i, s);
}
A) Output of this program is “             Hello w”
In this program the format specifier is a bit different from normal %s.
After the “%” operator the 20 forces to print minimum 20 characters to be printed in output.
The “.*” followed by that takes an integer argument and represents the number of characters to be printed from the string followed.
So, the argument i with value 7 forces to print first 7 characters of the variable s.
The remaining 13 characters are filled by preceding blank spaces.

23) Guess the output or error?
#include<stdio.h>
struct A
{
  int i;
  char str[10];
  float f;
};

int main ()
{
  struct A a = { 4 };
  printf ("%d %s %f\n", a.i, a.str, a.f);
}
A) The program will print "4 0.0000"
In C, when a structure variable in partially initialized, other members of that variables will be initialized to 0 or NULL.
Here, a.str will be initialized to NULL and a.f will be initialized to 0.0000.

24) How to use scanf to get a complete line(i.e upto ‘\n’) from input?
A) Use scanf(“%[^\n]”, str). [^\n] is a regular expression that means until ‘\n’ is encountered.

25) Print the output of this function pointer C program?
char fun()
{
  char c = ‘A’;
  printf(“Hello World”);
  return c;
}
int main()
{
  printf(“%d”, sizeof(fun()));
}
A) Output is 1. 
Even if this is function pointer, the sizeof will get the return type and returns the size of that data type.
Here, the return type is char, so the output is 1.

Q) What is the output ?
#include<stdio.h>
void main ()
{
  int x = 'Aa';
  printf ("%#x", x);
}
A)
 warning: multi-character character constant [-Wmultichar]
    7 | int x = 'Aa';
      |         ^~~~
0x4161
Output of this program is  “0x4161”.
The ‘Aa’ here is multi-character assignment.
It means the i will hold ascii value of these two characters in its two bytes.
Thus the output is 0x4161.

Q) What is the output ?
#include <stdio.h>
void main ()
{
  int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  printf ("%d", 1[a]);
}
A) Output of this program is 1. 
The a[1] expression is equivalent to *(a + 1) and 1[a] is equivalent to *(1 + a).
Both of them are same. So, 1[a] will return the value of a[1].


