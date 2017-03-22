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
    //Agent Parameters
    int num_indv = 100;
    double spring_free_length = 0.3;                            //[meters]
    double K1_min = 0.1;                                        //[Newton/meters]
    double K1_max = 6000;                                       //[Newton/meters]
    double K1_range = 5;                                        //[Newton/meters]
    double K2_min = 0.1;                                        //[Newton/meters]
    double K2_max = 6000;                                       //[Newton/meters]
    double K2_range = 5;                                        //[Newton/meters]
    double C1_min = 0.1;                                        //[kilogram/second]
    double C1_max = 1000;                                       //[kilogram/second]
    double C1_range = 5;                                        //[Newton/meters]
    double C2_min = 0.1;                                        //[kilogram/second]
    double C2_max = 1000;                                       //[kilogram/second]
    double C2_range = 5;                                        //[Newton/meters]
    double mass = 1600;                                         //[kilogram]
    
    //EA Parameters
    int gen_max = 2000;
    double mutation_rate = 0.5;                                 //[num*100=>%]
    int to_kill = num_indv/2;
    int num_sr = 2;
    
    //Simulator Parameters
    double time_max = 10;                                       //[seconds]
    double delta_t = 0.01;                                      //[seconds]
    //Wave 1
    double amp_1 = 0.15;                                        //[meters]
    double period_1 = 1;                                        //[second]
    double lamda_1 = 1;                                         //[meters]
    double freq_1 = 1/period_1;                                 //[hertz]
    double travel_speed_1 = freq_1*lamda_1;                     //[meters/second]
    double omega_1 = 2*3.14159*freq_1;                          //[radians/second]
    double delta_x = (travel_speed_1*delta_t);                  //[meters]
    //Wave 2
    double amp_2 = 0.05;                                        //[meters]
    double period_2 = 1/9;                                      //[second]
    double lamda_2 = 0.1;                                       //[meters]
    double freq_2 = 1/period_1;                                 //[hertz]
    double travel_speed_2 = freq_2*lamda_2;                     //[meters/second]
    double omega_2 = 2*3.14159*freq_2;                          //[radians/second]

    //Experimental switches
    int normal_wave = 1;                                        //0=off, 1=on
    int bumpy_wave = 0;                                         //0=off, 1=on
    
private:
};

#endif /* Parameters_hpp */
