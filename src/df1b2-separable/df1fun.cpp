/**
 * $Id: df1fun.cpp 1.1 2009/10/22 09:59:51 hsk021 Exp $
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1fun.h>
  prevariable * df1_one_variable::ind_var=0;
  int init_df1_one_variable::num_vars=0;

  df1_one_variable::df1_one_variable(const df1_one_variable& x)
  {
    v[0]=x.v[0];
    v[1]=x.v[1];
  }

 df1_one_vector::df1_one_vector(const df1_one_vector& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
   v = m2.v;
 }

 df1_one_vector::~df1_one_vector()
 {
   deallocate();
 }

 void df1_one_vector::deallocate(void)
 {
   if(shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df1_one_variable*) (shape->trueptr);
       delete [] v;
       v = NULL;
       delete shape;
       shape=0;
     }
   }
 }

 dvector value(const df1_one_vector& v)
 {
   
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   dvector cv(mmin,mmax);
   for (int i=mmin;i<=mmax;i++)
   {
     cv(i)=value(v(i));
   }
   return cv;
 }
   
 dvector first_derivatives(const df1_one_vector& v)
 {
   
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   dvector cv(mmin,mmax);
   for (int i=mmin;i<=mmax;i++)
   {
     cv(i)=*(v(i).get_udot());
   }
   return cv;
 }
   

  void df1_one_vector::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=0.0;
    }
  }

  df1_one_vector::df1_one_vector(void)
  {
    allocate();
  }

  df1_one_vector::df1_one_vector(int min,int max)
  {
    allocate(min,max);
  }

  void df1_one_vector::allocate(int min,int max)
  {
    index_min=min;
    index_max=max;
    v=new df1_one_variable[max-min+1];
    if (v==0)
    {
      cerr << "error allocating memory in df1_one_vector" << endl;
      ad_exit(1);
    }
    if ( (shape=new vector_shapex(min,max,v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df1_one_vector" 
           << endl;;
      ad_exit(1);
    }
    v-=min;
  }
  
  void df1_one_vector::allocate(void)
  {
    index_min=0;
    index_max=-1;
    v=0;
    shape=0;
  }
    

 dmatrix value(const df1_one_matrix& v)
 {
   
   int rmin=v.indexmin();
   int rmax=v.indexmax();
   dmatrix cm(rmin,rmax);
   for (int i=rmin;i<=rmax;i++)
   {
     int cmin=v(i).indexmin();
     int cmax=v(i).indexmax();
     cm(i).allocate(cmin,cmax); 
     for (int j=cmin;j<=cmax;j++)
     {
       cm(i,j)=value(v(i,j));
     }
   }
   return cm;
 }
   
 dmatrix first_derivatives(const df1_one_matrix& v)
 {
   
   int rmin=v.indexmin();
   int rmax=v.indexmax();
   dmatrix cm(rmin,rmax);
   for (int i=rmin;i<=rmax;i++)
   {
     int cmin=v(i).indexmin();
     int cmax=v(i).indexmax();
     cm(i).allocate(cmin,cmax); 
     cm(i)=first_derivatives(v(i));
   }
   return cm;
 }
   


 df1_one_matrix::df1_one_matrix(const df1_one_matrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
   v = m2.v;
 }

 df1_one_matrix::~df1_one_matrix()
 {
   deallocate();
 }

 void df1_one_matrix::deallocate(void)
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df1_one_vector*) (shape->get_pointer());
       delete [] v;
       v=0;
       delete shape;
       shape=0;
     }
   }
 }


  void df1_one_matrix::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).initialize();
    }
  }


  df1_one_matrix::df1_one_matrix(int rmin,int rmax,int cmin,int cmax)
  {
    index_min=rmin;
    index_max=rmax;
    v=new df1_one_vector[rmax-rmin+1];
    if (v==0)
    {
      cerr << "error allocating memory in df1_one_matrix" << endl;
      ad_exit(1);
    }
    if ( (shape=new mat_shapex(v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df1_one_vector" 
           << endl;;
    }
    v-=rmin;
    
    for (int i=rmin;i<=rmax;i++)
    {
      v[i].allocate(cmin,cmax);
    }
  }
    

  df1_one_variable& df1_one_variable::operator -= (double v)
  {
    *get_u() -= v;

    return *this;
  }


  df1_one_variable& df1_one_variable::operator -= (const df1_one_variable& v)
  {
    *get_u() -= *v.get_u();

    *get_udot() -= *v.get_udot();
    return *this;
  }

  df1_one_variable operator - (const df1_one_variable& z,double v)
  {
    df1_one_variable tmp;
    *tmp.get_u() = *z.get_u() - v;
    *tmp.get_udot() = *z.get_udot();

    return tmp;
  }

  df1_one_variable operator - (const df1_one_variable& v)
  {
    df1_one_variable z;
    *z.get_u() =- *v.get_u();

    *z.get_udot() =- *v.get_udot();
    return z;
  }

  df1_one_variable& df1_one_variable::operator += (const df1_one_variable& v)
  {
    *get_u() += *v.get_u();

    *get_udot() += *v.get_udot();
    return *this;
  }

  df1_one_variable sqrt(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=::sqrt(*x.get_u());
    double zp=0.5/u;

    *z.get_u() = u;

    *z.get_udot() = zp* *x.get_udot();

    return z;
  }

  df1_one_variable sin(const df1_one_variable& x)
  {
    df1_one_variable z;

    *z.get_u() = ::sin(*x.get_u());

    *z.get_udot() = ::cos(*x.get_u())* *x.get_udot();

    return z;
  }

  df1_one_variable cos(const df1_one_variable& x)
  {
    df1_one_variable z;

    *z.get_u() = ::cos(*x.get_u());

    *z.get_udot() = -::sin(*x.get_u())* *x.get_udot();

    return z;
  }

  df1_one_variable log(const df1_one_variable& x)
  {
    df1_one_variable z;

    *z.get_u() = ::log(*x.get_u());

    *z.get_udot() = 1.0/(*x.get_u())* *x.get_udot();

    return z;
  }

  df1_one_variable square(const df1_one_variable& x)
  {
    df1_one_variable z;

    *z.get_u() = square(*x.get_u());

    *z.get_udot() = 2.0*(*x.get_u())* *x.get_udot();

    return z;
  }

  df1_one_variable cube(const df1_one_variable& x)
  {
    df1_one_variable z;

    double x2= square(*x.get_u());

    *z.get_u() = x2;

    *z.get_udot() = 3.0*(x2 * *x.get_u())* *x.get_udot();

    return z;
  }



  df1_one_variable exp(const df1_one_variable& x)
  {
    df1_one_variable z;

    *z.get_u() = ::exp(*x.get_u());

    *z.get_udot() = ::exp(*x.get_u())* *x.get_udot();

    return z;
  }

  df1_one_variable inv(const df1_one_variable& x)
  {
    df1_one_variable z;
    double xinv=1.0/(*x.get_u());
    double zp=-xinv*xinv;

    *z.get_u() = xinv;
    *z.get_udot() = zp * *x.get_udot();

    return z;
  }

  df1_one_variable& df1_one_variable::operator = (const df1_one_variable& x)
  {
    *get_u() = *x.get_u();
    *get_udot() = *x.get_udot();
    return *this;
  }

  df1_one_variable& df1_one_variable::operator = (double x)
  {
    *get_u() = x;
    *get_udot() = 0.0;
    return *this;
  }


  df1_one_variable operator * (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u() *  *y.get_u();
    *z.get_udot() = *x.get_u() * *y.get_udot()
                 + *x.get_udot() * *y.get_u();
    return z;
  }

  df1_one_variable operator * (double x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_udot() = x * *y.get_udot();
    return z;
  }

  df1_one_variable operator * (const df1_one_variable& x,
    double y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u() *  y;
    *z.get_udot() =  *x.get_udot() * y;
    return z;
  }


  df1_one_variable operator / (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable u=inv(y);
    return x*u;
  }

  df1_one_variable operator / (const double x,
    const df1_one_variable& y)
  {
    df1_one_variable u=inv(y);
    return x*u;
  }

  df1_one_variable operator + (const double x,const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() =  x + *y.get_u();
    *z.get_udot() =  *y.get_udot();
    return z;
  }


  df1_one_variable operator + (const df1_one_variable& y,
    const double x)
  {
    df1_one_variable z;
    *z.get_u() =   x + *y.get_u();
    *z.get_udot() =  *y.get_udot();
    return z;
  }

  df1_one_variable operator + (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u() + *y.get_u();
    *z.get_udot() = *x.get_udot() + *y.get_udot();
    return z;
  }

  df1_one_variable operator - (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u() - *y.get_u();
    *z.get_udot() = *x.get_udot() - *y.get_udot();
    return z;
  }

  df1_one_variable operator - (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator / (const df1_one_variable& x,
    const df1_one_variable& y);
  df1_one_variable operator * (const df1_one_variable& x,
    const df1_one_variable& y);

  init_df1_one_variable::~init_df1_one_variable()
  {
    if (num_vars!=1)
    {
      cerr << "can opnly have one of these" << endl;
      ad_exit(1);
    }
    num_vars--;
  }

  init_df1_one_variable::init_df1_one_variable(const prevariable& _v)
  {
    if (num_vars!=0)
    {
      cerr << "can opnly have one of these" << endl;
      ad_exit(1);
    }
    num_vars++;
    ADUNCONST(prevariable,v)
    ind_var=&v;
    *get_u() =  value(v);
    *get_udot() = 1.0;
  }

  init_df1_one_variable::init_df1_one_variable(double v)
  {
    *get_u() =  v;
    *get_udot() = 1.0;
  }

  df1_one_variable::df1_one_variable(void)
  {
     

  }


df1_one_matrix choleski_decomp(const df1_one_matrix& MM)
{
  // kludge to deal with constantness
  df1_one_matrix & M= (df1_one_matrix &) MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df1_one_atrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df1_one_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n=rmax-rmin+1;
  df1_one_matrix L(1,n,1,n);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df1_one_variable tmp;
   
    if (value(M(1,1))<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
   
  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=n;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (j=2;j<=i-1;j++)
    {
      tmp=M(i,j);
      for (k=1;k<=j-1;k++)
      {
        tmp-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp/L(j,j);
    }
    tmp=M(i,i);
    for (k=1;k<=i-1;k++)
    {
      tmp-=L(i,k)*L(i,k);
    }
   
    if (value(tmp)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
   
    L(i,i)=sqrt(tmp);
  }

  return L;
}
/*
df1b2matrix& df1b2matrix::operator = (const df1_one_matrix& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != indexmin() || rmax != indexmax())
  {
    cerr << "unequal shape in "
     "df1b2matrix& df1b2matrix::operator = (const df1_one_matrix& M)"
      << endl;
    ad_exit(1);
  }

  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}
    

df1b2vector& df1b2vector::operator = (const df1_one_vector& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != indexmin() || rmax != indexmax())
  {
    cerr << "unequal shape in "
     "df1b2vector& df1b2vector::operator = (const df1_one_vector& M)"
      << endl;
    ad_exit(1);
  }

  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}
*/    

dvariable& dvariable::operator = (const df1_one_variable& v)
{
  const prevariable * px=df1_one_variable::ind_var;
  double  df= *v.get_udot();
  value(*this)=*v.get_u();
      
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
    &(value(*this)),&(value(*px)),df);

  return *this;
}


/*
df1b2variable cumd_norm(const df1b2variable& _x)
{
  df1b2variable z;
  init_df1_one_variable x(_x);

  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double b55=b5*5;
  const double b44=b4*4;
  const double b33=b3*3;
  const double b22=b2*2;
  const double p=.2316419;
  
  if (value(x)>=0)
  {
    df1_one_variable u1=p*x;
    df1_one_variable u2=1.+p*x;
    df1_one_variable u=1./(1.+p*x);
    df1_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df1_one_variable tmp1=-0.3989422804*exp(-.5*x*x);
    z=1.0+tmp1*y;
  }
  else
  {
    df1_one_variable w=-x;
    df1_one_variable u=1./(1+p*w);
    df1_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df1_one_variable tmp1=0.3989422804*exp(-.5*x*x);
    z=tmp1*y;
  }
  return z;
}

df1b2variable bounded_cumd_norm(const df1b2variable& _x, double beta)
{
  df1b2variable z;
  init_df1_one_variable x(_x);

  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double b55=b5*5;
  const double b44=b4*4;
  const double b33=b3*3;
  const double b22=b2*2;
  const double p=.2316419;
  
  if (value(x)>=0)
  {
    df1_one_variable u1=p*x;
    df1_one_variable u2=1.+p*x;
    df1_one_variable u=1./(1.+p*x);
    df1_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df1_one_variable tmp1=-0.3989422804*exp(-.5*x*x);
    z=1.0+tmp1*y;
  }
  else
  {
    df1_one_variable w=-x;
    df1_one_variable u=1./(1+p*w);
    df1_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df1_one_variable tmp1=0.3989422804*exp(-.5*x*x);
    z=tmp1*y;
  }
  z=beta*(z-0.5)+0.5;
  return z;
}
*/
/*
df1b2variable cumd_norm(const df1b2variable& _x)
{
  df1b2variable z;
  df1b2variable x=_x;

  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double b55=b5*5;
  const double b44=b4*4;
  const double b33=b3*3;
  const double b22=b2*2;
  const double p=.2316419;
  
  if (value(x)>=0)
  {
    df1b2variable u1=p*x;
    df1b2variable u2=1.+p*x;
    df1b2variable u=1./(1.+p*x);
    df1b2variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df1b2variable tmp1=-0.3989422804*exp(-.5*x*x);
    z=1.0+tmp1*y;
  }
  else
  {
    df1b2variable w=-x;
    df1b2variable u=1./(1+p*w);
    df1b2variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df1b2variable tmp1=0.3989422804*exp(-.5*x*x);
    z=tmp1*y;
  }
  return z;
}
*/

