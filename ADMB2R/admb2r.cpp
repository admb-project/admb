/********************************************************************************
*
* ADMB2R
*
* Routines for writing data from AD Model Builder to a file read by R with "dget"
*
* Jennifer Martin, Mike Prager and Andi Stephens
* NOAA, National Marine Fisheries Service
*
* jlmartin@usgs.gov
* mike.prager@noaa.gov
*
* Original version:  February 2006
*
* Many of these routines are implemented with templates and overloaded functions.
*
* In order to make them compiler-independent, overloaded functions are defined for
* all types anticipated for use.  These functions are gathered together under a
* single comment block describing them as a group.
*
* Overloaded functions are often paired with a similarly named "do_" function or
* template. The overloaded function passes various combinations of options to the
* "do_" function for processing.
*
*********************************************************************************/
/* CHANGELOG
*  Version 0.50   Andi   May 2006      Revised for compatibility
*  Version 0.85   MHP   8 Aug 2006     Changed names of ...info_vector to ...info_list
                                       to agree with actual R structure.  Changed
                                       default of argument "writestamp" to true (as
                                       documented). Moved documentation from Word to
                                       LaTeX, as Word file has deteriorated.
*  Version 0.99   Andi  11 Aug 2006    Commented out non-integer functs for
                                       writing row/col names.
                                       Added test_missing function.
*  Version 1.00   MHP   16 Aug 2006    Added factor of 2 to missing test, changed
                                       declaration of dum_matrix to four parameters for
                                       compatibility with older versions of ADMB.
*  Version 1.00   MHP   30 Aug 2006    Corrected missing-value test. Inserted some
                                       vector routines that had been removed in error.
*  Version 1.00   JLM   01 Sep 2006    Switch the default behavior of writing out missing
                                       values to false. Edited do_wrt_r_namevector to
                                       independently assign default vector min/max.
                                       Add additional details to some comment sections
                                       for clarity.
*  Version 1.01   JLM   09 Mar 2007    Fixed bug that didn't write out default row.names
                                       for a dataframe (close_r_df). Added function to
                                       write out a vector using one statement
                                       (wrt_r_complete_vector). Fixed a bug that didn't
                                       write error messages in many cases. Removed
                                       periods at end of first two comment lines for
                                       clarity (do_open_r_file).
* Version 1.1    JLM   12 Oct 2007     Expanded compatibility on multiple compilers.
* Version 1.11   MHP   19 Dec 2008     No changes to ADMB2R - renamed some files for
                                       Example 1 to avoid minor ADMB 9.x bug.
* Version 1.12   MHP   03 Sep 2009     Incorporated declarations fixes by J. Sibert.
                                       This removed many compatibility errors.
* Version 1.13   MHP   14 Sep 2009     Changed na_vector declar from int* to bool*.
* Version 1.14   MHP   15 Sep 2009     Added "endl" after 25 values to limit line
                                       lengths in wrt_r_complete_vector, wrt_r_matrix,
                                       and wrt_r_df_col.
* Version 1.15   JLM   13 Oct 2009     Added a new function "print_wrap" to wrap row
                                       and column names and .Names vectors after the
                                       25th comma-delimited element. Functions that
                                       needed mofication: close_r_matrix, close_r_df,
                                       close_r_vector, do_wrt_r_complete_vector,
                                       close_r_info_list, close_r_list, close_r_file,
                                       do_df_col_wrt_num. Modified the checking for
                                       no remainders method in wrt_r_complete_vector,
                                       wrt_r_matrix, and wrt_r_df_col to a method that
                                       increments a counter for better consistency.
*********************************************************************************/
#include <ctime>         // needed for timestamp
#include <string>        // string manipulation routines
#include <vector>        // vectors -- no need to manage array allocation by hand
#include <iomanip>       // needed to set precision
#include <iostream>      // needed for converting between data types
#if (__GNUC__) && (__GNUC__ < 3)
  // gcc 2.95 <strstream> header
  #include <strstream>
  typedef strstream my_sstream;
#else
  // use <sstream> header
  #include <sstream>
  typedef std::stringstream my_sstream;
#endif

using namespace std;

// GLOBAL VARIABLES

const char* version = "1.15";               // Version number
int i;                                      // For indices


// ** File I/O Variables

string outfile;                             // output file name
ofstream rfile;                             // ofstream for output file
ofstream errfile;                           // output stream for error message
string err_msg = "ADMB2R error messages:  ";   // error message


// ** General Housekeeping Variables

int level;                                  // Current nesting level for object names
bool OKflag = true;                         // error flag
string mflag;                               // is open object a matrix or data frame
string vecflag;                             // is open vector a list or simple vector
vector<bool> ObjDoneFlag;                   // flag to track object completion
vector<string> prevObj;                     // ( names of previous object, used in keeping
                                            // ( track of whether the object is complete

// ** Data Writing Variables

double missing = -99999.;                   // No data/missing data indicator
double epsilon = 1e-6;                      // A small number
bool writeNA = false;                       // Flag to turn on/off writing NA for missing data
bool naflag = false;                        // Flag to signal use of NA matrix or vector
imatrix dum_matrix;                         // Dummy variable in use of NA matrix
ivector dum_vector;                         // Dummy variable in use of NA vector
int dim1 = -1;                              // matrix dimensions or data frame min/max
int dim2 = -1;                              // matrix dimensions or data frame min/max
int digits = -1;                            // ( Digits of data precision; -1 will write data
                                            // ( as it appears in ADMB; 0 writes integers

// ** R Names Variables

vector<string> Rnames;                      // vector of names to write when closing the R object
string colnames;                            // list of names to be used for R columns
string rownames;                            // list of names to be used for R rows
int rowflag = 0;                            // Flag to write matrix or data frame row names
int colflag = 0;                            // Flag to write matrix or data frame column names
const char* quote = "\"";                   // Double-quote character (")
const char* cquote = ",\"";                 // comma plus double quote (,")

//=====================================================================================
// convert
//
// Utility routine to convert one type to another, e.g., double to string
//
// Use:
//     out_type - type desired
//     in_value - type to convert from
//=====================================================================================
template <class out_type, class in_value>
out_type convert(const in_value & t) {
    my_sstream stream;
    stream << t; // insert value to stream
    out_type result; // store conversion’s result here
    stream >> result; // write value to result
    return result;
} // end convert

//=====================================================================================
// test_missing
//
// Utility routine to test for the missing value.
// Returns true if the input value is the missing value.
//
//=====================================================================================

bool test_missing(double num) {
    return (fabs(num - missing) < epsilon);
}

//=====================================================================================
// write_errmsg
//
// Utility routine to write error message string (global) to screen and to logfile.
//
// No arguments.
//=====================================================================================
void write_errmsg() {
    // write error message to screen and file
    if ( err_msg != "ADMB2R error messages:  " ) {
        cout << "**** ADMB2R Error: Please check file admb2r.log for error messages." << endl;
    }
    errfile.open ("admb2r.log");
    errfile << err_msg << endl;
    errfile.close();
} // end write_errmsg

//=====================================================================================
// print_wrap
//
// Function to limit line lengths when printing to the rfile. Limits lines to 25 comma-
// delimited elements.
//
// ARGUMENTS:
//     s - the string to parse
//     a - (optional) any text to append to the string before writing a new line, for
//         example, any closing punctuation
//=====================================================================================
void print_wrap(string s, string a = "") {
string::size_type pos = s.find_first_of(",");
string::size_type istart = 0;
string  temp;
int counter = 0;

// first, append any additional text (such as closing punctuation)
s = s + a;

if (pos < s.length() ) { // check to see if there are some comma-delimited tokens
    while (pos != string::npos) {
        counter = counter + 1;
		if (counter == 25 ) {                            // when the 25th token is
	        temp = s.substr(istart, pos - istart + 1);   // found, extract the substring
		    rfile << temp << endl;                       // and print
		    istart = pos + 1;
		    counter = 0;
	    }
        pos = s.find_first_of(",", pos + 1); // find the next comma delimeter
    }

    // print the last batch of token, if there are any
    if (istart < s.length() ) {
        temp = s.substr(istart, s.length() - istart);
		// only print if there are more than spaces
		pos = temp.find_first_not_of(" ");
		if (pos < s.length()) {
            rfile << temp << endl;
		}
    }
} else {
    // no comma-delimited tokens found; print entire string
	rfile << s << endl;
	}
} // end print_wrap

//=====================================================================================
// do_open_r_file
//
// Open the output file and initialize the R data object.
//
// Arguments are passed to do_open_r_file by the overloaded open_r_file function.
//
// ARGUMENTS
//   fname - name of output file
//   numdigits - data precision
//          digits = -1 (default) or digits = 0 writes data out with default precision
//          of 6; digits > 0 will write ALL data out in scientific notation with the
//          specified number of digits after the decimal place.
//=====================================================================================
void do_open_r_file(const char* fname, int numdigits) {
    // initialize nesting level
    level = 0;

    // initialize dummy matrix
    dum_matrix.allocate(1,1,1,1);
   // initialize dummy vector
   dum_vector.allocate(1,1);

    // intialize object completion tracking variables
    ObjDoneFlag.clear();
    ObjDoneFlag.push_back(true);
    prevObj.clear();
    prevObj.push_back("");

    // initialize list of all R objects
    Rnames.clear();
    Rnames.push_back("c(");

    // initialize row/column names and vector of list objects
    colnames.erase();
    rownames.erase();

    // Open the R output file
    outfile = fname;
    rfile.open (fname);
    // check to make sure it opened OK
    if ( ! rfile.is_open() ) {
        err_msg = err_msg + "\n**** ADMB2R Error: Unable to open " + outfile;
        OKflag = false;
      write_errmsg();
        return;
    }

    // write a brief file header
    rfile <<"### This file written with ADMB2R version " << version << endl;
    rfile <<"### Read into R or S with x=dget('";
    rfile <<  fname << "')";
    rfile << endl;
    rfile << endl;

    // begin overall R structure (list)
    rfile << "structure(list(";
    rfile << endl;
    rfile << endl;

    // set precision based on the digits value specified.
    digits = numdigits;
    if ( digits > 0 ) {
        rfile << setiosflags (ios::scientific);
        rfile.precision(digits);
    }

} // End do_open_r_file

//=====================================================================================
// open_r_file
//
// Overloaded function to get the R file name, precision, and set the missing value
// indicator.
//
// Allows user to specify one of three combinations of open_r_file:
// open_r_file(fname)
// open_r_file(fname, numdigits)
// open_r_file(fname, numdigits, ismissing)
//
// ARGUMENTS:
//   fname - name of output file.
//          This argument is passed to do_open_rfile for further handling.
//   numdigits - (optional) data precision
//          This argument is passed to do_open_rfile for further handling.
//          digits = -1 (default) or digits = 0 writes data out with default precision
//          of 6; digits > 0 will write ALL data out in scientific notation with the
//          specified number of digits after the decimal place.
//   ismissing - (optional) indicates the value that is used to represent a missing datum.
//          If ismissing is specified, data matching this value will be replaced by NA in
//          the R file.
//======================================================================================
void open_r_file(const char* fname, int numdigits = -1) {

   // no missing value supplied, so turn off flag to write NAs to file
   writeNA = false;

   // pass info to do_open_r_file for processing
   do_open_r_file(fname, numdigits);

} // End open_r_file (numdigits)

//=====================================================================================
void open_r_file(const char* fname, int numdigits, double ismissing) {

   // missing is value supplied, so turn on flag to write NAs to file
   writeNA = true;
   // asign missing value to global variable
   missing = ismissing;

   // pass info to do_open_r_file for processing
   do_open_r_file(fname, numdigits);

} // End open_r_file (numdigits, ismissing)


//======================================================================================
// close_r_file
//
// Close R object and do housekeeping
//
// No arguments.
//======================================================================================
void close_r_file() {

    if ( OKflag == false ) {
        write_errmsg();
        if ( rfile.is_open() ) rfile.close();
        return; // exit if there was an earlier error
    }

    // check that there is at least one item in file
    if ( Rnames[0] == "c(" ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: No data written to " + outfile;
        OKflag = false;
        write_errmsg();
        return;
    }

    // check level; if level not equal to zero, one of the list objects didn't close properly
    if ( level != 0 ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Close list object with close_r_list().";
        write_errmsg();
        OKflag = false;
        return;
    }

    // check that final object is complete
    if ( ObjDoneFlag[0] = false ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: " + prevObj[level] + " is not complete!";
        OKflag = false;
        write_errmsg();
        return;
    }

    rfile << endl;
    rfile << "### Calling close_r_file -- last call in program." << endl;
    rfile << ")," << endl;
    rfile << endl;

	rfile << ".Names = ";
	print_wrap(Rnames[0], "))");

    rfile.close();

    // clear global variables: Rnames, colnames, rownames, ListNames
    Rnames.clear();
    colnames.erase();
    rownames.erase();
    prevObj.clear();
    prevObj.push_back("");
    ObjDoneFlag.clear();
    ObjDoneFlag.push_back(true);

    // re-set nesting level
    level = 0;

    write_errmsg();

} // end close_r_file


//=====================================================================================
// wrt_r_comment
//
// Write a comment to the output file.  Cannot be used before open_r_file.
//
// ARGUMENTS:
//     text - text to write as comment
//=====================================================================================
void wrt_r_comment(const char* text) {
    if ( ! rfile.is_open() ) { // exit if file hasn't been opened yet
        OKflag = false;
        err_msg = err_msg + "**** ADMB2R Error:  No open file\n";
      write_errmsg();
        return;
    }

    // if something goes wrong
    if ( rfile.bad() ) {
        if ( rfile.is_open() ) rfile.close();
        OKflag = false;
        err_msg = err_msg + "**** ADMB2R Error: Unable to write to " + outfile + "\n";
      write_errmsg();
        return;
    }

    rfile << "### " << text << endl;
} // end wrt_r_comment


//=====================================================================================
//  reg_Rnames
//
//  Adds object names to Names list, checks that previous object is complete,
//  and does other housekeeping chores
//
//  Called by open_r_matrix, open_r_list, open_r_info_list, open_r_vector, and open_r_df.
//
//  ARGUMENTS:
//    name - name of object to write
//    description - type of R object (used in error reporting if object is incomplete).
//======================================================================================
int reg_Rnames(const char* name, string description) {

    // check for previous object completion
    if ( OKflag == false ) return 0; // exit if there was an earlier error
    if ( prevObj[level] != "" ) {      // make sure there are previous objects to check
        //previous object is incomplete
        if ( ObjDoneFlag[level] == false ) {
            if ( rfile.is_open() ) rfile.close();
            err_msg = err_msg + "\n**** ADMB2R Error: " + prevObj[level] + " is still open";
            OKflag = false;
         write_errmsg();
            return 0;
        }
    }

    // add object name to list
    // if item not first in list add comma separator
    if ( Rnames[level] != "c(" ) {
        Rnames[level] = Rnames[level] + ", ";
        rfile << ", ";
    }
    Rnames[level] = Rnames[level] + quote + name + quote;

    // intialize object completion variables
    prevObj[level] = description + name;
    ObjDoneFlag[level] = false;

    if ( OKflag == true ) return 1;
    else return 0;

}  // end reg_Rnames


//======================================================================================
// add_colname
//
// Utility to add column name to list, with comma as necessary
//
// ARGUMENTS:
//      name - string to output.
//======================================================================================
void add_colname(const char* name) {
    if ( colnames != "c(" ) {
        colnames = colnames + ", ";  // Object is not first item; preceed with a comma
    }

    colnames = colnames + quote + name + quote;  // Add name to list

} // end add_colname


//======================================================================================
// add_rowname
//
// Utility to add row name to list, with comma as necessary
//
// ARGUMENTS:
//      name - string to output.
//======================================================================================
void add_rowname(const char* name) {
    if ( rownames != "c(" ) {
        rownames = rownames + ", ";  // Object is not first item; preceed with a comma
    }

    rownames = rownames + quote + name + quote;  // Add name to list

} // end add_rowname

//======================================================================================
// check_rownames
//
// In writing row or column names, determines whether the item to write is a row or a column.
// Performs bounds-checking.
//
// Called from do_wrt_r_namevector and do_wrt_r_numvector
//
// ARGUMENTS
//     start - first value in the series, or index of the first element in the vector
//     stop - last value in the series, or index of the last element in the vector
//     inc - how much to increment the values in the series
//======================================================================================
template <class T>
string check_rownames (T start, T stop, T inc) {

    string return_val = "error";            // return string indicating error, row or col

    T nitems = ((stop - start)/inc) + 1;    // number of items to write
    T diff = dim2 - dim1 + 1;               // number of values in matrix or data frame

    int M_dim;                              // dimension of row or column
    string cr_names;                        // variable to specify row or column names

    // determine if object is matrix or data frame and whether item is row or column names
    if ( mflag == "matrix" && rowflag == 2 && rownames == "" ) { // process rows first
        cr_names = rownames;                // item to write is row names for matrix
        return_val = "row";
    } else {
        if ( mflag == "matrix" && colflag == 2 && colnames == "" ) {
            cr_names = colnames;            // item to write is column names for matrix
            return_val = "col";
        }

        else {
            if ( mflag == "data frame" ) {
                cr_names = rownames;        // item is row names for data frame
                return_val = "row";
            }
        }
    }

    // validate number of items
    if ( mflag == "matrix" ) {              // this is a matrix object
        if ( cr_names == rownames ) {       // process rows first
            M_dim = dim1;
        }                                   // get matrix row dimension
        else {
            if ( cr_names == colnames ) M_dim = dim2;
        }                                   // get matrix col dimension

        // check to see if # elements OK
        if ( nitems != M_dim ) {
            if ( rfile.is_open() ) rfile.close();
            err_msg = err_msg + "\n**** ADMB2R Error: Number of matrix indices in wrt_r_namevector for ";
            err_msg = err_msg + prevObj[level] + " shoud be " + convert<string>(M_dim);
            OKflag = false;
         write_errmsg();
            return "error";
        }
    }

    // end of branch for matrix, begin branch for data frame

    else {
        // check that this is being called from a matrix or data frame
        if ( mflag == "" ) {
            if ( rfile.is_open() ) rfile.close();
            err_msg = err_msg + "\n**** ADMB2R Error: Invalid use of wrt_r_namevector for " + prevObj[level];
            OKflag = false;
         write_errmsg();
            return "error";
        }
        // check that number of items to print is the same as the data frame
        if ( nitems != diff ) {
            if ( rfile.is_open() ) rfile.close();
            err_msg = err_msg + "\n**** ADMB2R Error: Number of items to write in wrt_r_namevector for " ;
            err_msg = err_msg + prevObj[level] + " shoud be " + convert<string>(diff);
            OKflag = false;
         write_errmsg();
            return "error";
        }
    }
    return return_val;
}; // end check_rownames

//======================================================================================
// open_r_matrix
//
// Opens the matrix object and does housekeeping tasks
//
// ARGUMENTS:
//      name - name of matrix to write to file.
//======================================================================================

void open_r_matrix (const char* name) {

    // add info object name to list and check for object completion
    int flag = reg_Rnames(name, "Matrix Object ");
    if ( flag == 0 ) return;

    // set matrix/data frame flag for wrt_r_namevector
    mflag = "matrix";

    rfile << name << " = structure(c(" << endl;
};

//======================================================================================
// close_r_matrix
//
// Closes the matrix object and does housekeeping tasks
//
// No arguments.
//======================================================================================
void close_r_matrix() {
    if ( OKflag == false ) return;    // exit if there was an earlier error

    // check that row and column names are not empty
    if (rownames.empty() ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Please add row names to ";
        err_msg = err_msg + prevObj[level] + " using wrt_r_namevector";
        OKflag = false;
      write_errmsg();
        return;
    }
    if (colnames.empty() ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Please add column names to ";
        err_msg = err_msg + prevObj[level] + " using wrt_r_namevector";
        OKflag = false;
      write_errmsg();
        return;
    }

    rfile << ".Dimnames = list(" << endl;

    // Write row info
    print_wrap(rownames, ", ");

    // write out row/column names and rest of object
    print_wrap(colnames, "))");
    rfile << endl;

    // re-set matrix/data frame flag for wrt_r_namevector
    mflag.erase();

    // set object complete flag
    ObjDoneFlag[level] = true;

    // clear row/col names and dimensions and write flags for next use
    rownames.erase();
    colnames.erase();
    rowflag = 0;
    colflag = 0;
    dim1 = -1;
    dim2 = -1;

    // if something goes wrong
    if ( rfile.bad() ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Unable to write to " + outfile;
        OKflag = false;
      write_errmsg();
        return;
    }
} // end close_r_matrix

//=====================================================================================
// do_wrt_r_matrix
//
// Write a matrix subobject to the R data object.
// Matrices differ from data frames in that columns need not have names,
// and they are of uniform type in all columns, e.g. double.
//
// After this function is used, the column names must be written separately
// to complete the matrix.  That is done because the column names may or may
// not be the same as the column indices.  (Row names are assumed to be the
// same as the row indices, generally years.)
//
// Arguments are passed to do_wrt_r_matrix by the overloaded wrt_r_matrix function.
//
// ARGUMENTS:
//   xx - the matrix
//   na_matrix - a boolean matrix indicating which positions in the xx matrix
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA.
//====================================================================================
template <class T>
void do_wrt_r_matrix (const T& xx, imatrix& na_matrix) {

    int ir, ic;                      // row/column iterators in for statement
    int ra, rz, ca, cz;              // for matrix bounds
	int counter;                     // counter to limit line lengths

    ra = xx.rowmin();                // Get starting row index
    rz = xx.rowmax();                // Get ending row index
    ca = xx.colmin();                // Get starting column index
    cz = xx.colmax();                // Get ending column index

    // Write the matrix data
    for ( ic=ca; ic<=cz; ic++ ) {
        counter = 0;
		for ( ir=ra; ir<=rz; ir++ ) {
            counter++;

			// if value is the missing value indicator, and we're
            // using a missing value "value",  write "NA" instead
            if ( test_missing(convert<double>(xx(ir,ic))) && writeNA == true ) {
                rfile << "NA";
            }
            // if instead we're using a matrix of booleans to
            // indicate the position of missing values, check
            // to see if this position is a missing value
            else if (naflag && na_matrix[ir][ic]){
                rfile << "NA";
            }
            // otherwise use the value we're given.
            else {
                rfile << xx(ir,ic);
            }
            // write proper punctuation
            if ( ic==cz && ir==rz ) {
                rfile << "),";
            } else {
                rfile << ", ";
				if (counter == 25) {
			    rfile << endl;   // Limit line lengths
				counter = 0;
				}
            }
        }
		rfile << endl;
    }

    // Write dimensions of the matrix and save to dim1 and dim2
    i = rz-ra+1;     // # of row elements
    dim1 = i;
    rfile << ".Dim = c(" << i;
    i = cz-ca+1;    // # of column elements
    dim2 = i;
    rfile << "," << i << ")," << endl;

    //set matrix row and column names
    string temp;
    if ( rowflag == 0 ) rownames = "NULL";
    if ( rowflag == 1 ) {                   // write matrix row indices
        rownames = "c(";
        for ( ir=ra; ir<=rz; ir++ ) {
            temp = convert <string> (ir);   //convert index (integer) to string
            rownames = rownames + quote + temp + quote; //add index to list
            if ( ir==rz )
                rownames = rownames + ")";  // add appropriate punctuation
            else
                rownames = rownames + ", ";
        }
    }
    if ( rowflag == 2 ) rownames.erase();    // write row names with wrt_r_namevector

    if ( colflag == 0 ) colnames = "NULL";
    if ( colflag == 1 ) {                   // write matrix col indices
        colnames = "c(";
        for ( ic=ca; ic<=cz; ic++ ) {
            temp = convert <string> (ic);   //convert index (integer) to string
            colnames = colnames + quote + temp + quote; //add index to list
            if ( ic==cz )
                colnames = colnames + ")";  // add appropriate punctuation
            else
                colnames = colnames + ", ";
        }
    }
    if ( colflag == 2 ) colnames.erase();    // write column names with wrt_r_namevector

}; // end do_wrt_r_matrix

//======================================================================================
// wrt_r_matrix
//
// Overloaded function to write a matrix object.
// Defined here for types dvar_matrix, dmatrix, and imatrix.
//
// ARGUMENTS
//   xx - the matrix
//      This argument is passed to do_wrt_r_matrix for further handling.
//   rowoption, coloption - flags for whether to write row names and column names. Optional.
//      0 = write NULL for row or column (Default).
//      1 = write names with same index as matrix.
//      2 = write names with a vector or sequence of numbers.
//   isna - is an NA_matrix supplied. Optional.
//      false = no matrix will be supplied (Default). true = a NA matrix will follow.
//   na_matrix - (optional) a boolean matrix indicating which positions in the xx matrix
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA. This argument is passed to do_wrt_r_matrix
//      for further handling.
//======================================================================================
void wrt_r_matrix(const dvar_matrix& xx, int rowoption = 0, int coloption = 0,
                  bool isna = false, imatrix& na_matrix = dum_matrix) {

    // Set global flags
    rowflag = rowoption;
    colflag = coloption;
    naflag = isna;

    do_wrt_r_matrix<dvar_matrix> (xx, na_matrix);

} // wrt_r_matrix_wrt (dvar_matrix)
//======================================================================================
void wrt_r_matrix(const dmatrix& xx, int rowoption = 0, int coloption = 0,
                  bool isna = false, imatrix& na_matrix = dum_matrix) {

    // Set global flags
    rowflag = rowoption;
    colflag = coloption;
    naflag = isna;

    do_wrt_r_matrix<dmatrix> (xx, na_matrix);

} // wrt_r_matrix_wrt (dmatrix)
//======================================================================================
void wrt_r_matrix(const imatrix& xx, int rowoption = 0, int coloption = 0,
                  bool isna = false, imatrix& na_matrix = dum_matrix) {

    // Set global flags
    rowflag = rowoption;
    colflag = coloption;
    naflag = isna;

    do_wrt_r_matrix<imatrix> (xx, na_matrix);

} // end wrt_r_matrix (imatrix)


//======================================================================================
// do_wrt_r_namevector
//
// Function template for writing ADMB vector type row or column items
// Called from overloaded wrt_r_namevector functions.
//
// ARGUMENTS:
//     rowvec = the vector to use
//     start = position in vector at which to start writing
//     stop = position in vector at which to end writing
//======================================================================================
template <class T>
void do_wrt_r_namevector (const T& rowvec, int start, int stop) {

    string temp;
    string cr_names;                            // temp name for row or column names list

    // if using defaults (start=0, stop=0) then get vector bounds
    if ( start == 0 && stop == 0 ) {
        start = (rowvec).indexmin();
        stop = (rowvec).indexmax();
    } else if ( stop == 0 ) {
        stop = (rowvec).indexmax();
    }

    // do error checking and get which item (row or column names) to write
    string test = check_rownames<int> (start, stop, 1);
    if ( test == "error" ) return;

    if ( test == "row" ) cr_names = rownames;
    else cr_names = colnames;

    // now assign values to row or column names
    cr_names = "c(";
    for ( i=start; i<=stop; i++ ) {
        temp = convert <string> (rowvec[i]);        //convert vector to string
        cr_names = cr_names + quote + temp + quote; //add index to list
        if ( i==stop ) {
            cr_names = cr_names + ")";
        } else {
            cr_names = cr_names + ", ";
        }
    }

    if ( test == "col" )  colnames = cr_names;      // re-assign back to row- or colnames
    else rownames = cr_names;

}; // end do_wrt_r_namevector
//======================================================================================
// do_wrt_r_numvector
//
// Function template for writing row or column items using a series of numbers
// Called from wrt_r_namevector
//
// ARGUMENTS:
//     start = value to start the series
//     stop = value to end the series
//     inc = the increment between series values
//======================================================================================
template <class T>
void do_wrt_r_numvector (const T& start, const T& stop, T inc) {

    string temp;
    string cr_names; // temp name for row or column names list
    T iter;          // iterator

    // do error checking and get which item (row or column names) to write
    string test = check_rownames<T> (start, stop, inc);
    if ( test == "error" ) return;

    if ( test == "row" ) cr_names = rownames;
    else cr_names = colnames;

    // now assign values to row or column names
    cr_names = "c(";
    temp = convert <string> (start);
    cr_names = cr_names + quote + temp + quote;
    iter = start + inc;

    while ( iter<=stop ) {
        temp = convert <string> (iter);
        cr_names = cr_names + ", " + quote + temp + quote;
        iter = iter + inc;
    }

    cr_names = cr_names + ")";
    if ( test == "col" )  colnames = cr_names;  // re-assign back to rownames or colnames
    else rownames = cr_names;

}; // End do_wrt_r_numvector

//======================================================================================
// wrt_r_namevector
//
// Overloaded function to write matrix or data frame row/column names.
// Defined here for int and ivector.
// (The functions for ADMB dvector and dvar_vector types have been commented out to
//  prevent possible rounding errors.)
//
// Arguments
//    start - value to start row/column names with
//    stop - value to end row/column names with
//    inc - value to increment row/column names. Optional.
//====================================================================================
void wrt_r_namevector(const int& start, const int& stop, int inc = 1) {
    if ( OKflag == false ) return; // exit if there was an earlier error

    do_wrt_r_numvector<int> (start, stop, inc);

} // end wrt_r_namevector (int)

////====================================================================================
void wrt_r_namevector(const ivector& rowvec, int start = 0, int stop = 0) {
    if ( OKflag == false ) return; // exit if there was an earlier error

    do_wrt_r_namevector<ivector> (rowvec, start, stop);

} // end wrt_r_namevector (ivector)

////====================================================================================
//void wrt_r_namevector(const dvector& rowvec, int start = 0, int stop = 0) {
//    if ( OKflag == false ) return; // exit if there was an earlier error
//
//    do_wrt_r_namevector<dvector> (rowvec, start, stop);
//
//}  // end wrt_r_namevector (dvector)
//
//====================================================================================
//void wrt_r_namevector(const dvar_vector& rowvec, int start = 0, int stop = 0) {
//    if ( OKflag == false ) return; // exit if there was an earlier error
//
//    do_wrt_r_namevector<dvar_vector> (rowvec, start, stop);
//
//} // end wrt_r_namevector (dvar_vector)


//======================================================================================
// open_r_list
//
// Initalize a LIST object: add object to list of R objects, increment level and
// initialize the level checking variables
//
// ARGUMENTS:
//      name - name of object
//=======================================================================================
void open_r_list(const char* name) {
    // add info object name to list and check for object completion
    int flag = reg_Rnames(name, "List Object ");
    if ( flag == 0 ) return;

    // write beginning of structure to file
    rfile << name << " = structure(list(" << endl;
    rfile << endl;

    // increase level and initialize variables
    level = level + 1;
    Rnames.push_back("c(");

    // initialize object completion checking variables
    prevObj.push_back("");
    ObjDoneFlag.push_back(true);

} // end open_r_list


//======================================================================================
// close_r_list
//
// Close LIST object, decrement level and do housekeeping
//
// No arguments.
//======================================================================================
void close_r_list() {
    if ( OKflag == false ) return; // exit if there was an earlier error

    // check that at least one item is included in list
    if ( Rnames[level] == "c(" ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: No data written to " + prevObj[level];
        OKflag = false;
      write_errmsg();
        return;
    }

    // add closing punctuation and list of subobjects
	rfile << "), .Names = ";
	print_wrap(Rnames[level], "))");
    rfile << endl;

    // clear/remove global variables for this level
    Rnames.erase(Rnames.end(),Rnames.end());
    Rnames[level] = "c(";

    // decrease level
    level = level - 1;
    // set object complete flag
    ObjDoneFlag[level] = true;


    // if something goes wrong
    if ( rfile.bad() ) {
        if ( rfile.is_open() ) rfile.close();
        OKflag = false;
        err_msg = err_msg + "\n**** ADMB2R Error: Unable to write to " + outfile;
      write_errmsg();
        return;
    }
} // end r_list_close


//=====================================================================================
//   open_r_info_list
//
//   Initialize an information vector object and optionally write its DATE subobject.
//   The info-vector contains descriptive information about the data.
//   All major R objects should begin with an info-vector object.
//
//   ARGUMENTS
//       name - name of INFO object (e.g., "metadata")
//       writestamp - whether or not to write the date subobject. Optional.
//======================================================================================
void open_r_info_list(const char* name, bool writestamp=true) {
    // add info object name to list and check for object completion
    int flag = reg_Rnames(name, "Info Object ");
    if ( flag == 0 ) return;

    rfile << name << " = structure(list(" << endl;

    // inform the world there's an info_list open
    vecflag = "info";

    // initialize names of info data
    colnames = "c(";
    if ( writestamp ) {

        // get date and time
        time_t ltime;
        struct tm *today;
        char tmpbuf[50];

        time( &ltime );  // get time as a long integer.
        today = localtime( &ltime );  // convert to local time.
        strftime( tmpbuf, 50,
                  "%A, %d %b %Y at %H:%M:%S", today );  // apply formatting.

        // write date and time stamp
        rfile << "date = " << quote << tmpbuf << quote;

        // add to names of info data
        colnames = colnames + quote + "date" + quote;
    }
} //end open_r_info_list


//=====================================================================================
// close_r_info_list
//
// Close info-vector object
//
// No arguments.
//=====================================================================================
void close_r_info_list() {
    if ( OKflag == false ) return;           // exit if there was an earlier error

    if ( colnames == "c(" ) {                // check that there is at least one item
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: No items written to ";
        err_msg = err_msg + prevObj[level] + " using wrt_r_item.";
        OKflag = false;
      write_errmsg();
        return;
    }

    rfile << ")," << endl;
	rfile << ".Names = ";
	print_wrap(colnames, "))");
    rfile << endl;

    colnames.erase();                       // clear row and column names
    rownames.erase();

    vecflag.erase();

    ObjDoneFlag[level] = true;              // set object complete flag

} // end close_r_info_list


//=====================================================================================
//   open_r_vector
//
//   Initialize a simple vector object.
//   The vector an named, unordered list of numbers, characters, or logical values.
//   ARGUMENTS:
//       name - name of vector object (e.g., "agevector")
//======================================================================================
void open_r_vector(const char* name) {
    // add vector name to list and check for object completion
    int flag = reg_Rnames(name, "Info Object ");
    if ( flag == 0 ) return;

    // inform the world a vector item is open
    vecflag = "vector";

    rfile << name << " = structure(c(" << endl;

    // initialize names of info data
    colnames = "c(";
} //end open_r_vector


//=====================================================================================
// close_r_vector
//
// Close simple-vector object
//
// No arguments.
//=====================================================================================
void close_r_vector() {
    if ( OKflag == false ) return;           // exit if there was an earlier error

    if ( colnames == "c(" ) {                // check that there is at least one item
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: No items written to ";
        err_msg = err_msg + prevObj[level] + " using wrt_r_item.";
        OKflag = false;
      write_errmsg();
        return;
    }

    rfile << ")," << endl;
	rfile << ".Names = ";
	print_wrap(colnames, "))");
    rfile << endl;

    colnames.erase();                       // clear row and column names
    rownames.erase();
    vecflag.erase();

    ObjDoneFlag[level] = true;              // set object complete flag

} // end close_r_vector


//=====================================================================================
// wrt_r_item
//
// Overloaded function to write a name - value pair to the INFO object.
// Defined here for char *, int, double, bool, dvariable types
//
// ARGUMENTS
//   name - name of data subobject (int or char*)
//   value - corresponding datum
//=====================================================================================
void wrt_r_item(const char* name, const char* value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(name);
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << name << " = " << quote << value << quote;
    }

} //end wrt_r_item(char*)
//======================================================================================
void wrt_r_item(const char* name, bool value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(name);

    if (vecflag == "vector") {
        if ( value ) {
            rfile << "TRUE";
        } else {
            rfile << "FALSE";
        }
    } else {
        if ( value ) {
            rfile << name << " = " << "TRUE";
        } else {
            rfile << name << " = " << "FALSE";
        }
    }

} // end wrt_r_item(boolean)
//======================================================================================
void wrt_r_item(int name, bool value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(convert<char*>(name));

    if (vecflag == "vector") {
        if ( value ) {
            rfile << "TRUE";
        } else {
            rfile << "FALSE";
        }
    } else {
        if ( value ) {
            rfile << convert<char*>(name) << " = " << "TRUE";
        } else {
            rfile << convert<char*>(name) << " = " << "FALSE";
        }
    }

} // end wrt_r_item(boolean)
//======================================================================================
void wrt_r_item(const char* name, int value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(name);
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << name << " = " <<  value;
    }

} //end wrt_r_item(integer)
//======================================================================================
void wrt_r_item(int name, int value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(convert<char*>(name));
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << convert<char*>(name) << " = " <<  value;
    }

} //end wrt_r_item(integer)
//======================================================================================
void wrt_r_item(const char* name, double value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(name);
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << name << " = " <<  value;
    }

} //end wrt_r_item(double)
//======================================================================================
void wrt_r_item(int name, double value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(convert<char *>(name));
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << convert<char*>(name) << " = " <<  value;
    }

} //end wrt_r_item(double)
//======================================================================================
void wrt_r_item(const char* name, dvariable value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(name);
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << name << " = " <<  value;
    }

} //end wrt_r_item(dvariable)
//======================================================================================
void wrt_r_item(int name, dvariable value) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(convert<char*>(name));
    if (vecflag == "vector") {
        rfile << value;
    } else {
    rfile << convert<char*>(name) << " = " <<  value;
    }

} //end wrt_r_item(dvariable)

// overloaded functions to write NA's when no value argument is given
//=====================================================================================
void wrt_r_item(const char* name) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(name);
    if (vecflag == "vector") {
        rfile << "NA";
    } else {
    rfile << name << " = NA";
    }

} //end wrt_r_item
//=====================================================================================
void wrt_r_item(int name) {
    if ( OKflag == false ) return;                   // exit if there is an error
    if ( colnames != "c(" ) rfile << "," << endl;    // comma needed if not first item.

    add_colname(convert<char*>(name));
    if (vecflag == "vector") {
        rfile << "NA";
    } else {
    rfile << convert<char*>(name) << " = NA";
    }

} //end wrt_r_item

//====================================================================================
// open_r_df
//
// Initializes a data frame object.
// Data frames differ from matrices in that they require named columns,
// which are individually written and may be of different types, e.g.,
// columns of integers interspersed among columns of doubles.
//
// ARGUMENTS
//    name - name of object
//    start, stop - define the width of the data frame
//                  and the data frame's coordinate system
//                  i.e., bounds for the data frame vectors.
//    writerow - flag to write row.names (optional).
//        0 = do not write row.names (default).
//        1 = write row.names using the index values supplied
//        2 = write row.names with vector or other values
//======================================================================================
void open_r_df(const char* name, int start = -1, int stop = -1, int writerow = 0) {
    string temp;

    // add info object name to list and check for object completion
    int flag = reg_Rnames(name, "Data Frame Object ");
    if ( flag == 0 ) return;

    // intialize matrix/data frame flag
    mflag = "data frame";

    // set rowflag
    rowflag = writerow;

    // check validity of start/stop values
    if ( start == stop && start != -1 ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Invalid index min and max values in open_r_df for the data frame " + name;
        OKflag = false;
      write_errmsg();
        return;
    }

    // intialize min and max values for data bounds checking
    dim1 = start;
    dim2 = stop;

    //initialize vector names list
    colnames = "c(";

    // if user has chosen to write the row.names with the index values (writerow = 1), get row values now
   if ( rowflag == 1 ) wrt_r_namevector(dim1, dim2);

    // write beginning of object
    rfile << name << " = structure(list(" << endl;

} // end open_r_df

//======================================================================================
// close_r_df
//
// Writes data frame row and column names, adds punctuation, and does housekeeping.
//
// No arguments.
//======================================================================================
void close_r_df() {
    if ( OKflag == false ) return; // exit if there was an earlier error

    // check that column names not empty
    if ( colnames == "" || colnames == "c(" ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: No column names supplied for ";
        err_msg = err_msg + prevObj[level] ;
        OKflag = false;
      write_errmsg();
        return;
    }
    // check that if user wanted to write the row.names they called wrt_r_namevector
    if ( rowflag == 2 && rownames == "" ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: No row names supplied for ";
        err_msg = err_msg + prevObj[level];
        OKflag = false;
      write_errmsg();
        return;
    }

    // write closing punctuation
    rfile << ")," << endl;

	// Write names of vectors
	rfile << ".Names = ";
	print_wrap(colnames, "),");

	// If row names are being used write out row names
   if ( rowflag == 0 ) {
      rfile << "row.names = c(NA, " << ( dim2 - dim1 + 1 ) << ")," << endl;
   }
    else {
		rfile << "row.names = ";
        print_wrap(rownames, ",");
    }

    // write out rest of object
    rfile << "class = \"data.frame\")" << endl;
    rfile << endl;


    // clear row/col names and dimensions and write flags for next use
    rownames.erase();
    colnames.erase();
    rowflag = 0;
    colflag = 0;
    dim1 = -1;
    dim2 = -1;

    // clear matrix/data frame flag
    mflag.erase();

    // set object complete flag
    ObjDoneFlag[level] = true;

    // if something goes wrong
    if ( rfile.bad() ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Unable to write to " + outfile;
        OKflag = false;
      write_errmsg();
        return;
    }
} // end close_r_df


//======================================================================================
// do_df_col_wrt_vec
//
// Function template for writing a VECTOR as part of an R data frame.
// Called by wrt_r_df_col when ADMB vector types are used.
//
// ARGUMENTS
//    name - the name of the vector to be written as the R column name
//    xx - the ADMB dvector to be written
//    shift - if the vector doesn't have the same index range, shift is the value
//      in the data frame's index coordinates that corresponds to the first
//      element in vector xx.
//    na_vector - boolean vector indicating which positions in the xx vector
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA.
//======================================================================================
template <class T>
void do_df_col_wrt_vec (const char* name, const T& xx, int shift, bool* na_vector = NULL) {

    int counter;                                // counter to limit line lengths

	// if this is not the first item, print the comma separating the previous item
    if ( colnames != "c(" ) rfile << "," << endl;

    // add item to column names
    add_colname(name);

    // write column to file
    rfile << name << " = c(";

    // get vector's index min and max
    int ja = (xx).indexmin();
    int jz = (xx).indexmax();

    // set difference between vector's coordinate system and data frame's coordinate system
    int yshift = 0;

    // index values not initialized; set to first vector's index specifications
    if ( dim1 == -1 && dim2 == -1 ) {
        dim1 = ja;
        dim2 = jz;
    }

    // re-set vector index coordinates into data frame coordinates
    if ( shift != -999999 ) {
        yshift = ja - shift;
        jz = jz - ja + shift;
        ja = shift;
    }

    // Write the data:
	counter = 0;
    for ( int y=dim1; y<=dim2; y++ ) {
        counter++;
		if ( y<ja || y>jz ) {        // ( If out of range
            rfile << "NA";
        }     // ( write NA
        else { // if value is the missing value indicator, write "NA" instead
            if ( test_missing(convert<double>(xx[y + yshift])) && writeNA == true ) {
                rfile << "NA";
            } // if the value in the boolean vector is true, write "NA"
            else if (naflag && na_vector[y] == true) {
                rfile << "NA";
            }
            else {
                rfile << xx[y + yshift];
            } // If in range and not a missing datum, write data

        }
        if ( y==dim2 ) {
            rfile << ")";
        }      // ( Write appropriate punctuation
        else {                    // ( to separate or terminate the
            rfile << ", ";     // ( values in the vector.
			if (counter == 25) {
			    rfile << endl;   // Limit line lengths
				counter = 0;
				}
        }
    }

}; // end do_df_col_wrt_vec


//======================================================================================
// wrt_r_df_col
//
// Overloaded function to write an ADMB vector types as part of an R data frame.
// Defined here for dvector, ivector, and dvar_vector.
//
// ARGUMENTS
//    name - the name of the vector to be written as the R column name
//    xx - the ADMB dvector to be written
//    shift - if the vector doesn't have the same index range, shift is the value
//      in the data frame's index coordinates that corresponds to the first
//      element in vector xx. (optional)
//    isna - is an NA vector supplied. Optional.
//      false = no vector will be supplied (Default). true = a NA vector will follow.
//    na_vector - (optional) a boolean vector indicating which positions in the xx vector
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA. This argument is passed to do_df_col_wrt_vec
//      for further handling.
//======================================================================================
void wrt_r_df_col(const char* name, const dvector& xx, int shift = -999999,
                  bool isna = false, bool* na_vector = NULL) {
    if ( OKflag == false ) return; // exit if there was an earlier error

    naflag = isna;

    do_df_col_wrt_vec<dvector> (name, xx, shift, na_vector);

} // end wrt_r_df_col (dvector)
//======================================================================================
void wrt_r_df_col(const char* name, const ivector& xx, int shift = -999999,
                  bool isna = false, bool* na_vector = NULL) {
    if ( OKflag == false ) return; // exit if there was an earlier error

    naflag = isna;

    do_df_col_wrt_vec<ivector> (name, xx, shift, na_vector);

} // end wrt_r_df_col (ivector)
//======================================================================================
void wrt_r_df_col(const char* name, const dvar_vector& xx, int shift = -999999,
                  bool isna = false, bool* na_vector = NULL) {
    if ( OKflag == false ) return; // exit if there was an earlier error

    naflag = isna;

    do_df_col_wrt_vec<dvar_vector> (name, xx, shift, na_vector);

} // end wrt_r_df_col (dvar_vector)


//======================================================================================
// do_df_col_wrt_num
//
// Function template for writing a SERIES of NUMBERS as part of an R data frame.
// Called by wrt_r_df_col when a series of numbers are used.
//
// ARGUMENTS:
//    name - the name of the vector to be written as the R column name
//    start - value to start the numeric series
//    stop - value to end the numeric series
//    inc - the increment between values in the series
//    na_vector - a boolean vector indicating which positions in the series
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA.
//======================================================================================
template <class T>
void do_df_col_wrt_num (const char* name, const T& start, const T& stop, T inc,
                        bool* na_vector = NULL) {

    int counter;                                // counter to limit line lengths

	// index values not initialized
    if ( dim1 == -1 && dim2 == -1 ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Index min and max values unspecified";
        err_msg = err_msg + " in open_r_df for " + prevObj[level];
        OKflag = false;
      write_errmsg();
        return;
    }

    if ( colnames != "c(" ) rfile << "," << endl;  // Comma needed if vector is not first

    add_colname(name);

    rfile << name << " = c(";    // Column start

	// Write the data:
    T iter;
    iter = start;
    counter = 0;
	for ( int y=dim1; y<=dim2; y++ ) {
        counter++;
		if ( iter > stop ) {                // If out of range
            rfile << "NA";
        }            // write NA
        else if (naflag && na_vector[y]) {
            rfile << "NA";
        }
        else if (writeNA && test_missing(iter)) {
            rfile << "NA";
        }
        else {
            rfile << iter;
        }            // write out value to file
        iter = iter + inc;
        if ( y==dim2 ) {
            rfile << ")";
        }             // Write appropriate punctuation
        else {                           // to separate or terminate the
            rfile << ", ";            // values in the vector.
			if (counter == 25) {
			    rfile << endl;    // Limit line lengths
				counter = 0;
				}
        }
    }
}; // end do_df_col_wrt_num


//======================================================================================
// wrt_r_df_col
//
// Overloaded function to write a series of integers as part of an R data frame.
// Defined here for int.
// (Functions for double and dvariable types are commented out to prevent possible errors.)
//
// ARGUMENTS:
//    name - the name of the vector to be written as the R column name
//    xx - the ADMB dvector to be written
//    start - value to start the numeric series
//    stop - value to end the numeric series
//    inc - the increment between values in the series
//    isna - is an NA vector supplied. Optional.
//      false = no vector will be supplied (Default). true = a NA vector will follow.
//    na_vector - (optional) a boolean vector indicating which positions in the xx vector
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA. This argument is passed to do_df_col_wrt_vec
//      for further handling.
//======================================================================================
void wrt_r_df_col(const char* name, const int& start, const int& stop, int inc = 1,
                  bool isna = false, bool* na_vector = NULL) {

    if ( OKflag == false ) return; // exit if there was an earlier error

    naflag = isna;

    do_df_col_wrt_num<int> (name, start, stop, inc, na_vector);

} // end wrt_r_df_col (int)
//======================================================================================
//void wrt_r_df_col(char* name, const double& start, const double& stop, double inc = 1.00,
//                  bool isna = false, int* na_vector = NULL) {
//
//    if ( OKflag == false ) return; // exit if there was an earlier error
//
//    naflag = isna;
//
//    do_df_col_wrt_num<double> (name, start, stop, inc, na_vector);
//
//} // end wrt_r_df_col (double)
//=======================================================================================
//void wrt_r_df_col(char* name, const dvariable& start, const dvariable& stop, double inc = 1.00,
//                  bool isna = false, int* na_vector = NULL) {
//
//    if ( OKflag == false ) return; // exit if there was an earlier error
//
//    const double newstart = value(start);
//    const double newstop = value(stop);
//
//    naflag = isna;
//
//    do_df_col_wrt_num<double> (name, newstart, newstop, inc, na_vector);
//
//} // end wrt_r_df_col (dvariable)



//======================================================================================
// open_r_complete_vector
//
// Opens the vector object and does housekeeping tasks
//
// ARGUMENTS:
//      name - name of vector to write to file.
//======================================================================================

void open_r_complete_vector (const char* name) {
    if ( OKflag == false ) return;    // exit if there was an earlier error

    // add vector object name to list and check for object completion
    int flag = reg_Rnames(name, "Vector Object ");
    if ( flag == 0 ) return;

    rfile << name << " = structure(c(" << endl;
};

//======================================================================================
// close_r_complete_vector
//
// Closes the vector object and does housekeeping tasks
//
// No arguments.
//======================================================================================
void close_r_complete_vector() {
    if ( OKflag == false ) return;    // exit if there was an earlier error

    colnames.erase();                       // clear row and column names
    rownames.erase();

    ObjDoneFlag[level] = true;              // set object complete flag

    // if something goes wrong
    if ( rfile.bad() ) {
        if ( rfile.is_open() ) rfile.close();
        err_msg = err_msg + "\n**** ADMB2R Error: Unable to write to " + outfile;
        OKflag = false;
      write_errmsg();
        return;
    }
} // end close_r_complete_vector

//=====================================================================================
// do_wrt_r_complete_vector
//
// Write a vector subobject to the R data object all in one shot.
//
// Arguments are passed to do_wrt_r_complete_vector by the overloaded wrt_r_complete_vector function.
//
// ARGUMENTS:
//   xvec - the vector
//   name_flag - integer that indicates whether there is a vector of names. A value of 0
//      indicates no vector of names. A value of 1 indicates there is a vector of names.
//   name_vector - an integer vector of names to describe each element in the xvec vector.
//   na_vector - a boolean vector indicating which positions in the xvec vector
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA.
//====================================================================================
template <class T>
void do_wrt_r_complete_vector (const T& xvec, int name_flag, const ivector& name_vector,
                        ivector& na_vector) {

    int ir;                       // row iterator in for statement
    int ra, rz, na, nz;           // for vector bounds
   int i;                        // counter in for loop
   int counter;                  // counter for limiting line lengths
   int nelem1, nelem2;           // number of elements in each vector, for bounds checking

    if ( OKflag == false ) return;    // exit if there was an earlier error

   ra = (xvec).indexmin();               // Get starting index value
    rz = (xvec).indexmax();               // Get ending index value
   nelem1 = rz - ra + 1;                 // number of elements in xvec

   // get bounds of NA vector, if used
   if (naflag){
      na = (na_vector).indexmin();          // Get starting index value
        nz = (na_vector).indexmax();          // Get ending index value
       nelem2 = nz - na + 1;                 // number of elements
      // write error message if number of elements is not the same
      if ( nelem2 != nelem1 ) {
            if ( rfile.is_open() ) rfile.close();
            err_msg = err_msg + "\n**** ADMB2R Error: Number of vector elements in ";
            err_msg = err_msg + prevObj[level] + " is different than the NA vector used.";
            OKflag = false;
         write_errmsg();
            return;
        }
   }

    // Write the vector data
   i==0;
   counter = 0;
    for ( ir=ra; ir<=rz; ir++ ) {

        i = i + 1;
		counter++;

      // if value is the missing value indicator, and we're
        // using a missing value "value",  write "NA" instead
        if ( test_missing(convert<double>(xvec(ir))) && writeNA == true ) {
            rfile << "NA";
        }
        // if instead we're using a vector of booleans to
        // indicate the position of missing values, check
        // to see if this position is a missing value
        else if (naflag && na_vector(na + i - 1) ){
            rfile << "NA";
        }
        // otherwise use the value we're given.
        else {
            rfile << xvec(ir);
        }
        // write proper punctuation
        if ( ir==rz ) {
            rfile << "),";
        } else {
            rfile << ", ";
			if (counter == 25) {
			    rfile << endl;    // Limit line lengths
				counter = 0;
				}
        }
    }
	rfile << endl;

    //write default names if no name vector is present
   if ( name_flag == 0 ) {
      rfile << ".Names = NULL)" << endl;
   } else {
      na = (name_vector).indexmin();               // Get starting index value
      nz = (name_vector).indexmax();               // Get ending index value
      nelem2 = nz - na + 1;                        // number of elements

      // first check to make sure that both vectors have the same dimensions
      if ( nelem2 != nelem1 ) {
            if ( rfile.is_open() ) rfile.close();
            err_msg = err_msg + "\n**** ADMB2R Error: Number of vector elements in ";
            err_msg = err_msg + prevObj[level] + " is different than the names vector used.";
            OKflag = false;
         write_errmsg();
            return;
        }

	  counter = 0;
	  rfile << ".Names = c(";
      // write out the vector
      for ( ir=na; ir<=nz; ir++ ) {
         counter++;
		 rfile << name_vector(ir);
         // write proper punctuation
         if ( ir==nz ) {
            rfile << "))" << endl;
         } else {
            rfile << ", ";
			if (counter == 25) {
			    rfile << endl;    // Limit line lengths
				counter = 0;
				}
         }
      }
   }
   rfile << endl;

} // end do_wrt_r_complete_vector

//======================================================================================
// wrt_r_complete_vector
//
// Overloaded function to write a vector object all in one function call.
// Defined here for types dvar_vector, dvector, and ivector.
//
// ARGUMENTS
//   name - name of vector object to write (e.g., "agevector")
//   xvec - the vector
//      This argument is passed to do_wrt_r_complete_vector for further handling.
//   namevec - Vector to use to write names of vector items. Optional.
//   isna - is an NA_vector supplied. Optional.
//      false = no vector will be supplied (Default). true = a NA vector will follow.
//   na_vector - (optional) a boolean vector indicating which positions in the xvec vector
//      should be replaced with the NA missing value indicator. A value of 1 (true)
//      indicates the spot to replace with NA. This argument is passed to do_wrt_r_complete_vector
//      for further handling.
//======================================================================================
void wrt_r_complete_vector(const char* name, const dvar_vector& xvec,
                  bool isna = false, ivector& na_vector = dum_vector) {

    if ( OKflag == false ) return;    // exit if there was an earlier error

   open_r_complete_vector(name);

   // Set global flags
    naflag = isna;

    do_wrt_r_complete_vector<dvar_vector> (xvec, 0, dum_vector, na_vector);

   close_r_complete_vector();

} // wrt_r_complete_vector (dvar_vector)
//======================================================================================
void wrt_r_complete_vector(const char* name, const dvector& xvec,
                  bool isna = false, ivector& na_vector = dum_vector) {

    if ( OKflag == false ) return;    // exit if there was an earlier error

   open_r_complete_vector(name);

   // Set global flags
    naflag = isna;

    do_wrt_r_complete_vector<dvector> (xvec, 0, dum_vector, na_vector);

   close_r_complete_vector();

} // wrt_r_complete_vector (dvector)
//======================================================================================
void wrt_r_complete_vector(const char* name, const ivector& xvec,
                  bool isna = false, ivector& na_vector = dum_vector) {

    if ( OKflag == false ) return;    // exit if there was an earlier error

   open_r_complete_vector(name);

   // Set global flags
    naflag = isna;

    do_wrt_r_complete_vector<ivector> (xvec, 0, dum_vector, na_vector);

   close_r_complete_vector();

} // end wrt_r_complete_vector (ivector)
//======================================================================================
void wrt_r_complete_vector(const char* name, const dvar_vector& xvec, const ivector& namevec,
                  bool isna = false, ivector& na_vector = dum_vector) {

    if ( OKflag == false ) return;    // exit if there was an earlier error

   open_r_complete_vector(name);

   // Set global flags
    naflag = isna;

    do_wrt_r_complete_vector<dvar_vector> (xvec, 1, namevec, na_vector);

   close_r_complete_vector();

} // wrt_r_complete_vector (dvar_vector, ivector)
//======================================================================================
void wrt_r_complete_vector(const char* name, const dvector& xvec, const ivector& namevec,
                  bool isna = false, ivector& na_vector = dum_vector) {

    if ( OKflag == false ) return;    // exit if there was an earlier error

   open_r_complete_vector(name);

   // Set global flags
    naflag = isna;

    do_wrt_r_complete_vector<dvector> (xvec, 1, namevec, na_vector);

   close_r_complete_vector();

} // wrt_r_complete_vector (dvector, ivector)
//======================================================================================
void wrt_r_complete_vector(const char* name, const ivector& xvec, const ivector& namevec,
                  bool isna = false, ivector& na_vector = dum_vector) {

    if ( OKflag == false ) return;    // exit if there was an earlier error

   open_r_complete_vector(name);

   // Set global flags
    naflag = isna;

    do_wrt_r_complete_vector<ivector> (xvec, 1, namevec, na_vector);

   close_r_complete_vector();

} // end wrt_r_complete_vector (ivector, ivector)
//======================================================================================
// End File admb2r.cpp
//=======================================================================================

