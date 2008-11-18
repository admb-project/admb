
#include <fvar.hpp>
#include <iomanip.h>

extern unsigned _stklen=20000;

struct neural_net_design
{
  unsigned int num_levels;
  unsigned int * num_nodes;
};

int nvar_calc(int& num_levels,ivector& num_nodes);

dvar_vector Phi(dvar_vector& v);

void yinit(dmatrix& B,independent_variables& y,int& num_levels,
  ivector& num_nodes);


//double neural_fit(dvar3_array& W1,dvar_vector& y, ivector& num_nodes,int & num_levels,
//  dvar_matrix& x,int& print_switch);

void reset(dvar_matrix& B,dvar_vector& y,int& num_levels,
  ivector& num_nodes);

double neural_fit(dvar_vector& y, ivector& num_nodes,int & num_levels,
  dvar_matrix& x,dvar_matrix B,int& print_switch,
  ivector& ,ivector&);

double neural_fit(dvar_vector& y);


main()
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
  //d3_array W(1,num_levels-1,1,nrows,1,ncols);

  ifstream infile1("weights.par");


  nvar=nvar_calc(num_levels,num_nodes);// calculate the number of
				       // parameters to be estimated
  independent_variables y(1,nvar);  //make the vector of independent variables

  infile1 >> y;
  if (!infile1){ cerr << "ERROR reading y\n"; exit(1);}

  fmm fmc(nvar); //declare the function minimizer control structure for
		  //the conjugate gradient function minimizer
  double f;
  dvector g(1,nvar);
  fmc.maxfn=1000;
  fmc.iprint=1;
  // gradient_structure gs;
  while (fmc.ireturn>=0)
  {
    fmc.fmin(f,y,g);
    if (fmc.ireturn>0)
    {
      gradient_structure gs;
      f=neural_fit(y,num_nodes,num_levels,x,B,0,nrows,ncols);
      //f=neural_fit(y,num_nodes,num_levels,x,0);
      //f=neural_fit(y);
      //  END_MINIMIZATION(nvar,g)       // macro to end the minimization loop
					// This is the code for the expanded
      gradcalc(nvar,g);
    }
  }
  //neural_fit(y,num_nodes,num_levels,x,W,B,1,nrows,ncols); // Call neural_fit one more time
					      // to get report
  {
    // Save the current estimates for the parameters
    ofstream outfile("out.par");

    if (!outfile)
    {
      cerr << " Error writing data to file out.par\n";
      exit(1);
    }
  }
}

void yinit(dmatrix& B,independent_variables& y,int& num_levels,
  ivector& num_nodes)
{
  int ii=1;

  int rmin=B.rowmin();
  int rmax=B.rowmax();
  for (int i=rmin; i<=rmax; i++)
  {
    int imin=B(i).indexmin();
    int imax=B(i).indexmax();
    for (int j=imin; j<=imax; j++)
    {
      y(ii++)=B(i,j);
    }
  }
}


void reset(dvar_matrix& B,dvar_vector& y,int& num_levels,
  ivector& num_nodes)
{
  int ii=1;

  int rmin=B.rowmin();
  int rmax=B.rowmax();
  for (int i=rmin; i<=rmax; i++)
  {
    int imin=B(i).indexmin();
    int imax=B(i).indexmax();
    for (int j=imin; j<=imax; j++)
    {
      B(i,j)=y(ii++);
    }
  }
}

int nvar_calc(int& num_levels,ivector& num_nodes)
{
  int nvar=0;
  for (int i=1; i<num_levels; i++)
  {
    nvar+=num_nodes[i]*num_nodes[i+1];
  }
  for (i=2;i<=num_levels;i++)
  {
    nvar+=num_nodes(i);
  }
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
    tmp(i)=0.63662*atan(v(i)); //0.63662 is 2/PI
    // tmp(i)=0.31831*atan(v(i))+0.5; // This maps into (0,1) instead of (-1,1)
  }
  RETURN_ARRAYS_DECREMENT();
  return(tmp);
}

double neural_fit(dvar_vector& y, ivector& num_nodes,
  int & num_levels,
  dvar_matrix& x,dvar_matrix B,int& print_switch,
  ivector& nrows, ivector& ncols)
{
  int ii=0;

  reset(B,y,num_levels,num_nodes); // Put the y vector into the model
				     // parameters

  int num_learn;

  dvector correct_response(1,num_nodes[num_levels]);

  ifstream infile("learning.smp");
  infile >> num_learn;
  dvariable z;
  //d3_array W(1,num_levels-1,1,nrows,1,ncols);

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

	dmatrix T(1,x(i+1).indexmax(),1,x(i).indexmax());
	for (int iii=T.rowmin();iii<=T.rowmax();iii++)
	{
	  T(iii).fill_randn(iii+100*i+1);
	}
	//x[i+1]=B[i+1];
	x[i+1]=T*x[i]+B[i+1];

      }
      dvariable u=norm(correct_response-x[num_levels]);
      z+=u*u;
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
	//x[i+1]=Phi(W[i]*x[i]+B[i+1]);
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

      dvariable u=norm(correct_response-x[num_levels]);
      z+=u*u;
    }
  }

  dvariable v;
  //v=norm(W);
  //z+=.01*v*v;

  v=norm(B);
  z+=.01*v*v;

  return value(z);
}


double neural_fit(dvar_vector& y, ivector& num_nodes,int & num_levels,
  dvar_matrix& x,int& print_switch)
{ return value(y*y); }

double neural_fit(dvar_vector& y)
{ return value(y*y); }
