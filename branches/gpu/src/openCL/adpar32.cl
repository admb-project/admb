///////////////////////////////////////////////////////////////////////////////
//! Matrix multiplication on the device: C = A * B
//! wA is A's width and wB is B's width
////////////////////////////////////////////////////////////////////////////////
__kernel void
matrixMul( __global float* C, 
					 __global float* A, 
					 __global float* B, 
					 int wA, 
					 int wB){
	
	// 2D Thread ID
	int tx = get_local_id(0);
	int ty = get_local_id(1);
	
	// value stores the element 
	// that is computed by the thread
	float value = 0;
	for (int k = 0; k < wA; ++k){
      float elementA = A[ty * wA + k];
      float elementB = B[k * wB + tx];
      value += elementA * elementB;
	}
	
	// Write the matrix to device memory each 
	// thread writes one element
	C[ty * wA + tx] = value;
}

