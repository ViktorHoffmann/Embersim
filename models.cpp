#include "Embersim.h"

// single-valued constants
double g = 9.80665;                                                             // Gravitational acceleration at sea level              [m/s^2]
double M = 0.0289644;                                                           // Molar mass of earths air                             [kg/mol]
double Ru = 8.3144598;                                                          // Universal gas constant                               [J/(mol*K)]
double Rs = 287.058;                                                            // Specific gas constant                                [J/(kg*K)]

// multi-valued constants
double P[7] = { 101325,22632.10,5474.89,868.02,110.91,66.94,3.96 };             // Static pressure at bottom of atmospheric layer       [Pa]
double T[7] = { 288.15,216.65,216.65,228.65,270.65,270.65,214.65 };             // Standard temperature at bottom of atmospheric layer  [K]
double L[7] = { -0.0065,0,0.001,0.0028,0,-0.0028,-0.002 };                      // Standard temperature lapse rate                      [K/m]
double h[7] = { 0,11000,20000,32000,47000,51000,71000 };                        // Altitude at bottom of atmospheric layer              [m]

double atm_pres_model(double alt) {
	// Using barometric formula,
	// this absolute atmospheric pressure model
	// returns pressure and density approximation in
	// pascal and rho for given altitude.

	double atm_pres; //Pa
	if (alt >= h[0] && alt < h[1])
	{
		int i = 0;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[1] && alt < h[2])
	{
		// Temperature lapse rate is zero
		int i = 1;
		return atm_pres = P[i] * exp((((g * (-1)) * M * (alt - h[i])) / (Ru * T[i])));
	}
	if (alt >= h[2] && alt < h[3])
	{
		int i = 2;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[3] && alt < h[4])
	{
		int i = 3;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[4] && alt < h[5])
	{
		// Temperature lapse rate is zero
		int i = 4;
		return atm_pres = P[i] * exp((((g * (-1)) * M * (alt - h[i])) / (Ru * T[i])));
	}
	if (alt >= h[5] && alt < h[6])
	{
		int i = 5;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	if (alt >= h[6])
	{
		int i = 6;
		return atm_pres = P[i] * pow((T[i] / (T[i] + L[i] * (alt - h[i]))), ((g * M) / (Ru * L[i])));
	}
	else if (alt < h[0])
	{
		std::cout << "\u001b[31merror:\u001b[0m Altitude must be positive\n";
		return 0;
	}
	else
	{
		std::cout << "\u001b[31merror\u001b[0m\n";
		return 0;
	}
}

double atm_temp_model(double alt) {
	// The function uses the Standard temperature
	// and temperature lapse rate to model the
	// absolute atmospheric temperature as linear functions

	double atm_temp; //K
	if (alt >= h[0] && alt < h[1])
	{
		int i = 0;
		return atm_temp = T[i] + (alt * L[i]);
	}
	if (alt >= h[1] && alt < h[2])
	{
		int i = 1;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[2] && alt < h[3])
	{
		int i = 2;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[3] && alt < h[4])
	{
		int i = 3;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[4] && alt < h[5])
	{
		int i = 4;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[5] && alt < h[6])
	{
		int i = 5;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt >= h[6])
	{
		int i = 6;
		return atm_temp = T[i] + ((alt - h[i]) * L[i]);
	}
	if (alt < h[0])
	{
		std::cout << "\u001b[31merror:\u001b[0m Altitude must be positive\n";
	}
	else
	{
		std::cout << "\u001b[31merror\u001b[0m\n";
		return 0;
	}
	return 0;
}

double atm_dens_model(double alt) {
	// Calculation of atmospheric density

	double atm_dens; //rho
	return atm_dens = (atm_pres_model(alt) / (Rs * atm_temp_model(alt)));
}

double dyn_pres_model(double vel, double alt) {
	// This function calculates the dynamic pressure
	// with velocity and atmospheric density

	double dyn_pres; //Pa
	return dyn_pres = ((atm_dens_model(alt) * pow(vel, 2)) / 2);
}

void calcModel(std::string Input_file) {

	std::string Output_file = "aerodynamics.csv";
	std::vector<altvel> altvel = read_csv(Input_file);

	// initialize Header row
	std::vector<std::string> Header_row;
	Header_row.push_back("Altitude [m]");
	Header_row.push_back("Velocity [m/s]");
	Header_row.push_back("Temperature [K]");
	Header_row.push_back("Static Pressure [Pa]");
	Header_row.push_back("Static Density [kg/m^3]");
	Header_row.push_back("Dynamic Pressure [Pa]");

	// sim loop
	std::vector<Output_data> Output;
	for (int i = 0; i < altvel.size(); i++) {
		Output_data Output_tmp = { altvel[i].alt,
			altvel[i].vel,
			atm_temp_model(altvel[i].alt),
			atm_pres_model(altvel[i].alt),
			atm_dens_model(altvel[i].alt),
			dyn_pres_model(altvel[i].vel,altvel[i].alt) };
		Output.push_back(Output_tmp);
	}

	write_csv(Output_file, Header_row, Output);

}