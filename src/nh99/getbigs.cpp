/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#  include <df1b2fun.h>
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

  int tmp_nvar = 0, tmp_ndvar = 0;
  cif >> tmp_nvar >> tmp_ndvar;
  if (tmp_nvar!=nvar1)
  {
    cerr << " tmp_nvar != nvar1 in file " << tmpstring
           << endl;
    ad_exit(1);
  }

    int us=nvar1-nvar;
    int xsize = 0;
    dmatrix minv(1,us,1,us);
    dmatrix uhat_prime(1,us,1,nvar);
    uhat_prime.initialize();
    int Bnvar=nvar+us;
    // get l_uu and l_xu for covariance calculations
    if (lapprox->hesstype !=2)
    {
      dmatrix Dux(1,us,1,nvar);
      int usize = 0;
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
      uhat_prime=-minv*Dux;
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
      // calculate uhat_prime from the block diagnal matrix
      d3_array & H=*(lapprox->block_diagonal_hessian);
      d3_array & Dux=*(lapprox->block_diagonal_Dux);
      int mmin=H.indexmin();
      int mmax=H.indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (allocated(H(i)))
        {
          dmatrix tmp=-inv(H(i))*Dux(i);
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
      // rescale uhat_prime to be der wrt x
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
      d3_array & H=*(lapprox->block_diagonal_hessian);
      int mmin=H.indexmin();
      int mmax=H.indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (allocated(H(i)))
        {
          dmatrix tmp=inv(H(i));
          int rmin=H(i).indexmin();
          int rmax=H(i).indexmax();

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
            }
          }
        }
      }
    }
    minv.deallocate();
    BS.initialize();
    // random effects are never bounded?
    scale(xsize+1,Bnvar)=1.0;

    for (int i=1;i<=xsize;i++)
    {
      for (int j=1;j<=xsize;j++)
      {
        BS(i,j)=S(i,j);
      }
    }

    for (int i=xsize+1;i<=Bnvar;i++)
    {
      for (int j=1;j<=xsize;j++)
      {
        BS(i,j)=Sux(i-xsize,j);
        BS(j,i)=BS(i,j);
      }
    }

    for (int i=xsize+1;i<=Bnvar;i++)
    {
      for (int j=xsize+1;j<=Bnvar;j++)
      {
        BS(i,j)=Suu(i-xsize,j-xsize);
      }
    }
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
