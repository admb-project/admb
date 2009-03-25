/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"

/*
//  "template" for precompiled derivative code
 //   change XXX to function name and YYY to derivative function name
void DF_dvXXX(void);
dvar_vector XXX(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=XXX(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvXXX);
  return vtmp;
}

void DF_dvXXX(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
dvar_vector sin(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=sin(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvsin);
  return vtmp;
}

void DF_dvsin(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
dvar_vector exp(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=exp(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_value();
  vtmp.save_dvar_vector_position();
  save_identifier_string("hee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvexp);
  return vtmp;
}

void DF_dvexp(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("hee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector vtmp=restore_dvar_vector_value(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  verify_identifier_string("ddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    dfv1(i)=dfvtmp(i)*vtmp.elem(i);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}


void DF_dvcos(void);
dvar_vector cos(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=cos(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("cee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvcos);
  return vtmp;
}

void DF_dvcos(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("cee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
dvar_vector log(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=log(v1.elem_value(i));
  }

  save_identifier_string("cdd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvlog);
  return vtmp;
}

int ad_debug_arithmetic=1;

void DF_dvlog(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("cdd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
#    ifndef OPT_LIB
     if (ad_debug_arithmetic==1)
      if (v1.elem(i)==0.0 || fabs(v1.elem(i))<1.e-150 ||
        dfvtmp(i) > 1.e+150)
      {
        cerr << "Possible overflow in DF_dvlog" << endl;
      }
      
#    endif
    dfv1(i)=dfvtmp(i)/(v1.elem(i));
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvtan(void);
dvar_vector tan(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=tan(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("xee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvtan);
  return vtmp;
}

void DF_dvtan(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("xee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
dvar_vector atan(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=atan(v1.elem_value(i));
  }

  save_identifier_string("udd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvatan);
  return vtmp;
}

void DF_dvatan(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
dvar_vector sqrt(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=sqrt(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eve");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvsqrt);
  return vtmp;
}

dvar_vector sqr(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=sqrt(v1.elem_value(i));
  }

  save_identifier_string("ddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eve");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvsqrt);
  return vtmp;
}

void DF_dvsqrt(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eve");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
dvar_vector pow(_CONST dvar_vector& v1, CGNU_DOUBLE e)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem_value(i),e);
  }

  save_identifier_string("ddf");
  v1.save_dvar_vector_value();
  save_double_value(e);
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eef");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvpow);
  return vtmp;
}

void DF_dvpow(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eef");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  double e=restore_double_value();
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
dvar_vector pow(_CONST dvar_vector& v1,_CONST prevariable& e)
{
  //dvector cv1=value(v1);
  double ce=value(e);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem_value(i),ce);
  }

  save_identifier_string("ddg");
  e.save_prevariable_value();
  e.save_prevariable_position();
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eeg");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvdvpow);
  return vtmp;
}

void DF_dvdvpow(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);

  verify_identifier_string("eeg");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  prevariable_position epos=restore_prevariable_position();
  double e=restore_prevariable_value();
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
dvar_vector pow(_CONST dvar_vector& v1,int e)
{
  //dvector cv1=value(v1);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem_value(i),e);
  }

  save_identifier_string("ddf");
  v1.save_dvar_vector_value();
  save_double_value(double(e));
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eef");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvcpow);
  return vtmp;
}

void DF_dvcpow(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eef");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  double e=restore_double_value();
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
dvar_vector pow(_CONST dvector& v1,_CONST prevariable& e)
{
  //dvector cv1=value(v1);
  double ce=value(e);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=pow(v1.elem(i),ce);
  }

  save_identifier_string("eddg");
  e.save_prevariable_value();
  e.save_prevariable_position();
  v1.save_dvector_value();
  v1.save_dvector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("feeg");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_cdvpow);
  return vtmp;
}

void DF_cdvpow(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);

  verify_identifier_string("feeg");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector_position v1pos=restore_dvector_position();
  dvector v1=restore_dvector_value(v1pos);
  prevariable_position epos=restore_prevariable_position();
  double e=restore_prevariable_value();
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



