//
//  Individual.hpp
//  Vibrations_Term_Project
//
//  Created by Scott S Forer on 2/2/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Individual_hpp
#define Individual_hpp

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


class Individual
{
    friend class Parameters;
    friend class EA;
    friend class Simulator;
    
protected:
    
    
public:
    double K1;
    double K2;
    double C1;
    double C2;
    vector<double> y1;
    vector<double> y1_d;
    vector<double> y2;
    vector<double> y2_d;
    vector<double> accel;
    vector<double> x;
    vector<double> del_y;
    double fitness;
    
private:
};

#endif /* Individual_hpp */
