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
    void Get_New_x(double t, int ts, Individual* pI);
    void Get_New_y2(double t, int ts, Individual* pI);
    void Get_New_y2_d(double t, int ts, Individual* pI);
    void Get_New_Accel(double t, int ts, Individual* pI);
    void Get_New_y1(double t, int ts, Individual* pI);
    void Get_New_y1_d(double t, int ts, Individual* pI);
    void Run_Time_Step(double t, int ts, Individual* pI);
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
//Gets the new x
void Simulator::Get_New_x(double t, int ts, Individual* pI)
{
    pI->x.push_back(pI->x.at(ts-1)+pP->delta_t);
}

//-------------------------------------------------------------------------
//Gets the new acceleration
void Simulator::Get_New_Accel(double t, int ts, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y1
void Simulator::Get_New_y1(double t, int ts, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y1 dot
void Simulator::Get_New_y1_d(double t, int ts, Individual* pI)
{
    
}


//-------------------------------------------------------------------------
//Gets the new y2
void Simulator::Get_New_y2(double t, int ts, Individual* pI)
{
    int pi = 3.14159;
    double A = pP->amp*sin((2*pi)/(pP->travel_speed*pP->period));
    double B = pI->x.at(ts-1);
    double C = pP->travel_speed*pP->delta_t;
    double D = pP->travel_speed*t;
    pI->y2.push_back(A*(B+C-D));
}


//-------------------------------------------------------------------------
//Gets the new y2 dot
void Simulator::Get_New_y2_d(double t, int ts, Individual* pI)
{
    int pi = 3.14159;
    double A = pP->omega*pP->amp*cos((2*pi)/(pP->lamda));
    double B = pI->x.at(ts);
    double C = pP->travel_speed*t;
    pI->y2_d.push_back(A*(B+C));
}


//-------------------------------------------------------------------------
//Runs a single time step
void Simulator::Run_Time_Step(double t, int ts, Individual* pI)
{
    Get_New_x(t, ts, pI);
    Get_New_y2(t, ts, pI);
    Get_New_y2_d(t, ts, pI);
    Get_New_Accel(t, ts, pI);
    Get_New_y1(t, ts, pI);
    Get_New_y1_d(t, ts, pI);
}


//-------------------------------------------------------------------------
//Runs the entire simulation process
void Simulator::Simulate(Individual* pI)
{
    double t = 0;
    int ts = 0;
    while (t < pP->time_max)
    {
        if (t == 0)
        {
            Initialize_Agent(pI);
        }
        if (t > 0)
        {
            Run_Time_Step(t, ts, pI);
        }
        ts += 1;
        t += pP->delta_t;
    }
    //cout << "IN" << "\t" << pI->K1 << endl;
    //pI->K1 = 1;
    //cout << "OUT" <<"\t" << pI->K1 << endl;
}

#endif /* Simulator_hpp */
