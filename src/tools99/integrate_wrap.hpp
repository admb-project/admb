#include <df1b2fun.h>
#ifndef __MINGW32__
  #define FALSE false
  #define TRUE  true
#endif
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
TINYFUN3(ltail##FUN,to,par1,par2)

#define INTEGRATE1(FUN,par)						\
template<class Float>							\
 Float integrate##FUN(Float from, Float to, Float par){			\
  FUN<Float> f;								\
  f.par=par;								\
  Float ans = 0.0;							\
  return integrate(f,from,to);						\
}									\
TINYFUN3(integrate##FUN,from,to,par)

#define LTAIL1(FUN,par)							\
template<class Float>							\
 Float ltail##FUN(Float to, Float par){					\
  FUN<Float> f;								\
  f.par=par;								\
  Float ans = 0.0;							\
  return integrate(f,-INFINITY,to);					\
}									\
TINYFUN2(ltail##FUN,to,par)

#define INTEGRATE0(FUN)							\
template<class Float>							\
Float integrate##FUN(Float from, Float to){				\
  FUN<Float> f;								\
  Float ans = 0.0;							\
  return integrate(f,from,to);						\
}									\
TINYFUN2(integrate##FUN,from,to)

#define LTAIL0(FUN)							\
template<class Float>							\
Float ltail##FUN(Float to){						\
  FUN<Float> f;								\
  Float ans = 0.0;							\
  return integrate(f,-INFINITY,to);					\
}									\
TINYFUN1(ltail##FUN,to)
