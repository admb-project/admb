  #ifndef __GCCMANIP_HPP
  #define __GCCMANIP_HPP
  
//   #ifndef __GNUDOS__
//     #include <admanip.h>
//   #else
//     #include <iostream.h>
//   #endif
//   
//   class smanip_int 
//   { 
//   public:
//       smanip_int(BOR_CONST ios &(*f)(BOR_CONST ios&, int), int v) 
//       {
//         func=f;
//         val=v;
//       } 
//       friend istream &operator>>(BOR_CONST istream&, BOR_CONST smanip_int&); 
//       friend ostream &operator<<(BOR_CONST ostream&, BOR_CONST smanip_int&); 
//   private: 
//       ios &(*func)(BOR_CONST ios&, int); 
//       int val; 
//   }; 
//   
//   inline istream &operator>>(BOR_CONST istream &s, BOR_CONST smanip_int &m) 
//   {
//     (*m.func)(s, m.val); 
//     return s; 
//   } 
//   inline ostream &operator<<(BOR_CONST ostream &s, BOR_CONST smanip_int &m) 
//   { 
//     (*m.func)(s, m.val); 
//     return s; 
//   } 
//   
//   
//  smanip_int setprecision(int);
//  smanip_int setw(int);
   #endif
