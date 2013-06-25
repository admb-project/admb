#include "gdbprintlib.h"

/**
* Do nothing, this will be included by ADMB lexical analyzer
* so that the library is usable from within GDB
* @return Nothing
**/
void pad()
{
}

/**
* Print a double precision number to the screen
* @param v The double to print
* @return Nothing
**/
void pad(double v)
{
  cout << v << endl;
}

 /**
* Print an adstring to the screen
* @param v The adstring to print
* @return Nothing
**/
void pad(const adstring & v)
{
  cout << v << endl;
}

 /**
* Print a dvar3_array to the screen
* @param v The dvar3_array to print
* @return Nothing
**/
void pad(const dvar3_array & v)
{
  cout << v << endl;
}

 /**
* Print a matrix slice of a dvar3_array to the screen
* @param v The dvar3_array to print
* @param i 1-based index of the matrix to print
* @return Nothing
**/
void pad(const dvar3_array & v,int i)
{
  cout << v(i) << endl;
}

 /**
* Print a vector slice of a dvar3_array to the screen
* @param v The dvar3_array to print
* @param i 1-based index of the matrix to slice from
* @param j 1-based index of the row of the matrix to print
* @return Nothing
**/
void pad(const dvar3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

 /**
* Print a scalar of a dvar3_array to the screen
* @param v The dvar3_array to print
* @param i 1-based index of the matrix to slice from
* @param j 1-based index of the row of the matrix to print
* @param k 1-based index of the element of the vector to print
* @return Nothing
**/
void pad(const dvar3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

 /**
* Print a dvar4_array to the screen
* @param v The dvar4_array to print
* @return Nothing
**/
void pad(const dvar4_array & v)
{
  cout << v << endl;
}

 /**
* Print a 3D slice of a dvar4_array to the screen
* @param v The dvar4_array to print
* @param i 1-based index of the 3D object to print
* @return Nothing
**/
void pad(const dvar4_array & v,int i)
{
  cout << v(i) << endl;
}

 /**
* Print a matrix slice of a dvar4_array to the screen
* @param v The dvar4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @return Nothing
**/
void pad(const dvar4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

 /**
* Print a vector slice of a dvar4_array to the screen
* @param v The dvar4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @param k 1-based index of the vector to print
* @return Nothing
**/
void pad(const dvar4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

 /**
* Print a d4_array to the screen
* @param v The d4_array to print
* @return Nothing
**/
void pad(const d4_array & v)
{
  cout << v << endl;
}

 /**
* Print a 3D slice of a d4_array to the screen
* @param v The d4_array to print
* @param i 1-based index of the 3D object to print
* @return Nothing
**/void pad(const d4_array & v,int i)
{
  cout << v(i) << endl;
}

 /**
* Print a matrix slice of a d4_array to the screen
* @param v The d4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @return Nothing
**/
void pad(const d4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

 /**
* Print a vector slice of a d4_array to the screen
* @param v The d4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @param k 1-based index of the vector to print
* @return Nothing
**/
void pad(const d4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

 /**
* Print a d3_array to the screen
* @param v The d3_array to print
* @return Nothing
**/
void pad(const d3_array & v)
{
  cout << v << endl;
}

 /**
* Print a matrix slice of a d3_array to the screen
* @param v The d3_array to print
* @param i 1-based index of the matrix to print
* @return Nothing
**/
void pad(const d3_array & v,int i)
{
  cout << v(i) << endl;
}

 /**
* Print a vector slice of a d3_array to the screen
* @param v The d3_array to print
* @param i 1-based index of the matrix to print
* @param j 1-based index of the vector to print
* @return Nothing
**/
void pad(const d3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

/**
* Print a scalar of a d3_array to the screen
* @param v The d3_array to print
* @param i 1-based index of the matrix to print
* @param j 1-based index of the vector to print
* @param k 1-based index of the element to print
* @return Nothing
**/
void pad(const d3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}
 /**
* Print a i3_array to the screen
* @param v The i3_array to print
* @return Nothing
**/
void pad(const i3_array & v)
{
  cout << v << endl;
}

 /**
* Print a matrix slice of a i3_array to the screen
* @param v The i3_array to print
* @param i 1-based index of the matrix to print
* @return Nothing
**/
void pad(const i3_array & v,int i)
{
  cout << v(i) << endl;
}

 /**
* Print a vector slice of a i3_array to the screen
* @param v The i3_array to print
* @param i 1-based index of the matrix to print
* @param j 1-based index of the vector to print
* @return Nothing
**/
void pad(const i3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

/**
* Print a scalar of a i3_array to the screen
* @param v The i3_array to print
* @param i 1-based index of the matrix to print
* @param j 1-based index of the vector to print
* @param k 1-based index of the element to print
* @return Nothing
**/
void pad(const i3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

 /**
* Print a i4_array to the screen
* @param v The i4_array to print
* @return Nothing
**/
void pad(const i4_array & v)
{
  cout << v << endl;
}

 /**
* Print a 3D slice of a i4_array to the screen
* @param v The i4_array to print
* @param i 1-based index of the 3D object to print
* @return Nothing
**/
void pad(const i4_array & v,int i)
{
  cout << v(i) << endl;
}

 /**
* Print a matrix slice of a i4_array to the screen
* @param v The i4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @return Nothing
**/
void pad(const i4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

 /**
* Print a matrix slice of a i4_array to the screen
* @param v The i4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @return Nothing
**/
void pad(const i4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

 /**
* Print a scalar of a i4_array to the screen
* @param v The i4_array to print
* @param i 1-based index of the 3D object to print
* @param j 1-based index of the matrix to print
* @param k 1-based index of the vector to print
* @param l 1-based index of the element to print
* @return Nothing
**/
void pad(const i4_array & v,int i,int j,int k,int l)
{
  cout << v(i,j,k,l) << endl;
}

/**
* Print a dvar_vector to the screen
* @param v The dvar_vector
* @return Nothing
**/
void pad(const dvar_vector & v)
{
  cout << v << endl;
}

/**
* Print an element of a dvar_vector to the screen
* @param v The dvar_vector
* @param i 1-based index of the element to be printed
* @return Nothing
**/
void pad(const dvar_vector & v,int i)
{
  cout << v[i] << endl;
}

/**
* Print a prevariable to the screen
* @param v The prevariable to print
* @return Nothing
**/void pad(const prevariable & v)
{
  cout << v << endl;
}

/**
* Print a dvector to the screen
* @param v The dvector to print
* @return Nothing
**/
void pad(const dvector & v)
{
  cout << v << endl;
}

/**
* Print an ivector to the screen
* @param v The ivector to print
* @return Nothing
**/
void pad(const ivector & v)
{
  cout << v << endl;
}

/**
* Print a dvar_matrix to the screen
* @param v The dvar_matrix to print
* @return Nothing
**/
void pad(const dvar_matrix & v)
{
  cout << v << endl;
}

/**
* Print a vector slice of a dvar_matrix to the screen
* @param v The dvar_matrix to print
* @param i 1-based index of the vector to be printed
* @return Nothing
**/
void pad(const dvar_matrix & v,int i)
{
  cout << v(i) << endl;
}

/**
* Print a scalar of a dvar_matrix to the screen
* @param v The dvar_matrix to print
* @param i 1-based index of the vector to be printed
* @param j 1-based index of the element to be printed
* @return Nothing
**/
void pad(const dvar_matrix & v,int i,int j)
{
  cout << v(i,j) << endl;
}

/**
* Print a dmatrix to the screen
* @param v The dmatrix to print
* @return Nothing
**/
void pad(const dmatrix & v)
{
  cout << v << endl;
}

/**
* Print a imatrix to the screen
* @param v The imatrix to print
* @return Nothing
**/
void pad(const imatrix & v)
{
  cout << v << endl;
}

/**
* Print a vector slice of an imatrix to the screen
* @param v The imatrix to print
* @param i 1-based index of the vector to be printed
* @return Nothing
**/
void pad(const imatrix & v,int i)
{
  cout << v(i) << endl;
}

/**
* Print a scalar of an imatrix to the screen
* @param v The imatrix to print
* @param i 1-based index of the vector to be printed
* @param j 1-based index of the element to be printed
* @return Nothing
**/
void pad(const imatrix & v,int i,int j)
{
  cout << v(i,j) << endl;
}

/**
* Print an element of a dvar_vector to the screen in scientific notation
* @param v The dvar_vector
* @param i 1-based index of the element to be printed
* @return Nothing
**/
void pads(const dvar_vector & v,int i)
{
  cout << setscientific() << setprecision(5) << v[i] << endl;
}

/**
* Print a dvar_vector to the screen in scientific notation, with 5 significant figures
* @param v The dvar_vector
* @return Nothing
**/
void pads(const dvar_vector & v)
{
  cout << setscientific() << setprecision(5) << v << endl;
}

/**
* Print a vector slice of a dmatrix to the screen, with 12 significant figures.
* @param v The dmatrix to print
* @param i 1-based index of the vector to be printed
* @return Nothing
**/
void padp(const dmatrix & v,int i)
{
  cout << setprecision(12) << v(i) << endl;
}

/**
* Print a vector slice of a dvar_matrix to the screen, with 12 significant figures.
* @param v The dvar_matrix to print
* @param i 1-based index of the vector to be printed
* @return Nothing
**/
void padp(const dvar_matrix & v,int i)
{
  cout << setprecision(12) << v(i) << endl;
}

 /**
* Print the sum of a dvar_vector to the screen
* @param v The dvar_vector
* @return Nothing
**/
void padsum(const dvar_vector & v)
{
  cout << sum(v) << endl;
}

 /**
* Print the sum of a dvector to the screen
* @param v The dvector
* @return Nothing
**/
void padsum(const dvector & v)
{
  cout << sum(v) << endl;
}

 /**
* Print the sum of an ivector to the screen
* @param v The ivector
* @return Nothing
**/
void padsum(const ivector & v)
{
  cout << sum(v) << endl;
}

 /**
* Print the sum of a dvar_matrix to the screen
* @param v The dvar_matrix
* @return Nothing
**/
void padsum(const dvar_matrix & v)
{
  cout << sum(v) << endl;
}

 /**
* Print the sum of a dmatrix to the screen
* @param v The dmatrix
* @return Nothing
**/
void padsum(const dmatrix & v)
{
  cout << sum(v) << endl;
}

 /**
* Print the sum of an imatrix to the screen
* @param v The imatrix
* @return Nothing
**/
void padsum(const imatrix & v)
{
  cout << sum(v) << endl;
}
