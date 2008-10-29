#ifndef _ADSPLUS_H_
  #define _ADSPLUS_H_
#include <admodel.h>
#include <spcomm.h>
//char cc[40]={"Copyright (c) 1993,1994 Otter Research Ltd"};
//#define DO_PROFILE
#pragma interface
//#include <admodhd.h>

class SPparam_init_number: public param_init_number 
{
public:
  SPparam_init_number(void ): param_init_number() {;} 
protected:
  void allocate(int phase_start=1,const char *s="UNNAMED");
  void allocate(const char *s="UNNAMED");
  friend class model_parameters;
};

class SPparam_init_vector: public param_init_vector
{
public:
  SPparam_init_vector(void ): param_init_vector() {;} 
  void allocate(int phasestart=1,const char * s="UNNAMED");
  void allocate(const char * s="UNNAMED");
  friend class model_parameters;
};


class SPnamed_dvar_vector: public named_dvar_vector
{
public:
  SPnamed_dvar_vector(void ): named_dvar_vector() {;} 
  SPnamed_dvar_vector& operator = (_CONST dvar_vector& m);
  SPnamed_dvar_vector& operator = (_CONST dvector& m);
  SPnamed_dvar_vector& operator = (CGNU_DOUBLE m);
  SPnamed_dvar_vector& operator = (_CONST prevariable& m);
  friend class model_parameters;
  //void allocate(int mmin,int mmax,const char * s);
  ~SPnamed_dvar_vector(void ); //{SPsend(*this);}
};

class SPnamed_dvector: public named_dvector
{
public:
  SPnamed_dvector(void ): named_dvector() {;} 
  SPnamed_dvector& operator = (_CONST dvector& m);
  SPnamed_dvector& operator = (CGNU_DOUBLE m);
  friend class model_parameters;
  void allocate(int mmin,int mmax,const char * s);
  ~SPnamed_dvector(void ); //{SPsend(*this);}
};


class SPnamed_dvariable : public named_dvariable
{
protected:
  SPnamed_dvariable(void) : named_dvariable(){}
  SPnamed_dvariable& operator = (_CONST prevariable& m);
  SPnamed_dvariable& operator = (CGNU_DOUBLE m);
  ~SPnamed_dvariable(void);
  friend class model_parameters;
};

class SPnamed_dvar_matrix : public named_dvar_matrix
{
protected:
  SPnamed_dvar_matrix(void) : named_dvar_matrix() {}
public:
  SPnamed_dvar_matrix& operator = (CGNU_DOUBLE m);
  SPnamed_dvar_matrix& operator = (_CONST dmatrix& m);
  SPnamed_dvar_matrix& operator = (_CONST dvar_matrix& m);
  friend class model_parameters;
  ~SPnamed_dvar_matrix();
};

class SPnamed_dmatrix : public named_dmatrix
{
protected:
  SPnamed_dmatrix(void) : named_dmatrix() {}
public:
  SPnamed_dmatrix& operator = (CGNU_DOUBLE m);
  SPnamed_dmatrix& operator = (_CONST dmatrix& m);
  friend class model_parameters;
  ~SPnamed_dmatrix();
};


class SPparam_init_bounded_number: public param_init_bounded_number
{
public:
  SPparam_init_bounded_number(void ): param_init_bounded_number() {;} 
protected:
  void allocate(double _minb,double _maxb,int phase_start=1,
    const char * s="UNNAMED");
  void allocate(double _minb,double _maxb,const char * s="UNNAMED");
};


class SPparam_init_matrix: public param_init_matrix 
{
public:
  SPparam_init_matrix(void ): param_init_matrix() {;} 
protected:
  void allocate(int phase_start=1,const char * = "UNNAMED");
  void allocate(const char * = "UNNAMED");
};

class SPparam_init_bounded_matrix: public param_init_bounded_matrix 
{
public:
  SPparam_init_bounded_matrix(void ): param_init_bounded_matrix() {;} 

public:

  void allocate(double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(double _minb,double _maxb,const char * = "UNNAMED");
};


class SPdata_int : public data_int  
{
public:
  SPdata_int(void) : data_int() {;}  
  void allocate(int n,const char * s="UNNAMED");
  void allocate(const char * s="UNNAMED");
};

class SPdata_matrix : public data_matrix  
{
public:
  SPdata_matrix(void) : data_matrix() {;}  
  void allocate(const char * = "UNNAMED");
};

class SPdata_3array : public data_3array 
{
public:
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * ="UNNAMED");
/*
  void allocate(int hsl,int hsu,_CONST ivector& rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,_CONST ivector& rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl,int hsu,_CONST ivector& rmin,_CONST ivector& rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,_CONST ivector& cmin,int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,_CONST ivector& cmin,
    _CONST ivector& cmax,const char * ="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,
    _CONST ivector& cmax,const char * ="UNNAMED");
*/
};

class SPdata_4array : public data_4array 
{
public:
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
};

class SPdata_imatrix : public data_imatrix 
{
public:
  //void allocate(int rmin,int rmax,int cmin,int cmax,const char * ="UNNAMED");
  void allocate(const char * ="UNNAMED");
};

class SPdata_vector : public data_vector
{
public:
  SPdata_vector(void) : data_vector() {;}
  void allocate(const char * ="UNNAMED");
};

class SPdata_ivector : public data_ivector
{
public:
  SPdata_ivector(void) : data_ivector() {;}
  void allocate(int imin,int imax,const char * ="UNNAMED");
};

class SPdata_number : public data_number 
{
public:
  SPdata_number(void) : data_number() {;}
  void allocate(const char * ="UNNAMED");
};

class SPparam_init_bounded_vector: public param_init_bounded_vector
{
public:
  void allocate(double _minb,double _maxb,int phasestart=1,
   const char * name="UNNAMED");
  void allocate(double _minb,double _maxb,const char * name="UNNAMED");
};

#endif

