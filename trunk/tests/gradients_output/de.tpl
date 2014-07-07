DATA_SECTION
  init_int n
  init_matrix data(1,n,1,2)
  vector x
  vector Y
  vector xs
  vector Ys
  vector xends(1,2)
  number a
  number b
  number minx
  number maxx
  number maxY
 LOC_CALCS
  // we assume x's are in increasing order
  x=column(data,1);
  Y=column(data,2);
  int i;
  for (i=1;i<n;i++)
  {
    if (x(i) > x(i+1))
    {
      cerr << "Error x's shouldbe in incereasing order" << endl;
      ad_exit(1);
    }
  }

  double xmin=min(x);
  double xmax=max(x);
  a=1.0/(xmax-xmin);
  b=-xmin/(xmax-xmin);
  xs=a*x+b;
  maxY=max(Y);
  //xs=x;
  //Ys=Y;
  Ys=Y/maxY;
  xends(1)=xs(1);
  xends(2)=xs(n);
PARAMETER_SECTION
  init_vector Yends(1,2,2)   // Yends(1) is Y1	Yends(2) is Yn
  init_bounded_vector log_C(1,2,-5.0,4.0)   // C(i)>0
  init_matrix MM(1,2,1,3)  // C(i)>0
  init_bounded_matrix NN(1,2,1,3,-1.0,1.0)  // C(i)>0
  sdreport_vector B(1,2)   // 0 < B(1) < B(2)
  sdreport_vector A(1,2)   // 0 < B(1) < B(2)
  sdreport_vector Atilde(1,2)	// 0 < B(1) < B(2)
  sdreport_vector Btilde(1,2)	// 0 < B(1) < B(2)
  objective_function_value f
  sdreport_vector predYs(1,n)
 LOC_CALCS
  Yends(1)=Ys(1);
  Yends(2)=Ys(n);

PROCEDURE_SECTION

  B(1)=exp(log_C(1));
  B(2)=B(1)+exp(log_C(2));

  dvar_matrix M(1,2,1,2);
   cout << "B"<< endl << B << endl;
   cout << "xends"<< endl << xends << endl;

  int i,j;
  for (int i=1;i<=2;i++)
    for (int j=1;j<=2;j++)
      M(i,j) = exp(-B(i)*xends(j));

   cout << "M"<< endl << M << endl;
  /*
      Y1 = exp(-B1*xs1)*A1 +exp(-B2*xs1)*A2
      Yn = exp(-B1*xsn)*A1 +exp(-B2*xsn)*A2
  i.e.
      Y = M * A

   where   M =	exp(-B1*xs1) exp(-B2*xs1)
		exp(-B1*xsn) exp(-B2*xsn)
  so
   A=solve(M,Yends);
  */

   A=solve(M,Yends);
   cout << A << endl;
   predYs=A(1)*exp(-B(1)*xs)+A(2)*exp(-B(2)*xs);

   //predYs=A(1)*exp(-B(1)*(a*x+b))+A(2)*exp(-B(2)*(a*x+b));

   dvar_vector r2=square(predYs-Ys);
   dvariable vhat=sum(r2)/n;
   f+=0.5*n*(log(vhat));
   for (i=1;i<=2;i++)
     if (A(i)<0.001)
       f+=10000.*square(A(i)-.001);
   Atilde=maxY*elem_prod(A,exp(-b*B));
   Btilde=a*B;
   for (i=1;i<=2;i++)
     if (Atilde(i)<0.001)
       f+=10000.*square(Atilde(i)-.001);
   //Atilde=maxY*A;
   //Btilde=B;
   f+=norm2(MM);
   f+=norm2(NN);

REPORT_SECTION

   report << "predYs" << endl  << predYs  << endl;
   report << setprecision(12) << f << endl;
   report << "A" << endl;
   report << A << endl;
   report << "B" << endl;
   report << B << endl;
   report << "User space parameters" << endl;
   report << "Atilde" << endl;
   report << Atilde << endl;
   report << "Btilde" << endl;
   report << Btilde << endl;

   int nvar=initial_params::nvarcalc();
   // for now use fake g
   dvector g(1,nvar);
   g.fill_seqadd(100.,1.0);
   initial_params::save_all(report,6,g);

GLOBALS_SECTION
  #include "admodel.h"
  void add_slave_suffix(const adstring& s){}

