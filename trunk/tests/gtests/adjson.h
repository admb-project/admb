#ifndef __ADJSON_H__
#define __ADJSON_H__

namespace adjson {

/**
ADMB JSON object.
*/
class object
{
public:
  object();
  object(const object&);
  ~object();
};

/**
ADMB JSON array.
*/
class array
{
public:
  array();
  array(const array&);
  ~array();
};

}

namespace adjson {
/**
Default constructor
*/
object::object()
{
}
/**
Destructor
*/
object::~object()
{
}
/**
Default constructor
*/
array::array()
{
}
/**
Destructor
*/
array::~array()
{
}
}
#endif
