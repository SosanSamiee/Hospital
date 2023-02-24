#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <array>
//Hospital class to do project scenarios
class Hospital
{
    public:
        //class constructor
        Hospital();
        void get_numberbed();
        void get_numberpatient();
        void get_information();
        void FCFS();//scenario:first come first served
        void SJF();
        void  Priority_Scheduling();
        //void print_result();
    
    private:

        unsigned int number_bed;
        int number_patient;
        //array to store information
        std::array<std::array<int, 4>, 1000> information_table{};
        
};

//end class
#endif