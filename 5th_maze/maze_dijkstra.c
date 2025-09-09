#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>

#define SIDE 22

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */


unsigned char map[SIDE][SIDE] = 
	{
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1','X', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
		{'1','1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '0', '1'},
		{'1','1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '0', '1', '0', '1'},
		{'1','1', '1', '1', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '1', '0', '1'},
		{'1','1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1', '1', '1', '0', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
		{'1','1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '0', '1', '0', '1', '0', '1', '0', '1'},
		{'1','0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '0', '1'},
		{'1','0', '1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '0', '1', '0', '0', '0', '1'},
		{'1','0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
		{'1','0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '0', '1'},
		{'1','1', '1', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '1', '0', '1', '0', '1'},
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
		{'1','1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', 'O', '1'} ,
		{'1','1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};


void reset_map()
{
	int i, j;
	for(j=SIDE-1; j >=0; j--)
	{
		for(i=0; i <SIDE; i++)
		{
			if(map[i][j] == 'O')
				map[i][j] = '0';
		}
	}	
	map[SIDE-2][SIDE-2] = 'O';
}	




void print_map()
{
	int i, j;

	/*for(j=SIDE+1; j >=0; j--)
		printf("1 ");
	printf("\n");*/
	for(j=SIDE-1; j >=0; j--)
	{
		//printf("1 ");
		for(i=0; i <SIDE; i++)
		{
			if(map[i][j] != '0')
			{
				if(map[i][j] == 'X')
					printf(RED "X " RESET);
				else
				{	
					if(map[i][j] == 'O')
						printf(GREEN "O " RESET);
					else
						printf("%c ",map[i][j]);
				}
			}
			else
				printf("  ");
		}	
		//printf("1 ");
		printf("\n");
	}
	/*for(j=SIDE+1; j >=0; j--)
		printf("1 ");
	printf("\n");*/
	printf("\n");
}

int wall_left(int pos_x, int pos_y, int wall_x, int wall_y)
{
	int x = pos_x + wall_x;
	int y = pos_y + wall_y;
	if(x >= SIDE)
		return 1;
	if(x < 0)
		return 1;
	if(y >= SIDE)
		return 1;
	if(y < 0)
		return 1;

	if(map[x][y] == '1')
		return 1;
	else
		return 0;
}

int wall_front(int pos_x, int pos_y, int wall_x, int wall_y)
{
	int x = pos_x + (wall_y ? ((wall_y == 1) ? 1 : -1): 0);
	int y = pos_y + (wall_x ? ((wall_x == 1) ? -1 : 1): 0);
	if(x >= SIDE)
		return 1;
	if(x < 0)
		return 1;
	if(y >= SIDE)
		return 1;
	if(y < 0)
		return 1;

	if(map[x][y] == '1')
		return 1;
	else
		return 0;
}

void left_wall_solve()
{
	
	int wall_x = 0, wall_y = -1;

	int x = SIDE-2 , y = SIDE-2;

	while(map[1][1] != 'O')
	{
		

		//no wall to left:
		//turn left and move straight
		if(!wall_left(x, y, wall_x, wall_y))
		{
			
			int tmp = wall_y;
			wall_y = wall_x;
			wall_x = tmp * (-1);

		
			map[x][y] = '0';

			x = x + ((wall_y) ? ((wall_y == 1) ? 1: -1) : 0);
			y = y + ((wall_x) ? ((wall_x == 1) ? -1: 1) : 0);

			map[x][y] = 'O';
			usleep(125000);
		}
		//wall to the left
		else
		{
			//no wall in front
			//go straight
			if(!(wall_front(x, y ,wall_x, wall_y)))
			{
				
				map[x][y] = '0';
				//printf("x %d y %d\n",x,y);

				x = x + ((wall_y) ? ((wall_y == 1) ? 1: -1) : 0);
				y = y + ((wall_x) ? ((wall_x == 1) ? -1: 1) : 0);

				//printf("x %d y %d\n",x,y);

				map[x][y] = 'O';
				usleep(125000);
			}
			//wall in front
			//turn right, dont move
			else
			{
		
				int tmp = wall_x;
				wall_x = wall_y;
				wall_y = tmp * (-1);
				
			}
		}

		print_map();
	}
}













#define UP 		0
#define DOWN 	1
#define RIGHT 	2
#define LEFT 	3

struct edge
{
    //distance
    unsigned int distance;
    //pointer to target node
    struct graph_node *target;
};
struct graph_node
{
    //position
    int x;
    int y;
    //Links to 4 other nodes
    struct edge *connected[4];
    
    //dijsktra closest pointer
    struct graph_node *nearest;
    unsigned int distance;
    int visited;
};

struct graph_node *target;

struct graph_node *new_node(int x, int y)
{
	struct graph_node *new = (struct graph_node *)malloc(sizeof(struct graph_node));

	new->x = x;
	new->y = y;

	int i = 0;
	for(i=0; i<4; i++)
	{
		new->connected[i] = NULL;
	}

	new->nearest = NULL;
	new->distance = INT_MAX;
	new->visited = 0;

	if((x == 1) && (y == 1))
		target=new;

	return new;
}


int is_corner(int x, int y)
{
	/*
	Corner cases:
		Inner corner: 

			11   11   1x   x1
			1x   x1   11   11

		Outer corner

			 x   x    1     1
			1     1    x   x
	*/
	if(map[x+1][y+1] == '1')
	{
		if((map[x][y+1] == '1') && (map[x+1][y] == '1'))
			return 1;
		if((map[x][y+1] == '0') && (map[x+1][y] == '0'))
			return 1;
	}
	if(map[x-1][y-1] == '1')
	{
		if((map[x][y-1] == '1') && (map[x-1][y] == '1'))
			return 1;
		if((map[x][y-1] == '0') && (map[x-1][y] == '0'))
			return 1;
	}
	if(map[x+1][y-1] == '1')
	{
		if((map[x][y-1] == '1') && (map[x+1][y] == '1'))
			return 1;
		if((map[x][y-1] == '0') && (map[x+1][y] == '0'))
			return 1;
	}
	if(map[x-1][y+1] == '1')
	{
		if((map[x][y+1] == '1') && (map[x-1][y] == '1'))
			return 1;
		if((map[x][y+1] == '0') && (map[x-1][y] == '0'))
			return 1;
	}
	return 0;
}

int total_nodes = 0;
struct graph_node * visited[SIDE][SIDE];

int graph_not_wall(int direction, int x, int y)
{
	switch(direction)
	{
		case UP:
			if((map[x][y+1] != '1'))
				return 1;
			else
				return 0;
		case DOWN:
			if((map[x][y-1] != '1'))
				return 1;
			else
				return 0;
		case RIGHT:
			if((map[x+1][y] != '1'))
				return 1;
			else
				return 0;
		case LEFT:
			if((map[x-1][y] != '1'))
				return 1;
			else
				return 0;
	}
}



void build_graph(struct graph_node *root)
{
	int i;
	for(i=0 ; i<4 ; i++)
	{
		int x = root->x, y = root->y;

		int distance = 0;

		while(graph_not_wall(i, x, y))
		{

			//until we hit a wall, can go; update distance traveled
			switch(i)
			{	
				case UP:
					y++;
					break;
				case DOWN:
					y--;
					break;
				case RIGHT:
					x++;
					break;
				case LEFT:
					x--;
					break;
			}

			distance++;
			if(is_corner(x,y))
			{
				
				struct graph_node *node;
				//when we find a corner, generate new node, if no node generated here yet
				if(visited[x][y] == NULL)
				{
					node = new_node(x, y);
					//printf("Built at %d,%d\n",x,y);
					total_nodes++;

					visited[x][y] = node;
				}
				else
				{
					//already node there, just connect, if we haven;t yet
					node = visited[x][y];
				}
				if(root->connected[i] != NULL)
					continue;


				struct edge *new_connection = (struct edge *)malloc(sizeof(struct edge));
				struct edge *target_connection = (struct edge *)malloc(sizeof(struct edge));
				new_connection->distance = distance;
				new_connection->target = node;

				target_connection->distance = distance;
				target_connection->target = root;

				root->connected[i] = new_connection;
				switch(i)
				{	
					case UP:
						node->connected[DOWN] = target_connection;
						break;
					case DOWN:
						node->connected[UP] = target_connection;
						break;
					case RIGHT:
						node->connected[LEFT] = target_connection;
						break;
					case LEFT:
						node->connected[RIGHT] = target_connection;
						break;
				}

				//build graph on new node
				build_graph(node);

				//exit while loop
				break;
			}
		}
	}
}


/**************************************************
 * 
 * 
 * 	Queue for Dijkstra
 * 
 * 
 * ************************************************/
//linked list points to binary tree nodes
//treated as a FIFO (first in, first out) queueu
struct ll_node
{
	struct graph_node *graph_entry;
	struct ll_node *next;
};

struct ll_node *head = NULL;

//creates a new node, adds to head of queue
void add_to_queue(struct graph_node *graph_entry)
{
	struct ll_node *new_queue_entry = (struct ll_node *)malloc(sizeof(struct ll_node));

	new_queue_entry->graph_entry = graph_entry;
	new_queue_entry->next = head;

	head = new_queue_entry;
}

void delete_whole_queue()
{
	struct ll_node *to_free;

	if(head == NULL)
	{
		return;
	}
	while(head != NULL)
	{
		to_free = head;
		head = head->next;
		free(to_free);
	}
}

//returns element from tail of queue; also removes it from queue (without freeing it)
struct graph_node *get_from_queue()
{
	struct ll_node *p = head;
	struct graph_node *found = NULL;

	if(head == NULL)
	{
		return NULL;
	}

	//special case: if we just have one element (head == tail)
	if(head->next == NULL)
	{
		found = head->graph_entry;
		free(head);
		head = NULL;
		return found;
	}


	while((p->next)->next != NULL)
	{
		p = p->next;
	}
	//at this point, p points to second to last element
	found = (p->next)->graph_entry;
	free(p->next);
	p->next = NULL;
	return found;
}
/***************************************************************
 * 
 * 
 * 	End queue
 * 
 * 
 * *********************************************************/
/*struct edge
{
    //distance
    int distance;
    //pointer to target node
    struct graph_node *target;
};
struct graph_node
{
    //position
    int x;
    int y;
    //Links to 4 other nodes
    struct edge *connected[4];
    
    //dijsktra closest pointer
    struct graph_node *nearest;
    int distance;
    int visited;
};*/
void dijkstra()
{
	
}


void print_shortest_path(struct graph_node *node)
{
	if((node->x == (SIDE-2)) && (node->y == (SIDE-2)))
	{
		printf("(20,20)\n");
		return;
	}
	printf("(%d,%d) <- ",node->x,node->y);
	print_shortest_path(node->nearest);
}



/*
	Target is at position 2,2
*/

int main()
{
	reset_map();
	print_map();

	//left_wall_solve();

	//we know first node: start position
	int i, j;

	for(i=0; i<SIDE; i++)
	{
		for(j=0; j<SIDE; j++)
		{
			visited[i][j] = NULL;
		}	
	}

	struct graph_node *root = new_node(SIDE-2, SIDE-2);

	visited[SIDE-2][SIDE-2] = root;

	build_graph(root);

	printf("Generated graph with %d nodes\n",total_nodes);

	add_to_queue(root);

	root->nearest = root;
	root->distance = 0;

	dijkstra();

	printf("Shortest distance is %d\n",target->distance);

	print_shortest_path(target);

	return 0;
}