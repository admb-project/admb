/*
 * $Id$
 *
 * Copyright (c) 2009 ADMB Foundation
 */

  #define HOME_VERSION
  #include <fvar.hpp>
  #include <ludcmp.hpp>
  
  #ifdef __TURBOC__
    #pragma hdrstop
    #include <iostream.h>
  #endif
  
  #ifdef __ZTC__
    #include <iostream.hpp>
  #endif
  
  #define TINY 1.0e-20;
  void dfinvpret(void);
  
  int min(int a,int b)
  {
    if (a>b) return b;
    return a;
  }

/** Inverse of a varaiable matrix.    
    \param aa dvar_matrix conaining matrix to be inverted,\f$A\f$.
    \return dvar_matrix containing \f$A^{-1}\f$.
*/ 
  dvar_matrix inv(_CONST dvar_matrix& aa)
  {
    int i,imax,j,k,n;
    n=aa.colsize();
    int lb=aa.colmin();
    int ub=aa.colmax();
    dvar_matrix vc(lb,ub,lb,ub);
    if (n==1)
    {
      if (aa(lb,lb)==0.0)
      {
        cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
        ad_exit(1);
      }
      else
      {
        vc(lb,lb)=1.0/aa(lb,lb);
        return vc;
      }
    }
    else if (n==2)
    {
      dvariable det=aa(lb,lb)*aa(ub,ub)-aa(lb,ub)*aa(ub,lb);
      if (det==0.0)
      {
        cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
        ad_exit(1);
      }
      else
      {
        dvariable detinv=1.0/det;
        vc(lb,lb)=aa(ub,ub)*detinv;
        vc(ub,ub)=aa(lb,lb)*detinv;
        vc(lb,ub)=-aa(lb,ub)*detinv;
        vc(ub,lb)=-aa(ub,lb)*detinv;
        return vc;
      }
    }
      
    ivector indx(lb,ub);
    int One=1;
    indx.fill_seqadd(lb,One);
    double d;
    double w1,ssum,temp;
    dvar_matrix_position dmp(aa,0);
    //dmatrix bb=value(aa);
    cltudecomp bb(lb,ub);
    //bb=value(aa);   // bad because it creates an extra copy of aa
    bb.assign_value(aa);
    dvector vv(lb,ub);
  
    d=1.0;
    for (i=lb;i<=ub;i++)
    {
      w1=0.0;
      for (j=lb;j<=ub;j++)
      {
        temp=fabs(bb.elem(i,j));
        if (temp > w1)
        {
          w1=temp;
        }
      }
      if (w1 == 0.0)
      {
        cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
        ad_exit(1);
      }
      vv[i]=1.0/w1;
    }
  
    dmatrix alpha=bb.get_L();
    dmatrix beta=bb.get_U();
    double v1;
    for (j=lb;j<=ub;j++)
    {
      for (i=lb;i<j;i++)
      {
        ssum=bb.elem(i,j);
  
        if (lb<i)
        {
          ssum-=alpha(i)(lb,i-1)*beta(j)(lb,i-1);
        }
       
        bb.elem(i,j)=ssum;
      }
      w1=0.0;
      for (i=j;i<=ub;i++)
      {
        ssum=bb.elem(i,j);
        if (lb<j)
        {
          ssum-=alpha(i)(lb,j-1)*beta(j)(lb,j-1);
        }
        bb.elem(i,j)=ssum;
        v1=vv[i]*fabs(ssum);
        if ( v1 >= w1)
        {
          w1=v1;
          imax=i;
        }
      }
      if (j != imax)
      {
        for (k=lb;k<=ub;k++)
        {
          v1=bb.elem(imax,k);
          bb.elem(imax,k)=bb.elem(j,k);
          bb.elem(j,k)=v1;
        }
        d = -1.*d;
        vv[imax]=vv[j];
  
        //if (j<ub)
        {
          int itemp=indx.elem(imax);
          indx.elem(imax)=indx.elem(j);
          indx.elem(j)=itemp;
        }
        //cout << "indx= " <<indx<<endl;
      }
  
      if (bb.elem(j,j) == 0.0)
      {
        bb.elem(j,j)=TINY;
      }
  
      if (j != n)
      {
        double binv=1.0/bb.elem(j,j);
        for (i=j+1;i<=ub;i++)
        {
          bb.elem(i,j) *= binv;
        }
      }
    }
  
    dvector y(lb,ub);
    dvector x(lb,ub);
    //int lb=rowmin;
    //int ub=rowmax;
    cltudecomp& b=bb;
    ivector indxinv(lb,ub);
    for (i=lb;i<=ub;i++)
    {
      indxinv(indx.elem(i))=i;
    }
    for (int ii=lb;ii<=ub;ii++)
    {
      y.initialize();
      y(indxinv(ii))=1.;
      for (int i=indxinv(ii);i<=ub;i++)
      {
        // ssum=y(ii,i);
        if (i==indxinv(ii))
        {
          ssum=1.;
        }
        else
        {
          ssum=0.;
        }
        if (indxinv(ii)<i)
        {
          ssum-=alpha(i)(indxinv(ii),i-1)*y(indxinv(ii),i-1);
        }
        y.elem(i)=ssum;
      }
      for (i=ub;i>=lb;i--)
      {
        ssum=y.elem(i);
        for (int j=i+1;j<=ub;j++)
        {
          ssum-=beta(j,i)*x.elem(j);
        }
        x.elem(i)=ssum/b.elem(i,i);
      }
      y.save_dvector_value();
      x.save_dvector_value();
      nograd_assign_column(vc,x,ii);
    }
  
    dmatrix bb1(lb,ub,lb,ub);
    for (i=lb;i<=ub;i++)
    {
      for (j=lb;j<=ub;j++)
      {
        bb1(i,j)=bb(i,j);
      }
    }
    save_identifier_string("P5");
    x.save_dvector_position();
    y.save_dvector_position();
    indx.save_ivector_value();
    indx.save_ivector_position();
    aa.save_dvar_matrix_position();
    vc.save_dvar_matrix_position();
    bb1.save_dmatrix_value();
    bb1.save_dmatrix_position();
    save_identifier_string("P1");
    gradient_structure::GRAD_STACK1->
        set_gradient_stack(dfinvpret);
    return vc;
  }

/** Adjoint code for dvar_matrix inv(_CONST dvar_matrix& aa).
*/  
  void dfinvpret(void)
  {
    verify_identifier_string("P1");
    dmatrix_position bpos=restore_dmatrix_position();
    dmatrix b=restore_dmatrix_value(bpos);
    dvar_matrix_position v_pos=restore_dvar_matrix_position();
    dvar_matrix_position a_pos=restore_dvar_matrix_position();
    ivector_position indx_pos=restore_ivector_position();
    ivector indx=restore_ivector_value(indx_pos);
    dvector_position y_pos=restore_dvector_position();
    dvector_position x_pos=restore_dvector_position();
    verify_identifier_string("P5");
    int lb=b.colmin();
    int ub=b.colmax();
    dmatrix dfb(lb,ub,lb,ub);
    ivector indxinv(lb,ub);
    for (int i=lb;i<=ub;i++)
    {
      indxinv(indx.elem(i))=i;
    }
  
    double dfssum=0.;
    dvector dfy(lb,ub);
    #ifndef SAFE_INITIALIZE
      dfb.initialize();
      dfy.initialize();
    #endif
    for (int ii=ub;ii>=lb;ii--)
    {
      //x.save_dvector_value();
      dvector x=restore_dvector_value(x_pos);
      //y.save_dvector_value();
      dvector y=restore_dvector_value(y_pos);
      dvector dfx=restore_dvar_matrix_derivative_column(v_pos,ii);
      for (int i=lb;i<=ub;i++)
      {
        // x.elem(i)=ssum/b.elem(i,i);
        dfssum+=dfx.elem(i)/b.elem(i,i);
        dfb.elem(i,i)-=dfx.elem(i)*x.elem(i)/b.elem(i,i);
        dfx.elem(i)=0.;
        for (int j=ub;j>=i+1;j--)
        {
          // ssum -=b.elem(i,j)*x.elem(j);
          dfb.elem(i,j)-=dfssum*x.elem(j);
          dfx.elem(j)-=dfssum*b.elem(i,j);
        }
        // ssum=y.elem(i);
        dfy.elem(i)+=dfssum;
        dfssum=0.;
      }
  
      //for (i=ub;i>=lb;i--)
      int i2;
      for (i2=ub;i2>=indxinv(ii);i2--)
      {
        // y.elem(i)=ssum;
        dfssum+=dfy.elem(i2);
        dfy.elem(i2)=0.;
        // for (int j=i-1;j>=lb;j--)
        for (int j=i2-1;j>=indxinv(ii);j--)
        {
          // ssum-=b.elem(i,j)*y.elem(j);
          dfb.elem(i2,j)-=dfssum*y.elem(j);
          dfy.elem(j)-=dfssum*b.elem(i2,j);
        }
        //ssum=y.elem(i);
        dfy.elem(i2)=dfssum;
        dfssum=0.;
      }
      //x.initialize()
      //y.initialize()
      dfx.initialize();
      dfy.initialize();
    }
  
    for (int j=ub;j>=lb;j--)
    {
      for (int i=ub;i>=lb;i--)
      {
        if (i<=j)
        {
          // b.elem(i,j)=ssum;
          dfssum+=dfb.elem(i,j);
          dfb.elem(i,j)=0.;
        }
        else
        {
          // b.elem(i,j)=ssum/b.elem(j,j);
          dfssum+=dfb.elem(i,j)/b.elem(j,j);
          dfb.elem(j,j)-=dfb.elem(i,j)*b.elem(i,j)/b.elem(j,j);
          dfb.elem(i,j)=0.;
        }
  
        for (int k=min(i-1,j-1);k>=lb;k--)
        {
          // ssum-=b.elem(i,k)*b.elem(k,j);
          dfb.elem(i,k)-=dfssum*b.elem(k,j);
          dfb.elem(k,j)-=dfssum*b.elem(i,k);
        }
        // ssum=value(a(indx.elem(i),j);
        save_dmatrix_derivatives(a_pos,dfssum,indx.elem(i),j); // like this
        dfssum=0.;
      }
    }
  }
  
  #undef TINY
  #undef HOME_VERSION
