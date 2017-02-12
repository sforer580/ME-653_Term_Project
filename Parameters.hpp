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
    double spring_free_length = 1;                              //[meters]
    double K1_min = 1;                                          //[Newton/meters]
    double K1_max = 10;                                         //[Newton/meters]
    double K2_min = 1;                                          //[Newton/meters]
    double K2_max = 10;                                         //[Newton/meters]
    double C1_min = 1;                                          //[kilogram/second]
    double C1_max = 10;                                         //[kilogram/second]
    double C2_min = 1;                                          //[kilogram/second]
    double C2_max = 10;                                         //[kilogram/second]
    double mass = 1;                                            //[kilogram]
    int gen_max = 1;
    
    //Simulator Parameters
    double time_max = 1;                                        //[seconds]
    double delta_t = 0.1;                                       //[seconds]
    double amp = 1;                                             //[meters]
    double period = 1;                                          //[second]
    double lamda = 1;                                           //[meters]
    double freq = 1/period;                                     //[hertz]
    double travel_speed = freq*lamda;                           //[meters/second]
    double omega = 2*3.14159*freq;                              //[radians/second]
    double delta_x = (travel_speed*delta_t)/(freq*period);      //[meters]

    
    
private:
};

#endif /* Parameters_hpp */
