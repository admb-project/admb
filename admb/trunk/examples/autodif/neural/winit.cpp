#include <fvar.hpp>

int num_weights_calc(int& num_levels,ivector& num_nodes);

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{

  int num_levels;
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

  int iseed;
  double std_dev;
  cout << "\n\nEnter integer seed for the random number: ";
  cin >> iseed;
  cout << "\nEnter standard deviation\n"
          "  (a number in the range 0.5 to 1.5 seems to work well): ";
  cin >> std_dev;

  // fill W and B with normally distributed random numbers with mean 0
  // and standard deviations = std_dev
  for (i=1;i<num_levels;i++)
  {
    W(i).fill_randn(iseed+2*i);
    W(i)=std_dev*W(i);
  }
  B.fill_randn(iseed+1001);
  B=std_dev*B;

  ofstream outfile1("weights.par");
  outfile1 << W;
  if (!outfile1)
  {
     cerr << "ERROR writing weights to file weights.par\n"; exit(1);
  }
  outfile1 << B;
  if (!outfile1)
  { 
     cerr << "ERROR writing bias terms from file weights.par\n"; exit(1);
  }
  return 0;
}

