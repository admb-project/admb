#include "statsLib.h"

/**
* @file vcubicspline.cpp
* @brief Cubic spline functions
* 
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell,  James Ianelli
* 
* @date 12/14/2011
* @remarks
*/

vcubic_spline_function_array::vcubic_spline_function_array( const dvector & x)
 {
   int mmin=indexmin();
   int mmax=indexmax();

   int n=mmax-mmin+1;
   ptr = new pvcubic_spline_function[n];
   ptr-=mmin;
   for (int i=mmin;i<=mmax;i++)
   {
     // ptr[i]= new  vcubic_spline_function(x); // not sure how to call this...should return matrix ...
   }
 }

vcubic_spline_function_array::vcubic_spline_function_array(int mmin,int mmax,
 const dvector & x, const dvar_matrix& y)
 {
   index_min=mmin;
   index_max=mmax;
   int n=mmax-mmin+1;
   ptr = new pvcubic_spline_function[n];
   ptr-=mmin;
   for (int i=mmin;i<=mmax;i++)
   {
     ptr[i]= new  vcubic_spline_function(x,y(i));
   }
 }

vcubic_spline_function & vcubic_spline_function_array::operator () (int i)
{
	if (i<indexmin() || i> indexmax())
   {
     cerr << "index out of range in function"
          " vcubic_spline_function & operator () (int i)"
      << endl;
     ad_exit(1);
   }
   return *(ptr[i]);
 }


dvar_matrix vcubic_spline_function_array::operator( ) (const dvector & v)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   dvar_matrix tmp(mmin,mmax,v.indexmin(),v.indexmax());
   for (int i=mmin;i<=mmax;i++)
   {
     tmp(i)=(*this)(i)(v);
   }
   return tmp;
 }

vcubic_spline_function_array::~vcubic_spline_function_array()
{
   int mmin=indexmin();
   int mmax=indexmax();

   for (int i=mmin;i<=mmax;i++)
   {
     delete ptr[i];
   }
   ptr+=mmin;
   delete ptr;
   ptr=0;
 }




/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\brief A Wrapper for the vcubic_spline_function
	\param  spline_nodes a vector of spline knots
	\param  ip is a vector of interpreted points
	\return returns a vector of interpreted points 
	\sa
**/
dvar_vector cubic_spline(const dvar_vector& spline_nodes, const dvector& ip)
{
	RETURN_ARRAYS_INCREMENT();                                                              
	int nodes=size_count(spline_nodes);
	dvector ia(1,nodes);
	ia.fill_seqadd(0,1./(nodes-1));
	dvector fa = (ip-min(ip))/(max(ip)-min(ip));
	vcubic_spline_function ffa(ia,spline_nodes);
	RETURN_ARRAYS_DECREMENT();
	return(ffa(fa));
}



void bicubic_spline(const dvector& x, const dvector& y, dvar_matrix& knots, dvar_matrix& S)
{
	/*
	Author:  Steven Martell
	Date: July 29, 2010
	Comments:  Based on code from Numerical Recipies.

	This function returns matrix S which is the interpolated values of knots
	over knots[1..m][1..n] grid.

	first call splie2 to get second-derivatives at knot points
	void splie2(const dvector& _x1a,const dvector& _x2a,const dmatrix& _ya,dvar_matrix& _y2a)

	then run the splin2 to get the spline points
	dvariable splin2(const dvector& _x1a,const dvector* _x2a, const dmatrix _ya,
		dvar_matrix& _y2a, const double& x1,const double& x2)
	*/

	RETURN_ARRAYS_INCREMENT();
	int i,j;
	int m=knots.rowmax();
	int n=knots.colmax();

	int mm=S.rowmax()-S.rowmin()+1;
	int nn=S.colmax()-S.colmin()+1;

	dvar_matrix shift_S(1,mm,1,nn);

	dvector im(1,mm); im.fill_seqadd(0,1./(mm-1.));
	dvector in(1,nn); in.fill_seqadd(0,1./(nn-1.));
	dvar_matrix y2(1,m,1,n);	//matrix of second-derivatives
	y2=splie2(x,y,knots);

	for(i=1;i<=mm;i++){
		for(j=1;j<=nn;j++){
			shift_S(i,j)=splin2(x,y,knots,y2,in(j),im(i));
		}
	}

	int ii,jj;
	ii=0;
	for(i=S.rowmin();i<=S.rowmax();i++)
	{
		ii++; jj=0;
		for(j=S.colmin();j<=S.colmax();j++)
		{
			jj++;
			S(i,j)=shift_S(ii,jj);
		}
	}

	//cout<<shift_S<<endl;
	RETURN_ARRAYS_DECREMENT();
	//cout<<"Bicubic"<<endl;
}



	// dvar_vector spline(const dvector &_x,const dvar_vector&_y,double yp1,double ypn)
	// {
	// 	RETURN_ARRAYS_INCREMENT();
	// 	dvector& x=(dvector&) _x;
	// 	dvar_vector& y=(dvar_vector&) _y;
	// 	int orig_min=x.indexmin();
	// 	x.shift(1);
	// 	y.shift(1);
	// 	// need to check that x is monotone increasing;
	// 	if  ( x.indexmax() != y.indexmax() )
	// 	{
	// 	  cerr << " Incompatible bounds in input to spline, fix it" << endl;
	// 	}
	// 	int n=x.indexmax();
	// 	dvar_vector y2(1,n);
	// 	int i,k;
	// 	dvariable  p,qn,sig,un;
	// 	dvar_vector u(1,n-1);
	// 	if (yp1 > 0.99e30)
	//   {
	//     y2[1]=u[1]=0.0;
	//   }
	//   else
	//   {
	//     y2[1] = -0.5;
	//     u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
	//   }
	//   for (i=2;i<=n-1;i++)
	//   {
	//     sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
	//     p=sig*y2[i-1]+2.0;
	//     y2[i]=(sig-1.0)/p;
	//     u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
	//     u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
	//   }
	//   if (ypn > 0.99e30)
	//   {
	//     qn=un=0.0;
	//   }
	//   else
	//   {
	//     qn=0.5;
	//     un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
	//   }
	//   y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
	//   for (k=n-1;k>=1;k--)
	//   {
	//     y2[k]=y2[k]*y2[k+1]+u[k];
	//   }
	//   x.shift(orig_min);
	//   y.shift(orig_min);
	//   y2.shift(orig_min);
	//   RETURN_ARRAYS_DECREMENT();
	//   return y2;
	// }
	//
	//
	// dvariable splint(const dvector& _xa,const dvar_vector& _ya, const dvar_vector& _y2a,double x)
	// {
	//   RETURN_ARRAYS_INCREMENT();
	//   dvector& xa=(dvector&) _xa;
	//   dvar_vector& ya=(dvar_vector&) _ya;
	//   dvar_vector& y2a=(dvar_vector&) _y2a;
	//   int orig_min=xa.indexmin();
	//   xa.shift(1);
	//   ya.shift(1);
	//   y2a.shift(1);
	//   dvariable y;
	//   int n = xa.indexmax();
	//   int klo,khi,k;
	//   dvariable h,b,a;
	//
	//   klo=1;
	//   khi=n;
	//   while (khi-klo > 1)
	//   {
	//     k=(khi+klo) >> 1;
	//     if (xa[k] > x) khi=k;
	//     else klo=k;
	//   }
	//   h=xa[khi]-xa[klo];
	//   a=(xa[khi]-x)/h;
	//   b=(x-xa[klo])/h;
	//   y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
	//   xa.shift(orig_min);
	//   ya.shift(orig_min);
	//   y2a.shift(orig_min);
	//   RETURN_ARRAYS_DECREMENT();
	//   return y;
	// }
	//

dvar_matrix splie2(const dvector& _x1a,const dvector& _x2a,const dvar_matrix& _ya)//,dvar_matrix& _y2a)
{
/*  NR code:
	void splie2(float x1a[], float x2a[], float **ya, int m, int n, float **y2a)
	Given an m by n tabulated function ya[1..m][1..n], and tabulated independent variables
	x2a[1..n], this routine constructs one-dimensional natural cubic splines of the rows of ya
	and returns the second-derivatives in the array y2a[1..m][1..n]. (The array x1a[1..m] is
	included in the argument list merely for consistency with routine splin2.)
	{
	void spline(float x[], float y[], int n, float yp1, float ypn, float y2[]);
	int j;
	for (j=1;j<=m;j++)
	spline(x2a,ya[j],n,1.0e30,1.0e30,y2a[j]); Values 1x1030 signal a nat-
	}	*/
	RETURN_ARRAYS_INCREMENT();
	dvector& x1a=(dvector&) _x1a;
	dvector& x2a=(dvector&) _x2a;
	dvar_matrix& ya=(dvar_matrix&) _ya;
	//dvar_matrix& y2a=(dvar_matrix&) _y2a;
	int m=ya.rowmax();
	int n=ya.colmax();
	dvar_matrix y2a(1,m,1,n);
	int j;
	for(j=1;j<=m;j++)
		y2a(j)=spline(x1a,ya(j),1.0e30,1.e30);
	//function should return second-derivatives in y2a[1..m][1..n]
	RETURN_ARRAYS_DECREMENT();
	return y2a;
}



dvariable splin2(const dvector& _x1a,const dvector& _x2a, const dvar_matrix _ya,
	dvar_matrix& _y2a, const double& x1,const double& x2)//,dvariable& y)
{
	/*
	Original NR code:
	void splin2(float x1a[], float x2a[], float **ya, float **y2a, int m, int n,
	float x1, float x2, float *y)
	Given x1a, x2a, ya, m, n as described in splie2 and y2a as produced by that routine; and
	given a desired interpolating point x1,x2; this routine returns an interpolated function value y
	by bicubic spline interpolation.
	{
	void spline(float x[], float y[], int n, float yp1, float ypn, float y2[]);
	void splint(float xa[], float ya[], float y2a[], int n, float x, float *y);
	int j;
	float *ytmp,*yytmp;
	ytmp=vector(1,m);
	yytmp=vector(1,m); Perform m evaluations of the row splines constructed by
	splie2, using the one-dimensional spline evaluator
	splint.
	for (j=1;j<=m;j++)
	splint(x2a,ya[j],y2a[j],n,x2,&yytmp[j]);
	spline(x1a,yytmp,m,1.0e30,1.0e30,ytmp); Construct the one-dimensional colsplint(
	x1a,yytmp,ytmp,m,x1,y); umn spline and evaluate it.
	free_vector(yytmp,1,m);
	free_vector(ytmp,1,m);
	}
	*/
	RETURN_ARRAYS_INCREMENT();
	dvector& x1a=(dvector&) _x1a;
	dvector& x2a=(dvector&) _x2a;
	dvar_matrix& ya=(dvar_matrix&) _ya;
	dvar_matrix& y2a=(dvar_matrix&) _y2a;
	int j;
	int m=ya.rowmax();
	int n=ya.colmax();
	dvariable y;
	dvar_vector ytmp(1,m);
	dvar_vector yytmp(1,m);
	for (j=1;j<=m;j++)
		yytmp[j]=splint(x1a,ya[j],y2a[j],x2);

	ytmp=spline(x2a,yytmp,1.0e30,1.0e30);
	y=splint(x2a,yytmp,ytmp,x1);

	RETURN_ARRAYS_DECREMENT();
	return(y);
}

