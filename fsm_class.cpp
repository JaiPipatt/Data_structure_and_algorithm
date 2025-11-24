#include<iostream>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

class FSM;


struct state
{
	char *name;
	//unique ID
	int id;
	//function pointer to state transition function
		//returns ID of target state
	int (* stf)(FSM *fsm);
	struct state *next;
};


class FSM
{
	private:
	char *name;
	//number of states
	int state_count;

	//current state
	struct state *current;

	//list of states
	struct state *states;

	public:
	FSM(char *n)
	{
		//initializations
		current = NULL;
		states = NULL;

		state_count = 0;

		name = (char *)malloc(strlen(n)+1);
		strcpy(name,n);
	}

	//adds a new state to state machine, with given name
	void add_state(char *n)
	{
		struct state *s;

		s = new(struct state);

		s->name = (char *)malloc(strlen(n)+1);
		strcpy(s->name,n);

		/*
			Missing error handling:
				ensure we do not repeat state names
		*/

		s->id = state_count;
		state_count++;

		s->stf = NULL;

		s->next = states;
		states = s;
	}
	char *get_current_state()
	{
		return current->name;
	}
	void set_current_state(char *n)
	{
		struct state *s;

		s = states;

		while(strcmp(s->name,n)!=0)
		{
			s=s->next;
			/*
				Missing error handling:
					ensure we do not reach end of list without finding state
			*/
		}
		current = s;
	}
	//adds a new state transition function to a state with given name
	void add_stf(int (* stf)(FSM *fsm) ,char *n)
	{
		struct state *s;

		s = states;

		while(strcmp(s->name,n)!=0)
		{
			s=s->next;
			/*
				Missing error handling:
					ensure we do not reach end of list without finding state
			*/
		}
		s->stf = stf;
	}
	int get_state_id(char *n)
	{
		struct state *s;

		s = states;

		while(strcmp(s->name,n)!=0)
		{
			s=s->next;
			/*
				Missing error handling:
					ensure we do not reach end of list without finding state
			*/
		}
		return s->id;
	}
	struct state *get_state_by_id(int n)
	{
		struct state *s;

		s = states;

		while((s->id)!=n)
		{
			s=s->next;
			/*
				Missing error handling:
					ensure we do not reach end of list without finding state
			*/
		}
		return s;
	}
	//applies current state's transition function, modifies current state
	void transition()
	{
		int target_id;

		target_id = (*(current->stf))(this);

		current = get_state_by_id(target_id);
	}
};




int on_stf(FSM *fsm)
{
	/*
		More generally: would test all relevant inputs
		Decide which state we're supposed to go to (by name)
		return with "get_state_id" to get id of corresponding name
	*/
	return fsm->get_state_id((char *)"off");
}
int off_stf(FSM *fsm)
{
	return fsm->get_state_id((char *)"on");
}




int main()
{

	//Construct the state machine
	FSM fsm((char *)"light");

	fsm.add_state((char *)"on");
	fsm.add_state((char *)"off");

	fsm.add_stf(&on_stf ,(char *)"on");
	fsm.add_stf(&off_stf ,(char *)"off");

	fsm.set_current_state((char *)"off");


	//Operate it
	cout << "State " << fsm.get_current_state() << "\n";
	fsm.transition();
	cout << "State " << fsm.get_current_state() << "\n";
	fsm.transition();
	cout << "State " << fsm.get_current_state() << "\n";
	fsm.transition();
	cout << "State " << fsm.get_current_state() << "\n";
	fsm.transition();

	return 0;
}