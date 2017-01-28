/// Copyright (c) 2016 ADMB Foundation
/// Author: Johnoel Ancheta

#include <fvar.hpp>
#include "adjson.h"
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

istream& operator>>(istream& input, adjson::json& data)
{
  adjson::value* ret = data.parse(input); 
  data.set(ret);
  return input;
}
ostream& operator<<(ostream& output, const adjson::json& data)
{
  output << data.str();
  return output; 
}

namespace adjson
{
value* json::parse(istream& input)
{
  value* ret = 0;
  input >> std::ws;
  char p = (char)input.peek();
  while (p != EOF)
  {
    char c;
    if (p == '{')
    {
      object* o = new object();      

      input.get(c);
      while (c != '}')
      {
        string* s = (string*)parse(input);
        input >> std::ws >> c >> std::ws;
        value* v = parse(input);
        o->add(s, v);
        input >> std::ws >> c >> std::ws;
      }

      ret = o;
      break;
    }
    else if (p == '[')
    {
      array* a = new array();      

      input.get(c);
      while (c != ']')
      {
        value* p = parse(input);
        a->add(p);
        input >> std::ws >> c >> std::ws;
      }
      ret = a;
      break;
    }
    else if (p == '\"')
    {
      string* s = new string();      
      input.get(c);
      s->_value.push_back(c);
      input.get(c);
      while (c != '\"')
      {
        s->_value.push_back(c);
        input.get(c);
        if (c == '\\')
        {
          s->_value.push_back(c);
          input.get(c);
          s->_value.push_back(c);
          input.get(c);
        }
      }
      s->_value.push_back('\"');
      ret = s;
      break;
    }
    else if (p == '-' || std::isdigit(p))
    {
      number* n = new number();      
      input >> n->_value;
      ret = n;
      break;
    }
    else if (p == 't')
    {
      boolean* b = new boolean();      
      char str[6];
      input.read(str, 4);
      b->_value = true;
      ret = b;
      break;
    }
    else if (p == 'f')
    {
      boolean* b = new boolean();      
      char str[7];
      input.read(str, 5);
      b->_value = false;
      ret = b;
      break;
    }
    else if (p == 'n')
    {
      null* b = new null();      
      char str[6];
      input.read(str, 4);
      ret = b;
      break;
    }
    else
    {
      std::cerr << "Error: unknown char(" << p << ") in json input.\n";
      break;
    }
    input >> std::ws;
    p = (char)input.peek();
  }
  return ret;
}
};

istream& dvector::parse(istream& input)
{
  adjson::json data;
  input >> data;
  adjson::array* a = (adjson::array*)data.get_value();

  if (allocated())
  {
    deallocate();
  }
  size_t size = a->_value.size();
#ifndef OPT_LIB
  assert(size <= INT_MAX);
#endif
  allocate(1, static_cast<int>(size));
  for (size_t i = 0; i < size; ++i)
  {
    adjson::number* n = (adjson::number*)a->_value[i];
    v[i + 1] = n->_value;
  }

  return input;
}
