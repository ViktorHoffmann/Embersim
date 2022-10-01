#pragma once

#ifndef EMBERSIM_H_
#define EMBERSIM_H_

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
//#include <chrono>
//#include <thread>
#include <stdlib.h>

// Aerodynamics
double atm_pres_model(double alt);
double atm_temp_model(double alt);
double atm_dens_model(double alt);
double dyn_pres_model(double vel, double alt);

// File management
std::string find_data_path(void);
int read_csv(std::string Input_file);
void write_csv(std::string Output_file);

#endif // !EMBERSIM_H_