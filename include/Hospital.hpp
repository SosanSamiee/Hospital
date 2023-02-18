#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <array>

class Hospital
{
    public:
        Hospital();
        void get_numberbed();
        void get_numberpatient();
        void get_information();

    private:
        unsigned int number_bed;
        unsigned int number_patient;
        std::array<std::array<int, 3>, 1000> information_table{};
        
};

#endif