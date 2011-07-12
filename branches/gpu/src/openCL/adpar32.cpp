#include <oclUtils.h>
#include <shrQATest.h>

#include <memory>
#include <iostream>
#include <cassert>

#ifdef UNIX
#include <sstream>
#include <fstream>
#endif

//#include <direct.h>
#include <adpar32.h>


// Allocates a matrix with random float entries.
void randomInit(float* data, int size){
	for (int i = 0; i < size; ++i)
		data[i] = rand() / (float)RAND_MAX;
}
/*
df3_two_matrix ocl_choleski_decomp(const df3_two_matrix& MM){
	// based on choleski_decomp in src\df1b2-separable\df32fun.cpp
	df3_two_matrix & M = (df3_two_matrix &) MM;
  int rmin = M.indexmin();
  int cmin = M(rmin).indexmin();
  int rmax = M.indexmax();
  int cmax = M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df3_two_matrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df3_two_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n = rmax-rmin+1;
  df3_two_matrix L(1,n,1,n);

#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df3_two_variable tmp;
   
	if (value(M(1,1))<=0){
		cerr << "Error matrix not positive definite in choleski_decomp"
				 <<endl;
		ad_exit(1);
	}
	// Set up calculation on GPU device


}
*/
int cpuMatMult(int wa, int ha, int wb, int hb, bool printMatrices){
	if(wa > MAXMATRIXDIM |
		 wa < 1 |
		 ha > MAXMATRIXDIM |
		 ha < 1 |
		 wb > MAXMATRIXDIM |
		 wb < 1 |
		 hb > MAXMATRIXDIM |
		 hb < 1){
		printf("cpuMatMult: Error - Matrix dimensions must be between 1 and %d.\n",MAXMATRIXDIM);
		return(0);
	}
	if(wa != hb){
		printf("cpuMatMult: Error - The width of A (wa) must equal the height of B (hb).\n");
		return(0);		
	}
	printf("cpuMatMult: Multiply matrices using CPU...\n");
	printf("cpuMatMult: multiplying matrix A (%dx%d) by matrix B (%dx%d).\n",wa,ha,wb,hb);
	int wc = ha;  // width of matrix C is height of matrix A
	int hc = wb;  // height of matrix C is width of matrix B

	srand(2006);
 
	// 1. allocate host memory for matrices A and B
	unsigned int size_A = wa * ha;
	unsigned int mem_size_A = sizeof(float) * size_A;
	float* h_A = (float*) malloc(mem_size_A);
	
	unsigned int size_B = wb * hb;
	unsigned int mem_size_B = sizeof(float) * size_B;
	float* h_B = (float*) malloc(mem_size_B);
	
	// 2. initialize host memory
	randomInit(h_A, size_A);
	randomInit(h_B, size_B);
	
	// 3. print out A and B
	if(printMatrices){
		printf("\n\nMatrix A\n");
		for(int i = 0; i < size_A; i++){
			printf("%f ", h_A[i]);
			if(((i + 1) % wa) == 0)
				printf("\n");
		}
		
		printf("\n\nMatrix B\n");
		for(int i = 0; i < size_B; i++){
			printf("%f ", h_B[i]);
			if(((i + 1) % wb) == 0)
				printf("\n");
		}
	}

	// 4. allocate host memory for the result C
	unsigned int size_C = wc * hc;
	unsigned int mem_size_C = sizeof(float) * size_C;
	float* h_C = (float*) malloc(mem_size_C);
	
	// 5. do the multiplication
	float value = 0;
	for(int i = 0; i < wa; i++){
		for(int j = 0; j < hb; j++){
			value = 0.0;
			for(int k = 0; k < wa ; k++){
				//value += h_A[i][k] * h_B[k][j];
				value += h_A[i*wa+k] * h_B[k*hb+j];
			}
			h_C[i*wa+j] = value;
		}
	}

	// 6. print out the results
	printf("cpuMatMult: Done matrix multiplication\n");

	if(printMatrices){
		printf("\n\nMatrix C (Results)\n");
		for(int i = 0; i < size_C; i++)
			{
				printf("%f ", h_C[i]);
				if(((i + 1) % wc) == 0)
					printf("\n");
			}
		printf("\n");
	}

	// 10. clean up memory
	free(h_A);
	free(h_B);
	free(h_C);
	return(1);

}

int oclMatMult(int wa, int ha, int wb, int hb, bool printMatrices){
	if(wa > MAXMATRIXDIM |
		 wa < 1 |
		 ha > MAXMATRIXDIM |
		 ha < 1 |
		 wb > MAXMATRIXDIM |
		 wb < 1 |
		 hb > MAXMATRIXDIM |
		 hb < 1){
		printf("oclMatMult: Error - Matrix dimensions must be between 1 and %d.\n",MAXMATRIXDIM);
		return(0);
	}
	if(wa != hb){
		printf("oclMatMult: Error - The width of A (wa) must equal the height of B (hb).\n");
		return(0);		
	}
	printf("\noclMatMult: Multiply matrices using OpenCL/CUDA...\n");
	printf("oclMatMult: multiplying matrix A (%dx%d) by matrix B (%dx%d).\n",wa,ha,wb,hb);
	
	int wc = ha;  // width of matrix C is height of matrix A
	int hc = wb;  // height of matrix C is width of matrix B

	srand(2006);
 
	// 1. allocate host memory for matrices A and B
	unsigned int size_A = wa * ha;
	unsigned int mem_size_A = sizeof(float) * size_A;
	float* h_A = (float*) malloc(mem_size_A);
	
	unsigned int size_B = wb * hb;
	unsigned int mem_size_B = sizeof(float) * size_B;
	float* h_B = (float*) malloc(mem_size_B);
	
	// 2. initialize host memory
	randomInit(h_A, size_A);
	randomInit(h_B, size_B);
	
	// 3. print out A and B
	if(printMatrices){
		printf("\n\nMatrix A\n");
		for(int i = 0; i < size_A; i++){
			printf("%f ", h_A[i]);
			if(((i + 1) % wa) == 0)
				printf("\n");
		}
		
		printf("\n\nMatrix B\n");
		for(int i = 0; i < size_B; i++){
			printf("%f ", h_B[i]);
			if(((i + 1) % wb) == 0)
				printf("\n");
		}
	}

	// 4. allocate host memory for the result C
	unsigned int size_C = wc * hc;
	unsigned int mem_size_C = sizeof(float) * size_C;
	float* h_C = (float*) malloc(mem_size_C);
	
	// 5. Initialize OpenCL
	// OpenCL specific variables
	cl_int clErrNum;
	cl_platform_id clSelectedPlatformID = NULL; 

	cl_context clGPUContext;
	cl_command_queue clCommandQue;
	cl_program clProgram;
	cl_kernel clKernel;
	
	size_t dataBytes;
	size_t kernelLength;
	cl_int errcode;
	
	// OpenCL device memory for matrices
	cl_mem d_A;
	cl_mem d_B;
	cl_mem d_C;
	
	/*****************************************/
	/* Initialize OpenCL */
	/*****************************************/
	// ********************************************************************************
	// Need to first get the platformid. It cannot be NULL as in the NVidia examples!!!
	char cBuffer[PLATFORMINFOSIZE];
	bool bPassed = true;
	cl_int ciErrNum = oclGetPlatformID (&clSelectedPlatformID);
	oclCheckError(ciErrNum, CL_SUCCESS);

	ciErrNum = clGetPlatformInfo (clSelectedPlatformID, CL_PLATFORM_NAME, sizeof(cBuffer), cBuffer, NULL);
	if (ciErrNum == CL_SUCCESS){
		printf("oclMatMult: Successfully found CL platform - CL_PLATFORM_NAME: \t%s\n", cBuffer);
	}else{
		printf("oclMatMult: Error %i in clGetPlatformInfo Call !!!\n", ciErrNum);
		bPassed = false;
	}

	cl_context_properties props[3];
	props[0] = (cl_context_properties)CL_CONTEXT_PLATFORM;  // indicates that next element is platform
	props[1] = (cl_context_properties)clSelectedPlatformID;  // platform is of type cl_platform_id
	props[2] = (cl_context_properties)0;   // last element must be 0
	clGPUContext = clCreateContextFromType(props,
																				 CL_DEVICE_TYPE_GPU, 
																				 NULL, 
																				 NULL, 
																				 &errcode);

	shrCheckError(errcode, CL_SUCCESS);
	
	// get the list of GPU devices associated 
	// with context
	errcode = clGetContextInfo(clGPUContext, 
														 CL_CONTEXT_DEVICES, 0, NULL, 
														 &dataBytes);
	cl_device_id *clDevices = (cl_device_id *)malloc(dataBytes);
	errcode |= clGetContextInfo(clGPUContext, 
															CL_CONTEXT_DEVICES, dataBytes, 
															clDevices, NULL);
	shrCheckError(errcode, CL_SUCCESS);
	
	//Create a command-queue
	clCommandQue = clCreateCommandQueue(clGPUContext, 
																			clDevices[0], 0, &errcode);
	shrCheckError(errcode, CL_SUCCESS);
	
	// Setup device memory
	d_C = clCreateBuffer(clGPUContext, 
											 CL_MEM_READ_WRITE, 
											 mem_size_A, NULL, &errcode);
	d_A = clCreateBuffer(clGPUContext, 
											 CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 
											 mem_size_A, h_A, &errcode);
	d_B = clCreateBuffer(clGPUContext, 
											 CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 
											 mem_size_B, h_B, &errcode);
	
 
	// 6. Load and build OpenCL kernel
	char *clMatrixMul = oclLoadProgSource("C:\\admb-10.1\\src\\openCL\\adpar32.cl",
																				"// My comment\n",
																				&kernelLength);
	shrCheckError(clMatrixMul != NULL, shrTRUE);
	
	clProgram = clCreateProgramWithSource(clGPUContext,
																				1,
																				(const char **)&clMatrixMul,
																				&kernelLength,
																				&errcode);
	shrCheckError(errcode, CL_SUCCESS);
	
	errcode = clBuildProgram(clProgram,0,NULL, NULL, NULL, NULL);
	shrCheckError(errcode, CL_SUCCESS);
	
	clKernel = clCreateKernel(clProgram,"matrixMul", &errcode);
	shrCheckError(errcode, CL_SUCCESS);
	
  // 7. Launch OpenCL kernel
	size_t localWorkSize[2], globalWorkSize[2];
	
	int wA = wa;
	int wC = wc;
	errcode = clSetKernelArg(clKernel, 
													 0, 
													 sizeof(cl_mem), (void *)&d_C);
	errcode |= clSetKernelArg(clKernel, 
														1, 
														sizeof(cl_mem), (void *)&d_A);
	errcode |= clSetKernelArg(clKernel, 
														2, 
														sizeof(cl_mem), (void *)&d_B);
	errcode |= clSetKernelArg(clKernel, 
														3, 
														sizeof(int), (void *)&wA);
	errcode |= clSetKernelArg(clKernel, 
														4, 
														sizeof(int), (void *)&wC);
	shrCheckError(errcode, CL_SUCCESS);
	
	localWorkSize[0] = 3;
	localWorkSize[1] = 3;
	globalWorkSize[0] = 3;
	globalWorkSize[1] = 3;
	
	errcode = clEnqueueNDRangeKernel(clCommandQue, 
																	 clKernel, 
																	 2, 
																	 NULL, 
																	 globalWorkSize, 
																	 localWorkSize, 
																	 0, 
																	 NULL, 
																	 NULL);
	shrCheckError(errcode, CL_SUCCESS);
	
	// 8. Retrieve result from device
	errcode = clEnqueueReadBuffer(clCommandQue, 
																d_C, 
																CL_TRUE,
																0,
																mem_size_C,
																h_C, 
																0, 
																NULL,
																NULL);
	shrCheckError(errcode, CL_SUCCESS);
	
	// 9. print out the results
	printf("oclMatMult: Done matrix multiplication\n");

	if(printMatrices){
		printf("\n\nMatrix C (Results)\n");
		for(int i = 0; i < size_C; i++)
			{
				printf("%f ", h_C[i]);
				if(((i + 1) % wc) == 0)
					printf("\n");
			}
		printf("\n");
	}

	// 10. clean up memory
	free(h_A);
	free(h_B);
	free(h_C);
	return(1);
}

int oclDeviceTest(){
	printf("oclDeviceTest: Starting OpenCL Device tests...\n\n");
	
	bool bPassed = true;
	std::string sProfileString = "adpar32, Platform Name = ";
	
	// Get OpenCL platform ID for NVIDIA if avaiable, otherwise default
	printf("OpenCL SW Info:\n\n");
	char cBuffer[1024];
	cl_platform_id clSelectedPlatformID = NULL; 
	cl_int ciErrNum = oclGetPlatformID (&clSelectedPlatformID);
	oclCheckError(ciErrNum, CL_SUCCESS);

	// Get OpenCL platform name and version
	ciErrNum = clGetPlatformInfo (clSelectedPlatformID, CL_PLATFORM_NAME, sizeof(cBuffer), cBuffer, NULL);

	if (ciErrNum == CL_SUCCESS){
		printf(" CL_PLATFORM_NAME: \t%s\n", cBuffer);
		sProfileString += cBuffer;
	}else{
		printf(" Error %i in clGetPlatformInfo Call !!!\n\n", ciErrNum);
		bPassed = false;
	}
	sProfileString += ", Platform Version = ";

	ciErrNum = clGetPlatformInfo (clSelectedPlatformID, CL_PLATFORM_VERSION, sizeof(cBuffer), cBuffer, NULL);
	if (ciErrNum == CL_SUCCESS){
		printf(" CL_PLATFORM_VERSION: \t%s\n", cBuffer);
		sProfileString += cBuffer;
	}else{
		printf(" Error %i in clGetPlatformInfo Call !!!\n\n", ciErrNum);
		bPassed = false;
	}
	sProfileString += ", SDK Revision = ";

	// Log OpenCL SDK Revision # 
	printf(" OpenCL SDK Revision: \t%s\n\n\n", OCL_SDKREVISION);
	sProfileString += OCL_SDKREVISION;
	sProfileString += ", NumDevs = ";
	
	// Get and log OpenCL device info 
	cl_uint ciDeviceCount;
	cl_device_id *devices;
	printf("OpenCL Device Info:\n\n");
	ciErrNum = clGetDeviceIDs (clSelectedPlatformID, CL_DEVICE_TYPE_ALL, 0, NULL, &ciDeviceCount);

	// check for 0 devices found or errors... 
	if (ciDeviceCount == 0){
		printf(" No devices found supporting OpenCL (return code %i)\n\n", ciErrNum);
		bPassed = false;
		sProfileString += "0";
	}else if (ciErrNum != CL_SUCCESS){
		printf(" Error %i in clGetDeviceIDs call !!!\n\n", ciErrNum);
		bPassed = false;
	}else{
		// Get and log the OpenCL device ID's
		printf(" %u devices found supporting OpenCL:\n\n", ciDeviceCount);
		char cTemp[2];
#ifdef WIN32
		sprintf_s(cTemp, 2*sizeof(char), "%u", ciDeviceCount);
#else
		sprintf(cTemp, "%u", ciDeviceCount);
#endif
		sProfileString += cTemp;
		if ((devices = (cl_device_id*)malloc(sizeof(cl_device_id) * ciDeviceCount)) == NULL){
			printf(" Failed to allocate memory for devices !!!\n\n");
			bPassed = false;
		}
		ciErrNum = clGetDeviceIDs (clSelectedPlatformID, CL_DEVICE_TYPE_ALL, ciDeviceCount, devices, &ciDeviceCount);
		if (ciErrNum == CL_SUCCESS){
			//Create a context for the devices
			cl_context cxGPUContext = clCreateContext(0, ciDeviceCount, devices, NULL, NULL, &ciErrNum);
			if (ciErrNum != CL_SUCCESS){
				printf("Error %i in clCreateContext call !!!\n\n", ciErrNum);
				bPassed = false;
			}else{
				// show info for each device in the context
				for(unsigned int i = 0; i < ciDeviceCount; ++i ) {  
					printf(" ---------------------------------\n");
					clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(cBuffer), &cBuffer, NULL);
					printf(" Device %s\n", cBuffer);
					printf(" ---------------------------------\n");
					oclPrintDevInfo(LOGBOTH, devices[i]);
					sProfileString += ", Device = ";
					sProfileString += cBuffer;
				}
				
				// Determine and show image format support 
				cl_uint uiNumSupportedFormats = 0;

				// 2D
				clGetSupportedImageFormats(cxGPUContext, CL_MEM_READ_ONLY, 
																	 CL_MEM_OBJECT_IMAGE2D,   
																	 NULL, NULL, &uiNumSupportedFormats);
				cl_image_format* ImageFormats = new cl_image_format[uiNumSupportedFormats];
				clGetSupportedImageFormats(cxGPUContext, CL_MEM_READ_ONLY, 
																	 CL_MEM_OBJECT_IMAGE2D,   
																	 uiNumSupportedFormats, ImageFormats, NULL);
				printf("  ---------------------------------\n");
				printf("  2D Image Formats Supported (%u)\n", uiNumSupportedFormats); 
				printf("  ---------------------------------\n");
				printf("  %-6s%-16s%-22s\n\n", "#", "Channel Order", "Channel Type"); 
				for(unsigned int i = 0; i < uiNumSupportedFormats; i++){  
					printf("  %-6u%-16s%-22s\n", (i + 1),
								 oclImageFormatString(ImageFormats[i].image_channel_order), 
								 oclImageFormatString(ImageFormats[i].image_channel_data_type));
				}
				printf("\n"); 
				delete [] ImageFormats;
				
				// 3D
				clGetSupportedImageFormats(cxGPUContext, CL_MEM_READ_ONLY, 
																	 CL_MEM_OBJECT_IMAGE3D,   
																	 NULL, NULL, &uiNumSupportedFormats);
				ImageFormats = new cl_image_format[uiNumSupportedFormats];
				clGetSupportedImageFormats(cxGPUContext, CL_MEM_READ_ONLY, 
																	 CL_MEM_OBJECT_IMAGE3D,   
																	 uiNumSupportedFormats, ImageFormats, NULL);
				printf("  ---------------------------------\n");
				printf("  3D Image Formats Supported (%u)\n", uiNumSupportedFormats); 
				printf("  ---------------------------------\n");
				printf("  %-6s%-16s%-22s\n\n", "#", "Channel Order", "Channel Type"); 
				for(unsigned int i = 0; i < uiNumSupportedFormats; i++){  
					printf("  %-6u%-16s%-22s\n", (i + 1),
								 oclImageFormatString(ImageFormats[i].image_channel_order), 
								 oclImageFormatString(ImageFormats[i].image_channel_data_type));
				}
				printf("\n"); 
				delete [] ImageFormats;
			}
		}else{
			printf(" Error %i in clGetDeviceIDs call !!!\n\n", ciErrNum);
			bPassed = false;
		}
	}

	// masterlog info
	sProfileString += "\n";
	//printfEx(LOGBOTH | MASTER, 0, sProfileString.c_str());

	// Log system info(for convenience:  not specific to OpenCL) 
	printf("\nSystem Info: \n\n");
#ifdef _WIN32
	SYSTEM_INFO stProcInfo;         // processor info struct
	OSVERSIONINFO stOSVerInfo;      // Win OS info struct
	SYSTEMTIME stLocalDateTime;     // local date / time struct 
	
	// processor
	SecureZeroMemory(&stProcInfo, sizeof(SYSTEM_INFO));
	GetSystemInfo(&stProcInfo);

	// OS
	SecureZeroMemory(&stOSVerInfo, sizeof(OSVERSIONINFO));
	stOSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&stOSVerInfo);

	// date and time
	GetLocalTime(&stLocalDateTime); 
	
	// write time and date to logs
	printf(" Local Time/Date = %i:%i:%i, %i/%i/%i\n", 
				 stLocalDateTime.wHour, stLocalDateTime.wMinute, stLocalDateTime.wSecond, 
				 stLocalDateTime.wMonth, stLocalDateTime.wDay, stLocalDateTime.wYear); 
	
	// write proc and OS info to logs
	printf(" CPU Arch: %i\n CPU Level: %i\n # of CPU processors: %u\n Windows Build: %u\n Windows Ver: %u.%u %s\n\n\n", 
				 stProcInfo.wProcessorArchitecture, stProcInfo.wProcessorLevel, stProcInfo.dwNumberOfProcessors, 
				 stOSVerInfo.dwBuildNumber, stOSVerInfo.dwMajorVersion, stOSVerInfo.dwMinorVersion, 
				 (stOSVerInfo.dwMajorVersion >= 6)? "(Windows Vista / Windows 7)" : "");
#endif
	
#ifdef MAC
#else
#ifdef UNIX
	char timestr[255];
	time_t now = time(NULL);
	struct tm  *ts;
	
	ts = localtime(&now);
  
	strftime(timestr, 255, " %H:%M:%S, %m/%d/%Y",ts);
  
	// write time and date to logs
	printf(" Local Time/Date = %s\n",  timestr); 
	
	// write proc and OS info to logs
  
	// parse /proc/cpuinfo
	std::ifstream cpuinfo( "/proc/cpuinfo" ); // open the file in /proc        
	std::string tmp;
	
	int cpu_num = 0;
	std::string cpu_name = "none";        
	
	do {
		cpuinfo >> tmp;
    
		if( tmp == "processor" )
			cpu_num++;
		
		if( tmp == "name" )
			{
				cpuinfo >> tmp; // skip :
				
				std::stringstream tmp_stream("");
				do {
					cpuinfo >> tmp;
					if (tmp != std::string("stepping")) {
						tmp_stream << tmp.c_str() << " ";
					}
				}
				while (tmp != std::string("stepping"));
        
				cpu_name = tmp_stream.str();
			}
		
	}
	while ( (! cpuinfo.eof()) );
	
	// Linux version
	std::ifstream version( "/proc/version" );
	char versionstr[255];
	
	version.getline(versionstr, 255);
	
	printf(" CPU Name: %s\n # of CPU processors: %u\n %s\n\n\n", 
				 cpu_name.c_str(),cpu_num,versionstr);
#endif
#endif
	
	// finish
	//shrQAFinishExit(argc, (const char **)argv, (bPassed ? QA_PASSED : QA_FAILED) ); 
	return(1);
}
