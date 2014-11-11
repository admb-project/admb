// $Id:  $
/** \file ADMB_XMLDoc.h
Definition of class ADMB_XMLDoc. Based on the XMLDocument2 class by Johnoel Ancheta.
   Copyright&copy; 2014 John Sibert
   \author John Sibert
*/

#ifndef __ADMB_XMLDoc__
#define __ADMB_XMLDoc__

#include <fvar.hpp>
#include <admodel.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

using namespace std;


/** Class for handling ADMB data types in XML. 
*/
class ADMB_XMLDoc
{
protected:
   xmlDocPtr doc;            ///< pointer to an instance of xmlDoc
   xmlXPathContext* context; ///< pointer to an in instance of a xmlContext
   xmlNodePtr RootNode;      ///< pointer to root node of document
 
   string XMLFileName;       ///< xml file name (doc->URL)
   string DocRootName;       ///< root name of xml tree (doc->last->name)

   static const char * paramS; ///< string to indicate a "variable" object, possibly defined in PARAMETER_SECTION
   static const char * dataS;  ///< string to indicate a "constant" object, possibly defined in DATA_SECTION
   static const char * statS;  ///< string to indicate fit statistics, possibly computed in PROCEDURE_SECTION

public:
   ADMB_XMLDoc(); ///<  Create new empty xml document.
   /** Create new xml document.
  \param drn String containing the root name of the xml document tree.
  \param prg String containing program name (not currently used).
  \param id String containing indentifier for the model and and data values, e. g., 
  some sort of fit code.
  \param filen Name of the xml file produced.
  */
   ADMB_XMLDoc(const adstring& drn, const adstring& prg, const adstring& id, const adstring file);

  /** Initializes class members in empty xml document.
  \param drn String containing the root name of the xml document tree.
  \param prg String containing program name (not currently used).
  \param id String containing indentifier for the model and and data values, e. g., 
  some sort of fit code.
  \param filen Name of the xml file produced.
  */
   void allocate(const adstring& drn, const adstring& prg, const adstring& id, const adstring file);
   void allocate(const char* s);
  ~ADMB_XMLDoc(); 
   ADMB_XMLDoc(const ADMB_XMLDoc& t); ///< Undefined copy construcor

   int write(void);

   adstring getFileName()const {return adstring(XMLFileName.c_str());};
 
   /** @name XML Creation for AUTODIF and other types
    *  @{
    */
   /** Creates xml element for a variable.
   \param name adstring containing the name of the variable used in the ADMB code; 
   must match the variable named in "t" parameter.
   \param t The variable for with the element is to be 
            created; overloaded for many data types.
   \param title adstring containing a "user-friendly" description of the variable.
   \return 1 if successful; 0 otherwise.
   */
   int createXMLelement(const adstring& name, const double t, const adstring& title);
   int createXMLelement(const adstring& name, const int t, const adstring& title);
   int createXMLelement(const adstring& name, const adstring& t, const adstring& title);
   int createXMLelement(const adstring& name, const adstring_array& t, const adstring& title);
   int createXMLelement(const adstring& name, const ivector& t, const adstring& title);
<<<<<<< HEAD
   int createXMLelement(const adstring& name, const dvector& t, const adstring& title);
   int createXMLelement(const adstring& name, const param_init_bounded_number_vector& t, const adstring& title);
   int createXMLelement(const adstring& name, const param_init_bounded_number_matrix& t, const adstring& title, const int M);
   int createXMLelement(const adstring& name, const imatrix& t, const adstring& title);
   int createXMLelement(const adstring& name, const dmatrix& t, const adstring& title);
=======
   int createXMLelement(const adstring& name, const param_init_bounded_number_vector& t, const adstring& title);
   int createXMLelement(const adstring& name, const param_init_bounded_number_matrix& t, const adstring& title, const int M);
   int createXMLelement(const adstring& name, const imatrix& t, const adstring& title);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79
   /** @} */

   // -----------------------
   /** @name XML Creation for ADMB types
    *  @{
    */
   /** Creates xml element for ADMB types declared in 
       DATA_SECTION and PARAMETER_SECTION.
   \param t The variable for with the element is to be 
            created; overloaded for many data types.
   \param title adstring containing a "user-friendly" description of the variable.
   \return 1 if successful; 0 otherwise.
   */
   int createXMLelement(const data_int& t, const adstring& title);
   //int createXMLelement(const data_number& t, const adstring& title);
   int createXMLelement(const data_vector& t, const adstring& title);
   int createXMLelement(const data_matrix& t, const adstring& title);

   int createXMLelement(const named_dvariable& t, const adstring& title);
   int createXMLelement(const named_dvar_vector& t, const adstring& title);
   int createXMLelement(const named_dvar_matrix& t, const adstring& title);

   int createXMLelement(const param_init_bounded_number& t, const adstring& title);
   int createXMLelement(const param_init_bounded_vector& t, const adstring& title);
   int createXMLelement(const objective_function_value& t);
   /** @} */

   int createXMLcomment(const adstring& t);

   /** Stub. Intended to update xml element value for any ADMB types.
   ADMB needs to be modifited for this to work. One possibility is to 
   change virtual void save_value(BOR_CONST ofstream& ofs,int prec)=0;
   into virtual void save_value(ostream& ofs,int prec)=0;
   \param t element of initial_params::varptr array.
   */ 
   int createXMLelement(const initial_params& t);

   double getDouble(const string& name) const;
   int getInt(const string& name) const;
   adstring getString(const string& name) const;
   adstring_array getADStringArray(const string& name, const int lb, const int ub) const;
   void getADStringArray(const string& name, adstring_array* p) const;
   double getMinb(const string& name) const;
   double getMaxb(const string& name) const;
   int getPhase(const string& name) const;
   /** Returns 3 element "lui" control vector form inint_bounded_number node.
   \param name Name of the variable in the tpl file to be querried.
   \return dvector indexed from 1 to 3. 
   lui(1): estimation phase; 
   lui(2): lower bound; 
   lui(3): upper bound.
   */
   dvector getControlVector(const string& name) const;
   ivector getIvector(const string& name) const;
   ivector getIvector(const string& name, const int lb, const int ub) const; 
   dvector getDvector(const string& name) const;
   dvector getDvector(const string& name, const int lb, const int ub) const; 
   imatrix getImatrix(const string& name) const;
   dmatrix getDmatrix(const string& name) const;
   //dmatrix getDmatrix(const string& name, const int rowmin, const int rowmax,
   //                             const int colmin, const int colmax);

   bool set(const string& name, const double value);
   bool set(const string& name, const dvector& value);
   bool set(const string& name, const dmatrix& value);
   
   int read(const char* parfile);// throw (runtime_error);
   int write(const char* parfile);

protected:

   /** @name Node Creation
    *  @{
    */
   /**  Create new xml node for different types. Generally used
   to contsruct XMLelements in various createXMLelement overloads.
   Uses ostrstream class to process argument.
   \param t Overloaded for different argument types. 
   \param parent Pointer to the node to which the new node will be attached
   \return 1 if successful; 0 otherwise.
   */
    xmlNodePtr createNameNode(const adstring& name, const char* category);

    int createTitleNode(xmlNodePtr parent, const adstring& title);

    int createValueNode(xmlNodePtr parent, const int t);
    int createValueNode(xmlNodePtr parent, const double t);
    int createValueNode(xmlNodePtr parent, const ivector&  t);
    int createValueNode(xmlNodePtr parent, const imatrix&  t);
    int createValueNode(xmlNodePtr parent, const dvector&  t);
    int createValueNode(xmlNodePtr parent, const dmatrix&  t);
    int createValueNode(xmlNodePtr parent, const adstring&  t);
    int createValueNode(xmlNodePtr parent, const adstring_array&  t);
    //int createValueNode(xmlNodePtr parent, const param_init_bounded_number&  t);
    int createIndexNode(xmlNodePtr parent, const int lb, const int ub);
    int createIndexNode(xmlNodePtr parent, const int rlb, const int rub,
                                           const int clb, const int cub);

    int createBoundsNode(xmlNodePtr parent, const double min, const double max);
    int createBoundsNode(xmlNodePtr parent, const dvector& min, const dvector& max);
    int createBoundsNode(xmlNodePtr parent, const dmatrix& min, const dmatrix& max);
    int createActiveNode(xmlNodePtr parent, const int t);
    int createActiveNode(xmlNodePtr parent, const ivector& t);
    int createActiveNode(xmlNodePtr parent, const imatrix& t);
    int createPhaseNode(xmlNodePtr parent, const int t);
    int createPhaseNode(xmlNodePtr parent, const ivector& t);
    int createPhaseNode(xmlNodePtr parent, const imatrix& t);
   /** @} */

   string* getContentStringArray(const string& xpath) const;
   string getContentString(const string& xpath) const;
   string getContentString(const string& name, const string& tag) const;
   int getIndexInt(const string& name);
   ivector getIndexIvector(const string& name);

   bool setContent(const string& name, const string& value);

}; // class ADMB_XMLDoc

/**
  Implements allocate(...) instances of named ADMB_XMLDoc generated
  by tpl2cpp in the DATA_SECTION
*/
class init_xml_doc : public ADMB_XMLDoc, public model_name_tag
{
public:
  /// create unallocated instance
  init_xml_doc(void) : ADMB_XMLDoc(), model_name_tag() {;}
  /**
  Allocate member variables.
  \param s Root name for input XML file. Default file extension is ".xml".
  */
  void allocate(const char * s);
  friend class model_parameters;
};


#endif //#ifndef __ADMB_XMLDoc__
