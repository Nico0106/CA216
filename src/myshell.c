/*
myshell.c
Author: Nicolas Oyeleye
*/

// includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdint.h>
#include "myshell.h"
#include <sys/types.h>
#include <unistd.h>

/* Function Prototypes */
char *read_command(void);

/*
Function: main
@params: argc count of command line arguments argv list of command line arguments
returns: int
*/
int main(int argc, char **argv){
    char *command;

    do
    {
        firstPrompt();
        command = read_command();

        // declaring variables
        int flag = 0;
        int arraySize = 0;
        char *array[1024];
        char *token = strtok(command, " ");
        int i = 0;
        // manually getting array size
        while (token != NULL){
          arraySize += 1;
          array[i] = token;
          i++;
          token = strtok(NULL, " ");
        }
        //array for arguments passed
        char *realArray [arraySize];

        for (i = 0; i < arraySize; i++){
          realArray[i] = array[i];
        }
        // parsed the command to get the option that could be provided
        char *function = realArray[0], *option = realArray[1];

        // if there is a problem with the command exit
        if(!command){
          flag = 1;
          exit(EXIT_SUCCESS);
        }
        // if command is a null byte or a newline
        if(command[0] == '\0' || strcmp(command, "\n") == 0){
          free(command);
          flag = 1;
          continue;
        }

        /* dir for listing contents of directory
        -l for file info
        -a for hidden files
        -s for sorting by size*/
        if(strcmp(function, "dir") == 0){
          flag = 1;
          DIR *thisDirectory;
          struct dirent *dir;
          thisDirectory = opendir(".");
          if (thisDirectory){
            if (strcmp(option, "-a\n") == 0){
              system("ls -a");
            }
            else if (strcmp(option, "-l\n") == 0){
              system("ls -l");
            }
            else if (strcmp(option, "-s\n") == 0){
              system("ls -S");
            }
            else if (strcmp(option, "-a\n") != 0 && strcmp(option, "-l\n") != 0){
              char *option1 = strtok(option, "\n");
              printf("Error: Option %s not found!\n", option1);
            }
            closedir(thisDirectory);
          }
        }
        //if no option is provided
        else if(strcmp(command, "dir\n") == 0){
          flag = 1;
          system("ls");
        }

        //environ lists the environment variables
        if (strcmp(command, "environ\n") == 0){
          flag = 1;
          system("printenv");
        }
        // nano is the main editor for this shell
        if (strcmp(function, "nano") == 0){
          flag = 1;
          char joiner[100];
          char *breaking = strtok(option, "\n");
          strcpy(joiner, "nano ");
          strcat(joiner, breaking);
          system(joiner);
        }
        else if(strcmp(function, "nano\n") == 0){
          system("nano");
        }

        //help displays the user manual
        if(strcmp(function, "help") == 0){
          flag = 1;
          if(strcmp(option, "clr\n") == 0){
            system("sed -n -e 1,16p ../manual/readme");
          }
          else if(strcmp(option, "pwd\n") == 0){
            system("sed -n -e 18,33p readme");
          }
          else if(strcmp(option, "cd\n") == 0){
            system("sed -n -e 35,55p ../manual/readme");
          }
          else if(strcmp(option, "dir\n") == 0){
            system("sed -n -e 57,76p ../manual/readme");
          }
          else if(strcmp(option, "echo\n") == 0){
            system("sed -n -e 78,93p ../manual/readme");
          }
          else if(strcmp(option, "help\n") == 0){
            system("sed -n -e 95,113p ../manual/readme");
          }
          else if(strcmp(option, "pause\n") == 0){
            system("sed -n -e 115,130p ../manual/readme");
          }
          else if(strcmp(option, "quit\n") == 0){
            system("sed -n -e 132,147p ../manual/readme");
          }
          else if(strcmp(option, "nano\n") == 0){
            system("sed -n -e 149,164p ../manual/readme");
          }
          else if(strcmp(option, "environ\n") == 0){
            system("sed -n -e 166,181p ../manual/readme");
          }
          else if(strcmp(option, "mv\n") == 0){
          	system("sed -n -e 183,203p ../manual/readme");
          }
          else if(strcmp(option, "rm\n") == 0){
          	system("sed -n -e 205,223p ../manual/readme");
          }
          else if(strcmp(option, "mkdir\n") == 0){
          	system("sed -n -e 225,240p ../manual/readme");
          }
          else if(strcmp(option, "cat\n") == 0){
         	system("sed -n -e 242,257p ../manual/readme");
          }
          else if(strcmp(option, "bash\n") == 0){
          	system("sed -n -e 259,277p ../manual/readme");
          }
          else if(strcmp(option, "zsh\n") == 0){
         	system("sed -n -e 279,295p ../manual/readme");
          }
          else{
            printf("No manual entry for %s", option);
          }
        }

        //pause pauses the shell opertaion until enter is pressed
        if (strcmp(command, "pause\n") == 0){
          flag = 1;
          printf("Press <Enter> to continue the program!");
          getchar();
        }

        //echo prints whatever is passed to it to standard output
        if (strcmp(function, "echo") == 0){
          flag = 1;
          for (i = 1; i <= arraySize; i++){
            if (i == arraySize){
              printf("\n");
            }
            else{
              printf("%s ", realArray[i]);
            }
          }
        }

        // bash or zsh are unix command interpreters
        if (strcmp(command, "bash\n") == 0 || strcmp(command, "zsh\n")== 0){
	        flag = 1;
	        printf("Switching to %s\n", function);
	        system("sleep 1.5");
	        system(command);
	    }
		// cp ______________________________________________________________________________________
		//__________________________________________________________________________________________
	    if(strcmp(function, "cp") == 0){
	    	flag = 1;
	    	char cp[100];
	    	strcpy(cp, "cp ");
	    	strcat(cp, option);
	    	strcat(cp, " ");
	    	strcat(cp, realArray[2]);
	    	system(cp); 
	    }

        // mv moves the first argument to the specified directory
		if (strcmp(function, "mv") == 0){
        	flag = 1;
         	char move[100];
         	strcpy(move, "mv ");
        	strcat(move, option);
        	strcat(move, " ");
        	strcat(move, realArray[2]);
       		system(move);
        	printf("%s has been moved to %s\n", option, realArray[2]);
		}

		//rm removes the file directory specified 
		if (strcmp(function, "rm") == 0){
			flag = 1;
			int yes = 0;
			char remove[100];
			strcpy(remove, "rm ");
			strcat(remove, option);
			strcat(remove, " ");
			if (strcmp(option, "-f") == 0 || strcmp(option, "-r") == 0 || strcmp(option, "-fr") == 0){
				strcat(remove, realArray[2]);
				system(remove);
				char *option4 = strtok(realArray[2], "\n");
				printf("%s has been removed\n", option4);;
				yes = 1;
				}
			if (yes == 0){
				system(remove);
			}
		}

		//mkdir creates a new directory
		if (strcmp(function, "mkdir") == 0){
			flag = 1;
			char mkdir[100];
			strcpy(mkdir, "mkdir ");
			strcat(mkdir, option);
			system(mkdir);
			printf("%s directory has been created\n", strtok(option, "\n"));
		}

		// cat outpus the contents of a file to standard output
		if (strcmp(function, "cat") == 0){
			flag = 1;
			char cat[100];
			strcpy(cat, "cat ");
			strcat(cat, option);
			system(cat);
		}

		 // pwd prints working directory
        if (strcmp(function, "pwd\n") == 0){
          flag = 1;
          system("pwd");
        }

        // changes directory to provided directory
        if (strcmp(function, "cd") == 0){
          flag = 1;
          char dirNames[1000];
          char *option2 = strtok(option, "\n");
          int changeDir = chdir(option2);
          system("pwd");
        }
        // if no arguments are provided after cd
        else if (strcmp(command, "cd\n") == 0){
          flag = 1;
          system("pwd");
        }
        /*else{
          flag = 1;
          printf("Error: No such file or directory!\n");
        }*/

        //Clear the Screen
        if (strcmp(command, "clr\n") == 0){
          flag = 1;
          printf("Press <Enter> to clear the screen!");
          getchar();
          system("clear"); // clear in linux
        }
        //if option is provided after clr
        else if(strcmp(function, "clr") == 0){
          flag = 1;
          char *option3 = strtok(option, "\n");
          printf("Error: Option %s not found!\n", option3);
        }

        //quit quits the shell operation
        if(strcmp(command, "quit\n") == 0){
          flag = 1;
          free(command);
          exit(EXIT_SUCCESS);
        }

        //if none of the commands are used, print error message
        else{
          if (flag == 0){
            char *function1 = strtok(command, "\n");
            printf("Error: Command '%s' not found\n", function1);
          }
        }

        free(command);

    } while(1);

    exit(EXIT_SUCCESS);
}

/*
Function: read_command
@params: void
returns: char
description: This function reads the command given by the user.
*/
char *read_command(void){
  char buffer[1024];
  char *pointer = NULL;
  char lenPointer = 0;

  while(fgets(buffer, 1024, stdin)){
    int lenBuffer = strlen(buffer);

    if(!pointer){
      pointer = malloc(lenBuffer + 1);
    }
    else{
      char *pointer2 = realloc(pointer, lenPointer + lenBuffer + 1);

      if(pointer2){
        pointer = pointer2;
      }
      else{
        free(pointer);
        pointer = NULL;
      }
    }

    if(!pointer){
      fprintf(stderr, "Error: failed to alloc buffer: %s\n", strerror(errno));
      return NULL;
    }

    strcpy(pointer + lenPointer, buffer);

    if(buffer[lenBuffer - 1] == '\n'){
      if(lenBuffer == 1 || buffer[lenBuffer - 2] != '\\'){
        return pointer;
      }

      pointer[lenPointer + lenBuffer - 2] = '\0';
      lenBuffer = lenBuffer - 2;
      secondPrompt();
    }

    lenPointer += lenBuffer;
  }

  return pointer;
}
