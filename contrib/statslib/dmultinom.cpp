#include "statsLib.h"

/**
* @file dmultinom.cpp
* @brief Multinomial distribution
* 
* This file contains the multinomial distribution functions
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/13/2011
* @remarks
*/

dvariable dmultinom(const dvector& x, const dvar_vector& p)
{
	if(x.indexmin() != p.indexmin() || x.indexmax() != p.indexmax())
	{
		cerr << "Index bounds do not macth in"
		" dmultinom(const dvector& x, const dvar_vector& p)\n";
		ad_exit(1);
	}

	double n=sum(x);
	return -gammln(n+1.)+sum(gammln(x+1.))-x*log(p/sum(p));
}

double neff(const dvector& obs, const dvar_vector& pred)
{
	dvector resid=value(obs-pred);
	dvector var=value(elem_prod(1.-pred,pred));
	return sum(var)/norm2(resid);
}

// dvariable dmultinom(const dmatrix o, const dvar_matrix& p,dvar_matrix& nu,double& tau2,const double minp, double &neff)
// {
// 	RETURN_ARRAYS_INCREMENT();
// 	dvariable nloglike = dmultinom(o,p,nu,tau2,minp);
// 	int t = o.rowmin();
// 	int T = o.rowmax();
// 	dvector n(t,T);
// 	for(int i = t; i <= T; i++ )
// 	{
// 		n(i) = neff(o(i),p(i));
// 	}
// 	neff = mean(n(i));
// 	RETURN_ARRAYS_DECREMENT();
// 	return(nloglike);
// }
dvariable dmultinom(const dmatrix o, const dvar_matrix& p,dvar_matrix& nu,double& tau2,const double minp)
{	// returns the negative loglikelihood
	/*
     uses Martell dmvlogistic code for grouping age classes
     with observed proportions < minp
     NB minp must be greater than 0, otherwise algorithm returns
     an error if one of the observed proportions is zero.
     tau2 returns the median absolute standardized residual

	FIX ME SM I'm getting an array out of Bounds error in here for gear3
		has to do with the if statement (if minp >1.-4) because Ncount is only
		1.  I've commented the if statement out for now.
	*/
	RETURN_ARRAYS_INCREMENT();
	int i,j,k,n;
	int a = o.colmin();
	int A=o.colmax();
	int t=o.rowmin();
	int T=o.rowmax();
	dvector tmptau(1,A*T);	// vector of residuals
    int Ncount=1;
    dvariable Nsamp;           // multinomial sample size
	//FIXME NB Make proc_err into a switch in the control file
	//add this likelihood description to the documentation.
    dvariable proc_err=0.009;   // allow for process error in the pred.age freq...fixed value based on HCAM assessments
	nu.initialize();
	dvariable nloglike=0.;
    //ofstream ofs("check.tmp");

	for(i=t; i<=T; i++)
	{
		//cout<<"Ok to here 1"<<endl;
		Nsamp=sum(o(i))/(1.+proc_err*sum(o(i)));
		n=0;
		dvector oo = o(i)/sum(o(i));
		dvar_vector pp = p(i)/sum(p(i));

		//count # of observations greater than minp (2% is a reasonable number)
		for(j=a;j<=A;j++)
			if(oo(j) > minp)n++;

		ivector iiage(1,n);
		dvector o1(1,n); o1.initialize();
		dvar_vector p1(1,n); p1.initialize();
		k=1;
		for(j=a;j<=A;j++)
		{
			if(oo(j)<=minp)
			{
				o1(k)+=oo(j);
				p1(k)+=pp(j);
			}
			else
			{
				o1(k)+=oo(j);
				p1(k)+=pp(j);
				if(k<=n)iiage(k)=j;		//ivector for the grouped residuals
				if(k<n) k++;
			}
		}
		/*
		//assign residuals to nu based on iiage index
		dvar_vector t1 = elem_div(o1-p1,sqrt(elem_prod(p1,1.-p1)/Nsamp));
		for(j=1;j<=n;j++)
		{
			nu(i)(iiage(j))=t1(j);
			tmptau(Ncount++)=sqrt(square(value(t1(j))));
		}
		*/

		//CHANGED Later addition from Viv to prevent crashes if
		//min(p1) is very small.
		//if(min(p1)>1e-4)
		{
			dvar_vector t1 = elem_div(o1-p1,sqrt(elem_prod(p1,1.-p1)/Nsamp));
			for(j=1;j<=n;j++)
			{
				nu(i)(iiage(j))=t1(j);
				tmptau(Ncount++)=sqrt(square(value(t1(j))));
			}
		}
		//end of addition.
		// negative log Mulitinomial with constant is:
		// r = -1.*(gammln(Nsamp+1)+sum(Nsamp*o1(log(p1))-gammln(Nsamp+1)));
		// TODO add calculation for effective sample size.
		/*
			TODO Neff = sum(elem_prod(p1,1.-p1))/sum(square(o1-p1));
			for each year.  Plot the Nsamp vs Neff and look for a 1:1 slope.
		*/

		nloglike+=sum(-1.*elem_prod(Nsamp*o1,log(p1))+
					elem_prod(Nsamp*o1,log(o1)));
		//cout<<"Ok to here 2"<<endl;
	}

	dvector w=sort(tmptau(1,Ncount-1));
	//cout<<"All good "<<Ncount<<endl;
	tau2=w(int(Ncount/2.)); //median absolute residual (expected value of 0.67ish)

	RETURN_ARRAYS_DECREMENT();
	return(nloglike);
}


