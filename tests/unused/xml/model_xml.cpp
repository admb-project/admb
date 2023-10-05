// $Id:  $
/** \file model_xml.cpp
Allocate(...) functions for ADMB types declared in DATA_SECTION and PARAMETER_SECTION
of .tpl file.
   Copyright&copy; 2014 ADMB Foundation
   \author John Sibert
*/

#include <admodel.h>
#include "ADMB_XMLDoc.h"
#include "trace.h"

void init_adstring::operator = (const adstring& t);
{ 
   *this = t; 
}

void init_xml_doc::allocate(const char * s)
{
   adstring run_name(ad_comm::adprogram_name);
   adstring xml_name = run_name+adstring(".xml");
   read(xml_name);
   //int ret = read(xml_name);
}

//   init_adstring::allocate(init_xml_doc&, const char [15])’

void init_adstring::allocate(init_xml_doc& xml, const char* s)
{
   TRACE(s)
   TRACE(xml.getString(s));
   adstring tmp = xml.getString(s);
   TRACE(tmp)
   *this = tmp;
   TRACE(*this)
   model_name_tag::allocate(s);
   HERE
}

void param_init_number::allocate(init_xml_doc& xml, char const* s)
{
   allocate(1,s);               // call the default allocator
   *this = xml.getDouble(s);    // set the initial value
   model_name_tag::allocate(s); // set the name
}

void data_int::allocate(init_xml_doc& xml, char const* s)
{
   val = xml.getInt(s);
   model_name_tag::allocate(s);
}

void data_vector::allocate(init_xml_doc& xml, char const* s)
{
   *this = xml.getDvector(s);
   model_name_tag::allocate(s);
}

void data_matrix::allocate(init_xml_doc& xml, char const* s)
{
   *this = xml.getDmatrix(s);
   model_name_tag::allocate(s);
}

void param_init_bounded_number::allocate(init_xml_doc& xml, char const* s)
{
   const double minb = xml.getMinb(s);
   const double maxb = xml.getMaxb(s);
   const int phase_start = xml.getPhase(s);

   allocate(minb, maxb, phase_start, s);
   model_name_tag::allocate(s);

   // overwrite the initial value from the previous allocate
   *this  = xml.getDouble(s);
}

