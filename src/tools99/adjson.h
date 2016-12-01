/// Copyright (c) 2016 ADMB Foundation
/// Author: Johnoel Ancheta
///
/// A simple JSON implementation for ADMB.
/// See JSON Specification below, 
/// http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf
#ifndef __ADJSON_H__
#define __ADJSON_H__

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
using std::istream;
using std::ostream;
using std::ostringstream;
using std::vector;

namespace adjson
{
enum class values
{
  _object,
  _array,
  _number,
  _string,
  _boolean,
  _null
};
struct value
{
  values _type;

  virtual ~value() {}
  virtual std::string str() const  = 0;
  values get_type() const { return _type; }
};
class json
{
  value* _value;

public:
  json(): _value(0) { }
  json(const json& other) { }
  virtual ~json()
  {
    if (_value)
    {
      delete _value;
      _value = 0;
    }
  }
public:
  std::string str() const
    { return _value->str(); }

  value* get_value() const
    { return _value; }

  void set(value* other)
    { _value = other; }

  value* parse(istream& input);
};
struct object: value
{
  vector<value*> _value;

  object()
    { _type = values::_object; }

  std::string str() const
  {
    std::string ret;
    ret = "{";
    std::size_type size = _value.size() - 2;
    for (std::size_type i = 0; i < size; i += 2)
    {
      ret += _value[i]->str();
      ret += ":";
      ret += _value[i + 1]->str();
      ret += ", ";
    }
    ret += _value[size]->str();
    ret += ":";
    ret += _value[size + 1]->str();
    ret += "}";
    return ret;
  }
  void add(value* id, value* other)
  {
    _value.push_back(id);
    _value.push_back(other);
  }
};
struct array: value
{
  vector<value*> _value;

  array()
    { _type = values::_array; }

  std::string str() const
  {
    std::string ret;
    ret = "[";
    std::size_type size = _value.size() - 1;
    for (std::size_type i = 0; i < size; ++i)
    {
      ret += _value[i]->str();
      ret += ", ";
    }
    ret += _value[size]->str();
    ret += "]";
    return ret;
  }

  void add(value* other)
    { _value.push_back(other); }
};
struct number: value
{
  double _value;

  number()
    { _type = values::_number; }

  double get_value() const
    { return _value; }

  std::string str() const
  {
    ostringstream output;
    output << _value;
    return output.str();
  }
};
struct string: value
{
  std::string _value;

  string()
    { _type = values::_string; }

  std::string str() const
    { return _value; }

  std::string get_value() const
    { return str(); }
};
struct boolean: value
{
  bool _value;

  boolean(): _value(false)
    { _type = values::_boolean; }

  std::string str() const
    { return _value ? "true" : "false"; }

  bool get_value() const
    { return _value; }
};
struct null: value
{
  null()
    { _type = values::_null; }

  std::string str() const
    { return "null"; }

  value* get_value() const
    { return 0; }
};
};
istream& operator>>(istream& input, adjson::json& data);
ostream& operator<<(ostream& output, const adjson::json& data);
#endif
