#include "Embersim.h"

std::vector<double> alt;		                                                // Altitude        [m]
std::vector<double> vel;                                                        // Velocity        [m/s]

std::string find_data_path(void) {
	//return path of "data" folder inside of Embersim folder

	std::string working_dir_path = std::filesystem::current_path().string();
	std::size_t win_path_pos = working_dir_path.find("Embersim\\");
	std::size_t lin_path_pos = working_dir_path.find("Embersim/");

	if (win_path_pos != std::string::npos) {
		std::string data_dir_path = working_dir_path.erase(win_path_pos) + "Embersim\\data\\";
		return data_dir_path;
	}
	if (lin_path_pos != std::string::npos) {
		std::string data_dir_path = working_dir_path.erase(lin_path_pos) + "Embersim/data/";
		return data_dir_path;
	}
	else {
		std::cout << "error: couldn't find data directory" << std::endl;
	}
}

int read_csv(std::string Input_file) {
	// This function reads the .csv columns

	std::ifstream Infile;
	Infile.open(find_data_path() + Input_file);

	if (!Infile.good()) {
		std::cerr << "error: can't open input file\n" << std::endl;
		return 1;
	}
	
	std::cout << "Reading csv...\n";

	int i = 0; int j = 0;
	while (Infile.good()) {
		std::string line;
		// Read whole line
		while (getline(Infile, line))
		{
			std::istringstream iline(line);
			// Seperate line by the delimiter
			while (getline(iline, line, ';'))
			{
				if (j == 1)
				{
					// Column 2: velocity
					vel.push_back(strtod(line.c_str(), NULL));
					i++; j--;
				}
				else if (j == 0)
				{
					// Column 1: altitude
					alt.push_back(strtod(line.c_str(), NULL));
					i++; j++;
				}
			}
		}
	}
	std::cout << (alt.size() * (vel.size() <= alt.size()) + (vel.size() * (vel.size() > alt.size()))) << " lines and ";
	std::cout << (alt.size() + vel.size()) << " elements parsed\n";
	std::cout << "Reading done\n";
	return 0;
}

void write_csv(std::string Output_file) {
	// This function runs the simulation loop
	// and parses the solutions to the output .csv file.

	std::cout << "Printing to csv...\n";

	std::ofstream Outfile;
	Outfile.open(find_data_path() + Output_file);

	if (!Outfile.good()) {
		std::cerr << "error: can't open output file\n" << std::endl;
		return;
	}

	Outfile << "Altitude [m]" << ";" << "Velocity [m/s]" << ";" << "Temperature [K]"
		<< ";" << "Static Pressure [Pa]" << ";" << "Static Density [kg/m^3]" << ";" << "Dynamic Pressure [Pa]" << "\n";

	//Simulation loop
	for (int i = 0; i < (alt.size() * (vel.size() <= alt.size()) + (vel.size() * (vel.size() > alt.size()))); i++)
	{
		Outfile << alt[i] << ";" << vel[i] << ";" << atm_temp_model(alt[i]) << ";" << atm_pres_model(alt[i]) << ";" << atm_dens_model(alt[i]) << ";" << dyn_pres_model(vel[i], alt[i]) << "\n";
	}
	Outfile.close();

	std::cout << "Printing done\n";
}