

//											 Read Me


// In order to read user input, we've used the "readline" library for GNU that can be installed using    sudo apt-get install libreadline-dev
// To create the binary file, please use the command     gcc assignment.c -lreadline    
// To run the program please run      ./a.out

#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<string.h> 
#include<unistd.h> 
#include<readline/readline.h> 


// Read the input by the user
int scanUserInput(char* str) 
{ 
	char* strLine; 
	strLine = readline("\n>>> "); 
	if (strlen(strLine) != 0) {   // Checking if there was indeed an input or is empty
		strcpy(str, strLine);  //Once confirmed, we store back the input line into the str pointer (pass by referrence)
		return 0; 
	} else { 
		return 1; 
	} 
} 


// Executing the parsed comand using execvp which is similar to execl but takes an array of command + arguments 
void execArgs(char** commandToExec) 
{ 
	// Forking a child 
	pid_t childProcess = fork(); 

	if (childProcess == -1) {  // Couldn't fork a child
		printf("\nError, couldn't fork a child.."); 
		return; 
	} else if (childProcess == 0) { 
    
		if (execvp(commandToExec[0], commandToExec) < 0) {  //Command executed successfully
			printf("\nNo command found"); 
		} 
		exit(0); 
	} else { 
		// waiting for child to terminate 
		wait(NULL); 
		return; 
	} 
} 

// Function to execute builtin commands 
int nonExecutablesCMDs(char** parsed) 
{ 
	int nonExecutablesMax = 2, NonExecIdx = 0; 
    int i;
	char* NonExecCommands[nonExecutablesMax]; 

	NonExecCommands[0] = "q"; 
	NonExecCommands[1] = "cd"; 

	for (i = 0; i < nonExecutablesMax; i++) { 
		if (strcmp(parsed[0], NonExecCommands[i]) == 0) {  // Checking whether the input matches one of the commands in the list of non executable commands
			NonExecIdx = i + 1; 
			break; 
		} 
	} 

	switch (NonExecIdx) { 
	case 1: 
		printf("\nExit\n"); 
		exit(0); 
	case 2: 
		chdir(parsed[1]); 
		return 1;  
	default: 
		break; 
	} 
	return 0; 
} 


// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
	int i; 

	for (i = 0; i < 100; i++) {  //Setting max to 100 since max number of args to handle in our case is 100
		parsed[i] = strsep(&str, " "); //separating on a space delimiter basis

		if (parsed[i] == NULL) 
			break; 
		if (strlen(parsed[i]) == 0)  //Overwrite this item on the next iteration. This happens when there is space before a command.
			i--; 
	} 
} 


int main() 
{ 
	char userInp[1000], *parsedInp[100]; 


	while (1) { 
		
		// take input 
		if (scanUserInput(userInp)) {
			continue; 
        }
        
		//process input
        parseSpace(userInp, parsedInp); 

		//execute command + args
        if (nonExecutablesCMDs(parsedInp) == 0) 
            execArgs(parsedInp); 
	} 
	return 0; 
} 
