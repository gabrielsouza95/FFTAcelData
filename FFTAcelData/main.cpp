/// Está sendo utilizada a biblioteca de FFT do seguinte repositório:
/// https://github.com/d1vanov/Simple-FFT
#include "transform_data.h"
///
#include "file_reader.h"
#include "file_writer.h"
#include <complex>
// STL vectors use square brackets for element access operator
#define __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR 

int main(int argc, char *argv[]) {
	try
	{			
		if (argc == 2)
		{	
			File_Reader l_reader = File_Reader(argv[1],1);
			// programa inicializado com o path do arquivo como argumento para leitura
			ComplexArray1D l_axle_x = l_reader.get_axis_values(l_reader._axle_x),
					       l_axle_y = l_reader.get_axis_values(l_reader._axle_y),
						   l_axle_z = l_reader.get_axis_values(l_reader._axle_z);

			long l_sample_size = l_reader.get_amount_lines_readed();
			long l_sample_time = l_reader.get_sample_time();
			float l_sample_frequency = (float)l_sample_size / ((float)l_sample_time / 1000.0); //divide o l_sample_time por 1000 pois está em millis
			float l_fft_frequency = l_sample_frequency * (1.0/ (float)l_sample_size);
			
			std::cout << "\n A frequencia dos dados: " << l_sample_frequency << " Quantidade de dados: " << l_sample_size;

			Transform_Data transform = Transform_Data();

			long l_ajusted_size = transform.reduce_vector_size_to_pwr2(l_axle_x, l_sample_size); //reduz o tamanho do vetor para poder rodar no algoritmo de FFT da biblioteca
			transform.reduce_vector_size_to_pwr2(l_axle_y, l_sample_size);
			transform.reduce_vector_size_to_pwr2(l_axle_z, l_sample_size);

			ComplexArray1D l_transformed_x = l_axle_x, l_transformed_y = l_axle_y, l_transformed_z = l_axle_z;
			
			transform.fft_transform(l_axle_x, l_axle_y, l_axle_z,
								    l_transformed_x, l_transformed_y, l_transformed_z,
								    l_sample_size-1);
			std::cout << "\n Transformada realizada.";

			std::vector<double> l_real_transformed_x, l_real_transformed_y, l_real_transformed_z;
			
			transform.get_real_data_from_complex(l_transformed_x, l_real_transformed_x);
			transform.get_real_data_from_complex(l_transformed_y, l_real_transformed_y);
			transform.get_real_data_from_complex(l_transformed_z, l_real_transformed_z);

			File_Writer l_writer = File_Writer("output.txt","");
			l_writer.write_data(l_real_transformed_x, l_real_transformed_y, l_real_transformed_z, l_fft_frequency);
		}
		else // se for inicializado com argumentos diferentes dos esperados
		{
			std::cout << "\n Para executar o programa, digite " << argv[0] << " + nome_do_arquivo.txt ou caminho/nome_do_arquivo.txt";
		}

	}
	catch (...) {
		
	}
	return 1;
}
