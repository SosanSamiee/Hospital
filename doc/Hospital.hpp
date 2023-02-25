#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <vector>
#include <array>

//Hospital class to do project scenarios
class Hospital
{
    public:
        //class constructor
        Hospital();
        void get_information();
        void FCFS(); //scenario: first come first served
        void SJF(); //scenario: Shortesr Job First 
        void Priority_Scheduling(); //scenario: Priority Scheduling
        void print_result(int);
        void get_numberbed();
        void get_numberpatient();
    private:
    
        //number of dead
        int number_deaths = 0;
        int number_bed = 0;
        int number_patient = 0;
        //array to store information
        std::vector<std::array<int, 4>> information_table;
        //array to stor hospitalization information
        std::vector<std::array<int, 2> > hospitalization;
        //place of hospitalization of the patient
        std::vector<int> bed;
        // check alive
        std::vector<bool> alive;
        // check leave
        std::vector<bool> leave;
};

//end class
#endif