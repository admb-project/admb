extern "C" {
#include <pvm3.h>
}
#include <admodel.h>
#include <adpvm.h>
#if !defined(linux)
#  include <windows.h>
#endif
#define  __declspec(dllexport) 

extern int ad_constant_flag;

main(int argc,char * argv[])
{
  gradient_structure gs(25000000);
  time_t now;
  char name[12], buf[60];
  int ptid;

  load_adpvm_library();
  pvm_setopt(PvmRoute, PvmRouteDirect);
  
  d3_array C;
  int m;
  // ***************  begin receive block ***********************************
   ad_constant_flag=1;
   ptid=pvm_parent();
   adpvm_recv(ptid,-1);
   pvm_unpack(m);  // see if derivatives are
   cout << "m = " << m << endl;
   pvm_unpack(C); 
     adpvm_end_receive();
   ad_constant_flag=0;
  // ***************  end receive block ***********************************
  do
  {
    dvar_vector x;

    // ***************  begin receive block ***********************************
   ptid=pvm_parent();
     adpvm_recv(ptid,-1);
     pvm_unpack(gradient_structure::no_derivatives);  // see if derivatives are
     pvm_unpack(x);  // see if derivatives are
     adpvm_end_receive();
    // ***************  end receive block ***********************************
  
     int nmin=C.indexmin();
     int nmax=C.indexmax();
     dvar_matrix M(1,m,1,m);
     dvar_matrix N(1,m,1,m);
     N.initialize();

     dvariable f0=0.0;
     for (int i=nmin;i<=nmax;i++)
     {
       M=C(i);
       for (int j=1;j<=m;j++)
       {
         M(j,j)+=x(i);
       }
       N+=inv(M);
     }
  
    // ***************  begin send block ***********************************
   ptid=pvm_parent();
    double dd=1.345;
    cout << " starting send " << endl;
    pvm_initsend(PvmDataDefault);/* allocate message buffer */	
    pvm_pack(dd);
    pvm_pack(N);
    adpvm_send(ptid, 2);/* send buffer to master */
    cout << " finished send " << endl;
    // ***************  end send block ***********************************

    cout << "starting slave gradcalc " << endl;
    slave_gradcalc();
    cout << "finished slave gradcalc " << endl;
  }
  while(1);
}

