/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

#  if defined(USE_SHARE_FLAGS)
/*
  static int integer(const index_type& it)
  {
    return it.integer();
  }
*/

  int param_init_d3array::shared_size_count(void)
  {
    if (share_flags->get_current_phase() != current_phase)
    {
      share_flags->get_inv_matrix_shared(current_phase);
    }
    i3_array & bmap = share_flags->get_bmap();
    int  mmin=bmap.indexmin();
    int  mmax=bmap.indexmax();
    int nv=0;
    for (int i=mmin;i<=mmax;i++)
    {
      nv+=::size_count((*this)(bmap(i,1,1),bmap(i,1,2)));
    }
    return nv;
  }

  void param_init_d3array::shared_set_value_inv
    (const dvector& _x,const int& _ii)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvector,x)
    index_type& it=*(share_flags->get_invflags());
    //int mmin=share_flags->invflags->indexmin();
    //int mmax=share_flags->invflags->indexmax();
    int mmin=it.indexmin();
    int mmax=it.indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      int k1=it(i)(1).integer();
      int k2=it(i)(2).integer();
      const dvar_vector & v=(*this)(k1,k2);
      int kmin=v.indexmin();
      int kmax=v.indexmax();
      for (int k=kmin;k<=kmax;k++)
      {
        x(ii++)=::value(v(k));
      }
    }
  }

  void param_init_d3array::shared_set_value(const dvar_vector& _x,
    const int& _ii,const dvariable& pen)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvar_vector,x)
    i3_array & bmap = share_flags->get_bmap();
    int  mmin=bmap.indexmin();
    int  mmax=bmap.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      int  jmin=bmap(i).indexmin();
      int  jmax=bmap(i).indexmax();

      int ii1 = 0;
      for (int j=jmin;j<=jmax;j++)
      {
        dvar_vector& v=(*this)(bmap(i,j,1),bmap(i,j,2));

        int kmin=v.indexmin();
        int kmax=v.indexmax();

        ii1=ii;
        for (int k=kmin;k<=kmax;k++)
        {
          v(k)=x(ii1++);
        }
      }
      ii=ii1;
    }
  }

  void param_init_d3array::setshare
    (const index_type& sf,const index_type& af)
  {
    share_flags = new shareinfo(sf,af);
    int idim1= share_flags->get_shareflags()->dimension();
    share_flags->get_dimension()=idim1;
    int idim2= share_flags->get_activeflags()->dimension();
    switch (idim1)
    {
    case 1:
      share_flags->get_inv_vector_shared(current_phase);
      break;
    case 2:
      {
        cout << idim1 << " " << idim2 << endl;
         // check rationality
        int mmin1= share_flags->get_shareflags()->indexmin();
        int mmax1= share_flags->get_shareflags()->indexmax();
        int mmin2= share_flags->get_activeflags()->indexmin();
        int mmax2= share_flags->get_activeflags()->indexmax();
        int mmin=indexmin();
        int mmax=indexmax();
        if (mmin1 != mmin || mmax1 != mmax ||
          mmin2 != mmin || mmax2 != mmax)
        {
          cerr << "sanity error" << endl;
          ad_exit(1);
        }
        share_flags->get_inv_matrix_shared(current_phase);
      }
      break;
    default:
      cerr << "Error" << endl;
      ad_exit(1);
    }
  }
#  endif
