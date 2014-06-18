/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

extern "C"
{
  int kbhit(void) { return 0;}
}

int global_nvar=0;
class df1b2_gradlist;
//df1b2_gradlist * f1b2gradlist = NULL;

//int df1b2variable::noallocate=0;

//initial_df1b2params ** initial_df1b2params::varsptr
//  =new P_INITIAL_DF1B2PARAMS[1000];
//int initial_df1b2params::num_initial_df1b2params=0;         // array

//int initial_df1b2params::num_initial_df1b2params_sav=0;         // array
//initial_df1b2params ** initial_df1b2params::varsptr_sav=0;

//int initial_df1b2params::current_phase=0;

#if defined(__DERCHECK__)
int mydercheckercounter=0;
#endif

/**
 * Description not yet available.
 * \param
 */
void df1b2variable::save_adpool_pointer(void)
{
  if (adpool_stack_pointer> adpool_stack_size-1)
  {
    cerr << "overflow in save_adpool_pointer" << endl;
    ad_exit(1);
  }
  adpool_stack[adpool_stack_pointer]=pool;
  adpool_nvar_stack[adpool_stack_pointer++]=nvar;
}

/**
 * Description not yet available.
 * \param
 */
void df1b2variable::restore_adpool_pointer(void)
{
  if (adpool_stack_pointer<=0)
  {
    cerr << "underflow in save_adpool_pointer" << endl;
    ad_exit(1);
  }
  pool=adpool_stack[--adpool_stack_pointer];
  nvar=adpool_nvar_stack[adpool_stack_pointer];
}

/**
 * Description not yet available.
 * \param
 */
void initial_df1b2params::save_varsptr(void)
{
  initial_df1b2params::varsptr_sav=initial_df1b2params::varsptr;

  varsptr=new P_INITIAL_DF1B2PARAMS[1000];
  if (varsptr == 0)
  {
    cerr << "error allocating memory for "
      "initial_df1b2params::varsptr  " << endl;
    ad_exit(1);
  }

  num_initial_df1b2params_sav=num_initial_df1b2params;
  num_initial_df1b2params =0;
}

/**
 * Description not yet available.
 * \param
 */
void initial_df1b2params::restore_varsptr(void)
{
  if (num_initial_df1b2params == 0)
  {
    if (varsptr)
    {
      delete [] varsptr;
      varsptr=0;
    }
    varsptr=initial_df1b2params::varsptr_sav;
    varsptr_sav=0;

    num_initial_df1b2params= num_initial_df1b2params_sav;
    num_initial_df1b2params_sav=0;
  }
  else
  {
    if (num_initial_df1b2params+num_initial_df1b2params_sav
     > 1000)
    {
      cerr << "maximum numver of iitial_df1b2params is 1000 "
           << endl;
      ad_exit(1);
    }

    for (int i=0;i<num_initial_df1b2params_sav;i++)
    {
      varsptr[i+num_initial_df1b2params]=varsptr_sav[i];
    }
    num_initial_df1b2params+=num_initial_df1b2params_sav;
    delete varsptr_sav;
    varsptr_sav=0;
    num_initial_df1b2params_sav=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
initial_df1b2params::initial_df1b2params(void) : ind_index(0)
{
  scalefactor=0.0;
  phase_start=1;
  phase_save=1;
  add_to_list();
}

/*
static void stupid_xxx(int){;}
static void stupid_xxx(void *){;}
*/

typedef void (**ADprfptr)(void);
typedef void (*ADrfptr)(void);

/**
 * Description not yet available.
 * \param
 */
void df1b2_gradcalc1(void)
{
  //smartlist & list=f1b2gradlist->list;
  fixed_smartlist & nlist=f1b2gradlist->nlist;
  int ncount=f1b2gradlist->ncount;
  //ADrfptr rf2;
  int xcount=0;
  int tmpcount;
  int tcount=f1b2gradlist->ncount;

  //int check_pool_flag3=0;
  switch (df1b2variable::passnumber)
  {
  case 1:
    f1b2gradlist->list.save_end();
    f1b2gradlist->nlist.save_end();
  case 3:
#if defined(__DERCHECK__)
    //  derchecker->counter=f1b2gradlist->ncount;
    mydercheckercounter=f1b2gradlist->ncount;
#endif
    f1b2gradlist->list.set_reverse();
    f1b2gradlist->list.restore_end();
    f1b2gradlist->nlist.set_reverse();
    f1b2gradlist->nlist.restore_end();

    if (df1b2variable::passnumber==3)
    {
      f1b2gradlist->nlist3.save_end();
      f1b2gradlist->nlist3.set_reverse();
      f1b2gradlist->nlist3.restore_end();
      f1b2gradlist->list3.save_end();
      f1b2gradlist->list3.set_reverse();
      f1b2gradlist->list3.restore_end();
    }
    tmpcount=ncount;
    do
    {
      tmpcount--;
     /*
      if (!(tmpcount %100))
      {
        cout << "B " << tmpcount << endl;
      }
      if (tmpcount < 2)
      {
        cout << "B " << tmpcount << endl;
      }
      */
      //nlist-=sizeof(char*);
      --nlist;
      if (nlist.eof())
        break;
      ADrfptr rf=nlist.bptr->pf;
      (*rf)();
     /*
      if (check_pool_flag3)
      {
        if (xcount > 722)
        {
          cout << xcount << "  ";
          //check_pool_depths();
        }
      }
     */
#if defined(__DERCHECK__)
        //derchecker->counter--;
      mydercheckercounter--;
       // stupid_xxx(derchecker->counter);
#endif
        xcount++;
          tcount--;
       if (xcount > 99999999) cout << xcount << endl;
       //if (tcount == 6599 )
        //  cout << tcount << endl;
      /*
        if (initial_df1b2params::current_phase==2)
        {
          tcount--;
          if (rf2 != (nlist.buffer+122)->pf || xcount > 12488)
             cout << tcount << " " << xcount << " "
                  << (nlist.buffer+122)->pf << endl;
        }
       */
    }
    while(nlist.bptr>=nlist.buffer);
    break;
  case 2:
    {
      f1b2gradlist->list2.save_end();
      f1b2gradlist->list2.set_reverse();
      f1b2gradlist->list2.restore_end();
      f1b2gradlist->nlist2.save_end();
      f1b2gradlist->nlist2.set_reverse();
      f1b2gradlist->nlist2.restore_end();
#if defined(__DERCHECK__)
      // derchecker->counter=0;
      mydercheckercounter=0;
#endif
      f1b2gradlist->list.set_forward();
      f1b2gradlist->list.rewind();
      f1b2gradlist->nlist.set_forward();
      f1b2gradlist->nlist.rewind();

      //nlist.reset();  // set pointer to beginning of list
      --(f1b2gradlist->nlist2);  // backup one record
      int icount=0;
      do
      {
#if defined(__DERCHECK__)
        // derchecker->counter++;
        mydercheckercounter++;
#endif
        //ADrfptr rf=*ADprfptr(nlist.bptr);
        ADrfptr rf=nlist.bptr->pf;
        (*rf)();
        ++nlist;

       /*
        if (initial_df1b2params::current_phase==2)
        {
          if (icount >=4579)
          {
            cout << icount << endl;
          }
        }

        if (icount>28115)
        {
          cout << "icount = " << icount << endl;
        }
        */
      }
      while(++icount<ncount);
      // need this to get pointer right for step 3?
       // nlist-=sizeof(int); // set nlist to point to second record;
      //nlist++;

      break;
    }

  default:
     cerr << "illega value for df1b2variable::passnumber "
      " value = " << df1b2variable::passnumber << endl;
  }
}



double nsin(double x) {return -sin(x);}
double ncos(double x) {return -cos(x);}

double ADmult_add_fun(double x,double y);
df1b2function1 ADf1b2_sin(::sin,::cos,::nsin,::ncos,"sin");
df1b2function1 ADf1b2_cos(::cos,::nsin,::ncos,::sin);
df1b2function1 ADf1b2_exp(::exp,::exp,::exp,::exp,"exp");

/**
 * Description not yet available.
 * \param
 */
double AD_df1_atan(double x)
{
  return double(1.0)/(1+square(x));
}

/**
 * Description not yet available.
 * \param
 */
double AD_df2_atan(double x)
{
  return double(-2.0)*x/square(1+square(x));
}

/**
 * Description not yet available.
 * \param
 */
double AD_df1_tan(double x)
{
  return double(1.0)+square(tan(x));
}

/**
 * Description not yet available.
 * \param
 */
double AD_df2_tan(double x)
{
  double y=tan(x);
  return double(2.0)*y*(double(1.0)+square(y));
}

/**
 * Description not yet available.
 * \param
 */
double AD_df3_atan(double x)
{
  return double(-2.0)/square(double(1)+square(x))
         + double(12.0)*square(x)/cube(double(1)+square(x));
}

/**
 * Description not yet available.
 * \param
 */
double AD_df3_tan(double x)
{
  double y=square(tan(x));

  return double(2.0) * (double(1.0)+double(3.0)*y) * (double(1) + y);
}

df1b2function1 ADf1b2_tan(::tan,::AD_df1_tan,::AD_df2_tan ,::AD_df3_tan,"tan");

df1b2function1 ADf1b2_atan(::atan,::AD_df1_atan,::AD_df2_atan ,::AD_df3_atan,
  "atan");

/**
 * Description not yet available.
 * \param
 */
double AD_arg_inv(double x)
{
  return double(1.0)/x;
}

/**
 * Description not yet available.
 * \param
 */
double AD_minus_arg_inv2(double x)
{
  return double(-1.0)/(x*x);
}

/**
 * Description not yet available.
 * \param
 */
double AD_2arg_inv3(double x)
{
  return double(2.0)/(x*x*x);
}

/**
 * Description not yet available.
 * \param
 */
double AD_minus6_arg_inv4(double x)
{
  return double(-6.0)/(x*x*x*x);
}

df1b2function1 ADf1b2_inv(AD_arg_inv,AD_minus_arg_inv2,AD_2arg_inv3,
  AD_minus6_arg_inv4);

df1b2function1 ADf1b2_log(::log,AD_arg_inv,AD_minus_arg_inv2,AD_2arg_inv3);

/*
df1b2variable sin(const df1b2variable& x)
{
  return ADf1b2_sin(x);
}
*/

/**
 * Description not yet available.
 * \param
 */
df1b2variable atan(const df1b2variable& x)
{
  return ADf1b2_atan(x);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable tan(const df1b2variable& x)
{
  return ADf1b2_tan(x);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2variable::operator *= (const df1b2variable& v)
{
  return *this=*this*v;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2variable::operator /= (const df1b2variable& v)
{
  return *this=*this/v;
}


/*
df1b2variable cos(const df1b2variable& x)
{
  cout << "cos not implemented yet" << endl;
  ad_exit(1);
  return ADf1b2_sin(x);
}
*/

/**
 * Description not yet available.
 * \param
 */
df1b2variable exp(const df1b2variable& x)
{
  return ADf1b2_exp(x);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable mfexp(const df1b2variable& x)
{
  double b=60;
  if (value(x)<=b && value(x)>=-b)
  {
    return ADf1b2_exp(x);
  }
  else if (value(x)>b)
  {
    return exp(b)*(double(1.)+double(2.)*(x-b))/(double(1.)+x-b);
  }
  else
  {
    return exp(-b)*(double(1.)-x-b)/(double(1.)+double(2.)*(-x-b));
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable mfexp(const df1b2variable& x,double b)
{
  if (value(x)<=b && value(x)>=-b)
  {
    return ADf1b2_exp(x);
  }
  else if (value(x)>b)
  {
    return exp(b)*(double(1.)+double(2.)*(x-b))/(double(1.)+x-b);
  }
  else
  {
    return exp(-b)*(double(1.)-x-b)/(double(1.)+double(2.)*(-x-b));
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log(const df1b2variable& x)
{
  return ADf1b2_log(x);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable inv(const df1b2variable& x)
{
  return ADf1b2_inv(x);
}

/**
 * Description not yet available.
 * \param
 */
double ADproduct_fun(double x,double y)
{
  return x*y;
}

/**
 * Description not yet available.
 * \param
 */
double ADmult_add_fun(double x,double y)
{
  return x*y+x;
}

/**
 * Description not yet available.
 * \param
 */
double ADdiv_fun(double x,double y)
{
  return x/y;
}

/**
 * Description not yet available.
 * \param
 */
double ADsum_fun(double x,double y)
{
  return x+y;
}

/**
 * Description not yet available.
 * \param
 */
double ADdiff_fun(double x,double y)
{
  return x-y;
}

/**
 * Description not yet available.
 * \param
 */
double ADzero_fun(double x,double y)
{
  return 0.0;
}

/**
 * Description not yet available.
 * \param
 */
double ADzero_fun(double x)
{
  return 0.0;
}

/**
 * Description not yet available.
 * \param
 */
double AD1_fun(double x)
{
  return 1.0;
}

/**
 * Description not yet available.
 * \param
 */
double AD1_fun(double x,double y)
{
  return 1.0;
}

/**
 * Description not yet available.
 * \param
 */
double ADm1_fun(double x,double y)
{
  return -1.0;
}

/**
 * Description not yet available.
 * \param
 */
double AD_id(double x)
{
  return x;
}

/**
 * Description not yet available.
 * \param
 */
double ADfirst_arg(double x,double y)
{
  return x;
}

/**
 * Description not yet available.
 * \param
 */
double ADsecond_arg_plus1(double x,double y)
{
  return y+1;
}

/**
 * Description not yet available.
 * \param
 */
double ADsecond_arg(double x,double y)
{
  return y;
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_1(double x,double y)
{
  return 1.0/y;
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_2(double x,double y)
{
  return -x/(y*y);
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_22(double x,double y)
{
  return 2.0*x/(y*y*y);
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_122(double x,double y)
{
  return 2.0/(y*y*y);
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_12(double x,double y)
{
  return -1.0/(y*y);
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_11(double x,double y)
{
  return 0.0;
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_111(double x,double y)
{
  return 0.0;
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_112(double x,double y)
{
  return 0.0;
}

/**
 * Description not yet available.
 * \param
 */
double AD_div_222(double x,double y)
{
  return -6.0*x/(y*y*y*y);
}

df1b2function2 ADf1b2_div(ADdiv_fun,
 AD_div_1,AD_div_2,
 AD_div_11,AD_div_12,AD_div_22,
 AD_div_111,AD_div_112,AD_div_122,
 AD_div_222);

df1b2function2 ADf1b2_mult_add(ADmult_add_fun,
  ADsecond_arg_plus1,ADfirst_arg,
  ADzero_fun,AD1_fun,ADzero_fun,
  ADzero_fun, ADzero_fun, ADzero_fun,
  ADzero_fun,"mult_add");

/**
 * Description not yet available.
 * \param
 */
df1b2variable mult_add(const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_mult_add(x,y);
}


df1b2function2 ADf1b2_product(ADproduct_fun,
  ADsecond_arg,ADfirst_arg,
  ADzero_fun,AD1_fun,ADzero_fun,
  ADzero_fun, ADzero_fun, ADzero_fun,
  ADzero_fun,"product");

df1b2function2 ADf1b2_diff(ADdiff_fun,
  AD1_fun,ADm1_fun,
  ADzero_fun,ADzero_fun,ADzero_fun,
  ADzero_fun,ADzero_fun,ADzero_fun,
  ADzero_fun);

/**
 * Description not yet available.
 * \param
 */
double ADsquare_fun(double x)
{
  return x*x;
}

/**
 * Description not yet available.
 * \param
 */
double ADthree_square_fun(double x)
{
  return 3.0*x*x;
}

/**
 * Description not yet available.
 * \param
 */
double ADcube_fun(double x)
{
  return x*x*x;
}

/**
 * Description not yet available.
 * \param
 */
double ADtwo_id_fun(double x)
{
  return 2.0*x;
}

/**
 * Description not yet available.
 * \param
 */
double ADsix_id_fun(double x)
{
  return 6.0*x;
}

/**
 * Description not yet available.
 * \param
 */
double ADsix_fun(double x)
{
  return 6.0;
}

/**
 * Description not yet available.
 * \param
 */
double ADtwo_fun(double x)
{
  return 2.0;
}


df1b2function1 ADf1b2_square(ADsquare_fun,ADtwo_id_fun,ADtwo_fun,ADzero_fun,
  "square");

/**
 * Description not yet available.
 * \param
 */
df1b2variable square(const df1b2variable& x)
{
  return ADf1b2_square(x);
}

df1b2function1 ADf1b2_cube(ADcube_fun,ADthree_square_fun,ADsix_id_fun,ADsix_fun,
  "cube");

/**
 * Description not yet available.
 * \param
 */
df1b2variable cube(const df1b2variable& x)
{
  return ADf1b2_cube(x);
}

/*
df1b2variable fourth(const df1b2variable& _z)
{
  ADUNCONST(df1b2variable,z)
  df1b2variable u;
  double x=*z.get_u();
  tmp.get_u()=x3*x.get_u();
  double dfx=4.0*cube(x);
  double d2fx=12.0*square(x);
  double d3fx=24.0*x;

  double * xd=z.get_u_dot();
  double * zd=u.get_u_dot();
  *u.get_u()=f;
  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ =dfx * *xd++;
  }

  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1(&z,&u,dfx,d2f,d3f);
  return(u);
}
*/

/*
df1b2variable operator * (const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_product(x,y);
}


df1b2variable operator / (const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_div(x,y);
}
*/


/*
df1b2variable operator - (const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_diff(x,y);
}
*/

/*
df1b2variable operator * (double x,const df1b2variable& y)
{
  return ADf1b2_product(x,y);
}
*/
/*
df1b2variable operator * (const df1b2variable& x,double y)
{
  return ADf1b2_product(y,x);
}
*/

// the boilerplate for defining the + operator

df1b2function2 ADf1b2_sum(ADsum_fun,
  AD1_fun,AD1_fun,
  ADzero_fun,ADzero_fun,ADzero_fun,
  ADzero_fun, ADzero_fun, ADzero_fun, ADzero_fun,"sum");
/*
mydf1b2function2 ADf1b2_mysum(ADsum_fun,
  AD1_fun,AD1_fun,
  ADzero_fun,ADzero_fun,ADzero_fun,
  ADzero_fun, ADzero_fun, ADzero_fun, ADzero_fun);
*/

df1b2function1 ADf1b2_assign(AD_id,AD1_fun,ADzero_fun,ADzero_fun);

/*
df1b2function1 ADf1b2_pluseq(AD_id,AD1_fun,ADzero_fun,ADzero_fun);

df1b2variable& df1b2variable::operator += (const df1b2variable& y)
{
  return ADf1b2_pluseq(*this,y,1); // 1 so that special function is used
}


df1b2variable operator + (const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_sum(x,y);
}
*/



/*
df1b2variable mysum(const df1b2variable& x,const df1b2variable& y)
{
  return ADf1b2_mysum(x,y);
}
*/

/*
df1b2variable operator + (double x,const df1b2variable& y)
{
  return ADf1b2_sum(x,y);
}
*/
/*
df1b2variable operator + (const df1b2variable& x,double y)
{
  return ADf1b2_sum(x,y);
}
*/
