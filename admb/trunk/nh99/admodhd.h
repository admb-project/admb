#ifndef __ADMOD3D__
#define __ADMOD3D__

#pragma interface

#include <admodel.h>

class param_init_d3array: public named_dvar3_array,public initial_params
{
public:

  virtual void set_value(const dvar_vector& x,BOR_CONST int& ii,BOR_CONST dvariable& pen);
  virtual void copy_value_to_vector(BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void restore_value_from_vector(BOR_CONST dvector&,BOR_CONST int&);
  virtual void set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual int size_count(void);
  virtual void save_value(void);
  virtual void save_value(BOR_CONST ofstream& ofs,int prec);
  virtual void restore_value(BOR_CONST ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void hess_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii){};

public:

  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,
    int cmin,int cmax,int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,
    int cmin,int cmax, const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,
    int cmax,int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,
    int cmax,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,
    int cmax,int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,
    int cmax,const char * = "UNNAMED");
  param_init_d3array(void);
};

class param_init_bounded_d3array: public param_init_d3array
{
  double minb;
  double maxb;
public:

  virtual void set_value(const dvar_vector& x,BOR_CONST int& ii,BOR_CONST dvariable& pen);
  virtual void set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void sd_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void hess_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii){};

public:

  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");

  param_init_bounded_d3array(void);
};
#endif

