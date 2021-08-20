#ifndef FILEWRITER_H    // Para não ser adicionado mais de uma vez
#define FILEWRITER_H
//Criado para escrever os dados no arquivo

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//#include "transform_data.h"

class File_Writer {
	private:
		std::string _file_header;
		std::string _path_to_file;
	public:
		File_Writer(std::string p_path, std::string p_header);
		void write_data(std::vector<double> p_axle_x, std::vector<double> p_axle_y, std::vector<double> p_axle_z, float p_frequency);
		enum { _axle_x, _axle_y, _axle_z }; // 0 1 2		

};
#endif