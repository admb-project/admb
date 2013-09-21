These templates can be used to create overloaded functions for ADMB. They contain snippets that should be replaced with text specific to each function.For an example, see ecology_replacements.sh

The first argument to each function is always the data. There are versions written for functions of 1,2, or 3 parameters that can be scalars or vectors when applicable.


Snippets to replace in tmpl1var.cpp	
function;
\f$  \f$
func(
//calculate y(s,s)
//calculate y(v,s)
//calculate y(v,v)

possibly
a ;
a)
x independent
x,

Snippets to replace in tmpl2var.cpp
function;
\f$  \f$
func(
//calculate y(s,s,s)
//calculate y(v,s,s)
//calculate y(v,v,s)
//calculate y(v,s,v)
//calculate y(v,v,v)

possibly
a ;
a,
b ;
b)
x independent
x,

Snippets to replace in tmpl3var.cpp
function;
\f$  \f$
func(
//calculate y(s,s,s,s)
//calculate y(v,s,s,s)
//calculate y(v,v,s,s)
//calculate y(v,s,v,s)
//calculate y(v,v,v,s)
//calculate y(v,s,s,v)
//calculate y(v,v,s,v)
//calculate y(v,s,v,v)
//calculate y(v,v,v,v)

possibly
a ;
a,
b ;
b,
c ;
c)
x independent
x,
