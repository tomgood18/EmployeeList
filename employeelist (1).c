/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Thomas Good
 * Student ID: 13291455
 * Date of submission: - 13/04/2021
 * A brief statement on what you could achieve (less than 50 words):
 * 
 *	I achieved 14/14 passed test cases.
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 *	I could not seem to create 'get' functions for each of the employee 
 *	attributes without resulting in a buffer overflow in the last test case.
 *	I also found that I wasn't able to eliminate the use of global variables
 *	without other issues arising that i wasn't able to fix.
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/

#define MAX_COMPANY_SIZE 5
#define MAX_NAME_SIZE 11

/*******************************************************************************
 * List structs - you may define struct date_time and struct employee only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
/*  */

/* Date Struct declared first to use in Employee Struct */
struct date {
	int day;
	int month;
	int year; 
};
typedef struct date date_t;

/* Employee Struct */
struct employee { 
	char name[MAX_NAME_SIZE];
	float fte;
	date_t birthday;
};
typedef struct employee employee_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void printMenu(void);
int readAnswer(void);
void addEmployee(void);
void removeLastEmployee(void);
void displayEmployeeList(void);
void saveEmployee(char filename[25]);
int readEmployees(char filename[25]);
void invalidChoice(void);
char input(void);

/*******************************************************************************
 * Global Variables
*******************************************************************************/
employee_t employeelist [MAX_COMPANY_SIZE];
int employee_count = 0;

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void){	
	printMenu();
	readAnswer();
    return 0;
}

/*******************************************************************************
 * This function reads the users input and executes the appropriate function
 * inputs:
 * - none
 * outputs:
 * - int
*******************************************************************************/
int readAnswer(void){
	char dbFileName[] = "database";
	char answer;
 	answer = getchar();
	if (answer == '\n') {
		invalidChoice();
	} else {
		getchar();	/* Collects the '\n' character after entering answer */
		if (answer == '-') {
			getchar();
			getchar();
			invalidChoice();
		}
		else if (answer == '1') {
			/* If MAX_COMPANY_SIZE hasn't been reached yet, add employee */
			if (employee_count < MAX_COMPANY_SIZE) {
				addEmployee();
			} else {
				/* Otherwise don't add employee */
				printf("Maximum number of employees reached.\n");	
				printMenu();
				readAnswer();
			}
		} else if (answer == '2') {
			removeLastEmployee();
		} else if (answer == '3') {
			displayEmployeeList();
		} else if (answer == '4') {
			saveEmployee(dbFileName);
		} else if (answer == '5') {
			readEmployees(dbFileName);
			printMenu();
			readAnswer();
		} else if (answer == '6') {
			return 0;	/* exit program */
		} else {
			invalidChoice();
		}
	}
	return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printMenu(void){
    printf("\n\n"
    	"1. add employee\n"
    	"2. delete last employee\n"
    	"3. display employee list\n"
    	"4. save the employee list to the database\n"
    	"5. read the employee list from the database\n"
    	"6. exit the program\n"
		"Enter your choice>");
}

/*******************************************************************************
 * This function adds a new employee to the employeelist through the terminal.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void addEmployee(void){
	int val;
	char tempDay[20];
	char tempMonth[20];
	char tempYear[20];
	float tempFte;
	int check = 0;
	employee_t employee;
	date_t birthday;
    printf("Enter name>");
	/* Collects up to 100 characters for name */
	scanf("%100[^\n]", employee.name);
	/* Until given day is valid, ask for birthday day */
	while(check == 0) {
		printf("Enter birthday: day>");
		scanf("%s", &tempDay[0]);
		/* Checks if given value is int */
		val = atoi(tempDay);
		if (val == 0) {
			printf("Invalid day. ");
		} else {
			if (val >= 1 && val <= 31) {
				birthday.day = val;
				check = 1; 
			} else printf("Invalid day. "); 
		}
	}
	/* Resets check */
	check = 0;
	/* Until given month is valid, ask for birthday month */
	while(check == 0) {
		printf("Enter birthday: month>");
		scanf("%s", &tempMonth[0]);
		/* Checks if given value is int */
		val = atoi(tempMonth);
		if (val == 0) {
			printf("Invalid month. ");
		} else {
			if (val >= 1 && val <= 12) {
				birthday.month = val;
				check = 1; 
			} else printf("Invalid month. "); 
		}
	}
	/* Resets check */
	check = 0;
	/* Until given year is valid, ask for birthday year */
	while(check == 0) {
		printf("Enter birthday: year>");
		scanf("%s", &tempYear[0]);
		/* Checks if given value is int */
		val = atoi(tempYear);
		if (val == 0) {
			printf("Invalid year. ");
		} else {
			if (val >= 1800 && val <= 2017) {
				birthday.year = val;
				check = 1; 
			} else printf("Invalid year. "); 
		}
	}
	/* Resets check */
	check = 0;
	/* Until given FTE is valid, ask for FTE */
	while(check == 0) {
		printf("Enter FTE>");
		scanf("%f", &tempFte);
		if (tempFte >= 0.0 && tempFte <= 1.0) {
			employee.fte = tempFte;
			check = 1;
		} else printf("Invalid FTE. ");
	}
	check = 0;
	getchar();	/* Collect trailing '\n' */
	employee.birthday = birthday;
	employeelist[employee_count] = employee;
	employee_count++;
	printMenu();
	readAnswer();
}

/*******************************************************************************
 * This function removes the last employee added to the employeelist.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void removeLastEmployee(void){
	employee_t temp [MAX_COMPANY_SIZE];	
	/* Appends each element of the current employeelist into a temp list
	   but omits the last employee that was added to the employeelist */
	if (employee_count > 0) {
		int i;
		for(i=0;i<employee_count-1;i++){
			temp[i] = employeelist[i];
		}
		*employeelist = *temp;
		employee_count--;
	} else {
		printf("No employee.\n");
	}
	printMenu();
	readAnswer();
}

/*******************************************************************************
 * This function displays the employeelist.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void displayEmployeeList(void){
	if (employee_count < 1) {
		printf("No employee.\n");
	} else {
		printf("Name       Birthday   FTE\n"
		"---------- ---------- ------\n");
		int i;
		for (i=0;i<employee_count;i++) {
			char tempName[MAX_NAME_SIZE];
			int f;
			for (f=0; f<MAX_NAME_SIZE; f++) {
				tempName[f] = employeelist[i].name[f];
			}
			/* '%-10.10s' prints the employees name at a maximum and minimum 
			   of 10 characters, adding whitespace if under 10 and cutting 
			   the name short if over 10 */
			printf("%-10.10s %.2d-%.2d-%d %.4f\n",
			tempName, 
			employeelist[i].birthday.day, 
			employeelist[i].birthday.month, 
			employeelist[i].birthday.year, 
			employeelist[i].fte);
		}
	}
	printMenu();
	readAnswer();
}

/*******************************************************************************
 * This function saves the employeelist in the hard disk as a binary/text 
 * file named database.
 * inputs:
 * - char dbFileName[]
 * outputs:
 * - none
*******************************************************************************/
void saveEmployee(char dbFileName[]){
	/* Open the database file with write capabilities */
	FILE *fp = fopen(dbFileName, "w");
	if (employee_count < 1) {
		printf("No employee.\n");
	} else {
		int i;
		for (i=0;i<employee_count;i++) {
			/* Writes the employee to the database file in the correct format */
			fprintf(fp, "%-10s %d %d %d %f\n", 
			employeelist[i].name, 
			employeelist[i].birthday.day, 
			employeelist[i].birthday.month, 
			employeelist[i].birthday.year, 
			employeelist[i].fte);
		}
	}
	fclose (fp);
	printMenu();
	readAnswer();
}

/*******************************************************************************
 * This function reads the database file and put the data into employeelist
 * inputs:
 * - char dbFileName[]
 * outputs:
 * - int
*******************************************************************************/
int readEmployees(char dbFileName[]){
	FILE* fp = NULL;
	/* Open the database file with read capabilities */
    fp = fopen(dbFileName, "r");
	if(fp == NULL) {
        printf("Read error\n");
		return 0;
    } else {
		employee_count = 0;
		/* While it is not the end of the file, append the employee to 
		   the employeelist and increment employee_count by 1 */
		while (!feof(fp) && (employee_count <= MAX_COMPANY_SIZE)) {
			fscanf(fp, "%s %d %d %d %f", 
			&employeelist[employee_count].name[0], 
			&employeelist[employee_count].birthday.day, 
			&employeelist[employee_count].birthday.month, 
			&employeelist[employee_count].birthday.year, 
			&employeelist[employee_count].fte);
			employee_count++;
		}
		employee_count--;
	}
    fclose(fp);
	return 0;
}

/*******************************************************************************
 * This function resets the menu if the user chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void invalidChoice(void) {
	printf("Invalid choice.\n");
	printMenu();
	readAnswer();
}
