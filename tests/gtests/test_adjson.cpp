#include <sstream>
#include <gtest/gtest.h>
#include <adjson.h>
#include <fvar.hpp>
using adjson::json;
using adjson::value;
using adjson::object;
using adjson::array;
using adjson::string;
using adjson::number;
#ifndef __MINGW32__
using adjson::boolean;
#endif
using adjson::null;
using adjson::values;

class test_adjson: public ::testing::Test {};

TEST_F(test_adjson, constructor)
{
  json _json;

  ASSERT_TRUE(_json.get_value() == NULL);
}
TEST_F(test_adjson, input_output_array)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("[1, 2, 3, 4]");
  input >> data;

  array* a = (array*)data.get_value();

  ASSERT_EQ(4, a->_value.size());
  number* n0 = (number*)a->_value[0];
  ASSERT_NEAR(1, n0->_value, 0.1);
  number* n1 = (number*)a->_value[1];
  ASSERT_NEAR(2, n1->_value, 0.1);
  number* n2 = (number*)a->_value[2];
  ASSERT_NEAR(3, n2->_value, 0.1);
  number* n3 = (number*)a->_value[3];
  ASSERT_NEAR(4, n3->_value, 0.1);

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"[1, 2, 3, 4]", s.c_str());
}
TEST_F(test_adjson, input_output_number)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("4.5");
  input >> data;
  number* n = (number*)data.get_value();
  ASSERT_NEAR(4.5, n->get_value(), 0.01);

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"4.5", s.c_str());
}
TEST_F(test_adjson, input_output_string_withreversesolidusandquote)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("\"abc\\\"def\"");
  input >> data;
  string* str = (string*)data.get_value();
  ASSERT_STREQ((char*)"\"abc\\\"def\"", str->get_value().c_str());

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"\"abc\\\"def\"", s.c_str());
}
TEST_F(test_adjson, input_output_string_solidus)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("\"abc\/def\"");
  input >> data;
  string* str = (string*)data.get_value();
  ASSERT_STREQ((char*)"\"abc\/def\"", str->get_value().c_str());

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"\"abc\/def\"", s.c_str());
}
TEST_F(test_adjson, input_output_string_tab)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("\"abc\tdef\"");
  input >> data;
  string* str = (string*)data.get_value();
  ASSERT_STREQ((char*)"\"abc\tdef\"", str->get_value().c_str());

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"\"abc\tdef\"", s.c_str());
}
TEST_F(test_adjson, input_output_string)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("\"abcdef\"");
  input >> data;
  string* str = (string*)data.get_value();
  ASSERT_STREQ((char*)"\"abcdef\"", str->get_value().c_str());

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"\"abcdef\"", s.c_str());
}
TEST_F(test_adjson, input_output_true)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("true");
  input >> data;
#ifdef __MINGW32__
  adjson::boolean* n = (adjson::boolean*)data.get_value();
#else
  boolean* n = (boolean*)data.get_value();
#endif
  ASSERT_EQ(n->get_value(), true);

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"true", s.c_str());
}
TEST_F(test_adjson, input_output_false)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("false");
  input >> data;
#ifdef __MINGW32__
  adjson::boolean* n = (adjson::boolean*)data.get_value();
#else
  boolean* n = (boolean*)data.get_value();
#endif
  ASSERT_EQ(n->get_value(), false);

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"false", s.c_str());
}
TEST_F(test_adjson, input_output_null)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("null");
  input >> data;
  null* n = (null*)data.get_value();
  ASSERT_TRUE(n->get_type() == values::_null);

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"null", s.c_str());
}
TEST_F(test_adjson, input_output_object)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("{\"a\":\"1\", \"b\":\"2\", \"c\":\"3\", \"d\":\"4\"}");
  input >> data;

  object* a = (object*)data.get_value();

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"{\"a\":\"1\", \"b\":\"2\", \"c\":\"3\", \"d\":\"4\"}", s.c_str());
}
TEST_F(test_adjson, input_output_object_array)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("{\"a\":[\"1\", \"2\", \"3\", \"4\"]}");
  input >> data;

  object* a = (object*)data.get_value();

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"{\"a\":[\"1\", \"2\", \"3\", \"4\"]}", s.c_str());
}
TEST_F(test_adjson, input_output_array_object)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("[{\"a\":\"1\"}, {\"b\":\"2\"}, {\"c\":\"3\"}]");
  input >> data;

  object* a = (object*)data.get_value();

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"[{\"a\":\"1\"}, {\"b\":\"2\"}, {\"c\":\"3\"}]", s.c_str());
}
TEST_F(test_adjson, input_output_object_boolean)
{
  using std::istringstream;
  using std::ostringstream;

  json data;

  istringstream input("{\"a\":true, \"b\":false, \"c\":false}");
  input >> data;

  object* a = (object*)data.get_value();

  ostringstream output;
  output << data;
  std::string s = data.str();
  ASSERT_STREQ((char*)"{\"a\":true, \"b\":false, \"c\":false}", s.c_str());
}
TEST_F(test_adjson, input_output_dvector)
{
  using std::istringstream;
  using std::ostringstream;

  dvector v;
  istringstream input("[1.5, 2.4, 3.3, 4.2, 5.1]");
  v.parse(input);

  ASSERT_EQ(1, v.indexmin());
  ASSERT_EQ(5, v.indexmax());
  ASSERT_NEAR(1.5, v(1), 0.01);
  ASSERT_NEAR(2.4, v(2), 0.01);
  ASSERT_NEAR(3.3, v(3), 0.01);
  ASSERT_NEAR(4.2, v(4), 0.01);
  ASSERT_NEAR(5.1, v(5), 0.01);
}
