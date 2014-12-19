//  ******************************************************************
//  Testing Ecology Library
//
//  Created by Mollie Brooks on 2011-07-09.
//  Copyright (c) 2011. All rights reserved.
//  Comments:
//  ******************************************************************


DATA_SECTION
	init_int length;
	init_number x_s;
	init_vector x_v(1,length);
	init_number x_s_nrh
	init_vector x_v_nrh(1,length);

PARAMETER_SECTION
	init_number a_s;
	init_vector a_v(1,length);
	init_number b_s;
	init_vector b_v(1,length);
	init_number c_s;
	init_vector c_v(1,length);
	init_number theta;
	init_number a_s_nrh;
	init_vector a_v_nrh(1,length);
	init_number b_s_nrh;
	init_vector b_v_nrh(1,length);
	init_number c_s_nrh;
	init_vector c_v_nrh(1,length);
	objective_function_value f;

PROCEDURE_SECTION
	//Michaelis Menten1
	//outs<<"mm1"<<endl;
	outs<<Michaelis_Menten1(x_s,a_s,b_s)<<endl;
	outs<<Michaelis_Menten1(x_v,a_s,b_v)<<endl;
	outs<<Michaelis_Menten1(x_v,a_v,b_s)<<endl;
	outs<<Michaelis_Menten1(x_v,a_v,b_v)<<endl;
	//Michaelis Menten2
	//outs<<"mm2"<<endl;
	outs<<Michaelis_Menten2(x_s,a_s,b_s)<<endl;
	outs<<Michaelis_Menten2(x_v,a_s,b_v)<<endl;
	outs<<Michaelis_Menten2(x_v,a_v,b_s)<<endl;
	outs<<Michaelis_Menten2(x_v,a_v,b_v)<<endl;
	//Hill
	//outs<<"hill"<<endl;
	outs<<Hill(x_s,a_s,b_s,c_s)<<endl;
	outs<<Hill(x_v,a_v,b_s,c_s)<<endl;
	outs<<Hill(x_v,a_v,b_v,c_s)<<endl;
	outs<<Hill(x_v,a_v,b_s,c_v)<<endl;
	outs<<Hill(x_v,a_v,b_v,c_v)<<endl;
	outs<<Hill(x_v,a_s,b_v,c_s)<<endl;
	outs<<Hill(x_v,a_s,b_v,c_v)<<endl;
	outs<<Hill(x_v,a_s,b_s,c_v)<<endl;
	//HollingII
	//outs<<"HollingII"<<endl;
	outs<<HollingII(x_s,a_s,b_s)<<endl;
	outs<<HollingII(x_v,a_s,b_v)<<endl;
	outs<<HollingII(x_v,a_v,b_s)<<endl;
	outs<<HollingII(x_v,a_v,b_v)<<endl;
	//HollingIII
	//outs<<"HollingIII"<<endl;
	outs<<HollingIII(x_s,a_s,b_s)<<endl;
	outs<<HollingIII(x_v,a_s,b_v)<<endl;
	outs<<HollingIII(x_v,a_v,b_s)<<endl;
	outs<<HollingIII(x_v,a_v,b_v)<<endl;
	//HollingIV
	//outs<<"HollingIV"<<endl;
	outs<<HollingIV(x_s,a_s,b_s,c_s)<<endl;
	outs<<HollingIV(x_v,a_v,b_s,c_s)<<endl;
	outs<<HollingIV(x_v,a_v,b_v,c_s)<<endl;
	outs<<HollingIV(x_v,a_v,b_s,c_v)<<endl;
	outs<<HollingIV(x_v,a_v,b_v,c_v)<<endl;
	outs<<HollingIV(x_v,a_s,b_v,c_s)<<endl;
	outs<<HollingIV(x_v,a_s,b_v,c_v)<<endl;
	outs<<HollingIV(x_v,a_s,b_s,c_v)<<endl;
	//monomolecular
	//outs<<"monomolecular"<<endl;
	outs<<monomolecular(x_s,a_s,b_s)<<endl;
	outs<<monomolecular(x_v,a_s,b_v)<<endl;
	outs<<monomolecular(x_v,a_v,b_s)<<endl;
	outs<<monomolecular(x_v,a_v,b_v)<<endl;
	//logistic
	//outs<<"logistic"<<endl;
	outs<<logistic(x_s,a_s,b_s)<<endl;
	outs<<logistic(x_v,a_s,b_v)<<endl;
	outs<<logistic(x_v,a_v,b_s)<<endl;
	outs<<logistic(x_v,a_v,b_v)<<endl;	
	//logisticK
	//outs<<"logisticK"<<endl;
	outs<<logisticK(x_s,a_s,b_s,c_s)<<endl;
	outs<<logisticK(x_v,a_v,b_s,c_s)<<endl;
	outs<<logisticK(x_v,a_v,b_v,c_s)<<endl;
	outs<<logisticK(x_v,a_v,b_s,c_v)<<endl;
	outs<<logisticK(x_v,a_v,b_v,c_v)<<endl;
	outs<<logisticK(x_v,a_s,b_v,c_s)<<endl;
	outs<<logisticK(x_v,a_s,b_v,c_v)<<endl;
	outs<<logisticK(x_v,a_s,b_s,c_v)<<endl;
	//logistic3
	//outs<<"logistic3"<<endl;
	outs<<logistic3(x_s,a_s,b_s,c_s)<<endl;
	outs<<logistic3(x_v,a_v,b_s,c_s)<<endl;
	outs<<logistic3(x_v,a_v,b_v,c_s)<<endl;
	outs<<logistic3(x_v,a_v,b_s,c_v)<<endl;
	outs<<logistic3(x_v,a_v,b_v,c_v)<<endl;
	outs<<logistic3(x_v,a_s,b_v,c_s)<<endl;
	outs<<logistic3(x_v,a_s,b_v,c_v)<<endl;
	outs<<logistic3(x_v,a_s,b_s,c_v)<<endl;
	//theta logistic
	//outs<<"theta_logistic"<<endl;
	outs<<theta_logistic(x_s,a_s,b_s,c_s,theta)<<endl;
	outs<<theta_logistic(x_v,a_v,b_s,c_s,theta)<<endl;
	outs<<theta_logistic(x_v,a_v,b_v,c_s,theta)<<endl;
	outs<<theta_logistic(x_v,a_v,b_s,c_v,theta)<<endl;
	outs<<theta_logistic(x_v,a_v,b_v,c_v,theta)<<endl;
	outs<<theta_logistic(x_v,a_s,b_v,c_s,theta)<<endl;
	outs<<theta_logistic(x_v,a_s,b_v,c_v,theta)<<endl;
	outs<<theta_logistic(x_v,a_s,b_s,c_v,theta)<<endl;
	//Ricker
	//outs<<"Ricker"<<endl;
	outs<<Ricker(x_s,a_s,b_s)<<endl;
    outs<<Ricker(x_v,a_s,b_v)<<endl;
    outs<<Ricker(x_v,a_v,b_s)<<endl;
    outs<<Ricker(x_v,a_v,b_v)<<endl;
	//generalized_Ricker1
	outs<<generalized_Ricker1(x_s,a_s,b_s,c_s)<<endl;
	outs<<generalized_Ricker1(x_v,a_v,b_s,c_s)<<endl;
	outs<<generalized_Ricker1(x_v,a_v,b_v,c_s)<<endl;
	outs<<generalized_Ricker1(x_v,a_v,b_s,c_v)<<endl;
	outs<<generalized_Ricker1(x_v,a_v,b_v,c_v)<<endl;
	outs<<generalized_Ricker1(x_v,a_s,b_v,c_s)<<endl;
	outs<<generalized_Ricker1(x_v,a_s,b_v,c_v)<<endl;
	outs<<generalized_Ricker1(x_v,a_s,b_s,c_v)<<endl;
	//generalized_Ricker2
	outs<<generalized_Ricker2(x_s,a_s,b_s,c_s)<<endl;
	outs<<generalized_Ricker2(x_v,a_v,b_s,c_s)<<endl;
	outs<<generalized_Ricker2(x_v,a_v,b_v,c_s)<<endl;
	outs<<generalized_Ricker2(x_v,a_v,b_s,c_v)<<endl;
	outs<<generalized_Ricker2(x_v,a_v,b_v,c_v)<<endl;
	outs<<generalized_Ricker2(x_v,a_s,b_v,c_s)<<endl;
	outs<<generalized_Ricker2(x_v,a_s,b_v,c_v)<<endl;
	outs<<generalized_Ricker2(x_v,a_s,b_s,c_v)<<endl;
	//nonrectangular_hyperbola
	outs<<nonrectangular_hyperbola(x_s_nrh,a_s_nrh,b_s_nrh,c_s_nrh)<<endl;	
	outs<<nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_s_nrh,c_s_nrh)<<endl;
	outs<<nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_v_nrh,c_s_nrh)<<endl;
	outs<<nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_s_nrh,c_v_nrh)<<endl;
	outs<<nonrectangular_hyperbola(x_v_nrh,a_v_nrh,b_v_nrh,c_v_nrh)<<endl;
	outs<<nonrectangular_hyperbola(x_v_nrh,a_s_nrh,b_v_nrh,c_s_nrh)<<endl;
	outs<<nonrectangular_hyperbola(x_v_nrh,a_s_nrh,b_v_nrh,c_v_nrh)<<endl;
	outs<<nonrectangular_hyperbola(x_v_nrh,a_s_nrh,b_s_nrh,c_v_nrh)<<endl;
	//Gompertz 
	outs<<Gompertz(x_s,a_s,b_s)<<endl;
	outs<<Gompertz(x_v,a_s,b_v)<<endl;
	outs<<Gompertz(x_v,a_v,b_s)<<endl;
	outs<<Gompertz(x_v,a_v,b_v)<<endl;
	//Shepherd
	outs<<Shepherd(x_s,a_s,b_s,c_s)<<endl;
	outs<<Shepherd(x_v,a_v,b_s,c_s)<<endl;
	outs<<Shepherd(x_v,a_v,b_v,c_s)<<endl;
	outs<<Shepherd(x_v,a_v,b_s,c_v)<<endl;
	outs<<Shepherd(x_v,a_v,b_v,c_v)<<endl;
	outs<<Shepherd(x_v,a_s,b_v,c_s)<<endl;
	outs<<Shepherd(x_v,a_s,b_v,c_v)<<endl;
	outs<<Shepherd(x_v,a_s,b_s,c_v)<<endl;
	//Hassell
	outs<<Hassell(x_s,a_s,b_s,c_s)<<endl;
	outs<<Hassell(x_v,a_v,b_s,c_s)<<endl;
	outs<<Hassell(x_v,a_v,b_v,c_s)<<endl;
	outs<<Hassell(x_v,a_v,b_s,c_v)<<endl;
	outs<<Hassell(x_v,a_v,b_v,c_v)<<endl;
	outs<<Hassell(x_v,a_s,b_v,c_s)<<endl;
	outs<<Hassell(x_v,a_s,b_v,c_v)<<endl;
	outs<<Hassell(x_v,a_s,b_s,c_v)<<endl;
	
GLOBALS_SECTION
	#include <admodel.h>
	#include <pow_vectorized_RE.cpp>
	
	#include <Michaelis_Menten1.cpp>
	#include <Michaelis_Menten2.cpp>
	#include <Hill.cpp>
	#include <HollingII.cpp>
	#include <HollingIII.cpp>
	#include <HollingIV.cpp>
	#include <monomolecular.cpp>
	#include <logistic.cpp>
	#include <logisticK.cpp>
	#include <logistic3.cpp>
	#include <theta_logistic.cpp>
	#include <Ricker.cpp>
	#include <generalized_Ricker1.cpp>
	#include <generalized_Ricker2.cpp>
	#include <nonrectangular_hyperbola.cpp>
	#include <Gompertz.cpp>
	#include <Shepherd.cpp>
	#include <Hassell.cpp>
	ofstream outs("results_from_ADMB.txt");
	