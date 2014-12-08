DATA_SECTION
	init_int nobs;
	init_vector y(1,nobs);
	init_vector x(1,nobs);

	!! ad_comm::change_datafile_name("example.ctl");
	init_vector a_lup(1,3);
	init_vector b_lup(1,3);
	init_vector sig_lup(1,3);

	init_matrix theta_lup(1,3,1,3);
PARAMETER_SECTION

	init_bounded_number a(a_lup);
	init_bounded_number b(b_lup);
	init_bounded_number sig(sig_lup);

	init_bounded_number_vector theta(theta_lup);
	objective_function_value f;

	vector y_hat(1,nobs);
	vector y2_hat(1,nobs);

INITIALIZATION_SECTION
	sig 1.0;


PROCEDURE_SECTION
	
	y_hat = a + b * x;
	y2_hat = theta(1) + theta(2)*x;
	f     = dnorm(y - y_hat, sig);
	f    += dnorm(y-y2_hat,theta(3));


