#include<stdio.h>
#include<stdlib.h>
//comment this in Windows/MacOS: unistd is Linux specific
//lookup required header file for usleep() in your OS
#include<windows.h>

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

	for(j=SIDE-1; j >=0; j--)
	{
		printf("1 ");
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
		printf("1 ");
		printf("\n");
	}
}


#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

//assuming:
//it's a legal move
void move(int x, int y, int direction)
{
	//clear the map
	
	if(direction == WEST)
	{
		//update character
        map[x][y] = '0';
		map[x-1][y] = 'O';
		return;
	}
	if(direction == EAST)
	{
		//update character
        map[x][y] = '0';
		map[x+1][y] = 'O';
		return;
	}
	if(direction == NORTH)
	{
		//update character
        map[x][y] = '0';
		map[x][y+1] = 'O';
		return;
	}
	if(direction == SOUTH)
	{
		//update character
        map[x][y] = '0';
		map[x][y-1] = 'O';
		return;
	}
}


int wall_to_left(int x, int y, int direction)
{
	if(direction == WEST)
	{
		if(map[x][y-1] == '1')
			return 1;
		else
			return 0;
	}
	if(direction == EAST)
	{
		if(map[x][y+1] == '1')
			return 1;
		else
			return 0;
	}
	if(direction == NORTH)
	{
		if(map[x-1][y] == '1')
			return 1;
		else
			return 0;
	}
	if(direction == SOUTH)
	{
		if(map[x+1][y] == '1')
			return 1;
		else
			return 0;
	}
}

int wall_to_front(int x, int y, int direction)
{
	if(direction == WEST)
	{
		if(map[x-1][y] == '1')
			return 1;
		else
			return 0;
	}
	if(direction == EAST)
	{
		if(map[x+1][y] == '1')
			return 1;
		else
			return 0;
	}
	if(direction == NORTH)
	{
		if(map[x][y+1] == '1')
			return 1;
		else
			return 0;
	}
	if(direction == SOUTH)
	{
		if(map[x][y-1] == '1')
			return 1;
		else
			return 0;
	}
}

int turn_left(int direction)
{
	if(direction == WEST)
		return SOUTH;
	if(direction == SOUTH)
		return EAST;
	if(direction == EAST)
		return NORTH;

	return WEST;
}

int turn_right(int direction)
{
	if(direction == WEST)
		return NORTH;
	if(direction == NORTH)
		return EAST;
	if(direction == EAST)
		return SOUTH;

	return WEST;
}

int moved_x(int x,int direction)
{
	if(direction == WEST)
		return x-1;
	if(direction == EAST)
		return x+1;
	return x;
}
int moved_y(int y,int direction)
{
	if(direction == SOUTH)
		return y-1;
	if(direction == NORTH)
		return y+1;
	return y;
}



int left_wall_solve(int x, int y, int direction)
{
	//TODO...
    // printf("x: %d, y: %d, direction: %d\n", x, y, direction);
    if (x == 1 && y == 1) {
        printf("Reached the goal!\n");
        return 0;
    }
    if (wall_to_left(x,y,direction) == 0){

        direction = turn_left(direction);
        move(x,y,direction);
        x = moved_x(x,direction);
        y = moved_y(y,direction);

    } else if (wall_to_left(x,y,direction)==1 && wall_to_front(x, y, direction)==0){
        move(x,y,direction);
        x = moved_x(x,direction);
        y = moved_y(y,direction);

    } else{
        direction = turn_right(direction); 
    }
	print_map();
    // add sleep
    Sleep(50);
    left_wall_solve(x, y, direction);
    return 0;
}



int main()
{
	reset_map();
	print_map();

	left_wall_solve(SIDE-2, SIDE-2, WEST);

	return 0;
}