#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*
	Each element in a list is a person, with an attribute "name"
	And an emergency contact, who can be anyone else on the list
	(including themselves)

	"next" is standard linked list field, to connect each element to the next one
	(so we just need to keep a reference to the first element)
*/

struct list_node
{
	char *name;
	struct list_node *contact;
	struct list_node *next;	
};


/*
	This function creates an original linked list
	This list is just for testing purposes; you're encouraged to create new ones to try it out
*/
struct list_node *create_list()
{
	struct list_node *nodes[10];
	int i;

	//Allocates memory for all nodes
	for(i=0; i<10; i++)
	{
		nodes[i] = (struct list_node *)malloc(sizeof(struct list_node));
	}

	//links all the "next" fields
	for(i=0; i<9; i++)
	{
		nodes[i]->next = nodes[i+1];
	}
	nodes[9]->next = NULL;

	nodes[0]->name = (char *)malloc(strlen("John")+1);
	strcpy(nodes[0]->name,"John");
	nodes[0]->contact = nodes[1];

	nodes[1]->name = (char *)malloc(strlen("Mary")+1);
	strcpy(nodes[1]->name,"Mary");
	nodes[1]->contact = nodes[9];

	nodes[2]->name = (char *)malloc(strlen("Mohamed")+1);
	strcpy(nodes[2]->name,"Mohamed");
	nodes[2]->contact = nodes[0];

	nodes[3]->name = (char *)malloc(strlen("Liza")+1);
	strcpy(nodes[3]->name,"Liza");
	nodes[3]->contact = nodes[4];

	nodes[4]->name = (char *)malloc(strlen("Osenya")+1);
	strcpy(nodes[4]->name,"Osenya");
	nodes[4]->contact = nodes[4];

	nodes[5]->name = (char *)malloc(strlen("Peter")+1);
	strcpy(nodes[5]->name,"Peter");
	nodes[5]->contact = nodes[7];

	nodes[6]->name = (char *)malloc(strlen("Mahala")+1);
	strcpy(nodes[6]->name,"Mahala");
	nodes[6]->contact = nodes[2];

	nodes[7]->name = (char *)malloc(strlen("Rita")+1);
	strcpy(nodes[7]->name,"Rita");
	nodes[7]->contact = nodes[4];

	nodes[8]->name = (char *)malloc(strlen("Jacques")+1);
	strcpy(nodes[8]->name,"Jacques");
	nodes[8]->contact = nodes[8];

	nodes[9]->name = (char *)malloc(strlen("Paul")+1);
	strcpy(nodes[9]->name,"Paul");
	nodes[9]->contact = nodes[1];


	return nodes[0];
}

/*
	Prints the list and connections
	Carefully coded so you will have segmentation faults if your copy is not perfect
*/
void print_list(struct list_node *l)
{
	int i=0;
	while(l != NULL)
	{
		printf("Entry %d is %s, contact is %s\n",i,l->name,l->contact->name);
		i++;
		l = l->next;
	}
	printf("\n");
}


/*
	This is what you have to implement
	Remember this should work for any possible linked list implemented using the structure above,
	not just for the particular example given here
*/
struct list_node *copy_list(struct list_node *original)
{
	if (original == NULL) return NULL;

	// determine the length of the original list
    int len = 0;
    struct list_node *tmp_len;
    tmp_len = original;
    while (tmp_len != NULL)
    {
        len = len + 1;
        tmp_len = tmp_len->next;
    }

	// create an array to hold the copied nodes on the heap
    struct list_node **copy_node = malloc(len * sizeof(struct list_node *));

	// allocate memory for each copied node
	for(int i=0; i<len; i++)
	{
		copy_node[i] = (struct list_node *)malloc(sizeof(struct list_node));
	}

	// link the "next" fields of the copied nodes
	for(int i=0; i<len-1; i++)
	{
		copy_node[i]->next = copy_node[i+1];
	}

	// copy the data from the original list to the copied list
	struct list_node *tmp = original;

    for (int j = 0; j < len; j++)
    {
		// copy the name
        char *old_char = tmp->name;
		copy_node[j]->name = (char *)malloc(strlen(old_char)+1);
        strcpy(copy_node[j]->name, old_char);

		// find the index of the contact in the original list
        char *old_contact = tmp->contact->name;
        int contact_index = 0;
        struct list_node *contact_tmp;
        contact_tmp = original;
        char *cur_contact = contact_tmp->name;
        while (strcmp(cur_contact, old_contact) != 0)
        {
            contact_index++;
            contact_tmp = contact_tmp->next;
			cur_contact = contact_tmp->name;
        }

		// set the contact pointer in the copied node
        copy_node[j]->contact = copy_node[contact_index];
        tmp=tmp->next;
    }  

	copy_node[len-1]->next = NULL;

	struct list_node *result = copy_node[0];
	free(copy_node);
    return result;
}


/*
	Deletes a list
*/
struct list_node *delete_list(struct list_node *l)
{
	struct list_node *tmp;
	while(l != NULL)
	{
		tmp = l->next;

		free(l->name);
		l->name = NULL;
		l->contact = NULL;
		l->next = NULL;

		free(l);

		l=tmp; 
	}
	return NULL;
}

int main()
{
	struct list_node *original = NULL;
	struct list_node *copy = NULL;

	//create linked list
	original = create_list();

	//print linked list
	printf("Original:\n");
	print_list(original);

	//copy linked list
	copy = copy_list(original);

	//delete original linked list
	original = delete_list(original);

	//print copy
	printf("Copy:\n");
	//should print exactly the same thing as the original
	print_list(copy);
}