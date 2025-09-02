#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
	Student ID is an up to 8-digit number, where each digit is either 1, 2 or 3
		(e.g., "1", "2", "3", "123", "222" and "21112332" are all valid student IDs)
*/


struct ll_node {
    int id;
    float gpa;
    struct ll_node *next;
};

struct sorted_node {
	struct ll_node *data;
    struct sorted_node *next;
};

struct ll_node *student_ll = NULL;
struct sorted_node *id_ll = NULL;
struct sorted_node *gpa_ll = NULL;


void add_to_database( int id, float gpa) {

	// store in student_ll
    struct ll_node *p = (struct ll_node*)malloc(sizeof(struct ll_node));
	p->id = id;
	p->gpa = gpa;
	p->next = student_ll;
	student_ll = p;

	// store in sorted_id_node
	struct sorted_node *temp = (struct sorted_node*)malloc(sizeof(struct sorted_node));
	temp->data = p;
	temp->next = NULL;
	struct sorted_node *c = id_ll;
	if (id_ll==NULL) {
		id_ll = temp;

		printf("added id in case empty\n");
	} else if (id_ll->next==NULL)
	{
		if (id_ll->data->id > p->id) {
			id_ll->next = temp;
			printf("id greater than head\n");
		} else {
			temp->next = id_ll;
			id_ll->next = NULL;
			id_ll = temp;
			printf("id less than head\n");

		}
		printf("added id in case len<2\n");
	} else {
		printf("added id in case len>2\n");
		while ((p->id) > (c->next->data->id) && (c->next != NULL)) {
			c = c->next;
		}
		if (c->next == NULL) {
			c->next = temp;
			temp->next = NULL;
		}else {
			temp->next = c->next;
			c->next = temp;
		}
	}

	// store in sorted gpa_ll
	temp = (struct sorted_node*)malloc(sizeof(struct sorted_node));
	temp->data = p;
	temp->next = NULL;
	c = gpa_ll;
	if (gpa_ll==NULL) {
		gpa_ll = temp;
		printf("added gpa in case empty\n");
	} else if (gpa_ll->next==NULL)
	{
		if ((gpa_ll->data->gpa) > (p->gpa)) {
			gpa_ll->next = temp;
			printf("added gpa in case greater than head\n");
		} else {
			temp->next = gpa_ll;
			gpa_ll->next = NULL;
			gpa_ll = temp;
			printf("added gpa in case less than head\n");
		}
		printf("added gpa in case len<2\n");
	} else {
		printf("added gpa in case len>2\n");
		while ((p->gpa) > (c->next->data->gpa) && (c->next != NULL)) {
			c = c->next;
		}
		if (c->next == NULL) {
			c->next = temp;
			temp->next = NULL;
		}else {
			temp->next = c->next;
			c->next = temp;
		}
	}
}


void add_new_entry()
{
	int id;
	float gpa;

	printf("New student ID:\n");
	scanf("%d",&id);

	printf("New student GPA:\n");
	scanf("%f",&gpa);

	while(getchar() != '\n');

	//add to our database here
	add_to_database(id, gpa);
}

void show_by_ID() 
{	
	struct sorted_node *temp;
	temp = id_ll;
	while (temp != NULL) {
		printf("id: %d ,gpa: %f\n", temp->data->id, temp->data->gpa);
		temp = temp->next;
	}
}

void show_by_GPA() 
{	
	struct sorted_node *temp;
	temp = gpa_ll;
	while (temp != NULL) {
		printf("id: %d ,gpa: %f\n", temp->data->id, temp->data->gpa);
		temp = temp->next;
	}
}


void menu()
{
	char c[80];

	printf("Options: \n\
		1: Add new entry\n\
		2: Show all students by ID\n\
		3: Show all students by GPA\n\
		4: Show top 5%% of students by GPA\n\
		5: Search by student number\n");

	fgets(c,80,stdin);
	if(strlen(c) != 2)
	{
		printf("Invalid entry \"%s\".\n",c);
		return;
	}

	/*
		First: Get options 1, 2 and 3 working (ignore the rest)
		Second: get option 4 working
		Finally: get option 5 working
	*/


	switch(c[0])
	{
		case '1': 
			//Adds a new student to the database
			add_new_entry(); 
			break;
		case '2': 
			//Shows the list of all students, sorted by ID number
			show_by_ID(); 
			break;
		case '3': 
			//Shows the list of all students, sorted by GPA
			show_by_GPA();
			break;
		// case '4': 
		// 	//Shows 5% of studentd with highest GPA
		// 	top_5_percent();
		// 	break;
		// case '5': 
		// 	/*
		// 		Should receive 8 inputs from the user. 
		// 		Every time the user inputs a number, should print all students whose IDs match the number thus far

		// 		E.g.: if the database contains the students "122", "123", "131", and "222"

		// 			After user inputs "1", should print:
		// 				122
		// 				123
		// 				131

		// 			After user inputs "2", should print

		// 				122
		// 				123

		// 			And so on
		// 	*/
		// 	search_by_number();
		// 	break;
		default: 
			printf("Invalid entry \"%c\".\n",c[0]);
	}

	return;
}



int main()
{
	while(1)
	{
		menu();
	}
	return 0;
}