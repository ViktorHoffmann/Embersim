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
// initialize altvel struct for input vector
struct altvel {
	double alt, vel;
};
// initialize Output_data struct for output vector
struct Output_data {
	double alt, vel, atm_temp, atm_pres, atm_dens, dyn_pres;
};

std::string				find_data_path(void);
int						file_len(std::string Input_file);
std::vector<altvel>		read_csv(std::string Input_file);
int						write_csv(std::string Output_file, std::vector<std::string> Header_row, std::vector<Output_data> Output_data);

#endif // !EMBERSIM_H_