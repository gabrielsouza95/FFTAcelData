#ifndef TRANSFORMDATA_H    // Para não ser adicionado mais de uma vez
#define TRANSFORMDATA_H
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <complex>

/// Está sendo utilizada a biblioteca de FFT do seguinte repositório:
/// https://github.com/d1vanov/Simple-FFT
#include "fft.hpp"
#include "fft_settings.h"

// typedefing vectors
typedef std::vector<real_type> RealArray1D;
typedef std::vector<complex_type> ComplexArray1D;

class Transform_Data {
	private:

	public:
		Transform_Data(void);
		long reduce_vector_size_to_pwr2(ComplexArray1D & p_vector, long p_size);
		void fft_transform(ComplexArray1D p_axle_x_data, ComplexArray1D p_axle_y_data, ComplexArray1D p_axle_z_data,
			ComplexArray1D& p_transformed_x, ComplexArray1D& p_transformed_y, ComplexArray1D& p_transformed_z,
			long p_data_size);
		void get_real_data_from_complex(ComplexArray1D& p_complex, std::vector <double> &p_real);
		
		
};

#endif