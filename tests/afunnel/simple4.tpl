// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)
PARAMETER_SECTION
  init_number b0
  init_number b1
  objective_function_value f
PROCEDURE_SECTION
  //cout << "Start: " << gradient_structure::GRAD_STACK1->total() << endl;
  f = funnel([](dvariable& b0, dvariable& b1, const dvector& x, const dvector& y)
  {
    //cout << "A: " << gradient_structure::GRAD_STACK1->total() << endl;
    dvariable f;

    dvar_vector yhat(x.indexmin(), y.indexmax());
    yhat = b0 + b1 * x;
    f=regression(y, yhat);

    //cout << "B: " << gradient_structure::GRAD_STACK1->total() << endl;
    return f;
  }, b0, b1, x, y);
  //cout << "End: " << gradient_structure::GRAD_STACK1->total() << endl;
PRELIMINARY_CALCS_SECTION
  global_grad_stack = new grad_stack(10000, 10);
  global_grad_stack->allocate_RETURN_ARRAYS(25, 70);
FINAL_SECTION
  global_grad_stack->deallocate_RETURN_ARRAYS();
  delete global_grad_stack;
  global_grad_stack = nullptr;
GLOBALS_SECTION
  #include <fvar.hpp>
  #include <future>

  grad_stack* global_grad_stack = nullptr;

  std::future<std::pair<double, dvector>> afunnel(
    dvariable (*func)(
      dvariable& b0, dvariable& b1, const dvector& x, const dvector& y),
    dvariable& b0, dvariable& b1, const dvector& x, const dvector& y)
  {
    return std::async(std::launch::async, [=]()->std::pair<double, dvector>
    {
      double v = 0;
      dvector g(1, 2);

      gradient_structure::GRAD_STACK1 = global_grad_stack;
      {
        independent_variables scoped_independents(1, 2);
        scoped_independents(1) = value(b0);
        scoped_independents(2) = value(b1);

        // Set gradient_structure::NVAR
        dvar_vector scoped_variables(scoped_independents);

        dvariable f(0);

        dvariable a = scoped_variables(1);
        dvariable b = scoped_variables(2);

        f = func(a, b, x, y);

        v = value(f);

        gradcalc(2, g);
      }
      gradient_structure::GRAD_STACK1 = nullptr;

      return std::make_pair(v, g);
    });
  }
  dvariable to_dvariable(
    std::pair<double, dvector>& p,
    dvariable& x, dvariable& y)
  {
    dvariable var(p.first);
    dvector g(p.second);

    grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
    entry->func = default_evaluation;
    entry->dep_addr = &((*var.v).x);
    entry->ind_addr1 = &((*x.v).x);
    entry->mult1 = g(1);
    entry->ind_addr2 = &((*y.v).x);
    entry->mult2 = g(2);
    gradient_structure::GRAD_STACK1->ptr++;

    return var;
  }
  dvariable funnel(
    dvariable (*func)(
      dvariable& b0, dvariable& b1, const dvector& x, const dvector& y),
    dvariable& b0, dvariable& b1, const dvector& x, const dvector& y)
  {
    std::future<std::pair<double, dvector>> f = afunnel(func, b0, b1, x, y);
    std::pair<double, dvector> p = f.get();

    dvariable result;
    result = to_dvariable(p, b0, b1);
    return result;
  }
