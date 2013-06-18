\begin{lstlisting}
// file: userfin.cpp 

#include <fvar.hpp> 

double userfun(dvar_vector& x) 
{ 
  dvariable z,tmp; 
  int min,max; 
  min=x.indexmin(); 
  max=x.indexmax(); 
  tmp=x[min]-1; 
  z+=tmp*tmp; 
  for (int i=min;i<max;i++) 
  {  
    tmp=x[i+1]-x[i]; 
    z+=tmp*tmp; 
  } 
  return(value(z)); 
} 
\end{lstlisting}