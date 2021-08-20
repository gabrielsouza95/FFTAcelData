#include "transform_data.h"

Transform_Data::Transform_Data(void)
{
    //construtor
}

void Transform_Data::fft_transform(ComplexArray1D p_axle_x_data, ComplexArray1D p_axle_y_data, ComplexArray1D p_axle_z_data,
	ComplexArray1D& p_transformed_x, ComplexArray1D& p_transformed_y, ComplexArray1D& p_transformed_z,
	long p_data_size)
{
	const char* error_description = 0; 
	bool ret = simple_fft::FFT(p_axle_x_data, p_transformed_x, static_cast<int>(p_axle_x_data.size()), error_description);
	if (!ret) {
		std::cout << "\n Transformada FFT: FFT returnou com erro! Segue descrição do erro em inglês: "
			<< error_description << std::endl;
	}
}

long Transform_Data::reduce_vector_size_to_pwr2(ComplexArray1D &p_vector, long p_size)
{
    long l_closest_pwr2 = 0;
    
    for (int i = p_size; i >= 1; i--)
    {
        // se for potência de 2, ele quebra o laço
        if ((i & (i - 1)) == 0)
        {
            l_closest_pwr2 = i;
            break;
        }
    }

    while (p_vector.size() > l_closest_pwr2)
    {
        p_vector.pop_back();
    }

    return l_closest_pwr2;
}

void Transform_Data::get_real_data_from_complex(ComplexArray1D &p_complex, std::vector <double> &p_real)
{
    for (std::complex<double> x : p_complex)
        p_real.push_back(x.real());
}