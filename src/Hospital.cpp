#include "../include/Hospital.hpp"

#include <iostream>

Hospital::Hospital()
{
    get_numberbed();
    get_numberpatient();
    get_information();
    FCFS();
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
        information_table[i][0] = i + 1;
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
     
//first come, first served scenario
void Hospital::FCFS()
{
    std::array<std::array<int, 2>,  1000 > hospitalization{};
    std::array<int, 1000 > bed{};

    for(int i = 0; i < number_bed; i++)
    {
        bed[i] = 0;
    }

    int count = 0;

    for(int i = 0; count < number_patient ; i++)
    {
        for(int k = 0; k < number_bed; k++)
        {
            if(bed[k] == 0 && information_table[count][1] <= i)
            {
                bed[k] = information_table[count][2];
                hospitalization[count][0] = i;
                hospitalization[count][1] = k + 1;
                count++;
            }
        }
        for(int z = 0; z < number_bed; z++)
        {
            if(bed[z] != 0)
            {
                bed[z] -= 1;
            }
        }   
    }


    ////
    for(int i = 0; i < number_patient; i++)
    {
        std::cout << "pationt " << i + 1 << " >>>>   hospitalization time " << hospitalization[i][0] <<
        "    hospitalization bed  " << hospitalization[i][1] << std::endl; 
    }

}

