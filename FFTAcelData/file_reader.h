#ifndef FILEREADER_H    // Para não ser adicionado mais de uma vez
#define FILEREADER_H
//Criado para processar os dados do arquivo

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "transform_data.h"

class File_Reader {
	private:
		ComplexArray1D _acel[3]; //inicializa os vetores dos eixos para guardar os valores do arquivo
		long extract_sample_time(std::string p_file_path);
		long _sample_time;
		long _amount_lines;
	public:
		File_Reader(std::string p_path, int p_skiped_lines);
		ComplexArray1D get_axis_values(int p_axis);
		       long	get_sample_time(void);
		       long get_amount_lines_readed(void);

		enum { _axle_x, _axle_y, _axle_z }; // 0 1 2		
};

#endif