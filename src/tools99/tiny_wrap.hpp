#ifndef TINY_WRAP_H
#define TINY_WRAP_H

//#include <df1b2fun.h>

#define TINYFUN3(FUN,par1,par2,par3)					\
                                                                        \
double FUN(double par1, double par2, double par3){			\
  return FUN<double>(par1, par2, par3);					\
}									\
									\
dvariable FUN(dvariable par1, dvariable par2, dvariable par3){		\
  typedef tiny_ad::variable<1, 3> Float;				\
  Float par1##_ (value(par1), 0);		       			\
  Float par2##_ (value(par2), 1);					\
  Float par3##_ (value(par3), 2);					\
  Float ans=FUN(par1##_,par2##_,par3##_);				\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 3> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES3(y,par1,der[0],par2,der[1],par3,der[2]);		\
  return y;								\
}									\
									\
dvariable FUN(prevariable par1, prevariable par2, prevariable par3){    \
  return FUN((dvariable)par1, (dvariable)par2, (dvariable)par3);	\
}									\
									\
df1b2variable FUN(df1b2variable par1, df1b2variable par2, df1b2variable par3){ \
  typedef tiny_ad::variable<3, 3> Float;				\
  Float par1##_ (value(par1), 0);			       		\
  Float par2##_ (value(par2), 1);					\
  Float par3##_ (value(par3), 2);					\
  Float ans=FUN(par1##_,par2##_,par3##_);    				\
  double val=ans.value.value.value;					\
  tiny_vec<double, 3> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 9> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 27> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=par1.get_u_dot();						\
  double * yd=par2.get_u_dot();						\
  double * zd=par3.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++ + der1[2] * *zd++;	\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&par1,&par2,&par3,&tmp,			\
      der1[0],der1[1],der1[2],						\
      der2[0],der2[1],der2[2],der2[4],der2[5],der2[8],			\
      der3[0],der3[1],der3[2],der3[4],der3[5],der3[8],der3[13],der3[14],der3[17],der3[26]); \
  }									\
  return tmp;								\
}

#define TINYFUN2(FUN,par1,par2)						\
                                                                        \
double FUN(double par1, double par2){					\
  return FUN<double>(par1, par2);					\
}									\
									\
dvariable FUN(dvariable par1, dvariable par2){  			\
  typedef tiny_ad::variable<1, 2> Float;				\
  Float par1##_ (value(par1), 0);					\
  Float par2##_ (value(par2), 1);					\
  Float ans=FUN(par1##_,par2##_);					\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 2> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES2(y,par1,der[0],par2,der[1]);      			\
  return y;								\
}									\
									\
dvariable FUN(prevariable par1, prevariable par2){			\
  return FUN((dvariable)par1, (dvariable)par2);				\
}									\
									\
df1b2variable FUN(df1b2variable par1, df1b2variable par2){		\
  typedef tiny_ad::variable<3, 2> Float;				\
  Float par1##_ (value(par1), 0);					\
  Float par2##_ (value(par2), 1);					\
  Float ans=FUN(par1##_,par2##_);					\
  double val=ans.value.value.value;					\
  tiny_vec<double, 2> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 4> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 8> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=par1.get_u_dot();						\
  double * yd=par2.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++;			\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&par1,&par2,&tmp,				\
      der1[0],der1[1],							\
      der2[0],der2[1],der2[3],						\
      der3[0],der3[1],der3[3],der3[7]);	                        	\
  }									\
  return tmp;								\
}

#define TINYFUN1(FUN,par1)     						\
  									\
double FUN(double par1){					        \
  return FUN<double>(par1);						\
}									\
									\
dvariable FUN(dvariable par1){						\
  typedef tiny_ad::variable<1,1> Float;					\
  Float par1##_ (value(par1), 0);					\
  Float ans=FUN(par1##_);						\
  dvariable y;								\
  value(y)=ans.value;							\
  tiny_vec<double, 1> der = ans.getDeriv();				\
  AD_SET_DERIVATIVES1(y,par1,der[0]);					\
  return y;								\
}									\
									\
dvariable FUN(prevariable par1){					\
  return FUN((dvariable)par1);  					\
}									\
									\
df1b2variable FUN(df1b2variable par1){					\
  typedef tiny_ad::variable<3, 1> Float;				\
  Float par1##_ (value(par1), 0);	       				\
  Float ans=FUN(par1##_);						\
  double val=ans.value.value.value;					\
  tiny_vec<double, 1> der1 = ans.value.value.getDeriv();		\
  tiny_vec<double, 1> der2 = ans.value.getDeriv();			\
  tiny_vec<double, 1> der3 = ans.getDeriv();				\
									\
  df1b2variable tmp;							\
  double * xd=par1.get_u_dot();						\
  double * tmpd=tmp.get_u_dot();					\
  *tmp.get_u()=val;							\
  for (unsigned int i=0;i<df1b2variable::nvar;i++){			\
    *tmpd++ = der1[0] * *xd++;						\
  }									\
  if (!df1b2_gradlist::no_derivatives){					\
    f1b2gradlist->write_pass1(&par1,&tmp,der1[0],der2[0],der3[0]);	\
  }									\
  return tmp;								\
}

#endif
