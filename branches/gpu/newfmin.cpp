/*
*
 * $Id: newfmin.cpp 1001 2011-04-07 22:36:54Z johnoel $
 *
 * Author: Unknown
 * Copyright (c) 2009-2011 ADMB Foundation
 *
 * This file was originally written in FORTRAN II by and unknown author.
 * In the 1980s, it was ported to C and C++ and extensively modified by
 * David Fournier. 
 *
 */
/**
 * \file
 * newfmin by Dave Fournier including new BFGS algorithm and GPU calculations
 */
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

// next line added by Ian Taylor to kill Visual C++ warning about 
// "not all control paths return a value"
#pragma warning(default:4716)

#include <fvar.hpp>
#if defined(__SPDLL__)
#  if !defined(linux)
#    include <windows.h>
#  endif
#include <admodel.h>
#include <s.h>
#include <newredef.h>
#endif
#if defined(__BORLANDC__)
  #include <signal.h>
#endif
#ifdef __ZTC__
  #include <conio.h>
#endif
#ifdef __GNUDOS__
  #define ADGETCH getch
#endif
#include <fvar.hpp>
extern int ctlc_flag;
#if defined(__TURBOC__) && defined(__linux__)
  void clrscr(void);
#endif
#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <iostream.h>
  #include <conio.h>
#endif
#if defined (__WAT32__) || defined (__MSVC32__) 
  #include <conio.h>
#endif
#if defined(__CYGWIN__)
  int kbhit(void)
  {
    return 0;
  }
#endif
#ifdef __ZTC__
  #include <iostream.hpp>
  #include <disp.h>
  #define endl "\n"
  void clrscr(void);
#endif
#ifdef __SUN__
  #define getch getchar
  void clrscr(void); 
#endif
#if defined(__GNU__) || defined(UNIXKLUDGE)
  #define getch getchar
#endif
  #include <signal.h>
  extern "C" void onintr(int k)
  {
    signal(SIGINT, exit_handler);
    ctlc_flag = 1;
    if (ad_printf) (*ad_printf)("\npress q to quit or c to invoke derivative checker: ");
  }
#ifdef __NDPX__
  #include <iostream.hxx>
  extern "C" {
    void clrscr();
  };
#endif
#if defined (__MSVC32__)
  void __cdecl clrscr(void);
#endif
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void mat_vec_neg_mult(const dmatrix &K,dvector & v,const dvector & g);
void bfgs_update(dvector & s,dvector & y,dmatrix & K);  
int* pointer_to_phase = 0;
dmatrix * pK=0;
dvector * pV=0;
//dvector * pstep=0;
dvector * oldx=0;
dvector * oldg=0;

double dafsqrt( double x );
  void tracing_message(int traceflag,const char *s);
  void tracing_message(int traceflag,const char *s,int *pn);
  void tracing_message(int traceflag,const char *s,double *pd);
  void tracing_message(int traceflag,const char *s,double d);

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << endl;
      ofs.close();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s,int *pn)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << " " << *pn << endl;
      ofs.close();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s,double *pd)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << " " << *pd << endl;
      ofs.close();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s,double d)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << " " << d << endl;
      ofs.close();
    }
  }
int log_values_switch=0;
ofstream logstream("fmin.log");

/**
 * Description not yet available.
 * \param
 */
void print_values(const double& f, const dvector & x,const dvector& g)
{
  logstream << setprecision(13) << f << endl;
  logstream << setprecision(13) << x << endl;
  logstream << setprecision(13) << g << endl;
}
extern adtimer * pfmintime=0;
extern int traceflag;
#pragma warn -sig
/**
 * Description not yet available.
 * \param
 */
int roundup(int n)
{
  int rem=n%256;
  if (rem)
    n+=256-rem;
  return n;
}

  
int * star(ivector& v)
{
  return &(v(v.indexmin()));
}

double * star(const dvector& _v)
{
  ADUNCONST(dvector,v)

  return &(v(v.indexmin()));
}

class opencl_manager
{
public:
  const unsigned int MAX_SOURCE_SIZE;
  char *source_str;
  size_t source_size;
  cl_platform_id platform_id;
  cl_device_id device_id;
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_context context; 
  cl_command_queue command_queue; 
  cl_program program;
  cl_kernel kernel;
  cl_kernel kernel1;
  cl_kernel kernel2;
  cl_kernel kernel3;
  cl_kernel kernel4;
  cl_mem K_mem_obj;
  cl_mem s_mem_obj;
  cl_mem s1_mem_obj;
  cl_mem s2_mem_obj;
  cl_mem t_mem_obj;
  cl_mem y_mem_obj;
  cl_mem ky_mem_obj;
  cl_mem ty_mem_obj;
  cl_mem sy_mem_obj;
  cl_mem g_mem_obj;
  cl_mem Kg_mem_obj;
 
  opencl_manager(void);

  cl_int clGetDeviceIDs(void);
  cl_int clGetPlatformIDs(void);
  cl_int clCreateCommandQueue(void);
  cl_int clCreateContext(void);
  void setup_GPU(void);
  cl_int CreateBuffers(int n,int rn);
  cl_int LoadKernelSource(const char * filename);
  cl_int CreateKernels(void);
  cl_int vector_vector_multiplications(int n,int m1);
  cl_int Matrix_vector_multiplication(const dvector & s,const dvector & y,
    int m,int n);
  cl_int Matrix_mvector_multiplication(const dvector & s,const dvector & y,
    int m,int n);
  cl_int BFGS_update(int n,int m);
  cl_int Kinitialize(int n,int m);
};

void ocl_bfgs_update(dvector & s,dvector & y,int n,int m);  

cl_int opencl_manager::Kinitialize(int n,int m)
{
  size_t global_item_size[3]={n,n,1};  // nxn work items
  size_t local_item_size[3] = {16,16,1}; // Process in groups of size mxm 
  int mloc=16;
  cl_int ret;
  int no=0;
  ret = clSetKernelArg(kernel4,no++, sizeof(cl_mem), (void *)&K_mem_obj);
  ret = clSetKernelArg(kernel4,no++, sizeof(int), (void *)&n);
  ret = clSetKernelArg(kernel4,no++, sizeof(int), (void *)&mloc);

  ret = clEnqueueNDRangeKernel(command_queue, kernel4, 2, NULL,
     global_item_size, local_item_size, 0, NULL, NULL);
  if (ret!=CL_SUCCESS)
  {
    cout << "kernel4 execution failed  ret = " << ret << endl;
    cout << " n = " << n << "  m = " << m << endl;
  }
}
 
opencl_manager::opencl_manager(void) : MAX_SOURCE_SIZE(0x100000),
  platform_id(0),device_id(0)
{}


 cl_int opencl_manager::LoadKernelSource(const char * filename)
 {
   // Load the kernel source code into the array source_str
   FILE *fp;

   fp = fopen(filename, "r");
   if (!fp) 
   {
     fprintf(stderr, "Failed to load kernel source.\n");
     exit(1);
   }
   source_str = (char*)malloc(MAX_SOURCE_SIZE);
   source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
   fclose( fp );
 }



  cl_int opencl_manager::clCreateContext(void)
  {
    cl_int ret;
    context = ::clCreateContext( NULL, 1, 
       &device_id, NULL, NULL, &ret);
    return ret;
  }
 
  cl_int opencl_manager::clCreateCommandQueue(void)
  {
    cl_int ret;
    command_queue = ::clCreateCommandQueue(context,
      device_id, 0, &ret);
    if (ret)
      cerr << "Error creating command queue ret = " << ret << endl;
    else
      cerr << "command queue created successfully "  << endl;
    return ret;
  }



  cl_int opencl_manager::clGetPlatformIDs(void)
  {
    return ::clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  }

  cl_int opencl_manager::clGetDeviceIDs(void)
  {
    return ::clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU, 1,
          &device_id, &ret_num_devices);
  }
  void opencl_manager::setup_GPU(void)
  {
    clGetPlatformIDs();
    clGetDeviceIDs();
    clCreateContext();
    clCreateCommandQueue();
  }
  
  cl_int opencl_manager::CreateBuffers(int n,int rn)
  {
    int nn=n*n;
    cl_int retsave=0;
    cl_int ret;
    K_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
       nn * sizeof(double), NULL, &ret);
    if (ret!=CL_SUCCESS)
    {
      cout << "K buffer creation failed" << endl;
         exit(1);
    }
    retsave = retsave || ret;

   g_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   Kg_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   s_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   s1_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   s2_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   t_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   y_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   ky_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
          n * sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   ty_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, //CL_MEM_WRITE_ONLY,
          sizeof(double), NULL, &ret);
    retsave = retsave || ret;
   sy_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
          sizeof(double), NULL, &ret);
    retsave = retsave || ret;
    if (ret==0)
      cout << "All buffers created successfully " << endl;
    return retsave;
  }

cl_int opencl_manager::CreateKernels(void)
{  
  cl_int ret;
  cl_int retsave;
  retsave=0;
  // Create a program from the kernel source
  program = clCreateProgramWithSource(context, 1,
          (const char **)&source_str, (const size_t *)&source_size, &ret);
  retsave = retsave || ret;
  cout << "Program creation code = " << ret << endl;

  // Build the program
  ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
  retsave = retsave || ret;
    cout << "Program build code = " << ret << endl;
  
  // Create the OpenCL kernel
  kernel2 = clCreateKernel(program, "Vecdot", &ret);
  retsave = retsave || ret;
     cout << "Create Kernel2 error code = " << ret << endl;
 
  kernel = clCreateKernel(program, "bfgs", &ret);
  retsave = retsave || ret;
  cout << "Create Kernel error code = " << ret << endl;

  kernel3 = clCreateKernel(program, "bfgs2", &ret);
  retsave = retsave || ret;
  cout << "Create Kernel3 error code = " << ret << endl;

  kernel4 = clCreateKernel(program, "Kinitialize", &ret);
  retsave = retsave || ret;
  cout << "Create Kernel4 error code = " << ret << endl;
  
  kernel1 = clCreateKernel(program, "MatVecMul", &ret);
  retsave = retsave || ret;
  cout << "Create Kernel1 error code = " << ret << endl;
  return retsave;
}

cl_int opencl_manager::Matrix_vector_multiplication(const dvector& s,
  const dvector & y,int n,int m)
{
  cl_int ret;

  ret = clEnqueueWriteBuffer(command_queue, s_mem_obj, CL_TRUE, 0,
          n * sizeof(double), star(s), 0, NULL, NULL);

  ret = clEnqueueWriteBuffer(command_queue,y_mem_obj,CL_TRUE,0,
          n * sizeof(double), star(y), 0, NULL, NULL);

  int m1=256;
  size_t global_item_size1[3]={n,m1,1};  // nxn work items
  size_t local_item_size1[3] = {1,m1,1}; // Process in groups of size mxm 
  int no=0;
  ret = clSetKernelArg(kernel1,no++, sizeof(cl_mem), (void *)&K_mem_obj);
  ret = clSetKernelArg(kernel1,no++, sizeof(cl_mem), (void *)&y_mem_obj);
  ret = clSetKernelArg(kernel1,no++, sizeof(cl_mem), (void *)&ky_mem_obj);
  ret = clSetKernelArg(kernel1,no++, sizeof(int), (void *)&n);
  ret = clSetKernelArg(kernel1,no++, sizeof(int), (void *)&m);
  // Execute the OpenCL kernel on the list
  ret = clEnqueueNDRangeKernel(command_queue, kernel1, 2, NULL,
      global_item_size1, local_item_size1, 0, NULL, NULL);
  if (ret!=CL_SUCCESS)
  cout << "kernel1 execution failed" << endl;
}  
cl_int opencl_manager::Matrix_mvector_multiplication(const dvector & _g,
  const dvector & _Kmg,int n,int m)
{
  ADUNCONST(dvector,Kmg)
  ADUNCONST(dvector,g)
  cl_int ret;

  dvector mg(1,n);
  mg=-g;
  ret = clEnqueueWriteBuffer(command_queue,g_mem_obj,CL_TRUE,0,
          n * sizeof(double), star(mg), 0, NULL, NULL);

  int m1=256;
  size_t global_item_size1[3]={n,m1,1};  // nxn work items
  size_t local_item_size1[3] = {1,m1,1}; // Process in groups of size mxm 
  int no=0;
  ret = clSetKernelArg(kernel1,no++, sizeof(cl_mem), (void *)&K_mem_obj);
  ret = clSetKernelArg(kernel1,no++, sizeof(cl_mem), (void *)&g_mem_obj);
  ret = clSetKernelArg(kernel1,no++, sizeof(cl_mem), (void *)&Kg_mem_obj);
  ret = clSetKernelArg(kernel1,no++, sizeof(int), (void *)&n);
  ret = clSetKernelArg(kernel1,no++, sizeof(int), (void *)&m);
  // Execute the OpenCL kernel on the list
  ret = clEnqueueNDRangeKernel(command_queue, kernel1, 2, NULL,
      global_item_size1, local_item_size1, 0, NULL, NULL);
  if (ret!=CL_SUCCESS)
  cout << "kernel1 execution failed" << endl;
  ret = clEnqueueReadBuffer(command_queue, Kg_mem_obj, CL_TRUE, 0,
            n*sizeof(double), star(Kmg), 0, NULL, NULL);
}  


cl_int opencl_manager::vector_vector_multiplications(int n,int m1)
{
 //dot product of t=K*y and y to be put in ty
 int no=0;
 cl_int ret;
 ret = clSetKernelArg(kernel2,no++, sizeof(cl_mem), (void *)&ky_mem_obj);
 ret = clSetKernelArg(kernel2,no++, sizeof(cl_mem), (void *)&y_mem_obj);
 ret = clSetKernelArg(kernel2,no++, sizeof(cl_mem), (void *)&ty_mem_obj);
 ret = clSetKernelArg(kernel2,no++, sizeof(int), (void *)&n);
 ret = clSetKernelArg(kernel2,no++, sizeof(int), (void *)&m1);
 size_t global_item_size2[3]={m1,1,1};  // nxn work items
 size_t local_item_size2[3] = {m1,1,1}; // Process in groups of size mxm 
 ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL,
    global_item_size2, local_item_size2, 0, NULL, NULL);
 if (ret!=CL_SUCCESS)
   cout << "kernel2 execution failed" << endl;
 /*
 dvector v(1,n);
 dvector w(1,n);
 dvector s(1,n);
 ret = clEnqueueReadBuffer(command_queue, ky_mem_obj, CL_TRUE, 0,
            n*sizeof(double), star(v), 0, NULL, NULL);
 ret = clEnqueueReadBuffer(command_queue, y_mem_obj, CL_TRUE, 0,
            n*sizeof(double), star(w), 0, NULL, NULL);
 ret = clEnqueueReadBuffer(command_queue, s_mem_obj, CL_TRUE, 0,
            n*sizeof(double), star(s), 0, NULL, NULL);
 cout << "norm2(s) " << norm2(s) << endl;
 cout << "norm2(y) " << norm2(w) << endl;
 double ty;
 ret = clEnqueueReadBuffer(command_queue, ty_mem_obj, CL_TRUE, 0,
            sizeof(double), &ty, 0, NULL, NULL);
 cout <<  " n = " << n << " m1 = " << m1 << endl;
 cout << "Z  v*w  = " << v*w << " " << ty << endl;
 */

  // dot product of s and y to be put in sy
  no=0;
  ret = clSetKernelArg(kernel2,no++, sizeof(cl_mem), (void *)&s_mem_obj);
  ret = clSetKernelArg(kernel2,no++, sizeof(cl_mem), (void *)&y_mem_obj);
  ret = clSetKernelArg(kernel2,no++, sizeof(cl_mem), (void *)&sy_mem_obj);
  ret = clSetKernelArg(kernel2,no++, sizeof(int), (void *)&n);
  ret = clSetKernelArg(kernel2,no++, sizeof(int), (void *)&m1);
  
  ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL,
    global_item_size2, local_item_size2, 0, NULL, NULL);
  if (ret!=CL_SUCCESS)
      cout << "kernel2 execution failed" << endl;
 /*
 ret = clEnqueueReadBuffer(command_queue, s_mem_obj, CL_TRUE, 0,
            n*sizeof(double), star(v), 0, NULL, NULL);
 ret = clEnqueueReadBuffer(command_queue, y_mem_obj, CL_TRUE, 0,
            n*sizeof(double), star(w), 0, NULL, NULL);
 double sy;
 ret = clEnqueueReadBuffer(command_queue, sy_mem_obj, CL_TRUE, 0,
            sizeof(double), &sy, 0, NULL, NULL);
 cout <<  " n = " << n << " m1 = " << m1 << endl;
 cout << " norm2(s) = " << norm2(v) << " norm2(y)  = " << norm2(w) << endl;
 cout << "Z2  v*w  = " << v*w << " " << sy << "ret = " << ret << endl;
 */
}


cl_int opencl_manager::BFGS_update(int n,int m)
{
  int no=0;
  cl_int ret;
  ret = clSetKernelArg(kernel3,no++, sizeof(cl_mem), (void *)&K_mem_obj);
  ret = clSetKernelArg(kernel3,no++, sizeof(cl_mem), (void *)&s_mem_obj);
  ret = clSetKernelArg(kernel3,no++, sizeof(cl_mem), (void *)&ky_mem_obj);
  ret = clSetKernelArg(kernel3,no++, sizeof(cl_mem), (void *)&y_mem_obj);
  ret = clSetKernelArg(kernel3,no++, sizeof(cl_mem), (void *)&sy_mem_obj);
  ret = clSetKernelArg(kernel3,no++, sizeof(cl_mem), (void *)&ty_mem_obj);
  ret = clSetKernelArg(kernel3,no++, sizeof(int), (void *)&n);
  ret = clSetKernelArg(kernel3,no++, sizeof(int), (void *)&m);
  size_t global_item_size[3]={n,n,1};  // nxn work items
  size_t local_item_size[3] = {m,m,1}; // Process in groups of size mxm 
 /*
 dvector v(1,10);
 ret = clEnqueueReadBuffer(command_queue, K_mem_obj, CL_TRUE, 0,
            10*sizeof(double), star(v), 0, NULL, NULL);
  cout << " m = " << m << " n = " << n << endl;
  cout << "U1  K  = " << v << endl;
 */

 // Execute the OpenCL kernel on the list
 ret = clEnqueueNDRangeKernel(command_queue, kernel3, 2, NULL,
    global_item_size, local_item_size, 0, NULL, NULL);
 if (ret!=CL_SUCCESS)
   cout << "kernel3 execution failed ret = " << ret << endl;

 /*
 ret = clEnqueueReadBuffer(command_queue, K_mem_obj, CL_TRUE, 0,
            10*sizeof(double), star(v), 0, NULL, NULL);
  cout << "U2   K  = " << v << endl;
 */
  return ret;
}  

opencl_manager * pocl=0;

void fmm::fmin(BOR_CONST double& _f, const dvector & _x,BOR_CONST dvector& _g)
{
  if (pV==0)
  {
    int nv=roundup(_x.indexmax());
    pocl=new opencl_manager;
    pocl->setup_GPU();

    cerr << "Number of devices found " << pocl->ret_num_devices << endl;
    if (pocl->ret_num_devices==0)
    {
      if (pocl)
        delete pocl;
      pocl=0;
      cerr << "No GPU found" << endl;
      exit(1);
    }
    else
    {
      int ret;
      ret=pocl->LoadKernelSource("bfg2.cl");
      if (ret)
        cerr << "Error trying to load Kernel source  GPU" << endl;
      ret=pocl->CreateBuffers(nv);
      if (ret)
        cerr << "Error trying to create buffers on GPU" << endl;
      ret=pocl->CreateKernels();
      if (ret)
        cerr << "Error trying to create Kernel " << endl;
      int mocl=256;
      ret=pocl->Kinitialize(nv,mocl);
    }

    pV=new dvector(1,n);
    //pstep=new dvector(1,n);
    //(*pstep).initialize();
    oldx=new dvector(1,n);
    oldg=new dvector(1,n);
    (*oldx)=_x;
    (*oldg).initialize();
    pK=new dmatrix(1,n,1,n);
    pK->initialize();
    for (int i=1;i<=n;i++)
    {
      (*pK)(i,i)=1.0;
    }
  }
  if (log_values_switch)
  {
    print_values(_f,_x,_g);
  }
  if (pfmintime==0) pfmintime=new adtimer;
  tracing_message(traceflag,"A3");
  dvector& g=(dvector&) _g;
  double& f=(double&) _f;
  independent_variables& x= (independent_variables&) _x;
    #ifdef DIAG
      cout << "On entry to fmin: " << *this << endl;
    #endif
  tracing_message(traceflag,"A4");
#if !defined (__MSVC32__)
    #if defined( __SUN__) && !(defined __GNU__)
      #if defined( __HP__)
        if (ireturn <= 0 )
        {
	   signal(SIGINT, &onintr);
        }
      #else
        if (ireturn <= 0 )
        {
	   signal(SIGINT, (SIG_PF)&onintr);
        }
      #endif
    #endif
 #endif
    #if defined( __GNU__) || defined (__BORLANDC__)
      if (ireturn <= 0 ) 
      {
	 signal(SIGINT, &onintr);
      }
    #endif
    #ifdef __ZTC__
      if (ireturn <= 0 ) 
      {
        if (disp_inited == 0)
        {
          disp_open();
          disp_usebios();
        }
      }
    #endif
  tracing_message(traceflag,"A5");
      if (ireturn ==1 && dcheck_flag ==0) 
      {
        ireturn = 3;
      }
      if (ireturn >= 3)
      {
         derch(f, x, g, n, ireturn);
         return;
      }
      if (ireturn == 1) goto call1;
      if (ireturn == 2) goto call2;
      fbest=1.e+100;
  tracing_message(traceflag,"A6");
      if (!h) h.allocate(n);
      w.initialize();
      alpha=1.0;
      ihflag=0;
     if (n==0) 
     { 
       cerr << "Error -- the number of active parameters"
         " fmin must be > 0\n";
       ad_exit(1);
     } 
  tracing_message(traceflag,"A7");
     if (x.indexmin() !=1) 
     { 
       cerr << "Error -- minimum valid index"
         " for independent_variables in fmin must be 1\n"
        << " it is " << x.indexmin() << "\n";
        ad_exit(1);
     } 
     if (x.size() <n) 
     { 
       cerr << "Error -- the size of the independent_variables"
        " which is " << x.size() << " must be >= " << n << "\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     } 
  tracing_message(traceflag,"A8");
     if (g.indexmin() !=1) 
     { 
       cerr << "Error -- minimum valid index"
         " for the gradient vector in fmin must be 1\n"
        << " it is " << g.indexmin() << "\n";
        ad_exit(1);
     } 
     if (g.size() <n) 
     { 
       cerr << "Error -- the size of the gradient vector"
        " which is " << g.size() << " must be >=\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     } 
  tracing_message(traceflag,"A9");
     for (i=1; i<=n; i++)
           xx.elem(i)=x.elem(i); 
  tracing_message(traceflag,"A10");
      itn=0;
      icc=0;
       for (i=1; i< 11; i++)
          funval.elem(i)=0.;
  tracing_message(traceflag,"A11");
      ihang = 0;
      llog=1;
      np=n+1;
      n1=n-1;
      nn=n*np/2;
      is=n;
      iu=n;
      iv=n+n;
      ib=iv+n;
      iexit=0;
  tracing_message(traceflag,"A12");

      //hcalcs0(n,h,dmin);
      dmin=1.0;

      if (dmin <= 0.)
         goto label7020;
      if(dfn == 0.)
         z = 0.0; 
  tracing_message(traceflag,"A14");
      for (i=1; i<=n; i++)
      {
        xsave.elem(i)=x.elem(i);
        x.elem(i)=xx.elem(i);
      }
      ireturn=1;
  tracing_message(traceflag,"A15");
      if (h.disk_save())
      {
        cout << "starting hessian save" << endl;
        h.save();
        cout << "finished hessian save" << endl;
      }
  tracing_message(traceflag,"A16");
      return;
  call1:
  tracing_message(traceflag,"A17");
      if (h.disk_save())
      {
        cout << "starting hessian restore" << endl;
        h.restore();
        cout << "finished hessian restore" << endl;
      }
  tracing_message(traceflag,"A18");
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i);
      }
      ireturn=3;
  tracing_message(traceflag,"A19");
      {
      }
      for ( i=1; i<=n; i++)
         gbest.elem(i)=g.elem(i);
  tracing_message(traceflag,"A20");
      funval.elem(10) = f;
      df=dfn;
      if(dfn == 0.0)
         df = f - z;
      if(dfn < 0.0)
         df=fabs(df * f);
      if(df <= 0.0)
         df=1.;
label20:
      ic=0;
      iconv = 1;
      for ( i=1; i<=9; i++)
         funval.elem(i)= funval.elem(i+1);
      funval.elem(10) = f;
      if ( itn>15 && fabs( funval.elem(1)-funval.elem(10))< min_improve )
         ihang = 1;
      gmax = 0;
      for ( i=1; i<=n; i++)
      {
        if(fabs(g.elem(i)) > crit) iconv = 2;
        if(fabs(g.elem(i)) > fabs(gmax) ) gmax = g.elem(i);
      }
      if( iconv == 1 || ihang == 1)
      {
         ireturn=-1;
         goto label92;
      }
      if(iprint == 0)
         goto label21;
      if(itn == 0)
         goto label7000;
#if defined(USE_DDOUBLE)
#undef double
      if(fmod(double(itn),double(iprint)) != 0)
         goto label21;
#define double dd_real
#else
      if(fmod(double(itn),double(iprint)) != 0)
         goto label21;
#endif
      if (llog) goto label7010;
#     if   !defined (__MSVC32__)  && !defined (__WAT32__) && !defined(linux)
        if (!scroll_flag) clrscr();
#     endif
label7003:
      if (iprint>0)
      {
	if (ad_printf) 
        {
          (*ad_printf)("%d variables; iteration %ld; function evaluation %ld", n, itn, ifn);
          if (pointer_to_phase)
          {
            (*ad_printf)("; phase %d", *pointer_to_phase);
          }
	  (*ad_printf)("\nFunction value %15.7le; maximum gradient component mag %12.4le\n",
#if defined(USE_DDOUBLE)
#undef double
              double(f), double(gmax));
#define double dd_real
#else
              f, gmax);
#endif
        }
      }
label7002:
      if(iprint>0) 
      {
        fmmdisp(x, g, n, this->scroll_flag,noprintx);
      }
label21 :
      {
  
        // set USE_GPU_FLAG=1 to test out the GPU
        int USE_GPU_FLAG=1;
        if (USE_GPU_FLAG==0)
        { 
          dvector y=g-(*oldg);
          dvector s=xx(1,n)-(*oldx);
          if (itn>0)
          {
              bfgs_update(s,y,*pK);    
          }
          mat_vec_neg_mult(*pK,*pV,g);
          //ofstream ofs("CPU",ios::app);
          //ofs << setprecision(10) << *pV << endl;
        }
        else
        { 
          int nv=roundup(g.indexmax());

          if (nv==n)
          {
            dvector y=g-(*oldg);
            dvector s=xx(1,n)-(*oldx);
            int mocl=16;
            if (itn>0)
            {
              ocl_bfgs_update(s,y,n,mocl);  
            }
            dvector Kmg(1,n);
            pocl->Matrix_mvector_multiplication(g,Kmg,n,mocl);
            *pV=Kmg;
          }
          else
          {
            // pad vectors up to 256 
            dvector y(1,nv);
            dvector s(1,nv);
            dvector gb(1,nv);
            y(1,n)=g-(*oldg);
            s(1,n)=xx(1,n)-(*oldx);
            gb(1,n)=g;
            gb(n+1,nv).initialize();
            y(n+1,nv).initialize();
            s(n+1,nv).initialize();
            int mocl=16;
            if (itn>0)
            {
              ocl_bfgs_update(s,y,nv,mocl);  
            }
            dvector Kmg(1,nv);
            pocl->Matrix_mvector_multiplication(gb,Kmg,nv,mocl);
            *pV=Kmg(1,n);
          }
          //ofstream ofs("GPU",ios::app);
          //ofs << setprecision(10) << *pV << endl;
        }

      }

      itn=itn+1;
      for (i=1; i<=n; i++)
         x.elem(i)=xx.elem(i);
      (*oldx)=x;
      (*oldg)=g;
      pfmintime->get_elapsed_time_and_reset();

      w(n+1,2*n).shift(1)= *pV;

      gs=0.0;
      for (i=1; i<=n; i++)
         gs+=w.elem(is+i)*g.elem(i);
      iexit=2;
      if(gs >= 0.0)
         goto label92;
      gso=gs;
      alpha=-2.0*df/gs;
      if(alpha > 1.0)
        alpha=1.0;
      df=f;
      tot=0.0;
label30:
      iexit=3;
      if (ialph) { goto label92; }
      if( ifn >= maxfn)
      {
         maxfn_flag=1;
         goto label92;
      }
      else
      {
         maxfn_flag=0;
         iexit=1;
      }
      if(quit_flag) goto label92;
      for (i=1; i<=n; i++)
         {
         z=alpha*w.elem(is+i);
         xx.elem(i)+=z;
         //(*pstep)(i)+=alpha*w.elem(is+i);
         }
      for (i=1; i<=n; i++)
      {
        xsave.elem(i)=x.elem(i);
        gsave.elem(i)=g.elem(i);
        x.elem(i)=xx.elem(i);
        fsave = f;
      }
      fsave = f;
      ireturn=2;
      if (h.disk_save())
      {
        cout << "starting hessian save" << endl;
        h.save();
        cout << "finished hessian save" << endl;
      }
      return;
  call2:
      if (h.disk_save())
      {
        cout << "starting hessian restore" << endl;
        h.restore();
        cout << "finished hessian restore" << endl;
      }
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i);
        w.elem(i)=g.elem(i);
        g.elem(i)=gsave.elem(i);
      }
      fy = f;
      f = fsave;
      ireturn=-1;
      if (fy <= fbest)
      {
        fbest=fy;
        for (i=1; i<=n; i++)
        {
          x.elem(i)=xx.elem(i);
          gbest.elem(i)=w.elem(i);
        }
      }
      if (use_control_c==1)         
      {
#if (defined( __SUN__) && !defined(__GNU__)) || defined(UNIXKLUDGE) || defined(linux)
         if(ctlc_flag || ifn == dcheck_flag )
  #elif defined(__BORLANDC__)
         if ( kbhit() || ctlc_flag|| ifn == dcheck_flag )
  #else
         if ( kbhit() || ifn == dcheck_flag )
  #endif
         {
            int c=0;
            if (ifn != dcheck_flag)
            {
            #if !defined(__GNUDOS__)  || defined(UNIXKLUDGE)  || defined(linux) \
  	      || defined(__CYGWIN32__) || defined(__MINGW32__)
              c = toupper(getch());
            #else
              c = toupper(getxkey());
            #endif
            }
            else
              c='C';
            if ( c == 'C')
            {
              for (i=1; i<=n; i++)
              {
                x.elem(i)=xx.elem(i);
              }
              ireturn = 3;
              derch(f, x , w, n, ireturn);
              return;
            }
            else 
            {
              if ( c == 'Q'|| c == 'N') 
              {
                quit_flag=c;
                goto label92;
              }
              else
              {
                quit_flag=0;
              }
            }
         }
       }
       if (quit_flag)
       {
	 if (quit_flag==1) quit_flag='Q';
	 if (quit_flag==2) quit_flag='N';
         goto label92;
       }
       icc+=1;
       if( icc >= 5)
          icc=0;
      ic++;
      if( ic >imax)
      {
         if (iprint>0)
         {
           if (ad_printf) (*ad_printf)("  ic > imax  in fminim is answer attained ?\n" );
           fmmdisp(x, g, n, this->scroll_flag,noprintx);
         }
         ihflag=1;
         ihang=1;
         goto label92;
      }
      ifn++;
      gys=0.0;
      for (i=1; i<= n; i++)
         gys+=w.elem(i)*w.elem(is+i);
      if(fy>f+fringe)
      {
         goto label40;
      }
      if(fabs(gys/gso)<=.9)
         goto label50;
      if(fabs(gys/gso)<=.95 && ic > 4)
         goto label50;
      if(gys>0.0)
         goto  label40;
      tot+=alpha;
      z=10.0;
      if(gs<gys)
         z=gys/(gs-gys);
      if(z>10.0)
         z=10.0;
      alpha=alpha*z;
      if (alpha == 0.)
      {
         ialph=1;
         #ifdef __ZTC__
         if (ireturn <= 0)
         {
           disp_close();
         }
         #endif
         return;
      }
      f=fy;
      gs=gys;
      goto label30;
label40:
      for (i=1;i<=n;i++)
         xx.elem(i)-=alpha*w.elem(is+i);
      if (alpha == 0.)
      {
        ialph=1;
        return;
      }
      z=3.0*(f-fy)/alpha+gys+gs;
      zz=dafsqrt(z*z-gs*gys);
      z=1.0-(gys+zz-z)/(2.0*zz+gys-gs);
      if (fabs(fy-1.e+95) < 1.e-66)
      {
        alpha*=.001;
      }
      else
      {
        if (z>10.0) 
        {
          cout << "large z" << z << endl;
          z=10.0;
        }
        alpha=alpha*z;
      }
      if (alpha == 0.)
      {
         ialph=1;
        if (ialph)
        {
	   if (ad_printf) (*ad_printf)("\nFunction minimizer: Step size"
            "  too small -- ialph=1");
        }
         return;
      }
      goto label30;
label50:
      alpha+=tot;
      f=fy;
      df-=f;
      dgs=gys-gso;
      xxlink=1;
      if(dgs+alpha*gso>0.0)
         goto label52;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=w.elem(i)-g.elem(i);
      sig=1.0/(alpha*dgs);
      goto label70;
label52:
      zz=alpha/(dgs-alpha*gso);
      z=dgs*zz-1.0;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=z*g.elem(i)+w.elem(i);
      sig=1.0/(zz*dgs*dgs);
      goto label70;
label60:
      xxlink=2;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=g.elem(i);
      if(dgs+alpha*gso>0.0)
         goto label62;
      sig=1.0/gso;
      goto  label70;
label62:
      sig=-zz;
      goto label70;
label65:
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
      goto  label20;
label70:
      w.elem(iv+1)=w.elem(iu+1);
      pfmintime->get_elapsed_time_and_reset();

      //hcalcs2(n,n1,np,iv,iu,ib,h,g,w,sig,dmin);

      if (xxlink == 1) goto label60;
      if (xxlink == 2) goto label65;
label90:
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
label92:
      if (iprint>0)
      {
        if (ialph)
        {
	   if (ad_printf) (*ad_printf)("\nFunction minimizer: Step size too small -- ialph=1");
        }
        if (ihang == 1)
        {
	   if (ad_printf) (*ad_printf)("Function minimizer not making progress ... is minimum attained?\n");
#if defined(USE_DDOUBLE)
#undef double
           if (ad_printf) (*ad_printf)("Minimprove criterion = %12.4le\n",double(min_improve));
#define double dd_real
#else
           if (ad_printf) (*ad_printf)("Minimprove criterion = %12.4le\n",min_improve);
#endif
        }
      }
      if(iexit == 2)
      {
        if (iprint>0)
        {
          if (ad_printf) (*ad_printf)("*** grad transpose times delta x greater >= 0\n"
           " --- convergence critera may be too strict\n");
          ireturn=-1;
        }
      }
#     if defined (__MSVC32__)  && !defined (__WAT32__)
        if (scroll_flag == 0) clrscr();
#     endif
      if (maxfn_flag == 1)
      {
        if (iprint>0)
        {
	  if (ad_printf) (*ad_printf)("Maximum number of function evaluations exceeded");
        }
      }
      if (iprint>0)
      {
        if (quit_flag == 'Q')
          if (ad_printf) (*ad_printf)("User initiated interrupt");
      }
      if(iprint == 0) goto label777;
      if (ad_printf) (*ad_printf)("\n - final statistics:\n");
      if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
	      n, itn, ifn);
#if defined(USE_DDOUBLE)
#undef double
      if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
              double(f), double(gmax));
      if (ad_printf) (*ad_printf)("Exit code = %ld;  converg criter %12.4le\n",iexit,double(crit));
#define double dd_real
#else
      if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
              f, gmax);
      if (ad_printf) (*ad_printf)("Exit code = %ld;  converg criter %12.4le\n",iexit,crit);
#endif
      fmmdisp(x, g, n, this->scroll_flag,noprintx);
label777:
         if (ireturn <= 0)
         #ifdef DIAG
           if (ad_printf) (*ad_printf)("Final values of h in fmin:\n");
           cout << h << "\n";
         #endif
         #ifdef __ZTC__
         {
           disp_close();
         }
         #endif
         return;
label7000:
      if (iprint>0)
      {
#     if defined (__MSVC32__)  && !defined (__WAT32__)
        if (!scroll_flag) clrscr();
#endif
        if (ad_printf) (*ad_printf)("\nInitial statistics: ");
      }
      goto label7003;
label7010:
   if (iprint>0)
   {
#     if defined (__MSVC32__)  && !defined (__WAT32__)
     if (!scroll_flag)  clrscr();
#endif
     if (ad_printf) (*ad_printf)("\nIntermediate statistics: ");
   }
   llog=0;
   goto label7003;
label7020:
   if (iprint>0)
   {
     if (ad_printf) (*ad_printf)("*** hessian not positive definite\n");
   } 
         #ifdef __ZTC__
         if (ireturn <= 0)
         {
           disp_close();
         }
         #endif
         return;
   }

/**
 * Description not yet available.
 * \param
 */
   double dafsqrt( double x )
   {
   if (x>0)
      return(sqrt(x));
   else
      return(0.);
   }

    void bfgs_update(dvector & s,dvector & y,dmatrix & K)   
    {
      int n=s.indexmax();
      /*
      dmatrix K1(1,n,1,n);
      K1=K;
      {
        dvector t=K*y;   // symmetrixc matrix * vector
        dvector tsave=y*K;   // symmetrixc matrix * vector
        double sy=s*y;  // vector dot product
        double yt=y*t;  // vector dot product
        dvector s1=((sy + yt)/square(sy))*s;
        dvector s2=s/sy;
        // this is the update for the inverse of the Hessian
        K1=K1+outer_prod(s1,s)-outer_prod(t,s2)-outer_prod(s2,t);
      }
      */


      int i;
      dvector t(1,n);
      for (i=1;i<=n;i++)
      {
        double tmp=0.0;
        double * yj=&y(1);
        double * Kij=&K(i,1);
        for (int j=1;j<=n;j++)
        {
          tmp+= *Kij++ * *yj++;
        }
        t(i)=tmp;
      }
      //cout << "MM norm2(s) = " << norm2(s) << endl;
      double sy=s*y;  // vector dot product
      double yt=y*t;  // vector dot product
      dvector s1=((sy + yt)/square(sy))*s;
      dvector s2=s/sy;
      for (i=1;i<=n;i++)
      {
        double s1i=s1[i];
        double s2i=s2[i];
        double ti=t[i];
        double * sj=&s[1];
        double * tj=&t[1];
        double * s2j=&s2[1];
        for (int j=1;j<=i;j++)
        {
          K.elem(i,j)+=s1i* *sj++ -ti* *s2j++ -s2i* *tj++;
          K.elem(j,i)=K.elem(i,j);
        }
      }
      //cout << "HF norm2(K1-K)= " <<  norm2(K1-K)   << endl;
    }   

    void ocl_bfgs_update(dvector & s,dvector & y,int n,int m)   
    {
      pocl->Matrix_vector_multiplication(s,y,n,m);

      pocl->vector_vector_multiplications(n,m);

      int mocl=
      pocl->BFGS_update(n,m);
    }   



    void mat_vec_neg_mult(const dmatrix &K,dvector & v,
      const dvector & _g)
    {
      ADUNCONST(dvector,g)


    // void mat_vec_neg_mult(const dmatrix &K,dvector & v,
    //   const dvector & g)
    // {
      int n=g.indexmax();
      int i;
      for (i=1;i<=n;i++)
      {
        double tmp=0.0;
        double * gj=&g(1);
        double * K1ij=&( (*pK)(i,1));
        for (int j=1;j<=n;j++)
        {
          tmp+= *K1ij++ * *gj++;
        }
        v(i)=-tmp;
      }
      //cout << "BW " << norm2(v+K*g) << endl;
    }
