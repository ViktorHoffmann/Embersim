#include "Embersim.h"

void itfClrscr(void) {
	// clear screen
	std::cout << "\033[2J\033[1;1H";
}

std::string itfAnsi(std::string fg, std::string o1, std::string o2, std::string text) {
	// returns same string with given Ansi escape sequence
	// supported colors: black, red, green, yellow, blue, magenta, cyan, white, zero
	// supported options: bold, underline, blink, frame, zero
	// zero will ignore option

	int x, y, z;

	if (!fg.compare("zero"))		{x = 0;}
	else if (!fg.compare("black"))	{x = 30;}
	else if (!fg.compare("red"))	{x = 31;}
	else if (!fg.compare("green"))	{x = 32;}
	else if (!fg.compare("yellow"))	{x = 33;}
	else if (!fg.compare("blue"))	{x = 34;}
	else if (!fg.compare("magenta")){x = 35;}
	else if (!fg.compare("cyan"))	{x = 36;}
	else if (!fg.compare("white"))	{x = 37;}
	else {
		return "\u001b[31merror:\u001b[0m unsupported color code";
	}

	if (!o1.compare("zero"))			{y = 0;}
	else if (!o1.compare("bold"))		{y = 1;}
	else if (!o1.compare("underline"))	{y = 4;}
	else if (!o1.compare("blink"))		{y = 5;}
	else if (!o1.compare("frame"))		{y = 51;}
	else {
		return "\u001b[31merror:\u001b[0m unsupported option code";
	}

	if (!o2.compare("zero"))			{z = 0;}
	else if (!o2.compare("bold"))		{z = 1;}
	else if (!o2.compare("underline"))	{z = 4;}
	else if (!o2.compare("blink"))		{z = 5;}
	else if (!o2.compare("frame"))		{z = 51;}
	else {
		return "\u001b[31merror:\u001b[0m unsupported option code";
	}

	if (x != 0 && y != 0 && z != 0) {
		// color and all options
		std::string tmp = "\u001b[" + std::to_string(x) + ";" + std::to_string(y) + ";" + std::to_string(z) + "m" + text + "\u001b[0m";
		return tmp;
	}

	if ((x != 0 && y != 0 && z == 0) || (x != 0 && y == 0 && z != 0)) {
		// color and one option
		if (y != 0) {
			std::string tmp = "\u001b[" + std::to_string(x) + ";" + std::to_string(y) + "m" + text + "\u001b[0m";
			return tmp;
		}
		else {
			std::string tmp = "\u001b[" + std::to_string(x) + ";" + std::to_string(z) + "m" + text + "\u001b[0m";
			return tmp;
		}
	}

	if (x != 0 && y == 0 && z == 0) {
		// color and no options
		std::string tmp = "\u001b[" + std::to_string(x) + "m" + text + "\u001b[0m";
		return tmp;
	}

	if (x == 0 && y != 0 && z != 0) {
		// no color and all options
		std::string tmp = "\u001b[" + std::to_string(y) + ";" + std::to_string(z) + "m" + text + "\u001b[0m";
		return tmp;
	}

	if ((x == 0 && y != 0 && z == 0) || (x == 0 && y == 0 && z != 0)) {
		// no color and one option
		if (y != 0) {
			std::string tmp = "\u001b[" + std::to_string(y) + "m" + text + "\u001b[0m";
			return tmp;
		}
		else {
			std::string tmp = "\u001b[" + std::to_string(z) + "m" + text + "\u001b[0m";
			return tmp;
		}
	}

	if (x == 0 && y == 0 && z == 0) {
		// no color and no option
		return text;
	}
}

void itfStartup(void) {
	itfClrscr();
	std::cout << itfAnsi("red", "zero", "zero",   "E m b e r s i m") << std::endl;
	std::cout << itfAnsi("white", "zero", "zero", "following commands are available:\n") << std::endl;
	std::cout << itfAnsi("white", "zero", "zero", "-h to show this list of commands") << std::endl;
	std::cout << itfAnsi("white", "zero", "zero", "-c to calculate data from flightprofile") << std::endl;
	std::cout << itfAnsi("white", "zero", "zero", "   -v for verbose") << std::endl;
	std::cout << itfAnsi("white", "zero", "zero", "-x to exit the program\n") << std::endl;
}

std::string itfCommand(void) {
	std::string userIn;
	std::cout << itfAnsi("yellow", "zero", "zero", "Embersim> ");
	std::getline(std::cin, userIn);
	return userIn;
}