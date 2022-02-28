GLOBALS_SECTION
  #include "quadmap.h"
  #include <fvar.hpp>
  #include <adstring.hpp>
  #include <strstream>
  using std::ostrstream;
  //#include "newverify.h"
  #include "chol.h"
  #include "nLogNormal.h"
  #include "basics.h"
  #include "vspline.cpp"
  //#include <fstream.h>
  ofstream clogf("program.log");
  #define TRACE(object) clogf<<"line "<<__LINE__<<", file "<<__FILE__<<", "<<#object" =\n "<<object<<endl<<endl; 

  const double Mpg = 60.0;
  const double PiDiv180 = M_PI/180.0;
  int splineAppOrder = 0;  
  const int splineAppOrderMoon = 180; 
  const int nStepFirst=2;
  const double twentyLog10Exp = 8.68588963806503500; //20*log10(e)
  const double k1_getSST=3440.06479*M_PI/(G2R)/180.0;

  adstring_array filen;
  list<Quadmap*> qml;

  vcubic_spline_function setupApp(const dvector& knots, const dvar_vector& qSpar, int extendBy=50){
    double r=0.5;
    int oldN=knots.indexmax()-knots.indexmin()+1;
    int newN=2*extendBy+oldN;
    dvector newKnots(1,newN);
    dvar_vector newQSpar(1,newN);
    double lowKnot=knots(knots.indexmin());
    double higKnot=knots(knots.indexmax());
    dvariable lowVal=qSpar(qSpar.indexmin());
    dvariable higVal=qSpar(qSpar.indexmax());
    dvariable lowDf=qSpar(qSpar.indexmin()+1)-qSpar(qSpar.indexmin());
    lowDf/=knots(knots.indexmin()+1)-knots(knots.indexmin());
    dvariable higDf=qSpar(qSpar.indexmax())-qSpar(qSpar.indexmax()-1);
    higDf/=knots(knots.indexmax())-knots(knots.indexmax()-1);
    double lowDelta=(90.0+lowKnot)/extendBy;
    double higDelta=(90.0-higKnot)/extendBy;
    ofstream appout("approx.out");
    for(int i=1; i<=newN; ++i){
      if(i<=extendBy){
        newKnots(i)=-90+(i-1)*lowDelta;
        newQSpar(i)=lowVal-lowDelta*lowDf*((1.0-pow(r,extendBy-i+2.0))/(1.0-r)-1.0);
      }else{
        if((i>extendBy)&&(i<=(extendBy+oldN))){
          newKnots(i)=knots(i-extendBy-knots.indexmin()+1);
          newQSpar(i)=qSpar(i-extendBy-qSpar.indexmin()+1);
        }else{
          if(i>(extendBy+oldN)){
            newKnots(i)=higKnot+(i-extendBy-oldN)*higDelta;
            newQSpar(i)=higVal+higDelta*higDf*((1.0-pow(r,i-extendBy-oldN+1.0))/(1.0-r)-1.0);
          }
        }
      }  
      appout<<newKnots(i)<<" "<<newQSpar(i)<<" "<<higKnot<<" "<<higDelta<<" "<<higKnot+(i-extendBy)*higDelta<<endl;
    } 
    appout.close();
    vcubic_spline_function ret(newKnots,newQSpar);
    return ret;
  }


  dvar_vector cumsum(const dvar_vector& x){
    RETURN_ARRAYS_INCREMENT();
    int n=x.indexmin();
    int N=x.indexmax(); 
    int i=0;
    dvar_vector ret(n,N); 
    ret(n)=x(n);
    for(i=n+1; i<=N; ++i)ret(i)=ret(i-1)+x(i);
    RETURN_ARRAYS_DECREMENT();
    return ret;
  }

  dvar_vector thetaM(const dvar_vector& y, const dmatrix& data){
    RETURN_ARRAYS_INCREMENT();
    dvar_vector H=column(data,2)-column(data,6)-y(1);
    dvariable t1=y(2)*PiDiv180;
    dvar_vector t2=H*PiDiv180;
    dvariable t3=sin(t1);
    dvariable t4=cos(t1);
    dvar_vector t5=cos(t2);
    dvar_vector t6=t3*column(data,8)+t4*elem_prod(column(data,7),t5);
    dvar_vector t7=asin(t6)/PiDiv180;
    RETURN_ARRAYS_DECREMENT();
    return t7;
  }

  dvector thetaM(const dvector& y, const dmatrix& data){
    dvector H=column(data,2)-column(data,6)-y(1);
    double t1=y(2)*PiDiv180;
    dvector t2=H*PiDiv180;
    double t3=sin(t1);
    double t4=cos(t1);
    dvector t5=cos(t2);
    dvector t6=t3*column(data,8)+t4*elem_prod(column(data,7),t5);
    dvector t7=asin(t6)/PiDiv180;
    return t7;
  }

  dvar_vector thetaS(const dvar_vector& y, const dmatrix& data){
    RETURN_ARRAYS_INCREMENT();
    dvar_vector H=column(data,2)-column(data,3)-y(1);
    dvariable t1=y(2)*PiDiv180;
    dvar_vector t2=H*PiDiv180;
    dvariable t3=sin(t1);
    dvariable t4=cos(t1);
    dvar_vector t5=cos(t2);
    dvar_vector t6=t3*column(data,5)+t4*elem_prod(column(data,4),t5);
    dvar_vector t7=asin(t6)/PiDiv180;
    RETURN_ARRAYS_DECREMENT();
    return t7;
  }

  dvector thetaS(const dvector& y, const dmatrix& data){
    dvector H=column(data,2)-column(data,3)-y(1);
    double t1=y(2)*PiDiv180;
    dvector t2=H*PiDiv180;
    double t3=sin(t1);
    double t4=cos(t1);
    dvector t5=cos(t2);
    dvector t6=t3*column(data,5)+t4*elem_prod(column(data,4),t5);
    dvector t7=asin(t6)/PiDiv180;
    return t7;
  }

  dvar_vector lightTrans(const dvar_vector& x){
    RETURN_ARRAYS_INCREMENT();
    dvar_vector ret=twentyLog10Exp*log(x)+250;
    RETURN_ARRAYS_DECREMENT();
    return ret;
  }

  dvar_vector lightTransInv(const dvar_vector& x){
    RETURN_ARRAYS_INCREMENT();
    dvar_vector ret=exp((x-250.0)/twentyLog10Exp);
    RETURN_ARRAYS_DECREMENT();
    return ret;
  }

  dvariable splineLS(const dvar_vector lonlat, const dvector& obs, const dmatrix& data, vcubic_spline_function& qS, 
                     dvector& knots, dmatrix& ang){
    dvar_vector thS=thetaS(lonlat,data);
    //dvar_vector thM=thetaM(lonlat,data);

    //dvar_vector sun=lightTransInv(qS(thS));
    //dvar_vector predLight=lightTrans(sun);
    dvar_vector predLight=qS(thS);

    //ang(1)=value(thS);
    //ang(2)=obs;
    //ang(3)=value(predLight);
    dvariable ret=sum(square(predLight-obs));   
    return ret;
  }

  dvector calcKnots(dvector lonlat, dmatrix data, int blue, double extendFactor=1.01){
    dvector thS=thetaS(lonlat,data);
    dvector ret(1,splineAppOrder);
    double minA=min(thS);
    double maxA=max(thS);
    double extRange=extendFactor*(maxA-minA);
    minA=0.5*(minA+maxA)-0.5*extRange;
    maxA=0.5*(minA+maxA)+0.5*extRange;     
    if(blue==1){ // IF in blueLightMode overwrite 
      minA=-3.0; 
      maxA=5.0; 
    }
    ret(1)=minA;
    double delta=(maxA-minA)/(splineAppOrder-1.0); 
    for(int i=2; i<=splineAppOrder; ++i)ret(i)=ret(i-1)+delta;
    return ret;
  }

  dvector calcKnotsMoon(dvector lonlat, dmatrix data, double extendFactor=1.1){
    dvector thM=thetaM(lonlat,data);
    dvector ret(1,splineAppOrderMoon);
    double minA=min(thM);
    double maxA=max(thM);
    double extRange=extendFactor*(maxA-minA);
    minA=0.5*(minA+maxA)-0.5*extRange;
    if(minA<(-90))minA=(-90);
    maxA=0.5*(minA+maxA)+0.5*extRange;     
    if(maxA>90)maxA=90;
    ret(1)=minA;
    double delta=(maxA-minA)/(splineAppOrderMoon-1.0); 
    for(int i=2; i<=splineAppOrderMoon; ++i)ret(i)=ret(i-1)+delta;
    return ret;
  }

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

  dvariable wave(const dvar_vector& w, const dvector& p){
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
  }

  dvariable weight(dvariable& distsq, dvariable& radsq){
    return pow(1.0-pow(distsq/radsq,1.5),3.0); 
  }

  dvariable getSST(dvariable time, dvariable lon, dvariable lat, dvariable rad, 
                   dvector& sstDates, int noOfSstFiles){
    lon=360-lon; 
    dvariable sinLatG2R=sin(lat*G2R); 
    dvariable cosLatG2R=cos(lat*G2R);
    dvariable sinLonG2R=sin(lon*G2R); 
    dvariable cosLonG2R=cos(lon*G2R);
    dvariable radsq=rad*rad; 

    int whichmin=1; 
    double minval=value(fabs(time-sstDates(1)));
    int i;
    for(i=2; i<=noOfSstFiles; ++i){
      if(value(fabs(time-sstDates(i)))<minval){
        whichmin=i; 
        minval=value(fabs(time-sstDates(i)));
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
  }

  double dweight(double& distsq, double& radsq){
    return pow(1.0-pow(distsq/radsq,1.5),3.0); 
  }

  double dwave(dvector& w, dvector& p){
    double T=w*p; 
    double B=sum(w); 
    double tmp=T/B; 
    return tmp;
  }

  double dgetSST(double time, double lon, double lat, double rad, 
                dvector& sstDates, int noOfSstFiles){
    lon=360-lon; 
    double sinLatG2R=sin(lat*G2R); 
    double cosLatG2R=cos(lat*G2R);
    double sinLonG2R=sin(lon*G2R); 
    double cosLonG2R=cos(lon*G2R);
    double radsq=rad*rad; 

    int whichmin=1; 
    double minval=fabs(time-sstDates(1));
    int i;
    for(i=2; i<=noOfSstFiles; ++i){
      if(fabs(time-sstDates(i))<minval){
        whichmin=i; 
        minval=fabs(time-sstDates(i));
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
    closeby=qmlocal->get(lon,lat,rad); 
    dvector points(1,closeby.size());
    dvector weights(1,closeby.size()); 
    i=1;

    double t1;
    double t2;
    double t3;
    
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
      weights(i)=dweight(t3,radsq);
      i++; 
    }

    double ret=0;
    if(closeby.size()>=1){ 
      ret+=dwave(weights,points);
    }
    return ret; 
  }
  


DATA_SECTION
  !! ad_comm::change_datafile_name("sstsim.dat");
  init_int simmode; 
  !! if(simmode==1){
       init_int noOfSstFilesSim;
  !!   if(noOfSstFilesSim>0){
  !!     filen.allocate(1,noOfSstFilesSim);
  !!     cifstream* dat_in = ad_comm::global_datafile;
  !!     double x,y,v;
  !!     for(int i=1; i<=noOfSstFilesSim; ++i){
  !!       *dat_in>>filen(i);
  !!       Quadmap *qm = new Quadmap(-.01,-90.01,360.02,180.02);	
  !!       cout<<filen(i)<<endl;
  !!       ifstream fp_in;
  !!       fp_in.open(filen(i), ios::in); 
  !!       while(fp_in.eof()==0){
  !!         fp_in>>y; fp_in>>x; fp_in>>v;
  !!         qm->add(x,y,v);  
  !!       }
  !!       fp_in.close();
  !!       qml.push_back(qm);
  !!     }
         init_vector sstDatesSim(1,noOfSstFilesSim);
  !!     cout<<"size of qml is: "<<qml.size()<<endl;
         init_number rad; 
         init_number bsst; 
         init_int noSstObsSim;
         init_matrix sstObsMatSim(1,noSstObsSim,1,3);  
         vector ssttimesSim(1,noSstObsSim); 
         vector sstlon(1,noSstObsSim);
         vector sstlat(1,noSstObsSim);
         vector sstsst(1,noSstObsSim);       
  !!     ssttimesSim=column(sstObsMatSim,1);  
  !!     sstlon=column(sstObsMatSim,2);  
  !!     sstlat=column(sstObsMatSim,3);
  !!     ofstream simout("sstsim.out");
  !!     //cout<<"Before loop! "<<noSstObsSim<<endl;   
  !!     for(int i=1; i<=noSstObsSim; ++i){  
  !!       sstsst(i)=dgetSST(ssttimesSim(i),360-sstlon(i),sstlat(i),rad,sstDatesSim,noOfSstFilesSim)+bsst;  
  !!       simout<<setprecision(12)<<ssttimesSim(i)<<" "<<sstsst(i)<<endl;         
  !!       //cout<<ssttimesSim(i)<<" "<<sstsst(i)<<endl;         
  !!     }   
  !!     simout.close();    
  !!   }
  !!   //cout<<"Made it here!"<<endl; 
  !!       
  !!   exit(0);  
  !! }

  !! ad_comm::change_datafile_name("ukf.dat");
  init_int blueLightMode;  
  init_number midLon
  init_vector fixFirst(1,3);
  init_matrix fixFirstVar(1,2,1,2);
  int fixFirstVarZero;
  !! if(sum(square(fixFirstVar))==0){fixFirstVarZero=1;}else{fixFirstVarZero=0;}
  init_vector fixLast(1,3);
  init_matrix fixLastVar(1,2,1,2);
  int fixLastVarZero;
  !! if(sum(square(fixLastVar))==0){fixLastVarZero=1;}else{fixLastVarZero=0;}
  init_int lightrow
  init_int ncol
  init_int lightstep
  init_vector tmpidx1(1,lightstep)
  init_vector tmpidx2(1,lightstep)
  init_matrix obsMat(1,lightrow,1,ncol)

  //##################################################################SST-part
  init_int noOfSstFiles;
  !! if(noOfSstFiles>0){
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
    init_vector sstDates(1,noOfSstFiles);
    !! //cout<<"size of qml is: "<<qml.size()<<endl;
    init_int noSstObs;
    init_matrix sstObsMat(1,noSstObs,1,2); 
    vector ssttimes(1,noSstObs); 
    vector sstObs(1,noSstObs);
    !! ssttimes=column(sstObsMat,1);  
    !! sstObs=column(sstObsMat,2);  
    !! cout<<noSstObs<<"sst observations read."<<endl;
    !! TRACE(ssttimes)
    !! TRACE(sstObs)
  !! }
  //##################################################################END SST-part 

  matrix lightdat(1,lightrow,1,11)
  matrix ang(1,10,1,lightrow)

  !! ad_comm::change_datafile_name("model.cfg");
  init_int nSplineP
  int npar
  !! splineAppOrder=nSplineP;
  !! npar=12+splineAppOrder;
  init_vector thetaInit(1,npar)
  init_vector thetaPhase(1,13)  

  //1: JDU
  !! lightdat.colfill(1,column(obsMat,2));
  //2: SiderealUT
  !! lightdat.colfill(2,column(obsMat,3));
  //3: SunAlpha
  !! lightdat.colfill(3,column(obsMat,5));
  //4: CosSunDelta
  !! lightdat.colfill(4,cos(column(obsMat,6)*PiDiv180));
  //5: SinSunDelta
  !! lightdat.colfill(5,sin(column(obsMat,6)*PiDiv180));
  //6: MoonAlpha
  !! lightdat.colfill(6,column(obsMat,7));
  //7: CosMoonDelta
  !! lightdat.colfill(7,cos(column(obsMat,8)*PiDiv180));
  //8: SinMoonDelta
  !! lightdat.colfill(8,sin(column(obsMat,8)*PiDiv180));
  //9: MoonFrac
  !! lightdat.colfill(9,column(obsMat,9));

  vector lightobs(1,lightrow)
  !! lightobs=column(obsMat,10);

  //10: temp
  !! lightdat.colfill(10,column(obsMat,11));

  //11: depth
  !! lightdat.colfill(11,column(obsMat,4));

  ivector lightidx1(1,lightstep)
  ivector lightidx2(1,lightstep)
  vector lighttimes(0,lightstep+1)
  !! lighttimes(0)=fixFirst(3);  
  !! for(int i=1; i<=lightstep; ++i){
  !!   lightidx1(i)=(int)tmpidx1(i);
  !!   lightidx2(i)=(int)tmpidx2(i);
  !!   lighttimes(i)=column(obsMat,13)(lightidx1(i));
  !! }
  !! lighttimes(lightstep+1)=fixLast(3);  

  //init_int thetaDim
  //init_vector thetaInit(1,thetaDim)
  //init_vector thetaActive(1,thetaDim)

  vector knots(1,splineAppOrder) 
  !!   knots=calcKnots(fixFirst,getSubMat(lightdat,lightidx1(1),lightidx2(nStepFirst)),blueLightMode);     
  //vector knotsMoon(1,splineAppOrderMoon) 
  //!! knotsMoon=calcKnotsMoon(0.5*(fixFirst+fixLast),lightdat);     

  int stateDim;
  !! stateDim=2;

  //------------------------------------------------------------
  int nstep;  
  !!  nstep=lightstep;
  !!  if(noOfSstFiles>0){nstep+=noSstObs;} 
  vector times(0,nstep+1); 
  !! times(0,lightstep+1)=lighttimes; 
  !! for(int i=lightstep+2; i<=nstep+1; ++i){
  !!   times(i)=ssttimes(i-lightstep-1);
  !! }
  ivector idx1(1,nstep);
  ivector idx2(1,nstep);
  !! idx1(1,lightstep)=lightidx1;   
  !! idx2(1,lightstep)=lightidx2;   
  !! for(int i=lightstep+1; i<=nstep; ++i){
  !!   idx1(i)=lightrow+i-lightstep;    
  !!   idx2(i)=idx1(i); 
  !! }

  int nrow; 
  !! nrow=lightrow;
  !! if(noOfSstFiles>0){nrow+=noSstObs;}   
  vector obs(1,nrow);   
  !! obs(1,lightrow)=lightobs; 
  !! for(int i=lightrow+1; i<=nrow; ++i){obs(i)=sstObs(i-lightrow);}   
  matrix dat(1,nrow,1,11); 
  !! dat.initialize(); 
  !! for(int i=1; i<=lightrow; ++i){dat(i)=lightdat(i);} 
  !! for(int i=lightrow+1; i<=nrow; ++i){dat(i,2)=times(i-lightrow+lightstep+1);} 

  ivector order(0,nstep+1); 
  !! times=sort(times,order);
  
  !! ivector orderreduced(1,nstep);
  !! int count=0;  
  !! for(int i=0; i<=nstep+1; ++i){
  !!   if((order(i)<(nstep+1))&&(order(i)>0)){
  !!     count++; 
  !!     orderreduced(count)=order(i);
  !!   }
  !! }
  !! idx1=idx1(orderreduced);  
  !! idx2=idx2(orderreduced);  

  //ang used? yes, but only in light part, so ok unchanged. 
  //------------------------------------------------------------

  3darray P(0,nstep+1,1,stateDim,1,stateDim);
  !! P.initialize();
  3darray PP(0,nstep+1,1,stateDim,1,stateDim);
  !! PP.initialize();   

PARAMETER_SECTION        
  !! int ph = (int)thetaPhase(1);
  init_bounded_number u(-50,50,ph);
  !! ph = (int)thetaPhase(2);        
  init_bounded_number v(-50,50,ph);      
  !! ph = (int)thetaPhase(3);          
  init_bounded_number logD(-15,9,ph); 
  !! ph = (int)thetaPhase(4);               
  init_bounded_number logSS1(-15,15,ph);
  !! ph = (int)thetaPhase(5);         
  init_bounded_number logSS2(-10,10,ph);
  !! ph = (int)thetaPhase(6);         
  init_bounded_number logSS3(-10,10,ph);
  !! ph = (int)thetaPhase(7);         
  init_bounded_number rho(0,.3,ph);  

  !! if(noOfSstFiles>0){ph = (int)thetaPhase(8);}else{ph = -1;}
  init_bounded_number bsst(-10,10,ph);  
  !! if(noOfSstFiles>0){ph = (int)thetaPhase(9);}else{ph = -1;}
  init_bounded_number logSSsst(-10,6,ph);  
  !! if(noOfSstFiles>0){ph = (int)thetaPhase(10);}else{ph = -1;}
  init_bounded_number rad(25,1200,ph);  

  !! ph = (int)thetaPhase(11);                
  init_bounded_number dep1(-10,10,ph);
  !! ph = (int)thetaPhase(12);         
  init_bounded_number dep2(-10,10,ph);
  !! ph = (int)thetaPhase(13);         
  init_bounded_vector qSparTilde(1,splineAppOrder,0,200,ph);
  vector qSpar(1,splineAppOrder);

  init_vector weatherIdx(2,nstep,-3);  
  //init_bounded_vector qSparTildeMoon(1,splineAppOrderMoon,0,200);
  //vector qSparMoon(1,splineAppOrderMoon);

  init_number dummy(4);
  objective_function_value nLogL;


  matrix X(0,nstep+1,1,stateDim);  
  matrix V(0,nstep+1,1,stateDim);

  vector x0(1,stateDim);
  vector xN(1,stateDim);

  sdreport_number D;
  sdreport_number ss1;
  sdreport_number ss2;
  sdreport_number ss3;
  sdreport_number sssst;

PRELIMINARY_CALCS_SECTION
  u=thetaInit(1);				       
  v=thetaInit(2);
  logD=log(thetaInit(3));                                 
  logSS1=log(thetaInit(4));	 		       
  logSS2=log(thetaInit(5));		       
  logSS3=log(thetaInit(6));			       
  rho=thetaInit(7);
  bsst=thetaInit(8);
  logSSsst=log(thetaInit(9));
  rad=thetaInit(10);			       
  dep1=thetaInit(11);
  dep2=thetaInit(12);
  for(int i=1; i<=splineAppOrder; ++i){
    qSparTilde(i)=thetaInit(12+i);
  }			       

  //qSparTildeMoon=0.0;
  weatherIdx=0.0;

  x0(1,2)=zInv(fixFirst);
  //x0(3)=0.0;
  xN=zInv(fixLast);

PROCEDURE_SECTION
  double kappa=0.0;
  X.initialize();
  V.initialize();
  
  qSpar(1,splineAppOrder)=cumsum(qSparTilde(1,splineAppOrder)); 

  //dvariable splinePenalty=0.0; 
  //for(int ii=3; ii<=(splineAppOrder-1); ++ii){
  //  dvariable prev=qSpar(ii)-2*qSpar(ii-1)+qSpar(ii-2); 
  //  dvariable cur=qSpar(ii+1)-2*qSpar(ii)+qSpar(ii-1);
  //  if((prev<0)&&(cur>0))splinePenalty+=1.0e6*cur*cur*cur;  
  //}

  //qSparMoon(1,splineAppOrderMoon)=cumsum(qSparTildeMoon(1,splineAppOrderMoon)); 

  D=exp(logD);
  ss1=exp(logSS1);
  ss2=exp(logSS2);
  ss3=exp(logSS3);
  sssst=exp(logSSsst);

  cout<<"u="<<setprecision(4)<<u<<", "; 
  cout<<"v="<<setprecision(4)<<v<<", "; 
  cout<<"D="<<setprecision(4)<<D<<", "; 
  cout<<"ss1="<<setprecision(4)<<ss1<<", "; 
  cout<<"ss2="<<setprecision(4)<<ss2<<", ";   
  cout<<"ss3="<<setprecision(4)<<ss3<<", ";    
  cout<<"rho="<<setprecision(4)<<rho<<", ";
  cout<<"bsst="<<setprecision(4)<<bsst<<", ";
  cout<<"sssst="<<setprecision(4)<<sssst<<", ";
  cout<<"rad="<<setprecision(4)<<rad<<", ";
  cout<<"dep1="<<setprecision(4)<<dep1<<", ";
  cout<<"dep2="<<setprecision(4)<<dep2<<endl;
  cout<<setprecision(4)<<knots<<endl;   
  cout<<setprecision(4)<<qSpar<<endl;   
  //cout<<setprecision(4)<<knotsMoon<<endl;   
  //cout<<setprecision(4)<<qSparMoon<<endl;  
   
  cout.flush();

  //vcubic_spline_function qS(knots,qSpar);
  vcubic_spline_function qS=setupApp(knots,qSpar);
  
  nLogL=0.0;
  if(current_phase()==1){
    //cout<<"before"<<endl;
    int curIdx=0; 
    for(int i=1; i<=nStepFirst; ++i){
      ++curIdx; 
      while(idx1(curIdx)==idx2(curIdx)){
        ++curIdx; 
      }  
      nLogL+=splineLS(fixFirst,obs(idx1(curIdx),idx2(curIdx)),getSubMat(dat,idx1(curIdx),idx2(curIdx)),qS,knots,ang); 
    }
    //cout<<"after"<<endl; 
  }else{
    nLogL=unscentedKalmanFilter(x0, xN, obs, dat, idx1, idx2, times, X, V, P, PP, qS, kappa); 
  }
  //nLogL+=splinePenalty;  
  cout<<setprecision(9)<<nLogL<<endl;
  //cout<<setprecision(9)<<nLogL<<" ("<<splinePenalty<<")"<<endl;
  ofstream angout("ang.out");
  angout<<trans(ang);
  
  angout.close();

  if((knots(1)>min(ang(1)))||(knots(splineAppOrder)<max(ang(1)))){
    //cout<<"Warning: An angle outside the knots array were requested"<<endl;
    cout<<"Requested angle range ("<<min(ang(1))<<","<<max(ang(1))<<")"<<endl;
  } 

  ofstream sunout("sun.out");
  for(double angle=-90; angle<=90; angle+=0.1){
    sunout<<angle<<" "<<qS(angle)<<endl;
  } 
  sunout.close();
  



  //exit(0); // if I just want a single run.

//-------------------------------------------------------------------

//-------------------------------------------------------------------

FUNCTION dvar_vector z(const dvar_vector& alpha)
  RETURN_ARRAYS_INCREMENT();
  dvariable t1, t2;
  dvar_vector ret(1,2);
  t1=alpha(2)/Mpg*PiDiv180;
  t2=Mpg*cos(t1);
  ret(1)=-alpha(1)/t2+midLon;
  ret(2)=alpha(2)/Mpg;
  RETURN_ARRAYS_DECREMENT();
  return ret;

FUNCTION dvar_vector zInv(const dvar_vector& y)
  RETURN_ARRAYS_INCREMENT();
  dvar_vector ret(1,2);
  ret(1)=-(y(1)-midLon)*Mpg*cos(y(2)*PiDiv180);
  ret(2)=y(2)*Mpg;
  RETURN_ARRAYS_DECREMENT();
  return ret;

FUNCTION dvar_vector L(const dvar_vector& psi, const dmatrix& data, vcubic_spline_function& qS)
  RETURN_ARRAYS_INCREMENT();
  dvar_vector y=z(psi);
  dvar_vector thS=thetaS(y,data);
  
  dvector depth=column(data,11);    
  dvector d2=0.5*(fabs(depth-50.0)+(depth-50.0));

  dvar_vector ret=qS(thS)+dep1*depth+dep2*d2;
  //ret+=twentyLog10Exp*psi(3);
  //ret+=psi(3);
  //dvar_vector ret=qS(thS)+twentyLog10Exp*psi(3);
  ang(1)(thS.indexmin(),thS.indexmax())=value(thS);
  ang(2)(thS.indexmin(),thS.indexmax())=obs(thS.indexmin(),thS.indexmax());
  ang(3)(thS.indexmin(),thS.indexmax())=value(ret);
  RETURN_ARRAYS_DECREMENT();
  return ret;

//------------------------------------------------------------------

FUNCTION dvar_vector F(const dvar_vector& x, const double& dt)
  RETURN_ARRAYS_INCREMENT();
  int n1=x.indexmin();
  int n2=x.indexmax();
  dvar_vector ret(n1,n2);
  ret=x;
  ret(n1)+=u*dt; 
  ret(n1+1)+=v*dt; 
  RETURN_ARRAYS_DECREMENT();
  return ret;

FUNCTION dvar_matrix Q(const double& dt)
  RETURN_ARRAYS_INCREMENT();
  dvar_matrix ret(1,stateDim,1,stateDim);
  ret.initialize();
  ret(1,1)=2.0*D*dt;
  ret(2,2)=2.0*D*dt;
  RETURN_ARRAYS_DECREMENT();
  return ret;

FUNCTION dvar_vector G(const dvar_vector& x, const dmatrix& data, vcubic_spline_function& qS)
  RETURN_ARRAYS_INCREMENT();
  int n1=data.rowmin();
  int n2=data.rowmax();
  dvar_vector tmp(n1,n2); 
  if(data(n1,1)<1.0e-6){
    dvar_vector lonlat=z(x); 
    //cout<<"Before "<<setprecision(12)<<data(n1,2)<<" "<<lonlat(1)<<" "<<lonlat(2)<<" "<<rad<<endl; 
    tmp(n1)=getSST(data(n1,2),lonlat(1),lonlat(2),rad,sstDates,noOfSstFiles)+bsst; 
    //cout<<"After "<<tmp(n1)<<endl; 
  }else{
    tmp=L(x,data,qS);
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
  

FUNCTION dvar_matrix R(const dmatrix& data)
  RETURN_ARRAYS_INCREMENT();
  int n1=data.rowmin();
  int n2=data.rowmax();
  int ii;
  int jj;
  dvar_matrix ret(n1,n2,n1,n2);
  if(data(n1,1)<1.0e-6){
    ret(n1,n1)=sssst; 
  }else{
    ret.initialize();
    for(ii=n1; ii<=n2; ++ii){
      for(jj=ii; jj<=n2; ++jj){
        ret(ii,jj)=ss2;
        if(ii==jj)ret(ii,jj)+=ss3;
        if(ii!=jj)ret(ii,jj)*=exp(-fabs(data(ii,1)-data(jj,1))/rho);
        ret(jj,ii)=ret(ii,jj);
      }
    }
    for(ii=n1; ii<=n2; ++ii){
      for(jj=n1; jj<=n2; ++jj){
        ret(ii,jj)+=ss1;
      }
    }
  }
  RETURN_ARRAYS_DECREMENT();
  return ret;
  

//------------------------------------------------------------------

//------------------------------------------------------------------
FUNCTION dvariable unscentedKalmanFilter(const dvar_vector& x0, const dvar_vector& xN, const dvector& obs, const dmatrix& data, const ivector&  idx1, const ivector& idx2, const dvector& times, dvar_matrix& X, dvar_matrix& V, d3_array& Pall, d3_array& PPall, vcubic_spline_function& qS, const double& kappa)
  // -- Figure out the dimensions 
  int rmin=X.rowmin();
  int rmax=X.rowmax();
  int cmin=X.colmin();
  int cmax=X.colmax();
  int stateDim=cmax-cmin+1;
  int N=rmax-rmin+1;
  dvar_matrix T(1,stateDim,1,stateDim);
  int last=0;

  // -- Calculate the weights 
  dvector W(0,2*stateDim);
  W(0)=kappa/(stateDim+kappa);
  W(1,2*stateDim)=1.0/(2.0*(stateDim+kappa)); //1,2,...,2*stateDim

  // -- Take care of 0'th Obs
  dvar_matrix Xpoints(0,2*stateDim,cmin,cmax);
  for(int i=0; i<=(2*stateDim); ++i){
    Xpoints(i)=x0;
  }
  dvar_matrix P(cmin,cmax,cmin,cmax);
  P.initialize();
  P=fixFirstVar;
  Pall(0)=value(P);
  PPall(0)=value(P);
  X(0)=x0;
  V(0)=diagonal(P);

  dvariable nlogL=0.0; 
  for(int k=1; k<=rmax-1; ++k){
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
    int idxlow, idxhigh; 
    idxlow=idx1(k);
    idxhigh=idx2(k);
    dmatrix subData=getSubMat(data,idxlow,idxhigh);     
    dvar_matrix Ypoints(0,2*stateDim,idxlow,idxhigh);
    for(int i=0; i<=(2*stateDim); ++i){
      Ypoints(i)=G(Xpoints(i), subData, qS);
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

    if(blueLightMode==1){
      dvar_vector angles=thetaS(z(X(k)),getSubMat(data,idxlow,idxhigh));
      for(int i=idxlow; i<=idxhigh; ++i){
        if(angles(i)<-2.9)diffVec(i)*=-2.0*pow((angles(i)+3.0)*10.0,3.0)+3.0*square((angles(i)+3.0)*10.0); 
        if(angles(i)>4.9)diffVec(i)*=1.0-(-2.0*pow((angles(i)-4.9)*10.0,3.0)+3.0*square((angles(i)-4.9)*10.0)); 
        if((angles(i)<-3.0)||(angles(i)>5))diffVec(i)=0.0; 
      }
    }    

    X(k)+=K*diffVec;
    P-=K*S*trans(K);
    Pall(k)=value(P);

    V(k)=diagonal(P);
    dvar_vector zero(idxlow,idxhigh); 
    zero.initialize();
    nlogL+=nLogNormalChol(diffVec,zero,L);

    Xpoints=sigmaPoints(X(k),P,kappa);
  }  

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
  dvar_matrix Ypoints(0,2*stateDim,1,2);
  for(int i=0; i<=(2*stateDim); ++i){
    Ypoints(i)=z(Xpoints(i));
  }
  dvar_vector Yhat=weightedVectorMean(Ypoints,W);
  dvar_matrix Pyy=weightedCovEst(Ypoints,Yhat,W);
  dvar_matrix Pxy=weightedCov2Est(Xpoints,X(rmax),Ypoints,Yhat,W);
  dvar_matrix S=Pyy; 

  //S+=LAST POINT VARIANCE 
  if(fixLastVarZero==0){//meaning not zero
    Xpoints=sigmaPoints(xN,fixLastVar,kappa);
    for(int i=0; i<=(2*stateDim); ++i){
      Ypoints(i)=z(Xpoints(i));
    }
    S+=weightedCovEst(Ypoints,z(xN),W);
  }
  // -- The out-commented lines are replaced with the two lines below  
  // -- to optimize - tested and optimal 
  //dvar_matrix K=Pxy*inv(S);     
  //dvar_matrix L=choleski_decomp(S);
  dvar_matrix L=chol(S);
  dvar_matrix K=trans(fwsolve(L,bksolve(L,trans(Pxy))));
  dvar_vector diffVec(1,2);

  diffVec=z(xN)-Yhat;
  X(rmax)+=K*diffVec;
  P-=K*S*trans(K);

  Pall(rmax)=value(P);
  V(rmax)=diagonal(P);
  nlogL+=nLogNormalChol(z(xN),Yhat,L);    
  return nlogL;  
  


//------------------------------------------------------------------


BETWEEN_PHASES_SECTION
  cout<<"*********** Now entering phase "<<current_phase()<<" of 4 **********"<<endl; 
  if((current_phase()==4)&&(blueLightMode==0)){
    //weatherIdx.set_phase_start(-1);
    dummy.set_phase_start(-1);
    double minAng=min(ang(1))-0.5;
    double maxAng=max(ang(1))+0.5;
    double dAng=(maxAng-minAng)/(splineAppOrder-1);
    vcubic_spline_function qSLocal=setupApp(knots,qSpar);
    knots.fill_seqadd(minAng,dAng);
    qSparTilde=qSLocal(knots);
    cout<<"*********** "<<knots<<" **********"<<endl; 
    cout<<"*********** "<<qSparTilde<<" **********"<<endl; 
    for(int i=qSparTilde.indexmax(); i>=qSparTilde.indexmin()+1; --i){
      qSparTilde(i)-=qSparTilde(i-1);
    } 
    cout<<"*********** "<<qSparTilde<<" **********"<<endl; 
  }
  if((current_phase()==4)&&(blueLightMode==1)){
    dummy.set_phase_start(-1);
  }
REPORT_SECTION;
  if(current_phase()!=1){
    dmatrix Pstar(1,stateDim,1,stateDim);
    Pstar.initialize();
    d3_array Pmpt(0,nstep+1,1,stateDim,1,stateDim);
    Pmpt.initialize();
    dmatrix mpt(0,nstep+1,1,stateDim);
    mpt.initialize();
    dvector mptTmp(1,stateDim);
    mptTmp.initialize();
    double dt;
    double kappa=0.0;  
    dvector W(0,2*stateDim);
    W(0)=kappa/(stateDim+kappa);
    W(1,2*stateDim)=1.0/(2.0*(stateDim+kappa)); 

    mpt(nstep+1)=value(X(nstep+1));

    dmatrix tmpt(0,nstep+1,1,stateDim);
    tmpt.initialize();
    tmpt(nstep+1)=value(z(X(nstep+1)));
    d3_array tPmpt(0,nstep+1,1,stateDim,1,stateDim);
    tPmpt.initialize();
    Pmpt(nstep+1)=P(nstep+1);  
 
    if(fixLastVarZero==0){//meaning not zero 
      dmatrix SP=value(sigmaPoints(mpt(nstep+1),Pmpt(nstep+1),kappa));
      for(int j=0; j<=(2*stateDim); ++j){
        SP(j)=value(z(SP(j)));
      }
      tPmpt(nstep+1)=value(weightedCovEst(SP,tmpt(nstep+1),W));
    } 

    int stopat=0;
    if(fixFirstVarZero==1){//meaning zero
      stopat=1; 
    }

    for(int i=nstep; i>=stopat; --i){
      Pstar=P(i)*inv(PP(i+1));
      dt=times(i+1)-times(i);
      mptTmp(1)=value(u*dt);
      mptTmp(2)=value(v*dt);
      mpt(i)=value(X(i)+Pstar*(mpt(i+1)-X(i)-mptTmp));
      Pmpt(i)=value(P(i)+Pstar*(Pmpt(i+1)-PP(i+1))*trans(Pstar));
      dmatrix SP=value(sigmaPoints(mpt(i),Pmpt(i),kappa));
      for(int j=0; j<=(2*stateDim); ++j){
        SP(j)=value(z(SP(j)));
      }
      tmpt(i)=value(weightedVectorMean(SP,W));
      tPmpt(i)=value(weightedCovEst(SP,tmpt(i),W));
    }
    if(fixFirstVarZero==1){//meaning zero
      mpt(0)=value(X(0));
      Pmpt(0)=0;
      tmpt(0)=value(z(X(0)));
      tPmpt(0)=0;
    }

    ofstream mptout("mpt.out");
    for(int i=0; i<=nstep+1; ++i){
      mptout<<setprecision(12)<<times(i)<<" ";
      mptout<<mpt(i,1)<<" "<<mpt(i,2)<<" ";
      mptout<<Pmpt(i,1,1)<<" "<<Pmpt(i,1,2)<<" ";
      mptout<<Pmpt(i,2,1)<<" "<<Pmpt(i,2,2)<<" ";
      mptout<<tmpt(i,1)<<" "<<tmpt(i,2)<<" ";
      mptout<<tPmpt(i,1,1)<<" "<<tPmpt(i,1,2)<<" ";
      mptout<<tPmpt(i,2,1)<<" "<<tPmpt(i,2,2)<<" ";
      if(noOfSstFiles>0){
        mptout<<getSST(times(i),tmpt(i,1),tmpt(i,2),rad,sstDates,noOfSstFiles)+bsst<<endl;
      }else{
        mptout<<endl;
      }
    }
    mptout.close();

    ofstream predout("pred.out");
    for(int i=0; i<=nstep+1; ++i){
      predout<<X(i,1)<<" "<<X(i,2)<<" ";
      predout<<P(i,1,1)<<" "<<P(i,1,2)<<" ";
      predout<<P(i,2,1)<<" "<<P(i,2,2)<<" ";
      if((i!=0)&&(i!=(nstep+1))){
        dmatrix SP=value(sigmaPoints(X(i),P(i),kappa));
        for(int j=0; j<=(2*stateDim); ++j){
          SP(j)=value(z(SP(j)));
        }
        dvector predtmp=value(weightedVectorMean(SP,W));
        dmatrix tPP=value(weightedCovEst(SP,predtmp,W));
        predout<<predtmp(1)<<" "<<predtmp(2)<<" ";
        predout<<tPP(1,1)<<" "<<tPP(1,2)<<" ";
        predout<<tPP(2,1)<<" "<<tPP(2,2)<<endl;
      }else{
        predout<<z(X(i))<<" 0 0 0 0"<<endl;
      }
    }
    predout.close();

  }

TOP_OF_MAIN_SECTION
  arrmblsize=2000000;
  //gradient_structure::set_NUM_RETURN_ARRAYS(75);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(15000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(8000000);
  gradient_structure::set_MAX_NVAR_OFFSET(1000);

RUNTIME_SECTION
  maximum_function_evaluations 100, 100, 300, 10000;   
