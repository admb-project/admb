#include <fvar.hpp>


  class f1b1_data{
  {
  public:
    double        u;
    dvector       udot;      // tangent vector for u
    dvector       uhat;      // adjoint vector for u
    dvector       uhatdot;   // adjoint vector for udot

    f1b_data(int n) : udot(1,n), uhat(1,n), uhatdot(1,n) {}
    int nvar(void) {return udot.indexmax();}
  };

  class single_f1b1_function
  {
  public:
    double (*f)(double);
    double (*d1f)(double);
    double (*d11f)(double);
    single_f1b1_node operator () (dep_data& v)
    {
      f1b1_data * dep=v->dep;
      f1b_data tmp(dep->nvar());
      tmp.u=f(dep->u);
      udot=d1f(dep->u)*dep->udot;
      single_f1b1_node node : ;
      node.ind=*v;
      
    }
  }
      

  class double_f1b1_function
  {
  public:
    double (*f)(double,double);
    double (*d1f)(double,double);
    double (*d2f)(double,double);
    double (*d12f)(double,double);
    double (*d22f)(double,double);
    double_f1b1_node operator () (dep_data& v,dep_data& w)
    {
      f1b1_data * dep1=v->dep;
      f1b1_data * dep2=w->dep;
      f1b1_data * = new f1b1_data(tmp(dep->nvar()));
      tmp.u=f(dep1->u,dep2->u);
      udot=d1f(dep1->u)*dep1->udot;
      udot+=d2f(dep1->u)*dep1->udot;
    }
    class single_f1b1_node : dep_data(f1b1_data);
  };
      
  class dep_data
  {
  public:
    f1b1_data * dep;
    dep_data(f1b1_data * t) { dep=t;}
  };

  
  class single_f1b1_node : public dep_data {
  {
  public:
    dep_data * ind1;
    single_f1b1_function * f;
  };
    
  class double_f1b1_node : public dep_data {
  {
    dep_data * ind1;
    dep_data * ind2;
    double_f1b1_function * f;
  };
    

  
