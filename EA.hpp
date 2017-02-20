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
    int binary_select();
    void mutation(Individual &M);
    void natural_selection();
    void Run_Program();
    
    //Statistics
    vector<double> best_fitness;            //keeps track of the best individuals fitness for each generation
    vector<double> sys_design;              //keeps track of the best individuals design for each generation
    
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


//-------------------------------------------------------------------------
//randomly selects two individuals and decides which one will die based on their fitness
int EA::binary_select()
{
    int loser;
    int index_1 = rand() % agent.size();
    int index_2 = rand() % agent.size();
    while (index_1 == index_2)
    {
        index_2 = rand() % agent.size();
    }
    if(agent.at(index_1).fitness < agent.at(index_2).fitness)
    {
        loser = index_2;
        //cout << "loser" << "\t" <<  "agent" << "\t" << index_2 << endl;
    }
    else
    {
        loser = index_1;
        //cout << "loser" << "\t" <<  "agent" << "\t" << index_1 << endl;
    }
    return loser;
}


//-------------------------------------------------------------------------
//mutates the copies of the winning individuals
void EA::mutation(Individual &M)
{
    double random = ((double)rand()/RAND_MAX);
    if (random <= pP->mutation_rate)
    {
        double R1 = ((double)rand()/RAND_MAX) * pP->K1_range;
        double R2 = ((double)rand()/RAND_MAX) * pP->K1_range;
        M.K1 = M.K1 + (R1-R2);
    }
}


//-------------------------------------------------------------------------
//runs the entire natural selectiona dn mutation process
void EA::natural_selection()
{
    int kill;
    for(int k=0; k<pP->to_kill; k++)
    {
        kill = binary_select();
        agent.erase(agent.begin() + kill);
    }
    
    int to_replicate = pP->to_kill;
    for (int rep=0; rep<to_replicate; rep++)
    {
        Individual M;
        int spot = rand() % agent.size();
        M = agent.at(spot);
        //cout << "cp" << endl;
        mutation(M);
        agent.push_back(M);
        agent.at(agent.size()-1).age = 0;
    }
}


//-------------------------------------------------------------------------
//Runs the entire program
void EA::Run_Program()
{
    Build_Population();
    for (int gen=0; gen<pP->gen_max; gen++)
    {
        Run_Simulation();
        cout << "Acceleration" << endl;
        for (int s=0; s<agent.at(0).y1.size(); s++)
        {
            cout << agent.at(0).accel.at(s) << "\t";
        }
        cout << endl;
        cout << endl;
        cout << "Y1" << endl;
        for (int s=0; s<agent.at(0).y1.size(); s++)
        {
            cout << agent.at(0).y1.at(s) << "\t";
        }
        cout << endl;
        cout << endl;
        cout << "Y1 DOT" << endl;
        for (int s=0; s<agent.at(0).y1_d.size(); s++)
        {
            cout << agent.at(0).y1_d.at(s) << "\t";
        }
        cout << endl;
        cout << endl;
        cout << "Y2" << endl;
        for (int s=0; s<agent.at(0).y2.size(); s++)
        {
            cout << agent.at(0).y2.at(s) << "\t";
        }
        cout << endl;
        cout << endl;
        cout << "Y2 DOT" << endl;
        for (int s=0; s<agent.at(0).y2_d.size(); s++)
        {
            cout << agent.at(0).y2_d.at(s) << "\t";
        }
        cout << endl;
        cout << endl;
        cout << "DELTA Y" << endl;
        for (int s=0; s<agent.at(0).del_y.size(); s++)
        {
            cout << agent.at(0).del_y.at(s) << "\t";
        }
        cout << endl;
        cout << endl;
        natural_selection();
    }
}

#endif /* EA_hpp */
