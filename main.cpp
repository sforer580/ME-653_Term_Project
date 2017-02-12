//
//  main.cpp
//  Vibrations_Term_Project
//
//  Created by Scott S Forer on 2/2/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

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

#include "Parameters.hpp"
#include "Individual.hpp"
#include "Simulator.hpp"
#include "EA.hpp"

int main()
{
    srand(time(NULL));
    Parameters P;
    Simulator S;
    EA E;
    E.pP = &P;
    E.Run_Program();
}
