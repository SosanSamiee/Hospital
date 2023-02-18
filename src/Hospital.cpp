#include "../include/Hospital.hpp"

#include <iostream>

Hospital::Hospital()
{
    get_numberbed();
    get_numberpatient();
    get_information();
}

void Hospital::get_numberbed()
{
    std::cout << "Enter the capacity of hospital beds>>>> ";
    std::cin >> number_bed;
}


void Hospital::get_numberpatient()
{
    std::cout << "Enter the number of patient>>>> ";
    std::cin >> number_patient;
}

//get information
void Hospital::get_information()
{
    for(int i = 0; i < number_patient; i++)
    {
        //number patient
        information_table[i][0] = i;
        std::cout << "patient number   " << i + 1 << std::endl; 
        for(int j = 1; j < 4; j++)
        {
            switch (j)
            {
                case 1:
                    //get rrival time
                    std::cout << "Enter the patient's arrival time>>>> ";
                    std::cin >> information_table[i][j];
                    break;
                case 2:
                    //get time required to hospitalize 
                    std::cout << "Enter the time required to hospitalize the pationt>>>> ";
                    std::cin >> information_table[i][j];
                    break;
                case 3:
                    //get distance to death
                    std::cout << "Enter the time to death of the pationt>>>> ";
                    std::cin >> information_table[i][j];
                    break;
            }
        }
    }

}