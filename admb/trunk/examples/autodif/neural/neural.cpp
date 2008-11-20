

#include <fvar.hpp>
#include <iomanip.h>

extern unsigned _stklen=20000;

struct neural_net_design
{
  unsigned int num_levels;
  unsigned int * num_nodes;
};

int nvar_calc(int& num_levels,ivector& num_nodes);

dvar_vector sigmoid(dvar_vector& v);

void xinit(d3_array W,dmatrix& B,y,int& num_levels,ivector& num_nodes);

void reset(d3_array W,dmatrix& B,y,int& num_levels,ivector& num_nodes);

main()
{
  int num_levels;
  int nvar;

  ifstream infile("struct.nrl");
  infile >> num_levels;
  ivector num_nodes(1,num_levels);
  infile >> num_nodes;

  ivector iv(2,n)
  for (int i=2;i<=n;i++)
  {
    iv(i)=num_nodes(i); // Put the desired elements of num_nodes into iv
  }
  // Now declare B
  dvar_matrix B(2,n,1,iv);


  ivector nrows(1,n-1);
  ivector ncols(1,n-1);
  for (int i=1;i<n;i++)
  {
    nrows(i)=num_nodes(i+1);
    ncols(i)=num_nodes(i);
  }
  // Now declare W
  dvar3_array W(1,n-1,1,nrows,1,ncols);

  {
    ifstream infile1("weights.par");
    infile1 >> W;  // read in the current parameter estimates for weights
    infile1 >> B;  // read in the current parameter estimates for bias
  }

  nvar=num_weights_calc(num_levels,num_nodes);// calculate the number of
                                              // parameters to be estimated
  independent_variables y(1,nvar);  //make the vector of independent variables

  fmmc fmc(nvar); //declare the function minimizer control structure for
                  //the conjugate gradient function minimizer
  double f;
  dvector g(1,nvar);
  fmc.maxfn=1000;
  fmc.iprint=1;
  xinit(W,B,y,num_nodes); // Put the parameters into the vector of 
                          // independent variables
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc)  // macro to begin the minimization loop
    f=neural_function(x, num_nodes, num_levels,weights,nodes,0);
  END_MINIMZATION            // macro to end the minimization loop
  neural_function(x, num_nodes, num_levels,weights,nodes,1);
  {
    // Save the current estimates for the parameters
    ofstream outfile("out.par");
    outfile << W <<"\n";
    outfile << B <<"\n";
  }
}

void xinit(d3_array W,dmatrix& B,y,int& num_levels,ivector& num_nodes)
{
  int smin=W.slicemin();
  int smax=W.slicemax();
  int ii=1;
   
  for (int i=smin; i<smax; i++)
  {
    int rmin=W(i).rowmin();
    int rmax=W(i).rowmax();
    for (int j=rmin,j<=rmax;j++)
    {
      int imin=W(i,j).indexmin();
      int imax=W(i,j).indexmax();
      for (int k=imin,k<=imax;k++)
      {
        W(i,j,k)=y(ii++);
      }
    }
  }

  int rmin=B.row_min();
  int rmax=B.row_max();
  for (i=rmin; i<=rmax; i++)
  {
    int imin=B.indexmin();
    int imax=B.indexmax();
    for (int j=imin; j<=imax; j++)
    {
      B(i,j)=y(ii++);
    }
  }
}   

void reset(d3_array W,dmatrix& B,y,int& num_levels,ivector& num_nodes)
{
  int smin=W.slicemin();
  int smax=W.slicemax();
  int ii=1;
   
  for (int i=smin; i<smax; i++)
  {
    int rmin=W(i).rowmin();
    int rmax=W(i).rowmax();
    for (int j=rmin,j<=rmax;j++)
    {
      int imin=W(i,j).indexmin();
      int imax=W(i,j).indexmax();
      for (int k=imin,k<=imax;k++)
      {
        y(ii++)=W(i,j,k);
      }
    }
  }

  int rmin=B.row_min();
  int rmax=B.row_max();
  for (i=rmin; i<=rmax; i++)
  {
    int imin=B.indexmin();
    int imax=B.indexmax();
    for (int j=imin; j<=imax; j++)
    {
      y(ii++)=B(i,j);
    }
  }
}   

int nvar_calc(int& num_levels,ivector& num_nodes)
{
  int nvar=0;
  for (int i=1; i<num_levels; i++)
  {
    nvar+=num_nodes[i]*num_nodes[i+1];


#include <fvar.hpp>
#include <iomanip.h>

extern unsigned _stklen=20000;

struct neural_net_design
{
  unsigned int num_levels;
  unsigned int * num_nodes;
};

int nvar_calc(int& num_levels,ivector& num_nodes);

double neural_function(dvar_vector& x, ivector& num_nodes,int & num_levels,
  dvar_matrix ** weights,dvar_vector ** nodes, int& print_switch);

dvar_vector sigmoid(dvar_vector& v);

main()
{
  int num_levels;
  int nvar;

  ifstream infile("struct.nrl");
  infile >> num_levels;
  ivector num_nodes(1,num_levels);
  infile >> num_nodes;

  dvar_matrix x(1,n,1,num_nodes); // these are the nodes
  ivector iv(2,n)
  for (int i=2;i<=n;i++)
  {
    iv(i)=num_nodes(i); // Put the desired elements of num_nodes into iv
  }
  // Now declare B
  dvar_matrix B(2,n,1,iv);


  ivector nrows(1,n-1);
  ivector ncols(1,n-1);
  for (int i=1;i<n;i++)
  {
    nrows(i)=num_nodes(i+1);
    ncols(i)=num_nodes(i);
  }
  // Now declare W
  dvar3_array W(1,n-1,1,nrows,1,ncols);

  {
    ifstream infile1("weights.par");
    infile1 >> W;  // read in the current parameter estimates for weights
    infile1 >> B;  // read in the current parameter estimates for bias
  }

  nvar=num_weights_calc(num_levels,num_nodes);// calculate the number of
                                              // parameters to be estimated
  independent_variables y(1,nvar);  //make the vector of independent variables

  fmmc fmc(nvar); //declare the function minimizer control structure for
                  //the conjugate gradient function minimizer
  double f;
  dvector g(1,nvar);
  fmc.maxfn=1000;
  fmc.iprint=1;
  xinit(W,B,y,num_nodes); // Put the parameters into the vector of 
                          // independent variables
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc)  // macro to begin the minimization loop
    f=neural_function(x, num_nodes, num_levels,weights,nodes,0);
  END_MINIMZATION            // macro to end the minimization loop
  neural_function(x, num_nodes, num_levels,weights,nodes,1);
  {
    // Save the current estimates for the parameters
    ofstream outfile("out.par");
    outfile << W <<"\n";
    outfile << B <<"\n";
  }
}

xinit(d3_array W,dmatrix& B,y,int& num_levels,ivector& num_nodes)
{
  int smin=W.slicemin();
  int smax=W.slicemax();
   
  for (int i=smin; i<smax; i++)
  {
    int rmin=W(i).rowmin();
    int rmax=W(i).rowmax();
    for (int j=rmin,j<=rmax;j++)
    {
      int imin=W(i,j).indexmin();
      int imax=W(i,j).indexmax();
      for (int k=imin,k<=imax;k++)
      {
        W(i,j,k)=y(ii++);
      }
    }
  }




}
      


    nvar+=num_nodes[i]*num_nodes[i+1];
  }
  for (i=2;i<=n;i++)
  {
    nvar+=num_nodes(i); 
  }
}


int nvar_calc(int& num_levels,ivector& num_nodes)
{
  int nvar=0;
  for (int i=1; i<num_levels; i++)
  {
    nvar+=num_nodes[i]*num_nodes[i+1];
  }
  for (i=2;i<=n;i++)
  {
    nvar+=num_nodes(i); 
  }
  return nvar;
}

double neural_function(dvar_vector& y, ivector& num_nodes,int & num_levels,
  int& print_switch)
{
  int ii=0;

  dvar3_array W(1,n-1,1,nrows,1,ncols);
  dvar_matrix B(2,n,1,iv);

  int num_learn;

  dvector correct_response(1,num_nodes[num_levels]);

  ifstream infile("learning.smp");
  infile >> num_learn;
  dvariable z;

  if (print_switch ==0)
  {
    for (int k=1;k<= num_learn; k++)
    {
      infile >> *(nodes[1]);
      infile >> correct_response;
      for (i=1;i<num_levels; i++)
      {
        *(nodes[i+1])=sigmoid(*(weights[i])* *(nodes[i]));
      }
      dvariable u=norm(correct_response-*(nodes[num_levels]));
      z+=100*u*u;
    }
  }
  else
  {
    ofstream outfile("fitrep.out");
    for (int k=1;k<=num_learn; k++)
    {
      infile >> *(nodes[1]);
      infile >> correct_response;

      for (i=1;i<num_levels; i++)
      {
        *(nodes[i+1])=sigmoid(*(weights[i])* *(nodes[i]));
      }

      double diff;
      // determine if the neural net got this one right
      diff=max(fabs(correct_response-value(*(nodes[num_levels]))));
      if (diff > .4999)
      {
        outfile << " ** w ";
      }
      else
      {
        outfile << "    r ";
      }

      outfile << " sample " << k << "  ";
      for (int kk=1;kk<=num_nodes[num_levels]; kk++)
      {

        outfile  << correct_response[kk] << "  " <<
           (*(nodes[num_levels]))[kk] << "  ";

      }
      outfile << "\n";

      dvariable u=norm(correct_response-*(nodes[num_levels]));
      z+=u*u;
    }
  }
  z=z;
  dvariable v;
  for (i=1;i<num_levels; i++)  
  {
    v=norm(*(weights[i]));
    z+=v*v;
  }

  for (i=1;i<num_levels; i++)
  {
    delete weights[i];
  }


  for (i=1;i<=num_levels; i++)
  {
    delete nodes[i];
  }
  return value(z);
}


  dvar_vector sigmoid(dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(v.indexmin(),v.indexmax());

    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp[i]=sigmoid(v[i]);
    }
    RETURN_ARRAYS_DECREMENT();
    return (tmp);
  }


********************************************8
********************************************8
********************************************8
********************************************8
dvar_matrix x(1,n,1,num_nodes);



ivector iv(2,n)
for (int i=2;i<=n;i++)
{
  iv(i)=num_nodes(i); // Put the desired elements of num_nodes into iv
}
// Now declare B
dvar_matrix B(2,n,1,iv);




ivector nrows(1,n-1);
ivector ncols(1,n-1);
for (int i=1;i<n;i++)
{
  nrows(i)=num_nodes(i+1);
  ncols(i)=num_nodes(i);
}
// Now declare W
dvar3_array W(1,n-1,1,nrows,1,ncols);



dvar_vector get_response(dvector& stimulus,dvar_matrix& X,dvar_matrix& B,
  dvar3_array W)
// For an input dvector stimulus, this function calculates the output
// response dvar_vector of the neural net and returns it
{
  RETURN_ARRAYS_INCREMENT(); // should have this because the function 
                             // returns a variable type
  X[1]=stimulus;
  for (int i=1;i<n;i++)
  {
    X[i+1]=Phi(W[i]*X[i]+B[i+1]);  
  }
  RETURN_ARRAYS_DECREMENT(); 
  return(X[n]) // Returns the response of the neural net
}


double fcomp(ivector& num_nodes, dvar_matrix X, dvar_matrix B, dvar3_array& W)  
{
  // nsample is the number of examples in the training set
  unsigned int nsample;
  dvector stimulus(1,num_nodes(1));
  dvector response(1,num_nodes(1));
  ifstream infile("training.dat");  // training.dat is a file containing the 
                                    // training set 
  infile >> nsample;  // Read in the number of samples in the training set
   
  dvariable f;
  f=0.0;
  for (int i=1;i<=nsample;i++)
  {
    infile >> stimulus;
    infile >> response;
    {
      diff=response-get_response(stimulus,X,B,W); // diff is the difference
                 // between the desired response and the actual response
    }
    f += diff*diff;  // f will contain the squared error in the response  
  }
  double tmp=value(f);
  return(tmp);
}


dvar_vector Phi(dvar_vector& v)
{
  // This squashing function maps into the interval (-1,1)
  RETURN_ARRAYS_INCREMENT;  // Need this because the function returns a 
                            // variable type
  int min=v.minindex();
  int max=v.maxindex();
  dvar_vector tmp(min,max)
  for (int i=min;i<=max;i++)
  {
    tmp(i)=0.63662*atan(v(i)); //0.63662 is 2/PI 
    // tmp(i)=0.31831*atan(v(i))+0.5; // This maps into (0,1) instead of (-1,1)
  }
  RETURN_ARRAYS_DECREMENT; 
  return(tmp);
}
  }
  for (i=2;i<=n;i++)
  {
    nvar+=num_nodes(i); 
  }
  return nvar;
}


  int num_learn;

  dvector correct_response(1,num_nodes[num_levels]);

  ifstream infile("learning.smp");
  infile >> num_learn;
  dvariable z;

  if (print_switch ==0)
  {
    for (int k=1;k<= num_learn; k++)
    {
      infile >> *(nodes[1]);
      infile >> correct_response;
      for (i=1;i<num_levels; i++)
      {
        *(nodes[i+1])=sigmoid(*(weights[i])* *(nodes[i]));
      }
      dvariable u=norm(correct_response-*(nodes[num_levels]));
      z+=100*u*u;
    }
  }
  else
  {
    ofstream outfile("fitrep.out");
    for (int k=1;k<=num_learn; k++)
    {
      infile >> *(nodes[1]);
      infile >> correct_response;

      for (i=1;i<num_levels; i++)
      {
        *(nodes[i+1])=sigmoid(*(weights[i])* *(nodes[i]));
      }

      double diff;
      // determine if the neural net got this one right
      diff=max(fabs(correct_response-value(*(nodes[num_levels]))));
      if (diff > .4999)
      {
        outfile << " ** w ";
      }
      else
      {
        outfile << "    r ";
      }

      outfile << " sample " << k << "  ";
      for (int kk=1;kk<=num_nodes[num_levels]; kk++)
      {

        outfile  << correct_response[kk] << "  " <<
           (*(nodes[num_levels]))[kk] << "  ";

      }
      outfile << "\n";

      dvariable u=norm(correct_response-*(nodes[num_levels]));
      z+=u*u;
    }
  }
  z=z;
  dvariable v;
  for (i=1;i<num_levels; i++)  
  {
    v=norm(*(weights[i]));
    z+=v*v;
  }
  return value(z);
}

  dvar_vector sigmoid(dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(v.indexmin(),v.indexmax());

    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp[i]=sigmoid(v[i]);
    }
    RETURN_ARRAYS_DECREMENT();
    return (tmp);
  }


********************************************8
********************************************8
********************************************8
********************************************8
dvar_matrix x(1,n,1,num_nodes);



ivector iv(2,n)
for (int i=2;i<=n;i++)
{
  iv(i)=num_nodes(i); // Put the desired elements of num_nodes into iv
}
// Now declare B
dvar_matrix B(2,n,1,iv);




ivector nrows(1,n-1);
ivector ncols(1,n-1);
for (int i=1;i<n;i++)
{
  nrows(i)=num_nodes(i+1);
  ncols(i)=num_nodes(i);
}
// Now declare W
dvar3_array W(1,n-1,1,nrows,1,ncols);



dvar_vector get_response(dvector& stimulus,dvar_matrix& X,dvar_matrix& B,
  dvar3_array W)
// For an input dvector stimulus, this function calculates the output
// response dvar_vector of the neural net and returns it
{
  RETURN_ARRAYS_INCREMENT(); // should have this because the function 
                             // returns a variable type
  X[1]=stimulus;
  for (int i=1;i<n;i++)
  {
    X[i+1]=Phi(W[i]*X[i]+B[i+1]);  
  }
  RETURN_ARRAYS_DECREMENT(); 
  return(X[n]) // Returns the response of the neural net
}


double fcomp(ivector& num_nodes, dvar_matrix X, dvar_matrix B, dvar3_array& W)  
{
  // nsample is the number of examples in the training set
  unsigned int nsample;
  dvector stimulus(1,num_nodes(1));
  dvector response(1,num_nodes(1));
  ifstream infile("training.dat");  // training.dat is a file containing the 
                                    // training set 
  infile >> nsample;  // Read in the number of samples in the training set
   
  dvariable f;
  f=0.0;
  for (int i=1;i<=nsample;i++)
  {
    infile >> stimulus;
    infile >> response;
    {
      diff=response-get_response(stimulus,X,B,W); // diff is the difference
                 // between the desired response and the actual response
    }
    f += diff*diff;  // f will contain the squared error in the response  
  }
  double tmp=value(f);
  return(tmp);
}


dvar_vector Phi(dvar_vector& v)
{
  // This squashing function maps into the interval (-1,1)
  RETURN_ARRAYS_INCREMENT;  // Need this because the function returns a 
                            // variable type
  int min=v.minindex();
  int max=v.maxindex();
  dvar_vector tmp(min,max)
  for (int i=min;i<=max;i++)
  {
    tmp(i)=0.63662*atan(v(i)); //0.63662 is 2/PI 
    // tmp(i)=0.31831*atan(v(i))+0.5; // This maps into (0,1) instead of (-1,1)
  }
  RETURN_ARRAYS_DECREMENT; 
  return(tmp);
}
