#include "file_writer.h"

File_Writer::File_Writer(std::string p_path, std::string p_header)
{
	_path_to_file = p_path;
	_file_header = p_header;
}
void File_Writer::write_data(std::vector<double> p_axle_x, std::vector<double> p_axle_y,
	                         std::vector<double> p_axle_z, float p_frequency)
{
	std::ofstream l_result_file;
	l_result_file.open(_path_to_file);
	long l_interaction = 0;
	float l_frequency = 0.0;

	if (l_result_file.is_open())
	{
		if(!_file_header.empty())
			l_result_file << _file_header << "\n";
		
		std::reverse(p_axle_x.begin(), p_axle_x.end());//Inverte os vetores pois não permite erase() para fazer a
		std::reverse(p_axle_y.begin(), p_axle_y.end());//operação de colocar os elemetos dos vetores na ordem que já
		std::reverse(p_axle_z.begin(), p_axle_z.end());//está gravado mas o pop_back() sim.

		while (p_axle_x.size() > 0 && p_axle_y.size() > 0 && p_axle_z.size() > 0)
		{
			l_result_file << p_axle_x[p_axle_x.size()-1] << "," << p_axle_y[p_axle_y.size()-1] << "," << p_axle_z[p_axle_z.size()-1] << "," << l_frequency <<"\n";
			p_axle_x.pop_back();
			p_axle_y.pop_back();
			p_axle_z.pop_back();
			l_frequency += p_frequency;
		}

		l_result_file.close();
	}
	else
	{
		std::cout << " Could not write the file " + _path_to_file;
	}
}