#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <windows.h>


int hash(char *string, int length)
{
    int i, hash = 0;
    for(i=0; i < length; i++)
    {
        hash += (int)*(string + i);
    }
    return hash % 256;
}

struct ll_node
{
	char *key;
	int value;
	struct ll_node *next;
};

struct ll_node *hashtable[256];
struct ll_node *llist;




void add_to_hashtable(char *key_string, int value)
{
	int index = hash(key_string, strlen(key_string));

	struct ll_node *new_entry = (struct ll_node *)malloc(sizeof(struct ll_node));
	
	new_entry->key = (char *)malloc(strlen(key_string)+1);
	strcpy(new_entry->key, key_string);

	new_entry->value = value;

	new_entry->next = hashtable[index];

	hashtable[index] = new_entry;
}

struct ll_node *find_in_hashtable(char *key_string)
{
	int index = hash(key_string, strlen(key_string));

	struct ll_node *entry = hashtable[index];

	while(entry != NULL)
	{
		if(strcmp(entry->key,key_string)==0)
			return entry;
		entry=entry->next;
	}
	return NULL;
}



void add_to_llist(char *string, int value)
{
	struct ll_node *new_entry = (struct ll_node *)malloc(sizeof(struct ll_node));
	
	new_entry->key = (char *)malloc(strlen(string)+1);
	strcpy(new_entry->key, string);

	new_entry->value = value;

	new_entry->next = llist;
	llist=new_entry;
}

struct ll_node *find_in_llist(char *string)
{
	struct ll_node *entry = llist;

	while(entry != NULL)
	{
		if(strcmp(entry->key,string)==0)
			return entry;
		entry=entry->next;
	}
	return NULL;
}




void populate_hashtable_llist()
{
	static int x = 0;
	char to_str[5];

	sprintf(to_str,"%d",x);
	x++;

	add_to_hashtable(to_str,x);
	add_to_llist(to_str,x);
}






int main()
{
	int i;


	struct timespec start, stop;

	//initialize hashtable
	for(i = 0; i< 256; i++)
	{
		hashtable[i] = NULL;
	}

	//initialize linked list
	llist = NULL;

	for(i=0; i < 100000; i++)
	{
		populate_hashtable_llist();

		clock_t start = clock();
		find_in_hashtable("1024");
		clock_t stop = clock();

		printf("Hashtable: %03ld\t", stop - start);

		clock_t start_llist = clock();
		find_in_llist("1024");
		clock_t stop_llist = clock();

		printf("LList: %03ld\n", stop_llist - start_llist);
	}

	return 0;
}

// void print_current_time_with_ms (void)
// {
//     long            ms; // Milliseconds
//     time_t          s;  // Seconds
//     struct timespec spec;

//     clock_gettime(CLOCK_REALTIME, &spec);

//     s  = spec.tv_sec;
//     ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
//     if (ms > 999) {
//         s++;
//         ms = 0;
//     }

//     printf("Current time: %"PRIdMAX".%03ld seconds since the Epoch\n",
//            (intmax_t)s, ms);
// }