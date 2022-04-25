template<class F, class ...Args>
dvariable trapzd(double a, double b, int n, int& interval, dvariable& s, F&& func, Args&&... args)
{
  if (n == 1)
  {
    interval=1;
    return (s=0.5*(b-a)*(func(a, args...)+func(b, args...)));
  }

  double num_interval=interval;
  double hn=(b-a)/num_interval;
  double x=a+0.5*hn;
  int j = 1;
  dvariable sum;
  for (sum=0.0;j<=interval;j++,x+=hn) sum += func(x, args...);
  interval *= 2;
  s=0.5*(s+(b-a)*sum/num_interval);
  return s;
}
template<class F, class ...Args>
dvariable adromb(double a, double b, int ns, F&& func, Args&&... args)
{
  const int JMAX = 50;
  const double base = 4;
  int MAXN = min(JMAX, ns);
  dvar_vector s(1,MAXN+1);

  int interval = 0;
  dvariable s2;
  for(int j=1; j<=MAXN+1; j++)
  {
    s[j] = trapzd(a, b, j, interval, s2, func, args...);
  }
  for(int iter=1; iter<=MAXN+1; iter++)
  {
    for(int j=1; j<=MAXN+1-iter; j++)
    {
      s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
    }
  }
  return s[1];
}
