/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions for dvar_vector to compute sin, ...
*/
#include "fvar.hpp"

/*
//  "template" for precompiled derivative code
 //   change XXX to function name and YYY to derivative function name
void DF_dvXXX(void);
dvar_vector XXX(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=XXX(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  save_identifier_string("ddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvXXX);
  return vtmp;
}

void DF_dvXXX(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)*YYY(v1.elem(i));
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

*/


void DF_dvsin(void);

/**
Computes sin of each element in v1 to a dvar_vector.

@param v1 dvar_vector
*/
dvar_vector sin(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=sin(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvsin);
  return vtmp;
}
/**
Adjoint function to compute gradients for sin(const dvar_vector&)
*/
void DF_dvsin(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)*cos(v1.elem(i));
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvexp(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector exp(const dvar_vector& v1)
{
  int min = v1.indexmin();
  int max = v1.indexmax();
  //dvector cv1=value(v1);
  dvar_vector vtmp(min, max);
  double_and_int* pvtmp = vtmp.va + min;
  double_and_int* pv1 = v1.va + min;
  for (int i = min; i <= max; ++i)
  {
    pvtmp->x = exp(pv1->x);
    ++pvtmp;
    ++pv1;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_value(vtmp);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("hee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvexp);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvexp(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("hee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector vtmp=restore_dvar_vector_value(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  verify_identifier_string("ddd");
  int min = dfvtmp.indexmin();
  int max = dfvtmp.indexmax();
  dvector dfv1(min, max);
  double* pdfv1 = dfv1.get_v() + min;
  double* pvtmp = vtmp.get_v() + min;
  double* pdfvtmp = dfvtmp.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    *pdfv1 = *pdfvtmp * *pvtmp;
    ++pdfv1;
    ++pvtmp;
    ++pdfvtmp;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}


void DF_dvcos(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector cos(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=cos(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("cee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvcos);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvcos(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("cee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=-dfvtmp(i)*sin(v1.elem(i));
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvlog(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector log(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  int min = v1.indexmin();
  int max = v1.indexmax();
  dvar_vector vtmp(min, max);
  double_and_int* pvtmp = vtmp.va + min;
  double_and_int* pv1 = v1.va + min;
  for (int i = min; i <= max; ++i)
  {
    pvtmp->x = log(pv1->x);
    ++pvtmp;
    ++pv1;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("cdd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvlog);
  return vtmp;
}

#ifdef DEBUG
int ad_debug_arithmetic=1;
#endif

/**
 * Description not yet available.
 * \param
 */
void DF_dvlog(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("cdd");

  int min = dfvtmp.indexmin();
  int max = dfvtmp.indexmax();
  dvector dfv1(min, max);
  double* pdfv1 = dfv1.get_v() + min;
  double* pv1 = v1.get_v() + min;
  double* pdfvtmp = dfvtmp.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
#ifdef DEBUG
     if (ad_debug_arithmetic==1)
      if (v1.elem(i)==0.0 || fabs(v1.elem(i))<1.e-150 ||
        dfvtmp(i) > 1.e+150)
      {
        cerr << "Possible overflow in DF_dvlog" << endl;
      }
#endif
    *pdfv1 = *pdfvtmp / *pv1;
    ++pdfv1;
    ++pv1;
    ++pdfvtmp;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvtan(void);

/**
Computes tan of each element in v1 to a dvar_vector.

@param v1 dvar_vector
*/
dvar_vector tan(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=tan(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("xee");
  gs->GRAD_STACK1-> set_gradient_stack(DF_dvtan);

  return vtmp;
}
/**
Adjoint function to compute gradients for tan(const dvar_vector&).
*/
void DF_dvtan(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("xee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=tan(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)/pow(cos(v1.elem(i)),2);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvatan(void);

/**
Computes atan of each element in v1 to a dvar_vector.

@param v1 dvar_vector
*/
dvar_vector atan(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=atan(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("udd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvatan);
  return vtmp;
}
/**
Adjoint function to compute gradients for tan(const dvar_vector&).
*/
void DF_dvatan(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("udd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)/(1.+pow(v1.elem(i),2));
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvsqrt(void);

/**
Computes sqrt of each element in v1 to a dvar_vector.

@param v1 dvar_vector
*/
dvar_vector sqrt(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=sqrt(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eve");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvsqrt);
  return vtmp;
}
/**
Computes square of each element in v1 to a dvar_vector.

@param v1 dvar_vector
*/
dvar_vector sqr(const dvar_vector& v1)
{
  /*
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=sqrt(v1.elem_value(i));
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eve");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvsqrt);
  return vtmp;
  */

  return pow(v1, 2.0);
}
/**
Adjoint function to compute gradients for sqrt(const dvar_vector&).
*/
void DF_dvsqrt(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eve");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)/(2*sqrt(v1.elem(i)));
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvpow(void);

/**
Computes pow raised to the power e for each element in v1 to a dvar_vector.

@param v1 dvar_vector
*/
dvar_vector pow(const dvar_vector& v1, const double e)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem_value(i),e);
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddf");
  fp->save_dvar_vector_value(v1);
  fp->save_double_value(e);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eef");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvpow);
  return vtmp;
}
/**
Adjoint function to compute gradients for pow(const dvar_vector&, const double).
*/
void DF_dvpow(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eef");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  double e=fp->restore_double_value();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddf");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)*e*pow(v1.elem(i),e-1);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}


//  Don't have the functions for savinf and restoring
//    prevariables as yet

void DF_dvdvpow(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector pow(const dvar_vector& v1, const prevariable& e)
{
  //dvector cv1=value(v1);
  double ce=value(e);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem_value(i),ce);
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddg");
  fp->save_prevariable_value(e);
  fp->save_prevariable_position(e);
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eeg");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvdvpow);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvdvpow(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  verify_identifier_string("eeg");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  prevariable_position epos=fp->restore_prevariable_position();
  double e=fp->restore_prevariable_value();
  verify_identifier_string("ddg");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  double dfe=0.;
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    double tmp=pow(v1.elem(i),e-1);
    //vtmp.elem(i)=pow(value(v1.elem(i)),e);
    dfv1(i)=dfvtmp(i)*e*tmp;
    dfe+=dfvtmp(i)*v1.elem(i)*tmp*log(v1.elem(i));
  }
  dfv1.save_dvector_derivatives(v1pos);
  save_double_derivative(dfe,epos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvcpow(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector pow(const dvar_vector& v1,int e)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem_value(i),e);
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ddf");
  fp->save_dvar_vector_value(v1);
  fp->save_double_value(double(e));
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eef");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvcpow);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvcpow(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eef");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  double e=fp->restore_double_value();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddf");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)*e*pow(v1.elem(i),e-1);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_cdvpow(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector pow(const dvector& v1,const prevariable& e)
{
  //dvector cv1=value(v1);
  double ce=value(e);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem(i),ce);
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  save_identifier_string("eddg");
  fp->save_prevariable_value(e);
  fp->save_prevariable_position(e);
  fp->save_dvector_value(v1);
  fp->save_dvector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("feeg");
  gs->GRAD_STACK1->set_gradient_stack(DF_cdvpow);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_cdvpow(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  verify_identifier_string("feeg");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector_position v1pos=fp->restore_dvector_position();
  dvector v1=fp->restore_dvector_value(v1pos);
  prevariable_position epos=fp->restore_prevariable_position();
  double e=fp->restore_prevariable_value();
  verify_identifier_string("eddg");
  //dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  double dfe=0.;
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    double tmp=pow(v1.elem(i),e);
    //vtmp.elem(i)=pow(value(v1.elem(i)),e);
    //dfv1(i)=dfvtmp(i)*e*tmp;
    dfe+=dfvtmp(i)*tmp*log(v1.elem(i));
  }
  //dfv1.save_dvector_derivatives(v1pos);
  save_double_derivative(dfe,epos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
dvar_vector pow(const dvector& x,const dvar_vector& a)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();


  dvar_vector y(x.indexmin(), x.indexmax());
  for(int i=x.indexmin(); i<=x.indexmax(); i++)
  {
    y(i)=pow(x(i),a(i));
  }

  gs->RETURN_ARRAYS_DECREMENT();

  return(y);
}
