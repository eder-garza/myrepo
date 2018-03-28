/*
My program is a very basic form of the grep. I would like to point out 
that my program works only in the form of "./mygrep -f <file-name>". If
you try using the command in the form of "./mygrep --f=<file-name>", the
program will crash and give back an error. Also, I could not get my 
program to work well with the three different files. So, I have all of
the code done in this file. In the makefile, it only compiles this file
only. In order to run my program, you need to use the following format:
"cat <input-file> | ./mygrep -f <file-name>", where the input file is
where my program will get the regex from, and the file name is the one
where my program will search through to find the regex. My output of my
program is the line(s) that contain the regex. I would also like to 
point out that my program is a very simple form of the grep command.
My program only works with characters and brackets. Some examples are: 
"abc", "a[b-e]f", "a[b-zA-z]", etc. It does not work for more complex
regex. I was not sure on how to get it working with ",", ".", "\", "*", 
etc. The way my program works is that it will first create an array of
arrays called result. In here, it will store the regex in the similar way
we did for homework 6. If there is no regex given in the input, then it
will print out a message saying "No regex". After it stores the regex, it
will search through the text file given to search. The way the searching
works is by getting each individual line and scanning through each 
character. If the first character matches the first array of the regex,
then it will increase a counter. The counter is used to move to the 
second array of the regex to compare. For example, if the regex is "abc",
it will store "a", "b", and "c" in three different arrays. If a character
in the text file matches the first array, in this case the "a", the 
counter will move the search to the second array, which is the "b". If
the next character matches the second array, then it will increase the
counter. If not, then it will reset the counter back to zero. If the
counter goes through the arrays of the regex and the counter reaches the
number of arrays, then that means that the sequence was matched and 
prints out the line it is on. If the input were to be "a[b-e]f", my
program will store the regex in 3 arrays: "a", "bcde", and "f". When
searching through the text file and it reaches the second array, there 
is a for loop that will go through to check if it matches any of the
characters. If it does, then it will increase counter. If not, it will
reset the counter back to zero. The for loop only iterates once with 
the arrays like "a" or "f". Unfortunately, my program could not work
correctly without the #include <string.h> header. I tried having a while
loop to iterate through the lines in a file and each character, but it
was not storing things correctly. I got it to work with the <string.h>
and could not find an alternative. 
*/

//contains the "main" routine

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern int errno;

/********** getting regex *******************/

int main(int argc, char* argv[], char* env[])
{
	char results[10000][256];
	char c;
	int tracker = 0;

	while((c = getchar()) != EOF)
	{
		tracker++;
		char pos[256];

		for(int x = 0; x < 256; ++x)
			pos[x] = ' ';

		int loc = 0;

		if((c - 'a' >= 0 && c - 'z' <= 0) || (c - 'A' >= 0 && c - 'Z' <= 0)) 
		{
			pos[0] = c;
			loc++;
		}
		
		else if(c == '[')
		{
			c = getchar();

			while(c != ']')
			{
				if(c == '-')
				{
					char beg = pos[loc - 1] + 1;
					char end = (c = getchar());

					for(int x = (int)beg; x <= (end); ++x)
					{
						pos[loc] = (char)x;
						loc++;
					}

					c = getchar();
				}

				else
				{
					pos[loc] = c;
					c = getchar();
					loc++;
				}	
			}
		}

		for(int x = 0; x < loc; ++x)
		{
			results[tracker - 1][x] = pos[x];
		}
	}

	if(tracker == 0)
		printf("No regex\n");

	/********** scanning text file ********/

	int errnum;

	if(argc != 3)
	{
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		printf("Insufficient number of arguments");
	}

	FILE *file = fopen(argv[2], "r");

	int rep = 0;

	char* line;
	size_t len = 0;
	ssize_t read;

	int found = 0;

	while((read = getline(&line, &len, file)) != -1)
	{
		int count = 0;
		int pointer = 0;
		int found = 0;

		for(int x = 0; x < strlen(line); ++x)
		{
			int check = count;

			for(int y = 0; y < strlen(results[count]); ++y)
			{
				if(line[x] == results[count][y])
					count++;
			}

			if(check == count)
				count = 0;
			
			if(count == tracker)
			{
				printf("%s", line);
				count = 0;
			}
		}
	}

	fclose(file);

	exit(1);
}