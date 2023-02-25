#include "../include/Hospital.hpp"
#include <iostream>

//class constructor
Hospital::Hospital()
{
    get_numberbed();
    get_numberpatient();
    get_information();
    //FCFS();
    //SJF();
    //Priority_Scheduling();
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
    // check alive
    std::array<bool, 1000 > alive{};
    // check leave
    std::array<bool, 1000 > leave{};

    //Initialization
    for(int i = 0; i < number_bed; i++)
    {
        bed[i] = 0;
    }
    for (int i = 0; i < 1000; i++)
    {
        alive[i] = true ;
        leave[i] = false;
    }

    // hospitalized pation counter 
    int count = 0;
    //number of dead
    int number_deaths = 0;
    //number of pation how have come
    int number_pation_come = 0;
    // elapsed time calculation
    int count_time = 0; 
    // competion of treatment
    bool End = false ;
    for(int i = 0; ! End ; i++)
    {
        //std::cout << "i -> " << i << std::endl ;

        // caculate the number of pation how have come
        number_pation_come = 0;
        for ( int t = 0; number_patient > t && information_table[t][1] <= i  ; t++ )
        {
            number_pation_come++;
        }

        // caculate the number of pation how have bean leave
        for ( int t = 0; count > t  ; t++ )
        {
            if(! leave[t] && information_table[t][2] == 0 && information_table[t][3] != 0 )
            {
                leave[t] = true;         
                hospitalization[t][0] = 0 ;
                hospitalization[t][1] = -3;
            }
            if (! leave[t] && information_table[t][3] != 0  && hospitalization[t][0] >= information_table[t][1] && (count_time - information_table[t][1] >= hospitalization[t][0] - information_table[t][1] + information_table[t][2]) )
            {
                leave[t] = true;
            }
        }

        // check death
        for(int j = 0; j < number_pation_come ; j++)
        {
            if( !leave[j] && alive[j] && information_table[j][3] == 0 )
            {
                number_deaths++;
                alive[j] = false;
                leave[j] = true;
                hospitalization[j][0] = 0 ;
                hospitalization[j][1] = -2;
            }
            if ( !leave[j] && alive[j] && j >= count )
            {
                if ( (count_time - information_table[j][1]) >= information_table[j][3] )
                {
                    //std::cout <<" *\n" ;
                    number_deaths++;
                    alive[j] = false;
                    leave[j] = true;
                    hospitalization[j][0] = count_time ;
                    hospitalization[j][1] = -1;
                }
            }
            else if( !leave[j] && alive[j] && ( count_time - information_table[j][1] ) >= information_table[j][3] ) 
            {
                //std::cout << "**\n" ;
                
                number_deaths++;
                bed[hospitalization[j][1]-1] = 0;
                alive[j] = false;
                leave[j] = true;
            }
        }

        for ( int t = 0; number_patient > t  ; t++ )
        {
            if ( leave[t] )
            {
                End = true;
            }
            else
            {
                End = false;
                break;
            }
        }

        //hospitalization time
        for(int k = 0; count < number_patient && k < number_bed && information_table[count][1] <= i; k++)
        {
            if( !leave[count] && alive[count] && bed[k] == 0 )
            {
                bed[k] = information_table[count][2];
                hospitalization[count][0] = i;
                hospitalization[count][1] = k + 1;
                count++;
            }            
            if (! alive[count] )
            {
                //std::cout << "k -> " << k << std::endl ;
                count++;
                k--;
            }
        }

        //passing of time
        count_time++ ;
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
        if (alive[i]) 
        {
            if (hospitalization[i][1] == -3)
            {
                std::cout << "pationt " << i + 1 <<" >>>>   Outpation " << std::endl ;
            }
            else 
            {
                std::cout << "pationt " << i + 1 << " >>>>   hospitalization time " << 
                hospitalization[i][0] <<"    hospitalization bed  " << hospitalization[i][1] << std::endl; 
            }
        }
        else{
            std::cout << "pationt " << i + 1 ;
            if ( hospitalization[i][1] == -1 )
            {
                std::cout << " >>>>   death " << " -  \" Unfortunately, an ampty bed was not found for the patient and he died. \"  " << std::endl;
            }
            else if (hospitalization[i][1] == -2)
            {
                std::cout << " >>>>   death " << " -  \" The coming of a dead person. \"  " << std::endl ;
            }
            else
            {
                std::cout << " >>>>   hospitalization time " << hospitalization[i][0] <<
                "    hospitalization bed  " << hospitalization[i][1] << "   >>>>  death " << std::endl; 
            }
        }
    }
    
    //total waiting time
    long int total_waitingtime = 0;
    // //number of dead
    // int number_deaths = 0;

    for(int j = 0; j < number_patient; j++)
    {
        total_waitingtime += hospitalization[j][0] - information_table[j][1];
    }

    std::cout << "avarag = " << (float)total_waitingtime / (float)number_patient << std::endl;  
    std::cout << "\" To Allah we belong. and to him is our return. \" \n"
     << "the number of deaths = " << number_deaths << std::endl; 
    std::cout << "the number of recoveries = " << number_patient - number_deaths << std::endl;   
}

//scenario: Shortesr Job First 
void Hospital::SJF()                                                                                                                                                                                                
{
    //array to stor hospitalization information
    std::array<std::array<int, 2>,  1000 > hospitalization{};
    //place of hospitalization of the patient
    std::array<int, 1000 > bed{};

    // check alive
    std::array<bool, 1000 > alive{};
    // check leave
    std::array<bool, 1000 > leave{};

    //Initialization
    for(int i = 0; i < number_bed; i++)
    {
        bed[i] = 0;
    }
    for (int i = 0; i < 1000; i++)
    {
        alive[i] = true ;
        leave[i] = false;
    }
    //copy array
    std::array<std::array<int, 4>, 1000> information_in_SJF{};
    for(int i = 0; i < number_patient; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            information_in_SJF[i][j] = information_table[i][j];
        }
    }

    // hospitalized pation counter 
    int count = 0;
    //number of dead
    int number_deaths = 0;
    //number of pation how have come
    int number_pation_come = 0;
    // elapsed time calculation
    int count_time = 0; 
    // competion of treatment
    bool End = false ;

    for(int i = 0; ! End ; i++)
    {
        // caculate the number of pation how have come
        number_pation_come = 0;
        for ( int t = 0; number_patient > t && information_table[t][1] <= i  ; t++ )
        {
            number_pation_come++;
        }

        // caculate the number of pation how have bean leave
        for ( int t = 0;  number_pation_come > t  ; t++ )
        {
            if( ! leave[t] && information_table[t][2] == 0 && information_table[t][3] != 0 )
            {
                count++;
                hospitalization[t][0] = 0 ;
                hospitalization[t][1] = -3;
                leave[t] = true;            
            }
            if (! leave[t] && information_table[t][3] != 0  && hospitalization[t][0] >= information_table[t][1] && 
            (count_time - information_table[t][1] >= hospitalization[t][0] - information_table[t][1] + information_table[t][2]) )
            {
                leave[t] = true;
            }
        }

        // check death
        for(int j = 0; j < number_pation_come ; j++)
        {
            if( !leave[j] && alive[j] && information_table[j][3] == 0 )
            {
                count++;
                number_deaths++;
                alive[j] = false;
                leave[j] = true;
                hospitalization[j][0] = 0 ;
                hospitalization[j][1] = -2;
            }
            if ( !leave[j] && alive[j] && information_in_SJF[j][2] != 0 )
            {
                if ( (count_time - information_table[j][1]) >= information_table[j][3] )
                {
                    count++;
                    number_deaths++;
                    alive[j] = false;
                    leave[j] = true;
                    hospitalization[j][0] = count_time ;
                    hospitalization[j][1] = -1;
                }
            }
            else if( !leave[j] && alive[j] && ( count_time - information_table[j][1] ) >= information_table[j][3] ) 
            {
                number_deaths++;
                bed[hospitalization[j][1]-1] = 0;
                alive[j] = false;
                leave[j] = true;
            }
        }

        for ( int t = 0; number_patient > t  ; t++ )
        {
            if ( leave[t] )
            {
                End = true;
            }
            else
            {
                End = false;
                break;
            }
        }
        //hospitalization time
        for(int k = 0; count < number_patient && k < number_bed && information_table[k][1] <= i; k++)
        {

            if( bed[k] == 0 ) 
            {
                int min = 0;
                int c = 0;
                int check_pation = 0;
                for(int j = 0; information_in_SJF[j][1] <= i && j < number_patient  ; j++)
                {
                    if( ( !leave[j] && alive[j] ) && min == 0 && information_in_SJF[j][2] != 0)
                    {
                        min = information_in_SJF[j][2];
                        c = j;
                        check_pation = information_in_SJF[j][0];
                    }
                    if(( !leave[j] && alive[j] ) && information_in_SJF[j][2] != 0 && information_in_SJF[j][2] < min)
                    {
                        min = information_in_SJF[j][2];
                        c = j;
                        check_pation = information_in_SJF[j][0];
                    }
                }
                bed[k] = information_in_SJF[c][2];
                information_in_SJF[c][2] = 0;
                hospitalization[c][0] = i;
                hospitalization[c][1] = k + 1;
                count++;
            }
        }                                                                                               
        //passing of time
        count_time ++;
        for(int z = 0; z < number_bed; z++)
        {
            if(bed[z] != 0)
            {
                bed[z] -= 1;
            }
        }   
    }  
    std::cout << "....SJF..." << std::endl;
    //print scenario(FCFS) rasult
    for(int i = 0; i < number_patient; i++)
    {
        if (alive[i]) 
        {
            if (hospitalization[i][1] == -3)
            {
                std::cout << "pationt " << i + 1 <<" >>>>   Outpation " << std::endl ;
            }
            else 
            {
                std::cout << "pationt " << i + 1 << " >>>>   hospitalization time " << 
                hospitalization[i][0] <<"    hospitalization bed  " << hospitalization[i][1] << std::endl; 
            }
        }
        else{
            std::cout << "pationt " << i + 1 ;
            if ( hospitalization[i][1] == -1 )
            {
                std::cout << " >>>>   death " << " -  \" Unfortunately, an ampty bed was not found for the patient and he died. \"  " << std::endl;
            }
            else if (hospitalization[i][1] == -2)
            {
                std::cout << " >>>>   death " << " -  \" The coming of a dead person. \"  " << std::endl ;
            }
            else
            {
                std::cout << " >>>>   hospitalization time " << hospitalization[i][0] <<
                "    hospitalization bed  " << hospitalization[i][1] << "   >>>>  death " << std::endl; 
            }
        }
    }

    //total waiting time
    long int total_waitingtime = 0;
    // //number of dead
    // int number_deaths = 0;

    for(int j = 0; j < number_patient; j++)
    {
        total_waitingtime += hospitalization[j][0] - information_table[j][1];
    }

    std::cout << "avarag = " << (float)total_waitingtime / (float)number_patient << std::endl;  
    std::cout << "\" To Allah we belong. and to him is our return. \" \n"
     << "the number of deaths = " << number_deaths << std::endl; 
    std::cout << "the number of recoveries = " << number_patient - number_deaths << std::endl;   

}






