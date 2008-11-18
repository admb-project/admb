#include <fvar.hpp>

#ifdef __BCPLUSPLUS__
  #include <iomanip.h>
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  #include <iomanip.hpp>
  long _stack = 20000;
#endif

int nvar_calc(dmatrix& B, d3_array& W);

dvar_vector Phi(dvar_vector& v);

void yinit(d3_array& W,dmatrix& B,independent_variables& y,int& num_levels,
  ivector& num_nodes);

void reset(dvar3_array W,dvar_matrix& B,dvar_vector& y,int& num_levels,
  ivector& num_nodes);

double neural_fit(dvar_vector& y);

double neural_fit(dvar_vector& y, ivector& num_nodes, int & num_levels,
  dvar_matrix& x,dvar3_array& W,dvar_matrix B,int& print_switch,
  ivector& nrows, ivector& ncols);

void main()
{
  int num_levels;
  int nvar;


  ifstream infile("struct.nrl");
  infile >> num_levels;
  ivector num_nodes(1,num_levels);
  infile >> num_nodes;
  if (!infile)
  {
    cerr << " Error reading in data from file struct.nrl\n";
    exit(1);
  }
  infile.close();

  dmatrix x(1,num_levels,1,num_nodes); // these are the nodes

  ivector iv(2,num_levels);
  for (int i=2;i<=num_levels;i++)
  {
    iv(i)=num_nodes(i); // Put the desired elements of num_nodes into iv
  }
  // Now declare B
  dmatrix B(2,num_levels,1,iv);

  ivector nrows(1,num_levels-1);
  ivector ncols(1,num_levels-1);
  for (i=1;i<num_levels;i++)
  {
    nrows(i)=num_nodes(i+1);
    ncols(i)=num_nodes(i);
  }

  // Now declare W
  d3_array W(1,num_levels-1,1,nrows,1,ncols);

  ifstream infile1("weights.par");


  nvar=nvar_calc(B,W);// calculate the number of parameters to be estimated

  infile1 >> W;
  if (!infile1)
  { 
     cerr << "ERROR reading weights from file weights.par\n"; exit(1);
  }
  infile1 >> B;
  if (!infile1)
  { 
     cerr << "ERROR reading bias terms from file weights.par\n"; exit(1);
  }

  independent_variables y(1,nvar);  //make the vector of independent variables

  yinit(W,B,y,num_levels,num_nodes);// Put the initial values into the vector
				    // of independent variables

  fmmc fmc(nvar); //declare the function minimizer control structure for
		 //the conjugate gradient function minimizer
  double f;
  dvector g(1,nvar);
  fmc.maxfn=1000;
  fmc.iprint=1;
  fmc.crit=.1;
  gradient_structure::set_MAX_NVAR_OFFSET(270);
  gradient_structure gs;
  while (fmc.ireturn>=0)
  {
    fmc.fmin(f,y,g);
    if (fmc.ireturn>0)
    {
      f=neural_fit(y,num_nodes,num_levels,x,W,B,0,nrows,ncols);

      gradcalc(nvar,g);
    }
  }
  // Call neural_fit one more time to get report
  neural_fit(y,num_nodes,num_levels,x,W,B,1,nrows,ncols);
}

void yinit(d3_array& W,dmatrix& B,independent_variables& y,int& num_levels,
  ivector& num_nodes)
{
  int ii=1;
  set_value_inv(W,y,ii);
  set_value_inv(B,y,ii);
}


void reset(dvar3_array W,dvar_matrix& B,dvar_vector& y,int& num_levels,
  ivector& num_nodes)
{
  int ii=1;
  set_value(W,y,ii);
  set_value(B,y,ii);
}

int nvar_calc(dmatrix& B, d3_array& W)
{
  int nvar=0;
  nvar+=size_count(B);
  nvar+=size_count(W);
  return nvar;
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



dvar_vector Phi(dvar_vector& v)
{
  // This squashing function maps into the interval (-1,1)
  RETURN_ARRAYS_INCREMENT();  // Need this because the function returns a
			    // variable type
  int min=v.indexmin();
  int max=v.indexmax();
  dvar_vector tmp(min,max);
  for (int i=min;i<=max;i++)
  {
    //tmp(i)=0.63662*atan(v(i)); //0.63662 is 2/PI maps into (-1,1)
    tmp(i)=0.31831*atan(v(i)); //0.36831 is 1/PI maps into (-.5,.5)
    // tmp(i)=0.31831*atan(v(i))+0.5; // This maps into (0,1) instead of (-1,1)
  }
  RETURN_ARRAYS_DECREMENT();
  return(tmp);
}

double neural_fit(dvar_vector& y, ivector& num_nodes, int & num_levels,
  dvar_matrix& x,dvar3_array& W,dvar_matrix B,int& print_switch,
  ivector& nrows, ivector& ncols)
{
  int ii=0;

  reset(W,B,y,num_levels,num_nodes); // Put the y vector into the model
				     // parameters

  int num_learn;

  dvector correct_response(1,num_nodes[num_levels]);

  ifstream infile("learning.smp");
  infile >> num_learn;
  dvariable z;
  z=0.0;

  if (print_switch ==0)
  {
    for (int k=1;k<= num_learn; k++)
    {
      infile >> x[1];
      if (!infile)
      {
	cerr << "Error reading x[1] from file learning.smp\n";
	exit(1);
      }
      infile >> correct_response;
      if (!infile)
      {
	cerr << "Error reading correct_response from file learning.smp\n";
	exit(1);
      }
      for (int i=1;i<num_levels; i++)
      {
	x[i+1]=Phi(W[i]*x[i]+B[i+1]);
      }
      dvar_vector vdiff=correct_response-x[num_levels];
      z+=vdiff*vdiff;
    }
  }
  else
  {
    ofstream outfile("fitrep.out");
    for (int k=1;k<=num_learn; k++)
    {
      infile >> x[1];
      infile >> correct_response;

      for (int i=1;i<num_levels; i++)
      {
	x[i+1]=Phi(W[i]*x[i]+B[i+1]);
      }

      double diff;
      // determine if the neural net got this one right
      diff=max(fabs(correct_response-value(x[num_levels])));
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
	   x[num_levels][kk] << "  ";

      }
      outfile << "\n";
      dvar_vector vdiff=correct_response-x[num_levels];
      z+=vdiff*vdiff;
    }
  }

  // Add the penalty terms
  dvariable v;
  v=norm(W);
  z+=.01*v*v;

  v=norm(B);
  z+=.01*v*v;

  if (print_switch==1)
  {
    ofstream outfile1("est.par");
    outfile1 << W << "\n\n";
    if (!outfile1)
    {
      cerr << "ERROR writing weights to file est.par\n"; exit(1);
    }
    outfile1 << B;
    if (!outfile1)
    {
      cerr << "ERROR writing bias terms to file est.par\n"; exit(1);
    }
  }
  return value(z);
}

