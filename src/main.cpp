#include "../doc/Hospital.hpp"
using namespace std;
#include <iostream>

//main function 
int main()
{
    Hospital H;

    H.get_information();

    H.FCFS();
    cout << "\n--------------------------------------------------------------\n" << endl;
    H.SJF();
    cout << "\n--------------------------------------------------------------\n" << endl;
    H.Priority_Scheduling();
    
    return 0;
}
//end main

