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
    struct less_than_agent_fitness;
    void sort_indivduals_fitness();
    void Reset_Population();
    void Debug();
    void Clear_Population();
    void Run_Program();
    
    //Statistics
    vector<double> y1;
    vector<double> y1_d;
    vector<double> y1_dd;
    vector<double> y2;
    vector<double> y2_d;
    vector<double> y2_dd;
    vector<double> x;
    vector<double> del_y;
    vector<double> best_fitness;            //keeps track of the best individuals fitness for each generation
    vector<double> sys_design;              //keeps track of the best individuals design for each generation
    
    void Delete_Text_Files();
    void Store_Simulation_Data();
    void Write_Parameters_To_txt_File();
    void Store_Best_Individual();
    void Write_Best_Fitness_To_txt_File();
    void Write_Best_Individual_To_txt_File();
    void Run_Text_files();
    
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
        //cout << "AFTER" << "\t" << agent.at(i).fitness << endl;      //note that agent information is changed in simulation
    }
}


//-------------------------------------------------------------------------
//Randomly selects two individuals and decides which one will die based on their fitness
int EA::binary_select()
{
    int loser;
    int index_1 = rand() % agent.size();
    int index_2 = rand() % agent.size();
    while (index_1 == index_2)
    {
        index_2 = rand() % agent.size();
    }
    //winner is one with lower fitness
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
//Mutates the copies of the winning individuals
void EA::mutation(Individual &M)
{
    double random1 = ((double)rand()/RAND_MAX);
    if (random1 <= pP->mutation_rate)
    {
        double R1 = ((double)rand()/RAND_MAX) * pP->K1_range;
        double R2 = ((double)rand()/RAND_MAX) * pP->K1_range;
        M.K1 = M.K1 + (R1-R2);
        if (M.K1 < pP->K1_min)
        {
            M.K1 = pP->K1_min;
        }
        if (M.K1 > pP->K1_max)
        {
            M.K1 = pP->K1_max;
        }
    }
    
    double random2 = ((double)rand()/RAND_MAX);
    if (random2 <= pP->mutation_rate)
    {
        double R1 = ((double)rand()/RAND_MAX) * pP->K2_range;
        double R2 = ((double)rand()/RAND_MAX) * pP->K2_range;
        M.K2 = M.K2 + (R1-R2);
        if (M.K2 < pP->K2_min)
        {
            M.K2 = pP->K2_min;
        }
        if (M.K2 > pP->K2_max)
        {
            M.K2 = pP->K2_max;
        }
    }
    
    double random3 = ((double)rand()/RAND_MAX);
    if (random3 <= pP->mutation_rate)
    {
        double R1 = ((double)rand()/RAND_MAX) * pP->C1_range;
        double R2 = ((double)rand()/RAND_MAX) * pP->C1_range;
        M.C1 = M.C1 + (R1-R2);
        if (M.C1 < pP->C1_min)
        {
            M.C1 = pP->C1_min;
        }
        if (M.C1 > pP->C1_max)
        {
            M.C1 = pP->C1_max;
        }
    }
    
    double random4 = ((double)rand()/RAND_MAX);
    if (random4 <= pP->mutation_rate)
    {
        double R1 = ((double)rand()/RAND_MAX) * pP->C2_range;
        double R2 = ((double)rand()/RAND_MAX) * pP->C2_range;
        M.C2 = M.C2 + (R1-R2);
        if (M.C2 < pP->C2_min)
        {
            M.C2 = pP->C2_min;
        }
        if (M.C2 > pP->C2_max)
        {
            M.C2 = pP->C2_max;
        }
    }
}


//-------------------------------------------------------------------------
//Runs the entire natural selectiona dn mutation process
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
//Sorts the population based on their fitness from lowest to highest
struct EA::less_than_agent_fitness
{
    inline bool operator() (const Individual& struct1, const Individual& struct2)
    {
        return (struct1.fitness < struct2.fitness);
    }
};


//-------------------------------------------------------------------------
//Sorts population
void EA::sort_indivduals_fitness()
{
    for (int i=0; i<pP->num_indv; i++)
    {
        sort(agent.begin(), agent.end(), less_than_agent_fitness());
    }
}


//-------------------------------------------------------------------------
//Stores the best individual
void EA::Store_Best_Individual()
{
    best_fitness.push_back(agent.at(0).fitness);
    sys_design.clear();
    sys_design.push_back(agent.at(0).K1);
    sys_design.push_back(agent.at(0).K2);
    sys_design.push_back(agent.at(0).C1);
    sys_design.push_back(agent.at(0).C2);
}


//-------------------------------------------------------------------------
//Stores the data for the simulations
void EA::Store_Simulation_Data()
{
    for (int i=0; i<agent.at(0).y1.size(); i++)
    {
        y1.push_back(agent.at(0).y1.at(i));
        y1_d.push_back(agent.at(0).y1_d.at(i));
        y1_dd.push_back(agent.at(0).y1_dd.at(i));
        y2.push_back(agent.at(0).y2.at(i));
        y2_d.push_back(agent.at(0).y2_d.at(i));
        y2_dd.push_back(agent.at(0).y2_dd.at(i));
        x.push_back(agent.at(0).x.at(i));
        del_y.push_back(agent.at(0).del_y.at(i));
    }
}


//-------------------------------------------------------------------------
//Writes the parameters to txt files
void EA::Write_Parameters_To_txt_File()
{
    ofstream File1;
    File1.open("Parameters.txt");
    File1 << "EA Parameters" << endl;
    File1 << "--------------------------" << endl;
    File1 << "Number of individual" << "\t" << pP->num_indv << endl;
    File1 << "Number of generations" << "\t" << endl;
    File1 << "Mutation rate" << "\t" << pP->mutation_rate << endl;
    File1 << "To kill" << "\t" << pP->to_kill << endl;
    File1 << "Spring Length" << "\t" << pP->spring_free_length << "\t" << "[meters]" << endl;
    File1 << "K1 min" << "\t" << pP->K1_min << "\t" << "[Newton/meters]" << endl;
    File1 << "K1 max" << "\t" << pP->K1_max << "\t" << "[Newton/meters]" << endl;
    File1 << "K1 range" << "\t" << pP->K1_range << "\t" << "[Newton/meters]" << endl;
    File1 << "K2 min" << "\t" << pP->K2_min << "\t" << "[Newton/meters]" << endl;
    File1 << "K2 max" << "\t" << pP->K2_max << "\t" << "[Newton/meters]" << endl;
    File1 << "K2 range" << "\t" << pP->K2_range << "\t" << "[Newton/meters]" << endl;
    File1 << "C1 min" << "\t" << pP->C1_min << "\t" << "[kilogram/second]" << endl;
    File1 << "C1 max" << "\t" << pP->C1_max << "\t" << "[kilogram/second]" << endl;
    File1 << "C1 range" << "\t" << pP->C1_range << "\t" << "[kilogram/second]" << endl;
    File1 << "C2 min" << "\t" << pP->C2_min << "\t" << "[kilogram/second]" << endl;
    File1 << "C2 max" << "\t" << pP->C2_max << "\t" << "[kilogram/second]" << endl;
    File1 << "C2 range" << "\t" << pP->C2_range << "\t" << "[kilogram/second]" << endl;
    File1 << "Mass" << "\t" << pP->mass << "\t" << "[kilogram]" << endl;
    File1 << endl;
    
    File1 << "Simulator Parameters" << endl;
    File1 << "--------------------------" << endl;
    File1 << "Simulation time" << "\t" << pP->time_max << "\t" << "[seconds]" << endl;
    File1 << "Sampling time" << "\t" << pP->delta_t << "\t" << "[seconds]" << endl;
    File1 << "Delta X" << "\t" << pP->delta_x << "\t" << "[meters]" << endl;
    File1 << "Wave Parameters" << endl;
    File1 << "Wave 1" << endl;
    File1 << "Input amplitude" << "\t" << pP->amp_1 << "\t" << "[meters]" << endl;
    File1 << "Input period" << "\t" << pP->period_1 << "\t" << "[seconds]" << endl;
    File1 << "Wavelength" << "\t" << pP->lamda_1 << "\t" << "[meters]" << endl;
    File1 << "Wave frequency" << "\t" << pP->freq_1 << "\t" << "[hertz]" << endl;
    File1 << "Wave travel speed" << "\t" << pP->travel_speed_1 << "\t" << "[meters/second]" << endl;
    File1 << "Omega" << "\t" << pP->omega_1 << "\t" << "[radians/second]" << endl;
    File1 << "Wave 2" << endl;
    File1 << "Input amplitude" << "\t" << pP->amp_2 << "\t" << "[meters]" << endl;
    File1 << "Input period" << "\t" << pP->period_2 << "\t" << "[seconds]" << endl;
    File1 << "Wavelength" << "\t" << pP->lamda_2 << "\t" << "[meters]" << endl;
    File1 << "Wave frequency" << "\t" << pP->freq_2 << "\t" << "[hertz]" << endl;
    File1 << "Wave travel speed" << "\t" << pP->travel_speed_2 << "\t" << "[meters/second]" << endl;
    File1 << "Omega" << "\t" << pP->omega_2 << "\t" << "[radians/second]" << endl;
    File1 << endl;
    if (pP->normal_wave == 0)
    {
        File1 << "Normal Wave Experiment OFF" << endl;
    }
    if (pP->normal_wave == 1)
    {
        File1 << "Normal Wave Experiment ON" << endl;
    }
    if (pP->bumpy_wave == 0)
    {
        File1 << "Bumpy Wave Experiment OFF" << endl;
    }
    if (pP->bumpy_wave == 1)
    {
        File1 << "Bumpy Wave Experiment ON" << endl;
    }
    File1.close();
}


//-------------------------------------------------------------------------
//Writes the best fitness for each generation to a txt file
void EA::Write_Best_Fitness_To_txt_File()
{
    ofstream File2;
    File2.open("Best_Fitness.txt", ios_base::app);
    for (int s=0; s<best_fitness.size(); s++)
    {
        File2 << best_fitness.at(s) << "\t";
    }
    best_fitness.clear();
    File2 << endl;
    File2.close();
}


//-------------------------------------------------------------------------
//Writes the best individual to txt files
void EA::Write_Best_Individual_To_txt_File()
{
    ofstream File3;
    File3.open("Best_System_Design.txt", ios_base::app);
    File3 << sys_design.at(0) << "\t";
    File3 << sys_design.at(1) << "\t";
    File3 << sys_design.at(2) << "\t";
    File3 << sys_design.at(3) << "\t";
    File3 << endl;
    File3.close();
    
    ofstream File4;
    File4.open("Best_Individual_y1.txt");
    for (int s=0; s<agent.at(0).y1.size(); s++)
    {
        File4 << agent.at(0).y1.at(s) << "\t";
    }
    File4 << endl;
    File4.close();
    
    ofstream File5;
    File5.open("Best_Individual_y1_d.txt");
    for (int s=0; s<agent.at(0).y1_d.size(); s++)
    {
        File5 << agent.at(0).y1_d.at(s) << "\t";
    }
    File5 << endl;
    File5.close();
    
    ofstream File6;
    File6.open("Best_Individual_y1_dd.txt");
    for (int s=0; s<agent.at(0).y1_dd.size(); s++)
    {
        File6 << agent.at(0).y1_dd.at(s) << "\t";
    }
    File6 << endl;
    File6.close();
    
    ofstream File7;
    File7.open("Best_Individual_y2.txt");
    for (int s=0; s<agent.at(0).y2.size(); s++)
    {
        File7 << agent.at(0).y2.at(s) << "\t";
    }
    File7 << endl;
    File7.close();
    
    ofstream File8;
    File8.open("Best_Individual_y2_d.txt");
    for (int s=0; s<agent.at(0).y2_d.size(); s++)
    {
        File8 << agent.at(0).y2_d.at(s) << "\t";
    }
    File8 << endl;
    File8.close();
    
    ofstream File9;
    File9.open("Best_Individual_y2_dd.txt");
    for (int s=0; s<agent.at(0).y2_dd.size(); s++)
    {
        File9 << agent.at(0).y2_dd.at(s) << "\t";
    }
    File9 << endl;
    File9.close();
    
    ofstream File10;
    File10.open("Best_Individual_x.txt");
    for (int s=0; s<agent.at(0).x.size(); s++)
    {
        File10 << agent.at(0).x.at(s) << "\t";
    }
    File10 << endl;
    File10.close();
    
    ofstream File11;
    File11.open("Best_Individual_del_y.txt");
    for (int s=0; s<agent.at(0).del_y.size(); s++)
    {
        File11 << agent.at(0).del_y.at(s) << "\t";
    }
    File11 << endl;
    File11.close();
}


//-------------------------------------------------------------------------
//Runs the text files
void EA::Run_Text_files()
{
    Write_Best_Fitness_To_txt_File();
    Write_Best_Individual_To_txt_File();
    Write_Parameters_To_txt_File();
}


//-------------------------------------------------------------------------
//Resets the population
void EA::Reset_Population()
{
    for (int i=0; i<pP->num_indv; i++)
    {
        agent.at(i).y1.clear();
        agent.at(i).y1_d.clear();
        agent.at(i).y1_dd.clear();
        agent.at(i).y2.clear();
        agent.at(i).y2_d.clear();
        agent.at(i).y2_dd.clear();
        agent.at(i).x.clear();
        agent.at(i).del_y.clear();
        agent.at(i).fitness = 0;
    }
}


//-------------------------------------------------------------------------
//For Debugging purposes
void EA::Debug()
{
    /*
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
     cout << "Y1 DOUBLE DOT" << endl;
     for (int s=0; s<agent.at(0).y1_dd.size(); s++)
     {
     cout << agent.at(0).y1_dd.at(s) << "\t";
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
     cout << "Y2 DOUBLE DOT" << endl;
     for (int s=0; s<agent.at(0).y2_dd.size(); s++)
     {
     cout << agent.at(0).y2_dd.at(s) << "\t";
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
     */
}


//-------------------------------------------------------------------------
//Clears the population for the next stat run
void EA::Clear_Population()
{
    agent.clear();
    /*
    y1.clear();
    y1_d.clear();
    y1_dd.clear();
    y2.clear();
    y2_d.clear();
    y2_dd.clear();
    x.clear();
    del_y.clear();
    */
}


//-------------------------------------------------------------------------
//Deltes the text files
void EA::Delete_Text_Files()
{
    //
    if( remove( "Best_Fitness.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Fitness" );
    else
        puts( "Best_Fitness FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_del_y.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_del_y" );
    else
        puts( "Best_Individual_del_y FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_x.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_x" );
    else
        puts( "Best_Individual_x FILE SUCCESSFULLYDELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_y1.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_y1" );
    else
        puts( "Best_Individual_y1 FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_y1_d.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_y1_d" );
    else
        puts( "Best_Individual_y1_d FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_y1_dd.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_y1_dd" );
    else
        puts( "Best_Individual_y1_dd FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_y2.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_y2" );
    else
        puts( "Best_Individual_y2 FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_y2_d.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_y2_d" );
    else
        puts( "Best_Individual_y2_d FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_Individual_y2_dd.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_Individual_y2_dd" );
    else
        puts( "Best_Individual_y2_dd FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Best_System_Design.txt" ) != 0 )
        perror( "ERROR DELETING FILE Best_System_Design" );
    else
        puts( "Best_System_Design FILE SUCCESSFULLY DELETED" );
    cout << endl;
    //
    if( remove( "Parameters.txt" ) != 0 )
        perror( "ERROR DELETING FILE Parameters" );
    else
        puts( "Parameters FILE SUCCESSFULLY DELETED" );
    cout << endl;
}


//-------------------------------------------------------------------------
//Runs the entire program
void EA::Run_Program()
{
    Delete_Text_Files();
    for (int sr=0; sr<pP->num_sr; sr++)
    {
        Build_Population();
        for (int gen=0; gen<pP->gen_max; gen++)
        {
            if (gen % 100 == 0)
            {
                cout << "SR" << "\t" << sr << "::" << gen << endl;
            }
            if (gen < pP->gen_max-1)
            {
                Run_Simulation();
                Debug();
                sort_indivduals_fitness();
                Store_Best_Individual();
                //cout << "BEST FITNESS" << endl;
                //cout << agent.at(0).fitness << endl;
                natural_selection();
                Reset_Population();
            }
            else
            {
                Run_Simulation();
                Debug();
                sort_indivduals_fitness();
                Store_Best_Individual();
                //Store_Simulation_Data();
                Run_Text_files();
                cout << "FINAL GENERATION" << endl;
                cout << "BEST FITNESS" << endl;
                cout << agent.at(0).fitness << endl;
                /*
                 for (int i=0; i<agent.at(0).del_y.size(); i++)
                 {
                 cout << agent.at(0).del_y.at(i) << "\t";
                 }
                 */
            }
        }
        Clear_Population();
    }
}

#endif /* EA_hpp */
