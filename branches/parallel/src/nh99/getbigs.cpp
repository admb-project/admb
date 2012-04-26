/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#endif
#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::get_bigS(int ndvar,int nvar1,int nvar,
  dmatrix& S,dmatrix& BS,dvector& scale)
{ 
  dmatrix tv(1,ndvar,1,nvar1);
  adstring tmpstring="admodel.dep";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".dep";
  cifstream cif((char*)tmpstring);

  int tmp_nvar,tmp_ndvar;
  cif >> tmp_nvar >> tmp_ndvar;
  if (tmp_nvar!=nvar1)
  {
    cerr << " tmp_nvar != nvar1 in file " << tmpstring
           << endl;
    ad_exit(1);
  }


#if defined(USE_LAPLACE)

    int us=nvar1-nvar;
    int xsize,usize;
    dmatrix minv(1,us,1,us);
    dmatrix Dux(1,us,1,nvar);
    dmatrix uhat_prime(1,us,1,nvar);
    uhat_prime.initialize();
    int Bnvar=nvar+us;
    // get l_uu and l_xu for covariance calculations
    if (lapprox->hesstype !=2)
    {
      tmpstring = ad_comm::adprogram_name + ".luu";
      uistream ifs1((char*)(tmpstring));
      ifs1 >> usize >> xsize;
      if (!ifs1)
      {
        cerr << "Error reading from file " << tmpstring << endl;
        ad_exit(1);
      }
      // check xsize and usize
      if (xsize !=nvar ||usize !=us)
      {
        cerr << "size error in file " << tmpstring << endl;
        ad_exit(1);
      }
      ifs1 >> minv;
      ifs1 >> Dux;
      if (!ifs1)
      {
        cerr << "Error reading from file " << tmpstring << endl;
        ad_exit(1);
      }
      uhat_prime=minv*Dux;
    }
    else
    {
      if (nvar !=lapprox->xsize)
      {
        cerr << "error in sizes in mod_sd" << endl;
        ad_exit(1);
      }
      if (us !=lapprox->usize)
      {
        cerr << "error in sizes in mod_sd" << endl;
        ad_exit(1);
      }
      xsize=lapprox->xsize;
      usize=lapprox->usize;
      // calculate uhat_prime from the block diagnal matrix
      d3_array & H=*(lapprox->block_diagonal_hessian); 
      d3_array & Dux=*(lapprox->block_diagonal_Dux);
      int mmin=H.indexmin();
      int mmax=H.indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (allocated(H(i)))
        {
          dmatrix tmp=inv(H(i))*Dux(i);
          int rmin=H(i).indexmin();
          int rmax=H(i).indexmax();
          int tmpmin=Dux(i).indexmin();
          int cmin=Dux(i,tmpmin).indexmin();
          int cmax=Dux(i,tmpmin).indexmax();
          
          for (int j=rmin;j<=rmax;j++)
          {
            for (int k=cmin;k<=cmax;k++)
            {
              int i1=(*lapprox->block_diagonal_re_list)(i,j)-nvar;
              uhat_prime(i1,(*lapprox->block_diagonal_fe_list)(i,k))=
                tmp(j,k);
            }
          }
        }
      }
      #if defined(USE_ADMPI)
      if (ad_comm::mpi_manager)
      {
        int umin=uhat_prime.indexmin();
        int umax=uhat_prime.indexmax();
        if (ad_comm::mpi_manager->is_master())
        {
          for (int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
          {
            for (int i=umin;i<=umax;i++)
            {
              uhat_prime(i)+=ad_comm::mpi_manager->get_dvector_from_slave(si);
            }
          }
        }
        else
        {
          for (int i=umin;i<=umax;i++)
          {
            ad_comm::mpi_manager->send_dvector_to_master(uhat_prime(i));
          }
        }
      }
      #endif
      // rescale uhat_prime to be der wrt x
      int master_only=1;
      #if defined(USE_ADMPI)  
      if (ad_comm::mpi_manager)
      {
        if (ad_comm::mpi_manager->is_slave())
        {
          master_only=0;
        }
      }
      #endif

      if (master_only)
      {
        int rmin=uhat_prime.indexmin();
        int rmax=uhat_prime.indexmax();
        int cmin=uhat_prime(rmin).indexmin();
        int cmax=uhat_prime(rmin).indexmax();
        for (int i=rmin;i<=rmax;i++)
        {
          for (int j=cmin;j<=cmax;j++)
          {
            uhat_prime(i,j)*=scale(j);
          }
        }
      }
    }
    dmatrix Sux=uhat_prime*S;
    dmatrix Suu=Sux*trans(uhat_prime);
    if (lapprox->hesstype !=2)
    {
      if (lapprox->saddlepointflag==2)
      {
        Suu-=minv;
      }
      else
      {
        Suu+=minv;
      }
    }
    else
    {
      //send Suu to slaves
      #if defined(USE_ADMPI)
      if (ad_comm::mpi_manager)
      {
        int Suumin=Suu.indexmin();
        int Suumax=Suu.indexmax();
        if (ad_comm::mpi_manager->is_master())
        {
          for (int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
          {
            for (int i=Suumin;i<=Suumax;i++)
            {
              ad_comm::mpi_manager->send_dvector_to_slave(Suu(i),si);
            }
          }
        }
        else
        {
          for (int i=Suumin;i<=Suumax;i++)
          {
            Suu(i)=ad_comm::mpi_manager->get_dvector_from_master();
          }
        }
      }
      #endif

      d3_array & H=*(lapprox->block_diagonal_hessian); 
      int mmin=H.indexmin();
      int mmax=H.indexmax();
      //send mmin mmax
      #if defined(USE_ADMPI)
      if (ad_comm::mpi_manager)
      {
        if (ad_comm::mpi_manager->is_slave())
        {
          ad_comm::mpi_manager->send_int_to_master(mmin);
          ad_comm::mpi_manager->send_int_to_master(mmax);
        }
      }
      #endif

      for (int i=mmin;i<=mmax;i++)
      {
        int allocate_flag=allocated(H(i));
        //send allocate_flag
        #if defined(USE_ADMPI)
        if (ad_comm::mpi_manager)
        {
          if (ad_comm::mpi_manager->is_slave())
          {
              ad_comm::mpi_manager->send_int_to_master(allocate_flag);
          }
        }
        #endif

        if (allocate_flag)
        {
          dmatrix tmp=inv(H(i));
          int rmin=H(i).indexmin();
          int rmax=H(i).indexmax();
          //send rmin rmax allocate flag
          #if defined(USE_ADMPI)
          if (ad_comm::mpi_manager)
          {
            if (ad_comm::mpi_manager->is_slave())
            {
              ad_comm::mpi_manager->send_int_to_master(rmin);
              ad_comm::mpi_manager->send_int_to_master(rmax);
            }
          }
          #endif

          for (int j=rmin;j<=rmax;j++)
          {
            for (int k=rmin;k<=rmax;k++)
            {
              int j1=(*lapprox->block_diagonal_re_list)(i,j)-nvar;
              int k1=(*lapprox->block_diagonal_re_list)(i,k)-nvar;
              if (lapprox->saddlepointflag==2)
              {
                Suu(j1,k1)-=tmp(j,k);
              }
              else
              {
                Suu(j1,k1)+=tmp(j,k);
              }
              //send j1,k1,Suu(j1,k1)
              #if defined(USE_ADMPI)
              if (ad_comm::mpi_manager)
              {
                if (ad_comm::mpi_manager->is_slave())
                {
                  ad_comm::mpi_manager->send_int_to_master(j1);
                  ad_comm::mpi_manager->send_int_to_master(k1);
                  ad_comm::mpi_manager->send_double_to_master(Suu(j1,k1));
                }
              }
              #endif
            }
          }
        }
      }
      // send Suu to master

      #if defined(USE_ADMPI)
      if (ad_comm::mpi_manager)
      {
        if (ad_comm::mpi_manager->is_master())
        {
          for (int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
          {
            //get mmin mmax
            int mmmin,mmmax;
            ad_comm::mpi_manager->get_int_from_slave(mmmin,si);
            ad_comm::mpi_manager->get_int_from_slave(mmmax,si);

            for (int i=mmmin;i<=mmmax;i++)
            {
              //get allocate_flag
              int allocate_flag;
              ad_comm::mpi_manager->get_int_from_slave(allocate_flag,si);
              if (allocate_flag)
              {
                //get rmin rmax
                int rmin,rmax;
                ad_comm::mpi_manager->get_int_from_slave(rmin,si);
                ad_comm::mpi_manager->get_int_from_slave(rmax,si);
          
                for (int j=rmin;j<=rmax;j++)
                {
                  for (int k=rmin;k<=rmax;k++)
                  {
                    //get ji k1 Suu(j1,k1)
                    int j1,k1;
                    ad_comm::mpi_manager->get_int_from_slave(j1,si);
                    ad_comm::mpi_manager->get_int_from_slave(k1,si);
                    Suu(j1,k1)=ad_comm::mpi_manager->get_double_from_slave(si);
                  }
                }
              }
            }

          } //end for
        }
      }
      #endif
    }
    minv.deallocate();
    BS.initialize();
    // random effects are never bounded?
    scale(xsize+1,Bnvar)=1.0;

    int master_only=1;
    #if defined(USE_ADMPI)  
    if (ad_comm::mpi_manager)
    {
      if (ad_comm::mpi_manager->is_slave())
      {
        master_only=0;
      }
    }
    #endif

    if (master_only)
    {
      int i;

      for (i=1;i<=xsize;i++)
      {
        for (int j=1;j<=xsize;j++)
        {
          BS(i,j)=S(i,j);
        }
      }
   
      for (i=xsize+1;i<=Bnvar;i++)
      {
        for (int j=1;j<=xsize;j++)
        {
          BS(i,j)=Sux(i-xsize,j);
          BS(j,i)=BS(i,j);
        }
      }
    
      for (i=xsize+1;i<=Bnvar;i++)
      {
        for (int j=xsize+1;j<=Bnvar;j++)
        {
          BS(i,j)=Suu(i-xsize,j-xsize);
        }
      }

    } //end master_only
#   endif


 // 
 //   int us=nvar1-nvar;
 //   int xsize,usize;
 //   // get l_uu and l_xu for covariance calculations
 //   tmpstring = ad_comm::adprogram_name + ".luu";
 //   uistream ifs1((char*)(tmpstring));
 //   ifs1 >> usize >> xsize;
 //   if (!ifs1)
 //   {
 //     cerr << "Error reading from file " << tmpstring << endl;
 //     ad_exit(1);
 //   }
 //   // check xsize and usize
 //   if (xsize !=nvar ||usize !=us)
 //   {
 //     cerr << "size error in file " << tmpstring << endl;
 //     ad_exit(1);
 //   }
 //   dmatrix minv(1,usize,1,usize);
 //   dmatrix Dux(1,usize,1,xsize);
 //   int Bnvar=xsize+usize;
 //   ifs1 >> minv;
 //   ifs1 >> Dux;
 //   if (!ifs1)
 //   {
 //     cerr << "Error reading from file " << tmpstring << endl;
 //     ad_exit(1);
 //   }
 //   dmatrix S(1,nvar,1,nvar);
 //   read_covariance_matrix(S,nvar);
 //   dmatrix uhat_prime=minv*Dux;
 //   dmatrix Sux=uhat_prime*S;
 //   dmatrix Suu=Sux*trans(uhat_prime);
 //   Suu+=minv;
 //   //Suu=minv;
 //   minv.deallocate();
 //   BS.initialize();
 //   // random effects are never bounded?
 // 
 //   int i;
 // 
 //   for (i=1;i<=xsize;i++)
 //   {
 //     for (int j=1;j<=xsize;j++)
 //     {
 //       BS(i,j)=S(i,j);
 //     }
 //   }
 //  
 //   for (i=xsize+1;i<=Bnvar;i++)
 //   {
 //     for (int j=1;j<=xsize;j++)
 //     {
 //       BS(i,j)=Sux(i-xsize,j);
 //       BS(j,i)=BS(i,j);
 //     }
 //   }
 //   
 //   for (i=xsize+1;i<=Bnvar;i++)
 //   {
 //     for (int j=xsize+1;j<=Bnvar;j++)
 //     {
 //       BS(i,j)=Suu(i-xsize,j-xsize);
 //     }
 //   }
}
