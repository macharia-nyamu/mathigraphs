#include <stdio.h>
#include <string.h>
#include "mathi.h"
#include "headers/mathigraphs.h"

int main()
{
	char cont[] = "mathigraphs# ";

	// opening remarks
	starter();

	// loop wrapper
	while(1)
	{
		printf("%s", cont);
		fflush(stdout);

		// get the user input
		InputResult inp = mathi_get_string("");
		if(inp.code == 1)
		{
			printf("Invalid condition\n");;
			continue;
		}

		// validate the input // from mathi c library
		char *user_inp = mathi_string_to_lower((char*)inp.value);
		if (mathi_string_compare(user_inp, "help") == 0)
		{
			bar_help();
		}
		else if(mathi_string_compare(user_inp, "exit") == 0)
		{
			printf("Bye!\n");
			break;
		}
		else if (strncmp(user_inp, "bar", 3) == 0) // supports bar only for now
		{
			display_bar(user_inp);
		}
		else
		{
			printf("Invalid command. Type help to see commands\n");
		}

		// new lines
		printf("\n");
	}

	return 0;
}