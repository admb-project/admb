void begin_df1b2_funnel();
void end_df1b2_funnel();
void begin_df1b2_funnel2();
void end_df1b2_funnel2();

template <typename T, typename U, typename V, typename W, typename X>
void df1b2_parameters<T, U, V, W, X>::allocate()
{
  if constexpr(std::is_same<X,df1b2variable>::value)
  {
    ad_comm::global_datafile->clear();
    ad_comm::global_datafile->seekg(0, std::ios::beg);
  }
  n.allocate("n");
  y.allocate(1,n,"y");
  b.allocate(-.9999,.9999,2,"b");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  mu.allocate(-10,10,-1,"mu");
  mu_x.allocate(-10,3,1,"mu_x");
  x.allocate(1,n,2,"x");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
template <typename T, typename U, typename V, typename W, typename X>
void df1b2_parameters<T, U, V, W, X>::deallocate()
{
  if constexpr(std::is_same<X,df1b2variable>::value)
  {
    b.deallocate();
    log_sigma.deallocate();
    mu.deallocate();
    mu_x.deallocate();
    x.deallocate();
    g.deallocate();
  }
}
template <typename T, typename U, typename V, typename W, typename X>
void df1b2_parameters<T, U, V, W, X>::user_function()
{
  g =0.0;
  int i;	
  sf1(log_sigma,b,x(1));
  for (i=2;i<=n;i++)
  {
    sf2(log_sigma,b,x(i),x(i-1));
  }
  for (i=1;i<=n;i++)
  {
    sf3(x(i),mu,mu_x,i);
  }
}
template <typename T, typename U, typename V, typename W, typename X>
template <class F>
void df1b2_parameters<T, U, V, W, X>::separable(F&& f)
{
  if constexpr(std::is_same<X,df1b2variable>::value)
  {
    begin_df1b2_funnel2();
  }
  else
  {
    begin_df1b2_funnel();
  }
  f();
  if constexpr(std::is_same<X,df1b2variable>::value)
  {
    end_df1b2_funnel2();
  }
  else
  {
    end_df1b2_funnel();
  }
}
template <typename T, typename U, typename V, typename W, typename X>
void df1b2_parameters<T, U, V, W, X>::sf1(const T& ls, const T& bb, const T& x_1)
{
  separable([this, &ls, &bb, &x_1]()
  {
    g -= -ls + 0.5*log(1-square(bb))  - 0.5*square(x_1/mfexp(ls))*(1-square(bb));
  });
}
template <typename T, typename U, typename V, typename W, typename X>
void df1b2_parameters<T, U, V, W, X>::sf2(const T& ls,const T& bb,const T& x_i,const T& x_i1)
{
  separable([this, &ls, &bb, &x_i, &x_i1]()
  {
    g -= -ls - .5*square((x_i-bb*x_i1)/mfexp(ls));
  });
}
template <typename T, typename U, typename V, typename W, typename X>
void df1b2_parameters<T, U, V, W, X>::sf3(const T& x_i ,const T& mu ,const T& mu_x ,int i)
{
  separable([this, &x_i, &mu, &mu_x, &i]()
  {
    X log_sigma_y = 0.5*(mu_x + x_i);
    X sigma_y = mfexp(log_sigma_y);
    g -= -log_sigma_y - .5*square((y(i)-mu)/sigma_y);
  });
}
