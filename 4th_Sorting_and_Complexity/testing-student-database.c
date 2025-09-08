#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include <time.h> 

/*
	Student ID is an up to 8-digit number, where each digit is either 1, 2 or 3
		(e.g., "1", "2", "3", "123", "222" and "21112332" are all valid student IDs)
*/


struct data_tree {
    int id;
    float gpa;
    struct data_tree *one;
	struct data_tree *two;
	struct data_tree *three;
};

struct sorted_node {
	struct data_tree *data;
    struct sorted_node *next;
};

struct data_tree *student_tree = NULL;
struct sorted_node *id_ll = NULL;
struct sorted_node *gpa_ll = NULL;

int id_exists(int id);
int random_id();
void populate_random(int count);

// Validate that an ID contains only digits 1,2,3 (and at least one digit)
int is_valid_id(int id) {
	if (id <= 0) return 0;
	while (id > 0) {
		int d = id % 10;
		if (d < 1 || d > 3) return 0;
		id /= 10;
	}
	return 1;
}


void add_to_tree(struct data_tree *p, struct data_tree *root ,int depth, int lenght, int id)
{
	char sid[9];
	snprintf(sid, sizeof(sid), "%d", id);

	if (depth == 1) {
		switch (sid[lenght-1])
		{
			case '1':
				root->one = p;
				break;
			
			case '2':
				root->two = p;
				break;

			case '3':
				root->three = p;
				break;
		}
		return;
	}
	int i = lenght-depth;
	depth--;
	switch (sid[i])
	{
		case '1':
			if (root->one == NULL) {
				struct data_tree *temp = malloc(sizeof(struct data_tree));
				temp->id = -1; // placeholder
				temp->gpa = -1.0f;
				temp->one = temp->two = temp->three = NULL;
				root->one = temp;
				add_to_tree(p, temp, depth, lenght, id);
			} else {
				add_to_tree(p, root->one, depth, lenght, id);
			}
			break;
		
		case '2':
			if (root->two == NULL) {
				struct data_tree *temp = malloc(sizeof(struct data_tree));
				temp->id = -1; // placeholder
				temp->gpa = -1.0f;
				temp->one = temp->two = temp->three = NULL;
				root->two = temp;
				add_to_tree(p, temp, depth, lenght, id);
			} else {
				add_to_tree(p, root->two, depth, lenght, id);
			}
			break;

		case '3':
			if (root->three == NULL) {
				struct data_tree *temp = malloc(sizeof(struct data_tree));
				temp->id = -1; // placeholder
				temp->gpa = -1.0f;
				temp->one = temp->two = temp->three = NULL;
				root->three = temp;
				add_to_tree(p, temp, depth, lenght, id);
			} else {
				add_to_tree(p, root->three, depth, lenght, id);
			}
			break;
	}
}

void add_to_database( int id, float gpa) 
{
	if (!is_valid_id(id)) {
		printf("Error: ID must contain only digits 1,2,3. Entry skipped.\n");
		return;
	}
	struct data_tree *p = (struct data_tree*)malloc(sizeof(struct data_tree));
	p->id = id;
	p->gpa = gpa;
	p->one = p->two = p->three = NULL;


	// store in tree
	char sid[9];
	snprintf(sid, sizeof(sid), "%d", id);
	int len = strlen(sid);
	add_to_tree(p, student_tree, len, len, id);

	
	// store in sorted_id_node
	struct sorted_node *temp = (struct sorted_node*)malloc(sizeof(struct sorted_node));
	temp->data = p;
	temp->next = NULL;
	struct sorted_node *c = id_ll;
	if (id_ll==NULL) {
		id_ll = temp;

		// printf("added id in case empty\n");
	} 
	else if (id_ll->next==NULL)
	{
		if (id_ll->data->id < p->id) {
			id_ll->next = temp;
			// printf("id greater than head\n");
		} 
		else {
			temp->next = id_ll;
			id_ll->next = NULL;
			id_ll = temp;
			// printf("id less than head\n");

		}
		// printf("added id in case len<2\n");
	} 
	else 
	{
		// printf("added id in case len>2\n");
		if ((p->id)<(c->data->id)) {
			temp->next = id_ll;
			id_ll = temp;
			// printf("added to head\n");
		} 
		else {
			while ((c->next != NULL) && (p->id) > (c->next->data->id)) {
				c = c->next;
			}
		}
		if (c->next == NULL) {
			c->next = temp;
			temp->next = NULL;
		}
		else {
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

		// printf("added gpa in case empty\n");
	} 
	else if (gpa_ll->next==NULL)
	{
		if (gpa_ll->data->gpa < p->gpa) {
			gpa_ll->next = temp;
			// printf("gpa greater than head\n");
		} else {
			temp->next = gpa_ll;
			gpa_ll->next = NULL;
			gpa_ll = temp;
			// printf("gpa less than head\n");

		}
		// printf("added gpa in case len<2\n");
	} 
	else 
	{
		// printf("added gpa in case len>2\n");
		if ((p->gpa)<(c->data->gpa)) {
			temp->next = gpa_ll;
			gpa_ll = temp;
			// printf("added to head\n");
		} 
		else {
			while ((c->next != NULL) && (p->gpa) > (c->next->data->gpa) ) {
				c = c->next;
			}
		}
		// printf("found pos\n");
		if (c->next == NULL) {
			// printf("add to tail\n");
			c->next = temp;
			temp->next = NULL;
		}else {
			temp->next = c->next;
			c->next = temp;
		}
	}
}

// NEW: check if an ID already exists (linear scan of id_ll)
int id_exists(int id) {
    struct sorted_node *c = id_ll;
    while (c) {
        if (c->data->id == id) return 1;
        c = c->next;
    }
    return 0;
}

// NEW: generate a random ID length 1..8, digits only 1..3
int random_id() {
    int len = (rand() % 8) + 1;
    int id = 0;
    for (int i = 0; i < len; i++) {
        id = id * 10 + (rand() % 3 + 1); // digit 1..3
    }
    return id;
}

// NEW: populate database with 'count' random unique IDs
void populate_random(int count) {
    int added = 0;
    while (added < count) {
        int id = random_id();
        if (id_exists(id)) continue; // avoid overwriting existing IDs
        float gpa = ((float)rand() / (float)RAND_MAX) * 4.0f;
        add_to_database(id, gpa);
        added++;
    }
    printf("Added %d random entries.\n", added);
}



void add_new_entry()
{
	int id;
	float gpa;

	printf("New student ID:\n");
	while (1) {
		if (scanf("%d", &id) != 1) {
			printf("Invalid input. Try again: ");
			while (getchar() != '\n');
			continue;
		}
		if (!is_valid_id(id)) {
			printf("ID must use only digits 1,2,3. Try again: ");
			while (getchar() != '\n');
			continue;
		}
		break;
	}

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

void top_5_percent() 
{
	struct sorted_node *temp;
	int count = 0;
	temp = gpa_ll;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}

	int n = (int)(0.05 * count + 0.5); 
	if (n < 1) n = 1;  
	int pos = count-n;
	temp = gpa_ll;

	for (int i = 0; i < count; i++)	
	{
		if (i >= pos) 
		{
			printf("id: %d ,gpa: %f\n", temp->data->id, temp->data->gpa);
		}
		temp = temp->next;
	}
}

void print_all_element_in_root (struct data_tree*root) {
	if (root == NULL) {
		return;
	}
	if (root->id != -1) {
		printf("id: %d ,gpa: %f\n", root->id, root->gpa);
	}
	print_all_element_in_root(root->one);
	print_all_element_in_root(root->two);
	print_all_element_in_root(root->three);
}


int search_tree(struct data_tree* root, char num) {
    if (root == NULL) {
        printf("No IDs match this prefix. Search terminated.\n");
        return 0;
    }
	switch (num) {
		case '1': root = root->one; break;
		case '2': root = root->two; break;
		case '3': root = root->three; break;
		default: printf("Invalid input"); break;
	}
    if (root == NULL) {
        printf("No IDs match this prefix. Search terminated.\n");
        return 0;
    }
    print_all_element_in_root(root);
	return 1;
}

void search_by_number() 
{	
	char Num[9];
	struct data_tree *temp = student_tree;
	for (int i = 1; i < 9; i++) {
		printf("Enter id: ");
		fgets(Num, 9, stdin);
		if (!search_tree(temp, Num[0])) {
            break; // no matches for this prefix
        }
		switch (Num[0])
		{
			case '1':temp = temp->one; break;
			case '2':temp = temp->two; break;
			case '3':temp = temp->three; break;
			default:
				printf("Invalid input\n");
				temp = temp;
				break;
		}
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
        5: Search by student number\n\
        6: Populate 200 random entries\n");

    fgets(c,80,stdin);
    if(strlen(c) != 2)
    {
        printf("Invalid entry \"%s\".\n",c);
        return;
    }

    // ...existing switch...
    switch(c[0])
    {
        case '1':
            add_new_entry();
            break;
        case '2':
            show_by_ID();
            break;
        case '3':
            show_by_GPA();
            break;
        case '4':
            top_5_percent();
            break;
        case '5':
            search_by_number();
            break;
        case '6':
            populate_random(200);
            break;
        default:
            printf("Invalid entry \"%c\".\n",c[0]);
    }
    return;
}

int main() {

	// initialize the student tree
    student_tree = (struct data_tree*)malloc(sizeof(struct data_tree));
	student_tree->id = -1;     // sentinel marker (not a real student id)
	student_tree->gpa = -1.0f;
	student_tree->one = student_tree->two = student_tree->three = NULL;

    // NEW: seed RNG
    srand((unsigned)time(NULL));

    while (1) {
        menu();
    }
    return 0;
}