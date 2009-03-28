/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 * 
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 * 
 * License:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



#if !defined(_DOUBLE_IND_)
#define _DOUBLE_IND_ 
  class double_index_guts;
  class double_index_type;
  class double_number_index;
  class double_vector_index;
  class double_matrix_index;
  class double_i3_index;

  class pre_double_index_type
  {
    const double_index_type * a;
    int i;
  public:
    pre_double_index_type( const double_index_type * _a,int _i) : a(_a),i(_i){}
    friend class double_index_type;
  };


  class ad_double
  {
  protected:
    double d;
  public:
    operator double () const { return d;}
    ad_double(BOR_CONST double& _d, BOR_CONST adkludge& k) : d(_d) {}
    ad_double(double _d) : d(_d) {}
    ad_double(const double_index_type& it);
    ad_double make_ad_double(double _d) {adkludge adk; return ad_double(d,adk);}
    ad_double& operator = (const ad_double&);
  };


  class double_index_guts
  {
    friend class ad_double;
  protected:
    int * ncopies;
  public:
    virtual double_index_guts * operator [] (int) = 0;
    virtual int  isdouble(void) const { return 1;}
    virtual operator double () { cerr << "Error in index_type"
     " -- object not dereferenced enough" << endl; exit(1); return 1;}
    virtual int indexmin(void)=0;
    virtual int indexmax(void)=0;
    double_index_guts(); 
    double_index_guts(const double_index_guts& ig);
    virtual ~double_index_guts();
    friend class double_index_type;
  };


  class double_index_type
  {
    double_index_guts * p;
  public:
    double ddouble(void) const;
    int isdouble(void) const { return p->isdouble();}
    double_index_type(double x);
    //index_type(const data_int& x);
    double_index_type(BOR_CONST dvector& x);
    double_index_type(BOR_CONST dmatrix& x);
    double_index_type(BOR_CONST d3_array& x);
    double_index_type(BOR_CONST pre_double_index_type& pit);
    double_index_type(const double_index_type& pit);
    //index_type (i4_array& x) { p = new i4_index(x);}
    ~double_index_type ();
    double_index_type operator [] (int i);
    double_index_type operator () (int i);
    double_index_type operator [] (int i) const; 
    double_index_type operator () (int i) const; 
    int indexmin(void) const { return p->indexmin();}
    int indexmax(void) const { return p->indexmax();}
    friend class ad_integer;
  };

  class double_index : public ad_double, public double_index_guts
  {
  private:
    virtual int  isdouble_(void) const { return 0;}
    virtual double_index_guts * operator [] (int i);
    virtual int indexmin(void){return 1;}
    virtual int indexmax(void){return 1;}
  public:
    virtual ~double_index() {}
    double_index(double i) : ad_double(i) {}
    // only overload this for number_index ... will fail for other classes 
    virtual operator double () { return d;} 
    friend class double_index_type;
  };

  class dvector_index : public dvector, public double_index_guts
  {
    virtual double_index_guts * operator [] (int i)
    {
      return new double_index(dvector::operator [](i));
    }
  public:
    //vector_index(BOR_CONST ivector& v) : ivector(v){}
    dvector_index(BOR_CONST dvector& v);
    virtual ~dvector_index();
    virtual int indexmin(void){return dvector::indexmin();}
    virtual int indexmax(void){return dvector::indexmax();}
    friend class double_index_type;
  };

  class dmatrix_index : public dmatrix, public double_index_guts
  {
  private:
    virtual double_index_guts * operator [] (int i);
    //{
      //return new dvector_index(dmatrix::operator [](i));
    //}
  public:
    virtual ~dmatrix_index();
    dmatrix_index(BOR_CONST dmatrix& v) : dmatrix(v){}
    virtual int indexmin(void){return dmatrix::rowmin();}
    virtual int indexmax(void){return dmatrix::rowmax();}
    friend class double_index_type;
  };

  class d3_index : public d3_array, public double_index_guts
  {
    virtual double_index_guts * operator [] (int i)
    {
      return new dmatrix_index(d3_array::operator [](i));
    }
  public:
    d3_index(d3_array& v) : d3_array(v){}
    virtual int indexmin(void){return d3_array::slicemin();}
    virtual int indexmax(void){return d3_array::slicemax();}
    friend class index_type;
  };
#endif
