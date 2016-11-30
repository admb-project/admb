/// Copyright (c) 2016 ADMB Foundation
/// Author: Johnoel Ancheta

#include <fvar.hpp>
#include "adjson.h"

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
  char p = input.peek();
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
        value* ret = parse(input);
        a->add(ret);
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
      char str[4];
      input.read(str, 4);
      b->_value = true;
      ret = b;
      break;
    }
    else if (p == 'f')
    {
      boolean* b = new boolean();      
      char str[5];
      input.read(str, 5);
      b->_value = false;
      ret = b;
      break;
    }
    else if (p == 'n')
    {
      null* b = new null();      
      char str[4];
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
    p = input.peek();
  }
  return ret;
}
};

istream& dvector::parse(istream& input)
{
  adjson::json data;
  adjson::array* a = (adjson::array*)data.parse(input);

  if (allocated())
  {
    deallocate();
  }
  int size = a->_value.size();
  allocate(1, size);
  for (int i = 0; i < size; ++i)
  {
    adjson::number* n = (adjson::number*)a->_value[i];
    v[i + 1] = n->_value;
  }

  return input;
}
