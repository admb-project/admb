#include <future>
#include <fvar.hpp>

std::future<std::pair<double, dvector>> thread_funnel(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps)
{
  gradient_structure* gs = gradient_structure::get();
  return std::async(std::launch::async, [=]()->std::pair<double, dvector>
  {
    gradient_structure::_instance = gs;

    double v = 0;
    dvector g(1, 4);
    //gradient_structure::get()->GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
    {
      independent_variables scoped_independents(1, 4);
      scoped_independents(1) = value(tau);
      scoped_independents(2) = value(nu);
      scoped_independents(3) = value(sigma);
      scoped_independents(4) = value(beta);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);

      dvariable f(0);

      dvariable _tau = scoped_variables(1);
      dvariable _nu = scoped_variables(2);
      dvariable _sigma = scoped_variables(3);
      dvariable _beta = scoped_variables(4);

      f = func(_tau, _nu, _sigma, _beta, ai, nsteps);

      v = value(f);

      gradcalc(4, g);
    }
    //gradient_structure::get()->GRAD_STACK1->deallocate_RETURN_ARRAYS();

    return std::make_pair(v, g);
  });
}
