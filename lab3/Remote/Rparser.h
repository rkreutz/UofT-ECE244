#include "Node.h"
#define CH_NOTHING -1	


using namespace std;

int few_arg ( string last ); 		//function to analise the number of arguments.
int node ( string x , string x2 , int *y , int *z);		//function to analise both nodes given by user.
int resistance ( string x , double *r );				//function to analise the resistance given by user.
int not_all ( string x );					//function to analise if string it's equal to 'all'.
int more_arg (string control);


void add ( stringstream &lineStream );		//
void changeR ( stringstream &lineStream );	//
void find ( stringstream &lineStream );		//		FUNCTIONS FOR EACH COMMAND
void list ( stringstream &lineStream );		//
void clear ( stringstream &lineStream );	//


