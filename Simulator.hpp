//
//  Simulator.hpp
//  Vibrations_Term_Project
//
//  Created by Scott S Forer on 2/2/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Simulator_hpp
#define Simulator_hpp

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


class Simulator
{
    friend class Parameters;
    friend class EA;
    friend class Individual;
    
protected:
    
    
public:
    Parameters* pP;
    void Initialize_Agent(Individual* pI);
    void Simulate(Individual* PI);
    
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Runs the entire simulation process
void Simulator::Initialize_Agent(Individual* pI)
{
    pI->y2.push_back(0);
    pI->y1.push_back(pP->spring_free_length);
}


//-------------------------------------------------------------------------
//Runs the entire simulation process
void Simulator::Simulate(Individual* pI)
{
    //cout << "IN" << "\t" << pI->K1 << endl;
    //pI->K1 = 1;
    //cout << "OUT" <<"\t" << pI->K1 << endl;
}

#endif /* Simulator_hpp */
