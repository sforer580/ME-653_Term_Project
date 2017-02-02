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
    int num_indv = 10;
    int gen_max = 300;
    double time_max = 10;
    double delta_t = 0.1;
    
    
private:
};

#endif /* Parameters_hpp */
