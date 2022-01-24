// Anders Nielsen <anders.nielsen@hawaii.edu> Sep 2005 

#ifndef __nLogNormal_h__
#define __nLogNormal_h__

#include <fvar.hpp>
#include <math.h>

const double log2pi = log(2.0*M_PI);

void dmdm_bksolve(void);

dvar_matrix bksolve(const dvar_matrix& L, const dvar_matrix& b)
{
  RETURN_ARRAYS_INCREMENT();	  
  int i, k, r, R, c, C;
  r=b.rowmin();
  R=b.rowmax();
  c=b.colmin();
  C=b.colmax();

  dvector sumVec(c,C);
  dmatrix xVal(r,R,c,C);
  dmatrix LVal=value(L);
  dmatrix bVal=value(b);

  for(i=r; i<=R; ++i){
    sumVec=bVal(i); 
    for(k=i-1; k>=r; k--){
      sumVec-=LVal(i,k)*xVal(k);
    }
    xVal(i)=sumVec/LVal(i,i);
  }

  dvar_matrix x=nograd_assign(xVal);
  save_identifier_string("TEST1");
  L.save_dvar_matrix_value();
  L.save_dvar_matrix_position();
  b.save_dvar_matrix_value();
  b.save_dvar_matrix_position();
  x.save_dvar_matrix_value();
  x.save_dvar_matrix_position();
  save_identifier_string("TEST6");
  gradient_structure::get()->GRAD_STACK1->
           set_gradient_stack(dmdm_bksolve);
  RETURN_ARRAYS_DECREMENT();
  return x;
}

void dmdm_bksolve(void)
{
  verify_identifier_string("TEST6");
  dvar_matrix_position xpos=restore_dvar_matrix_position();
  dmatrix dfx=restore_dvar_matrix_derivatives(xpos);
  dmatrix x=restore_dvar_matrix_value(xpos);
  dvar_matrix_position bpos=restore_dvar_matrix_position();
  dmatrix b=restore_dvar_matrix_value(bpos);
  dvar_matrix_position Lpos=restore_dvar_matrix_position();
  dmatrix L=restore_dvar_matrix_value(Lpos);
  verify_identifier_string("TEST1");

  int i, k, r, R, c, C;
  r=b.rowmin();  
  R=b.rowmax();  
  c=b.colmin();
  C=b.colmax();

  dmatrix dfL(Lpos);
  dmatrix dfb(bpos);
  dvector sumVec(c,C);
  dvector dfsumVec(c,C);
  dfL.initialize();
  dfb.initialize();
  dfsumVec.initialize();


  for(i=R; i>=r; --i){
    //bring back sumVec 
    sumVec=x(i)*L(i,i);

    //xVal(i)=sumVec/LVal(i,i);
    dfsumVec+=dfx(i)/L(i,i);
    dfL(i,i)+= -(dfx(i)*sumVec)/(L(i,i)*L(i,i)); 
    dfx(i)=0.0;

    for(k=r; k<=i-1; k++){
      //sumVec-=LVal(i,k)*xVal(k);
      dfL(i,k)-=dfsumVec*x(k);
      dfx(k)-=dfsumVec*L(i,k);

    }
    //sumVec=bVal(i); 
    dfb(i)+=dfsumVec; 
    dfsumVec=0.0;
  }

  dfL.save_dmatrix_derivatives(Lpos);
  dfb.save_dmatrix_derivatives(bpos);
}


dvar_vector nLogNormal(const dvar_vector& x, const dvar_matrix& mu, const dvar_matrix& S)
{
  RETURN_ARRAYS_INCREMENT();	
  int r, R, c, C, N;
  r=mu.rowmin();
  R=mu.rowmax();
  c=mu.colmin();
  C=mu.colmax();
  N=R-r+1;
  dvar_vector ret(c,C);
  dvar_matrix diff(r,R,c,C);
  for(int i=c; i<=C; ++i)diff.colfill(i,x-column(mu,i));
  dvariable logDet;
  dvar_matrix chol=choleski_decomp(S);
  logDet=2.0*sum(log(diagonal(chol)));
  dvar_matrix tmp=bksolve(chol,diff);
  ret=0.5*(log2pi*N+logDet+colsum(square(tmp)));
  RETURN_ARRAYS_DECREMENT();
  return ret;
}

dvar_vector nLogNormal(const dvar_matrix& x, const dvar_vector& mu, const dvar_matrix& S)
{
  RETURN_ARRAYS_INCREMENT();
  dvar_vector ret=nLogNormal(mu, x, S);
  RETURN_ARRAYS_DECREMENT();
  return ret;
}

dvariable nLogNormal(const dvar_vector& x, const dvar_vector& mu, const dvar_matrix& S)
{
  RETURN_ARRAYS_INCREMENT();	
  dvar_matrix MU(mu.indexmin(),mu.indexmax(),1,1);
  MU.colfill(1,mu);
  dvar_vector tmp=nLogNormal(x, MU, S);
  dvariable ret=tmp(tmp.indexmin());	
  RETURN_ARRAYS_DECREMENT();
  return ret;
}

//TEST
dvar_vector nLogNormalChol(const dvar_vector& x, const dvar_matrix& mu, const dvar_matrix& chol)
{
  RETURN_ARRAYS_INCREMENT();	
  int r, R, c, C, N;
  r=mu.rowmin();
  R=mu.rowmax();
  c=mu.colmin();
  C=mu.colmax();
  N=R-r+1;
  dvar_vector ret(c,C);
  dvar_matrix diff(r,R,c,C);
  for(int i=c; i<=C; ++i)diff.colfill(i,x-column(mu,i));
  dvariable logDet;
  logDet=2.0*sum(log(diagonal(chol)));
  dvar_matrix tmp=bksolve(chol,diff);
  ret=0.5*(log2pi*N+logDet+colsum(square(tmp)));	
  RETURN_ARRAYS_DECREMENT();
  return ret;
}

dvar_vector nLogNormalChol(const dvar_matrix& x, const dvar_vector& mu, const dvar_matrix& chol)
{
  RETURN_ARRAYS_INCREMENT();	
  dvar_vector ret=nLogNormalChol(mu, x, chol);	
  RETURN_ARRAYS_DECREMENT();
  return ret;
}

dvariable nLogNormalChol(const dvar_vector& x, const dvar_vector& mu, const dvar_matrix& chol)
{
  RETURN_ARRAYS_INCREMENT();	
  dvar_matrix MU(mu.indexmin(),mu.indexmax(),1,1);
  MU.colfill(1,mu);
  dvar_vector tmp=nLogNormalChol(x, MU, chol);
  dvariable ret=tmp(tmp.indexmin());	
  RETURN_ARRAYS_DECREMENT();
  return ret;
}

void dmdm_fwsolve(void);

dvar_matrix fwsolve(const dvar_matrix& L, const dvar_matrix& b)
{  
  RETURN_ARRAYS_INCREMENT();	
  int i, k, r, R, c, C;
  r=b.rowmin();
  R=b.rowmax();
  c=b.colmin();
  C=b.colmax();

  dvector sumVec(c,C);
  dmatrix xVal(r,R,c,C);
  dmatrix LVal=value(L);
  dmatrix bVal=value(b);

  for(i=R; i>=r; --i){
    sumVec=bVal(i); 
    for(k=i+1; k<=R; k++){
      sumVec-=LVal(k,i)*xVal(k);
    }
    xVal(i)=sumVec/LVal(i,i);
  }

  dvar_matrix x=nograd_assign(xVal);
  save_identifier_string("TEST1");
  L.save_dvar_matrix_value();
  L.save_dvar_matrix_position();
  b.save_dvar_matrix_value();
  b.save_dvar_matrix_position();
  x.save_dvar_matrix_value();
  x.save_dvar_matrix_position();
  save_identifier_string("TEST6");
  gradient_structure::get()->GRAD_STACK1->
           set_gradient_stack(dmdm_fwsolve);	
  RETURN_ARRAYS_DECREMENT();
  return x;
}

void dmdm_fwsolve(void)
{
  verify_identifier_string("TEST6");
  dvar_matrix_position xpos=restore_dvar_matrix_position();
  dmatrix dfx=restore_dvar_matrix_derivatives(xpos);
  dmatrix x=restore_dvar_matrix_value(xpos);
  dvar_matrix_position bpos=restore_dvar_matrix_position();
  dmatrix b=restore_dvar_matrix_value(bpos);
  dvar_matrix_position Lpos=restore_dvar_matrix_position();
  dmatrix L=restore_dvar_matrix_value(Lpos);
  verify_identifier_string("TEST1");

  int i, k, r, R, c, C;
  r=b.rowmin();  
  R=b.rowmax();  
  c=b.colmin();
  C=b.colmax();

  dmatrix dfL(Lpos);
  dmatrix dfb(bpos);
  dvector sumVec(c,C);
  dvector dfsumVec(c,C);
  dfL.initialize();
  dfb.initialize();
  dfsumVec.initialize();


  for(i=r; i<=R; ++i){
    //bring back sumVec 
    sumVec=x(i)*L(i,i);

    //xVal(i)=sumVec/LVal(i,i);
    dfsumVec+=dfx(i)/L(i,i);
    dfL(i,i)+= -(dfx(i)*sumVec)/(L(i,i)*L(i,i)); 
    dfx(i)=0.0;

    for(k=R; k>=i+1; k--){
      //sumVec-=LVal(k,i)*xVal(k);
      dfL(k,i)-=dfsumVec*x(k);
      dfx(k)-=dfsumVec*L(k,i);
    }
    //sumVec=bVal(i); 
    dfb(i)+=dfsumVec; 
    dfsumVec=0.0;
  }

  dfL.save_dmatrix_derivatives(Lpos);
  dfb.save_dmatrix_derivatives(bpos);
}



#endif



