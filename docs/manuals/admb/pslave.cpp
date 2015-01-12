#include <adpvm2.h>

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
  // ***************  begin constant receive block ***********************************
   ptid=pvm_parent();
   pvm_recv(ptid,-1);
   pvm_unpack(m);  
   pvm_unpack(C); 
   pvm_end_receive();
  // ***************  end receive block ***********************************
  reset_gradient_stack();
  do
  {
    dvar_vector x;
    gradient_structure::no_derivatives=0;

    // ***************  begin receive block ***********************************
     ptid=pvm_parent();
     adpvm_recv(ptid,-1);
     adpvm_unpack(gradient_structure::no_derivatives);  // see if derivatives are
     adpvm_unpack(x);  // see if derivatives are
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
    cout << " starting send " << endl;
    adpvm_initsend(PvmDataDefault);/* allocate message buffer */	
    adpvm_pack(N);
    adpvm_send(ptid, 2);/* send buffer to master */
    cout << " finished send " << endl;
    // ***************  end send block ***********************************

    slave_gradcalc();
  }
  while(1);
}

