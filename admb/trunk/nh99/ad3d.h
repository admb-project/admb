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
  param_init_d3array(void);
};

  void param_init_d3array::copy_value_to_vector(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

  void param_init_d3array::restore_value_from_vector(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

  void param_init_d3array::save_value(BOR_CONST ofstream& ofs,int prec)
  {
    ofs << setw(prec+6) << setprecision(prec) << dvar3_array(*this) << endl;
  }

  void param_init_d3array::allocate(int smin,int smax,int rmin,int rmax,
    int cmin,int cmax,const char * s)
  {
    allocate(smin,smax,rmin,rmax,cmin,cmax,phase_start,s);
  }

  void param_init_d3array::allocate(int smin,int smax,int rmin,int rmax,
    int cmin,int cmax,int phase_start, const char * s)
  {
    named_dvar3_array::allocate(smin,smax,rmin,rmax,cmin,cmax,s);
    initial_params::allocate(phase_start);
    if (ad_comm::global_parfile)
    {
      *(ad_comm::global_parfile) >> dvar3_array(*this);
    }
    else
    {
      dvar3_array::operator=(initial_value);
    }
  }

  void param_init_d3array::hess_scale(BOR_CONST dvector& v,BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    int smin=slicemin();
    int smax=slicemax();
    for (int k=smin;k<=smax;i++)
    {
      int mmin=(*this(k)).rowmin();
      int mmax=(*this(k)).rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        int cmin=((*this)(k,i)).indexmin();
        int cmax=((*this)(k,i)).indexmax();
        for (int j=cmin;j<=cmax;j++)
        {
          v(ii++)=0.;
        }
      }
    }
  }

  void param_init_d3array::sd_scale(BOR_CONST dvector& v,BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    int smin=slicemin();
    int smax=slicemax();
    for (int k=smin;k<=smax;i++)
    {
      int mmin=(*this(k)).rowmin();
      int mmax=(*this(k)).rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        int cmin=((*this)(k,i)).indexmin();
        int cmax=((*this)(k,i)).indexmax();
        for (int j=cmin;j<=cmax;j++)
        {
          v(ii++)=1.;
        }
      }
    }
  }

cifstream& operator >> (BOR_CONST cifstream& s, param_init_3darray& m)
{
  s >> dvar3_array(m);
  return s;
}

void param_init_d3array::restore_value(BOR_CONST ifstream& ofs)
{
  ofs  >> dvar3_array(*this);
}
