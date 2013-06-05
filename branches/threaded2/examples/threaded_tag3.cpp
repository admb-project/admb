#include "all.hpp"
#include "threaded_tag3.h"


#ifdef __MSC__
  double mfexp(const double& );
  dvariable mfexp(const prevariable& );
  dvar_vector mfexp(const dvar_vector& );
  dvector mfexp(const dvector& );
#else
  double mfexp(double& );
  dvariable mfexp(BOR_CONST prevariable& );
  //dvar_vector mfexp(dvar_vector& );
  //dvector mfexp(dvector& );
#endif

#ifdef __MSVC32__
  dvariable age_at_length_calcxx(double& v,dvar_vector& gml,int nslots);
#else
  dvariable age_at_length_calcxx(const dvariable& v,dvar_vector& gml,int nslots);
#endif
#include <adthread.h>
extern mf_pvm_manager * mf_pvm;

 
double mmaxZ[5];

void xxxtags::allocate(void)
{
 initial_tag_release_by_age.allocate(1,num_tag_releases,1,nage);
 initial_tag_release_by_age.initialize();
 tagcatch.allocate(1,num_tag_releases,1,num_regions,initial_tag_period,
   terminal_tag_period,
   1,num_tagfish_incidents,min_tag_age4,nage);


  if (!age_flags(96)) 
  {
    cout << " initial_tag_year(2) "  << initial_tag_year(2)  << endl;
    tagN.allocate(1,num_tag_releases,1,num_regions,
      index_type(initial_tag_year),nyears,min_tag_age1,nage);
    tagnum_fish.allocate(1,num_tag_releases,1,num_regions,initial_tag_period,
      imatrix(1,num_tag_releases,num_fish_periods),min_tag_age,nage);
  }
  else
  {
    tagN.allocate(1,num_tag_releases,1,num_regions,
      index_type(initial_tag_year),index_type(terminal_tag_year),
      min_tag_age6,nage);
    tagnum_fish.allocate(1,num_tag_releases,1,num_regions,initial_tag_period,
      terminal_tag_period,min_tag_age5,nage);
    pooledtagN.allocate(1,num_regions,min_tag_year,nyears,1,nage);
    pooledobstagcatch.allocate(1,num_regions,
      minttp+1,num_fish_periods,
      1,num_pooledtagfish_incidents,1,nage);
      
    pooled_tagnum_fish.allocate(1,num_regions,minttp+1,num_fish_periods,
       1,nage);
    epooled_tagnum_fish_recr.allocate(1,num_regions,minttp+1,num_fish_periods,
       1,nage);
    pooled_tagcatch.allocate(1,num_regions,minttp+1,
      num_fish_periods,
      1,num_pooledtagfish_incidents,1,nage);

  } 
    
  obstagcatch1.allocate(1,num_tag_releases,1,num_regions,
    initial_tag_period, terminal_tag_period,
    1,num_tagfish_incidents,min_tag_age4,nage);

  obstagcatch.allocate(1,num_tag_releases,1,num_regions,
    initial_tag_period, terminal_tag_period,
    1,num_tagfish_incidents,min_tag_age4,nage);
}

int xxxtags::get_variables_from_master1(void)
{
  int tn=0;  // from master
  ad_comm::pthread_manager->read_lock_buffer(tn);
  cout << "start getting stuff from master" << endl;
  int flag=ad_comm::pthread_manager->get_int(tn);
  if (flag)
    return 1;
  rep_rate=ad_comm::pthread_manager->get_dvar3_array(tn);
  nat_mort=ad_comm::pthread_manager->get_dvar_matrix(tn); 
  fraction=ad_comm::pthread_manager->get_dvar_matrix(tn);
  incident_sel=ad_comm::pthread_manager->get_dvar4_array(tn);
  tot_mort=ad_comm::pthread_manager->get_dvar3_array(tn); 
 // tagnum_fish=ad_comm::pthread_manager->get_dvar4_array(tn);
 // tagN=ad_comm::pthread_manager->get_dvar4_array(tn);
  nrtm=ad_comm::pthread_manager->get_dvar4_array(tn);
  Dad=ad_comm::pthread_manager->get_dvar4_array(tn); 
  nrfm=ad_comm::pthread_manager->get_dvar5_array(tn);
  nrsurv=ad_comm::pthread_manager->get_dvar4_array(tn);
  //tagcatch=ad_comm::pthread_manager->get_dvar5_array(tn); 
  fish_mort_calcs=ad_comm::pthread_manager->get_dvar4_array(tn); 
  if (pmsd)
  {
    pmsd->nat_mort=ad_comm::pthread_manager->get_dvar3_array(tn); 
  }
  obstagcatch=ad_comm::pthread_manager->get_dvar5_array(tn); 
  fish_pars=ad_comm::pthread_manager->get_dvar_matrix(tn);
  tag_fish_rep=ad_comm::pthread_manager->get_dvar_matrix(tn);
  //pooled_tagcatch=ad_comm::pthread_manager->get_dvar4_array(tn); 
  //pooledobstagcatch=ad_comm::pthread_manager->get_dvar4_array(tn); 
  cout << "end getting stuff from master" << endl;
  ad_comm::pthread_manager->read_unlock_buffer(tn);
  return 0;
}
int xxxtags::get_variables_from_master_1A(int nt)
{
  adtimer adt;
  ad_comm::pthread_manager->read_lock_buffer(nt);
  int tm=adt.get_elapsed_time_and_reset();
  cout << "Time getting read lock in get_variables_from_master_1A " 
       << tm/1000.  << endl;
  int flag=ad_comm::pthread_manager->get_int(nt);
  if (flag)
    return 1;
  rep_rate=ad_comm::pthread_manager->get_dvar3_array(nt);
  if (ad_comm::pthread_manager->gmin(1)<nt)
  {
    //tagnum_fish+=ad_comm::pthread_manager->get_dvar4_array(nt);
    //tagN+=ad_comm::pthread_manager->get_dvar4_array(nt);
    //tagcatch+=ad_comm::pthread_manager->get_dvar5_array(nt); 
    //obstagcatch+=ad_comm::pthread_manager->get_dvar5_array(nt); 
    // !!! this was for pbstagcatch
    //ad_comm::pthread_manager->get_dvar5_array(nt); 
    fish_pars=ad_comm::pthread_manager->get_dvar_matrix(nt);
    tag_fish_rep=ad_comm::pthread_manager->get_dvar_matrix(nt);
    dvar4_array tmp4=ad_comm::pthread_manager->get_dvar4_array(nt); 
    cout << " proc " << nt << " pooled_tagcatch " << sum(tmp4) << endl;
    pooled_tagcatch+=tmp4;
    //pooled_tagcatch+=ad_comm::pthread_manager->get_dvar4_array(nt); 
    //pooledobstagcatch+=ad_comm::pthread_manager->get_dvar4_array(nt); 
    ad_comm::pthread_manager->get_dvar4_array(nt); 
  }
  else
  {
    //tagnum_fish=ad_comm::pthread_manager->get_dvar4_array(nt);
    //tagN=ad_comm::pthread_manager->get_dvar4_array(nt);
    //tagcatch=ad_comm::pthread_manager->get_dvar5_array(nt); 
    //obstagcatch=ad_comm::pthread_manager->get_dvar5_array(nt); 
    fish_pars=ad_comm::pthread_manager->get_dvar_matrix(nt);
    tag_fish_rep=ad_comm::pthread_manager->get_dvar_matrix(nt);
    dvar4_array tmp4=ad_comm::pthread_manager->get_dvar4_array(nt); 
    cout << " proc " << nt << " pooled_tagcatch " << sum(tmp4) << endl;
    pooled_tagcatch=tmp4;
    //pooled_tagcatch=ad_comm::pthread_manager->get_dvar4_array(nt); 
    pooledobstagcatch=ad_comm::pthread_manager->get_dvar4_array(nt); 
  }
  
  ad_comm::pthread_manager->read_unlock_buffer(nt);
  return 0;
}


int xxxtags::get_variables_from_master2(int tn)
{
  ad_comm::pthread_manager->read_lock_buffer(tn);
  int flag=ad_comm::pthread_manager->get_int(tn);
  if (flag)
  {
    ad_comm::pthread_manager->read_unlock_buffer(tn);
    return 1;
  }
  if (pmsd)
  {
    pmsd->vb_coff=ad_comm::pthread_manager->get_dvar_matrix(tn); 
  }
  //initial_tag_release_by_age=ad_comm::pthread_manager->get_dvar_matrix(tn);
  vb_coff=ad_comm::pthread_manager->get_dvar_vector(tn);
  var_coff=ad_comm::pthread_manager->get_dvar_vector(tn);
  //cout << "UUU " << vb_coff << endl;
  ad_comm::pthread_manager->read_unlock_buffer(tn);
  return 0;
}

int dvar_len_fish_stock_history::send_variables_to_tag_slave1(int flag,
  int slave_number)
{
  ad_comm::pthread_manager->write_lock_buffer(slave_number);
 
  ad_comm::pthread_manager->send_int(flag,slave_number);
  ad_comm::pthread_manager->send_dvar3_array(rep_rate,slave_number);
  ad_comm::pthread_manager->send_dvar_matrix(nat_mort,slave_number); 
  ad_comm::pthread_manager->send_dvar_matrix(fraction,slave_number);
  ad_comm::pthread_manager->send_dvar4_array(incident_sel,slave_number);
  ad_comm::pthread_manager->send_dvar3_array(tot_mort,slave_number); 
  //ad_comm::pthread_manager->send_dvar4_array(tagnum_fish,slave_number);
  //ad_comm::pthread_manager->send_dvar4_array(tagN,slave_number);
  ad_comm::pthread_manager->send_dvar4_array(nrtm,slave_number);
  ad_comm::pthread_manager->send_dvar4_array(Dad,slave_number); 
  ad_comm::pthread_manager->send_dvar5_array(nrfm,slave_number);
  ad_comm::pthread_manager->send_dvar4_array(nrsurv,slave_number);
  //ad_comm::pthread_manager->send_dvar5_array(tagcatch,slave_number); 
  ad_comm::pthread_manager->send_dvar4_array(fish_mort_calcs,slave_number); 
  if (pmsd)
  {
    ad_comm::pthread_manager->send_dvar3_array(pmsd->nat_mort,slave_number); 
  }
  ad_comm::pthread_manager->send_dvar5_array(obstagcatch,slave_number); 
  ad_comm::pthread_manager->send_dvar_matrix(fish_pars,slave_number);
  ad_comm::pthread_manager->send_dvar_matrix(tag_fish_rep,slave_number);

  //ad_comm::pthread_manager->send_dvar4_array(pooled_tagcatch,slave_number); 
  //ad_comm::pthread_manager->send_dvar4_array(pooledobstagcatch,slave_number); 
  long int offset=ad_comm::pthread_manager->get_offset(slave_number);
  cout << "sent " << offset << "bytes in send tag slave 1" << endl;
  ad_comm::pthread_manager->write_unlock_buffer(slave_number);
}

int xxxtags::send_variables_to_tag_slave_1A(int flag,int slave_number)
{
  ad_comm::pthread_manager->write_lock_buffer(slave_number);
  ad_comm::pthread_manager->send_int(flag,slave_number);
  ad_comm::pthread_manager->send_dvar3_array(rep_rate,slave_number);
  //ad_comm::pthread_manager->send_dvar_matrix(nat_mort,slave_number); 
  //ad_comm::pthread_manager->send_dvar_matrix(fraction,slave_number);
  //ad_comm::pthread_manager->send_dvar4_array(incident_sel,slave_number);
  //ad_comm::pthread_manager->send_dvar3_array(tot_mort,slave_number); 
  //ad_comm::pthread_manager->send_dvar4_array(tagnum_fish,slave_number);
  //ad_comm::pthread_manager->send_dvar4_array(tagN,slave_number);
  //ad_comm::pthread_manager->send_dvar5_array(tagcatch,slave_number); 
  //ad_comm::pthread_manager->send_dvar4_array(fish_mort_calcs,slave_number); 
  if (pmsd)
  {
   // ad_comm::pthread_manager->send_dvar3_array(pmsd->nat_mort,slave_number); 
  }
  //ad_comm::pthread_manager->send_dvar5_array(obstagcatch,slave_number); 
  ad_comm::pthread_manager->send_dvar_matrix(fish_pars,slave_number);
  ad_comm::pthread_manager->send_dvar_matrix(tag_fish_rep,slave_number);
  ad_comm::pthread_manager->send_dvar4_array(pooled_tagcatch,slave_number); 
  ad_comm::pthread_manager->send_dvar4_array(pooledobstagcatch,slave_number); 
  long int offset=ad_comm::pthread_manager->get_offset(slave_number);
  cout << "sent " << offset << "bytes in send tag slave 1A" << endl;
  ad_comm::pthread_manager->write_unlock_buffer(slave_number);
}

int dvar_len_fish_stock_history::send_variables_to_tag_slave2(int flag,
  int slave_number)
{
  ad_comm::pthread_manager->write_lock_buffer(slave_number);
  ad_comm::pthread_manager->send_int(flag,slave_number);
  if (pmsd)
  {
    ad_comm::pthread_manager->send_dvar_matrix(pmsd->vb_coff,slave_number); 
  }
  ad_comm::pthread_manager->send_dvar_vector(vb_coff,slave_number);
  ad_comm::pthread_manager->send_dvar_vector(var_coff,slave_number);
  ad_comm::pthread_manager->write_unlock_buffer(slave_number);
}

int xxxtags::send_variables_to_tag_slave2(int flag,
  int slave_number)
{
  ad_comm::pthread_manager->write_lock_buffer(slave_number);
  ad_comm::pthread_manager->send_int(flag,slave_number);
  if (pmsd)
  {
    ad_comm::pthread_manager->send_dvar_matrix(pmsd->vb_coff,slave_number); 
  }
  ad_comm::pthread_manager->send_dvar_vector(vb_coff,slave_number);
  ad_comm::pthread_manager->send_dvar_vector(var_coff,slave_number);
  ad_comm::pthread_manager->write_unlock_buffer(slave_number);
}

void dfadsleep(void)
{
  verify_identifier_string("RT");
  int sec=restore_int_value();
  verify_identifier_string("YD");
  sleep(sec);
}


void adsleep(int sec)
{
  sleep(sec);
  save_identifier_string("YD");
  save_int_value(sec);
  save_identifier_string("RT");
  gradient_structure::GRAD_STACK1->
   set_gradient_stack(dfadsleep);
}
  

dvariable xxxtags::tag_catch_equations_calc_loop_1(void)
{
  int tn=0;
  get_constant_data(tn);
  gradient_structure::set_MAX_NVAR_OFFSET(10000);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(120000000);
  gradient_structure::set_MAX_NVAR_OFFSET(30000);
  gradient_structure gs(100000000);
  adtimer adt1;

  int sno=ad_comm::pthread_manager->get_slave_number();
  allocate();
  do
  {
    adt1.get_elapsed_time_and_reset();
    int iflag=get_variables_from_master2(0);
    double tm=adt1.get_elapsed_time_and_reset();
    cout << "get_variables_from_master2(0) time waiting =" << tm << endl;
    if (ad_comm::pthread_manager->ngroups>1)
    {
      int mmin=ad_comm::pthread_manager->gmin(2);
      int mmax=ad_comm::pthread_manager->gmax(2);
      for (int kk=mmin;kk<=mmax;kk++)
      {
        send_variables_to_tag_slave2(iflag,kk);
      }
    }
    if (iflag==1) break;

    iflag=get_variables_from_master1();
    if (num_tag_releases>0)
    {
      var_convert_tag_lengths_to_age();
      if (!age_flags(96))
        observed_tags_by_age_from_length();
      else
        observed_tags_by_age_from_length_pooled();
    }

    if (iflag==1) break;
    dvar_vector sv;
    dvariable ffpen=0.0;
    dvariable imppen=0.0;
    //catch_equations_calc(sv,pq_flag,imppen);
    ffpen+=imppen;
    if (!pq_flag)
    {
      if (num_tag_releases && age_flags(122)==0)
      {
        if (!age_flags(96))
        {
          adt1.get_elapsed_time_and_reset();
          ffpen+=tag_catch_equations_calc(sv);
          double tm=adt1.get_elapsed_time_and_reset();
          cout << "AA " << tm << endl;
        }
        else
        {
          adt1.get_elapsed_time_and_reset();
          ffpen+=xtag_catch_equations_calc_pooled(sv);
          xpooled_tag_catch_equations_calc(sv);
          double tm=adt1.get_elapsed_time_and_reset();
          cout << "BB " << tm << endl;
        }
      }
    }

    dvariable tmp=0;
    if (ad_comm::pthread_manager->ngroups>1)
    {
      int mmin=ad_comm::pthread_manager->gmin(2);
      int mmax=ad_comm::pthread_manager->gmax(2);
      for (int kk=mmin;kk<=mmax;kk++)
      {
        send_variables_to_tag_slave_1A(0,kk);
      }
    }

    tm=adt1.get_elapsed_time_and_reset();
    cout << "time before fit_tag_returns in loop 1 slave "  << sno 
         << "   "  << tm/1000 << endl;
    tmp=fit_tag_returns();
    tm=adt1.get_elapsed_time_and_reset();
    cout << "fit_tag_returns in loop 1 slave "  << sno 
         << "   "  << tmp << endl;
    cout << "time after fit_tag_returns in loop 1 slave "  << sno 
         << "   "  << tm/1000 << endl;
   
    int nt=0;
    ad_comm::pthread_manager->write_lock_buffer(nt);
    ad_comm::pthread_manager->send_dvariable(tmp,nt); 
    ad_comm::pthread_manager->write_unlock_buffer(nt);

    slave_gradcalc();

  }
  while(1);
}

dvariable xxxtags::tag_catch_equations_calc(dvar_vector& sv)
{
  mmaxZ[1]=0.0;
  dvariable ffpen=0.0;
  double one_plus=1.e0+1.e-10;
  int break_flag=0;
  ivector tmp_mp(1,num_regions);
  int mmin,mmax;
  int ir,ip,it;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  for (it=mmin;it<=mmax;it++)
  {

    get_initial_tag_population(sv,it);

    int current_year=tag_year(it);
    ivector rip(1,num_regions);
    ivector skip_flag(1,num_regions);
    rip=initial_tag_period(it);
    skip_flag.initialize();
    for (ir=1;ir<=num_regions;ir++)
    {
      //if (rip(ir)==num_fish_periods(ir))
      {
        if (move_flags(ir,rip(ir)))
        {
          skip_flag(ir)=1;
          tmp_mp(ir)=move_index(ir,rip(ir));
        }
      }
    }

    int finished_flag=0;
    for (ir=1;ir<=num_regions;ir++)
    {
      tagnum_fish(it,ir,rip(ir))=tagN(it,ir,year(ir,rip(ir)));
    }
    do
    {
      finished_flag=1;
      int myprintflag=0;
      for (int ir=1;ir<=num_regions;ir++)
      {
        break_flag=0;
        int& ip=rip(ir);
        do
        {
          if (ip>=num_fish_periods(ir)) break;
          finished_flag=0;
          if (skip_flag(ir))
          {
            skip_flag(ir)=0;
            break;
          }
          int jmin=tagnum_fish(it,ir,ip).indexmin();
          if (year(ir,ip+1)==year(ir,ip))
          {
            if (!num_fish_incidents(ir,ip) || !tag_flags(it,1) || 
              ip >= initial_tag_period(it,ir)+tag_flags(it,1))
            {
              tagnum_fish(it,ir,ip+1)=tagnum_fish(it,ir,ip)
                -tot_mort(ir,ip)(jmin,nage);
            }
            else
            {
              //new_do_newton_raphson_for_tags(it,ir,ip,ffpen);
              do_newton_raphson_for_tags2(it,ir,ip,ffpen);
              // new code to do NR properly DF May 08 08
              //new_do_newton_raphson_for_tags(it,ir,ip,ffpen);
              tagnum_fish(it,ir,ip+1)=tagnum_fish(it,ir,ip)
                -nrtm(it,ir,ip)(jmin,nage);
            }

          }
          else
          {
            // age the tags
            //tagnum_fish(it,ir,ip+1,1)=-15.0;
            if (it==1 && ir==1 && ip==40)
            {
              cout << "HERE" << endl;
            }

            if (!num_fish_incidents(ir,ip) || !tag_flags(it,1) || 
              ip >= initial_tag_period(it,ir)+tag_flags(it,1))
            {
              if (nage>2 && jmin<nage-1)
                --tagnum_fish(it,ir,ip+1)(jmin+1,nage-1)=
                  tagnum_fish(it,ir,ip)(jmin,nage-2)
                    -tot_mort(ir,ip)(jmin,nage-2);

              if (jmin<nage)
              {
                tagnum_fish(it,ir,ip+1,nage)=
                  log(1.e-12 + mfexp(tagnum_fish(it,ir,ip,nage-1)
                  -tot_mort(ir,ip,nage-1))
                  + mfexp(tagnum_fish(it,ir,ip,nage)-tot_mort(ir,ip,nage)) );
              }
              else
              {
                tagnum_fish(it,ir,ip+1,nage)=
                  tagnum_fish(it,ir,ip,nage)-tot_mort(ir,ip,nage);
              }
            }
            else
            {
              //new_do_newton_raphson_for_tags(it,ir,ip,ffpen);
              do_newton_raphson_for_tags2(it,ir,ip,ffpen);
              // new code to do NR properly DF May 08 08
              //new_do_newton_raphson_for_tags(it,ir,ip,ffpen);



              int n1=nage-1;
              if (nage>2) 
              {
                if (jmin<n1)
                {
                  --tagnum_fish(it,ir,ip+1)(jmin+1,nage-1)=
                  tagnum_fish(it,ir,ip)(jmin,nage-2)-nrtm(it,ir,ip)(jmin,nage-2);
                }
              }
              if (jmin<nage)
              {
                tagnum_fish(it,ir,ip+1,nage)=
                  log(1.e-10 + mfexp(tagnum_fish(it,ir,ip,nage-1)
                  -tot_mort(ir,ip,nage-1))
                  + mfexp(tagnum_fish(it,ir,ip,nage)-nrtm(it,ir,ip,nage)));
              }
              else
              {
                tagnum_fish(it,ir,ip+1,nage)=
                  tagnum_fish(it,ir,ip,nage)-nrtm(it,ir,ip,nage);
              }
            }
          }
          if (move_flags(ir,ip+1))
          {
            tmp_mp(ir)=move_index(ir,ip+1);
            break_flag=1;
          } 
          ip++;
        }
        while (!break_flag); 
      }
      // move the tags
      if (sum(tmp_mp))
      {
        if (num_regions>1)
        {
          // !!!!!!  check_sanity(tmp_mp,tagnum_fish(it),rip,it,*this);
          dvar_matrix tmp=fast_diffusion_calcs(nage,num_regions,
            tagnum_fish(it),Dad(tmp_mp(1)),rip,0,pmsd);
            //tagnum_fish(it),Dad(tmp_mp(1)),rip);
          for (int ir=1;ir<=num_regions;ir++)
          {
            tagnum_fish(it,ir,rip(ir))=log(1.e-12+tmp(ir));
          }
        }
      }
      tmp_mp=0;
    } // need to decide when to quit
    while (!finished_flag);
  }

  
  for (it=mmin;it<=mmax;it++)
  {
    int rmin=1;
    int rmax=num_regions;
   /*
    if (pmsd)
    {
        int cs=pmsd->tag_species_pointer(it);
        rmin=pmsd->region_bounds(cs,1);
        rmax=pmsd->region_bounds(cs,2);
    }
    else
    {
      rmin=1;
      rmax=num_regions;
    }
   */
 
    for (ir=rmin;ir<=rmax;ir++)
    {
      for (int ip=initial_tag_period(it,ir);ip<=num_fish_periods(ir);ip++)  
      {
        if (!tag_flags(it,1) || 
          ip >= initial_tag_period(it,ir)+tag_flags(it,1))
        {
          for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
          {        
            dvar_vector& tc=tagcatch(it,ir,ip,fi);
            int jmin=tc.indexmin();
            tc=exp(fish_mort_calcs(ir,ip,fi)(jmin,nage)
              +tagnum_fish(it,ir,ip));
          }
        }
        else
        {
          //double ssum=0;
          cout << "can not goe here" << endl;
          for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
          {        
            tagcatch(it,ir,ip,fi)=
              exp(nrfm(it,ir,ip,fi)-log(1.e-10+nrtm(it,ir,ip))+
              log(one_plus-nrsurv(it,ir,ip))+tagnum_fish(it,ir,ip));
          }
        }
      }
    }
  }
 
  return ffpen;
}

void xxxtags::get_initial_tag_population(dvar_vector& sv,
  int it)
{
  tagN(it).initialize();
  int ir;

  int yr1=tag_year(it);
  for (ir=1;ir<=num_regions;ir++)
  {
    tagN(it,ir)=-15.0;
  }
  ir=tag_region(it);
  tagN(it,ir,yr1)=log(initial_tag_release_by_age(it)+1.e-12);

  // here is where we "diffuse " the tagged fish to move them between 
  // the regions
  if (num_regions>1) do_the_diffusion(yr1,sv,tagN(it));
}
  
void xxxtags::do_the_diffusion(int year,dvar_vector& sv,dvar3_array& N,
  ofstream * pofs)
{
  dvar_matrix tmp=fast_diffusion_calcs(nage,num_regions,N,Dad(1),year,pmsd);
  //check_derivative_values("epos1");
  for (int ir=1;ir<=num_regions;ir++)
  {
    N(ir,year)=log( 5.e-10+tmp(ir) );
  }
  //check_derivative_values("fpos1");
}
dvar_matrix fast_diffusion_calcs(int nage,int num_regions,dvar3_array& N,
  dvar3_array& Dad,ivector& rip,int maxage,pxxxmspd & pmsd)
{ 
  const double delta=1.e-6;
  //const double nd=num_regions*delta;    //NMD 4Oct2012

  int j;
  if (!pmsd)
  { 
    const double nd=num_regions*delta;  //NMD 2Oct2012
    if (maxage) nage=min(nage,maxage);
    int jmin=N(1,rip(1)).indexmin();
    dvar_matrix EN(jmin,nage,1,num_regions);
    dvar_matrix tmp(jmin,nage,1,num_regions);
    tmp.initialize();
  
    for (j=jmin;j<=nage;j++)
    {
      for (int is=1;is<=num_regions;is++)
      {
        EN(j,is)=mfexp(N(is,rip(is),j));
      }
    }
    for (j=jmin;j<=nage;j++)
    {
      for (int ir=1;ir<=num_regions;ir++)
      {
        for (int is=1;is<=num_regions;is++)
        {
          tmp(j,ir)+=Dad(j)(ir,is)*EN(j,is);
        }
      }
      dvariable ss=sum(tmp(j));
      tmp(j)+=delta;
      tmp(j)*=ss/(ss+nd);
    }
    return trans(tmp);
  }
  else
  { 
    const double nd=pmsd->num_real_regions*delta;  //NMD 2Oct2012
    if (maxage) nage=min(nage,maxage);
    int jmin=N(1,rip(1)).indexmin();
    int nrr=pmsd->num_real_regions;
    int ns=pmsd->num_species;
    dvar_matrix tmp1(1,num_regions,jmin,nage);
    int isp;
    for (isp=1;isp<=ns;isp++)
    {
      int offset=(isp-1)*nrr;
      dvar_matrix EN(jmin,nage,1,nrr);
      dvar_matrix tmp(jmin,nage,1,nrr);
      tmp.initialize();
    
      for (j=jmin;j<=nage;j++)
      {
        for (int is=1;is<=nrr;is++)
        {
          EN(j,is)=mfexp(N(is+offset,rip(is+offset),j));
        }
      }
      for (j=jmin;j<=nage;j++)
      {
        dvar_matrix td=Dad(j).sub(1+offset,nrr+offset).shift(1);
        for (int ir=1;ir<=nrr;ir++)
        {
          for (int is=1;is<=nrr;is++)
          {
            tmp(j,ir)+=td(ir,is)*EN(j,is);
          }
        }
        dvariable ss=sum(tmp(j));
        tmp(j)+=delta;
        tmp(j)*=ss/(ss+nd);
      }
      tmp1.sub(1+offset,nrr+offset).shift(1)=trans(tmp);
    }
    return tmp1;
  }
}
dvar_matrix fast_diffusion_calcs(int nage,int num_regions,dvar3_array& N,
  dvar3_array& Dad,int year,pxxxmspd & pmsd)
{ 
  const double delta=1.e-6;
  //const double nd=num_regions*delta;   //NMD 2Oct2012
  if (!pmsd)
  { 
    const double nd=num_regions*delta;  //NMD 2Oct2012
    dvar_matrix EN(1,nage,1,num_regions);
    dvar_matrix tmp(1,nage,1,num_regions);
    tmp.initialize();
    int j;
    for (j=1;j<=nage;j++)
    {
      for (int is=1;is<=num_regions;is++)
      {
        EN(j,is)=mfexp(N(is,year,j));
      }
    }
    for (j=1;j<=nage;j++)
    {
      for (int ir=1;ir<=num_regions;ir++)
      {
        for (int is=1;is<=num_regions;is++)
        {
          tmp(j,ir)+=Dad(j)(ir,is)*EN(j,is);
        }
      }
      dvariable ss=sum(tmp(j));
      tmp(j)+=delta;
      tmp(j)*=ss/(ss+nd);
    }
    return trans(tmp);
  }
  else
  { 
    const double nd=pmsd->num_real_regions*delta;  //NMD 2Oct2012
    int nrr=pmsd->num_real_regions;
    int ns=pmsd->num_species;
    dvar_matrix tmp1(1,num_regions,1,nage);
    int isp;
    for (isp=1;isp<=ns;isp++)
    {
      int offset=(isp-1)*nrr;
      dvar_matrix EN(1,nage,1,nrr);
      dvar_matrix tmp(1,nage,1,nrr);
      tmp.initialize();
      int j;
      for (j=1;j<=nage;j++)
      {
        for (int is=1;is<=nrr;is++)
        {
          EN(j,is)=mfexp(N(is+offset,year,j));
        }
      }
      for (j=1;j<=nage;j++)
      {
        dvar_matrix td=Dad(j).sub(1+offset,nrr+offset).shift(1);
        for (int ir=1;ir<=nrr;ir++)
        {
          for (int is=1;is<=nrr;is++)
          {
            tmp(j,ir)+=td(ir,is)*EN(j,is);
          }
        }
        dvariable ss=sum(tmp(j));        
        tmp(j)+=delta;
        tmp(j)*=ss/(ss+nd);
      }
      tmp1.sub(1+offset,nrr+offset).shift(1)=trans(tmp);
    }
    return tmp1;
  }
}
void xxxtags::
  do_newton_raphson_for_tags2(int it,int ir,int ip,dvariable& _ffpen)
{
  dvariable ffpen=0.0;
  int jmin=tagnum_fish(it,ir,ip).indexmin();
  const dvar_vector& enf=mfexp(tagnum_fish(it,ir,ip));
  dvariable tot_num_fish=sum(enf);
  double nfi=num_fish_incidents(ir,ip);
  dvar_matrix sel(1,nfi,jmin,nage);
  dvar_matrix logsel(1,nfi,jmin,nage);
  int fi;
  for (fi=1;fi<=nfi;fi++)
  {
    int i=parent(ir,ip,fi);
    int rr=realization_region(i,1);
    int rp=realization_period(i,1);
    int ri=realization_incident(i,1);
    logsel(fi)=incident_sel(rr,rp,ri)(jmin,nage);
    sel(fi)=mfexp(logsel(fi));
    /*
  if(it == 2 && ir == 3){  //NMD2Oct2012
  //if(it == 51 && ir == 9){  //NMD2Oct2012
    ofsff << endl << " it = " << it << "   ir = " << ir << "  ip: " << ip << "  fi: " << fi << endl;
    ofsff << " sel(fi) = " <<  sel(fi) << endl;
    ofsff << " logsel(fi) = " <<  logsel(fi) << endl;
  }  //NMD2Oct2012
    */
  }

  dvar_matrix& fm=nrfm(it,ir,ip);
  dvar_matrix M(1,nfi,1,nfi);
  M.initialize();
  dvar_matrix C(1,nfi,jmin,nage);
  dvariable tnf=sum(enf);
  //ofsff << tnf << " " << it << " " << ir << " " << ip << endl;
  if (nfi>1)
  {
    //cout <<"tag3.cpp " << nfi << endl;
  }
  dvar_vector actual_tag_catch=
    elem_div(tot_tag_catch(it,ir,ip),1.e-6+rep_rate(ir,ip));
  
  dvariable region_tot_tag_catch=sum(actual_tag_catch);

  const dvar_vector& ctm=nrtm(it,ir,ip)(jmin,nage);
  dvar_vector& tm=(dvar_vector&)ctm;
  int yr=year(ir,ip);  
  dvar_vector MM=mfexp(get_nat_mort_region(ir)(yr)(jmin,nage)+fraction(ir,ip));
  double normd=0.0;
  int noprogressflag=0;
  if (region_tot_tag_catch>0)
  {
    dvariable surv_rate=(1.0-region_tot_tag_catch/tnf);
  
    dvar_vector kc(1,nfi);

    kc=actual_tag_catch+1.e-5;
    
    dvar_vector qq=elem_div(kc,sel*enf);
    dvar_vector TC(1,nfi);
    int itt=0;
    int badflag=0;
    double rmax=0.7;
    if (age_flags(116)!=0)
    {
      rmax=age_flags(116)/100.;
    }
    dvar_vector Z(jmin,nage);
    do
    {
      Z=qq*sel+MM;
      dvar_vector S(jmin,nage);
      int Zmaxflag=0;
      int ia;
      for (ia=jmin;ia<=nage;ia++)
      {
        if (value(Z(ia))<=rmax)
        {
          S(ia)=exp(-Z(ia));
        }
        else
        {
          Zmaxflag=1;
          dvariable dd=Z(ia)-rmax;
          S(ia)=exp(-rmax)-exp(-rmax)*dd;
        }
      }
      dvar_vector S1N=elem_prod(1.0-S,enf);
      dvar_matrix t1(1,nfi);
      for (int fi=1;fi<=nfi;fi++)
      {
        t1(fi)=elem_div(qq(fi)*sel(fi),Z);
        C(fi)=elem_prod(t1(fi),S1N);
        TC(fi)=sum(C(fi));
      }
      /*
      if (Zmaxflag==0)
      {
        for (int fi=1;fi<=nfi;fi++)
        {
          dvariable Dq=sum(C(fi))/qq(fi);
          dvar_vector DZ=qq(fi)*elem_prod(elem_div(sel(fi),Z),enf)-
            elem_prod(C(fi),1.0+1.0/Z);
          M(fi,fi)=Dq;
          for (int fj=1;fj<=nfi;fj++)
          {
            M(fi,fj)+=DZ*sel(fj);
          }
        }
      }
      else
      {
        for (int fi=1;fi<=nfi;fi++)
        {
          dvariable Dq=sum(C(fi))/qq(fi);
          dvar_vector DZ(jmin,nage);
          for (ia=jmin;ia<=nage;ia++)
          {
            if (value(Z(ia))<=rmax)
            {
              DZ(ia)=qq(fi)*sel(fi,ia)/Z(ia)*enf(ia)-
                C(fi,ia)*(1.0+1.0/Z(ia));
            }
            else
            {
              DZ(ia)=qq(fi)*sel(fi,ia)/Z(ia)*enf(ia)-
                C(fi,ia)/Z(ia)
                +C(fi,ia)/(1.0-S(ia))*exp(-rmax);
            }
          }
          M(fi,fi)=Dq;
          for (int fj=1;fj<=nfi;fj++)
          {
            M(fi,fj)+=DZ*sel(fj);
          }
        }
      }
      */
      dvar_matrix M2=get_jac2(nfi,jmin,nage,qq,sel,enf,MM,rmax);
     /*
      cout <<"tag3.cpp " << M2-M << endl << endl;
      cout <<"tag3.cpp " << trans(M2)-M << endl << endl;
      cout <<"tag3.cpp " << setw(10) << setfixed() << setprecision(3) << norm2(M2-M) << endl;
      */
      M=M2;
      dvar_vector diff=TC-kc;
      normd=norm(value(diff));
      //cout <<"tag3.cpp " <<  elem_div(diff,TC)  << endl;
      int pflag=1;
      if (!badflag)
      {
        // this is newton raphson for q
        dvariable fp1=0.0;
        //dvar_matrix invM=inv(M);
        //ofsff << "M" << endl;
        //ofsff << setw(10) << setprecision(4) << M << endl;
        //ofsff << "invM" << endl;
        //ofsff << setscientific() << setw(10)<< setprecision(4) << invM << endl;
        dvector cqold=value(qq);
        dvar_vector hh=solve(M,diff);
        qq-=hh;
        if (itt>3)
        {
          if (norm(value(qq)-cqold)<1.e-20)
          {
            noprogressflag=1;
          }
        }
        
        int mmin=qq.indexmin();
        int mmax=qq.indexmax();
        for (int i=mmin;i<=mmax;i++)
        {
          qq(i)=posfun(qq(i),1.e-10,fp1);
          if (value(qq(i))<=0.0)
          {
            cerr << "This can't happen " << qq(i) << endl;
            ad_exit(1);
          }
        }
        //ffpen+=fp1;
        //pflag=check_pos(qq,nfi);
        if (!pflag)
        {
          dvariable tmp=0.0;
          throw function_minimizer_exception();
          badflag=1;
          qq+=inv(M)*diff;
          qq=elem_div(qq,mfexp(elem_div(inv(M)*diff,qq)));
        }
        else
        {
          itt++;
        }
      }
      else
      {
        // this i newton raphson for log(q)
        qq=elem_div(qq,1.e-20+mfexp(elem_div(inv(M)*diff,qq)));
        //cout << " " << qq(1);
        itt++;
        pflag=check_pos(qq,nfi);
      }
      if (itt>7) break;
      if (noprogressflag==1) 
      {
        noprogressflag=0;
        break;
      }
      //if ( (itt>1 && pflag && !badflag) || (itt>3 && pflag) )break;
    }
    while(1);
    if (normd>0.5)
    {
      cout << "difficult tag NR A " << normd;
      cout << "  it= " << it ;
      cout << "  region = " << ir ;
      cout << "  fishing period = " << ip << endl;
      cout << " There are " << nfi << " fisheries ";
      for (int i=1;i<=nfi;i++)
        cout << parent(ir,ip,i) << " ";
      cout << endl;
    }
    //cout <<"tag3.cpp " << endl;
    int j;
    //dvar_vector lambda(jmin,nage);
    //lambda.initialize();
    for (j=jmin;j<=nage;j++)
    {
      if (value(Z(j))>rmax)
      {
        if (value(Z(j)) >mmaxZ[1])
        {
         mmaxZ[1]=value(Z(j));
         mmaxZ[2]=it;
         mmaxZ[3]=ir;
         mmaxZ[4]=ip;
        }
        age_flags(181)=2;
        //fpen+=100.*square(Z(j)-rmax);
        dvariable dd=Z(j)-rmax;
        dvariable ppen=0.0;
        dvariable Zstar=rmax-posfun(0.2-dd,0.1,ppen)+0.2;
        ffpen+=ppen;

	/*
        //if(it == 2 && ir == 3){  //NMD1Oct2012
	if(it == 51 && ir == 9){  //NMD1Oct2012
	  ofsff << endl << " it = " << it << "   ir = " << ir << "   j = " << j << endl; endl;
	  ofsff << " Zstar = " << Zstar << endl;
	  ofsff << " dd = " << dd << endl;
	  ofsff << " rmax = " << rmax << endl;
	  ofsff << " dd = " << dd << endl;
	  ofsff << " ppen = " << ppen << endl;
	  ofsff << " MM(j) = " << MM(j) << endl;
	  ofsff << " Zstar-MM(j) = " << Zstar-MM(j) << endl;
        }  //NMD1Oct2012
	*/
  
        dvariable tmp=Zstar-MM(j);
        if (value(tmp)<=0.0)
        {
          ffpen+=100.0*square(log(1.0-tmp));
          //cerr << "Error zstar too small" << endl;
          //ad_exit(1);
        }
        //lambda(j)=log(tmp/(Z(j)-MM(j)));
      }
    }
    dvar_vector tmpFF=log(qq);
    for (fi=1;fi<=nfi;fi++)
    {
      fm(fi)(jmin,nage)=logsel(fi)+tmpFF(fi);  // +lambda;
    }
    tm.initialize();
    for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) // Loop over fishing
    {                                         // incidents for this period
      tm+=mfexp(fm(fi));
    }
    tm+=MM;
  }
  else
  {
    for (fi=1;fi<=nfi;fi++)
    {
      fm(fi)=-10.0;
    }
    tm=MM;
  }
  nrsurv(it,ir,ip)=mfexp(-tm);
  switch (it)
  {
  case 72:
  case 21:
  case 112:
    break;
  default:
    ;
    _ffpen+=ffpen;
  }
}

dvar_matrix xxxtags::get_nat_mort_region(int ir)
{
  if (!pmsd)
    return nat_mort;
  else
  {
    int is=pmsd->region_species_pointer(ir);
    if (is==1)
      return nat_mort;
    else
      return pmsd->nat_mort(is);
  }
}

void admb_tag_thread(void*);
void admb_tag_thread_1(void*);
void admb_tag_thread_2(void*);

int tag_thread_tester(int nslaves,dvar_len_fish_stock_history& fsh)
{
  int i;
  cifstream ifs("groupinfo");
  if (!ifs)
  {
    cerr << "error opening file groupinfo" << endl;
    return 1;
  }
  int ngroups=2;
  ifs >> ngroups;
  ivector ng(1,ngroups);
  ng(1)=1;
  ifs >> ng(1);
  if (ngroups>1)
  {
    ng(2)=1;
    ifs >> ng(2);
  }
  if (ngroups>2)
  {
    ng(3)=1;
    ifs >> ng(3);
  }
  if (!ifs)
  {
    cerr << "error reading file groupinfo" << endl;
    return 1;
  }
  
  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,5000000);
  //ad_comm::pthread_manager = new adpthread_manager(NSLAVES,500);
  int NSLAVES=sum(ng);
  new_thread_data* data1 = new new_thread_data[NSLAVES+1];
  // initialize data to pass to thread 1
  for (i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no = i;
    data1[i].pfsh=&fsh;
  }
  ad_comm::pthread_manager->attach_code(&admb_tag_thread_1);
  if (ngroups>1)
  {
    ad_comm::pthread_manager->attach_code(&admb_tag_thread_2);
  }
  if (ngroups>2)
  {
    ad_comm::pthread_manager->attach_code(&admb_catch_wt);
  }
  //cout << "TTT creating threads" << endl;
  ad_comm::pthread_manager->create_all(data1);
  int gmin=ad_comm::pthread_manager->gmin(1);
  int gmax=ad_comm::pthread_manager->gmax(1);
  for (i=gmin;i<=gmax;i++)
  {
    fsh.send_constant_data(i);
  }
  if (ngroups>1)
  {
    int gmin=ad_comm::pthread_manager->gmin(2);
    int gmax=ad_comm::pthread_manager->gmax(2);
    for (i=gmin;i<=gmax;i++)
    {
      fsh.send_constant_data(i);
    }
  }

  if (ngroups>2)
  {
    int gmin=ad_comm::pthread_manager->gmin(3);
    int gmax=ad_comm::pthread_manager->gmax(3);
    for (i=gmin;i<=gmax;i++)
    {
      fsh.send_constant_data_3(i);
    }
  }

  return 0;
}

/*
void admb_tag_thread(void *ptr)
{
  volatile new_thread_data * tptr = (new_thread_data *) ptr;
  int sno=tptr->thread_no;
  ad_comm::pthread_manager->set_slave_number(sno);

  // get information from master
  pthread_mutex_lock(&ad_comm::pthread_manager->copy_mutex);
  xxxtags tagstuff=tptr->pfsh->make_tagstuff(sno);
  pthread_mutex_unlock(&ad_comm::pthread_manager->copy_mutex);
  tagstuff.tag_catch_equations_calc_loop();
}
*/

void admb_tag_thread_1(void *ptr)
{
  new_thread_data * tptr = (new_thread_data *) ptr;
  int sno=tptr->thread_no;
  ad_comm::pthread_manager->set_slave_number(sno);

  // get information from master
  pthread_mutex_lock(&ad_comm::pthread_manager->copy_mutex);
  xxxtags tagstuff=tptr->pfsh->make_tagstuff(sno);
  pthread_mutex_unlock(&ad_comm::pthread_manager->copy_mutex);
  tagstuff.tag_catch_equations_calc_loop_1();
}

void admb_tag_thread_2(void *ptr)
{
  new_thread_data * tptr = (new_thread_data *) ptr;
  int sno=tptr->thread_no;
  ad_comm::pthread_manager->set_slave_number(sno);

  //get information from master
  pthread_mutex_lock(&ad_comm::pthread_manager->copy_mutex);
  xxxtags tagstuff=tptr->pfsh->make_tagstuff(sno);
  pthread_mutex_unlock(&ad_comm::pthread_manager->copy_mutex);
  tagstuff.tag_catch_equations_calc_loop_2();
}

xxxtags dvar_len_fish_stock_history::make_tagstuff(int sno)
{
 /*
  xxxtags tmp=xxxtags::xxxtags(sno,num_regions,min_tag_group,max_tag_group,
  num_tag_releases, tag_year,initial_tag_period,move_flags,move_index,
  num_fish_periods,num_fish_incidents,tag_flags,year,tag_region,nage,
  parent,realization_period,realization_region,realization_incident,
  age_flags,tot_tag_catch,fish_flags,
  num_real_fish_periods,
  terminal_tag_period,
  parest_flags,
  min_init_tag_period,
  minttp,
  num_pooledtagfish_incidents,
  tag_shlen,
  min_tag_year,
  nyears,
  tag_filen,
  tag_nlint,
  initial_tag_release_by_length,
  num_fisheries,
  num_tagfish_incidents,
  obstagcatch_by_length,
  pooledobstagcatch_by_length,
  pooledtot_tag_catch,
  initial_tag_year,
  min_tag_age1,
  terminal_tag_year,
  min_tag_age4,
  min_tag_age5,
  min_tag_age6,
  min_tag_age,
  grouped_fishery_projection_flag);

  if (pmsd)
  {
    tmp.pmsd=new xxxmspd;
    tmp.pmsd->num_species=pmsd->num_species;
    tmp.pmsd->num_real_regions=pmsd->num_real_regions;
    tmp.pmsd->region_species_pointer=pmsd->region_species_pointer;
    tmp.pmsd->tag_species_pointer=pmsd->tag_species_pointer;
    tmp.pmsd->region_bounds=pmsd->region_bounds;
  }
 */
  xxxtags tmp=xxxtags::xxxtags();
  return tmp;
}

dvariable xxxtags::fit_tag_returns(void)
{
  dvariable f1=0.0;
 /*
  {
    int sno=ad_comm::pthread_manager->get_slave_number();
    //f1+=norm2(tag_fish_rep);
    f1+=norm2(tagcatch);
    f1+=norm2(obstagcatch);
    return f1;
  }
 */
  
  dvariable f=0.0;
  dvariable gp_pen=0.0;
  int gp_pen_flag=0;
  int fi;
  dvar_matrix obsgroupedcatch;
  dvar_matrix groupedcatch;

  ivector group_flags32=column(fish_flags,32);
  int gsum32=sum(group_flags32);
  int gmax32=Max(group_flags32);
  ivector gp_fish32(1,gmax32);
  ivector iflag(1,gmax32);
  if (gmax32)
  {
    gp_fish32.initialize();
    for (fi=1;fi<=num_fisheries;fi++)
      gp_fish32(group_flags32(fi))=fi;
    if (allocated(obsgroupedcatch))
      obsgroupedcatch.deallocate();
    obsgroupedcatch.allocate(1,gmax32,1,nage);
    if (allocated(groupedcatch))
      groupedcatch.deallocate();
    groupedcatch.allocate(1,gmax32,1,nage);
  }
  else
  {
    if (allocated(obsgroupedcatch))
      obsgroupedcatch.deallocate();
    obsgroupedcatch.allocate(1,num_fisheries,1,nage);
    if (allocated(groupedcatch))
      groupedcatch.deallocate();
    groupedcatch.allocate(1,num_fisheries,1,nage);
  }
  dvariable totobstags=sum(obstagcatch);
  dvariable totpredtags=0.0;

  int mmin,mmax;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  int ng1=ad_comm::pthread_manager->num_in_group(1);
  int sno=ad_comm::pthread_manager->get_slave_number();
  if (ng1>1)
  {
    int gmin=ad_comm::pthread_manager->gmin(1);
    int gmax=ad_comm::pthread_manager->gmax(1);
    int tpt=num_tag_releases/ng1;
    mmin=1+(sno-gmin)*tpt; 

    if (sno>gmin) gp_pen_flag=1;

    if (sno<gmax)
    {
      mmax=mmin+tpt-1;
    } 
    else
    {
      mmax=num_tag_releases;
    }
  }
  if (!gsum32)   // no fishery grouping
  {
    //for (int it=mmin;it<=mmax;it++)
    for (int it=mmin;it<=mmin+1;it++)
    {
      int rmin=1;
      int rmax=num_regions;
      if (pmsd)
      {
        int cs=pmsd->tag_species_pointer(it);
        rmin=pmsd->region_bounds(cs,1);
        rmax=pmsd->region_bounds(cs,2);
      }
      for (int ir=rmin;ir<=rmax;ir++)
      {
        int ub;
        if (!age_flags(96))
          ub=num_fish_periods(ir);
        else
          ub=terminal_tag_period(it,ir);
        // DF  july 14 05
        if (ub>num_real_fish_periods(ir))
        {
          ub=num_real_fish_periods(ir);
        }
        for (int ip=initial_tag_period(it,ir);ip<=ub;ip++)
        {
          for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
          {
            if (fishery_projection_flag(ir,ip,fi)==0)
            {
              dvar_vector& tc=tagcatch(it,ir,ip,fi);
              int jmin=tc.indexmin();
              for (int j=jmin;j<=nage;j++)
              {
                if (tagcatch(it,ir,ip,fi,j)<0)
                {
                  cerr << tagcatch(it,ir,ip,fi,j) << endl;
                }
                if (tagcatch(it,ir,ip,fi,j)>1000)
                {
                  cerr << tagcatch(it,ir,ip,fi,j) << endl;
                }
              }
              int pp1=parent(ir,ip,fi);
              dvar_vector rtc;
              if (age_flags(198))
                rtc=tag_rep_rate(it,ir,ip,fi)*tagcatch(it,ir,ip,fi);
              else
                rtc=rep_rate(ir,ip,fi)*tagcatch(it,ir,ip,fi);
          
              totpredtags+=sum(rtc);
              switch (parest_flags(111))
              {
                case 0:
                  f+=sum(elem_div(square(obstagcatch(it,ir,ip,fi)-rtc),
                     .01+rtc));
                  break;
                case 1:
                  f-=sum(log(exp(elem_div(
                    square(obstagcatch(it,ir,ip,fi)-rtc),
                    -.01-rtc ))+0.01));
                  break;
                case 2:
                {
                  dvar_vector lrtc=log(1.e-11+rtc);
                    f+=sum(rtc) - obstagcatch(it,ir,ip,fi)*lrtc;
               // for (int i=1;i<=nage;i++)
                for (int j=jmin;j<=nage;j++)
                      f+=gammln(obstagcatch(it,ir,ip,fi,j)+1.0);
                }
                  break;
                case 3:
                  {
                    dvariable a=fish_pars(4,pp1)+50.0001;
                    rtc+=1.e-11;
                    int ns=rtc.indexmax()-rtc.indexmin()+1; 
                    dvar_vector ap=log(a+rtc);
                    f+=sum(a*ap)+obstagcatch(it,ir,ip,fi)*ap;
                    f-=ns*a*log(a)+obstagcatch(it,ir,ip,fi)*log(rtc);
                    f-=sum(gammln(a+obstagcatch(it,ir,ip,fi)));
                    f+=sum(gammln(obstagcatch(it,ir,ip,fi)+1.0));
                    f+=ns*gammln(a);
                  }
    
                  break;
                case 4:
                  {
                    rtc+=1.e-11;
                    dvar_vector a=(fish_pars(4,pp1)+50.0001)*rtc;
                    //dvar_vector a=(fish_pars(4,pp1)+50.0001)*sqrt(rtc);
                    int ns=rtc.indexmax()-rtc.indexmin()+1; 
                    dvar_vector ap=log(a+rtc);
                    f+=a*ap+obstagcatch(it,ir,ip,fi)*ap;
                    f-=a*log(a)+obstagcatch(it,ir,ip,fi)*log(rtc);
                    f-=sum(gammln(a+obstagcatch(it,ir,ip,fi)));
                    f+=sum(gammln(obstagcatch(it,ir,ip,fi)+1.0));
                    f+=sum(gammln(a));
                  }
    
                  break;
              default:
                cerr << "Illegal value for parest_flags(111) value = "
                     <<  parest_flags(111)  << endl;
              }
            }
          }
        }
      }
    }
  }
  else   // have grouping
  {
    //dvar_matrix f_by_tag(mmin,mmax,1,10000);
    //ivector icount(mmin,mmax);
    //icount.initialize();
    //f_by_tag.initialize();
    int rmin=1;
    int rmax=num_regions;
    dvar_vector f_by_r(rmin,rmax);
    f_by_r.initialize();
    for (int it=mmin;it<=mmax;it++)
    {
      if (pmsd)
      {
        int cs=pmsd->tag_species_pointer(it);
        rmin=pmsd->region_bounds(cs,1);
        rmax=pmsd->region_bounds(cs,2);
      }


      for (int ir=rmin;ir<=rmax;ir++)
      {
        int ub;
        if (!age_flags(96))
          ub=num_real_fish_periods(ir);
        else
          ub=terminal_tag_period(it,ir);
        // DF  july 14 05
        if (ub>num_real_fish_periods(ir))
        {
          ub=num_real_fish_periods(ir);
        }
        for (int ip=initial_tag_period(it,ir);ip<=ub;ip++)
        {
          if (num_fish_incidents(ir,ip)>0)
          { 
            // deal with the number of age classes for this tag group
            // at this time
            if (allocated(groupedcatch))
              groupedcatch.deallocate();
            if (allocated(obsgroupedcatch))
              obsgroupedcatch.deallocate();
            int jmin1=tagcatch(it,ir,ip,1).indexmin();
            obsgroupedcatch.allocate(1,gmax32,jmin1,nage);
            groupedcatch.allocate(1,gmax32,jmin1,nage);

            groupedcatch.initialize();
            obsgroupedcatch.initialize();
            groupedcatch.initialize();
            iflag.initialize();
            ivector& pi=parent(ir,ip);
            dvector xtmp(1,9);
            for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
            {
              int pp1=pi(fi);
              int pp=group_flags32(pp1);

              dvar_vector rtc;
              if (age_flags(198))
                rtc=tag_rep_rate(it,ir,ip,fi)*tagcatch(it,ir,ip,fi);
              else
                rtc=rep_rate(ir,ip,fi)*tagcatch(it,ir,ip,fi);

              int jmin=rtc.indexmin();
              totpredtags+=sum(rtc);
              iflag(pp)=1;
              obsgroupedcatch(pp)+=obstagcatch(it,ir,ip,fi); 
              groupedcatch(pp)+=rtc;
            }
    
            int ig;
            for (ig=1;ig<=gmax32;ig++)
            {
              if(iflag(ig))
              {
                if (grouped_fishery_projection_flag(ir,ip,ig)==0)
                {
                  switch (parest_flags(111))
                  {
                    case 0:
                      f+=sum(elem_div(
                        square(obsgroupedcatch(ig)-groupedcatch(ig)),
                       .01+groupedcatch(ig) ));
                      break;
                    case 1:
                      f-=sum(log(exp(elem_div(
                        square(obsgroupedcatch(ig)-groupedcatch(ig)),
                        -.01-groupedcatch(ig) ))+0.01));
                      break;
                    case 2:
                      {
                        dvar_vector lrtc=log(1.e-11+groupedcatch(ig));
                          f+=sum(groupedcatch(ig)) - obsgroupedcatch(ig)*lrtc;
                      for (int i=1;i<=nage;i++)
                            f+=gammln(obsgroupedcatch(ig,i)+1.0);
                    }
                      break;
                    case 3:
                      {
                        dvar_vector rtc=1.e-11+groupedcatch(ig);
                        dvariable a=fish_pars(4,gp_fish32(ig))+50.0001;
                        int ns=rtc.indexmax()-rtc.indexmin()+1; 
                        dvar_vector ap=log(a+rtc);
                        f+=sum(a*ap)+obsgroupedcatch(ig)*ap;
                        f-=ns*a*log(a)+obsgroupedcatch(ig)*log(rtc);
                        f-=sum(gammln(a+obsgroupedcatch(ig)));
                        f+=sum(gammln(obsgroupedcatch(ig)+1.0));
                        f+=ns*gammln(a);
                      }
      
                      break;
                    case 4:
                      {
                        // !!! Dave dvar_vector rtc=1.e-10+groupedcatch(ig);
                        dvar_vector obsgroupedcatch1=obsgroupedcatch(ig);
                        dvar_vector rtc=1.e-11+groupedcatch(ig);
                        dvar_vector a=(fish_pars(4,gp_fish32(ig)) +50.0001)*rtc;
                        //dvar_vector a=(fish_pars(4,gp_fish32(ig))+50.0001)*sqrt(rtc);
                        int ns=rtc.indexmax()-rtc.indexmin()+1; 
                        dvar_vector ap=log(a+rtc);
                      
                        //icount(it)++;
                        //f1+=norm2(groupedcatch(ig)-obsgroupedcatch1);
                       
                        f_by_r(ir)+=a*ap+obsgroupedcatch1*ap;
                        f_by_r(ir)-=a*log(a)+obsgroupedcatch1*log(rtc);
                        f_by_r(ir)-=sum(gammln(a+obsgroupedcatch1));
                        f_by_r(ir)+=sum(gammln(obsgroupedcatch1+1.0));
                        f_by_r(ir)+=sum(gammln(a));
                      }
      
                      break;
                    default:
                      cerr << "Illegal value for parest_flags(111) value = "
                         <<  parest_flags(111)  << endl;
                  }
                } 
              }
            }
          }
        }
      }
    }
    //cout << "f_by_r " << f_by_r << endl;
    f+=sum(f_by_r);
  }
  const dvar_vector& a=fish_pars(4)+50.0001;
  //cout << "a = " << a << endl;
  dvar_vector& q=fish_pars(5);
  //cout << "q = " << q << endl;
  if (gp_pen_flag==0)
  {
    if (sum(column(fish_flags,34)))
      gp_pen=grouped_tag_reporting_rate_penalty();
  }
  if (gp_pen_flag==0)
  {
    if (age_flags(105)>0)
    {
      dvariable tot_pen=age_flags(105)/100.*square(totobstags-totpredtags);
      //cout << "Total observed tags = " << totobstags << endl;
      //cout << "Total predicted tags = " << totpredtags << endl;
      //cout << "Total tags penalty =   " << tot_pen << endl;
      f+=tot_pen;
      f1+=tot_pen;
      cout << "slave totpen " << tot_pen << endl;
    }
  }

  if (age_flags(96))
  {
    //if (gp_pen_flag==0)
    {
      //dvariable tmp=fit_pooled_tag_returns();
      //f+=tmp;
      //cout << "slave " << sno << " pooled " << tmp << endl;
    }
  }
  cout << "slave gp_pen " << gp_pen << endl;
  //f+=gp_pen;
  cout << "slave f " << f << endl;
  //f1=0.0;
  return f;
}
dvariable xxxtags::tag_rep_rate
  (int it,int ir,int rp,int fi)
{
   int pp=parent(ir,rp,fi);
   return tag_fish_rep(it,pp);
}

dvariable xxxtags::grouped_tag_reporting_rate_penalty(void)
{
  ivector group_flags=column(fish_flags,34);
  dvariable gp_pen=0.0;
  int fi;
  for (int ir=1;ir<=num_regions;ir++)
  {
    for (int ip=min_init_tag_period(ir);ip<=num_fish_periods(ir);ip++)
    {
      for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
      {
        ivector& pi=parent(ir,ip);
        for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
        {
          for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
          {
            for (int fi1=1;fi1<=fi;fi1++)
            {
              if (group_flags(pi(fi))== group_flags(pi(fi1)))
	      {
                gp_pen+=100.*square(log(
                  (1.e-5+rep_rate(ir,ip,fi))/
                  (1.e-5+rep_rate(ir,ip,fi1)) ));
              }
            }
          }
        }
      }
    }
  }
  return gp_pen;
}
dvariable xxxtags::fit_pooled_tag_returns(void)
{
  //cout << "norm2(pooled_tagcatch) " <<  norm2(pooled_tagcatch) << endl;
  //cout << "norm2(pooledobstagcatch) " << norm2(pooledobstagcatch) << endl;
  int fi;
  ivector group_flags32=column(fish_flags,32);
  int gsum32=sum(group_flags32);
  int gmax32=Max(group_flags32);
  ivector gp_fish32(1,gmax32);
  ivector iflag(1,gmax32);
  dvar_matrix pooledobsgroupedcatch;
  dvar_matrix pooledgroupedcatch;
  if (gmax32)
  {
    gp_fish32.initialize();
    for (fi=1;fi<=num_fisheries;fi++)
      gp_fish32(group_flags32(fi))=fi;
    pooledobsgroupedcatch.allocate(1,gmax32,1,nage);
    pooledgroupedcatch.allocate(1,gmax32,1,nage);
  }
  else
  {
    pooledobsgroupedcatch.allocate(1,num_fisheries,1,nage);
    pooledgroupedcatch.allocate(1,num_fisheries,1,nage);
  }
  pooledobsgroupedcatch.initialize();
  pooledgroupedcatch.initialize();

  dvariable f=0.0;
  dvariable gp_pen=0.0;
  dvar_vector& rep_rate1=fish_pars(3);
  if (!gsum32) // no grouping
  {
    for (int ir=1;ir<=num_regions;ir++)
    {
      for (int ip=minttp(ir)+1;ip<=num_real_fish_periods(ir);ip++)
      {
        for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
        {
          if (fishery_projection_flag(ir,ip,fi)==0)
          {
            for (int j=1;j<=nage;j++)
            {
              if (pooled_tagcatch(ir,ip,fi,j)<0)
              {
                cerr << pooled_tagcatch(ir,ip,fi,j) << endl;
              }
              int pp1=parent(ir,ip,fi);
              const dvar_vector& xrtc=rep_rate(ir,ip,fi)*pooled_tagcatch(ir,ip,fi);
              dvar_vector& rtc=(dvar_vector&) xrtc;
              switch (parest_flags(111))
  	      {
              case 0:
                f+=sum(elem_div(square(pooledobstagcatch(ir,ip,fi)-rtc),
                   .01+rtc));
                break;
              case 1:
                f-=sum(log(exp(elem_div(
                  square(pooledobstagcatch(ir,ip,fi)-rtc),
                  -.01-rtc ))+0.01));
                break;
              case 2:
  	        {
  	          dvar_vector lrtc=log(1.e-10+rtc);
                    f+=sum(rtc) - pooledobstagcatch(ir,ip,fi)*lrtc;
  		  for (int i=1;i<=nage;i++)
                    f+=gammln(pooledobstagcatch(ir,ip,fi,i)+1.0);
                }
                break;
              case 3:
                {
                  dvariable a=fish_pars(4,pp1)+50.0001;
                  rtc+=1.e-10;
                  int ns=rtc.indexmax()-rtc.indexmin()+1; 
                  dvar_vector ap=log(a+rtc);
                  f+=sum(a*ap)+pooledobstagcatch(ir,ip,fi)*ap;
                  f-=ns*a*log(a)+pooledobstagcatch(ir,ip,fi)*log(rtc);
                  f-=sum(gammln(a+pooledobstagcatch(ir,ip,fi)));
                  f+=sum(gammln(pooledobstagcatch(ir,ip,fi)+1.0));
                  f+=ns*gammln(a);
                }
                break;
              case 4:
                {
                  rtc+=1.e-10;
                  dvar_vector a=(fish_pars(4,pp1)+50.0001)*rtc;
                  //dvar_vector a=(fish_pars(4,pp1)+50.0001)*sqrt(rtc);
                  int ns=rtc.indexmax()-rtc.indexmin()+1; 
                  dvar_vector ap=log(a+rtc);
                  f+=a*ap+pooledobstagcatch(ir,ip,fi)*ap;
                  f-=a*log(a)+pooledobstagcatch(ir,ip,fi)*log(rtc);
                  f-=sum(gammln(a+pooledobstagcatch(ir,ip,fi)));
                  f+=sum(gammln(pooledobstagcatch(ir,ip,fi)+1.0));
                  f+=sum(gammln(a));
                }
                break;
  
  	      default:
  	        cerr << "Illegal value for parest_flags(111) value = "
  	           <<  parest_flags(111)  << endl;
              }
            }
          }
	}
      }
    }
  }
  else  // grouping
  {
    //ofstream ofsv("slavex");
    int icount=0;
    for (int ir=1;ir<=num_regions;ir++)
    {
      for (int ip=minttp(ir)+1;ip<=num_real_fish_periods(ir);ip++)
      {
        pooledobsgroupedcatch.initialize();
        pooledgroupedcatch.initialize();
        iflag.initialize();
        ivector& pi=parent(ir,ip);
        if (ir==1 && ip==37)
        {
          cout << "HERE" << endl;
        }
        for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
        {
          int pp1=pi(fi);
          int pp=group_flags32(pp1);
          const dvar_vector& rtc=rep_rate(ir,ip,fi)*pooled_tagcatch(ir,ip,fi);
          iflag(pp)=1;

          if (sum(pooledobstagcatch(ir,ip,fi))< -1.0)
          {
            cout << "XHERE" << endl;
          }
          pooledobsgroupedcatch(pp)+=pooledobstagcatch(ir,ip,fi);

          pooledgroupedcatch(pp)+=rtc;
        }

        for (fi=1;fi<=gmax32;fi++)
        {
          if (grouped_fishery_projection_flag(ir,ip,fi)==0)
          {
            if(iflag(fi))
            {
              switch (parest_flags(111))
              {
              case 0:
                f+=sum(elem_div(
                  square(pooledobsgroupedcatch(fi)-pooledgroupedcatch(fi)),
                 .01+pooledgroupedcatch(fi) ));
                break;
              case 1:
                f-=sum(log(exp(elem_div(
                  square(pooledobsgroupedcatch(fi)-pooledgroupedcatch(fi)),
                  -.01-pooledgroupedcatch(fi) ))+0.01));
                break;
              case 2:
                {
                  dvar_vector lrtc=log(1.e-10+pooledgroupedcatch(fi));
                  f+=sum(pooledgroupedcatch(fi))
                    - pooledobsgroupedcatch(fi)*lrtc;
                  for (int i=1;i<=nage;i++)
                  f+=gammln(pooledobsgroupedcatch(fi,i)+1.0);
                }
                break;
              case 3:
                {
                  dvar_vector rtc=1.e-10+pooledgroupedcatch(fi);
                  dvariable a=fish_pars(4,gp_fish32(fi))+50.0001;
                  int ns=rtc.indexmax()-rtc.indexmin()+1; 
                  dvar_vector ap=log(a+rtc);
                  f+=sum(a*ap)+pooledobsgroupedcatch(fi)*ap;
                  f-=ns*a*log(a)+pooledobsgroupedcatch(fi)*log(rtc);
                  f-=sum(gammln(a+pooledobsgroupedcatch(fi)));
                  f+=sum(gammln(pooledobsgroupedcatch(fi)+1.0));
                  f+=ns*gammln(a);
                }
                break;
              case 4:
                {
                  // !! Dave dvar_vector rtc=1.e-10+pooledgroupedcatch(fi);
                  dvar_vector rtc=1.e-10+pooledgroupedcatch(fi);
                  dvar_vector a=(fish_pars(4,gp_fish32(fi))+50.0001)*rtc;
                  //dvar_vector a=(fish_pars(4,gp_fish32(fi))+50.0001)*sqrt(rtc);
                  int ns=rtc.indexmax()-rtc.indexmin()+1; 
                  dvar_vector ap=log(a+rtc);
                  dvariable f1=0.0;
                  if (++icount==156)
                  {
                    cout << "HERE" << endl;
                  }
                  f1+=a*ap+pooledobsgroupedcatch(fi)*ap;
                  f1-=a*log(a)+pooledobsgroupedcatch(fi)*log(rtc);
                  f1-=sum(gammln(a+pooledobsgroupedcatch(fi)));
                  f1+=sum(gammln(pooledobsgroupedcatch(fi)+1.0));
                  f1+=sum(gammln(a));
                  f+=f1;
                  //ofsv << f1 << " " << f << endl;
                }
                break;
  
              default:
                cerr << "Illegal value for parest_flags(111) value = "
                     <<  parest_flags(111)  << endl;
              }
            } 
          }
        }
      }
    }
  }
  //cout << norm2(pooledgroupedcatch) << endl;
  //cout << norm2(pooledobsgroupedcatch) << endl;
  f+=gp_pen;
  //check_derivative_values("Bpos0");
  return f;
}
void xxxtags::var_convert_tag_lengths_to_age(void)
{
  initial_tag_release_by_age.initialize();
  int mmin,mmax;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  {
    int mmin=initial_tag_release_by_length.indexmin();
    int mmax=initial_tag_release_by_length.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      int jmin=initial_tag_release_by_length(i).indexmin();
      int jmax=initial_tag_release_by_length(i).indexmax();
      for (int j=jmin;j<=jmax;j++)
      {
        if (initial_tag_release_by_length(i,j)<0.0)
        {
          sleep(2);
          cerr << "This can't happen "  << setprecision(16)
               << initial_tag_release_by_length(i,j)<< endl;
          ad_exit(1);
        }
      }
    }
  }
 /*
  int ng1=ad_comm::pthread_manager->num_in_group(1);
  int sno=ad_comm::pthread_manager->get_slave_number();
  if (ng1>1)
  {
    int gmin=ad_comm::pthread_manager->gmin(1);
    int gmax=ad_comm::pthread_manager->gmax(1);
    int tpt=num_tag_releases/ng1;
    mmin=1+(sno-gmin)*tpt; 

    if (sno>gmin) gp_pen_flag=1;

    if (sno<gmax)
    {
      mmax=mmin+tpt-1;
    } 
    else
    {
      mmax=num_tag_releases;
    }
  }
 */
  if (!pmsd)
  {
    for (int it=mmin;it<=mmax;it++)
    {
      ivector& itrl=initial_tag_release_by_length(it);
      for (int il=1;il<=tag_nlint;il++)
      {
        if (itrl(il))
        {        
          double len=tag_shlen+(il-0.5)*tag_filen;
          dvariable age;
          if (!parest_flags(175) && !parest_flags(174))
          {
            age=age_at_length_calc(len,vb_coff,nage,parest_flags);
          }
          else
          {
            cout << "error" << endl;
            ad_exit(1);
            age=age_at_length_calcxx(len,gml,nage+1);
          }
          double cage=value(age);
          if (cage<=1)
          {
            initial_tag_release_by_age(it,1)+=itrl(il);
          }
          else if (cage>=nage)
          {
            initial_tag_release_by_age(it,nage)+=itrl(il);
          }
          else
          {
            dvariable sf;
            sf=daves_kludge1(age);
            int jj=int(cage);
            dvariable tp= sf*itrl(il);
  
            initial_tag_release_by_age(it,jj)+=
              itrl(il);
            initial_tag_release_by_age(it,jj)-=tp;
  
            initial_tag_release_by_age(it,jj+1)+=tp;
          }
        } 
      }
    }
  }
  else
  {
    cout << "error" << endl;
    ad_exit(1);
    for (int it=mmin;it<=mmax;it++)
    {
      int isp=pmsd->tag_species_pointer(it);
      //int offset=4*(isp-2);
        
      ivector& itrl=initial_tag_release_by_length(it);
      for (int il=1;il<=tag_nlint;il++)
      {
        if (itrl(il))
        {        
          double len=tag_shlen+(il-0.5)*tag_filen;
          dvariable age;
          if (!parest_flags(175) && !parest_flags(174))
          {
            if (isp==1)
            {
              age=age_at_length_calc(len,vb_coff,nage,parest_flags);
            }
            else
            {
              dvar_vector tvb=pmsd->vb_coff(isp);
              age=age_at_length_calc(len,tvb,nage,parest_flags);
            }
          }
          else
          {
            cout << "can't get here" << endl;
            age=age_at_length_calcxx(len,gml,nage+1);
          }
          double cage=value(age);
          if (cage<=1)
          {
            initial_tag_release_by_age(it,1)+=itrl(il);
          }
          else if (cage>=nage)
          {
            initial_tag_release_by_age(it,nage)+=itrl(il);
          }
          else
          {
            dvariable sf;
            sf=daves_kludge1(age);
            int jj=int(cage);
            dvariable tp= sf*itrl(il);
  
            initial_tag_release_by_age(it,jj)+=
              itrl(il);
            initial_tag_release_by_age(it,jj)-=tp;
  
            initial_tag_release_by_age(it,jj+1)+=tp;
          }
        } 
      }
    }
  }
  {
    int mmin=initial_tag_release_by_age.indexmin();
    int mmax=initial_tag_release_by_age.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      int jmin=initial_tag_release_by_age(i).indexmin();
      int jmax=initial_tag_release_by_age(i).indexmax();
      for (int j=jmin;j<=jmax;j++)
      {
        if (initial_tag_release_by_age(i,j)<0.0)
        {
          sleep(2);
          cerr << "This can't happen "  << setprecision(16)
               << initial_tag_release_by_age(i,j)<< endl;
          ad_exit(1);
        }
      }
    }
  }
}
dvariable xxxtags::xtag_catch_equations_calc_pooled(dvar_vector& sv)
{
  int break_flag=0;
  ivector tmp_mp(1,num_regions);
  dvariable ffpen=0.0;
  epooled_tagnum_fish_recr.initialize();
  pooledtagN=-20;
  int it;
  int mmin,mmax;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  int ng1=ad_comm::pthread_manager->num_in_group(1);
  int sno=ad_comm::pthread_manager->get_slave_number();
  if (ng1>1)
  {
    int gmin=ad_comm::pthread_manager->gmin(1);
    int gmax=ad_comm::pthread_manager->gmax(1);
    int tpt=num_tag_releases/ng1;
    mmin=1+(sno-gmin)*tpt; 
    if (sno<gmax)
    {
      mmax=mmin+tpt-1;
    } 
    else
    {
      mmax=num_tag_releases;
    }
  }
  for (int it=mmin;it<=mmax;it++)
  {
    get_initial_tag_population(sv,it);
    //get_initial_tag_population_test(sv,it);

    int current_year=tag_year(it);
    ivector rip(1,num_regions);
    rip=initial_tag_period(it);
    int finished_flag=0;
    int eflag=0;
    int ir;
    for (ir=1;ir<=num_regions;ir++)
    {
      tagnum_fish(it,ir)=-20.0;
    }
    for (ir=1;ir<=num_regions;ir++)
    {
      tagnum_fish(it,ir,rip(ir))=tagN(it,ir,year(ir,rip(ir)));
    }
    do
    {
      finished_flag=1;
      eflag=0;
      for (int ir=1;ir<=num_regions;ir++)
      {
        break_flag=0;
        int& ip=rip(ir);
        do
        {
          if ( ip>=num_fish_periods(ir) || ip>terminal_tag_period(it,ir) ) 
          {
            eflag=1;
            break;
          }
          finished_flag=0;
          if (ip < terminal_tag_period(it,ir))
          {
            if (year(ir,ip+1)==year(ir,ip))
            { 
              if (!num_fish_incidents(ir,ip) || !tag_flags(it,1) || ip >= initial_tag_period(it,ir)+tag_flags(it,1))
              {
                tagnum_fish(it,ir,ip+1)=tagnum_fish(it,ir,ip)-tot_mort(ir,ip);
              }
              else
              {
                do_newton_raphson_for_tags(it,ir,ip,ffpen);
                tagnum_fish(it,ir,ip+1)=tagnum_fish(it,ir,ip)-nrtm(it,ir,ip);
              }
              tagnum_fish(it,ir,ip+1)=tagnum_fish(it,ir,ip)-tot_mort(ir,ip);
            }
            else
            {
              if (!num_fish_incidents(ir,ip) || !tag_flags(it,1) || ip >= initial_tag_period(it,ir)+tag_flags(it,1))
              {
                dvar_vector & tnf=tagnum_fish(it,ir,ip);
                int jmin=tnf.indexmin();
                if (nage>2 && jmin<nage-1)
                  --tagnum_fish(it,ir,ip+1)(jmin+1,nage-1)
                    =tnf(jmin,nage-2)
                    -tot_mort(ir,ip)(jmin,nage-2);
                  //--tagnum_fish(it,ir,ip+1)(2,nage-1)
                  //  =tagnum_fish(it,ir,ip)(1,nage-2)
                  //  -tot_mort(ir,ip)(1,nage-2);
       
                if (jmin<nage)
                {
                  tagnum_fish(it,ir,ip+1,nage) 
                    = log(mfexp(tagnum_fish(it,ir,ip,nage)-tot_mort(ir,ip,nage))
                    + mfexp(tnf(nage-1)-tot_mort(ir,ip,nage-1)));
                }
                else
                {
                  tagnum_fish(it,ir,ip+1,nage) 
                    = tnf(nage)-tot_mort(ir,ip,nage);
                }
              }
              else
              {
                do_newton_raphson_for_tags(it,ir,ip,ffpen);

                int minage=nrtm(it,ir,ip).indexmin();
                if (nage>minage+1)
                  --tagnum_fish(it,ir,ip+1)(minage+1,nage-1)
                   =tagnum_fish(it,ir,ip)(minage,nage-2)
                   -nrtm(it,ir,ip)(minage,nage-2);
       
                tagnum_fish(it,ir,ip+1,nage) 
                  = log( 1.e-20
                     +(mfexp(tagnum_fish(it,ir,ip,nage)-nrtm(it,ir,ip,nage))
                      )
                  + mfexp(tagnum_fish(it,ir,ip,nage-1)-nrtm(it,ir,ip,nage-1)));
              }
            }
          }
          else
          {
            eflag=1;
            if (!tag_flags(it,1) || ip >= initial_tag_period(it,ir)+tag_flags(it,1))
            {
              int jmin=tagnum_fish(it,ir,ip).indexmin();
              
              if (nage>2 && jmin<nage-1)
                --epooled_tagnum_fish_recr(ir,ip+1)(jmin+1,nage-1)
                  +=mfexp(tagnum_fish(it,ir,ip)(jmin,nage-2)
                  -tot_mort(ir,ip)(jmin,nage-2));
   
              if (nage>2 && jmin<nage)
                epooled_tagnum_fish_recr(ir,ip+1,nage) 
                  += mfexp(tagnum_fish(it,ir,ip,nage)-tot_mort(ir,ip,nage))
                  + mfexp(tagnum_fish(it,ir,ip,nage-1)-tot_mort(ir,ip,nage-1));
              else
                epooled_tagnum_fish_recr(ir,ip+1,nage) 
                  += mfexp(tagnum_fish(it,ir,ip,nage)-tot_mort(ir,ip,nage));
            }
            else
            {
              do_newton_raphson_for_tags(it,ir,ip,ffpen);

              if (nage>2)
                --epooled_tagnum_fish_recr(ir,ip+1)(2,nage-1)
                 +=mfexp(tagnum_fish(it,ir,ip)(1,nage-2)
                 -nrtm(it,ir,ip)(1,nage-2));
   
              epooled_tagnum_fish_recr(ir,ip+1,nage) 
                += mfexp(tagnum_fish(it,ir,ip,nage)-nrtm(it,ir,ip,nage))
                + mfexp(tagnum_fish(it,ir,ip,nage-1)-nrtm(it,ir,ip,nage-1));
            }
          }
          if (move_flags(ir,ip))
          {
            tmp_mp(ir)=move_index(ir,ip);
            break_flag=1;
          } 
          ip++;
        }
        while (!break_flag); 
      }
      // move the tags  -- need to deal with pooled ones
      {
        if (num_regions>1 && !eflag)
        {
          check_sanity(tmp_mp);
          dvar_matrix tmp=
            fast_diffusion_calcs(nage,num_regions,tagnum_fish(it),
            Dad(tmp_mp(1)),rip);
          for (int ir=1;ir<=num_regions;ir++)
          {
            tagnum_fish(it,ir,rip(ir))=log(5.e-10+tmp(ir));
          }
        }
      }
    } // need to decide when to quit
    while (!finished_flag);
  }

  const double one_plus=1.e0+1.e-12;
  for (it=mmin;it<=mmax;it++)
  {
    for (int ir=1;ir<=num_regions;ir++)
    {
      for (int ip=initial_tag_period(it,ir);ip<=terminal_tag_period(it,ir);ip++)
      {
        if (!tag_flags(it,1) || 
          ip >= initial_tag_period(it,ir)+tag_flags(it,1))
        {
          for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
          {        
            dvar_vector& tc=tagcatch(it,ir,ip,fi);
            int jmin=tc.indexmin();
            tc=exp(fish_mort_calcs(ir,ip,fi)(jmin,nage)+tagnum_fish(it,ir,ip));
          }
        }
        else
        {
          for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
          {        
            dvar_vector& tc=tagcatch(it,ir,ip,fi);
            int jmin=tc.indexmin();
            tc=exp(nrfm(it,ir,ip,fi)-log(1.e-10+nrtm(it,ir,ip))+
              log(one_plus-nrsurv(it,ir,ip)(jmin,nage))+tagnum_fish(it,ir,ip));
          }
        }
      }
    }
  }
/*
# if defined(COUNT_FISH)
  print_tag_accounting_info();
  exit(1);
#endif
*/
  return ffpen;
}
void xxxtags::do_newton_raphson_for_tags(int it,int ir,int ip,
  dvariable& _ffpen)
{
  dvariable ffpen=0.0;
  int jmin=tagnum_fish(it,ir,ip).indexmin();
  const dvar_vector& enf=mfexp(tagnum_fish(it,ir,ip));
  dvariable tot_num_fish=sum(enf);
  double nfi=num_fish_incidents(ir,ip);
  dvar_matrix sel(1,nfi,jmin,nage);
  dvar_matrix logsel(1,nfi,jmin,nage);
  int fi;
  for (fi=1;fi<=nfi;fi++)
  {
    int i=parent(ir,ip,fi);
    int rr=realization_region(i,1);
    int rp=realization_period(i,1);
    int ri=realization_incident(i,1);
    logsel(fi)=incident_sel(rr,rp,ri)(jmin,nage);
    sel(fi)=mfexp(logsel(fi));
  }

  dvar_matrix& fm=nrfm(it,ir,ip);
  dvar_matrix M(1,nfi,1,nfi);
  dvar_matrix C(1,nfi,jmin,nage);
  dvariable tnf=sum(enf);
  //ofsff << tnf << " " << it << " " << ir << " " << ip << endl;
  if (nfi>1)
  {
    //cout <<"tag3.cpp " << nfi << endl;
  }
  dvar_vector actual_tag_catch=
    elem_div(tot_tag_catch(it,ir,ip),1.e-6+rep_rate(ir,ip));
  
  dvariable region_tot_tag_catch=sum(actual_tag_catch);

  const dvar_vector& ctm=nrtm(it,ir,ip)(jmin,nage);
  dvar_vector& tm=(dvar_vector&)ctm;
  int break_flag=0;
  if (region_tot_tag_catch>0)
  {
    dvariable surv_rate=(1.0-region_tot_tag_catch/tnf);
  
    dvar_vector kc(1,nfi);


    double cut=0.2;
    double fringe=0.02;
    if (age_flags(118)>0)
    {
      cut=age_flags(118)/100.;
    }
    if (age_flags(119)>0)
    {
      fringe=age_flags(119)/100.;
    }
    double c2=cut+fringe;

    
    if (surv_rate<=c2)
    {
      dvariable tmp=0.0;
      dvariable ks=fringe+posfun(surv_rate-fringe,cut,tmp);

      double penwt=1.0;
      if (age_flags(117)>0) penwt=age_flags(117)/1.e+8;
      if (age_flags(117)<0) penwt=0.0;
        ffpen+=penwt*tmp;

      if (value(ks)>1.0)
      {
        cout << "fringe " << fringe << " surv rate  " << surv_rate 
             << " cut " << cut << endl;
        cout << "enter number " << endl;
        int num;
        cin >> num;
        cout << "this can't happen ks = " << ks << endl;
        ad_exit(1);
      }
      dvariable kr= (1.0-ks)*tnf/region_tot_tag_catch;
      kc=kr*actual_tag_catch+1.e-10;
    }
    else
    {
      kc=actual_tag_catch+1.e-10;
    }
    dvar_vector qq=elem_div(kc,sel*enf);
    dvar_vector TC(1,nfi);
    int itt=0;
    int badflag=0;
    double normd=0.0;
    do
    {
      // moved M.initialize() to here
      M.initialize();
      int yr=year(ir,ip);  
      dvar_vector Z=qq*sel+mfexp(get_nat_mort_region(ir)(yr)(jmin,nage)
        +fraction(ir,ip));
      dvar_vector S=exp(-Z);
      dvar_vector S1N=elem_prod(1.0-S,enf);
      for (int fi=1;fi<=nfi;fi++)
      {
        dvar_vector t1=elem_div(qq(fi)*sel(fi),Z);
        C(fi)=elem_prod(t1,S1N);
        TC(fi)=sum(C(fi));
        dvariable Dq=sum(C(fi))/qq(fi);
        dvar_vector DZ=qq(fi)*elem_prod(elem_div(sel(fi),Z),enf)-
          elem_prod(C(fi),1.0+1.0/Z);
        M(fi,fi)=Dq;
        for (int fj=1;fj<=nfi;fj++)
        {
          M(fi,fj)+=DZ*sel(fj);
        }
      }
      for (int fi=1;fi<=nfi;fi++)
      {
        if (kc(fi)<1.e-5)
        {
          for (int fj=1;fj<=nfi;fj++)
          {
            M(fi,fj)=0.0;
            M(fj,fi)=0.0;
          }
          M(fi,fi)=1000.0;
        }
      }
      dvar_vector diff=TC-kc;
      normd=norm(value(diff));
      if (break_flag==1) break;
      //cout <<"tag3.cpp " <<  elem_div(diff,TC)  << endl;
      int pflag=1;
      if (!badflag)
      {
        // this is newton raphson for q
        dvar_vector hs=solve(M,diff);
        for (int fi=1;fi<=nfi;fi++)
        {
          if (kc(fi)<1.e-5) hs(fi)=0.0;
        }
        qq-=hs;
       /*
        int mmin=qq.indexmin();
        int mmax=qq.indexmax();
        dvariable fp1=0.0;
        for (int i=mmin;i<=mmax;i++)
        {
          qq(i)=posfun(qq(i),1.e-10,fp1);
        }
        ffpen+=fp1;
       */
        //pflag=check_pos(qq,nfi);
        if (!pflag)
        {
          dvariable tmp=0.0;
          throw function_minimizer_exception();
          badflag=1;
          qq+=inv(M)*diff;
          qq=elem_div(qq,mfexp(elem_div(inv(M)*diff,qq)));
        }
        else
        {
          itt++;
        }
      }
      else
      {
        // this i newton raphson for log(q)
        qq=elem_div(qq,1.e-20+mfexp(elem_div(inv(M)*diff,qq)));
        //cout << " " << qq(1);
        itt++;
        pflag=check_pos(qq,nfi);
      }
      if ( (itt>8 && pflag && !badflag) || (itt>8 && pflag) || normd<1.e-6 )break_flag=1;
    }
    while(1);
    dvariable fp1=0.0;
    int mmin=qq.indexmin();
    int mmax=qq.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      qq(i)=posfun(qq(i),1.e-10,fp1);
    }
    ffpen+=fp1;
    if (normd>.05)
    {
      cout << "difficult tag NR B " << normd;
      cout << "  it= " << it ;
      cout << "  ir= " << ir ;
      cout << "  ip= " << ip << endl;
      cout << "Predicted tag catch           " << setw(10) << setprecision(2) << setfixed() << TC  << endl; 
      cout << "Expanded observed tag catch kc" << setw(10) << setprecision(2) << setfixed() <<  kc << endl;
      cout << "total number of tags present  " << setw(10) << setprecision(2) << setfixed() <<  tnf << endl;
    }
    //cout <<"tag3.cpp " << endl;
    dvar_vector tmpFF=log(qq);
    for (fi=1;fi<=nfi;fi++)
    {
      fm(fi)(jmin,nage)=logsel(fi)+tmpFF(fi);
    }
    tm.initialize();
    for (fi=1;fi<=num_fish_incidents(ir,ip);fi++) // Loop over fishing
    {                                         // incidents for this period
      tm+=mfexp(fm(fi));
    }
    tm+=mfexp(get_nat_mort_region(ir)(year(ir,ip))(jmin,nage)
      +fraction(ir,ip));
  }
  else
  {
    for (fi=1;fi<=nfi;fi++)
    {
      fm(fi)=-10.0;
    }
    tm=mfexp(get_nat_mort_region(ir)(year(ir,ip))(jmin,nage)
      +fraction(ir,ip));
  }
  nrsurv(it,ir,ip)=mfexp(-tm);
  switch (it)
  {
  case 72:
  case 21:
  case 112:
    break;
  default:
    ;
    _ffpen+=ffpen;
  }
}
void xxxtags::xpooled_tag_catch_equations_calc(dvar_vector& sv)
{
  double one_plus=1.e0+1.e-10;
  int current_year=min_tag_year;
  ivector rip(1,num_regions);
  rip=minttp+1;
  int ir;
  for (int i=1;i<=num_regions;i++)
  {
    pooled_tagnum_fish(i)=-50.;
  }
  
  {
    int mmin=pooledtagN.indexmin();
    int mmax=pooledtagN.indexmax();
    for (int i1=mmin;i1<=mmax;i1++)
    {
      if (allocated(pooledtagN(i1)))
      {
        int mmin=pooledtagN(i1).indexmin();
        int mmax=pooledtagN(i1).indexmax();
        for (int i2=mmin;i2<=mmax;i2++)
        {
          if (allocated(pooledtagN(i1,i2)))
          {
            pooledtagN(i1,i2)=-30.;
          }
        }
      }
    }            
  }
  int finished_flag=0;
  int break_flag=0;
  int nomoveflag=0;

  ivector tmp_mp(1,num_regions);
  ivector add_flag(1,num_regions);
  add_flag.initialize();
  {
    int mmin=pooled_tagnum_fish.indexmin();
    int mmax=pooled_tagnum_fish.indexmax();
    for (int i1=mmin;i1<=mmax;i1++)
    {
      if (allocated(pooled_tagnum_fish(i1)))
      {
        int mmin=pooled_tagnum_fish(i1).indexmin();
        int mmax=pooled_tagnum_fish(i1).indexmax();
        for (int i2=mmin;i2<=mmax;i2++)
        {
          if (allocated(pooled_tagnum_fish(i1,i2)))
          {
            pooled_tagnum_fish(i1,i2)=-30.;
          }
        }
      }
    }            
  }
  do
  {
    finished_flag=1;
    for (ir=1;ir<=num_regions;ir++)
    {
      break_flag=0;
      int& ip=rip(ir);
      do
      {

        if (ip>=num_fish_periods(ir)) 
        {
          nomoveflag=1;
          break;
        }
        finished_flag=0;
        if (!add_flag(ir))
        {
          pooled_tagnum_fish(ir,ip)=log(1.e-20+epooled_tagnum_fish_recr(ir,ip)
            +mfexp(pooled_tagnum_fish(ir,ip)));
          add_flag(ir)=1;
        }
        if (year(ir,ip+1)==year(ir,ip))
        {
          pooled_tagnum_fish(ir,ip+1)=
	    log(mfexp(pooled_tagnum_fish(ir,ip)-tot_mort(ir,ip))+
              epooled_tagnum_fish_recr(ir,ip+1));
        }
        else
        {
          pooled_tagnum_fish(ir,ip+1,1)=
            log(1.e-20+epooled_tagnum_fish_recr(ir,ip+1,1));

          pooled_tagnum_fish(ir,ip+1)(2,nage-1)=
            log(1.e-10+
            ++(mfexp(pooled_tagnum_fish(ir,ip)(1,nage-2)-
	        tot_mort(ir,ip)(1,nage-2)))
            + epooled_tagnum_fish_recr(ir,ip+1)(2,nage-1));

          pooled_tagnum_fish(ir,ip+1,nage)=
            log(1.e-10 
             + mfexp(pooled_tagnum_fish(ir,ip,nage-1)-tot_mort(ir,ip,nage-1))
             + mfexp(pooled_tagnum_fish(ir,ip,nage)-tot_mort(ir,ip,nage)) 
             + epooled_tagnum_fish_recr(ir,ip+1,nage));
         } 
         if (move_flags(ir,ip)) 
         {
           tmp_mp(ir)=move_index(ir,ip);
           break_flag=1;
         } 
         ip++;
       }
       while (!break_flag); 
     }
    // move the tags
    {
      if (num_regions>1&& !nomoveflag)
      {
        check_sanity(tmp_mp);
        dvar_matrix tmp=fast_diffusion_calcs(nage,num_regions,
          pooled_tagnum_fish,Dad(tmp_mp(1)),rip);
        for (int ir=1;ir<=num_regions;ir++)
        {
          pooled_tagnum_fish(ir,rip(ir))=log(5.e-10+tmp(ir));
        }
      }
      else
      {
        cout << "Avoided move" << endl;
      }
    }
  } // need to decide when to quit
  while (!finished_flag);


  for (ir=1;ir<=num_regions;ir++)
  {
    for (int ip=minttp(ir)+1;ip<=num_fish_periods(ir);ip++)
    {
      for (int fi=1;fi<=num_pooledtagfish_incidents(ir,ip);fi++)
      {        
        pooled_tagcatch(ir,ip,fi)=
          mfexp(fish_mort_calcs(ir,ip,fi)+pooled_tagnum_fish(ir,ip));
      }
    }
  }
  //greport("leaving pooled_tag_catch_equations_calc");
#if defined(COUNT_FISH)
  {
    dvar_vector ttt(min_tag_year,nyears);
    int iy;
    for (iy=min_tag_year;iy<=nyears;iy++)
    {
      for (int ir=1;ir<=num_regions;ir++)
        for (int j=1;j<=nage;j++)
          ttt(iy)+=exp(pooledtagN(ir,iy,j));
    }
    ofstream ofs("ptagrep");
    ofs << "pooled tags" << endl;
    for (iy=min_tag_year;iy<=nyears;iy++)
    {
      ofs << "year " << iy << "  ";
      ofs << ttt(iy) << endl;
    }
    dvariable ttc=0.0;
    for (int i1=tagcatch.indexmin();i1<=tagcatch.indexmax();i1++)
      for (int j1=1;j1<=num_regions;j1++)
        for (int k1=tagcatch(i1,j1).indexmin();k1<=tagcatch(i1,j1).indexmax();k1++)
         ttc+=sum(tagcatch(i1,j1,k1));
    
    ofs << "total number of tags caught " << endl;
    ofs << ttc << endl;
    ad_exit(1);
  }
#endif
}
dvariable xxxtags::tag_catch_equations_calc_loop_2(void)
{
  int tn=0;
  get_constant_data(tn);
  gradient_structure::set_MAX_NVAR_OFFSET(10000);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(120000000);
  gradient_structure::set_MAX_NVAR_OFFSET(30000);
  gradient_structure gs(100000000);
  adtimer adt1;

  allocate();
  tot_tags_catch();
  do
  {
    pooled_tagcatch.initialize(); 
    pooledobstagcatch.initialize(); 
    int mmin=ad_comm::pthread_manager->gmin(1);
    int mmax=ad_comm::pthread_manager->gmax(1);
    int iflag;
    for (int kk=mmin;kk<=mmax;kk++)
    {
      iflag=get_variables_from_master2(kk);
    }
    if (iflag==1) break;
    var_convert_tag_lengths_to_age();
    adt1.get_elapsed_time_and_reset();
    if (ad_comm::pthread_manager->ngroups>1)
    {
      for (int kk=mmin;kk<=mmax;kk++)
      {
        iflag=get_variables_from_master_1A(kk);
      }
      double tm=adt1.get_elapsed_time_and_reset();
      cout << "in get_variables_from_master_1A time waiting =" << tm << endl;
      if (iflag==1) break;
    }
    //pooled_tagcatch.initialize(); 
    //pooledobstagcatch.initialize(); 
    dvar_vector sv;
    dvariable ffpen=0.0;
    adt1.get_elapsed_time_and_reset();
    dvariable tmp=fit_pooled_tag_returns();
    double tm=adt1.get_elapsed_time_and_reset();
    cout << "fit_tag_returns in loop 2 "  << tmp << endl;
    int nt=0;
    // send results of fit_pooled_tags to master thread
    tmp=0.0;
    ad_comm::pthread_manager->write_lock_buffer(nt);
    ad_comm::pthread_manager->send_dvariable(tmp,nt); 
    ad_comm::pthread_manager->write_unlock_buffer(nt);
    slave_gradcalc();
  }
  while(1);
}


#ifdef __MSVC32__
  dvariable age_at_length_calcxx(double& v,dvar_vector& gml,int nslots);
#else
  dvariable age_at_length_calcxx(const dvariable& v,dvar_vector& gml,int nslots);
#endif

extern mf_pvm_manager * mf_pvm;

void xxxtags::observed_tags_by_age_from_length(void)
{
  obstagcatch1.initialize();
  dvar_vector vbc(1,vb_coff.indexmax());
  dvar_vector vc(1,var_coff.indexmax());
  vbc=vb_coff;
  vc=var_coff;
  dvar_vector sigma(1,nage);
  dvariable rho=exp(-vb_coff(3));
  dvariable vbdiff=vb_coff(2)-vb_coff(1);
  dvariable vbtmp=1-pow(rho,nage-1);

  for (int j=1;j<=nage;j++)
  {
    dvariable tmp=(1.-pow(rho,j-1))/(1.-pow(rho,nage-1));
    sigma(j)=var_coff(1)*exp(var_coff(2)*(-1+2*tmp));
  }
  int mmin,mmax;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  int ng1=ad_comm::pthread_manager->num_in_group(1);
  int sno=ad_comm::pthread_manager->get_slave_number();
  if (ng1>1)
  {
    int gmin=ad_comm::pthread_manager->gmin(1);
    int gmax=ad_comm::pthread_manager->gmax(1);
    int tpt=num_tag_releases/ng1;
    mmin=1+(sno-gmin)*tpt; 

    //if (sno>gmin) gp_pen_flag=1;

    if (sno<gmax)
    {
      mmax=mmin+tpt-1;
    } 
    else
    {
      mmax=num_tag_releases;
    }
  }
  int isold=1;
  for (int it=mmin;it<=mmax;it++)
  {
    int tr=tag_region(it);
    int lb=1;
    int ub=num_regions;
    int is=1;
    if (pmsd)
    {
      is=pmsd->region_species_pointer(tr);
      lb=pmsd->region_bounds(is,1);
      ub=pmsd->region_bounds(is,2);
    }
    if (is !=isold)
    {
      isold=is;
      vbc=get_vb_coff_region(tr);
      rho=exp(-vbc(3));
      vbdiff=vbc(2)-vbc(1);
      vc=get_var_coff_species(is);
      vbtmp=1-pow(rho,nage-1);
      for (int j=1;j<=nage;j++)
      {
        dvariable tmp=(1.-pow(rho,j-1))/(1.-pow(rho,nage-1));
        sigma(j)=vc(1)*exp(vc(2)*(-1+2*tmp));
      }
    }
    for (int ir=lb;ir<=ub;ir++)
    {
      for (int ip=initial_tag_period(it,ir);ip<=num_fish_periods(ir);ip++)
      {
        for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
        {
          if(tot_tag_catch(it,ir,ip,fi))
          {
            int tyear=year(ir,ip);
            int diff=tyear-tag_year(it);
            const ivector& ocbl=ivector(obstagcatch_by_length(it,ir,ip,fi));
            for (int il=1;il<=tag_nlint;il++)
            {
              if (ocbl(il)>0)
              {
                int num_recaps=ocbl(il);
                double len=tag_shlen+(il-0.5)*tag_filen;

                dvariable age=age_at_length_calc(len,rho,vbdiff,
                  vbtmp,vbc,nage,parest_flags);


                double cage=value(age);
                if (cage<=1)
                {
                  int ind=1+diff;
                  if (ind>nage) ind=nage;
                  obstagcatch1(it,ir,ip,fi,ind)+=num_recaps;
                }
                else if (cage+diff>=nage)
                {
                  obstagcatch1(it,ir,ip,fi,nage)+=num_recaps;
                }
                else
                {
                  int jj=int(cage)+diff;
                  dvariable sf;
                  sf=daves_kludge1(age);
                  obstagcatch1(it,ir,ip,fi,jj)+=(1.-sf)*num_recaps;
                  obstagcatch1(it,ir,ip,fi,jj+1)+=sf*num_recaps;
                }
              }
            }
          }
          obstagcatch(it,ir,ip,fi)=obstagcatch1(it,ir,ip,fi);
        }
      }
    }
  }
}

void xxxtags::observed_tags_by_age_from_length_pooled(void)
{
  obstagcatch1.initialize();
  dvar_vector vbc=vb_coff;
  dvar_vector vc=var_coff;
  dvar_vector sigma(1,nage);
  dvariable rho=exp(-vb_coff(3));
  for (int j=1;j<=nage;j++)
  {
    dvariable tmp=(1.-pow(rho,j-1))/(1.-pow(rho,nage-1));
    sigma(j)=vc(1)*exp(vc(2)*(-1+2*tmp));
  }
  int mmin,mmax;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  int ng1=ad_comm::pthread_manager->num_in_group(1);
  int sno=ad_comm::pthread_manager->get_slave_number();
  if (ng1>1)
  {
    int gmin=ad_comm::pthread_manager->gmin(1);
    int gmax=ad_comm::pthread_manager->gmax(1);
    int tpt=num_tag_releases/ng1;
    mmin=1+(sno-gmin)*tpt; 

    //if (sno>gmin) gp_pen_flag=1;

    if (sno<gmax)
    {
      mmax=mmin+tpt-1;
    } 
    else
    {
      mmax=num_tag_releases;
    }
  }
  int isold=1;
  for (int it=mmin;it<=mmax;it++)
  {
    int tr=tag_region(it);
    int lb=1;
    int ub=num_regions;
    int is=1;
    if (pmsd)
    {
      int is=pmsd->region_species_pointer(tr);
      lb=pmsd->region_bounds(is,1);
      ub=pmsd->region_bounds(is,2);
    }
    if (is !=isold)
    {
      isold=is;
      vbc=get_vb_coff_region(tr);
      rho=exp(-vbc(3));
      //vbdiff=vbc(2)-vbc(1);
      vc=get_var_coff_species(is);
      //vbtmp=1-pow(rho,nage-1);
      for (int j=1;j<=nage;j++)
      {
        dvariable tmp=(1.-pow(rho,j-1))/(1.-pow(rho,nage-1));
        sigma(j)=vc(1)*exp(vc(2)*(-1+2*tmp));
      }
    }
    for (int ir=1;ir<=num_regions;ir++)
    {
      for (int ip=initial_tag_period(it,ir);ip<=terminal_tag_period(it,ir);ip++)
      {
        for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
        {
          if(tot_tag_catch(it,ir,ip,fi))
          {
            int tyear=year(ir,ip);
            int diff=tyear-tag_year(it);
            const ivector& ocbl=ivector(obstagcatch_by_length(it,ir,ip,fi));
            for (int il=1;il<=tag_nlint;il++)
            {
              if (ocbl(il)>0)
              {
                int num_recaps=ocbl(il);
                double len=tag_shlen+(il-0.5)*tag_filen;
                dvariable age=age_at_length_calc(len,vbc,nage);
                double cage=value(age);
                if (cage<=1)
                {
                  int ind=1+diff;
                  if (ind>nage) ind=nage;
                  obstagcatch1(it,ir,ip,fi,ind)+=num_recaps;
                }
                else if (cage+diff>=nage)
                {
                  obstagcatch1(it,ir,ip,fi,nage)+=num_recaps;
                }
                else
                {
                  int jj=int(cage)+diff;
                  dvariable sf;
                  sf=daves_kludge(age);
                  obstagcatch1(it,ir,ip,fi,jj)+=(1.-sf)*num_recaps;
                  obstagcatch1(it,ir,ip,fi,jj+1)+=sf*num_recaps;
                }
              }
            }
          }
          obstagcatch(it,ir,ip,fi)=obstagcatch1(it,ir,ip,fi);
        }
      }
    }
  }
  pooledobstagcatch.initialize();

  for (int ir=1;ir<=num_regions;ir++)
  {
    int ipmax=num_fish_periods(ir);  
    for (int ip=minttp(ir)+1;ip<=ipmax;ip++)
    {
      for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
      {
        if (pooledtot_tag_catch(ir,ip,fi))
        {
          int tyear=year(ir,ip);
          const ivector& ocbl=ivector(pooledobstagcatch_by_length(ir,ip,fi));
          for (int il=1;il<=tag_nlint;il++)
          {
            if (ocbl(il)>0)
            {
              int num_recaps=ocbl(il);
              pooledobstagcatch(ir,ip,fi,nage)+=num_recaps;
            }
          }
        }
      }
    }
  }
}
dvar_vector  xxxtags::get_vb_coff_region(int ir)
{
  if (!pmsd)
    return vb_coff;
  else
  {
    int is=pmsd->region_species_pointer(ir);
    if (is==1)
      return vb_coff;
    else
      return pmsd->vb_coff(is);
  }
}
dvar_vector xxxtags::get_var_coff_species(int is)
{
  if (!pmsd)
    return var_coff;
  else
  {
    if (is==1)
      return var_coff;
    else
      return pmsd->var_coff(is);
  }
}

void xxxtags::tot_tags_catch(void)
{
  int mmin,mmax;
  if (mf_pvm->pvm_switch)
  {
    mmin=min_tag_group;
    mmax=max_tag_group;
  }
  else
  {
    mmin=1;
    mmax=num_tag_releases;
  }
  for (int it=mmin;it<=mmax;it++)
  {
    for (int ir=1;ir<=num_regions;ir++)
    {
      int ipmax=num_fish_periods(ir);  
      if (age_flags(96)) ipmax=terminal_tag_period(it,ir);
      for (int ip=initial_tag_period(it,ir);ip<=ipmax;ip++)
      {
        for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
        {
          tot_tag_catch(it,ir,ip,fi)= sum(obstagcatch_by_length(it,ir,ip,fi));
        }
      }
    }
  }
  if (age_flags(96))
  for (int ir=1;ir<=num_regions;ir++)
  {
    for (int ip=minttp(ir)+1;ip<=num_fish_periods(ir);ip++)  
    {
      for (int fi=1;fi<=num_fish_incidents(ir,ip);fi++) 
      {
        if (sum(pooledobstagcatch_by_length(ir,ip,fi))<0.0)
        {
          cout << "HERE" << endl;
        }
        pooledtot_tag_catch(ir,ip,fi)
          = sum(pooledobstagcatch_by_length(ir,ip,fi));
      }
    }
  }
}

void xxxtags::get_constant_data(int tn)
{
  ad_comm::pthread_manager->cread_lock_buffer(tn);
  num_regions=ad_comm::pthread_manager->get_int(tn); 
  num_tag_releases=ad_comm::pthread_manager->get_int(tn); 
  tag_year=ad_comm::pthread_manager->get_ivector(tn); 
  initial_tag_period=ad_comm::pthread_manager->get_imatrix(tn); 
  move_flags=ad_comm::pthread_manager->get_imatrix(tn); 
  move_index=ad_comm::pthread_manager->get_imatrix(tn); 
  num_fish_periods=ad_comm::pthread_manager->get_ivector(tn);
  num_fish_incidents=ad_comm::pthread_manager->get_imatrix(tn); 
  tag_flags=ad_comm::pthread_manager->get_imatrix(tn);  
  year=ad_comm::pthread_manager->get_imatrix(tn); 
  tag_region=ad_comm::pthread_manager->get_ivector(tn); 
  nage=ad_comm::pthread_manager->get_int(tn); 
  parent=ad_comm::pthread_manager->get_i3_array(tn); 
  realization_period=ad_comm::pthread_manager->get_imatrix(tn);
  realization_region=ad_comm::pthread_manager->get_imatrix(tn); 
  realization_incident=ad_comm::pthread_manager->get_imatrix(tn); 
  age_flags=ad_comm::pthread_manager->get_ivector(tn); 
  tot_tag_catch=ad_comm::pthread_manager->get_d4_array(tn);
  fish_flags=ad_comm::pthread_manager->get_imatrix(tn);  
  num_real_fish_periods=ad_comm::pthread_manager->get_ivector(tn); 
  terminal_tag_period=ad_comm::pthread_manager->get_imatrix(tn);
  parest_flags=ad_comm::pthread_manager->get_ivector(tn);
  min_init_tag_period=ad_comm::pthread_manager->get_ivector(tn);
  minttp=ad_comm::pthread_manager->get_ivector(tn);
  num_pooledtagfish_incidents=ad_comm::pthread_manager->get_imatrix(tn);
  tag_shlen=ad_comm::pthread_manager->get_int(tn);
  min_tag_year=ad_comm::pthread_manager->get_int(tn);
  nyears=ad_comm::pthread_manager->get_int(tn);
  tag_filen=ad_comm::pthread_manager->get_int(tn);
  tag_nlint=ad_comm::pthread_manager->get_int(tn);
  initial_tag_release_by_length=ad_comm::pthread_manager->get_imatrix(tn);
  num_fisheries=ad_comm::pthread_manager->get_int(tn);
  num_tagfish_incidents=ad_comm::pthread_manager->get_i3_array(tn);
  obstagcatch_by_length=ad_comm::pthread_manager->get_d5_array(tn);
  pooledobstagcatch_by_length=ad_comm::pthread_manager->get_d4_array(tn);
  pooledtot_tag_catch=ad_comm::pthread_manager->get_d3_array(tn);
  initial_tag_year=ad_comm::pthread_manager->get_ivector(tn); 
  min_tag_age1=ad_comm::pthread_manager->get_i3_array(tn); 
  terminal_tag_year=ad_comm::pthread_manager->get_ivector(tn);
  min_tag_age4=ad_comm::pthread_manager->get_i4_array(tn);
  min_tag_age5=ad_comm::pthread_manager->get_i3_array(tn);
  min_tag_age6=ad_comm::pthread_manager->get_i3_array(tn); 
  min_tag_age=ad_comm::pthread_manager->get_i3_array(tn);
  grouped_fishery_projection_flag=ad_comm::pthread_manager->get_i3_array(tn); 
  ad_comm::pthread_manager->cread_unlock_buffer(tn);
}
void dvar_len_fish_stock_history::send_constant_data(int sno)
{
  ad_comm::pthread_manager->cwrite_lock_buffer(sno);
  ad_comm::pthread_manager->send_int(num_regions,sno);
  ad_comm::pthread_manager->send_int(num_tag_releases,sno);
  ad_comm::pthread_manager->send_ivector(tag_year,sno); 
  ad_comm::pthread_manager->send_imatrix(initial_tag_period,sno); 
  ad_comm::pthread_manager->send_imatrix(move_flags,sno); 
  ad_comm::pthread_manager->send_imatrix(move_index,sno); 
  ad_comm::pthread_manager->send_ivector(num_fish_periods,sno);
  ad_comm::pthread_manager->send_imatrix(num_fish_incidents,sno); 
  ad_comm::pthread_manager->send_imatrix(tag_flags,sno);  
  ad_comm::pthread_manager->send_imatrix(year,sno); 
  ad_comm::pthread_manager->send_ivector(tag_region,sno); 
  ad_comm::pthread_manager->send_int(nage,sno); 
  ad_comm::pthread_manager->send_i3_array(parent,sno); 
  ad_comm::pthread_manager->send_imatrix(realization_period,sno);
  ad_comm::pthread_manager->send_imatrix(realization_region,sno); 
  ad_comm::pthread_manager->send_imatrix(realization_incident,sno); 
  ad_comm::pthread_manager->send_ivector(age_flags,sno); 
  ad_comm::pthread_manager->send_d4_array(tot_tag_catch,sno);
  ad_comm::pthread_manager->send_imatrix(fish_flags,sno);  
  ad_comm::pthread_manager->send_ivector(num_real_fish_periods,sno); 
  ad_comm::pthread_manager->send_imatrix(terminal_tag_period,sno);
  ad_comm::pthread_manager->send_ivector(parest_flags,sno);
  ad_comm::pthread_manager->send_ivector(min_init_tag_period,sno);
  ad_comm::pthread_manager->send_ivector(minttp,sno);
  ad_comm::pthread_manager->send_imatrix(num_pooledtagfish_incidents,sno);
  ad_comm::pthread_manager->send_int(tag_shlen,sno);
  ad_comm::pthread_manager->send_int(min_tag_year,sno);
  ad_comm::pthread_manager->send_int(nyears,sno);
  ad_comm::pthread_manager->send_int(tag_filen,sno);
  ad_comm::pthread_manager->send_int(tag_nlint,sno);
  ad_comm::pthread_manager->send_imatrix(initial_tag_release_by_length,sno);
  ad_comm::pthread_manager->send_int(num_fisheries,sno);
  ad_comm::pthread_manager->send_i3_array(num_tagfish_incidents,sno);
  ad_comm::pthread_manager->send_d5_array(obstagcatch_by_length,sno);
  ad_comm::pthread_manager->send_d4_array(pooledobstagcatch_by_length,sno);
  ad_comm::pthread_manager->send_d3_array(pooledtot_tag_catch,sno);
  ad_comm::pthread_manager->send_ivector(initial_tag_year,sno); 
  ad_comm::pthread_manager->send_i3_array(min_tag_age1,sno); 
  ad_comm::pthread_manager->send_ivector(terminal_tag_year,sno);
  ad_comm::pthread_manager->send_i4_array(min_tag_age4,sno);
  ad_comm::pthread_manager->send_i3_array(min_tag_age5,sno);
  ad_comm::pthread_manager->send_i3_array(min_tag_age6,sno); 
  ad_comm::pthread_manager->send_i3_array(min_tag_age,sno);
  ad_comm::pthread_manager->send_i3_array(grouped_fishery_projection_flag,sno); 
  ad_comm::pthread_manager->cwrite_unlock_buffer(sno);
}
