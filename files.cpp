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

int file_len(std::string Input_file) {
	// Returns row number of file without the header row
	std::ifstream Infile;
	Infile.open(find_data_path() + Input_file);

	if (!Infile.good()) {
		std::cout << "\u001b[31merror:\u001b[0m can't open input file\n" << std::endl;
		return 1;
	}

	int rows = 0;
	while (Infile.good()) {
		std::string line;
		while (getline(Infile, line)) {
			std::istringstream iline(line);
			while (getline(iline, line, '\n')) {
				rows++;
			}
		}
	}
	return rows;
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
	/* todo:
		- function takes output file as string, header row as array and data struct vector
	*/

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