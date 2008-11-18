dvariable reset(ivector& control,dvar_vector& x,dvar_vector& p, dvar_vector& mu,
    dvar_vector& sd,dvector& mumin, dvector& mumax, dvector& sdmin,
    dvector& sdmax);
dvariable log_likelihood(dvector y,dvar_vector p,dvar_vector& mu,
	dvar_vector& sd);
void xinit(ivector& control,independent_variables& x,dvector& p,dvector& mu,
    dvector& sd,dvector& mumin,dvector& mumax,dvector& sdmin,dvector& sdmax);
int nvarcal(ivector& control ,int ngroups);
double fcomp(dvector y,dvar_vector p,dvar_vector& mu,dvar_vector& sd,
  dvector& mumin, dvector& mumax, dvector& sdmin, dvector& sdmax,
  ivector& control,dvar_vector& x,int print_switch);
dvariable normalize_p(dvar_vector& p);
void save_pars(dvar_vector& p,dvar_vector& mu,dvar_vector& sd,
  dvector& mumin, dvector& mumax,dvector& sdmin, dvector& sdmax,
  ivector& control);
