void begin_df1b2_funnel();
void end_df1b2_funnel();
void begin_df1b2_funnel2();
void end_df1b2_funnel2();

template <typename T, typename U, typename V, typename W>
sdv<T, U, V, W>::sdv()
{
  n.allocate("n");
  y.allocate(1,n,"y");
  b.allocate(-.9999,.9999,2,"b");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  mu.allocate(-10,10,-1,"mu");
  mu_x.allocate(-10,3,1,"mu_x");
  x.allocate(1,n,2,"x");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
template <typename T, typename U, typename V, typename W>
void sdv<T, U, V, W>::userfunction()
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
template <typename T, typename U, typename V, typename W>
void sdv<T, U, V, W>::sf1(const T& ls, const T& bb, const T& x_1)
{
  begin_df1b2_funnel();
  g -= -ls + 0.5*log(1-square(bb))  - 0.5*square(x_1/mfexp(ls))*(1-square(bb));
  end_df1b2_funnel();
}
template <typename T, typename U, typename V, typename W>
void sdv<T, U, V, W>::sf2(const T& ls, const T& bb, const T& x_i, const T& x_i1)
{
  begin_df1b2_funnel();
  g -= -ls - .5*square((x_i-bb*x_i1)/mfexp(ls));
  end_df1b2_funnel();
}
template <typename T, typename U, typename V, typename W>
void sdv<T, U, V, W>::sf3(const T& x_i, const T& mu, const T& mu_x, int i)
{
  begin_df1b2_funnel();
  dvariable log_sigma_y = 0.5*(mu_x + x_i);
  dvariable sigma_y = mfexp(log_sigma_y);
  g -= -log_sigma_y - .5*square((y(i)-mu)/sigma_y);
  end_df1b2_funnel();
}
template <typename T, typename U, typename V, typename W>
void df1b2_parameters<T, U, V, W>::allocate()
{
  ad_comm::global_datafile->clear();
  ad_comm::global_datafile->seekg(0, std::ios::beg);

  n.allocate("n");
  y.allocate(1,n,"y");
  b.allocate(-.9999,.9999,2,"b");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  mu.allocate(-10,10,-1,"mu");
  mu_x.allocate(-10,3,1,"mu_x");
  x.allocate(1,n,2,"x");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
template <typename T, typename U, typename V, typename W>
void df1b2_parameters<T, U, V, W>::deallocate()
{
  b.deallocate();
  log_sigma.deallocate();
  mu.deallocate();
  mu_x.deallocate();
  x.deallocate();
  g.deallocate();
}
template <typename T, typename U, typename V, typename W>
void df1b2_parameters<T, U, V, W>::user_function()
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
template <typename T, typename U, typename V, typename W>
void df1b2_parameters<T, U, V, W>::sf1(const T& ls, const T& bb,const T& x_1)
{
  begin_df1b2_funnel2();
  g -= -ls + 0.5*log(1-square(bb))  - 0.5*square(x_1/mfexp(ls))*(1-square(bb));
  end_df1b2_funnel2();
}
template <typename T, typename U, typename V, typename W>
void df1b2_parameters<T, U, V, W>::sf2(const T& ls,const T& bb,const T& x_i,const T& x_i1)
{
  begin_df1b2_funnel2();
  g -= -ls - .5*square((x_i-bb*x_i1)/mfexp(ls));
  end_df1b2_funnel2();
}
template <typename T, typename U, typename V, typename W>
void df1b2_parameters<T, U, V, W>::sf3(const T& x_i ,const T& mu ,const T& mu_x ,int i)
{
  begin_df1b2_funnel2();
  df1b2variable log_sigma_y = 0.5*(mu_x + x_i);
  df1b2variable sigma_y = mfexp(log_sigma_y);
  g -= -log_sigma_y - .5*square((y(i)-mu)/sigma_y);
  end_df1b2_funnel2();
}
