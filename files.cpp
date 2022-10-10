#include "Embersim.h"

std::string find_data_path(void) {
	//return path of "data" folder inside of Embersim folder

	std::string working_dir_path = std::filesystem::current_path().string();
	std::size_t win_path_pos = working_dir_path.find("Embersim\\");

	if (win_path_pos != std::string::npos) {
		std::string data_dir_path = working_dir_path.erase(win_path_pos) + "Embersim\\data\\";
		return data_dir_path;
	}

	std::size_t lin_path_pos = working_dir_path.find("Embersim/");
	if (lin_path_pos != std::string::npos) {
		std::string data_dir_path = working_dir_path.erase(lin_path_pos) + "Embersim/data/";
		return data_dir_path;
	}
	else {
		std::cout << "\u001b[31merror:\u001b[0m couldn't find data directory" << std::endl;
		return "";
	}
	return "";
}


std::vector<Output_data> find_max(std::string Input_file) {
	//todo:
	//	- find max in all columns
	//	- find timestamp of each max
	//	- return vector as		Output_data | Output_data | Output_data ... (unit)
	//								    123 |	      456 |		    789	... (time)

	std::ifstream Infile;
	Infile.open(find_data_path() + Input_file);

	if (!Infile.good()) {
		std::cout << itfAnsi("red", "zero", "zero", "error: ") << "can't read file\n" << std::endl;
	}

	double max_alt = 0, max_vel = 0, max_atm_temp = 0, max_atm_pres = 0, max_atm_dens = 0, max_dyn_pres = 0;
	int max_alt_stamp, max_vel_stamp, max_atm_temp_stamp, max_atm_pres_stamp, max_atm_dens_stamp, max_dyn_pres_stamp;
	std::vector<Output_data> result;
	Output_data result_tmp;

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
				if (j == 5) {
					if (max_dyn_pres < strtod(line.c_str(), NULL)) {
						max_dyn_pres = strtod(line.c_str(), NULL);
						max_dyn_pres_stamp = i;
					}
					i++;  j = 0;
				}
				else if (j == 4) {
					if (max_atm_dens < strtod(line.c_str(), NULL)) {
						max_atm_dens = strtod(line.c_str(), NULL);
						max_atm_dens_stamp = i;
					}
					j++;
				}
				else if (j == 3) {
					if (max_atm_pres < strtod(line.c_str(), NULL)) {
						max_atm_pres = strtod(line.c_str(), NULL);
						max_atm_pres_stamp = i;
					}
					j++;
				}
				else if (j == 2) {
					if (max_atm_temp < strtod(line.c_str(), NULL)) {
						max_atm_temp = strtod(line.c_str(), NULL);
						max_atm_temp_stamp = i;
					}
					j++;
				}
				else if (j == 1)
				{
					// Col 2: vel
					if (max_vel < strtod(line.c_str(), NULL)) {
						max_vel = strtod(line.c_str(), NULL);
						max_vel_stamp = i;
					}
					j++;
				}
				else if (j == 0)
				{
					// Col 1: alt
					if (max_alt < strtod(line.c_str(), NULL)) {
						max_alt = strtod(line.c_str(), NULL);
						max_alt_stamp = i;
					}
					j++;
				}
			}
		}
	}

	result_tmp.alt = max_alt;
	result_tmp.vel = max_vel;
	result_tmp.atm_temp = max_atm_temp;
	result_tmp.atm_pres = max_atm_pres;
	result_tmp.atm_dens = max_atm_dens;
	result_tmp.dyn_pres = max_dyn_pres;
	result.push_back(result_tmp);

	result_tmp.alt = max_alt_stamp;
	result_tmp.vel = max_vel_stamp;
	result_tmp.atm_temp = max_atm_temp_stamp;
	result_tmp.atm_pres = max_atm_pres_stamp;
	result_tmp.atm_dens = max_atm_dens_stamp;
	result_tmp.dyn_pres = max_dyn_pres_stamp;
	result.push_back(result_tmp);

	return result;
}

std::vector<altvel> read_csv(std::string Input_file) {
	// This function reads the .csv columns

	std::ifstream Infile;
	Infile.open(find_data_path() + Input_file);

	if (!Infile.good()) {
		std::cout << "\u001b[31merror:\u001b[0m can't open input file\n" << std::endl;
	}

	std::vector<double> vel_tmp;
	std::vector<double> alt_tmp;
	std::vector<altvel> altvel_tmp;

	std::cout << "Reading csv...\n";
	//todo: if csv header found skip it
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
					vel_tmp.push_back(strtod(line.c_str(), NULL));
					i++; j--;
				}
				else if (j == 0)
				{
					// Column 1: altitude
					alt_tmp.push_back(strtod(line.c_str(), NULL));
					j++;
				}
			}
		}
	}

	for (int i = 0; i < alt_tmp.size(); i++) {
		altvel isaltvel = {alt_tmp[i], vel_tmp[i]};
		altvel_tmp.push_back(isaltvel);
	}

	std::cout << "Reading done!\n";
	return altvel_tmp;
}

int write_csv(std::string Output_file, std::vector<std::string> Header_row, std::vector<Output_data> Output) {
	// This function parses the solutions to the output .csv file.

	std::ofstream Outfile;
	Outfile.open(find_data_path() + Output_file);

	if (!Outfile.good()) {
		std::cout << "\u001b[31merror:\u001b[0m can't open output file\n" << std::endl;
		return 1;
	}

	std::cout << "Printing to csv...\n";
	// parse .csv header row
	for (int i = 0; i < Header_row.size(); i++) {
		Outfile << Header_row[i] << ";";
	}
	Outfile << "\n";
	// parse Data matrix
	for (int i = 0; i < Output.size(); i++) {
		Outfile << Output[i].alt << ";"
			<< Output[i].vel << ";"
			<< Output[i].atm_temp << ";"
			<< Output[i].atm_pres << ";"
			<< Output[i].atm_dens << ";"
			<< Output[i].dyn_pres;
		Outfile << "\n";
	}

	Outfile.close();
	std::cout << "Printing done!\n";
	return 0;
}