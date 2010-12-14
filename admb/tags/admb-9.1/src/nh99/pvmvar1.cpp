/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>

#if defined(USE_ADPVM)


 int pvm_params::num_pvm_params=0;
 const int pvm_params::maxnum_pvm_params=50;
 pvm_params * pvm_params::varsptr[pvm_params::maxnum_pvm_params+1];
    
  void pvm_int::assign(const ivector& u)
  {
    if(ad_comm::pvm_manager)
    {
      int nsp=ad_comm::pvm_manager->num_slave_processes;
      if (u.indexmin() !=0 || u.indexmax() != nsp)
      {
        cerr << "Error in pvm_int::assign  validindex bounds must be 0 "
             << ad_comm::pvm_manager->num_slave_processes << endl;
        ad_exit(1);
      }
      if (allocated(v))
        v.deallocate();
      v.allocate(0,nsp);
      v=u;
      d=u(0);
    }
  }
  pvm_int::operator int() 
  { 
    return d;
  }
  pvm_number::operator double() { return d;}

  void pvm_number::assign(const dvector& u)
  {
    if(ad_comm::pvm_manager)
    {
      int nsp=ad_comm::pvm_manager->num_slave_processes;
      if (u.indexmin() !=0 || u.indexmax() != nsp)
      {
        cerr << "Error in pvm_number::assign  valid index bounds must be 0 "
             << ad_comm::pvm_manager->num_slave_processes << endl;
        ad_exit(1);
      }
      if (allocated(v))
        v.deallocate();
      v.allocate(0,nsp);
      v=u;
      d=u(0);
    }
  }

  void pvm_params::send_all_to_slaves(void)
  {
    for (int i=0;i<num_pvm_params;i++)
    { 
      varsptr[i]->send_to_slaves();
    }
  } 

  void pvm_params::get_all_from_master(void)
  {
    for (int i=0;i<num_pvm_params;i++)
    { 
      varsptr[i]->get_from_master();
    }
  }

  void pvm_params::allocate(const char * s)
  {
    add_to_list();
  }

  void pvm_params::allocate(void)
  {
    add_to_list();
  }

  void pvm_params::add_to_list(void)
  {
    if (num_pvm_params>=pvm_params::maxnum_pvm_params)
    {
      cerr << " This version of ADMB only supports "
           <<  pvm_params::num_pvm_params << " pvm parameter"
        " objects" << endl;
      ad_exit(1);
    }
    varsptr[num_pvm_params++]= this; // this is the list of 
                                         // fundamental objects
  }




void pvm_int::send_to_slaves(void)
{
  // *********  begin constant send block  *************
  int ii=1;
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      adpvm_pack(v(ii++));
      adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end constant send block  *************
}


void pvm_number::send_to_slaves(void)
{
  // *********  begin constant send block  *************
  int ii=1;
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      adpvm_pack(v(ii++));
      adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end constant send block  *************
}



void pvm_int::get_from_master(void)
{
  int x;
  int ptid=pvm_parent();
  // ***************  begin constant receive block *********************
  adpvm_slave_crecv(ptid);
  adpvm_unpack(x);  
  adpvm_slave_end_creceive();
  // ***************  end receive block ***********************************
  d=x;
}
  
void pvm_number::get_from_master(void)
{
  double x;
  int ptid=pvm_parent();
  // ***************  begin constant receive block *********************
  adpvm_slave_crecv(ptid);
  adpvm_unpack(x);  
  adpvm_slave_end_creceive();
  // ***************  end receive block ***********************************
  d=x;
}
  
#endif //  #if defined(USE_ADPVM)

