import numpy as np

import inaccel.coral as inaccel

if __name__== "__main__":
	size = np.int32(1024 * 1024)

	# Allocate four vectors & Initialize input vectors with random values
	a = inaccel.array(np.random.rand(size), dtype = np.float32)
	b = inaccel.array(np.random.rand(size), dtype = np.float32)
	c_add = inaccel.ndarray(size, dtype = np.float32)
	c_sub = inaccel.ndarray(size, dtype = np.float32)

	# Send a request for "addition" accelerator to the Coral FPGA Resource Manager
	# Request arguments must comply with the accelerator's specific argument list
	vadd = inaccel.request("com.inaccel.math.vector.addition")
	vadd.arg(a).arg(b).arg(c_add).arg(size)
	inaccel.wait(inaccel.submit(vadd))

	# Send a request for "subtraction" accelerator to the Coral FPGA Resource Manager
	# Request arguments must comply with the accelerator's specific argument list
	vsub = inaccel.request("com.inaccel.math.vector.subtraction")
	vsub.arg(a).arg(b).arg(c_sub).arg(size)
	inaccel.wait(inaccel.submit(vsub))

	# Check output vectors
	valid = True

	if not np.array_equal(c_add, a + b):
		valid = False

	if not np.array_equal(c_sub , a - b):
		valid = False

	if valid:
		print('Results: RIGHT!')
		exit(0)
	else:
		print('Results: WRONG!')
		exit(1)
