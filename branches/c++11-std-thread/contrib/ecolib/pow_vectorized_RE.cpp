#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 
df1b2vector pow(const dvector& x,  const df1b2variable& a)
{
    RETURN_ARRAYS_INCREMENT();	
	df1b2vector y(x.indexmin(), x.indexmax());
	
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		y(i)=pow(x(i),a);
	}	

	RETURN_ARRAYS_DECREMENT();	
    return(y);
}
df1b2vector pow(const dvector& x,  const df1b2vector& a)
{
    RETURN_ARRAYS_INCREMENT();	
	df1b2vector y(x.indexmin(), x.indexmax());
	
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		y(i)=pow(x(i),a(i));
	}	

	RETURN_ARRAYS_DECREMENT();	
    return(y);
}
dvar_vector pow(const dvector& x,const dvar_vector& a)
{
    RETURN_ARRAYS_INCREMENT();	
	dvar_vector y(x.indexmin(), x.indexmax());

	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		y(i)=pow(x(i),a(i));
	}	

	RETURN_ARRAYS_DECREMENT();	
    return(y);
}
	
	
