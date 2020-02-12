//this struct is used to read/write a vector of 16 floats
struct float16
{
	float f[16];
};

extern "C"
{
	void vadd_kernel(float16* input1, float16* input2, float16* output, int size)
	{
		//pragmas to set input1, input2 and output arrays as M_AXI I/O
		#pragma HLS interface m_axi port=input1 offset=slave bundle=gmem0
		#pragma HLS interface s_axilite port=input1 bundle=control
		#pragma HLS interface m_axi port=input2 offset=slave bundle=gmem1
		#pragma HLS interface s_axilite port=input2 bundle=control
		#pragma HLS interface m_axi port=output offset=slave bundle=gmem2
		#pragma HLS interface s_axilite port=output bundle=control

		//pragmas to set size scalar and return type of the kernel
		#pragma HLS interface s_axilite port=size bundle=control
		#pragma HLS interface s_axilite port=return bundle=control

		//data_pack directive is used to create a single 512 bit wide port for each array
		#pragma HLS data_pack variable=input1
		#pragma HLS data_pack variable=input2
		#pragma HLS data_pack variable=output

		//allign the size to 16 elements
		int size16 = (size + 15) / 16;

		//pipeline loop
		P_External_Loop: for (int i = 0; i < size16; i++)
		{
			#pragma HLS pipeline II=1

			//read a 16-float vector from input1 and a 16-float vector from input2
			float16 in1 = input1[i];
			float16 in2 = input2[i];

			float16 out;

			//unroll loop
			U_Internal_Loop: for (int j = 0; j < 16; j++)
			{
				#pragma HLS unroll

				//perform 16 parallel calculations
				out.f[j] = in1.f[j] + in2.f[j];
			}

			//write the resulting 16-float vector to output
			output[i] = out;
		}
	}
}
