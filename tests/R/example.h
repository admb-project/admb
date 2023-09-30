extern "C" {

  void 
#ifdef _WIN32
  __stdcall __declspec(dllexport) 
#endif
  simple(int *_n,double *_x,double *_output,char ** dll_options);

  void 
#ifdef _WIN32
  __stdcall __declspec(dllexport) 
#endif
  example();
};
