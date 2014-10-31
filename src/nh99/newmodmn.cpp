/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

double polint(double * xa,double * ya,double x);

void get_confidence_interval(const dvector& left_bd, const dvector& right_bd,
  dmatrix& ms, const dvector& xs, const dvector& siglevel,
  const int& level_index, int index);
void get_onesided_intervals(const dvector& left_bd, const dvector& right_bd,
  dmatrix& ms, const dvector& xs, const dvector& siglevel,
  const int& level_index, int index);
void report_confidence_limits(const ofstream& ofs3,int numsig_levels,
  const dvector& siglevel, const dvector& left_bd, const dvector& right_bd);
void report_onesided_confidence_limits(const ofstream& ofs3,int numsig_levels,
  const dvector& siglevel, const dvector& left_bd, const dvector& right_bd,
  int ip);

void report_confidence_limits(const ofstream& _ofs3,int numsig_levels,
  const dvector& siglevel, const dvector& left_bd, const dvector& right_bd)
{
  ofstream& ofs3=(ofstream&) _ofs3;
  ofs3 << "Minimum width confidence limits:" << endl
       <<                    " significance level  lower bound"
       << "  upper bound" << endl;
  for (int i=1;i<=numsig_levels;i++)
  {
    ofs3 << "                 " << setw(12) << siglevel(i)
         << "             " << left_bd(i) << "     " << right_bd(i) << endl;
  }
  ofs3 << endl;
}

void report_onesided_confidence_limits(const ofstream& _ofs3,int numsig_levels,
  const dvector& siglevel, const dvector& left_bd, const dvector& right_bd,
  int ip)
{
  ofstream& ofs3=(ofstream&) _ofs3;
  int i;
  for (i=1;i<=numsig_levels;i++)
  {
    ofs3 << "The probability is " << setw(7) << siglevel(i) << " that "
         << likeprof_params::likeprofptr[ip]->label()
         << " is greater than " << left_bd(i) << endl;
  }
  ofs3 << endl;
  for (i=1;i<=numsig_levels;i++)
  {
    ofs3 << "The probability is " << setw(7) << siglevel(i) << " that "
         << likeprof_params::likeprofptr[ip]->label()
         << " is less than " << right_bd(i) << endl;
  }
  ofs3 << endl;
}

  dvector smooth(const dvector& v);

#ifndef CURVE_CORRECT
  void function_minimizer::normalize_posterior_distribution(double udet,
    const dvector& siglevel, const ofstream& _ofs2,int num_pp,
    const dvector& _all_values, const dmatrix& actual_value,double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet, const dmatrix& xdist,
    const dmatrix& penalties)
  /*
  void function_minimizer::normalize_posterior_distribution(double udet,
    dvector& siglevel, const ofstream& ofs2,int num_pp, const dvector& all_values,
    dmatrix& actual_value,double global_min,int offset, const dmatrix& lprof,
    dmatrix& ldet, const dmatrix& xdist, const dmatrix& penalties)
   */
   // dmatrix& ldet, const dmatrix& xdist, const dmatrix& penalties,
   // const dmatrix& lg_jacob)
#else

  void function_minimizer::normalize_posterior_distribution(double udet,
    const dvector& siglevel, const ofstream& ofs2,int num_pp,
    const dvector& all_values, const dmatrix& actual_value,
    double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet,
    const dmatrix& xdist,
    const d3_array& eigenvals,d3_array& curvcor)
/*
  void function_minimizer::normalize_posterior_distribution(double udet,
    const dvector& siglevel, const ofstream& ofs2,int num_pp,
    const dvector& all_values,
    const dmatrix& actual_value,double global_min,int offset,
    const dmatrix& lprof,
    const dmatrix& ldet, const dmatrix& xdist,
    const d3_array& eigenvals,d3_array& curvcor)
*/
#endif
  {
    dvector& all_values=(dvector&) _all_values;
    ofstream& ofs2=(ofstream&) _ofs2;
    ofstream savef("diags");
    //ofstream ofs3((char*) (ad_comm::adprogram_name + ".plt") );
    //dvector siglevel("{.90,.95,.975}");
#ifndef CURVE_CORRECT
    dmatrix left_bd(1,3,1,3);
    dmatrix right_bd(1,3,1,3);
    dmatrix lower_bd(1,3,1,3);
    dmatrix upper_bd(1,3,1,3);
#else
    dmatrix left_bd(0,3,1,3);
    dmatrix right_bd(0,3,1,3);
    dmatrix lower_bd(0,3,1,3);
    dmatrix upper_bd(0,3,1,3);
#endif
    double sigma;
    /*int nvar=*/initial_params::nvarcalc();
    int numsig_levels=siglevel.indexmax();
    for (int ip=0;ip<likeprof_params::num_likeprof_params;ip++)
    {
     {
      adstring profrep_name=(likeprof_params::likeprofptr[ip]->label());
      size_t llen = length(profrep_name);
      if (llen>8) profrep_name=profrep_name(1,8);
      ofstream ofs3((char*) (profrep_name+adstring(".plt")));
      sigma=likeprof_params::likeprofptr[ip]->get_sigma();
      //double diff;
      ofs2 << likeprof_params::likeprofptr[ip]->label() << ":" << endl;
      ofs3 << likeprof_params::likeprofptr[ip]->label() << ":" << endl;
      ofs2 << sigma << endl  << global_min << " " << udet << endl;
      dvector tempint0(-num_pp,num_pp);
      dvector tempint1(-num_pp,num_pp);
      dvector tempint2(-num_pp,num_pp);
      {
        ofstream ofs("dgs2");
        ofs << "lprof" << endl << lprof << endl;
      }
      int j;
      for (j=-num_pp;j<=num_pp;j++) //go in positive and negative directions
      {
        all_values(j)=actual_value(ip,j-offset);
        double lp=lprof(ip,j);
      #if defined(DO_PROFILE)
        tempint0(j)= exp(global_min-lp+.5*(-ldet(ip,j)+ldet(ip,0)));
      #endif
        tempint1(j)= exp(global_min-lp);

        tempint2(j)=
          square((actual_value(ip,j)-actual_value(ip,-offset))/
            (1.414*sigma));
        tempint2(j)=exp(-tempint2(j));
      }
      dmatrix m(1,3,-num_pp,num_pp);
      for (j=-num_pp;j<=num_pp;j++)
      {
      #if defined(DO_PROFILE)
        m(1,j)=tempint0(j)/xdist(ip,j);
      #endif
        if (xdist(ip,j)<1.e-50)
        {
          cerr << " xdist(" << ip << "," << j << ") too small" << endl;
          char ch;
          cin >> ch;
          m(2,j)=1.e+20;
        }
        else
        {
          // profile likelihood adjusted for gradient of dep var
          m(2,j)=tempint1(j)/xdist(ip,j);
        }
        //m(2,j)=tempint1(j);
      }
      //m(2,num_pp)=tempint1(num_pp)/xdist(ip,num_pp);
      m(3)=tempint2; //+ 1.e-4*max(tempint2);

     /*
      savef << "penalties" << endl << setw(9) << setprecision(4)
            << penalties(ip) << endl;
      savef << "normalized exp(lg_jacob)" << endl << setw(9) << setprecision(4)
            << exp(2.*(lg_jacob(ip)-lg_jacob(ip,0))) << endl;
     */
      savef << "tempint1 " << endl << setw(9) << setprecision(3)
            << tempint1 << endl;
     #if defined(DO_PROFILE)
      savef << "m(1) " << endl << setw(9) << setprecision(3) << m(1) << endl;
     #endif
      savef << "m(2) " << endl << setw(9) << setprecision(3) << m(2) << endl;
      savef << "m(3) " << endl << setw(9) << setprecision(3) << m(3) << endl;
      savef << "xdistance" << endl;
      savef << xdist(ip) << endl << endl;

      int min_ind = -num_pp;
      int max_ind = num_pp;

      dvector xs(7*min_ind,7*max_ind);
      dmatrix ms(1,3,7*min_ind,7*max_ind);

      int kmult=7;
      for (int k=min_ind;k<=max_ind;k++)
      {
        double val=all_values(k);
        xs(kmult*k)=val;
        if (k<max_ind)
        {
          double diff=all_values(k+1)-all_values(k);
          for (int i=1;i<kmult;i++)
          {
            xs(kmult*k+i)=val+i/double(kmult)*diff;
          }
        }
      }
      {
        int mmin=m.rowmin();
        int mmax=m.rowmax();
        for (int i=mmin;i<=mmax;i++)
        {
          int cmin=m(i).indexmin();
          int cmax=m(i).indexmax();
          for (int j=cmin;j<=cmax;j++)
          {
            if (m(i,j)<=0.0) m(i,j)=1.e-50;
          }
        }
      }
      //dmatrix lm=log(m);
      dmatrix lm=m;
      int lowlimit=2;
      #if defined(DO_PROFILE)
        lowlimit=1;
      #else
        lowlimit=2;
      #endif

      for (int ii=lowlimit;ii<=3;ii++)
      {
        int k;
        for (k=min_ind;k<=0;k++)
        {
          //double * xa=(&all_values(k))-1;
          //double * ya=(&lm(ii,k))-1;
          //ms(ii,kmult*k)=exp(lm(ii,k));
          ms(ii,kmult*k)=lm(ii,k);
          if (k<max_ind)
          {
            double l=lm(ii,k);
            double u=lm(ii,k+1);
            for (int i=1;i<kmult;i++)
            {
              ms(ii,kmult*k+i)=l+double(i)/kmult*(u-l);
              //ms(ii,kmult*k+i)=polint(xa,ya,xs(k*kmult+i));
            }
          }
        }

        for (k=1;k<=max_ind;k++)
        {
          //double * xa=(&all_values(k))-2;
          //double * ya=(&lm(ii,k))-2;
          //ms(ii,kmult*k)=exp(lm(ii,k));
          ms(ii,kmult*k)=lm(ii,k);
          if (k<max_ind)
          {
            double l=lm(ii,k);
            double u=lm(ii,k+1);
            for (int i=1;i<kmult;i++)
            {
              ms(ii,kmult*k+i)=l+double(i)/kmult*(u-l);
            }
          }
        }
      }

    /*
      savef << "ms(2) " << endl << setw(9) << setprecision(3) << ms(2) << endl;
      savef << "ms(3) " << endl << setw(9) << setprecision(3) << ms(3) << endl;
    */

      dvector ssum(1,3);
      ssum.initialize();
      for (j=lowlimit;j<=3;j++)
      {
        for (int i=7*min_ind;i<7*max_ind;i++)
        {
          if (ms(j,i)<0.0)
          {
            ms(j,i)=0.0;
          }
          else
          {
            ssum(j)+=ms(j,i)*(xs(i+1)-xs(i));
          }
        }
      }
      for (j=lowlimit;j<=3;j++)
      {
        if (ssum(j) !=0)
        {
        /*
          cout << ms(j) << endl << ssum(j) << endl << endl;
          char ch;
          cin >> ch;
        */
          ms(j)/=ssum(j);
        }
      }
      // now do the integrals
      for (j=lowlimit;j<=3;j++)
      {
        int level_index=1;
        do
        {
          get_confidence_interval(left_bd(j),right_bd(j),ms,xs,
            siglevel,level_index,j);
          get_onesided_intervals(lower_bd(j),upper_bd(j),ms,xs,
            siglevel,level_index,j);
          level_index++;
        }
        while (level_index <= numsig_levels);
      }

      double min_cutoff = 1.e-3/sigma;
      int i;
      for (i=7*min_ind;i<=0;i++)
      {
        if (max(ms(2,i),ms(3,i)) > min_cutoff) break;
      }
      int new_min_ind = int(max(i,7*min_ind));
      for (i=0;i<=7*max_ind;i++)
      {
        if (max(ms(2,i),ms(3,i)) < min_cutoff) break;
      }
      int new_max_ind = min(i,7*max_ind);
      dmatrix output(1,2,new_min_ind,new_max_ind);

      output(1)=xs(new_min_ind,new_max_ind);

    #if defined(DO_PROFILE)
      output(2)=ms(1)(new_min_ind,new_max_ind);
      {
        ofs3 << "Adjusted Profile likelihood" << endl;
        ofs3 << trans(output) << endl;
        report_confidence_limits(ofs3,numsig_levels,siglevel,left_bd(1),
          right_bd(1));
        ofs3 << "One sided confidence limits for the "
                "adjusted profile likelihood:" << endl << endl;
        report_onesided_confidence_limits(ofs3,numsig_levels,siglevel,
          lower_bd(1),upper_bd(1),ip);
      }
     #endif

      output(2)=ms(2)(new_min_ind,new_max_ind);
      {
        ofs3 << "Profile likelihood" << endl;
        ofs3 << trans(output) << endl;
        report_confidence_limits(ofs3,numsig_levels,siglevel,left_bd(2),
          right_bd(2));
        ofs3 << "One sided confidence limits for the "
                "profile likelihood:" << endl << endl;
        report_onesided_confidence_limits(ofs3,numsig_levels,siglevel,
          lower_bd(2),upper_bd(2),ip);
      }

      output(2)=ms(3)(new_min_ind,new_max_ind);
      {
        ofs3 << "Normal approximation" << endl;
        ofs3 << trans(output) << endl;
        report_confidence_limits(ofs3,numsig_levels,siglevel,left_bd(3),
          right_bd(3));
        ofs3 << "One sided confidence limits for the "
                "Normal approximation:" << endl << endl;
        report_onesided_confidence_limits(ofs3,numsig_levels,siglevel,
          lower_bd(3),upper_bd(3),ip);
      }
     }
    }
  }


  dvector smooth(const dvector& v)
  {
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    int diff=mmax-mmin+1;
    dvector tmp(mmin,mmax);
    tmp(mmin)=.8*v(mmin)+.2*v(mmin+1);
    tmp(mmin+1)=.2*v(mmin)+.6*v(mmin+1)+.2*v(mmin+2);
    int i;
    for (i=mmin+2;i<=mmin+diff/4;i++)
    {
      tmp(i)=.1*v(i-2)+.2*v(i-1)+.4*v(i)+.2*v(i+1)+.1*v(i+2);
    }
    for (i=mmin+diff/4+1;i<mmax-diff/4;i++)
    {
      tmp(i)=v(i);
    }
    for (i=mmax-diff/4;i<=mmax-2;i++)
    {
      tmp(i)=.1*v(i-2)+.2*v(i-1)+.4*v(i)+.2*v(i+1)+.1*v(i+2);
    }
    tmp(mmax)=.8*v(mmax)+.2*v(mmax-1);
    tmp(mmax-1)=.2*v(mmax)+.6*v(mmax-1)+.2*v(mmax-2);
    return tmp;
  }

double polint(double * xa,double * ya,double x)
{
  double prod1=(xa[1]-xa[2])*(xa[1]-xa[3]);
  double prod2=(xa[2]-xa[1])*(xa[2]-xa[3]);
  double prod3=(xa[3]-xa[1])*(xa[3]-xa[2]);
  if (prod1==0)
  {
    double y=ya[1];
    return y;
  }
  if (prod2==0)
  {
    double y=ya[2];
    return y;
  }
  if (prod3==0)
  {
    double y=ya[2];
    return y;
  }
  double y= (x-xa[2])*(x-xa[3])/prod1*ya[1]
           +(x-xa[1])*(x-xa[3])/prod2*ya[2]
           +(x-xa[1])*(x-xa[2])/prod3*ya[3];
  return y;
}
