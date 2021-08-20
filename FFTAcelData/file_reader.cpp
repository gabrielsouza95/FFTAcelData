#include "file_reader.h"

File_Reader::File_Reader(std::string p_path, int p_lines_to_skip) 
// p_skiped_lines - pula a quantidade de linhas do arquivo que representam o cabeçalho e podem ser ignoradas
{
	std::cout << "FileReader inicializado com path: " << p_path << "\n";
	std::string file_line;
	std::ifstream target_file(p_path);
	int l_lines_skiped = 0;
	_amount_lines = 0;
	_sample_time = extract_sample_time(p_path);

	if (target_file.is_open())
	{
		while (getline(target_file, file_line))
		{
			
			if (l_lines_skiped < p_lines_to_skip)
				l_lines_skiped++;
			else
			{
				_amount_lines++;
				std::string delimiter = ","; //faz o ',' ser o delimitador que divide os valores no arquivo
				std::size_t l_line_place = file_line.find(delimiter), l_last_place = file_line.find_last_of(delimiter); //encontra a primeira e a última ocorrência do delimitador 
				std::string extracted_value = file_line.substr(0, l_line_place); //extrai um valor da linha do arquivo
			    
				while (!file_line.empty())
				{
					if (l_line_place == std::string::npos) //se não encontrou nenhuma ocorrência do ',', está no valor Z pois os outros dois foram consumidos da linha
					{
						_acel[_axle_z].push_back(std::stod(extracted_value));
						file_line.clear();
					}
					else if (l_line_place < l_last_place) //se encontrou alguma ocorrência de ',' mas tem mais de uma, está no valor X pois nenhum valor foi consumido da linha ainda
					{
						_acel[_axle_x].push_back(std::stod(extracted_value));
					}
					else //se encontrou alguma ocorrência da ',' e é a última da linha, tá no valor Y
					{
						_acel[_axle_y].push_back(std::stod(extracted_value));
					}
					file_line.erase(0, l_line_place + delimiter.length());            //consome o valor lido da linha 'file_content'
					l_line_place = file_line.find(delimiter);                         //encontra a primeira ','
					l_last_place = file_line.find_last_of(delimiter);				  //encontra a última ','
					extracted_value = file_line.substr(0, file_line.find(delimiter)); //extrai mais um valor
				}
			}
		}
		target_file.close();
	}
	else {
		std::cout << " Could not open the file " + p_path;
	}
}

long File_Reader::extract_sample_time(std::string p_file_path)
{
	std::string delimiter = "-"; //faz o '-' ser o delimitador que divide os valores no nome do arquivo
	std::size_t l_line_place = p_file_path.find(delimiter), l_last_place = p_file_path.find_last_of(delimiter); //encontra a primeira e a última ocorrência do delimitador 
	std::string extracted_value = p_file_path.substr(l_line_place + 1, l_last_place); //extrai o valor de duração em millis do nome do arquivo

	long l_sample_time = std::stol(extracted_value, nullptr, 10);

	return l_sample_time;
}

ComplexArray1D File_Reader::get_axis_values(int p_axis)
{
	return _acel[p_axis];
}

long File_Reader::get_amount_lines_readed(void)
{
	return _amount_lines;
}

long File_Reader::get_sample_time(void)
{
	return _sample_time;
}