#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configure.c"
int countOfField = 0;
char countData[20];
void create(FILE *fpData, FILE *fpField)
{  
	fpField = fopen(FIELD_FILE_NAME, "r");
	char fieldData[countOfField * 20];
	fpData = fopen(DATA_FILE_NAME, "a");
	char datData[countOfField * 20];
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(fieldData, sizeof(fieldData), fpField) > 0)
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
void read(FILE *fpData,FILE *fpField)
{
	fpData = fopen(DATA_FILE_NAME, "r");
	char datData[countOfField * 20];
	fpField = fopen(FIELD_FILE_NAME, "r");
	char fieldData[countOfField * 20];
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fscanf(fpField, "%s", fieldData) > 0)
		{
			printf("%s ", fieldData);
		}
		printf("\n");
		while(fgets(datData, sizeof(datData), fpData) > 0)
		{
			
			puts(datData);
			
		}
		fclose(fpData);
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
		char menu[100];
	
		if(fpMenu == NULL)
		{
			printf("Error.");
			exit(0);
		}
		else
		{
			while(fgets(menu, sizeof(menu), fpMenu) > 0)
			{	
				printf("%s", menu);
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
	fpField = fopen("fields.cfg", "r");
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(countData, sizeof(countData), fpField) > 0)
		{
			countOfField = countOfField + 1;
		}
		fclose(fpField);
	}
	showMenu(fpData, fpField);
}