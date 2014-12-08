DATA_SECTION
	int n;
	!! n = 4;
	vector lb(1,n);
	vector ub(1,n);
	ivector phz(1,n);
	vector ival(1,n);
	LOC_CALCS
		lb(1,n) = 0;
		ub(1,n) = 5;
		phz = 1;
		ival = 3;
	END_CALCS
INITIALIZATION_SECTION
	theta ival;

PARAMETER_SECTION
	init_bounded_number_vector theta(1,n,lb,ub,phz);
	objective_function_value f;

PROCEDURE_SECTION
	f = 0;
	for(int i = 1; i <= n; i++ )
	{
		f += square(theta(i) -1.0);
	}
