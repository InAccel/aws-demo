#include <cstdlib>
#include <iostream>

#include <inaccel/coral>

void random(inaccel::vector<float> &vector, int size) {
	for (int i = 0; i < size; i++) {
		vector[i] = (float) rand();
	}
}

int main() {
	int size = 1024 * 1024;

	// Allocate four vectors
	inaccel::vector<float> a(size), b(size), c_add(size), c_sub(size);

	// Initialize input vectors with random values
	random(a, size);
	random(b, size);

	// Send a request for "addition" accelerator to the Coral FPGA Resource Manager
	// Request arguments must comply with the accelerator's specific argument list
	inaccel::request vadd("com.inaccel.math.vector.addition");
	vadd.arg(a).arg(b).arg(c_add).arg(size);
	inaccel::wait(inaccel::submit(vadd));

	// Send a request for "subtraction" accelerator to the Coral FPGA Resource Manager
	// Request arguments must comply with the accelerator's specific argument list
	inaccel::request vsub("com.inaccel.math.vector.subtraction");
	vsub.arg(a).arg(b).arg(c_sub).arg(size);
	inaccel::wait(inaccel::submit(vsub));

	// Check output vectors
	bool valid = true;

	for (int i = 0; i < size; i++) {
		if (c_add[i] != (a[i] + b[i])) valid = false;

		if (c_sub[i] != (a[i] - b[i])) valid = false;
	}

	if (valid) {
		std::cout << "Results: RIGHT!" << std::endl;
		return 0;
	} else {
		std::cout << "Results: WRONG!" << std::endl;
		return 1;
	}
}
