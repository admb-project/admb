/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
//#if defined(__BORLANDC__) && !defined(__linux__)

#include <stdio.h>
#if defined(__MSVC32__)
#  define WIN32
#endif

#if defined(__BORLANDC__)
#define WIN32
#endif
#include <adpvm2.h>
//#if defined(__BORLANDC__)
#define AD_USE_DYNAMIC_LOAD
//#endif

#if defined AD_USE_DYNAMIC_LOAD

#define HAVE_PVM

int ad_constant_flag=0;

//#define  __declspec(dllexport) 

#define AD__PRELOAD

/**
 * Description not yet available.
 * \param
 */
int load_adpvm_library(void)
{ 
  int ierr=0;
  return ierr;
}


#if defined(USE_ADPVM)

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack_number_derivative(void)
{
  verify_identifier_string("D");
  prevariable_position dvpos=restore_prevariable_position();
  double dv=restore_prevariable_derivative(dvpos);
  pvm_pack(dv);
  verify_identifier_string("C");
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack_index_bounds(void)
{
  verify_identifier_string("L");
  int imax=restore_int_value();
  int imin=restore_int_value();
  verify_identifier_string("K");
  //pvm_pkint(&imin,1,1);
  //pvm_pkint(&imax,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const prevariable& _v)
{
  dvariable& v = (dvariable&) _v;
  save_identifier_string("C");
  v.save_prevariable_position();
  save_identifier_string("D");
  pvm_upkdouble((double*)(&(value(v))),1,1);
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_pack_number_derivative);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const double& _v)
{
  double& v = (double&) _v;
  pvm_upkdouble(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const int& _v)
{
  int& v = (int&) _v;
  pvm_upkint(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_send_derivatives(void)
{
  verify_identifier_string("F");
  int n=restore_int_value();
  int id=restore_int_value();
  verify_identifier_string("E");
  int icheck =pvm_send(id,2);
}

#if defined(HAVE_PVM)

/**
 * Description not yet available.
 * \param
 */
int adpvm_recv(int id,int n)
{
  int status=pvm_recv(id,n);
  //cout << status << endl;
  if (!ad_constant_flag)
  {
    save_identifier_string("E");
    save_int_value(id);
    save_int_value(n);
    save_identifier_string("F");
    gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_send_derivatives);
  }
  return status;
}
#else

/**
 * Description not yet available.
 * \param
 */
int adpvm_recv(int id,int n)
{
  return 0;
}
#endif

/**
 * Description not yet available.
 * \param
 */
void adpvm_receive_derivatives(void)
{
  verify_identifier_string("H");
  int n=restore_int_value();
  int id=restore_int_value();
  verify_identifier_string("G");
  int bid=0;
  if ( (bid=pvm_recv(id,2))<0)
  {
    cerr << "error in adpvm_receive_derivatvies" << endl;
    ad_exit(1);
  }
}

#if defined(HAVE_PVM)

/**
 * Description not yet available.
 * \param
 */
void adpvm_send(int id,int n)
{
  int err=pvm_send(id,n);
  //cout << err << endl;
  if (!ad_constant_flag)
  {
    save_identifier_string("G");
    save_int_value(id);
    save_int_value(n);
    save_identifier_string("H");
    gradient_structure::GRAD_STACK1->
      set_gradient_stack(adpvm_receive_derivatives);
  }
}
#else

/**
 * Description not yet available.
 * \param
 */
void adpvm_send(int id,int n)
{
}
#endif

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack_vector_derivatives(void)
{
  kkludge_object kk;
  verify_identifier_string("Y");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  verify_identifier_string("X");
  dvector v(dvpos,kk);
  pvm_unpack(v);
  v.save_dvector_derivatives(dvpos);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dvar_vector& _v)
{
  dvar_vector& v =(dvar_vector&) _v;
  int imin=v.indexmin();
  int imax=v.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  pvm_pkdouble(&(value(v(imin))),imax-imin+1,1);
  
  save_identifier_string("X");
  v.save_dvar_vector_position();
  save_identifier_string("Y");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_unpack_vector_derivatives);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dvar_matrix & _m)
{
  dvar_matrix& m = (dvar_matrix &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dvar3_array & _m)
{
  dvar3_array& m = (dvar3_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dvar4_array & _m)
{
  dvar4_array& m = (dvar4_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dvar5_array & _m)
{
  dvar5_array& m = (dvar5_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void initialize_pvm_buffer(void)
{
  int bufid = pvm_initsend( PvmDataDefault );
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_initsend( int mode )
{
  int bufid = pvm_initsend( mode );
  return bufid;
}

/**
 * Description not yet available.
 * \param
 */
void  adpvm_end_receive(void)
{
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(initialize_pvm_buffer);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack_number_derivative(void)
{
  verify_identifier_string("S");
  double dv;
  pvm_upkdouble(&dv,1,1);;
  prevariable_position dvpos=restore_prevariable_position();
  verify_identifier_string("R");
  save_double_derivative(dv,dvpos);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const prevariable& _v)
{
  prevariable& v = (prevariable&) _v;
  save_identifier_string("R");
  v.save_prevariable_position();
  save_identifier_string("S");
  pvm_pkdouble((double*)(&(value(v))),1,1);
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_unpack_number_derivative);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack_vector_derivatives(void)
{
  //int bufid = adpvm_initsend( PvmDataRaw );
  verify_identifier_string("D");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  dvector dv=restore_dvar_vector_derivatives(dvpos);
  int imin=dv.indexmin();
  int imax=dv.indexmax();
  pvm_pack(dv);
  verify_identifier_string("B");
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dvar_vector& _v)
{
  dvar_vector& v = (dvar_vector&) _v;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(v))
  {
    if (v.indexmin()!=imin) 
    {
      cerr << "Error in min index in "
          "void adpvm_unpack(const dvar_vector& v)" << endl;
      ad_exit(1);
    }
    if (v.indexmax()!=imax) 
    {
      cerr << "Error in max index in" 
          " void adpvm_unpack(const dvar_vector& v)" << endl;
      ad_exit(1);
    }
  }
  else
  {
    v.allocate(imin,imax);
  }
  pvm_upkdouble(&(value(v(imin))),imax-imin+1,1);
  save_identifier_string("B");
  v.save_dvar_vector_position();
  save_identifier_string("D");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_pack_vector_derivatives);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dvar_matrix & _m)
{
  dvar_matrix& m = (dvar_matrix &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvar_matrix& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in" 
          " void adpvm_unpack(const dvar_matrix& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
  save_identifier_string("K");
  save_int_value(imin);
  save_int_value(imax);
  save_identifier_string("L");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_pack_index_bounds);
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dvar3_array & _m)
{
  dvar3_array& m = (dvar3_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvar_3array& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in" 
          " void adpvm_unpack(const dvar3_array& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dvar4_array & _m)
{
  dvar4_array& m = (dvar4_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dvar5_array & _m)
{
  dvar5_array& m = (dvar5_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in" 
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
      m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(double v)
{
  pvm_pkdouble(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(char * v,int n)
{
  pvm_pkbyte(v,n,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(char * v,int n)
{
  pvm_upkbyte(v,n,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dvector& _v)
{
  dvector& v =(dvector&) _v;
  if (allocated(v))
  {
    int imin=v.indexmin();
    int imax=v.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    pvm_pkdouble(&(v(imin)),imax-imin+1,1);
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const dmatrix & _m)
{
  dmatrix& m = (dmatrix &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const d3_array & _m)
{
  d3_array& m = (d3_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const d4_array & _m)
{
  d4_array& m = (d4_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const d5_array & _m)
{
  d5_array& m = (d5_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dvector& _v)
{
  dvector& v = (dvector&) _v;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(v)) {
    if (v.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (v.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    v.allocate(imin,imax);
  }
  pvm_upkdouble(&(v(imin)),imax-imin+1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const dmatrix & _m)
{
  dmatrix& m = (dmatrix &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dmatrix& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dmatrix& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const d3_array & _m)
{
  d3_array& m = (d3_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const d4_array & _m)
{
  d4_array& m = (d4_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const d5_array & _m)
{
  d5_array& m = (d5_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
      m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(int v)
{
  pvm_pkint(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const ivector& _v)
{
  ivector& v =(ivector&) _v;
  int imin=v.indexmin();
  int imax=v.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  pvm_pkint(&(v(imin)),imax-imin+1,1);
}
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const imatrix & _m)
{
  imatrix& m = (imatrix &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_pack(const i3_array & _m)
{
  i3_array& m = (i3_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
/*   
void adpvm_pack(const i4_array & _m)
{
  i4_array& m = (i4_array &) _m;
  int imin=m.indexmin();
  int imax=m.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
}
    
void adpvm_pack(const i5_array & _m)
{
  i5_array& m = (i5_array &) _m;
  int imin=m.indexmin();
  int imax=m.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  for (int i=imin;i<=imax;i++) adpvm_pack(m(i));
}
*/
    
/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const ivector& _v)
{
  ivector& v = (ivector&) _v;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(v)) {
    if (v.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (v.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    v.allocate(imin,imax);
  }
  pvm_upkint(&(v(imin)),imax-imin+1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const imatrix & _m)
{
  imatrix& m = (imatrix &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          "void adpvm_unpack(const imatrix& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          "void adpvm_unpack(const imatrix& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) 
  {
    pvm_unpack(m(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_unpack(const i3_array & _m)
{
  i3_array& m = (i3_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
         "void adpvm_unpack(const i3_array& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
         "void adpvm_unpack(const i3_array& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
/*    
void adpvm_unpack(const i4_array & _m)
{
  i4_array& m = (i4_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in 
          void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in 
          void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
    
void adpvm_unpack(const i5_array & _m)
{
  i5_array& m = (i5_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in 
          void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in 
          void adpvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
      m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) adpvm_unpack(m(i));
}
*/  
// ************************************************************
// ************************************************************

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const prevariable& _v)
{
  dvariable& v = (dvariable&) _v;
  pvm_upkdouble((double*)(&(value(v))),1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const double& _v)
{
  double& v = (double&) _v;
  pvm_upkdouble(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const int& _v)
{
  int& v = (int&) _v;
  pvm_upkint(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dvar_vector& _v)
{
  dvar_vector& v =(dvar_vector&) _v;
  int imin=v.indexmin();
  int imax=v.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  pvm_pkdouble(&(value(v(imin))),imax-imin+1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dvar_matrix & _m)
{
  dvar_matrix& m = (dvar_matrix &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dvar3_array & _m)
{
  dvar3_array& m = (dvar3_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dvar4_array & _m)
{
  dvar4_array& m = (dvar4_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dvar5_array & _m)
{
  dvar5_array& m = (dvar5_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    


void  pvm_end_receive(void) {; }

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const prevariable& _v)
{
  prevariable& v = (prevariable&) _v;
  pvm_pkdouble((double*)(&(value(v))),1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dvar_vector& _v)
{
  dvar_vector& v = (dvar_vector&) _v;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(v))
  {
    if (v.indexmin()!=imin) 
    {
      cerr << "Error in min index in "
          "void pvm_unpack(const dvar_vector& v)" << endl;
      ad_exit(1);
    }
    if (v.indexmax()!=imax) 
    {
      cerr << "Error in max index in" 
          " void pvm_unpack(const dvar_vector& v)" << endl;
      ad_exit(1);
    }
  }
  else
  {
    v.allocate(imin,imax);
  }
  pvm_upkdouble(&(value(v(imin))),imax-imin+1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dvar_matrix & _m)
{
  dvar_matrix& m = (dvar_matrix &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvar_matrix& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in" 
          " void pvm_unpack(const dvar_matrix& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dvar3_array & _m)
{
  dvar3_array & m = (dvar3_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvar_3array& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in" 
          " void pvm_unpack(const dvar3_array& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dvar4_array & _m)
{
  dvar4_array& m = (dvar4_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dvar5_array & _m)
{
  dvar5_array& m = (dvar5_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in" 
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
      m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(double v)
{
  pvm_pkdouble(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dvector& _v)
{
  dvector& v =(dvector&) _v;
  if (allocated(v))
  {
    int imin=v.indexmin();
    int imax=v.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    pvm_pkdouble(&(v(imin)),imax-imin+1,1);
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const dmatrix & _m)
{
  dmatrix& m = (dmatrix &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const d3_array & _m)
{
  d3_array& m = (d3_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const d4_array & _m)
{
  d4_array& m = (d4_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const d5_array & _m)
{
  d5_array& m = (d5_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dvector& _v)
{
  dvector& v = (dvector&) _v;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(v)) {
    if (v.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (v.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    v.allocate(imin,imax);
  }
  pvm_upkdouble(&(v(imin)),imax-imin+1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const dmatrix & _m)
{
  dmatrix& m = (dmatrix &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dmatrix& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dmatrix& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const d3_array & _m)
{
  d3_array& m = (d3_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const d4_array & _m)
{
  d4_array& m = (d4_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const d5_array & _m)
{
  d5_array& m = (d5_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
      m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(int v)
{
  pvm_pkint(&v,1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const ivector& _v)
{
  ivector& v =(ivector&) _v;
  int imin=v.indexmin();
  int imax=v.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  pvm_pkint(&(v(imin)),imax-imin+1,1);
}
    
/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const imatrix & _m)
{
  imatrix& m = (imatrix &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void pvm_pack(const i3_array & _m)
{
  i3_array& m = (i3_array &) _m;
  if (allocated(m))
  {
    int imin=m.indexmin();
    int imax=m.indexmax();
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
    for (int i=imin;i<=imax;i++) pvm_pack(m(i));
  }
  else
  {
    int imin=0;
    int imax=-1;
    pvm_pkint(&imin,1,1);
    pvm_pkint(&imax,1,1);
  }
}
/*   
void pvm_pack(const i4_array & _m)
{
  i4_array& m = (i4_array &) _m;
  int imin=m.indexmin();
  int imax=m.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  for (int i=imin;i<=imax;i++) pvm_pack(m(i));
}
    
void pvm_pack(const i5_array & _m)
{
  i5_array& m = (i5_array &) _m;
  int imin=m.indexmin();
  int imax=m.indexmax();
  pvm_pkint(&imin,1,1);
  pvm_pkint(&imax,1,1);
  for (int i=imin;i<=imax;i++) pvm_pack(m(i));
}
*/
    
/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const ivector& _v)
{
  ivector& v = (ivector&) _v;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(v)) {
    if (v.indexmin()!=imin) {
      cerr << "Error in min index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
    if (v.indexmax()!=imax) {
      cerr << "Error in max index in"
          " void pvm_unpack(const dvector& v)" << endl;
      ad_exit(1);
    }
  } else {
    v.allocate(imin,imax);
  }
  pvm_upkint(&(v(imin)),imax-imin+1,1);
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const imatrix & _m)
{
  imatrix& m = (imatrix &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
          "void pvm_unpack(const imatrix& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
          "void pvm_unpack(const imatrix& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) 
  {
    pvm_unpack(m(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
void pvm_unpack(const i3_array & _m)
{
  i3_array& m = (i3_array &) _m;
  int imin;
  int imax;
  pvm_upkint(&imin,1,1);
  pvm_upkint(&imax,1,1);
  if (allocated(m)) {
    if (m.indexmin()!=imin) {
      cerr << "Error in min index in"
         "void pvm_unpack(const i3_array& v)" << endl;
      ad_exit(1);
    }
    if (m.indexmax()!=imax) {
      cerr << "Error in max index in"
         "void pvm_unpack(const i3_array& v)" << endl;
      ad_exit(1);
    }
  } else {
    m.allocate(imin,imax);
  }
  for (int i=imin;i<=imax;i++) pvm_unpack(m(i));
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_slave_vinitsend(int mode)
{
  return adpvm_initsend(mode);
}
  
/**
 * Description not yet available.
 * \param
 */
int adpvm_slave_cinitsend(int mode)
{
  return adpvm_initsend(mode);
}
  
/**
 * Description not yet available.
 * \param
 */
void adpvm_slave_vsend(int ptid)
{
  adpvm_send(ptid, 2);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_slave_csend(int ptid)
{
  ad_constant_flag=1;
  adpvm_send(ptid, 2);
  ad_constant_flag=0;
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_slave_vrecv(int ptid)
{
  int ierr=pvm_recv(ptid,-1);
  adpvm_unpack(gradient_structure::no_derivatives); 
  
  if (!gradient_structure::no_derivatives) 
  {
    save_identifier_string("E");
    save_int_value(ptid);
    save_int_value(2);
    save_identifier_string("F");
    gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpvm_send_derivatives);
  }
  
  return ierr;
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_slave_crecv(int ptid)
{
  ad_constant_flag=1;
  int ierr=adpvm_recv(ptid,-1);
  ad_constant_flag=0;
  return ierr;
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_master_vinitsend(int mode)
{
  int bufid = adpvm_initsend(mode);
  adpvm_pack(gradient_structure::no_derivatives); 
  return bufid;
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_master_cinitsend(int mode)
{
  int bufid = adpvm_initsend(mode);
  return bufid;
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_master_csend(int id)
{
  ad_constant_flag=1;
  adpvm_send(id,1);
  ad_constant_flag=0;
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_master_vsend(int id)
{
  adpvm_send(id,1);
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_master_vrecv(int id)
{
  return adpvm_recv(id,2); 
}
int adpvm_master_crecv(int id) 
{
  ad_constant_flag=1;
  int status=adpvm_recv(id,2); 
  ad_constant_flag=0;
  return status;
}

/**
 * Description not yet available.
 * \param
 */
void  adpvm_master_end_vreceive(void)
{
  adpvm_end_receive();
}

/**
 * Description not yet available.
 * \param
 */
void  adpvm_slave_end_vreceive(void)
{
  adpvm_end_receive();
}

void  adpvm_master_end_creceive(void) { }

void  adpvm_slave_end_creceive(void) { }

/**
 * Description not yet available.
 * \param
 */
dvar_vector get_x_from_master(void)
{
  dvar_vector x;
  int ptid=pvm_parent();
  // ***************  begin variable receive block *********************
  adpvm_slave_vrecv(ptid);
  adpvm_unpack(x);  
  adpvm_slave_end_vreceive();
  // ***************  end receive block ***********************************
  return x;
}
  
/**
 * Description not yet available.
 * \param
 */
dvector get_dvector_from_master(void)
{
  dvector x;
  int ptid=pvm_parent();
  // ***************  begin variable receive block *********************
  adpvm_slave_crecv(ptid);
  adpvm_unpack(x);  
  adpvm_slave_end_creceive();
  // ***************  end receive block ***********************************
  return x;
}
  
/**
 * Description not yet available.
 * \param
 */
dmatrix get_dmatrix_from_master(void)
{
  dmatrix x;
  int ptid=pvm_parent();
  // ***************  begin variable receive block *********************
  adpvm_slave_crecv(ptid);
  adpvm_unpack(x);  
  adpvm_slave_end_creceive();
  // ***************  end receive block ***********************************
  return x;
}
  
/**
 * Description not yet available.
 * \param
 */
void send_f_to_master(const dvariable& f)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  adpvm_slave_vinitsend(PvmDataDefault);/* allocate message buffer */	
  adpvm_pack(f);
  adpvm_slave_vsend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}

/**
 * Description not yet available.
 * \param
 */
void send_dv3_to_master(const dvar3_array& v)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  adpvm_slave_vinitsend(PvmDataDefault);/* allocate message buffer */	
  adpvm_pack(v);
  adpvm_slave_vsend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}

/**
 * Description not yet available.
 * \param
 */
void send_dvector_to_master(const dvector& v)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  adpvm_slave_cinitsend(PvmDataDefault);/* allocate message buffer */	
  adpvm_pack(v);
  adpvm_slave_csend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}
#endif //#if defined(USE_ADPVM)
#endif
