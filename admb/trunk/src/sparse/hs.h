/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California
 */

#if !defined(__HS_H__)
#define  __HS_H__ 
extern "C" 
{
  #include "cs.h"
}
class dcompressed_triplet;
class dvar_compressed_triplet;

 //class hs_symbolic    	// Info for symbolic cholesky
 //{
 //    public:
 //
 //    int n ;     	// Dimension of underlying pos. def. matrix
 //    ivector pinv ;     	// inverse row perm. for QR, fill red. perm for Chol 
 //    ivector parent ;   	// elimination tree for Cholesky and QR 
 //    ivector cp ;       	// column pointers for Cholesky, row counts for QR 
 //    double lnz ;    	// # entries in L for LU or Cholesky; in V for QR 
 //
 //    hs_symbolic(int, XCONST css *); 
 //    hs_symbolic(int n, XCONST dmatrix &T, int order);
 //    hs_symbolic(XCONST dcompressed_triplet &T, int order);
 //    hs_symbolic(XCONST dvar_compressed_triplet &T, int order);
 //    int is_null(); 
 //    int cmp(hs_symbolic &S);
 //    hs_symbolic(void);
 //};

class hs_smatrix    	// matrix in compressed-column, 0 offset
{
    public:

    int nzmax ;     	// maximum number of entries; in practice nzmax= # non-zero
    int m ;         	// number of rows 
    int n ;         	// number of columns; m=n for symmetric matrix 
    ivector p ;        	// column pointers (size n+1) or col indices; size nzmax 
    ivector i ;        	// row indices, size nzmax 
    dvector x ;     	// numerical values, size nzmax 

    //hs_smatrix(int ,XCONST dmatrix &); 			// Initialization
    hs_smatrix(int ,XCONST dcompressed_triplet &); 			// Initialization
    hs_smatrix(int n, int nzmax); 			// Initialization
    hs_smatrix(XCONST cs *A);		// To convert from cs-format
    hs_smatrix(XCONST hs_symbolic &); 			// To generate cholesky factor
    hs_smatrix(XCONST hs_smatrix &); 			// Copy XCONSTructor
    void reallocate(int _nzmax);
    hs_smatrix& operator = (XCONST hs_smatrix &); 	// Assigment

    double trace_log();					// Used in determinant 		
    double trace_log(int &);					// Used in determinant 		
    int print();
    int print_pattern();
    int print_trans_zeros();
    hs_symbolic sym;
    
    dvector & get_x(void) {return x;}
    hs_smatrix(void) : nzmax(0),m(0),n(0){}
};

class dvar_hs_smatrix    	// matrix in compressed-column, 0 offset
{
    public:

    int nzmax ;     	// maximum number of entries; in practice nzmax= # non-zero
    int m ;         	// number of rows 
    int n ;         	// number of columns; m=n for symmetric matrix 
    ivector p ;        	// column pointers (size n+1) or col indices; size nzmax 
    ivector i ;        	// row indices, size nzmax 
    dvar_vector x ;     	// numerical values, size nzmax 

    dvar_hs_smatrix(int ,XCONST dmatrix &); 			// Initialization
    dvar_hs_smatrix(int ,XCONST dvar_compressed_triplet &); 			// Initialization
    dvar_hs_smatrix(int n, int nzmax); 			// Initialization
    dvar_hs_smatrix(XCONST cs *A);		// To convert from cs-format
    dvar_hs_smatrix(XCONST hs_symbolic &); 			// To generate cholesky factor
    dvar_hs_smatrix(XCONST dvar_hs_smatrix &); 			// Copy XCONSTructor
    void reallocate(int _nzmax);
    dvar_hs_smatrix& operator = (XCONST dvar_hs_smatrix &); 	// Assigment

    dvariable trace_log(hs_symbolic&);			// Used in determinant 		
    dvariable trace_log(hs_symbolic&,int&);			// Used in determinant 		
    dvariable trace_log();			// Used in determinant 		
    dvariable trace_log(int &);			// Used in determinant 		
    int print();
    int print_pattern();
    int print_trans_zeros();
    hs_symbolic sym;
};

cs *hs_calloc();
double 	cs_cumsum (ivector &p, ivector &c, int n);
static 	int cs_wclear (int mark, int lemax, ivector &w, int n);
void 	cs_transpose (XCONST hs_smatrix &A, int values, hs_smatrix &AT);
void 	cs_transpose (XCONST dvar_hs_smatrix &A, int values, dvar_hs_smatrix &AT);
cs*	hs_convert(XCONST hs_smatrix & CC);
int 	cs_ereach (XCONST hs_smatrix &A, int k, XCONST ivector &parent, ivector &s, ivector &w);
int 	cs_ereach (XCONST dvar_hs_smatrix &A, int k, XCONST ivector &parent, ivector &s, ivector &w);
void 	hs_symperm(XCONST hs_smatrix &A, XCONST ivector &pinv, hs_smatrix &C);
void 	hs_symperm(XCONST dvar_hs_smatrix &A, XCONST ivector &pinv, dvar_hs_smatrix &C);
int 	chol(XCONST hs_smatrix &A, XCONST hs_symbolic &S, hs_smatrix &L);
int 	chol(XCONST dvar_hs_smatrix &A, XCONST hs_symbolic &S, dvar_hs_smatrix &L);
dvector cs_ipvec(XCONST ivector &p, XCONST dvector &b);
dvector cs_pvec (XCONST ivector &p, XCONST dvector &b);
dvar_vector cs_pvec (XCONST ivector &p, XCONST dvar_vector &b);
dvector cs_lsolve (XCONST hs_smatrix &L, XCONST dvector &y);
dvar_vector cs_lsolve (XCONST dvar_hs_smatrix &L, XCONST dvar_vector &y);
dvector cs_ltsolve (XCONST hs_smatrix &L, XCONST dvector &y);
dvar_vector cs_ltsolve (XCONST dvar_hs_smatrix &L, XCONST dvar_vector &y);
int 	cs_fkeep (hs_smatrix &A, int (*fkeep) (int, int, double, void *), void *other);
int 	cs_fkeep (dvar_hs_smatrix &A, int (*fkeep) (int, int, const prevariable& , void *), void *other);
int 	cs_scatter(XCONST hs_smatrix &A, int j, double beta, ivector &w, dvector &x, int mark,hs_smatrix &C, int nz);
int 	cs_scatter(XCONST dvar_hs_smatrix &A, int j, double beta, ivector &w, dvar_vector &x, int mark,hs_smatrix &C, int nz);
hs_smatrix cs_add(XCONST hs_smatrix &A, XCONST hs_smatrix &B, double alpha=1.0, double beta=1.0);
dvar_hs_smatrix cs_add(XCONST dvar_hs_smatrix &A, XCONST dvar_hs_smatrix &B, double alpha=1.0, double beta=1.0);
int 	cs_tdfs (int j, int k, ivector &head, XCONST ivector &next, ivector &post, ivector &stack);
ivector cs_amd (XCONST hs_smatrix &A);
ivector cs_amd (XCONST dvar_hs_smatrix &A);
ivector cs_amd (int order,XCONST hs_smatrix &A);
ivector cs_amd (int order,XCONST dvar_hs_smatrix &A);
ivector cs_etree (XCONST hs_smatrix &A);
ivector cs_etree (XCONST dvar_hs_smatrix &A);
ivector cs_post (XCONST ivector &parent, int n);
int 	cs_leaf (int i, int j, XCONST ivector &first, ivector &maxfirst, ivector &prevleaf,ivector &ancestor, int *jleaf);
ivector cs_counts (XCONST hs_smatrix &A, XCONST ivector &parent, XCONST ivector &post);
ivector cs_counts (XCONST dvar_hs_smatrix &A, XCONST ivector &parent, XCONST ivector &post);
ivector cs_pinv (XCONST ivector &p, int n);

dvariable ln_det(XCONST dvar_hs_smatrix & M);
dvariable ln_det(XCONST dvar_hs_smatrix & M,XCONST hs_symbolic&);
dvariable ln_det(XCONST dvar_hs_smatrix & M,XCONST hs_symbolic&,int& sgn);
dvariable ln_det(XCONST dvar_hs_smatrix & M,int& sgn);

istream & operator >> (istream & is,dcompressed_triplet & M);
istream & operator >> (istream & is,dvar_compressed_triplet & M);

dmatrix make_dmatrix(dcompressed_triplet& M,int n,int m);
dvar_matrix make_dvar_matrix(dvar_compressed_triplet& M,int n,int m);
#endif
