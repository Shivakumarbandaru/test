#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configure.c"
//#include "printAndUnderline.c"
int countOfFields = 0;
char header[150];
int printAndUnderline(int underline)
{
	int size = underline;
	printf("\n");
	for(int counter = 0; counter < size; counter++)
	{
		printf("-");
	}
	return 0;
}
void create(FILE *fpData, FILE *fpField)
{  
	fpField = fopen(FIELD_FILE_NAME, "r");
	char fieldData[countOfFields * LINE_LENGTH];
	fpData = fopen(DATA_FILE_NAME, "a");
	char datData[countOfFields * LINE_LENGTH];
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(fieldData, sizeof(fieldData), fpField) != NULL)
		{
			printf("Enter %s", fieldData);
			scanf("%s", datData);
			
			fprintf(fpData, "%s ", datData);
		}
		fprintf(fpData, "\n");
		fclose(fpData);
		fclose(fpField);
	}
}
void read(FILE *fpData, FILE *fpField)
{
	fpData = fopen(DATA_FILE_NAME, "r");
	char datData[countOfFields * LINE_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	char fieldData[countOfFields * LINE_LENGTH];
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		int size = 0;
		int underline = 0;
		printf("\n|");
		while(fscanf(fpField, "%s", fieldData) > 0)
		{
			size = printf("%s   |", fieldData);
			underline = underline + size;
		}
		printAndUnderline(underline);
		printf("\n");
		
		while(fgets(datData, sizeof(datData), fpData) > 0)
		{
			puts(datData);
			
		}
		fclose(fpData);
	}
}
void update(FILE *fpData, FILE *fpField)
{
	fpData = fopen(DATA_FILE_NAME, "rb+");
	char datData[countOfFields * LINE_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	char fieldData[countOfFields * LINE_LENGTH];
	int decision;
	char IdNumber[LINE_LENGTH];
	int IdFound = 0;
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fscanf(fpField, "%s", fieldData) > 0)
		{
			fflush(stdin);
			printf("Enter %s to update: ", fieldData);
			scanf("%s", &IdNumber);
			break;
		}
	}
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fscanf(fpData, "%s", datData) > 0)
		{
			if(strcmp(IdNumber, datData) == 0)
			{
				printf("Id number is matched");
				IdFound++;

				break;
			}
			fseek(fpData, 1L*(sizeof(datData) -20), 1);
			//int value = sizeof((count1fFields - 1) * LINE_LENGTH);
			//printf("%d", value);
			break;
			
		}
		fclose(fpData);
		if(IdFound == 0)
		{
			printf("not matched");
		}

	}
}
void exitProcess()
{
	printf("Thank you.");
	exit(0);
}
void showMenu(FILE *fpData, FILE *fpField)
{
	int userInput;
	while(1)
	{
		FILE *fpMenu;
		fpMenu = fopen("menu.cfg", "r");
		char menuLine[100];
	
		if(fpMenu == NULL)
		{
			printf("Error.");
			exit(0);
		}
		else
		{
			while(fgets(menuLine, sizeof(menuLine), fpMenu) > 0)
			{	
				printf("%s", menuLine);
			}
		}
		printf("\nEnter your choice: ");
		scanf("%d", &userInput);
		switch(userInput)
		{
			case 1:
				create(fpData, fpField);
				break;
			case 2:
				read(fpData,fpField);
				break;
			case 3:
				update(fpData,fpField);
				break;
			case 4:
				exitProcess();
				break;
			default:
				printf("Error! Please select correct option.\n");
				break;
		}
	}
}
FILE *fpField; 
FILE *fpData;
void main()
{
	char fieldData[20];
	fpField = fopen("fields.cfg", "r");
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(fieldData, sizeof(fieldData), fpField) > 0)
		{
			countOfFields = countOfFields + 1;
		}
		fclose(fpField);
	}
	showMenu(fpData, fpField);
}