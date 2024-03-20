#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

void ReadFile(std::string file_name, std::vector<std::vector<double>>* image_data) {

	std::ifstream file(file_name);
	std::vector<double> new_row;
	std::string str;

	while (std::getline(file, str)) {
		std::istringstream ss(str);
		double token;
		while (ss >> token) {
			new_row.push_back(token);
		}

		image_data->push_back(new_row);
		new_row.clear();
	}
}

void WriteFile(std::string file_name, std::vector<std::vector<double>>* image_data) {
	std::ofstream output_file(file_name);

	for (unsigned int i = 0; i < image_data->size(); i++) {
		for (unsigned int j = 0; j < (*image_data)[i].size(); j++) {
			output_file << (*image_data)[i][j] << " ";
		}
		output_file << std::endl;
	}
}


int main(int argc, char*argv[]) {
	std::string input_file_name = std::string(argv[1]);
	std::string output_file_name = std::string(argv[2]);

	std::vector<std::vector<double>> data;

	ReadFile(input_file_name, &data);

	WriteFile(output_file_name, &data);
}




