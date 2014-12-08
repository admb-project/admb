#include "statsLib.h"

/**
* @file fill.cpp
* @brief Fills a matrix with a vector
* \ingroup STATLIB
* This function fills a matrix m with a vector v.  The matrix must
* have the same number of elements as the vector.
* eg. fill(m,v);          \n
* Example;                \n
* vector x(1,50);         \n
* matrix m(1,5,1,10);     \n
* !! x.fill_seqadd(1,1);  \n
* !! fill(m,x);           \n
* !! cout<<m<<endl;       \n
* Produces the following output.\n
*  
*  1 2 3 4 5 6 7 8 9 10\n
*  1 2 3 4 5 6 7 8 9 10\n
*  1 2 3 4 5 6 7 8 9 10\n
*  1 2 3 4 5 6 7 8 9 10\n
*  1 2 3 4 5 6 7 8 9 10\n
* 
* 
* @param m is a dmatrix
* @param v is a dvector.
* 
* @author Dave Fournier & Steve Martell
* 
* @date 3/24/2011
*/

/** \author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-07-11
	\param  _d a data matix that is filled with vector v
	\param  _v a data vector
	
	\sa
**/
void fill(const dmatrix& _d,const dvector& _v)
{
 ADUNCONST(dmatrix,d) 
 ADUNCONST(dvector,v)
 int mmin =d.indexmin();
 int mmax =d.indexmax();
 int sz=0;
 int i;
 ivector sz1(mmin,mmax);
 for (i=mmin;i<=mmax;i++)
 {
   sz1(i)=d(i).indexmax()-d(i).indexmin()+1;
   sz+=sz1(i);
 }
 
 if (sz != v.indexmax()-v.indexmin()+1)
 {
   cerr << "Error in sizes in function"
     " void fill(const dmatrix& _d,const dvector& v)" << endl;
   ad_exit(1);
 }
 int offset=v.indexmin();
 for (i=mmin;i<=mmax;i++)
 {
   d(i)=v(offset,offset+sz1(i)-1).shift(d(i).indexmin());
 }
}

/** \author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-07-11
	\param  _d a data matix that is filled with vector v
	\param  _v a data vector
	
	\sa
**/
void fill(const dvar_matrix& _d,const dvar_vector& _v)
{
 ADUNCONST(dvar_matrix,d)
 ADUNCONST(dvar_vector,v)
 int mmin =d.indexmin();
 int mmax =d.indexmax();
 int sz=0;
 int i;
 ivector sz1(mmin,mmax);
 for (i=mmin;i<=mmax;i++)
 {
   sz1(i)=d(i).indexmax()-d(i).indexmin()+1;
   sz+=sz1(i);
 }
 
 if (sz != v.indexmax()-v.indexmin()+1)
 {
   cerr << "Error in sizes in function"
     " void fill(const dmatrix& _d,const dvector& v)" << endl;
   ad_exit(1);
 }
 int offset=v.indexmin();
 for (i=mmin;i<=mmax;i++)
 {
   d(i)=v(offset,offset+sz1(i)-1).shift(d(i).indexmin());
 }
}
