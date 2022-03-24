// KFtrack program by John Sibert <jsibert@soest.hawaii.edu> (2001)
// Modifications by Anders Nielsen <anielsen@dina.kvl.dk> (2002+3+4+5+6+7)    
// Modifications by Chi Lam <chihinl@usc.edu> (2006+7)    
//
// This version includes: 
//
// Unscented Kalman filter 
// Quadmap 
// Smoothing  
// Minor modification of likelihood function 
// Known recapture position option (but weight is not used anymore)
// first need not to be known 
// error estimates on most probable track 
// Now with SST also ...  
 
GLOBALS_SECTION
  #include <fstream>
  #include <strstream>
  using std::ifstream;
  using std::ofstream;
  using std::ostrstream;
  #include "quadmap.h"
  #include "chol.h"
  #include "nLogNormal.h"
  #include "basics.h"
  #include <math.h>
  #include <fvar.hpp>
  #include <adstring.hpp>
  #include "yrmonday.h"
  #include "trace.h"
  #undef REPORT
  #define REPORT(object) report << #object " = " << object << endl;
  #define MREPORT(object) report << #object ": \n" << object << endl;

  year_month_day_vector sstDates;
  adstring_array filen; 

  list<Quadmap*> qml;  

  // function prototypes
  adstring make_banner();
  double azimuth(const double& y, const double& x);
  dvariable azimuth(const dvariable& y, const dvariable& x);
  dvariable gc_dist(const dvector& y1, const dvar_vector y2);
  int previous_solstice(const int y0, const int m0, const int d0);
  
  // global variables
  const double Mpg = 60.0; // Nautical miles per degree
  const double PiDiv180 = M_PI/180.0;
  const double two_pi = M_PI*2.0;
  const double eps = 1e-8;  //small number to avoid divide by 0
  //const double radius=8.0; 
  const double kappa=0.0;
  const double k1_getSST=3440.06479*M_PI/(G2R)/180.0;
  year_month_day_vector track_dates;
  ofstream clogf("ukfsst.log");
  int u_phase = -1;
  int v_phase = -1;
  int D_phase = -1;
  int bx_phase = -1;
  int by_phase = -1;
  int bsst_phase = -1;
  int vx_phase = -1;
  int vy_phase = -1;
  int vsst_phase=-1;
  int var_struct_phase = -1;
  int a0_phase = -1;
  int b0_phase = -1;
  int r_phase = -1;

  adstring copyright("\n  (c) 2001,2002,2003,2004,2005,2006 John Sibert and Anders Nielsen \n"\
          "  Pelagic Fisheries Research Program, University of Hawaii\n");
  adstring banner = make_banner();

  void X_dv_wave(void){
    verify_identifier_string("aaaa");
    double dftmp=restore_prevariable_derivative();
    dvector_position ppos=restore_dvector_position();
    dvector p=restore_dvector_value(ppos);
    dvar_vector_position wpos=restore_dvar_vector_position();
    double B=restore_double_value(); 
    double T=restore_double_value(); 
    verify_identifier_string("bbbb");
  
    double Bsq=B*B;
  
    dvector dfw=dftmp*(p/B-T/Bsq);
    dfw.save_dvector_derivatives(wpos);
  }
 
DATA_SECTION
  !!cout << banner << endl;
  init_int npoint;
  !!TRACE(npoint)
  init_int release_point
  !!TRACE(release_point)
  init_int recap_point
  !!TRACE(recap_point)
  init_int u_active;
  init_int v_active;
  init_int D_active;
  init_int bx_active;
  init_int by_active;
  init_int bsst_active;
  init_int vx_active;
  init_int vy_active;
  init_int vsst_active;
  init_int a0_active;
  init_int b0_active;
  init_int r_active;

  init_number init_u;
  init_number init_v;
  init_number init_D;
  init_number init_bx;
  init_number init_by;
  init_number init_bsst;  
  init_number init_vx;
  init_number init_vy;
  init_number init_vsst;
  init_number init_a0;
  init_number init_b0;
  init_number init_r;
  init_int var_struct; 
  //init_int cos_errors;
  //init_int dev_errors;
  //init_number vy_dev_penalty_wt;
  
  int stateDim; 
  !! stateDim=2; 
  int nphase;
  vector solar_date(1,npoint);
  int gsolstice;
  init_matrix dat_mat(1,npoint,1,3);
  init_int nobs;
  !! //cout<<nobs<<endl;
  init_matrix obs_mat_data(1,nobs,1,4);
  matrix obs_mat(1,nobs,1,5); 
  !! for(int i=1; i<=4; ++i)obs_mat.colfill(i,column(obs_mat_data,i));

  number start_long;
  !! double minLon=1000, maxLon=-1000; 
  !! for(int i=1; i<=nobs; ++i){
  !!   if(obs_mat(i,2)==1){
  !!     if(obs_mat(i,1)<minLon)minLon=obs_mat(i,1); 
  !!     if(obs_mat(i,1)>maxLon)maxLon=obs_mat(i,1); 
  !!   }
  !! }
  !! start_long = minLon+0.5*(maxLon-minLon);
  !! TRACE(start_long)

  //##################################################################SST-part
  init_int noOfSstFiles;
  !! //cout<<noOfSstFiles<<endl;
  !! filen.allocate(1,noOfSstFiles);
  !! cifstream* dat_in = ad_comm::global_datafile;
  !! double x,y,v;
  !! for(int i=1; i<=noOfSstFiles; ++i){
  !!   *dat_in>>filen(i);
  !!   Quadmap *qm = new Quadmap(-.01,-90.01,360.02,180.02);	
  !!   cout<<filen(i)<<endl;
  !!   ifstream fp_in;
  !!   fp_in.open(filen(i), ios::in); 
  !!   while(fp_in.eof()==0){
  !!     fp_in>>y; fp_in>>x; fp_in>>v;
  !!     qm->add(x,y,v);  
  !!   }
  !!   fp_in.close();
  !!   qml.push_back(qm);
  !! }
  init_imatrix sstdatemat(1,noOfSstFiles,1,3);
  !! sstDates.allocate(1,noOfSstFiles);
  vector sstSolarDate(1,noOfSstFiles);
  !! int gs1 = previous_solstice(sstdatemat(1,1),sstdatemat(1,2),sstdatemat(1,3));
  !! int gs2 = previous_solstice((int)dat_mat(1,1),(int)dat_mat(1,2),(int)dat_mat(1,3));
  !! if(gs1<gs2){gsolstice=gs1;}else{gsolstice=gs2;}
   !! for (int i = 1; i <= noOfSstFiles; i++)
  !! {
  !!    sstDates(i).set(sstdatemat(i,1),sstdatemat(i,2),sstdatemat(i,3));
  !!    sstSolarDate(i) = sstDates(i).get_gregorian() - gsolstice + 1;
  !! }
  !! //for (int i = 1; i <= noOfSstFiles; i++)
  !! //{
  !! //  cout<<sstDates(i).get_year()<<" "<<sstDates(i).get_month()<<" "<<sstDates(i).get_day();
  !! //  cout<<" "<<sstSolarDate(i)<<endl;
  !! //}
  !! //cout<<"size of qml is: "<<qml.size()<<endl;
  //##################################################################END SST-part

  !! track_dates.allocate(1,npoint);
  !! for (int i = 1; i <= npoint; i++)
  !! {
  !!   // convert month day year to date (year_month_day object)
  !!   track_dates(i).set((int)dat_mat(i,1),(int)dat_mat(i,2),(int)dat_mat(i,3));
  !!
  !!   // convert date to days from solstice
  !!   solar_date(i) = track_dates(i).get_gregorian() - gsolstice + 1;
  !! }
  ivector idx1(1,npoint);
  !! idx1.initialize(); 
  ivector idx2(1,npoint);
  !! idx2.initialize();

  !! idx1(1)=1; 
  !! int j=1; 
  !! for(int i=2; i<=nobs; ++i){
  !!   if(fabs(obs_mat(i,4)-obs_mat(i-1,4))>0.5){
  !!     j++;
  !!     idx1(j)=i; 
  !!     idx2(j-1)=i-1;  
  !!   }
  !! }
  !! idx2(npoint)=nobs;
  !! //for (int i = 1; i <= npoint; i++)cout<<idx1(i)<<" "<<idx2(i)<<endl; 
  
  !! for (int i = 1; i <= npoint; i++){
  !!   for(int j=idx1(i); j<=idx2(i); ++j){
  !!     obs_mat(j,5)=solar_date(i);
  !!   }
  !! }

  3darray P(1,npoint,1,stateDim,1,stateDim);
  3darray PP(1,npoint,1,stateDim,1,stateDim);

 LOCAL_CALCS
   nphase = 0;
   if (u_active || v_active || D_active)
   {
     nphase ++;
     if (u_active)
       u_phase = nphase;
     if (v_active)
       v_phase = nphase;
     if (D_active)
       D_phase = nphase;
   } 
   if (vx_active || vy_active || vsst_active || bx_active || by_active || bsst_active)
   {
     nphase ++;
     if (bx_active)
       bx_phase = nphase;
     if (by_active)
       by_phase = nphase;
     if (bsst_active)
       bsst_phase = nphase;
     if (vx_active)
       vx_phase = nphase;
     if (vy_active)
       vy_phase = nphase;
     if (vsst_active)
       vsst_phase = nphase;
   }
   if (var_struct || r_active)
   {
     nphase ++;
     var_struct_phase = nphase;
     if(a0_active)a0_phase=var_struct_phase;
     if(b0_active)b0_phase=var_struct_phase;
     if (r_active)
       r_phase = nphase;
   }
   TTRACE(u_active,u_phase)
   TTRACE(v_active,v_phase)
   TTRACE(D_active,D_phase)
   TTRACE(bx_active,bx_phase)
   TTRACE(by_active,by_phase)
   TTRACE(vx_active,vx_phase)
   TTRACE(vy_active,vy_phase)
   TTRACE(var_struct,var_struct_phase)
   cout<<"Leaving data section ..."<<endl; 

PARAMETER_SECTION
  init_bounded_number uu(-50.0,50.0,u_phase);
  init_bounded_number vv(-50.0,50.0,v_phase);
  init_bounded_number D(0.0,5000.0,D_phase);
  init_bounded_number vx(0.0,50.0,vx_phase);
  init_bounded_number vy(0.0,50.0,vy_phase);
  init_bounded_number vsst(0.0,50.0,vsst_phase);
  init_bounded_number bx(-50.0,50.0,bx_phase);
  init_bounded_number by(-50.0,50.0,by_phase);
  init_bounded_number bsst(-50.0,50.0,bsst_phase);
  init_bounded_number a0(0.0,50.0,a0_phase); 
  init_bounded_number b0(-80.0,80.0,b0_phase);


  init_bounded_number radius(25,1200,r_phase);
  objective_function_value nLogL;
 
  sdreport_number sduu;
  sdreport_number sdvv;
  sdreport_number sdD;
  sdreport_number sdbx;
  sdreport_number sdby;
  sdreport_number sdbsst;
  sdreport_number sdvx;
  sdreport_number sdvy;
  sdreport_number sdvsst;
  sdreport_number sdr;

  matrix X(1,npoint,1,stateDim);
  matrix V(1,npoint,1,stateDim);

  vector lonlat0(1,stateDim);
  !! int gotlon=0; 
  !! int gotlat=0; 
  !! for(int i=1; i<=nobs; ++i){
  !!   if(obs_mat(i,2)==1)gotlon=i; 
  !!   if(obs_mat(i,2)==2)gotlat=i;
  !!   if((gotlon>0)&&(gotlat>0))break;  
  !! }
  !! lonlat0(1)=obs_mat(gotlon,1); 
  !! lonlat0(2)=obs_mat(gotlat,1); 
  

 LOCAL_CALCS
   radius = init_r; 
   uu = init_u;
   vv = init_v;
   D  = init_D;
   bx = init_bx;
   by = init_by;
   bsst = init_bsst;
   vx = init_vx;
   vy = init_vy;
   vsst = init_vsst;
   if (D < eps) 
     D = eps;
   TTRACE(init_D,D)
   if (vx < eps) 
     vx = eps;
   TTRACE(init_vx,vx)
   if (vy < eps) 
     vy = eps;
   TTRACE(init_vy,vy)
   if (vsst < eps) 
     vsst = eps;
   TTRACE(init_vsst,vsst)
   if (var_struct_phase < 0){
     a0 = eps;
     b0 = 0.0;
   }else{
     a0 = init_a0;
     b0 = init_b0;
   }
   cout<<"Leaving parameter section ..."<<endl; 

PROCEDURE_SECTION
  //cout<<uu<<" "<<vv<<" "<<D<<" "<<vx<<" "<<vy<<" "<<vsst<<" ";
  //cout<<bx<<" "<<by<<" "<<bsst<<" "<<a0<<" "<<b0<<" "<<radius<<endl;
  dvar_matrix varx0(1,stateDim,1,stateDim);
  varx0.initialize();
  if(release_point!=1){
    varx0(1,1)=1000;
    varx0(2,2)=1000;
  }  
  dvar_vector x0=zInv(lonlat0); 
  
  //year_month_day testDate;
  //testDate.set(2001,6,1);
  //int testGsolDate= testDate.get_gregorian() - gsolstice + 1;
  //cout<<getSST(testGsolDate,200,20,1.5)<<endl;
  //cout<<solar_date<<endl;
  //cout<<sstSolarDate<<endl;

  nLogL=unscentedKalmanFilter(x0, varx0, obs_mat, idx1, idx2, solar_date, X, V, P, PP, kappa);

  sduu=uu;
  sdvv=vv;
  sdD=D;
  sdbx=bx;
  sdby=by;
  sdbsst=bsst;
  sdvx=vx;
  sdvy=vy;
  sdvsst=vsst;
  sdr=radius;

FUNCTION dvariable wave(const dvar_vector& w, const dvector& p)
  dvector cw=value(w);
  double T=cw*p; 
  double B=sum(cw); 
  double tmp=T/B; 

  dvariable vtmp=nograd_assign(tmp);

  // The derivative list considerations
  save_identifier_string("bbbb"); 
  save_double_value(T); 
  save_double_value(B); 
  w.save_dvar_vector_position();
  p.save_dvector_value();
  p.save_dvector_position();
  vtmp.save_prevariable_position();
  save_identifier_string("aaaa");
  gradient_structure::get()->GRAD_STACK1->
            set_gradient_stack(X_dv_wave);
  return vtmp;

FUNCTION dvariable weight(dvariable& distsq, dvariable& radsq)
  return pow(1.0-pow(distsq/radsq,1.5),3.0); 
  
FUNCTION dvariable getSST(const dvariable& time, dvariable lon, dvariable lat, dvariable rad)
  dvariable sinLatG2R=sin(lat*G2R); 
  dvariable cosLatG2R=cos(lat*G2R);
  dvariable sinLonG2R=sin(lon*G2R); 
  dvariable cosLonG2R=cos(lon*G2R);
  dvariable radsq=rad*rad; 
 
  int whichmin=1; 
  double minval=value(fabs(time-sstSolarDate(1)));
  int i;
  for(i=2; i<=noOfSstFiles; ++i){
    if(value(fabs(time-sstSolarDate(i)))<minval){
      whichmin=i; 
      minval=value(fabs(time-sstSolarDate(i)));
    }
  }  
  i=1;
  list<Quadmap*>::const_iterator qmpos=qml.begin();
  while(i<whichmin){
    i++;
    qmpos++;
  } 
  Quadmap* qmlocal= *qmpos;
  list<Located>::const_iterator pos;
  list<Located> closeby;
  closeby=qmlocal->get(value(lon),value(lat),value(rad)); 
  dvector points(1,closeby.size());
  dvar_vector weights(1,closeby.size()); 
  i=1;
  
  dvariable t1;
  dvariable t2;
  dvariable t3;
  
  double locxG2R;   
  double locyG2R;   
  list<Located>::const_iterator startpos=closeby.begin();
  list<Located>::const_iterator endpos=closeby.end();
  for(pos=startpos; pos!=endpos; ++pos){
    Located loc = (Located)*pos;
    locxG2R=loc.x*G2R;
    locyG2R=loc.y*G2R;
    points(i)=loc.v;
    t1=sinLatG2R*sin(locyG2R)+cosLatG2R*cos(locyG2R)*(cosLonG2R*cos(locxG2R)+sinLonG2R*sin(locxG2R));
    t2=k1_getSST*acos(t1);
    t3=t2*t2;
    weights(i)=weight(t3,radsq);
    i++; 
  }
  dvariable ret=0;
  if(closeby.size()>=1){ 
    ret+=wave(weights,points);
  }
  return ret; 

FUNCTION dvar_vector z(const dvar_vector& alpha)
  dvariable t1, t2;
  dvar_vector ret(1,2);
  t1=alpha(2)/Mpg*PiDiv180;
  t2=Mpg*cos(t1);
  ret(1)=-alpha(1)/t2+start_long;
  ret(2)=alpha(2)/Mpg;
  return ret;

FUNCTION dvar_vector zInv(const dvar_vector& y)
  dvar_vector ret(1,2);
  ret(1)=-(y(1)-start_long)*Mpg*cos(y(2)*PiDiv180);
  ret(2)=y(2)*Mpg;
  return ret;

  //----------------------------------------------------------------------------------
FUNCTION dvar_vector F(const dvar_vector& x, const double& dt)
  int n1=x.indexmin();
  int n2=x.indexmax();
  dvar_vector ret(n1,n2);
  ret=x;
  ret(n1)+=uu*dt;
  ret(n1+1)+=vv*dt;
  return ret;

FUNCTION dvar_matrix Q(const double& dt)
  int stateDim=2;
  dvar_matrix ret(1,stateDim,1,stateDim);
  ret.initialize();
  ret(1,1)=2.0*D*dt;
  ret(2,2)=2.0*D*dt;
  return ret;

FUNCTION dvar_vector G(const dvar_vector& x, const dmatrix& data)
  int maxObsDim=3; 
  int r1=data.rowmin(); 
  int r2=data.rowmax(); 
  dvar_vector tmp(1,maxObsDim);
  tmp(1,2)=z(x);
  funnel_dvariable fsst; 
  ad_begin_funnel();
  fsst=getSST(data(r1,5),tmp(1),tmp(2),radius); 
  tmp(3)=fsst; 
  tmp(1)+=bx; 
  tmp(2)+=by; 
  tmp(3)+=bsst; 
  dvar_vector ret(r1,r2);
  for(int i=r1; i<=r2; ++i)ret(i)=tmp((int)data(i,2));
  return ret;

FUNCTION dvar_vector Glast(const dvar_vector& x, const dmatrix& data)
  int maxObsDim=3; 
  int r1=data.rowmin(); 
  int r2=data.rowmax(); 
  dvar_vector tmp(1,maxObsDim);
  tmp(1,2)=z(x);
  funnel_dvariable fsst; 
  ad_begin_funnel();
  fsst=getSST(data(r1,5),tmp(1),tmp(2),radius);  
  tmp(3)=fsst;
  tmp(3)+=bsst; 
  dvar_vector ret(r1,r2);
  for(int i=r1; i<=r2; ++i)ret(i)=tmp((int)data(i,2));
  return ret;

FUNCTION dvar_matrix R(const dmatrix& data)
  int maxObsDim=3;
  int n1=data.rowmin();
  int n2=data.rowmax();
  dvar_vector tmp(1,maxObsDim);
  tmp(1)=vx*vx; 
  if (var_struct==1){
    int sdx = (int)fmod(data(n1,5),365.25);
    int bdx = (int)(sdx/182.625) + 1;
    dvariable e1 = cos(two_pi*(pow(-1.0,bdx)*b0+data(n1,5))/365.25);
    dvariable e3 = vy*1.0/sqrt(e1*e1+a0);
    tmp(2) = e3*e3;
  }else{
    tmp(2) = vy*vy;
  }
  tmp(3)=vsst*vsst;  
  dvar_matrix ret(n1,n2,n1,n2);
  ret.initialize();
  for(int i=n1; i<=n2; ++i)ret(i,i)=tmp((int)data(i,2));
  return ret;

  //----------------------------------------------------------------------------------

	
FUNCTION dvariable unscentedKalmanFilter(const dvar_vector& x0, const dvar_matrix& varx0, const dmatrix& data, const ivector&  idx1, const ivector& idx2, const dvector& times, dvar_matrix& X, dvar_matrix& V, d3_array& Pall, d3_array& PPall, const double& kappa)
  // -- Figure out the dimensions
  dvector obs=column(data,1);

  int rmin=X.rowmin();
  int rmax=X.rowmax();
  int cmin=X.colmin();
  int cmax=X.colmax();
  int stateDim=cmax-cmin+1;
  int N=rmax-rmin+1;
  dvar_matrix T(1,stateDim,1,stateDim);

  // -- Calculate the weights
  dvector W(0,2*stateDim);
  W(0)=kappa/(stateDim+kappa);
  W(1,2*stateDim)=1.0/(2.0*(stateDim+kappa)); //1,2,...,2*stateDim

  // -- Take care of 0'th Obs
  dvar_matrix Xpoints(0,2*stateDim,cmin,cmax);
  dvar_matrix P(cmin,cmax,cmin,cmax);
  if(release_point==1){
    for(int i=0; i<=(2*stateDim); ++i){
      Xpoints(i)=x0;
    }
    P.initialize();
  }else{
    Xpoints=sigmaPoints(x0,varx0,kappa);
    P=varx0;
  }
  
  X(1)=x0;
  V(1)=diagonal(P);

  dvariable nlogL=0.0;
  for(int k=2; k<=rmax-1; ++k){
    int idxlow=idx1(k);
    int idxhigh=idx2(k);
    dmatrix subData=getSubMat(data,idxlow,idxhigh);
    double dt=times(k)-times(k-1);
    // Next state prediction
    for(int i=0; i<=(2*stateDim); ++i){
      Xpoints(i)=F(Xpoints(i), dt);
    }

    X(k)=weightedVectorMean(Xpoints,W);
    P=weightedCovEst(Xpoints,X(k),W); 
    P+=Q(dt);
    PPall(k)=value(P);
    Xpoints=sigmaPoints(X(k),P,kappa);
    dvar_matrix Ypoints(0,2*stateDim,idxlow,idxhigh);
    for(int i=0; i<=(2*stateDim); ++i){
      Ypoints(i)=G(Xpoints(i), subData);
    }

    dvar_vector Yhat=weightedVectorMean(Ypoints,W);
    dvar_matrix Pyy=weightedCovEst(Ypoints,Yhat,W);
    dvar_matrix Pxy=weightedCov2Est(Xpoints,X(k),Ypoints,Yhat,W);
    dvar_matrix S=Pyy;
    S+=R(subData);
    // -- The out-commented lines are replaced with the two lines below
    // -- to optimize - tested and optimal
    //dvar_matrix K=Pxy*inv(S);
    //dvar_matrix L=choleski_decomp(S);
    
    dvar_matrix L=chol(S);
    dvar_matrix K=trans(fwsolve(L,bksolve(L,trans(Pxy))));

    dvar_vector diffVec(idxlow,idxhigh);
    diffVec=getSubVec(obs,idxlow,idxhigh)-Yhat;

    X(k)+=K*diffVec;
    P-=K*S*trans(K);
    Pall(k)=value(P);

    V(k)=diagonal(P);
    nlogL+=nLogNormalChol(getSubVec(obs,idxlow,idxhigh),Yhat,L);
    Xpoints=sigmaPoints(X(k),P,kappa);
  }
  // Take care of final point
  dmatrix subData=getSubMat(data,idx1(rmax),idx2(rmax));
  double dt=times(rmax)-times(rmax-1);
  // Next state prediction
  for(int i=0; i<=(2*stateDim); ++i){
    Xpoints(i)=F(Xpoints(i), dt);
  }
  X(rmax)=weightedVectorMean(Xpoints,W);
  P=weightedCovEst(Xpoints,X(rmax),W);
  P+=Q(dt);

  PPall(rmax)=value(P);
  Xpoints=sigmaPoints(X(rmax),P,kappa);
  
  dvar_matrix Ypoints(0,2*stateDim,idx1(rmax),idx2(rmax));
  for(int i=0; i<=(2*stateDim); ++i){
    if(recap_point==1){
      Ypoints(i)=Glast(Xpoints(i), subData);
    }else{
      Ypoints(i)=G(Xpoints(i), subData);
    }
  }
  dvar_vector Yhat=weightedVectorMean(Ypoints,W);
  dvar_matrix Pyy=weightedCovEst(Ypoints,Yhat,W);
  dvar_matrix Pxy=weightedCov2Est(Xpoints,X(rmax),Ypoints,Yhat,W);
  dvar_matrix S=Pyy;
  if(recap_point==1){
    if((S.rowmax()-S.rowmin()+1)>2)S(S.rowmax(),S.colmax())+=vsst*vsst; 
  }else{
    S+=R(subData);
  }
  //S+=ZERO -- if fixed
  // -- The out-commented lines are replaced with the two lines below
  // -- to optimize - tested and optimal
  //dvar_matrix K=Pxy*inv(S);
  //dvar_matrix L=choleski_decomp(S);
  dvar_matrix L=chol(S);
  dvar_matrix K=trans(fwsolve(L,bksolve(L,trans(Pxy))));
  dvar_vector diffVec(idx1(rmax),idx2(rmax));
  diffVec=getSubVec(obs,idx1(rmax),idx2(rmax))-Yhat;
  X(rmax)+=K*diffVec;
  P-=K*S*trans(K);
  Pall(rmax)=value(P);
  V(rmax)=diagonal(P);
  nlogL+=nLogNormalChol(getSubVec(obs,idx1(rmax),idx2(rmax)),Yhat,L);
  return nlogL;

REPORT_SECTION
  cout<<"REPORT SECTION BEGIN"<<endl;

  dmatrix Pstar(1,stateDim,1,stateDim);
  Pstar.initialize();
  d3_array Pmpt(1,npoint,1,stateDim,1,stateDim);
  Pmpt.initialize();
  dmatrix mpt(1,npoint,1,stateDim);
  mpt.initialize();
  dvector mptTmp(1,stateDim);
  mptTmp.initialize();
  double dt;
  dvector W(0,2*stateDim);
  W(0)=kappa/(stateDim+kappa);
  W(1,2*stateDim)=1.0/(2.0*(stateDim+kappa));
  mpt(npoint)=value(X(npoint));

  dmatrix tmpt(1,npoint,1,stateDim);
  tmpt.initialize();

  d3_array tPmpt(1,npoint,1,stateDim,1,stateDim);
  tPmpt.initialize();
  Pmpt(npoint)=P(npoint);

  if(recap_point==1){
    tmpt(npoint)=value(z(X(npoint)));
    // tPmpt is already zero
  }else{
    dmatrix SP=value(sigmaPoints(mpt(npoint),Pmpt(npoint),kappa));
    for(int j=0; j<=(2*stateDim); ++j){
      SP(j)=value(z(SP(j)));
    }
    tmpt(npoint)=value(weightedVectorMean(SP,W));
    tPmpt(npoint)=value(weightedCovEst(SP,tmpt(npoint),W));
  }

  for(int i=npoint-1; i>1; --i){
    Pstar=P(i)*inv(PP(i+1));
    dt=solar_date(i+1)-solar_date(i);
    mptTmp(1)=value(uu*dt);
    mptTmp(2)=value(vv*dt);
    mpt(i)=value(X(i)+Pstar*(mpt(i+1)-X(i)-mptTmp));
    Pmpt(i)=value(P(i)+Pstar*(Pmpt(i+1)-PP(i+1))*trans(Pstar));

    dmatrix SP=value(sigmaPoints(mpt(i),Pmpt(i),kappa));
    for(int j=0; j<=(2*stateDim); ++j){
      SP(j)=value(z(SP(j)));
    }
    tmpt(i)=value(weightedVectorMean(SP,W));
    tPmpt(i)=value(weightedCovEst(SP,tmpt(i),W));
  }
  mpt(1)=value(X(1));
  Pmpt(1)=0;
  tmpt(1)=value(z(X(1)));
  tPmpt(1)=0;


  ofstream mptout("mpt.out");
  for(int i=1; i<=npoint; ++i){
    mptout<<solar_date(i)<<" ";
    mptout<<mpt(i,1)<<" "<<mpt(i,2)<<" ";
    mptout<<Pmpt(i,1,1)<<" "<<Pmpt(i,1,2)<<" ";
    mptout<<Pmpt(i,2,1)<<" "<<Pmpt(i,2,2)<<" ";
    mptout<<tmpt(i,1)<<" "<<tmpt(i,2)<<" ";
    mptout<<value(getSST(solar_date(i),tmpt(i,1),tmpt(i,2),radius))<<" ";
    mptout<<tPmpt(i,1,1)<<" "<<tPmpt(i,1,2)<<" ";
    mptout<<tPmpt(i,2,1)<<" "<<tPmpt(i,2,2)<<endl;
  }
  mptout.close();

  ofstream predout("pred.out");
  for(int i=1; i<=npoint; ++i){
    predout<<X(i,1)<<" "<<X(i,2)<<" ";
    predout<<P(i,1,1)<<" "<<P(i,1,2)<<" ";
    predout<<P(i,2,1)<<" "<<P(i,2,2)<<" ";
    if((i!=1)&&(i!=npoint)){
      dmatrix SP=value(sigmaPoints(X(i),P(i),kappa));
      for(int j=0; j<=(2*stateDim); ++j){
        SP(j)=value(z(SP(j)));
      }
      dvector predtmp=value(weightedVectorMean(SP,W));
      dmatrix tPP=value(weightedCovEst(SP,predtmp,W));
      predout<<predtmp(1)<<" "<<predtmp(2)<<" ";
      predout<<value(getSST(solar_date(i),predtmp(1),predtmp(2),radius))<<" ";
      predout<<tPP(1,1)<<" "<<tPP(1,2)<<" ";
      predout<<tPP(2,1)<<" "<<tPP(2,2)<<endl;
    }else{
      predout<<z(X(i))<<" "<<value(getSST(solar_date(i),z(X(i))(1),z(X(i))(2),radius))<<" 0 0 0 0"<<endl;
    }
  }
  predout.close();

  ofstream timeout("time.out");
  for(int i=1; i<=npoint; ++i){
    timeout<<dat_mat(i,1)<<" ";
    timeout<<dat_mat(i,2)<<" ";
    timeout<<dat_mat(i,3)<<" ";
    timeout<<solar_date(i)-solar_date(1)<<endl;
  }
  timeout.close();

  //  ofstream smoothout("smooth.out");
  //  cout<<filen(1)<<endl;
  //  ifstream fp_in;
  //  fp_in.open(filen(1), ios::in);
  //  double x,y,v,s;  
  //  while(fp_in.eof()==0){
  //    fp_in>>y; fp_in>>x; fp_in>>v;
  //    s=value(getSST(sstSolarDate(1),x,y,radius));  
  //    smoothout<<y<<" "<<x<<" "<<v<<" "<<s<<endl; 
  //  }
  //  fp_in.close();
  //  smoothout.close();
  cout<<"REPORT SECTION END"<<endl;

TOP_OF_MAIN_SECTION
  arrmblsize=20000000;
  gradient_structure::set_CMPDIF_BUFFER_SIZE(30000000);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(10000000);
