#include "CRec.h"
using namespace std;

int main(int argc, char *argv[])
{
    CRectangle rect ;
    CRectangle rectb (5,6);
    cout << "rect area: " << rect.area() << endl;
    cout << "rectb area: " << rectb.area() << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
