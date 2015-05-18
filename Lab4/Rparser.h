#define CH_NOTHING -1
#include "NodeList.h"
#include "ResistorList.h"

using namespace std;

int few_arg ( string last ); 		//function to analise the number of arguments.
int node ( string x , string x2 , int *y , int *z);		//function to analise both nodes given by user.
int resistance ( string x , double *r );				//function to analise the resistance given by user.
int not_all ( string x );					//function to analise if string it's equal to 'all'.
int more_arg (string control);


void add ( stringstream &lineStream , NodeList *list_of_nodes);		//
void changeR ( stringstream &lineStream , NodeList *list_of_nodes);	//
void find ( stringstream &lineStream , NodeList *list_of_nodes);		//		FUNCTIONS FOR EACH COMMAND
void list ( stringstream &lineStream , NodeList *list_of_nodes);		//
void clear ( stringstream &lineStream , NodeList *list_of_nodes);	//
void remove ( stringstream &lineStream , NodeList *list_of_nodes);

