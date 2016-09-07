#include <df1b2fun.h>
#define FALSE false
#define TRUE  true
#include "integrate.hpp"
using gauss_kronrod::integrate;

#define LTAIL2(FUN,par1,par2)						\
template<class Float>							\
 Float ltail##FUN(Float to, Float par1, Float par2){			\
  FUN<Float> f;								\
  f.par1=par1;								\
  f.par2=par2;								\
  Float ans = 0.0;							\
  return integrate(f,-INFINITY,to);					\
}									\
									\
 double ltail##FUN(double to, double par1, double par2){		\
   return ltail##FUN<double>(to,par1,par2);				\
}									\
									\
dvariable ltail##FUN(dvariable to, dvariable par1, dvariable par2){	\
  typedef tiny_ad::variable<1, 3> Float;				\
  Float to_ (value(to), 0);						\
  Float par1##_ (value(par1), 1);					\
  Float par2##_ (value(par2), 2);					\
  Float ans=ltail##FUN(to_,par1##_,par2##_);				\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 3> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES3(y,to,der[0],par1,der[1],par2,der[2]);		\
  return y;								\
}									\
									\
dvariable ltail##FUN(prevariable to, prevariable par1, prevariable par2){\
  return ltail##FUN((dvariable)to, (dvariable)par1, (dvariable)par2);	\
}									\
									\
df1b2variable ltail##FUN(df1b2variable to, df1b2variable par1, df1b2variable par2){\
  typedef tiny_ad::variable<3, 3> Float;				\
  Float to_ (value(to), 0);						\
  Float par1##_ (value(par1), 1);					\
  Float par2##_ (value(par2), 2);					\
  Float ans=ltail##FUN(to_,par1##_,par2##_);				\
  double val=ans.value.value.value;					\
  tiny_vec<double, 3> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 9> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 27> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=to.get_u_dot();						\
  double * yd=par1.get_u_dot();						\
  double * zd=par2.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++ + der1[2] * *zd++;	\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&to,&par1,&par2,&tmp,			\
      der1[0],der1[1],der1[2],						\
      der2[0],der2[1],der2[2],der2[4],der2[5],der2[8],			\
      der3[0],der3[1],der3[2],der3[4],der3[5],der3[8],der3[13],der3[14],der3[17],der3[26]);\
  }									\
  return tmp;								\
}

#define INTEGRATE1(FUN,par)						\
template<class Float>							\
 Float integrate##FUN(Float from, Float to, Float par){			\
  FUN<Float> f;								\
  f.par=par;								\
  Float ans = 0.0;							\
  return integrate(f,from,to);						\
}									\
									\
double integrate##FUN(double from, double to, double par){		\
  return integrate##FUN<double>(from,to,par);				\
}									\
									\
dvariable integrate##FUN(dvariable from, dvariable to, dvariable par){	\
  typedef tiny_ad::variable<1, 3> Float;				\
  Float from_ (value(from), 0);						\
  Float to_ (value(to), 1);						\
  Float par##_ (value(par), 2);						\
  Float ans=integrate##FUN(from_,to_,par##_);				\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 3> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES3(y,from,der[0],to,der[1],par,der[2]);		\
  return y;								\
}									\
									\
dvariable integrate##FUN(prevariable from, prevariable to, prevariable par){ \
  return integrate##FUN((dvariable)from, (dvariable)to, (dvariable)par);\
}									\
									\
df1b2variable integrate##FUN(df1b2variable from, df1b2variable to, df1b2variable par){\
  typedef tiny_ad::variable<3, 3> Float;				\
  Float from_ (value(from), 0);						\
  Float to_ (value(to), 1);						\
  Float par##_ (value(par), 2);						\
  Float ans=integrate##FUN(from_,to_,par##_);				\
  double val=ans.value.value.value;					\
  tiny_vec<double, 3> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 9> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 27> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=from.get_u_dot();						\
  double * yd=to.get_u_dot();						\
  double * zd=par.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++ + der1[2] * *zd++;	\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&from,&to,&par,&tmp,			\
     der1[0],der1[1],der1[2],						\
     der2[0],der2[1],der2[2],der2[4],der2[5],der2[8],			\
     der3[0],der3[1],der3[2],der3[4],der3[5],der3[8],der3[13],der3[14],der3[17],der3[26]); \
  }									\
  return tmp;								\
}

#define LTAIL1(FUN,par)							\
template<class Float>							\
 Float ltail##FUN(Float to, Float par){					\
  FUN<Float> f;								\
  f.par=par;								\
  Float ans = 0.0;							\
  return integrate(f,-INFINITY,to);					\
}									\
									\
double ltail##FUN(double to, double par){				\
  return ltail##FUN<double>(to,par);					\
}									\
									\
dvariable ltail##FUN(dvariable to, dvariable par){			\
  typedef tiny_ad::variable<1, 2> Float;				\
  Float to_ (value(to), 0);						\
  Float par##_ (value(par), 1);						\
  Float ans=ltail##FUN(to_,par##_);					\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 2> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES2(y,to,der[0],par,der[1]);				\
  return y;								\
}									\
									\
dvariable ltail##FUN(prevariable to, prevariable par){			\
  return ltail##FUN((dvariable)to, (dvariable)par);			\
}									\
									\
df1b2variable ltail##FUN(df1b2variable to, df1b2variable par){		\
  typedef tiny_ad::variable<3, 2> Float;				\
  Float to_ (value(to), 0);						\
  Float par##_ (value(par), 1);						\
  Float ans=ltail##FUN(to_,par##_);					\
  double val=ans.value.value.value;					\
  tiny_vec<double, 2> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 4> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 8> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=to.get_u_dot();						\
  double * yd=par.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++;			\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&to,&par,&tmp,				\
      der1[0],der1[1],							\
      der2[0],der2[1],der2[3],						\
      der3[0],der3[1],der3[3],der3[7]);	                        	\
  }									\
  return tmp;								\
}

#define INTEGRATE0(FUN)							\
template<class Float>							\
Float integrate##FUN(Float from, Float to){				\
  FUN<Float> f;								\
  Float ans = 0.0;							\
  return integrate(f,from,to);						\
}									\
									\
double integrate##FUN(double from, double to){				\
  return integrate##FUN<double>(from,to);				\
}									\
									\
dvariable integrate##FUN(dvariable from, dvariable to){		        \
  typedef tiny_ad::variable<1, 2> Float;				\
  Float from_ (value(from), 0);						\
  Float to_ (value(to), 1);						\
  Float ans=integrate##FUN(from_,to_);					\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 2> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES2(y,from,der[0],to,der[1]);				\
  return y;								\
}									\
									\
dvariable integrate##FUN(prevariable from, prevariable to){		\
  return integrate##FUN((dvariable)from, (dvariable)to);		\
}									\
									\
df1b2variable integrate##FUN(df1b2variable from, df1b2variable to){	\
  typedef tiny_ad::variable<3, 2> Float;				\
  Float from_ (value(from), 0);						\
  Float to_ (value(to), 1);						\
  Float ans=integrate##FUN(from_,to_);					\
  double val=ans.value.value.value;					\
  tiny_vec<double, 2> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 4> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 8> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=from.get_u_dot();						\
  double * yd=to.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++;			\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&from,&to,&tmp,				\
			      der1[0],der1[1],				\
			      der2[0],der2[1],der2[3],			\
			      der3[0],der3[1],der3[3],der3[7]);		\
  }									\
  return tmp;								\
}

#define LTAIL0(FUN)							\
template<class Float>							\
Float ltail##FUN(Float to){						\
  FUN<Float> f;								\
  Float ans = 0.0;							\
  return integrate(f,-INFINITY,to);					\
}									\
									\
double ltail##FUN(double to){						\
  return ltail##FUN<double>(to);					\
}									\
									\
dvariable ltail##FUN(dvariable to){					\
  typedef tiny_ad::variable<1,1> Float;					\
  Float to_ (value(to), 0);						\
  Float ans=ltail##FUN(to_);						\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 1> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES1(y,to,der[0]);					\
  return y;								\
}									\
									\
dvariable ltail##FUN(prevariable to){					\
  return ltail##FUN((dvariable)to);					\
}									\
									\
df1b2variable ltail##FUN(df1b2variable to){				\
  typedef tiny_ad::variable<3, 1> Float;				\
  Float to_ (value(to), 0);						\
  Float ans=ltail##FUN(to_);						\
  double val=ans.value.value.value;					\
  tiny_vec<double, 1> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 1> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 1> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=to.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++;						\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&to,&tmp,der1[0],der2[0],der3[0]);	\
  }									\
  return tmp;								\
}
