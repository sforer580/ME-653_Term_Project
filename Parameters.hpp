//
//  Parameters.hpp
//  Vibrations_Term_Project
//
//  Created by Scott S Forer on 2/2/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <ctime>
#include <random>


using namespace std;


class Parameters
{
    friend class EA;
    friend class Individual;
    friend class Simulator;
    
protected:
    
    
public:
    //EA Parameters
    int num_indv = 1;
    double K1_min = 1;                          //[units]
    double K1_max = 10;                         //[units]
    double K2_min = 1;                          //[units]
    double K2_max = 10;                         //[units]
    double C1_min = 1;                          //[units]
    double C1_max = 10;                         //[units]
    double C2_min = 1;                          //[units]
    double C2_max = 10;                         //[units]
    int gen_max = 300;
    
    //Simulator Parameters
    double time_max = 10;                       //[seconds]
    double delta_t = 0.1;                       //[seconds]
    double spring_free_length = 1;              //[meters]
    double amp = 1;                             //[meters]
    double period = 1;                          //[second]
    double lamda = 1;                           //[meters]
    double freq = 1/period;                     //[hertz]
    double travel_speed = freq*lamda;           //[meters/seconds]

    
    
private:
};

#endif /* Parameters_hpp */
