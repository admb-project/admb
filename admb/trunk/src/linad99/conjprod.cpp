/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 */

// this is to get UNIX systems to use getchar
// #define UNIXKLUDGE

//#define DIAG
#ifndef __GNUDOS__
  #include <conio.h>
#else
  #include <unistd.h>
#endif

#include <fvar.hpp>
extern int ctlc_flag;

#ifdef __TURBOC__
#pragma hdrstop
#include <conio.h>
#include <iomanip.h>
#endif

#include <ctype.h>
#include <string.h>

//#define CUBIC_INTERPOLATION

#if defined (__WAT32__) || defined (__MSVC32__)
#include <conio.h>
#endif

#ifdef __ZTC__
#include <conio.h>
#include <iomanip.hpp>
#include <disp.h>

  // preprocessor defines and function definitions that emulate Borland
  // text screen managment functions using the Zortech disp_ package
  // note the order of includes is important - this stuff should come
  // after stdio.h, disp.h and anything that might also include these

//#define if (ad_printf) (*ad_printf) disp_if (ad_printf) (*ad_printf)

  void gotoxy(int x, int y);
  void clrscr();

  struct text_info
  {
    unsigned char  winleft,   wintop;
    unsigned char  winright,  winbottom;
  //unsigned char  attribute, normattr;
    unsigned char  currmode;
    unsigned char  screenheight;
    unsigned char  screenwidth;
    unsigned char  curx, cury;
  };

  void gettextinfo(struct text_info *r);
#endif

#if defined(UNIXKLUDGE) || \
  ((defined(__SUN__) || defined(__GNU__)) && !defined(__GNUDOS__))
#include <iostream.h>
#include <signal.h>
#define getch getchar
  void clrscr(void); // { if (ad_printf) (*ad_printf)("\n"); }
  #if defined(__HP__) || defined(linux)
  extern "C" void onintr(int k);
  #else
  extern "C" int onintr(int* k);
  #endif
#endif



#ifdef __NDPX__

#include <iostream.hxx>
  extern "C" {
#include <grex.h>
    void clrscr();
  };

  void gotoxy(int x, int y);

  struct text_info
  {
    unsigned char  winleft,   wintop;
    unsigned char  winright,  winbottom;
  //unsigned char  attribute, normattr;
  //unsigned char  currmode;
    unsigned char  screenheight;
    unsigned char  screenwidth;
    unsigned char  curx, cury;
  };

  void gettextinfo(struct text_info *r);
#endif


class fmmc;


double do_interpolate( BOR_CONST double& fret,BOR_CONST double& left_bracket,
  double& left_bracket_value, BOR_CONST dvector& left_bracket_gradient,
  double& right_bracket, BOR_CONST double& right_bracket_value,
  dvector& right_bracket_gradient, BOR_CONST dvector& theta, BOR_CONST dvector& d, BOR_CONST int& J,
  long int& ifn, BOR_CONST double& crit1,
  int& int_flag,BOR_CONST double& rho_1, BOR_CONST double& Psi_2, BOR_CONST dvector& g1);

void do_extrapolate( BOR_CONST double& left_bracket, BOR_CONST double& left_bracket_value,
  dvector& left_bracket_gradient, BOR_CONST double& right_bracket,
  double& right_bracket_value, BOR_CONST dvector& right_bracket_gradient, BOR_CONST dvector& theta,
  dvector& d, BOR_CONST int& J, BOR_CONST double& rho_0,long int& ifn,BOR_CONST int& ifnex,
  int& ext_flag,BOR_CONST double& rho_1, BOR_CONST double& rf, BOR_CONST dvector& g1);

double mylinmin( BOR_CONST double& fret, BOR_CONST double& Phi_i, BOR_CONST dvector& theta1, BOR_CONST dvector& q_i,
  fmmc& cs);

void  bracket_report( BOR_CONST dvector& theta, BOR_CONST double& left_bracket,
  double& right_bracket, BOR_CONST dvector& d);

double cubic_interpolation( BOR_CONST double& u, BOR_CONST double& v, BOR_CONST double& a, BOR_CONST double& b,
  double& ap, BOR_CONST double& bp);


double Phi( BOR_CONST dvector&);
double min( BOR_CONST double&, BOR_CONST double&);
double max( BOR_CONST double&, BOR_CONST double&);

#include <math.h>

#define ITMAX 5000
#define EPS 1.0e-10
#define FREEALL free_vector(xi,1,n);free_vector(h,1,n);free_vector(g,1,n);


void fmmc::fmin( BOR_CONST double& fret,BOR_CONST dvector& p,BOR_CONST dvector& gg)
{
  dfn=0.0;;
  maxfn_flag=0;
  iexit=0;
  ihflag=0;
#ifdef __ZTC__
    if (disp_inited == 0)
    {
       disp_open();
       disp_usebios();
    }
#endif
  int n=p.size();
  dvector& xi=*(this->xi);
  dvector& h=*(this->h);
  dvector& g=*(this->g);
  double& fp=this->fp;
  //int& its=this->its;
  int& J=this->J;
  if (this->frp_flag > 0) this->ifn++;

  if (ireturn >= 3)
  {
    {
      derch(fret, p , gg, n, ireturn);
    }
    return;
  }

  if (this->frp_flag>1)
  {
    if (fret < fbest)
    {
#ifdef DIAG
        cerr << " Improving fbest  old fbest = " << fbest << "\n" <<
                "                  new fbest = " << fret << "\n";
#endif

      int con_flag;
      for (int jj=gg.indexmin();jj<=gg.indexmax();jj++)
      {
        con_flag=1;
        if (fabs(gg(jj)) > crit)
        {
          con_flag=0;
          break;
        }
      }

      if ( con_flag==1)
      {
        this->ireturn=-1;
        {
	  if (iprint>0)
          {
            if (ad_printf) (*ad_printf)("Gradient magnitude criterion satisfied\n");
            if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
              n, iter, ifn);
            if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
               fret, max(fabs(gg)) );
            fmmdisp(p, gg, n, this->scroll_flag); //fmc);
          }
        }
        return;
      }
      fbest=fret;
      *xbest=p;
      *gbest=gg;
    }
  }



  if (this->frp_flag==1) goto label800;
  if (this->frp_flag==2) goto label2000;
  if (this->frp_flag==3) goto label3000;

#if defined(__SUN__) && !defined(__GNUDOS__) && !defined(__MSVC32__)
  #ifdef __HP__
  signal(SIGINT, &onintr);
  #else
  signal(SIGINT, (SIG_PF)&onintr);
  #endif
#endif
#if (defined(__GNU_) && !defined(__GNUDOS__)) || defined(UNIXKLUDGE)
  signal(SIGINT, &onintr);
#endif
  this->J=1;
  this->rho_min=1.e-10;
  this->converge_flag=0;

  this->frp_flag=1;
  this->ireturn=1;
  return;
label800:

  fbest=fret;
  *xbest=p;
  *gbest=gg;

  this->frp_flag=0;
  this->ireturn=0;
  xi=gg;
  this->fp=fret;
  //(*dfunc)(p,xi);

  if (iprint>0)
  {
    if (!(iter%iprint)&& (iprint > 0) )
    {
#     if !defined (__WAT32__) && !defined (__MSVC32__)
        if (!scroll_flag) clrscr();
#     endif
      if (ad_printf) (*ad_printf)("Initial statistics: ");
      if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
       n, iter, ifn);
      if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
       fbest, max(fabs(*gbest)) );
      fmmdisp(*xbest, *gbest, n, this->scroll_flag); //fmc);
    }
  }

  {
    for (int j=1;j<=n;j++)
    {
      g[j] = -xi[j];
      xi[j]=h[j]=g[j];
    }
  }

  this->ifnex=0;

  //this->its=1;

label1000:
    iter++;
  label5:
#if ((defined(__SUN__) || defined(__GNU__)) && !defined(__GNUDOS__)) || defined(UNIXKLUDGE)
    if (ctlc_flag)
#else
    if ( kbhit() )
#endif
    {
      int c = toupper(getch());
      if ( c == 'C')
      {
        ireturn = 3;
        {
          derch(fret, p , gg, n, ireturn);
        }
        return;
      }
      else
      {
        if ( c == 'Q' || c == 'N' )
        {
          quit_flag=c;
          this->ireturn=-1;
          {
	    if (iprint>0)
            {
              if (ad_printf) (*ad_printf)("User initiated interrupt\n");
              if (ad_printf) (*ad_printf)(" - final statistics:\n");
              if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
                n, iter, ifn);
              if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
                fbest, max(fabs(*gbest)) );
              fmmdisp(*xbest, *gbest, n, this->scroll_flag); //fmc);
            }
          }
          p=*xbest;
          gg=*gbest;
          return;
        }
        else
        {
          quit_flag=0;
        }
      }
    }
    {
      mylinmin(fret,fp,p,-1.*(g),*this);
    }
    if (this->lin_flag ==0) goto label10;

      p=*(this->extx);
      this->frp_flag=2;
      this->ireturn=1;
      return;


    label2000:
      this->ireturn=0;
      this->frp_flag=0;
      //this->extf=fcomp( *(this->extx),*(this->extg) );
      this->extf=fret;
      *(this->extx)=p;
      *(this->extg)=gg;
      goto label5;
  label10:

    {
      for ( int i=1; i<=9; i++)
      {
        (*funval)[i]= (*funval)[i+1];
      }
    }

    (*funval)[10] = fret;

    if ( iter>15 && fabs( (*funval)[1]-(*funval)[10])< min_improve )
    {
      ihang = 1;
      this->ireturn=-1;
      {
	if (iprint>0)
        {
          if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
            n, iter, ifn);
          if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
             fbest, max(fabs(*gbest)) );
          fmmdisp(*xbest, *gbest, n, this->scroll_flag); //fmc);
        }
      }
      p=*xbest;
      gg=*gbest;
      return;
    }


  /*  Moved this up to entry point
    {
      int con_flag;
      for (int jj=gg.indexmin();jj<=gg.indexmax();jj++)
      {
        con_flag=1;
        if (fabs(g(jj)) > crit)
        {
          con_flag=0;
          break;
        }
      }

      if ( con_flag==1)
      {
        this->ireturn=-1;
        {
	  if (iprint>0)
          {
            if (ad_printf) (*ad_printf)("Gradient magnitude criterion satisfied\n");
            if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
              n, iter, ifn);
            if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
             fbest, max(fabs(*gbest)) );
            fmmdisp(*xbest, *gbest, n, this->scroll_flag); //fmc);
          }
        }
        p= *xbest;
        gg= *gbest;
        return;
      }
    }
 */


    if ( ifn > maxfn )
    {
      {
	if (iprint>0)
        {
          if (ad_printf) (*ad_printf)("Maximum number of function evaluations exceeded\n");
          if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
            n, iter, ifn);
          if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
             fbest, max(fabs(*gbest)) );
          fmmdisp(*xbest, *gbest, n, this->scroll_flag); //fmc);
        }
      }
      p=*xbest;
      gg=*gbest;
      this->ireturn=-1;
      return;
    }

    if (iprint>0)
    {
      if (!(iter%iprint)&&(iprint>0))
      {
	{
#     if !defined (__WAT32__) && !defined (__MSVC32__)
            if (!scroll_flag) clrscr();
#         endif
	  if (ad_printf) (*ad_printf)("Intermediate statistics: ");
	}
	if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
	 n, iter, ifn);
	if (ad_printf) (*ad_printf)("Function value %le; maximum gradient component mag %le\n",
	     fbest, max(fabs(*gbest)) );
	  fmmdisp(*xbest, *gbest, n, this->scroll_flag); //fmc);
      }
    }

    this->frp_flag=3;
    this->ireturn=1;
    // return;
  label3000:
    this->frp_flag=0;
    this->ireturn=0;
    xi=gg;
    this->fp=fret;

    //fp=fcomp(p,xi);

    this->dgg=this->gg=0.0;
    {
      for (int j=1;j<=n;j++)
      {
        this->gg += g[j]*g[j];
/*      dgg += xi[j]*xi[j];  */
        this->dgg += (xi[j]+g[j])*xi[j];
      }
    }
    if (this->gg == 0.0)
    {
      this->ireturn=-1;
      return;
    }
    this->gam=this->dgg/this->gg;
    {
      for (int j=1;j<=n;j++)
      {
        g[j] = -xi[j]; // g seems to hold the negative gradient
        xi[j]=h[j]=g[j]+this->gam*h[j];
      }
    }
//  if (this->iter <= ITMAX) goto label1000;
    goto label1000;

  cerr << "Too many iterations in FRPRMN\n";
}

#undef ITMAX
#undef EPS
#undef FREEALL


// version of mylinmin which uses the deviative to help
// bracket the minimum

double mylinmin( BOR_CONST double& fret, BOR_CONST double& Phi_i, BOR_CONST dvector& theta1, BOR_CONST dvector& q_i,
  fmmc& cs)

{
  // d is the current direction for the 1 dimensional search
  // q_i is the gradient at the current best point

  dvector& theta= *(cs.theta);
  if (cs.lin_flag==1)goto label1;
  if (cs.lin_flag==2)goto label2;
  if (cs.lin_flag==3)goto label3;
  {
    *(cs.theta) = theta1;
    *(cs.d)=*(cs.xi);
    cs.rho_0=pow(2.,-cs.J)/norm(q_i);
    cs.gamma=q_i* *(cs.d);
    cs.lin_flag=1;
    *(cs.extx)=theta+cs.rho_0* *(cs.d);
  }
  return 0;
label1:
  {
    cs.lin_flag=0;
    cs.Psi_0=cs.extf;
    *(cs.g2)=*(cs.extg);

    //double rho_star=gamma*rho_0*rho_0/(2*(gamma*rho_0+Phi_i-Psi_0));

    cs.ext_flag=0;
    cs.int_flag=0;
    cs.dir_deriv=*(cs.d)* *(cs.g2);
    cs.left_bracket_value=Phi_i;
    *(cs.left_bracket_gradient)=q_i;
    cs.left_bracket=0;
  }


  //cout << "Check " << cs.Psi_0 << " " << Phi_i << "  " << cs.dir_deriv << "\n";

  if (!(cs.Psi_0 < Phi_i && cs.dir_deriv < 0)) goto label555;
  // Extrapolate to get a right bracket

    label100:
    {
#ifdef DIAG
        cerr << "doing extrapolation\n";
#endif
      do_extrapolate(cs.left_bracket,cs.left_bracket_value,
        *(cs.left_bracket_gradient), cs.right_bracket,
        cs.right_bracket_value,*(cs.right_bracket_gradient),theta,
        *(cs.d),cs.J,cs.rho_0,cs.ifn,cs.ifnex,cs.ext_flag,cs.rho_1,
	cs.Psi_1,*(cs.grad) );

    }
    if (cs.ext_flag==0)
    {
      goto label120;
    }
    else
    {
      {
       cs.lin_flag=2;
       *(cs.extx)=theta+cs.rho_1* *(cs.d);
       //extx=theta+rho_1*d;
      }
      return 0;
    label2:
      cs.lin_flag=0;
      //Psi_1=fcomp(theta+rho_1*d,grad);
      cs.Psi_1=cs.extf;
      *(cs.grad)= *(cs.extg);
    }
    goto label100;

  //label120:
  //  int itemp=1;

label555:
  //else
  // We have a bracket
  {
#ifdef DIAG
        cerr << "We have a right bracket\n";
#endif
     cs.right_bracket=cs.rho_0;
     cs.right_bracket_value=cs.Psi_0;
     *(cs.right_bracket_gradient)=*(cs.g2);
  }
 label120:
  // cout << "After extrapolation\n";
  bracket_report(theta,cs.left_bracket,cs.right_bracket,*(cs.d));

  // We have a bracket [theta,theta+rho_0*d] so interpolate
  {
  label1100:
   {
    //cout << "Intrap\n";
    cs.rho_i=do_interpolate(fret,cs.left_bracket,cs.left_bracket_value,
      *(cs.left_bracket_gradient),cs.right_bracket,cs.right_bracket_value,
      *(cs.right_bracket_gradient),theta,*(cs.d),cs.J,cs.ifn,cs.crit1,
      cs.int_flag,cs.rho_1,cs.Psi_1,*(cs.grad) );
   }
    if (cs.int_flag==0)
    {
      goto label1120;
    }
    else
    {
     {
      cs.lin_flag=3;
      *(cs.extx)=theta+cs.rho_1* *(cs.d) ;
     }
      return 0;
    label3:
      cs.lin_flag=0;
      //Psi_1=fcomp(theta+rho_1*d,grad);
      cs.Psi_1=cs.extf;
      *(cs.grad)=*(cs.extg);
    }
    goto label1100;

  label1120:
    int itemp=1;;

  }
  theta=theta+cs.rho_i* *(cs.d) ;
  return cs.converge_flag;
}

double do_interpolate( BOR_CONST double& fret, BOR_CONST double& left_bracket,
  double& left_bracket_value, BOR_CONST dvector& left_bracket_gradient,
  double& right_bracket, BOR_CONST double& right_bracket_value,
  dvector& right_bracket_gradient, BOR_CONST dvector& theta, BOR_CONST dvector& d, BOR_CONST int& _J,
  long int& ifn, BOR_CONST double& crit1,
  int& int_flag,BOR_CONST double& rho_1, BOR_CONST double& Psi_2, BOR_CONST dvector& g1)
{
  double rho_min=1.e-10;
  int& J = (int&) _J;
  static double rho_star;
  static double dir_deriv;
  //double Psi_2;
  //dvector g1(1,d.size());
  static double gamma;
  static double gamma1;
  static double rho_0;
  if (int_flag ==1) goto label200;
  J+=1;
label120:
  // do
  //{
    gamma=left_bracket_gradient*d;
#ifdef CUBIC_INTERPOLATION
      gamma1=right_bracket_gradient*d;
#endif
    rho_0=right_bracket-left_bracket;


#ifdef DIAG
      cout << "f'(x) " << gamma  << "   "
         << "f'(y) " << gamma1 << endl;

      cout << "f(x)  " << left_bracket_value  << "   "
         << "f(y)  " << right_bracket_value << endl;

      cout << "x     " << left_bracket  << "   "
         << "y     " << right_bracket << endl;
#endif

    if (gamma==0.0)
    {
      rho_star=0.;
    }
    else
    {
#ifdef CUBIC_INTERPOLATION
        rho_star=cubic_interpolation(left_bracket,right_bracket,
          left_bracket_value,right_bracket_value,gamma,gamma1);
#else
        double step=gamma*rho_0*rho_0/
          (2*(gamma*rho_0+left_bracket_value-right_bracket_value));
         // rho_star=left_bracket+gamma*rho_0*rho_0/
	 //(2*(gamma*rho_0+left_bracket_value-right_bracket_value));
         double width=right_bracket-left_bracket;
         if (step<.25*width)step=.25*width;
         if (step>.75*width)step=.75*width;
         rho_star=left_bracket+step;

#endif
    }

    if (rho_star < left_bracket )
    {
      cout << " rho_star out of range ..value changed\n";
    }

    if (rho_star > right_bracket)
    {
      cout << " rho_star out of range ..value changed\n";
      rho_star=.001*left_bracket+.999*right_bracket;
    }

    if (rho_star <= rho_min)
    {
      return rho_min;
    }
    int_flag=1;
    rho_1=rho_star;
    return rho_min;
label200:
    int_flag=0;
    rho_1=rho_star;
    //Psi_2=fcomp(theta+rho_star*d,g1);
    //J+=1;

    dir_deriv=d*g1;

    //cout << "Check2 " << Psi_2 << " " << left_bracket_value << "  " <<
    //   d*g1 << "\n";

    if (Psi_2 < left_bracket_value && (d*g1) < 0)
    {

#ifdef DIAG
        cout << " Before interpolation -- new left side\n";
        bracket_report( theta,left_bracket,right_bracket,d);
#endif

      left_bracket =rho_star;
      left_bracket_value=Psi_2;
      left_bracket_gradient=g1;

#ifdef DIAG
        cout << " After interpolation -- new left side\n";
        bracket_report( theta,left_bracket,right_bracket,d);
#endif
    }
    else
    {

#ifdef DIAG
        cout << " Before interpolation -- new right side\n";
        bracket_report( theta,left_bracket,right_bracket,d);
#endif
      right_bracket =rho_star;
      right_bracket_value=Psi_2;
      right_bracket_gradient=g1;


#ifdef DIAG
        cout << " After interpolation -- new right side\n";
        bracket_report( theta,left_bracket,right_bracket,d);
#endif
    }

  //while (dir_deriv > crit1
  //   && (right_bracket-left_bracket)> 1.e-10);

   double cos_theta=d*g1/(norm(d)*norm(g1));
#ifdef DIAG
     cerr << " The cosine of angle between the search direction and \n"
       " the gradient is " << cos_theta << "\n";
#endif

  if (cos_theta > crit1
     && (right_bracket-left_bracket)> 1.e-10)
  {
    if (cos_theta > .05)
    {
      J+=1;
    }
    goto label120;
  }

  if (cos_theta < -crit1 && (right_bracket-left_bracket)> 1.e-10)
  {
    goto label120;
  }

#ifdef DIAG
     if (cos_theta < crit1)
     {
      cerr << " Leaving interpolation routine because"
        " the cosine of angle between the \n search direction and "
       " the gradient is < crit1 = " << crit1  << "\n";
     }
#endif


  fret=Psi_2;
  return rho_star;
}


void do_extrapolate( BOR_CONST double& left_bracket, BOR_CONST double& left_bracket_value,
  dvector& left_bracket_gradient, BOR_CONST double& right_bracket,
  double& right_bracket_value, BOR_CONST dvector& right_bracket_gradient, BOR_CONST dvector& theta,
  dvector& d, BOR_CONST int& J, BOR_CONST double& rho_0,long int& ifn,BOR_CONST int& ifnex,
  int& ext_flag,BOR_CONST double& rho_1, BOR_CONST double& rf, BOR_CONST dvector& g1)
{
  if (ext_flag==1) goto label1500;
  J=J/2;
  rho_1=4.*rho_0;
  //dvector g1(1,d.size());
#ifndef __NDPX__
  double Psi_1;
#endif
label1000:
    ext_flag=1;
    return;
label1500:
#ifdef __NDPX__
  double Psi_1;
#endif
    ext_flag=0;
    //Psi_1=fcomp(theta+rho_1*d,g1);
    Psi_1=rf;
    ifnex++;
    if (Psi_1 >= left_bracket_value || d*g1 >0) goto label2000;
    left_bracket_value=Psi_1;
    left_bracket_gradient=g1;
    left_bracket=rho_1;
    rho_1=4*rho_1;
    goto label1000;
label2000:

  right_bracket=rho_1;
  right_bracket_value=Psi_1;
  right_bracket_gradient=g1;
}

void  bracket_report( BOR_CONST dvector& theta, BOR_CONST double& left_bracket,
  double& right_bracket, BOR_CONST dvector& d)
{
  double f=0;
  double fp1=0;
  double fp2=0;
  dvector g(1,d.size());
  dvector u(1,d.size());
  ivector ii(1,3);
  int one=1;
  ii.fill_seqadd(one,one);

#ifdef DIAG
    cout << "lb " <<  setprecision(4) << setw(12) << left_bracket
      << "rb " << setprecision(4) << setw(12)  << right_bracket
      << setprecision(4) << setw(12) << theta(ii) <<"\n";
#endif
}


double cubic_interpolation( BOR_CONST double& u, BOR_CONST double& v, BOR_CONST double& aa, BOR_CONST double& bb,
  double& ap, BOR_CONST double& bp)
{
  //cout <<"Begin cube\n";
  dmatrix M(1,4,1,4);

  M(1,1)=1;M(2,1)=0;M(3,1)=1;M(4,1)=0; // First column

  M(1,2)=u;M(2,2)=1;M(3,2)=v;M(4,2)=1; // Second column

  for (int i=3;i<=4;i++)
  {
    M(1,i)=u*M(1,i-1);
    M(2,i)=(i-1)*M(1,i-1);
    M(3,i)=v*M(3,i-1);
    M(4,i)=(i-1)*M(3,i-1);
  }

  dvector d(1,4);
  d(1)=aa;
  d(2)=ap;
  d(3)=bb;
  d(4)=bp;

  dvector e = inv(M)*d;
  double a,b,c;

  a=3*e(4);
  b=2*e(3);
  c=e(2);

  double q;
  if (a !=0)
  {
    if (b>0)
    {
      double y=b*b-4*a*c;
      if (y<0) return (u+v)/2.;
      q=-.5*(b+sqrt(y));
    }
    else
    {
      double y=b*b-4*a*c;
      if (y<0) return (u+v)/2.;
      q=-.5*(b-sqrt(b*b-4*a*c));
    }
    double x1,x2;
    x1=q/a;       // x1 and x2 are the two roots of the quadratic
    x2=c/q;       // equation that is the max andmin of the cubic
                  // polynomial
    double sgn1,sgn2;
    sgn1=b+2*a*x1;
    sgn2=b+2*a*x2;
    if (sgn1>0)
    {
      return x1;
    }
    else
    {
      return x2;
    }
  }
  else
  {
    // coeffcient of the quadratic term = 0
    return -c/b;
  }
    //cout <<"end cube\n";
}

#undef CUBIC_INTERPOLATION

fmmc::fmmc(BOR_CONST int& n)
{
  ctlc_flag = 0;
  maxfn=500;
  lin_flag=0;
  ext_flag=0;
  int_flag=0;
  ifnex=0;
  frp_flag=0;
  quit_flag=0;
  #ifdef __ZTC__
    scroll_flag=0;
  #else
    scroll_flag=1;
  #endif
  crit=1.e-4;
  crit1=1.e-2;
  min_improve=1.e-6;
  ireturn=0;
  iprint=1;
  imax=30;
  ihang=0;
  iter=0;
  ifn=0;
  left_bracket_gradient=new dvector(1,n);
  right_bracket_gradient=new dvector(1,n);
  funval=new dvector(1,10);
  g=new dvector(1,n);
  h=new dvector(1,n);
  xi=new dvector(1,n);
  d=new dvector(1,n);
  extx=new dvector(1,n);
  g2=new dvector(1,n);
  grad=new dvector(1,n);
  extg=new dvector(1,n);
  theta=new dvector(1,n);
  xbest=new dvector(1,n);
  gbest=new dvector(1,n);
}

fmmc::~fmmc(void)
{
  delete left_bracket_gradient;
  delete right_bracket_gradient;
  delete funval;
  delete g;
  delete h;
  delete xi;
  delete d;
  delete extx;
  delete g2;
  delete grad;
  delete extg;
  delete theta;
  delete xbest;
  delete gbest;
}


void derch(BOR_CONST double& f,BOR_CONST dvector& _x,BOR_CONST dvector& _gg,int n,BOR_CONST int & _ireturn)
{
  int& ireturn=(int&) _ireturn;
  dvector& x = (dvector&) _x;
  dvector& gg = (dvector&) _gg;
  static long int i, n1 ,n2;
  static double fsave;
  static double s, f1, f2, g2, xsave;
  static long int j = 1;
  static int si;
  si=gg.indexmax();
  static dvector g(1,si);

  if (ireturn == 4 ) goto label4;
  else if (ireturn == 5) goto label5;
  g=gg;
  while (j > 0)
  {
    //cout << "\nEntering derivative checker.\n";
    cout << "\n Enter index (1 ... "<< n <<") of derivative to check.";
    cout << "  To check all derivatives, enter 0: ";
    cin >> j;
    if (j <= 0)
    {
      cout << "\n   Checking all derivatives. Press X to terminate checking.\n";
      n1 = 1;
      n2 = n;
    }
    else
    {
      n1 = j;
      n2 = j;
    }
    cout << "   Enter step size (to quit derivative checker, enter 0): ";
    cin >> s;
    cout << "\n       X           Function     Analytical     Finite Diff;  Index\n";

    if (s <= 0) ad_exit(0);

    for (i=n1; i<=n2; i++)
    {
      xsave=x(i);
      x(i)=xsave+s;
      fsave = f;
      ireturn = 4; // fgcomp(&f1,x,g1,n, params, vars);
      return;

    label4:
      f1 = f;
      x(i)=xsave-s;
      ireturn= 5; //fgcomp(&f2,x,g1,n, params, vars);
      return;

    label5:
      f2 = f;
      f = fsave;
      x(i)=xsave;
      g2=(f1-f2)/(2.*s);

      if (ad_printf) (*ad_printf)("  %12.5e  %12.5e  %12.5e  %12.5e ; %5d \n",
              x(i), f, g(i), g2, i);

    } // for loop
  } // while (j > 0)
//  ireturn = 2;
  ad_exit(0);
}

// #undef DIAG
