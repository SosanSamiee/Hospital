#include "../include/Hospital.hpp"
#include <iostream>

//class constructor
Hospital::Hospital()
{
    get_numberbed();
    get_numberpatient();
    get_information();
    FCFS();
}

//getting the capacity of hospital
void Hospital::get_numberbed()
{
    std::cout << "Enter the capacity of hospital beds>>>> ";
    std::cin >> number_bed;
}

//getting the number of patient
void Hospital::get_numberpatient()
{
    std::cout << "Enter the number of patient>>>> ";
    std::cin >> number_patient;
}

//getting patient information
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
     
//scenario: first come, first served 
void Hospital::FCFS()
{
    //array to stor hospitalization information
    std::array<std::array<int, 2>,  1000 > hospitalization{};
    //place of hospitalization of the patient
    std::array<int, 1000 > bed{};

    //Initialization
    for(int i = 0; i < number_bed; i++)
    {
        bed[i] = 0;
    }

    int count = 0;

    for(int i = 0; count < number_patient ; i++)
    {
        //hospitalization time
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
        //passing of time
        for(int z = 0; z < number_bed; z++)
        {
            if(bed[z] != 0)
            {
                bed[z] -= 1;
            }
        }   
    }

    std::cout << "....FCFS..." << std::endl;
    //print scenario(FCFS) rasult
    for(int i = 0; i < number_patient; i++)
    {
        std::cout << "pationt " << i + 1 << " >>>>   hospitalization time " << 
        hospitalization[i][0] <<"    hospitalization bed  " << hospitalization[i][1] << std::endl; 
    }
    
    //total waiting time
    long int total_waitingtime = 0;
    //number of dead
    int number_deaths = 0;

    for(int j = 0; j < number_patient; j++)
    {
        if( hospitalization[j][0] - information_table[j][1] + 
            information_table[j][2] > information_table[j][3])
        {
            number_deaths++;
        }
        total_waitingtime += hospitalization[j][0];
    }

    std::cout << "avarag = " << (float)total_waitingtime / (float)number_patient << std::endl;  
    std::cout << "the number of deaths = " << number_deaths << std::endl; 
    std::cout << "the number of recoveries = " << number_patient - number_deaths << std::endl;   
}



