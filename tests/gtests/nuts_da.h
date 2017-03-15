/** Copyright (c) 2016 ADMB Foundation */
#include <vector>

//function [samples, epsilon] = nuts_da(f, M, Madapt, theta0, delta)
void nuts_da(const int M, const int Madapt, const std::vector<double>& theta0, const double delta);
