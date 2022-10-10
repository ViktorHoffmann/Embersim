#include "Embersim.h"

int main() {
	itfStartup();

	std::string userIn = itfCommand();

	while (userIn.compare("-x")) {
		if (!userIn.compare("-h")) {
			itfStartup();
		}

		else if (!userIn.compare("-c") && userIn.length() == 2) {
			std::cout << "select the file to read from the data folder:" << std::endl;
			std::string path = find_data_path();
			for (const auto& entry : std::filesystem::directory_iterator(path)) {
				std::cout << entry.path() << std::endl;
			}

			std::string file = itfCommand();
			calcModel(file);
		}

		else if (!userIn.compare("-c -v") && userIn.length() == 5) {
			std::cout << "select the file to read from the data folder:" << std::endl;
			std::string path = find_data_path();
			for (const auto& entry : std::filesystem::directory_iterator(path)) {
				std::cout << entry.path() << std::endl;
			}

			std::string Output_file = "cal_result.csv";
			std::string file = itfCommand();
			calcModel(file);
			std::vector<Output_data> max = find_max(Output_file);

			std::cout << itfAnsi("red", "zero", "zero", "Max Altitude:            ") << max[0].alt << itfAnsi("red", "zero", "zero", " at time stamp ") << max[1].alt << std::endl;
			std::cout << itfAnsi("red", "zero", "zero", "Max Velocity:            ") << max[0].vel << itfAnsi("red", "zero", "zero", " at time stamp ") << max[1].vel << std::endl;
			std::cout << itfAnsi("red", "zero", "zero", "Max Ambient temperature: ") << max[0].atm_temp << itfAnsi("red", "zero", "zero", " at time stamp ") << max[1].atm_temp << std::endl;
			std::cout << itfAnsi("red", "zero", "zero", "Max Static pressure:     ") << max[0].atm_pres << itfAnsi("red", "zero", "zero", " at time stamp ") << max[1].atm_pres << std::endl;
			std::cout << itfAnsi("red", "zero", "zero", "Max Static density:      ") << max[0].atm_dens << itfAnsi("red", "zero", "zero", " at time stamp ") << max[1].atm_dens << std::endl;
			std::cout << itfAnsi("red", "zero", "zero", "Max Dynamic pressure:    ") << max[0].dyn_pres << itfAnsi("red", "zero", "zero", " at time stamp ") << max[1].dyn_pres << std::endl;
		}

		else {
			std::cout << itfAnsi("red", "zero", "zero", "unknown command") << std::endl;
		}

		userIn = itfCommand();
	}
	std::cout << itfAnsi("red", "zero", "zero", "closing") << std::endl;
	return 0;
}