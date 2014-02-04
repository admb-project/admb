// $Id:  $
/** \file model_xml.cpp
Allocate(...) functions for ADMB types declared in DATA_SECTION and PARAMETER_SECTION
of .tpl file.
   Copyright&copy; 2014 ADMB Foundation
   \author John Sibert
*/

#include "ADMB_XMLDoc.h"
#include "admodel.h"
#include "trace.h"

void init_xml_doc::allocate(const char * s)
{
   adstring run_name(ad_comm::adprogram_name);
   adstring xml_name = run_name+adstring(".xml");
   int ret = read(xml_name);
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

