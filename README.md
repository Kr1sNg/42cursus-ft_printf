# my journey with ft_printf()

_as the second practical project in the Common Core (cursus) of School 42_

![](https://cdn-images-1.medium.com/max/1200/0*9QrjlooKoUZpB_fz)

It’s 13:30 in the afternoon, right after my lunch, and I’m about to start this project for l’Ecole 42 Perpignan. It will be the second project I have done after a sequence of drama with the function library “libft”, which I will tell you all about in another post.

Ok, well. First of all, we have to check the subject: “**_ft_printf _**— Because ft_putnbr() and ft_putstr() aren’t enough”. So in general with this project, I will try to implement the function **_printf()_** on my own.

![42’s subject of ft_printf](https://cdn-images-1.medium.com/max/1200/1*aJs0qnAF0OmV3kP4o33ysw.png)

With the keyword _“_[**_variadic functions_**](https://www.geeksforgeeks.org/variadic-functions-in-c/)_”_, here’s what I found on the Internet.

----------

#### Variadic functions

**_Variadic functions_** are functions that can take a variable number of arguments. It takes one fixed argument (or mandatory argument) and then any number of arguments can be passed, by the “…” at the end of syntax.

**Syntax**
<code>#include <stdarg.h>  
  return_type 		function_name(data_type variable_name, ...);  
  </code>
applying to ***ft_printf:***
<code>(int)		ft_printf("mandatory argument", 'variable argument', ...);
</code>

Allowed external functions:
<code>#include <stdarg.h>  
void		va_start(va_list ap, last_arg); 
type 	va_arg(va_list ap, type);  
void 	va_copy(va_list dest, va_list src);  
void		va_end(va_list ap);  
</code>

-   _va_list_ : is an object type suitable for holding the information needed by the macros _va_start_, _va_arg_, _va_copy_, and _va_end_.
-   _ap :_ is a variable of type _va_list_.
-   _last_arg_ : is the last fixed argument (the mandatory argument).
-   _type_ : type of variable

OK after refreshing my brain with one track-list of “[Anh trai say hi](https://youtu.be/TM9SGdrOMsk?si=enlNndTUk2I08kBj)” finally, I could focus one more time in **_ft_printf()_**.

----------

#### printf()

**_printf()_** is a C standard library function that formats texts and writes it to standard output. Otherwise, **_printf_** means _print formatted._

**Format specifiers**

-   **%c** : Prints a single character (char / int)
-   **%s** : Prints a null-terminated string (char *)
-   **%p** : Prints the address of a pointer or any other variable. The output is displayed in hexadecimal value (base 16). It’s a format specifier for printing data of type (void *)
-   **%d** : Prints a decimal (base 10) number (int)
-   **%i** : Prints an integer in base 10 (int)
-   **%u** : Prints an unsigned decimal (base 10) number (unsigned int)
-   **%x** : Prints a number in hexadecimal (base 16) lowercase format (unsigned int)
-   **%X** : Prints a number in hexadecimal (base 16) uppercase format (unsigned int)
-   **%%** : Prints a percent sign (%)

**Prototype and return value**

Following the guideline, the prototype of **_ft_printf_** is:
<code>int  ft_printf(const char *, ...); </code>

It returns a value of type int to make sure that the operation of function was successful or not using the return value.

-   if a positive value is returned (indicating the number of characters written in total), it means the operation was successful.
-   if a negative value is returned, there was some error.

Example with the return of real **_printf()_**
<code>#include <stdio.h>  
int main()  
{  
    int result = printf("Sentence to know how many %s\n", "characters were written");
    printf("%d characters were written in total (both mandatory and variable arguments)\n", result);  
}
</code>

----------

### Building the function ft_printf()

#### Pseudo-code:

1.  **_ft_printf_** will write every character of the initial string (in mandatory argument) each by each until it finds a ‘%’.
2.  When it finds a ‘%’, it will look at the character in the next position. It will find the character which defines the type of the first variable argument (the second argument in prototype).
3.  Depending on what is found, ft_printf will call the following function that displays the argument of the particular type in standard output. Par example, if there is an “s” after the ‘%’, then it calls a function that displays string, or if there is a “d”, it will call a function that displays decimal numbers, etc.
4.  After the first variable argument has been successfully written, go back to step 1, until finishing the mandatory argument (with the NULL character).
5.  Do not forget to count the number of characters which has been printed each time, in order to return the final number of characters at the end of ft_printf.

#### Coding:

There are some probable problems I want to note:

-   cast type of variable arguments **av_arg** for **%p, %x, %X** is *“unsigned long long”*
-   print ***“(nil)”*** and return 5 when pointer in **%p** is 0 (or NULL), else print ***“0x”*** and hexadecimal.
-   always remember to count the number of printed characters to return in the end of function.

#### **Bonus part:**

Format prototype:
% [‘ + ’ ‘ — ’ ‘ ’ ‘ 0 ’ ‘ # ’] [ _( number )_ ] [ .number ]
________________%_<_____flag_____><__width__><_.precision_>

**Flags:**

-   [#] : Used with **%x** or **%X** specifiers the value is preceded with “0x” or “0X” respectively for values different than zero.
-   [+] : Forces to precede the result of **%i** and **%d** specifiers with a plus (+) or minus (-) sign even for positive numbers (+99) and zero (+0). By default, only negative numbers are preceded by a (-) sign.
-   [space] : If no sign is going to be written in the result of **%i** and **%d** specifiers, a blank space is inserted before the value. That means (space) can’t work with [+]
-   [0] : Left-pads the number with zeroes (0) instead of spaces when padding is specified with the width bigger than argument length (ex: [-000002024]). Flag [0] work with **%d %i %u %x %X %%** specifiers together with [width] or [.precision].
-   [-] : Left-justify within the given field width which is longer than argument length (ex: [2024______]), the right justification is the default (ex: [______2024]). Flag [-] can’t work together with flag [0].

**Width:**

-   **[number]** : Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.

**.precision:**

- [.number] : For integer specifiers (**%d**, **%i**, **%u**, **%x**, **%X**): _precision_ specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A _precision_ of 0 means that no character is written for the value 0. For **%s**: this is the maximum number of characters to be printed. By default, all characters are printed until the ending null character is encountered.

----------

F̶i̶n̶a̶l̶l̶y̶,̶ ̶I̶ ̶c̶o̶u̶l̶d̶n̶’̶t̶ ̶f̶i̶n̶i̶s̶h̶ ̶t̶h̶e̶ ̶b̶o̶n̶u̶s̶ ̶p̶a̶r̶t̶.̶ ̶I̶t̶’̶s̶ ̶t̶o̶o̶ ̶l̶o̶n̶g̶ ̶a̶n̶d̶ ̶t̶o̶o̶ ̶c̶o̶m̶p̶l̶i̶c̶a̶t̶e̶d̶ ̶w̶h̶e̶n̶ ̶m̶i̶x̶i̶n̶g̶ ̶f̶l̶a̶g̶s̶!̶ ̶I̶ ̶h̶a̶v̶e̶ ̶t̶o̶ ̶a̶d̶m̶i̶t̶ ̶t̶h̶a̶t̶ ̶I̶ ̶d̶i̶d̶n̶’̶t̶ ̶h̶a̶v̶e̶ ̶e̶n̶o̶u̶g̶h̶ ̶p̶a̶t̶i̶e̶n̶c̶e̶ ̶t̶o̶ ̶g̶e̶t̶ ̶i̶t̶ ̶😢̶

Shortly update, at the end of Milestone 1, after finishing Born2beroot and get_next_line, I returned to fix what I had given up in this project, and finally, it passed all bonuses. So I’m officially done with this! Woohoo 🎉

----------

**References:**
<br>[printf](https://cplusplus.com/reference/cstdio/printf/) <br>
[Let's build a mini printf function](https://youtu.be/byRw36Y3Hjs?si=vALAB0UQ5mC5cB-P) <br>
[ft_printf | Guide](https://42-cursus.gitbook.io/guide/rank-01/ft_printf)
