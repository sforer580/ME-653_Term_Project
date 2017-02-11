//
//  EA.hpp
//  Vibrations_Term_Project
//
//  Created by Scott S Forer on 2/2/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef EA_hpp
#define EA_hpp

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


class EA
{
    friend class Parameters;
    friend class Individual;
    friend class Simulator;
    
protected:
    
    
public:
    Parameters* pP;
    
    vector<Individual> agent;
    
    void Build_Population();
    void Run_Simulation();
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Builds population of individuals
void EA::Build_Population()
{
    for (int i=0; i<pP->num_indv; i++)
    {
        Individual I;
        agent.push_back(I);
        agent.at(i).K1 = pP->K1_min + (rand() / double(RAND_MAX))*(pP->K1_max - pP->K1_min);
        agent.at(i).K2 = pP->K2_min + (rand() / double(RAND_MAX))*(pP->K2_max - pP->K2_min);
        agent.at(i).C1 = pP->C1_min + (rand() / double(RAND_MAX))*(pP->C1_max - pP->C1_min);
        agent.at(i).C2 = pP->C2_min + (rand() / double(RAND_MAX))*(pP->C2_max - pP->C2_min);
        agent.at(i).fitness = 0;
    }
}


//-------------------------------------------------------------------------
//Puts each individual into the simulation
void EA::Run_Simulation()
{
    for (int i=0; i<pP->num_indv; i++)
    {
        //cout << "BEFORE" << "\t" << agent.at(i).K1 << endl;
        Simulator S;
        Parameters P;
        S.pP = &P;
        Individual* pI;
        pI = & agent.at(i);
        S.Simulate(pI);
        //cout << "AFTER" << "\t" << agent.at(i).K1 << endl;      //note that agent information is changed in simulation
    }
}


#endif /* EA_hpp */
