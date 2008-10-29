class prevariable_position
{
  double_and_int * v;
public:
  prevariable_position(_CONST prevariable& x){v=x.get_v();}
  prevariable_position(double_and_int * p){v=p;}
  double& xval() { return( (v->x) ); }
};

double restore_prevariable_derivative(BOR_CONST prevariable_position& pre);
double restore_prevariable_derivative(void);
prevariable_position restore_prevariable_position(void);
void save_double_derivative(CGNU_DOUBLE x, BOR_CONST prevariable_position& pos);
double restore_prevariable_value(void);
void save_double_value(CGNU_DOUBLE x);
