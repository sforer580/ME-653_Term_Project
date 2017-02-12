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
    void Get_New_y1(int t, Individual* pI);
    void Get_New_y1_d(int t, Individual* pI);
    void Get_New_y2(int t, Individual* pI);
    void Get_New_y2_d(int t, Individual* pI);
    void Get_New_Accel(int t, Individual* pI);
    void Run_Time_Step(int t, Individual* pI);
    void Simulate(Individual* PI);
    
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Sets the intial conditions for the individual
void Simulator::Initialize_Agent(Individual* pI)
{
    pI->x.push_back(0);
    pI->del_y.push_back(0);
    pI->y2.push_back(0);
    pI->y2_d.push_back(0);
    pI->y1.push_back(pP->spring_free_length);
    pI->y1_d.push_back(0);
    pI->accel.push_back(0);
}


//-------------------------------------------------------------------------
//Gets the new acceleration
void Simulator::Get_New_Accel(int t, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y1
void Simulator::Get_New_y1(int t, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y1 dot
void Simulator::Get_New_y1_d(int t, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y2
void Simulator::Get_New_y2(int t, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y2 dot
void Simulator::Get_New_y2_d(int t, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Runs a single time step
void Simulator::Run_Time_Step(int t, Individual* pI)
{
    Get_New_Accel(t, pI);
    Get_New_y1(t, pI);
    Get_New_y1_d(t, pI);
    Get_New_y2(t, pI);
    Get_New_y2_d(t, pI);
}


//-------------------------------------------------------------------------
//Runs the entire simulation process
void Simulator::Simulate(Individual* pI)
{
    for (int t=0; t<pP->time_max; t++)
    {
        if (t == 0)
        {
            Initialize_Agent(pI);
        }
        if (t > 0)
        {
            Run_Time_Step(t,pI);
        }
    }
    //cout << "IN" << "\t" << pI->K1 << endl;
    //pI->K1 = 1;
    //cout << "OUT" <<"\t" << pI->K1 << endl;
}

#endif /* Simulator_hpp */
