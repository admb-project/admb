msimple.tpl and msimpl1.tpl do the same computations as simple.tpl but on
matrix with the same number of rows as threads and more elements per row. 
In the threaded version, each row is computed on a separae thread.

The numerical results are identical, but the decrease in execution time is  only
about 12%


Unthreaded

$ time msimple1 -nohess

 - final statistics:
2 variables; iteration 9; function evaluation 54
Function value   5.8917e+06; maximum gradient component mag   1.3769e-04
Exit code = 1;  converg criter   1.0000e-04
Var   Value    Gradient   |Var   Value    Gradient   |Var   Value    Gradient   
  1  2.00010  1.37693e-04 |  2  3.98762  3.03774e-06 |

real	0m4.411s
user	0m4.356s
sys	0m0.048s


Using 8 threads
$ time msimple -nohess

 - final statistics:
2 variables; iteration 9; function evaluation 54
Function value   5.8917e+06; maximum gradient component mag   1.3769e-04
Exit code = 1;  converg criter   1.0000e-04
Var   Value    Gradient   |Var   Value    Gradient   |Var   Value    Gradient   
  1  2.00010  1.37693e-04 |  2  3.98762  3.03774e-06 |

real	0m3.876s
user	0m17.161s
sys	0m1.740s


(4.411 - 3.876)/4.411 = 0.535/4.411 = 0.121
