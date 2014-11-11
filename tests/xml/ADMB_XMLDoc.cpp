// $Id: $
/** \file ADMB_XMLDoc.cpp 
Source code for class ADMB_XMLDoc. Based on the XMLDocument2 class by Johnoel Ancheta.
    \author John Sibert
*/
#include "ADMB_XMLDoc.h"
#include "admodel.h"
#include <stdexcept>
#include "trace.h"
//#include <gdbprintlib.h>

using namespace std;

const char* ADMB_XMLDoc::dataS = (const char*)"CON";
const char* ADMB_XMLDoc::paramS = (const char*)"VAR";
const char* ADMB_XMLDoc::statS = (const char*)"STAT";

ADMB_XMLDoc::ADMB_XMLDoc()
{
   doc = NULL;
   context = NULL;
   RootNode = NULL;
   xmlInitParser();
}

ADMB_XMLDoc::ADMB_XMLDoc(const adstring& drn, const adstring& prg, const adstring& id, const adstring filen)
{
   allocate(drn, prg, id, filen);
}

void ADMB_XMLDoc::allocate(const adstring& drn, const adstring& prg, const adstring& id, const adstring filen)
{
   doc = xmlNewDoc(BAD_CAST "1.0");
   //file << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
   XMLFileName = (const char*)filen;
  
   DocRootName = (const char*)drn;
   RootNode = xmlNewNode(NULL, BAD_CAST DocRootName.c_str());
   //file << "<?xml-stylesheet type=\"text/xsl\" href=\"ADMB.xsl\"?>" << endl;
   //xmlNewProp(ss, BAD_CAST "type",BAD_CAST "text/xsl");
   //xmlNewProp(ss, BAD_CAST "href",BAD_CAST "ADMB.xsl");
   xmlNodePtr ss = xmlNewPI(BAD_CAST "xml-stylesheet", 
                BAD_CAST "type=\"text/xsl\" href=\"ADMB.xsl\"");
   xmlNewProp(RootNode, BAD_CAST "id", BAD_CAST (const char*)id);
   xmlDocSetRootElement(doc, RootNode);
   xmlAddPrevSibling(RootNode,ss);
   
   xmlNodePtr CNode = xmlNewComment (BAD_CAST "a simple comment in the previos node");
   xmlAddPrevSibling(RootNode,CNode);


   /*
   if (1)
   {
   xmlSaveFormatFileEnc(BAD_CAST XMLFileName.c_str(),doc,"UTF-8", 1);

    exit(1);
    }
   */
 }

/** Terminates the document tree
*/
ADMB_XMLDoc::~ADMB_XMLDoc()
{
    //Free the global variables that may
    //have been allocated by the parser.
    xmlCleanupParser();
} 
 
/** Write the contents of doc to a file.
   @param parfile character string containing filename to write the xml tree.
   \return Number of bytes written
 */
int ADMB_XMLDoc::write(void)
{
   int nbyte = 0;
   nbyte = xmlSaveFormatFileEnc((const char*)XMLFileName.c_str(),doc, "UTF-8", 1);
   return  nbyte;
}

int ADMB_XMLDoc::createXMLcomment(const adstring& t)
{
   xmlNodePtr node = xmlNewComment (BAD_CAST (const char*)t); 
   //xmlAddPrevSibling(RootNode,node);
   xmlAddChild(RootNode,node);
   return ((node == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const double t, const adstring& title)
{
   // create name node for variable 
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   
   // create title node and add to name node
   createTitleNode(node,title);

   // create value node and add to name node
   createValueNode(node,t);

   // add name node to root
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
 }

int ADMB_XMLDoc::createXMLelement(const named_dvariable& _t, const adstring& title)
{
   ADUNCONST(named_dvariable, t);
   adstring name(t.get_name());

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
   createValueNode(node,value(t));
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const named_dvar_vector& _t, const adstring& title)
{
   ADUNCONST(named_dvar_vector, t);
   adstring name(t.get_name());
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
<<<<<<< HEAD
   createIndexNode(node,i1,i2);
   createValueNode(node,value(t));
=======
   createValueNode(node,value(t));
   createIndexNode(node,i1,i2);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79

   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const named_dvar_matrix& _t, const adstring& title)
{
   ADUNCONST(named_dvar_matrix, t);
   adstring name(t.get_name());
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
   const int i1 = t.colmin();
   const int i2 = t.colmax();
   const int j1 = t.rowmin();
   const int j2 = t.rowmax();
   createIndexNode(node,j1,j2,i1,i2);
   createValueNode(node,value(t));
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
} 



int ADMB_XMLDoc::createXMLelement(const data_int& _t, const adstring& title)
{
   ADUNCONST(data_int, t);
   adstring name(t.get_name());

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   createValueNode(node,(int)t);
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}
/*
int ADMB_XMLDoc::createXMLelement(const adstring& name,const data_int& _t, const adstring& title)
{
   ADUNCONST(data_int, t);

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   createValueNode(node,(int)t);
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}
*/
int ADMB_XMLDoc::createXMLelement(const data_vector& _t, const adstring& title)
{
   ADUNCONST(data_vector, t) 
   adstring name(t.get_name());
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();
   createIndexNode(node, i1,i2);
   createValueNode(node,t);
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
} 

int ADMB_XMLDoc::createXMLelement(const data_matrix& _t, const adstring& title)
{
   ADUNCONST(data_matrix, t) 
   adstring name(t.get_name());
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   const int i1 = t.colmin();
   const int i2 = t.colmax();
   const int j1 = t.rowmin();
   const int j2 = t.rowmax();
   createIndexNode(node,j1,j2,i1,i2);
   createValueNode(node,t);
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
} 

int ADMB_XMLDoc::createXMLelement(const param_init_bounded_number& _t, const adstring& title)
{
   ADUNCONST(param_init_bounded_number, t);
   adstring name(t.get_name());
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
   createValueNode(node,value(t));
   createBoundsNode(node,t.get_minb(),t.get_maxb());
   createActiveNode(node, active(t));
   createPhaseNode(node,t.phase_start);
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const param_init_bounded_number_matrix& _t, const adstring& title, const int M)
{
   ADUNCONST(param_init_bounded_number_matrix, t) 
   //adstring name(t.get_name());
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
   //const int j1 = t.colmin();
   //const int j2 = t.colmax();
   //const int i1 = t.rowmin();
   //const int i2 = t.rowmax();
   const int i1 = 1;
   const int i2 = M;
   dmatrix vt(i1,i2); //,j1,j2);
   dmatrix maxb(i1,i2);
   dmatrix minb(i1,i2);
   imatrix phase(i1,i2);
   imatrix active(i1,i2);
   int j1,j2;
   for (int i = i1; i <= i2; i++)
   {
      j1 = t(i).indexmin();
      j2 = t(i).indexmax();
      vt(i).allocate(j1,j2);
      maxb(i).allocate(j1,j2);
      minb(i).allocate(j1,j2);
      phase(i).allocate(j1,j2);
      active(i).allocate(j1,j2);
      for (int j = j1; j <= j2; j++)
      {
         vt(i,j) = value(t(i,j));
         maxb(i,j) = t(i,j).get_maxb();
         minb(i,j) = t(i,j).get_minb();
         phase(i,j) = t(i,j).phase_start;
         active(i,j) =  (phase(i,j) > 0);
      }
   }
<<<<<<< HEAD
=======
   createValueNode(node,vt);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79
   createIndexNode(node,i1,i2,j1,j2);
   createBoundsNode(node,minb,maxb);
   createPhaseNode(node,phase);
   createActiveNode(node,active);
<<<<<<< HEAD
   createValueNode(node,vt);
=======
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79

   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}

xmlNodePtr ADMB_XMLDoc::createNameNode(const adstring& name, const char* category)
{
   xmlNodePtr node = xmlNewNode(NULL, BAD_CAST (const char*)name);
   if (category)
     xmlNewProp(node, BAD_CAST "category", BAD_CAST category);
   return node;
}


int ADMB_XMLDoc::createTitleNode(xmlNodePtr parent, const adstring& title)
{
   xmlNodePtr tNode = xmlNewNode(NULL, BAD_CAST "title");
   xmlNodeAddContent(tNode,BAD_CAST (const char*)title);
   xmlAddChild(parent,tNode);

   return ((tNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const adstring& t)
{
   xmlNodePtr tNode = xmlNewChild(parent,NULL, BAD_CAST "value", 
                                  BAD_CAST (const char*)t);
   return ((tNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const int t)
{
   ostringstream ostr;
   ostr << t;
   // create value node and add to name node
   xmlNodePtr vNode = xmlNewNode(NULL, BAD_CAST "value");
   xmlNodeAddContent(vNode, BAD_CAST (const char*)ostr.str().c_str());
   xmlAddChild(parent,vNode);

   return ((vNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const double t)
{
   ostringstream ostr;
   ostr << setprecision(16) << t;
   // create value node and add to name node
   xmlNodePtr vNode = xmlNewNode(NULL, BAD_CAST "value");
   xmlNodeAddContent(vNode, BAD_CAST (const char*)ostr.str().c_str());
   xmlAddChild(parent,vNode);

   return ((vNode==NULL));
}

/*
int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const param_init_bounded_number&  t)
{
   ostringstream ostr;
   ostr << setprecision(16) << value(t);
   // create value node and add to name node
   xmlNodePtr vNode = xmlNewNode(NULL, BAD_CAST "value");
   xmlNodeAddContent(vNode, BAD_CAST (const char*)ostr.str().c_str());
   xmlAddChild(parent,vNode);

   return ((vNode==NULL));
}
*/

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const dvector& t)
{
   ostringstream ostr;
   ostr << setprecision(16) << t;
   xmlNodePtr vNode = xmlNewChild(parent,NULL, BAD_CAST "value", 
                                  BAD_CAST (const char*)ostr.str().c_str());

   return ((vNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const dmatrix& t)
{
   ostringstream ostr;
   ostr << setprecision(16) << t;
   xmlNodePtr vNode = xmlNewChild(parent,NULL, BAD_CAST "value", 
                                  BAD_CAST (const char*)ostr.str().c_str());

   return ((vNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const adstring_array& _t)
{
   ADUNCONST(adstring_array, t)
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();
   ostringstream ostr;
   for (int i = i1; i <= i2; i++)
   {
      ostr << t(i);
      if (i < i2)
        ostr << " ";
   }
   xmlNodePtr vNode = xmlNewChild(parent,NULL, BAD_CAST "value", 
                                  BAD_CAST (const char*)ostr.str().c_str());

   return ((vNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const ivector& t)
{
   ostringstream ostr;
   ostr << t;
   xmlNodePtr vNode = xmlNewChild(parent,NULL, BAD_CAST "value", 
                                  BAD_CAST (const char*)ostr.str().c_str());

   return ((vNode==NULL));
}

int ADMB_XMLDoc::createValueNode(xmlNodePtr parent, const imatrix& t)
{
   ostringstream ostr;
   ostr << t;
   xmlNodePtr vNode = xmlNewChild(parent,NULL, BAD_CAST "value", 
                                  BAD_CAST (const char*)ostr.str().c_str());

   return ((vNode==NULL));
}

int ADMB_XMLDoc::createBoundsNode(xmlNodePtr parent,  const double min, const double max)
{
   xmlNodePtr bNode = xmlNewNode(NULL, BAD_CAST "bounds");
   xmlNodePtr mNode = xmlNewNode(NULL, BAD_CAST "min");
   ostringstream ostr;
   ostr << min << ends;
   xmlNodeAddContent(mNode, BAD_CAST (const char*)ostr.str().c_str());
   xmlAddChild(bNode,mNode);

   mNode = xmlNewNode(NULL, BAD_CAST "max");
   // "rewind" the ostr, but don't forget the << ends
   ostr.seekp(ios_base::beg);
   ostr << max << ends;
   xmlNodeAddContent(mNode, BAD_CAST (const char*)ostr.str().c_str());
   xmlAddChild(bNode,mNode);
   
   xmlAddChild(parent,bNode);

   return ((bNode==NULL));

}

int ADMB_XMLDoc::createBoundsNode(xmlNodePtr parent,  const dvector& min, const dvector& max)
{
   xmlNodePtr node = createNameNode("bounds",NULL);
   ostringstream ostr;
   ostr << min << ends;
   xmlNewChild(node, NULL, BAD_CAST "min", BAD_CAST ostr.str().c_str());
   
   ostr.seekp(ios_base::beg);
   ostr << max << ends;
   xmlNewChild(node, NULL, BAD_CAST "max", BAD_CAST ostr.str().c_str());

   
   xmlNodePtr tNode = xmlAddChild(parent,node);

   return ((tNode==NULL));

}

int ADMB_XMLDoc::createBoundsNode(xmlNodePtr parent,  const dmatrix& min, const dmatrix& max)
{
   xmlNodePtr node = createNameNode("bounds",NULL);
   ostringstream ostr;
   ostr << min << ends;
   xmlNewChild(node, NULL, BAD_CAST "min", BAD_CAST ostr.str().c_str());
   
   ostr.seekp(ios_base::beg);
   ostr << max << ends;
   xmlNewChild(node, NULL, BAD_CAST "max", BAD_CAST ostr.str().c_str());
   
   xmlNodePtr tNode = xmlAddChild(parent,node);

   return ((tNode==NULL));

}

int ADMB_XMLDoc::createActiveNode(xmlNodePtr parent,  const int t)
{
   xmlNodePtr node = xmlNewNode(NULL, BAD_CAST "active");
   ostringstream ostr;
   ostr << t;
   xmlNodeAddContent(node, BAD_CAST (const char*)ostr.str().c_str());

   xmlAddChild(parent,node);
   
   return ((node==NULL));
}

int ADMB_XMLDoc::createActiveNode(xmlNodePtr parent,  const ivector& t)
{
   ostringstream ostr;
   ostr << t;
   xmlNodePtr node = xmlNewChild(parent, NULL, BAD_CAST "active",
                                 BAD_CAST (const char*)ostr.str().c_str());

   return ((node==NULL));
}

int ADMB_XMLDoc::createActiveNode(xmlNodePtr parent,  const imatrix& t)
{
   ostringstream ostr;
   ostr << t;
   xmlNodePtr node = xmlNewChild(parent, NULL, BAD_CAST "active",
                                 BAD_CAST (const char*)ostr.str().c_str());

   return ((node==NULL));
}

int ADMB_XMLDoc::createPhaseNode(xmlNodePtr parent,  const int t)
{
   xmlNodePtr node = xmlNewNode(NULL, BAD_CAST "phase");
   ostringstream ostr;
   ostr << t;
   xmlNodeAddContent(node, BAD_CAST (const char*)ostr.str().c_str());

   xmlAddChild(parent,node);
   
   return ((node==NULL));
}

int ADMB_XMLDoc::createPhaseNode(xmlNodePtr parent,  const ivector& t)
{
   ostringstream ostr;
   ostr << t;
   
   xmlNodePtr node = xmlNewChild(parent,NULL, BAD_CAST "phase",
                         BAD_CAST (const char*)ostr.str().c_str());
   
   return ((node==NULL));
}

int ADMB_XMLDoc::createPhaseNode(xmlNodePtr parent,  const imatrix& t)
{
   ostringstream ostr;
   ostr << t;
   
   xmlNodePtr node = xmlNewChild(parent,NULL, BAD_CAST "phase",
                         BAD_CAST (const char*)ostr.str().c_str());
   
   return ((node==NULL));
}

int ADMB_XMLDoc::createXMLelement(const objective_function_value& _t)
{
   ADUNCONST(objective_function_value, t)
   adstring name(t.get_name());
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::statS);
   createTitleNode(node, adstring("Fit Statistics"));
   
   ostringstream ostr;
   ostr << initial_params::nvarcalc() << ends;
   xmlNewChild(node, NULL, BAD_CAST "n", BAD_CAST ostr.str().c_str());

   createValueNode(node,value(t));

   ostr.seekp(ios_base::beg);
   ostr << t.fun_without_pen << ends;
   xmlNewChild(node, NULL, BAD_CAST "fun_without_pen", BAD_CAST ostr.str().c_str());

   ostr.seekp(ios_base::beg);
   ostr << setprecision(16) << t.gmax << ends;
   xmlNewChild(node, NULL, BAD_CAST "gmax", BAD_CAST ostr.str().c_str());
   
   xmlNodePtr tNode =  xmlAddChild(RootNode,node);
   return ((tNode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const param_init_bounded_number_vector& _t, const adstring& title)
{
   ADUNCONST(param_init_bounded_number_vector, t) 
   // adstring name(t.get_name());
   // no member named 'get_name' in 'param_init_bounded_number_vector'
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();
   dvector minb(i1,i2);
   dvector maxb(i1,i2);
   ivector phase(i1,i2);
   ivector activef(i1,i2);
   dvector vt(i1,i2);
   for (int i = i1; i <= i2; i++)
   {
      minb(i) = t(i).get_minb();
      maxb(i) = t(i).get_maxb();
      phase(i) = t(i).phase_start;
      activef(i) = active(t(i));
      vt(i) = value(t(i));
   } 

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
<<<<<<< HEAD
=======
   createValueNode(node,vt);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79
   createIndexNode(node,i1,i2);
   createBoundsNode(node,minb,maxb);
   createActiveNode(node,activef);
   createPhaseNode(node,phase);
<<<<<<< HEAD
   createValueNode(node,vt);
=======
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79

   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const adstring_array& _t, const adstring& title)
{
   ADUNCONST(adstring_array, t)
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
<<<<<<< HEAD
   createIndexNode(node,i1,i2);
   createValueNode(node,t);
=======
   createValueNode(node,t);
   createIndexNode(node,i1,i2);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79
   
   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}


int ADMB_XMLDoc::createXMLelement(const adstring& name, const ivector& t, const adstring& title)
{
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();

<<<<<<< HEAD
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   createIndexNode(node,i1,i2);
   createValueNode(node,t);

   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const dvector& t, const adstring& title)
{
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   createIndexNode(node,i1,i2);
   createValueNode(node,t);
=======
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
   createValueNode(node,t);
   createIndexNode(node,i1,i2);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79

   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const imatrix& _t, const adstring& title)
{
   ADUNCONST(imatrix, t)
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   const int i1 = t.colmin();
   const int i2 = t.colmax();
   const int j1 = t.rowmin();
   const int j2 = t.rowmax();
<<<<<<< HEAD
   createIndexNode(node,j1,j2,i1,i2);
   createValueNode(node,t);
 
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const dmatrix& _t, const adstring& title)
{
   ADUNCONST(dmatrix, t)
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   const int i1 = t.colmin();
   const int i2 = t.colmax();
   const int j1 = t.rowmin();
   const int j2 = t.rowmax();
   createIndexNode(node,j1,j2,i1,i2);
   createValueNode(node,t);
=======
   createValueNode(node,t);
   createIndexNode(node,j1,j2,i1,i2);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79
 
   xmlNodePtr nnode = xmlAddChild(RootNode,node);
   return ((nnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const param_init_bounded_vector& _t, const adstring& title)
{
   ADUNCONST(param_init_bounded_vector, t) 
   adstring name(t.get_name());
   const int i1 = t.indexmin();
   const int i2 = t.indexmax();

   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::paramS);
   createTitleNode(node,title);
<<<<<<< HEAD
   createIndexNode(node,i1,i2);
   createValueNode(node,value(t));
=======
   createValueNode(node,value(t));
   createIndexNode(node,i1,i2);
>>>>>>> eb3141094430ef5950422c9c35664b311e187a79
   createBoundsNode(node,t.get_minb(),t.get_maxb());
   createActiveNode(node,active(t));
   createPhaseNode(node,t.phase_start);

   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createIndexNode(xmlNodePtr parent, const int lb, const int ub)
{
   xmlNodePtr node = createNameNode("index",NULL);
   ostringstream ostr;
   ostr << lb << ends;
   xmlNewChild(node, NULL, BAD_CAST "lb", BAD_CAST ostr.str().c_str());
   ostr.seekp(ios_base::beg);
   ostr << ub << ends;
   xmlNewChild(node, NULL, BAD_CAST "ub", BAD_CAST ostr.str().c_str());
   xmlNodePtr tnode = xmlAddChild(parent,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createIndexNode(xmlNodePtr parent, const int nrl, const int nrh,
                                           const int ncl, const int nch)
{
   // imat.cpp: imatrix::imatrix(int nrl, int nrh, int ncl, int nch)
   xmlNodePtr node = createNameNode("index",NULL);
   ostringstream ostr;
   ostr << nrl << ends;
   xmlNewChild(node, NULL, BAD_CAST "nrl", BAD_CAST ostr.str().c_str());
   ostr.seekp(ios_base::beg);
   ostr << nrh << ends;
   xmlNewChild(node, NULL, BAD_CAST "nrh", BAD_CAST ostr.str().c_str());
   ostr.seekp(ios_base::beg);
   ostr << ncl << ends;
   xmlNewChild(node, NULL, BAD_CAST "ncl", BAD_CAST ostr.str().c_str());
   ostr.seekp(ios_base::beg);
   ostr << nch << ends;
   xmlNewChild(node, NULL, BAD_CAST "nch", BAD_CAST ostr.str().c_str());

   xmlNodePtr tnode = xmlAddChild(parent,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const adstring& t, const adstring& title)
{
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   createValueNode(node,t);
   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

int ADMB_XMLDoc::createXMLelement(const adstring& name, const int t, const adstring& title)
{
   xmlNodePtr node = createNameNode(name, ADMB_XMLDoc::dataS);
   createTitleNode(node,title);
   createValueNode(node,t);
   xmlNodePtr tnode = xmlAddChild(RootNode,node);
   return ((tnode == NULL));
}

 /**
 Read and parse and xml file. Reports errors for ill-formed xml tree.
 \param parfile XMLFileName
 */
int ADMB_XMLDoc::read(const char* parfile)
{
   if (parfile == 0) {
      return -1;
   }

   doc = xmlParseFile(parfile);
   if (doc == NULL) 
   {
      cerr << "Error parsing " << parfile << endl;
      //xmlErrorPtr ErrorPtr1 = xmlGetLastError();
      ad_exit(1);
   }
   XMLFileName = string((char*)(doc->URL));
   DocRootName = string((char*)(doc->last->name));

   context = xmlXPathNewContext(doc);
   if (context == NULL)
   {
      ad_exit(1);
   }

   return 0;
}


/**
   \param name Variable name of devarialbe to fetch
   \return Value of name in xml node 
*/
double ADMB_XMLDoc::getDouble(const string& name) const
{
   double d = 0.0;
   string s = getContentString(name,"value");
   if (!s.empty()) {
      d = strtod(s.c_str(),0);
   }
   else {
      throw runtime_error("Error: XPath=\"" + name + "\" does not exist.\n");
   }

   return d;
}

int ADMB_XMLDoc::getInt(const string& name) const
{
   int d = 0;
   string s = getContentString(name,"value");
   if (!s.empty()) {
      d = atoi(s.c_str());
   }
   else {
      throw runtime_error("Error: XPath=\"" + name + "\" does not exist.\n");
   }

   return d;
}

adstring ADMB_XMLDoc::getString(const string& name) const
{
   adstring d;
   string s = getContentString(name,"value");
   if (!s.empty()) {
      d = adstring(s.c_str());
   }
   else {
      throw runtime_error("Error: XPath=\"" + name + "\" does not exist.\n");
   }

   return d;
}

/*
<fleet_names category="CON">
  <title>Names of fleets to use in the model</title>
  <value> fjpl jppl pgpl sbpl jpps</value>
</fleet_names>

#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}
*/

/** Extract adstring_array from xml document.
This function causes a segment violation on return. 
The problem seems to be passing the array.
\param name Name of the variable.
\parm lb Upper bound of array.
\parm ub Lower bound of array.
\return Reference to adstring_array&
*/
adstring_array ADMB_XMLDoc::getADStringArray(const string& name, const int lb, const int ub) const
{
   string s = getContentString(name,"value");
   adstring_array a(lb,ub);

   istringstream istr(s);
 
   for (int i = lb; i <= ub; i++)
   {
     istr >> a(i);
   }


   return a;
}

void ADMB_XMLDoc::getADStringArray(const string& name, adstring_array* p) const
{
   string s = getContentString(name,"value");
   char * pch = NULL;
   pch = strtok((char*)s.c_str()," ");

   const int lb = p->indexmin();
   const int ub = p->indexmax();
   for (int i = lb; ((i <= ub)&&(pch != NULL)); i++)
   {
      adstring tmp(pch);
      (*p)(i) = tmp; //adstring((const char*)pch);
      pch = strtok (NULL, " ");
   }
}

ivector ADMB_XMLDoc::getIvector(const string& name) const
{
   string xpath = "/"+DocRootName + "/" + name + "/index/";
   string s = getContentString(xpath+"lb");
   int lb = atoi(s.c_str());
   s = getContentString(xpath+"ub");
   int ub = atoi(s.c_str());
   ivector d = getIvector(name, lb, ub);

   return d;
}

ivector ADMB_XMLDoc::getIvector(const string& name, const int lb, const int ub) const
{
   string s = getContentString(name,"value");
   istringstream istr(s);
   ivector d(lb,ub);
   istr >> d;
   return d;
}

dvector ADMB_XMLDoc::getDvector(const string& name) const
{
   string xpath = "/"+DocRootName + "/" + name + "/index/";
   string s = getContentString(xpath+"lb");
   int lb = atoi(s.c_str());
   s = getContentString(xpath+"ub");
   int ub = atoi(s.c_str());
   dvector d = getDvector(name, lb, ub);

   return d;
}

dvector ADMB_XMLDoc::getDvector(const string& name, const int lb, const int ub) const
{
   string s = getContentString(name,"value");
   istringstream istr(s);
   dvector d(lb,ub);
   istr >> d;
   return d;
}
/*
double ADMB_XMLDoc::getMinNumberMatrixBounds(const string& name) const
{
   string xpath;
   string s;
   xpath = "/"+DocRootName + "/" + name + "/index/"; 
   s = getContentString(xpath+"nrl");
   int nrl = atoi(s.c_str());
   s = getContentString(xpath+"nrh");
   int nrh = atoi(s.c_str());
   s = getContentString(xpath+"ncl");
   int ncl = atoi(s.c_str());
   s = getContentString(xpath+"nch");
   int nch = atoi(s.c_str());

   dmatrix m(nrl, nrh, ncl, nch);
   xpath = "/"+DocRootName + "/" + name + "/bounds/min"; 
   s = getContentString(xpath);
   istringstream istr(s);
   istr >> m;
   double b = min(m);
   return(b);
}

double ADMB_XMLDoc::getMaxNumberMatrixBounds(const string& name) const
{
   string xpath;
   string s;
   xpath = "/"+DocRootName + "/" + name + "/index/"; 
   s = getContentString(xpath+"nrl");
   int nrl = atoi(s.c_str());
   s = getContentString(xpath+"nrh");
   int nrh = atoi(s.c_str());
   s = getContentString(xpath+"ncl");
   int ncl = atoi(s.c_str());
   s = getContentString(xpath+"nch");
   int nch = atoi(s.c_str());

   dmatrix m(nrl, nrh, ncl, nch);
   xpath = "/"+DocRootName + "/" + name + "/bounds/max"; 
   s = getContentString(xpath);
   istringstream istr(s);
   istr >> m;
   double b = max(m);
   return(b);
}
*/

double ADMB_XMLDoc::getMinb(const string& name) const
{
   string xpath = "/"+DocRootName + "/" + name + "/bounds/"; 
   string s = getContentString(xpath+"min");
   double d = strtod(s.c_str(),0);
   return(d);
}

double ADMB_XMLDoc::getMaxb(const string& name) const
{
   string xpath = "/"+DocRootName + "/" + name + "/bounds/"; 
   string s = getContentString(xpath+"max");
   double d = strtod(s.c_str(),0);
   return(d);
}

//   int getPhase(const string& name) const;
int ADMB_XMLDoc::getPhase(const string& name) const
{
   string s = getContentString(name,"phase");
   int d = atoi(s.c_str());
   return(d);
}

dvector ADMB_XMLDoc::getControlVector(const string& name) const
{
   dvector lui(1,3);
   lui(1) = getPhase(name);
   lui(2) = getMinb(name);
   lui(3) = getMaxb(name);
   return(lui);
}

/*
    <index>
      <nrl>1</nrl>
      <nrh>80</nrh>
      <ncl>1</ncl>
      <nch>40</nch>
    </index>
*/
imatrix ADMB_XMLDoc::getImatrix(const string& name) const
{
   string xpath = "/"+DocRootName + "/" + name + "/index/"; 
   string s = getContentString(xpath+"nrl");
   int nrl = atoi(s.c_str());
   s = getContentString(xpath+"nrh");
   int nru = atoi(s.c_str());

   // you must call istringstream::clear() 
   // in order to reuse the istringstream instance
   istringstream istr;

   s = getContentString(xpath+"ncl");
   int ncl = atoi(s.c_str());
   //istr.str(s);
   //ivector ncl(nrl,nru);
   //istr >> ncl;

   s = getContentString(xpath+"nch");
   int nch = atoi(s.c_str());
   //istr.clear();
   //istr.str(s);
   //ivector nch(nrl,nru);
   //istr >> nch;

   imatrix m(nrl, nru, ncl, nch);

   s =  getContentString(name,"value");
   istr.clear();
   istr.str(s);
   istr >> m;

   return m;
}

/*
    <index>
      <nrl>1</nrl>
      <nrh>1</nrh>
      <ncl>1</ncl>
      <nch>19</nch>
    </index>
*/ 
dmatrix ADMB_XMLDoc::getDmatrix(const string& name) const
{
   string xpath = "/"+DocRootName + "/" + name + "/index/"; 
   string s = getContentString(xpath+"nrl");
   int nrl = atoi(s.c_str());
   s = getContentString(xpath+"nrh");
   int nrh = atoi(s.c_str());

   // you must call istringstream::clear() 
   // in order to reuse the istringstream instance
   istringstream istr;

   s = getContentString(xpath+"ncl");
   int ncl = atoi(s.c_str());
   //istr.str(s);
   //ivector ncl(nrl,nru);
   //istr >> ncl;

   s = getContentString(xpath+"nch");
   int nch = atoi(s.c_str());
   //istr.clear();
   //istr.str(s);
   //ivector nch(nrl,nru);
   //istr >> nch;

   dmatrix m(nrl, nrh, ncl, nch);

   s =  getContentString(name,"value");
   istr.clear();
   istr.str(s);
   istr >> m;

   return m;
}

/**
 * @param xpathfull absolute element xpath
 */
string ADMB_XMLDoc::getContentString(const string& xpathfull) const 
{
   string value;
   xmlXPathObject* xpathObj = NULL;
   xpathObj = xmlXPathEvalExpression((xmlChar*)xpathfull.c_str(), context);
   if (xpathObj != 0)
   {

      if (xpathObj->type == XPATH_NODESET) {
         xmlNodeSet* xmlnodeset = xpathObj->nodesetval;
         const int max = xmlnodeset->nodeNr;
         for (int i = 0; i < max; i++) {
            xmlNode* xmlnode = xmlnodeset->nodeTab[i];
            if (xmlnode != 0 && xmlnode->children)
            {
               value += (char*)xmlnode->children->content;
            }
         }
      }
   }
   if (value.empty())
   {
      cerr << "Error: Unable to extract XPath, \"" << xpathfull 
           << "\", from XML tree in file " << XMLFileName << endl;
      ad_exit(1);
   }

   return value;
}

/**
   \param name Element name
   \param tag A specific tag, i. e., "value"
 */
string ADMB_XMLDoc::getContentString(const string& name, const string& tag) const 
{
   string value;
   string xpathfull = "/"+DocRootName + "/" + name + "/" + tag;
   value = getContentString(xpathfull);

   return value;
}

/**
 * @param xname absolute element xpath
 */
string* ADMB_XMLDoc::getContentStringArray(const string& xpathfull) const 
{
   string* value = NULL;
   xmlXPathObject* xpathObj = xmlXPathEvalExpression((xmlChar*)xpathfull.c_str(), context);
   if (xpathObj == 0) {
      return value;
   }

   if (xpathObj->type == XPATH_NODESET) 
   {
      xmlNodeSet* xmlnodeset = xpathObj->nodesetval;
      const int max = xmlnodeset->nodeNr;
      value = new string[max];
      for (int i = 0; i < max; i++) 
      {
         xmlNode* xmlnode = xmlnodeset->nodeTab[i];
         if (xmlnode != 0 && xmlnode->children)
         {
             value[i] = (char*)xmlnode->children->content;
         }
      }
   }

   return value;
}


