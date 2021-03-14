DATA_SECTION
  init_vector s(1,2)

PARAMETER_SECTION
  init_vector ss(1,2)
 LOCAL_CALCS
   ss = s;
 END_CALCS

 objective_function_value y

PROCEDURE_SECTION
  y = M_PI-atan2(ss(1),ss(2));
 
REPORT_SECTION
  report << ss << endl;
  // wrong value
  report<<"atan2(dvariable,dvariable)="<<atan2(ss[1],ss[2])<<endl;
  //report << "atan(dvariable/dvariable)=" << atan(ss[1]/ss[2]) << endl;

  dvector st(1,2);
  st[1] = value(ss[1]);
  st[2] = value(ss[2]);
  // correct value
  report<<"atan2(double,double)="<<atan2(st[1], st[2])<<endl;
  //report << "atan(double/double)=" << atan(st[1]/st[2]) << endl;

  //atan2(dvariable,dvariable)=1.35777
  //atan2(double,double)=-1.78382
