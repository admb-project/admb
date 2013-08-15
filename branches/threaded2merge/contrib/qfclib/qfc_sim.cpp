 /** 
  * \file	qfc_sim.cpp
  * \brief functions useful for simulation model in admb
  * \date 7/28/2011
  * \author Weihai Liu
  * \ingroup QFC
  *
  *  Following user defined functions are more useful for doing simulation model in admb, 
  *  the easy way to use these functions is with your tpl file
  *  under the GLOBALS_SECTION , add a line on top as   #include "qfclib.h", 
  *  there is a testfunction.tpl file within this folder show how to use these functions.
  *
  *  ================  brief list for usage  ============================\n
  *  1. return some values for the specific variable name in admb ouput file,
  *     such as find the parameter value and its std value from .std file, 
  *     use findValFromFile("test.std","linf",2), see findValFromFile()  \n
  *  2. doing random sampling with or without replacement, see sample()  \n 
  *  3. remove the duplicate values from a vector, see unique()  \n  
  *  4. several random number generator, runif(), rnorm(), rgamma(), rdirichlet() \n
  *  5. round your matrix, vector, sclar to some specific decimals for display 
  *     in report_section, such as round(dmatrix,4), see round()  \n  
  *  6. convert vector to matrix by row or by column or its reverse form,  
  *     see matrix2vector(), vector2matrix() \n
  *  =============================================================\n
  *
  *  found any bug , contact Weihai Liu at liuweih@msu.edu \n
  *  Quantitative Fisheries Center(QFC), Michigan State University \n
  */


  #include "qfclib.h"
 

  /** get how many rows for one specific variable(varName) in admb output file(filename)
   * \ingroup QFC
   * \param filename : search for admb output file name
   * \param varName : variable name being searched for
   * \return  return 1 for unique name or  many rows for same name , return 0 for not found
   */
  int numRows4VarFromFile(adstring filename,adstring varName)
  {
     const int MAXCHARS=1000; // constant value for max number of character readin for each line
     const char *delim=" ,#:="; //change the delimiters as you need," ,#:="

     ifstream infile(filename); // open file for read in
     char readin[MAXCHARS]; 
     int cnt=0; 
     while(!infile.eof()){
       infile.getline(readin,MAXCHARS);
       char *pch;
       pch = strtok(readin,delim); //first string or char[] being separated
       while(pch != NULL)
       {       
          //printf ("%s\n",pch);
          if(strcmp(pch,(char*)varName)== 0) {cnt++; break;} //find the matched variable name        
          pch = strtok(NULL,delim);
       } //end inner while()
     } 
     infile.close();
     //cout<<cnt<<endl;
     return cnt;
  }



  /** find the number of values(numVals) for one specific variable(varName) from an admb output file
   * \ingroup QFC
   * \param filename : search for admb output file name
   * \param varName : variable name being searched for
   * \param numVals : number of values following that specific variable names for return
   * \return  return the found number of values for that variable name, if having unique name, then return one row matrix
   * if having same name, return several rows matrix
   */
  dmatrix findValFromFile(adstring filename,adstring varName,int numVals)
  {
     int repeat=numRows4VarFromFile(filename,varName);
     if (repeat<=0) {cerr<<"Can not found that variable name in this file"<<endl; exit(1);}
     const int MAXCHARS=1000; //constant value for max number of character readin for each line
     const char *delim=" ,#:="; //change the delimiters as you need," ,#:="

     ifstream infile(filename); //open file for read in
     dmatrix results(1,repeat,1,numVals); //output
     char readin[MAXCHARS]; 
     int cnt=0; //how many values needed after found that variable
     int lines=0; //track of num rows for repeat
     int start=0; //find the matched variable name
 
     while(!infile.eof()){
       infile.getline(readin,MAXCHARS);
       char *pch;
       pch = strtok(readin,delim); //first string or char[] being separated
       while(pch != NULL)
       {       
          //printf ("%s\n",pch);
          if(start==1) { //if founded the variable we needed
            cnt++;
            results(lines,cnt)=atof(pch); //change to double
            //cout<<results(linecnt)<<" "<<readin<<endl;
            if(cnt==numVals) start=0; //exit after readin in all we need # of values
          }
          if(strcmp(pch,(char*)varName)== 0) {//find the matched variable name
            start=1; //find the matched variable name
            cnt=0; //reset numVals counter as 0
            lines++; //update line index
            if(lines>repeat) break; //exit after reading num of repeat rows
          }
         
          pch = strtok(NULL,delim);
       } //end inner while()
     }//end first while() 
     infile.close();

     return results;
  }            
 



 

  /** find the unique values from input vector and only return the unique
   *  (by remove the duplicate) values in ascending order
   * \ingroup QFC
   * \param in : contain duplicate values in the input vector
   * \return return a vector comprised of unique values in ascending order and its index starting from 1 
   */
  dvector unique(const dvector& in)
  {
    dvector lookup(1,in.size()); //track of duplicate index
    lookup=1; //initial 1 as no duplicate, duplicate mark as 0
    
    dvector all=sort(in);  

    //find duplicates
    for(int i=all.indexmin();i<all.indexmax();i++)
    {
      if(lookup(i)!=0) //0 means already marked as duplicate, so skip it, initial as all 1
      {
        for(int j=i+1;j<=all.size();j++)
        {
          if(all(i) == all(j)) 
            lookup(j)=0; //mark same duplicate as 0
        }  
      }
    }   
    
    //output the unique by removing the duplicates
    int tot=int(sum(lookup)); //total unique value
    dvector out(1,tot);
    int idx=1;
    for(int i=all.indexmin();i<=all.indexmax();i++)
      if(lookup(i)==1)  //only output unique value, duplicate mark as 0
        out(idx++) = all(i);
    
    return out;
  }




  /** generate a random sample index(size is nSample) based on the input samples(source) 
   *  with or without replacement
   * \ingroup QFC
   * \param source : baseline samples as input
   * \param nSample : random sample size for output
   * \param withReplace : if 0 for without replacement, nonzero  means with replacement
   * \param rng :  admb build in random number generator
   * \return return an index vector which are the index from the samples, 
   * if want to access the values, use return dvector version 
  */
  ivector sample(const dvector& source,int nSample,int withReplace,const random_number_generator& rng)
  {
    int totN=source.size();
    dvector lookup(source.indexmin(),source.indexmax());
    lookup=source;
    ivector out(1,nSample);
  
    if(withReplace==0){  //sampling without replacement, all unique site index
      out(1)=source.indexmin()+int(totN*randu(rng)); 
      lookup(out(1))=0;//if selected, then mark lookup as 0
  
      for(int i=2;i<=nSample;i++){ 
        out(i)=source.indexmin()+int(totN*randu(rng)); 
        while(lookup(out(i))==0){ //which means already being selected
          out(i)=source.indexmin()+int(totN*randu(rng));
        }
        lookup(out(i))=0;//if selected, then mark lookup as 0
      }
    }else{  //with replacement,allow repeat sampling    
      for(int i=1;i<=nSample;i++) 
        out(i)=source.indexmin()+int(totN*randu(rng)); 
    }

    return out;  //you can use source(out) to access the sample
  }






  /** convert the matrix as a vector eithter by row=1(default) or by column=0,
   * \ingroup QFC
   * \param input : the matrix being converted, can also be ragged matrix 
   * \param byrow : default as by row, use 1, anynumber other than 1 as by column
   * \return return a vector which index starting from 1 
   */
  dvector matrix2vector(const dmatrix& input, int byrow=1)
  {
    dvector out(1,size_count(input)); //input.rowsize()*input.colsize() 
    long  idx=1;
    if(byrow==1){ //by row
      for(int i=input.indexmin();i<=input.indexmax();i++) //row
        for(int j=input(i).indexmin();j<=input(i).indexmax();j++) //col
          out(idx++)=input(i,j);
    }
    else{ //by column
      for(int i=input.colmin();i<=input.colmax();i++)  //col
        for(int j=input.rowmin();j<=input.rowmax();j++) //row
          out(idx++)=input(j,i);    
    }
    return out;
  }

  /** convert the matrix as a vector eithter by row=1(default) or by column=0,
   * overloading function
   * \ingroup QFC
   * \param input : the matrix being converted, can also be ragged matrix 
   * \param byrow : default as by row, use 1, anynumber other than 1 as by column
   * \return return a vector which index starting from 1 
   */
  dvar_vector matrix2vector(const dvar_matrix& input, int byrow=1)
  {
    dvar_vector out(1,size_count(input)); //input.rowsize()*input.colsize() 
    long  idx=1;
    if(byrow==1){ //by row
      for(int i=input.indexmin();i<=input.indexmax();i++) //row
        for(int j=input(i).indexmin();j<=input(i).indexmax();j++) //col
          out(idx++)=input(i,j);
    }
    else{ //by column
      for(int i=input.colmin();i<=input.colmax();i++)  //col
        for(int j=input.rowmin();j<=input.rowmax();j++) //row
          out(idx++)=input(j,i);    
    }
    return out;
  }

  /** convert the matrix as a vector eithter by row=1(default) or by column=0,
   * overloading function 
   * \ingroup QFC
   * \param input : the matrix being converted, can also be ragged matrix 
   * \param byrow : default as by row, use 1, anynumber other than 1 as by column
   * \return return a vector which index starting from 1 
   */
  df1b2vector matrix2vector(const df1b2matrix& input, int byrow=1)
  {
    df1b2vector out(1,size_count(input)); //input.rowsize()*input.colsize() 
    long  idx=1;
    if(byrow==1){ //by row
      for(int i=input.indexmin();i<=input.indexmax();i++) //row
        for(int j=input(i).indexmin();j<=input(i).indexmax();j++) //col
          out(idx++)=input(i,j);
    }
    else{ //by column
      for(int i=input.colmin();i<=input.colmax();i++)  //col
        for(int j=input.rowmin();j<=input.rowmax();j++) //row
          out(idx++)=input(j,i);    
    }
    return out;
  }





  /** convert the Vector as a Matrix eithter by row=1(default) or by column=0,
   * \ingroup QFC
   * \param input : long vector/array being converted
   * \param nrow : the number of rows for output matrix 
   * \param ncol : the number of columns for output matrix 
   * \param byrow : default as by row, use 1, which fill the each row from top to bottom 
   *  Or any number other than 1 as by column, which fill each column from left to right
   * \return return a matrix which row and column index all starting from 1 
   */
  dmatrix vector2matrix(dvector& input, int nrow, int ncol, int byrow=1)
  {
    if(nrow*ncol != input.size()){
      cerr<<"In vector2matrix(): Defined matrix dimension not fit the input vector size"<<endl; 
      exit(1);
    }
    dmatrix out(1,nrow,1,ncol);  
    long  idx=input.indexmin();
    if(byrow==1){ //by row
      for(int i=1;i<=nrow;i++) //row
        for(int j=1;j<=ncol;j++) //col
          out(i,j)=input(idx++);
    }
    else{ //by column
      for(int i=1;i<=ncol;i++)  //col
        for(int j=1;j<=nrow;j++) //row
          out(j,i)=input(idx++);    
    }
    return out;
  }

  /** convert the Vector as a Matrix eithter by row=1(default) or by column=0,
   * overloading function
   * \ingroup QFC
   * \param input : long vector/array being converted
   * \param nrow : the number of rows for output matrix 
   * \param ncol : the number of columns for output matrix 
   * \param byrow : default as by row, use 1, which fill the each row from top to bottom 
   *  Or any number other than 1 as by column, which fill each column from left to right
   * \return return a matrix which row and column index all starting from 1 
   */
  df1b2matrix vector2matrix(df1b2vector& input, int nrow, int ncol, int byrow=1)
  {
    if(nrow*ncol != input.size()){
      cerr<<"In vector2matrix(): Defined matrix dimension not fit the input vector size"<<endl; 
      exit(1);
    }
    df1b2matrix out(1,nrow,1,ncol);  
    long  idx=input.indexmin();
    if(byrow==1){ //by row
      for(int i=1;i<=nrow;i++) //row
        for(int j=1;j<=ncol;j++) //col
          out(i,j)=input(idx++);
    }
    else{ //by column
      for(int i=1;i<=ncol;i++)  //col
        for(int j=1;j<=nrow;j++) //row
          out(j,i)=input(idx++);    
    }
    return out;
  }

  /** convert the Vector as a Matrix eithter by row=1(default) or by column=0,
   * overloading function
   * \ingroup QFC
   * \param input : long vector/array being converted
   * \param nrow : the number of rows for output matrix 
   * \param ncol : the number of columns for output matrix 
   * \param byrow : default as by row, use 1, which fill the each row from top to bottom 
   *  Or any number other than 1 as by column, which fill each column from left to right
   * \return return a matrix which row and column index all starting from 1 
   */
  dvar_matrix vector2matrix(const dvar_vector& input, int nrow, int ncol, int byrow=1)
  {
    if(nrow*ncol != input.size()){
      cerr<<"In vector2matrix(): Defined matrix dimension not fit the input vector size"<<endl; 
      exit(1);
    }
    dvar_matrix out(1,nrow,1,ncol);  
    long  idx=input.indexmin();
    if(byrow==1){ //by row
      for(int i=1;i<=nrow;i++) //row
        for(int j=1;j<=ncol;j++) //col
          out(i,j)=input(idx++);
    }
    else{ //by column
      for(int i=1;i<=ncol;i++)  //col
        for(int j=1;j<=nrow;j++) //row
          out(j,i)=input(idx++);    
    }
    return out;
  }





  

  
  /** determine if two double values are equal within some precision
   * \ingroup QFC
   * \param nVal1 : double value used for comparison
   * \param nVal2 : another double value used for comparison
   * \param nPrecision : the number of decimals 
   * \return return true/false for two double values compare based on some specific number of decimals 
   */
  bool doubleEqual(double nVal1, double nVal2, int nPrecision)
  {
    const double base = 10; 
    // if want equal, you can define an arrange like 
    bool bRet = (((nVal2 - pow(base,-nPrecision)) < nVal1) && (nVal1 < (nVal2 + pow(base,-nPrecision))));
   return bRet;
  }






  /** generate one random uniform from (low,upper)
   * \ingroup QFC
   * \param low : low range 
   * \param upper : high range
   * \param rng :  admb build in random number generator 
   * \return return uniform random number within range (low, upper) 
   */
  double runif(double low, double upper, random_number_generator & rng)
  {      
    return low+ randu(rng)*(upper-low);  //randu() get (0,1)
  }




  /** generate one random normal number N(mu,sigma)
   * \ingroup QFC
   * \param mu : mean
   * \param sigma : std. deviation
   * \param rng :  admb build in random number generator 
   * \return return normal random number N(mu,sigma) 
   */
  double rnorm(double mu, double sigma, random_number_generator & rng)
  {      
    return mu + randn(rng)*sigma; 
  }




  /** generate one random lognormal number LN(mu,sigma)
   * \ingroup QFC
   * \param mu : mean
   * \param sigma : std. deviation
   * \param rng :  admb build in random number generator 
   * \return return lognormal random number LN(mu,sigma) 
   */
  double rlnorm(double mu, double sigma, random_number_generator & rng)
  {      
    return mfexp(mu + randn(rng)*sigma); 
  }





  /** generate random gamma number, pseudo code see http://en.wikipedia.org/wiki/Gamma_distribution ,
   * Gamma(alpha, belta)=x^(alpha-1)*belta^alpha*exp(-belta*x)/gamma(alpha)
   * \ingroup QFC
   * \param alpha : shape parameter, >0  =1/CV^2
   * \param rng :  admb build in random number generator 
   * \return return gamma random number 
   */
  double rgamma(double alpha, random_number_generator& rng) 
  {
    double  v0, v1, v2, fract, em, qm, tmp, gam_n1; 
    int i; 

    //calculate Gamma(n,1) integer part first
    tmp = 1.;
    if (int(alpha) == 0) //which means 0<alpha <1
        gam_n1 = 0;
    else{
        for( i = 1;i<=int(alpha);i++)
            tmp *= randu(rng);   //using modified rnd()
        
        gam_n1 = -1. * log(tmp);
    }

    fract = alpha - int(alpha) + EPS;  //fractional part of alpha
    v0 = QFC_M_E / (QFC_M_E + fract);

    //calculate the fractional gamma(fract,1)
    while(1){
        v1 =  randu(rng);
        v2 =  randu(rng);
        if (v1 <= v0){
            em = pow(v1 / (v0 + EPS), 1. / fract);
            qm = v2 * pow(em, fract - 1.);
        }else{
            em = 1. - log((v1 - v0) / (1. - v0 + EPS));
            qm = v2 * mfexp(-em);
        }
        if (qm <= (pow(em, fract - 1.) * mfexp(-em))) break;        
    }

    return (em + gam_n1);
  }





  /** generate random gamma number, 
   * mean is alpha/belta,  variance is alpha/(belta^2)
   * \ingroup QFC
   * \param alpha : shape parameter, >0  =1/CV^2
   * \param beta : rate =1/scale,inverse of the scale parameter, >0  =1/(mean*CV^2)
   * \param rng :  admb build in random number generator 
   * \return return gamma random number 
   */
  double rgamma(double alpha, double beta, random_number_generator& rng) 
  {return rgamma(alpha,rng)/beta; }





  /** generate random beta(alpha, beta) number, 
   * \ingroup QFC
   * \param alpha : alpha parameter
   * \param beta : beta parameter
   * \param rng :  admb build in random number generator 
   * \return return beta random number 
   */
  double rbeta(double alpha, double beta, random_number_generator& rng) 
  {return rgamma(alpha,rng)/(rgamma(alpha,rng)+rgamma(beta,rng)); }





  /** generate random dirichlet number
   * \ingroup QFC
   * \param shape : shape parameter
   * \param rng :  admb build in random number generator 
   * \return return dirichlet random number 
   */
  dvector rdirichlet(const dvector& shape,random_number_generator& rng)
  {
    double tot=0;
    int ncat=shape.size();
    dvector gam(shape.indexmin(),ncat);
    dvector results(shape.indexmin(),ncat);
    int i;
  
    //generate gamma random number first
    for (i=shape.indexmin(); i<=shape.indexmax(); i++) {
      gam[i]=rgamma(shape[i],rng);        
    }
  
    tot=sum(gam);
    //normalize them by its sum
    for (i=shape.indexmin(); i<=shape.indexmax(); i++) {
      results[i] = gam[i]/tot;
      
      if (results[i]< EPS)
        results[i]= EPS; // not put zero 
      //cout<<results(i)<<endl;
    }
    return results;
  }

