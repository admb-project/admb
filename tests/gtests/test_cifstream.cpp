//MY Signature
//Another line for testing
#include <gtest/gtest.h>
#include <climits>
#include <cifstrem.h>

class test_cifstream: public ::testing::Test {};

TEST_F(test_cifstream, signature)
{
  cifstream cifs("test_cifstream.cpp");
  ASSERT_STREQ("//MY Signature", cifs.signature());
}
TEST_F(test_cifstream, get_file_name)
{
  cifstream cifs("test_cifstream.cpp");
  ASSERT_STREQ("test_cifstream.cpp", cifs.get_file_name());
}
TEST_F(test_cifstream, getline)
{
  cifstream cifs("test_cifstream.cpp");
  char line[20];
  cifs.getline(line, 20, '\n');
  ASSERT_STREQ("//MY Signature", line);
}
TEST_F(test_cifstream, call_signature_twice)
{
  cifstream cifs("test_cifstream.cpp");
  char* signature = cifs.signature();
  ASSERT_STREQ("//MY Signature", signature);
  char* signature2 = cifs.signature();
  ASSERT_STREQ("//MY Signature", signature2);
}
TEST_F(test_cifstream, big_signature)
{
  cifstream cifs("big_signature.txt");
  char* bigsignature = cifs.signature();
  ASSERT_STREQ(
    "01234567890123456789012345678901234567890123456789012345678901234567890123456789",
    bigsignature);
  char line[5];
  cifs.getline(line, 5, '\n');
  ASSERT_STREQ("END", line);
}
TEST_F(test_cifstream, double)
{
  cifstream cifs("test_cifstream_getfield.txt");
  double d;
  cifs >> d;
  ASSERT_DOUBLE_EQ(2.5, d);
  cifs >> d;
  ASSERT_DOUBLE_EQ(7.8, d);
  cifs.close();
}
TEST_F(test_cifstream, get_non_blank_line)
{
  int get_non_blank_line(const ifstream& _infile, char*& line,
     const int& line_length);

  int MAX_LINE_LENGTH = 10000;
  cifstream cifs("test_cifstream_get_non_blank_line.txt");
  char* signature = cifs.signature();
  ASSERT_STREQ("get_non_blank_line", signature);
  char* line = new char[MAX_LINE_LENGTH];

  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 3);
  ASSERT_STREQ("ONE", line);
  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 3);
  ASSERT_STREQ("TWO", line);
  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 5);
  ASSERT_STREQ("THREE", line);
  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 4);
  ASSERT_STREQ("FOUR", line);

  ASSERT_EQ(get_non_blank_line(cifs, line, MAX_LINE_LENGTH), 0);

  cifs.close();
}
TEST_F(test_cifstream, dvariable)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_dvariable.txt");
  ofs << "# d\n";
  ofs << 0.5 << endl;
  ofs.close();

  dvariable d;

  cifstream cifs("test_cifstream_dvariable.txt");
  cifs >> d;
  cifs.close();

  ASSERT_DOUBLE_EQ(0.5, value(d));
}
TEST_F(test_cifstream, dvar3_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_dvariable.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs.close();

  dvar3_array vararr3(1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_dvariable.txt");
  cifs >> vararr3;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, value(vararr3(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2, value(vararr3(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3, value(vararr3(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4, value(vararr3(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5, value(vararr3(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6, value(vararr3(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7, value(vararr3(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8, value(vararr3(2, 2, 2)));
}
TEST_F(test_cifstream, i3_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_iarray.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs.close();

  i3_array arr3(1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_iarray.txt");
  cifs >> arr3;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, arr3(1, 1, 1));
  ASSERT_DOUBLE_EQ(2, arr3(1, 1, 2));
  ASSERT_DOUBLE_EQ(3, arr3(1, 2, 1));
  ASSERT_DOUBLE_EQ(4, arr3(1, 2, 2));
  ASSERT_DOUBLE_EQ(5, arr3(2, 1, 1));
  ASSERT_DOUBLE_EQ(6, arr3(2, 1, 2));
  ASSERT_DOUBLE_EQ(7, arr3(2, 2, 1));
  ASSERT_DOUBLE_EQ(8, arr3(2, 2, 2));
}
TEST_F(test_cifstream, dvar4_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_dvariable.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs << 9 << endl;
  ofs << 10 << endl;
  ofs << 11 << endl;
  ofs << 12 << endl;
  ofs << 13 << endl;
  ofs << 14 << endl;
  ofs << 15 << endl;
  ofs << 16 << endl;
  ofs.close();

  dvar4_array vararr4(1, 2, 1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_dvariable.txt");
  cifs >> vararr4;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, value(vararr4(1, 1, 1, 1)));
  ASSERT_DOUBLE_EQ(2, value(vararr4(1, 1, 1, 2)));
  ASSERT_DOUBLE_EQ(3, value(vararr4(1, 1, 2, 1)));
  ASSERT_DOUBLE_EQ(4, value(vararr4(1, 1, 2, 2)));
  ASSERT_DOUBLE_EQ(5, value(vararr4(1, 2, 1, 1)));
  ASSERT_DOUBLE_EQ(6, value(vararr4(1, 2, 1, 2)));
  ASSERT_DOUBLE_EQ(7, value(vararr4(1, 2, 2, 1)));
  ASSERT_DOUBLE_EQ(8, value(vararr4(1, 2, 2, 2)));
  ASSERT_DOUBLE_EQ(9, value(vararr4(2, 1, 1, 1)));
  ASSERT_DOUBLE_EQ(10, value(vararr4(2, 1, 1, 2)));
  ASSERT_DOUBLE_EQ(11, value(vararr4(2, 1, 2, 1)));
  ASSERT_DOUBLE_EQ(12, value(vararr4(2, 1, 2, 2)));
  ASSERT_DOUBLE_EQ(13, value(vararr4(2, 2, 1, 1)));
  ASSERT_DOUBLE_EQ(14, value(vararr4(2, 2, 1, 2)));
  ASSERT_DOUBLE_EQ(15, value(vararr4(2, 2, 2, 1)));
  ASSERT_DOUBLE_EQ(16, value(vararr4(2, 2, 2, 2)));
}
TEST_F(test_cifstream, i4_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_iarray.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs << 9 << endl;
  ofs << 10 << endl;
  ofs << 11 << endl;
  ofs << 12 << endl;
  ofs << 13 << endl;
  ofs << 14 << endl;
  ofs << 15 << endl;
  ofs << 16 << endl;
  ofs.close();

  i4_array arr4;
  arr4.allocate(1, 2, 1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_iarray.txt");
  cifs >> arr4;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, arr4(1, 1, 1, 1));
  ASSERT_DOUBLE_EQ(2, arr4(1, 1, 1, 2));
  ASSERT_DOUBLE_EQ(3, arr4(1, 1, 2, 1));
  ASSERT_DOUBLE_EQ(4, arr4(1, 1, 2, 2));
  ASSERT_DOUBLE_EQ(5, arr4(1, 2, 1, 1));
  ASSERT_DOUBLE_EQ(6, arr4(1, 2, 1, 2));
  ASSERT_DOUBLE_EQ(7, arr4(1, 2, 2, 1));
  ASSERT_DOUBLE_EQ(8, arr4(1, 2, 2, 2));
  ASSERT_DOUBLE_EQ(9, arr4(2, 1, 1, 1));
  ASSERT_DOUBLE_EQ(10, arr4(2, 1, 1, 2));
  ASSERT_DOUBLE_EQ(11, arr4(2, 1, 2, 1));
  ASSERT_DOUBLE_EQ(12, arr4(2, 1, 2, 2));
  ASSERT_DOUBLE_EQ(13, arr4(2, 2, 1, 1));
  ASSERT_DOUBLE_EQ(14, arr4(2, 2, 1, 2));
  ASSERT_DOUBLE_EQ(15, arr4(2, 2, 2, 1));
  ASSERT_DOUBLE_EQ(16, arr4(2, 2, 2, 2));
}
TEST_F(test_cifstream, dvar5_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_dvariable.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs << 9 << endl;
  ofs << 10 << endl;
  ofs << 11 << endl;
  ofs << 12 << endl;
  ofs << 13 << endl;
  ofs << 14 << endl;
  ofs << 15 << endl;
  ofs << 16 << endl;
  ofs << 17 << endl;
  ofs << 18 << endl;
  ofs << 19 << endl;
  ofs << 20 << endl;
  ofs << 21 << endl;
  ofs << 22 << endl;
  ofs << 23 << endl;
  ofs << 24 << endl;
  ofs << 25 << endl;
  ofs << 26 << endl;
  ofs << 27 << endl;
  ofs << 28 << endl;
  ofs << 29 << endl;
  ofs << 30 << endl;
  ofs << 31 << endl;
  ofs << 32 << endl;
  ofs.close();

  dvar5_array vararr5(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_dvariable.txt");
  cifs >> vararr5;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, value(vararr5(1, 1, 1, 1, 1)));
  ASSERT_DOUBLE_EQ(2, value(vararr5(1, 1, 1, 1, 2)));
  ASSERT_DOUBLE_EQ(3, value(vararr5(1, 1, 1, 2, 1)));
  ASSERT_DOUBLE_EQ(4, value(vararr5(1, 1, 1, 2, 2)));
  ASSERT_DOUBLE_EQ(5, value(vararr5(1, 1, 2, 1, 1)));
  ASSERT_DOUBLE_EQ(6, value(vararr5(1, 1, 2, 1, 2)));
  ASSERT_DOUBLE_EQ(7, value(vararr5(1, 1, 2, 2, 1)));
  ASSERT_DOUBLE_EQ(8, value(vararr5(1, 1, 2, 2, 2)));
  ASSERT_DOUBLE_EQ(9, value(vararr5(1, 2, 1, 1, 1)));
  ASSERT_DOUBLE_EQ(10, value(vararr5(1, 2, 1, 1, 2)));
  ASSERT_DOUBLE_EQ(11, value(vararr5(1, 2, 1, 2, 1)));
  ASSERT_DOUBLE_EQ(12, value(vararr5(1, 2, 1, 2, 2)));
  ASSERT_DOUBLE_EQ(13, value(vararr5(1, 2, 2, 1, 1)));
  ASSERT_DOUBLE_EQ(14, value(vararr5(1, 2, 2, 1, 2)));
  ASSERT_DOUBLE_EQ(15, value(vararr5(1, 2, 2, 2, 1)));
  ASSERT_DOUBLE_EQ(16, value(vararr5(1, 2, 2, 2, 2)));
  ASSERT_DOUBLE_EQ(17, value(vararr5(2, 1, 1, 1, 1)));
  ASSERT_DOUBLE_EQ(18, value(vararr5(2, 1, 1, 1, 2)));
  ASSERT_DOUBLE_EQ(19, value(vararr5(2, 1, 1, 2, 1)));
  ASSERT_DOUBLE_EQ(20, value(vararr5(2, 1, 1, 2, 2)));
  ASSERT_DOUBLE_EQ(21, value(vararr5(2, 1, 2, 1, 1)));
  ASSERT_DOUBLE_EQ(22, value(vararr5(2, 1, 2, 1, 2)));
  ASSERT_DOUBLE_EQ(23, value(vararr5(2, 1, 2, 2, 1)));
  ASSERT_DOUBLE_EQ(24, value(vararr5(2, 1, 2, 2, 2)));
  ASSERT_DOUBLE_EQ(25, value(vararr5(2, 2, 1, 1, 1)));
  ASSERT_DOUBLE_EQ(26, value(vararr5(2, 2, 1, 1, 2)));
  ASSERT_DOUBLE_EQ(27, value(vararr5(2, 2, 1, 2, 1)));
  ASSERT_DOUBLE_EQ(28, value(vararr5(2, 2, 1, 2, 2)));
  ASSERT_DOUBLE_EQ(29, value(vararr5(2, 2, 2, 1, 1)));
  ASSERT_DOUBLE_EQ(30, value(vararr5(2, 2, 2, 1, 2)));
  ASSERT_DOUBLE_EQ(31, value(vararr5(2, 2, 2, 2, 1)));
  ASSERT_DOUBLE_EQ(32, value(vararr5(2, 2, 2, 2, 2)));
}
TEST_F(test_cifstream, d5_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_darray.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs << 9 << endl;
  ofs << 10 << endl;
  ofs << 11 << endl;
  ofs << 12 << endl;
  ofs << 13 << endl;
  ofs << 14 << endl;
  ofs << 15 << endl;
  ofs << 16 << endl;
  ofs << 17 << endl;
  ofs << 18 << endl;
  ofs << 19 << endl;
  ofs << 20 << endl;
  ofs << 21 << endl;
  ofs << 22 << endl;
  ofs << 23 << endl;
  ofs << 24 << endl;
  ofs << 25 << endl;
  ofs << 26 << endl;
  ofs << 27 << endl;
  ofs << 28 << endl;
  ofs << 29 << endl;
  ofs << 30 << endl;
  ofs << 31 << endl;
  ofs << 32 << endl;
  ofs.close();

  d5_array arr5;
  arr5.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_darray.txt");
  cifs >> arr5;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, arr5(1, 1, 1, 1, 1));
  ASSERT_DOUBLE_EQ(2, arr5(1, 1, 1, 1, 2));
  ASSERT_DOUBLE_EQ(3, arr5(1, 1, 1, 2, 1));
  ASSERT_DOUBLE_EQ(4, arr5(1, 1, 1, 2, 2));
  ASSERT_DOUBLE_EQ(5, arr5(1, 1, 2, 1, 1));
  ASSERT_DOUBLE_EQ(6, arr5(1, 1, 2, 1, 2));
  ASSERT_DOUBLE_EQ(7, arr5(1, 1, 2, 2, 1));
  ASSERT_DOUBLE_EQ(8, arr5(1, 1, 2, 2, 2));
  ASSERT_DOUBLE_EQ(9, arr5(1, 2, 1, 1, 1));
  ASSERT_DOUBLE_EQ(10, arr5(1, 2, 1, 1, 2));
  ASSERT_DOUBLE_EQ(11, arr5(1, 2, 1, 2, 1));
  ASSERT_DOUBLE_EQ(12, arr5(1, 2, 1, 2, 2));
  ASSERT_DOUBLE_EQ(13, arr5(1, 2, 2, 1, 1));
  ASSERT_DOUBLE_EQ(14, arr5(1, 2, 2, 1, 2));
  ASSERT_DOUBLE_EQ(15, arr5(1, 2, 2, 2, 1));
  ASSERT_DOUBLE_EQ(16, arr5(1, 2, 2, 2, 2));
  ASSERT_DOUBLE_EQ(17, arr5(2, 1, 1, 1, 1));
  ASSERT_DOUBLE_EQ(18, arr5(2, 1, 1, 1, 2));
  ASSERT_DOUBLE_EQ(19, arr5(2, 1, 1, 2, 1));
  ASSERT_DOUBLE_EQ(20, arr5(2, 1, 1, 2, 2));
  ASSERT_DOUBLE_EQ(21, arr5(2, 1, 2, 1, 1));
  ASSERT_DOUBLE_EQ(22, arr5(2, 1, 2, 1, 2));
  ASSERT_DOUBLE_EQ(23, arr5(2, 1, 2, 2, 1));
  ASSERT_DOUBLE_EQ(24, arr5(2, 1, 2, 2, 2));
  ASSERT_DOUBLE_EQ(25, arr5(2, 2, 1, 1, 1));
  ASSERT_DOUBLE_EQ(26, arr5(2, 2, 1, 1, 2));
  ASSERT_DOUBLE_EQ(27, arr5(2, 2, 1, 2, 1));
  ASSERT_DOUBLE_EQ(28, arr5(2, 2, 1, 2, 2));
  ASSERT_DOUBLE_EQ(29, arr5(2, 2, 2, 1, 1));
  ASSERT_DOUBLE_EQ(30, arr5(2, 2, 2, 1, 2));
  ASSERT_DOUBLE_EQ(31, arr5(2, 2, 2, 2, 1));
  ASSERT_DOUBLE_EQ(32, arr5(2, 2, 2, 2, 2));
}
TEST_F(test_cifstream, i5_array)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_iarray.txt");
  ofs << "# d\n";
  ofs << 1 << endl;
  ofs << 2 << endl;
  ofs << 3 << endl;
  ofs << 4 << endl;
  ofs << 5 << endl;
  ofs << 6 << endl;
  ofs << 7 << endl;
  ofs << 8 << endl;
  ofs << 9 << endl;
  ofs << 10 << endl;
  ofs << 11 << endl;
  ofs << 12 << endl;
  ofs << 13 << endl;
  ofs << 14 << endl;
  ofs << 15 << endl;
  ofs << 16 << endl;
  ofs << 17 << endl;
  ofs << 18 << endl;
  ofs << 19 << endl;
  ofs << 20 << endl;
  ofs << 21 << endl;
  ofs << 22 << endl;
  ofs << 23 << endl;
  ofs << 24 << endl;
  ofs << 25 << endl;
  ofs << 26 << endl;
  ofs << 27 << endl;
  ofs << 28 << endl;
  ofs << 29 << endl;
  ofs << 30 << endl;
  ofs << 31 << endl;
  ofs << 32 << endl;
  ofs.close();

  i5_array arr5;
  arr5.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  cifstream cifs("test_cifstream_iarray.txt");
  cifs >> arr5;
  cifs.close();

  ASSERT_DOUBLE_EQ(1, arr5(1, 1, 1, 1, 1));
  ASSERT_DOUBLE_EQ(2, arr5(1, 1, 1, 1, 2));
  ASSERT_DOUBLE_EQ(3, arr5(1, 1, 1, 2, 1));
  ASSERT_DOUBLE_EQ(4, arr5(1, 1, 1, 2, 2));
  ASSERT_DOUBLE_EQ(5, arr5(1, 1, 2, 1, 1));
  ASSERT_DOUBLE_EQ(6, arr5(1, 1, 2, 1, 2));
  ASSERT_DOUBLE_EQ(7, arr5(1, 1, 2, 2, 1));
  ASSERT_DOUBLE_EQ(8, arr5(1, 1, 2, 2, 2));
  ASSERT_DOUBLE_EQ(9, arr5(1, 2, 1, 1, 1));
  ASSERT_DOUBLE_EQ(10, arr5(1, 2, 1, 1, 2));
  ASSERT_DOUBLE_EQ(11, arr5(1, 2, 1, 2, 1));
  ASSERT_DOUBLE_EQ(12, arr5(1, 2, 1, 2, 2));
  ASSERT_DOUBLE_EQ(13, arr5(1, 2, 2, 1, 1));
  ASSERT_DOUBLE_EQ(14, arr5(1, 2, 2, 1, 2));
  ASSERT_DOUBLE_EQ(15, arr5(1, 2, 2, 2, 1));
  ASSERT_DOUBLE_EQ(16, arr5(1, 2, 2, 2, 2));
  ASSERT_DOUBLE_EQ(17, arr5(2, 1, 1, 1, 1));
  ASSERT_DOUBLE_EQ(18, arr5(2, 1, 1, 1, 2));
  ASSERT_DOUBLE_EQ(19, arr5(2, 1, 1, 2, 1));
  ASSERT_DOUBLE_EQ(20, arr5(2, 1, 1, 2, 2));
  ASSERT_DOUBLE_EQ(21, arr5(2, 1, 2, 1, 1));
  ASSERT_DOUBLE_EQ(22, arr5(2, 1, 2, 1, 2));
  ASSERT_DOUBLE_EQ(23, arr5(2, 1, 2, 2, 1));
  ASSERT_DOUBLE_EQ(24, arr5(2, 1, 2, 2, 2));
  ASSERT_DOUBLE_EQ(25, arr5(2, 2, 1, 1, 1));
  ASSERT_DOUBLE_EQ(26, arr5(2, 2, 1, 1, 2));
  ASSERT_DOUBLE_EQ(27, arr5(2, 2, 1, 2, 1));
  ASSERT_DOUBLE_EQ(28, arr5(2, 2, 1, 2, 2));
  ASSERT_DOUBLE_EQ(29, arr5(2, 2, 2, 1, 1));
  ASSERT_DOUBLE_EQ(30, arr5(2, 2, 2, 1, 2));
  ASSERT_DOUBLE_EQ(31, arr5(2, 2, 2, 2, 1));
  ASSERT_DOUBLE_EQ(32, arr5(2, 2, 2, 2, 2));
}
TEST_F(test_cifstream, adstring2)
{
  std::ofstream ofs("test_cifstream_adstring.txt");
  ofs << "# d\n";
  ofs << "testadstring 2\n" << endl;
  ofs.close();

  adstring ads;

  cifstream cifs("test_cifstream_adstring.txt");
  cifs >> ads;
  cifs.close();

  ASSERT_STREQ((char*)ads, "testadstring");
}
TEST_F(test_cifstream, char_array)
{
  std::ofstream ofs("test_cifstream_adstring.txt");
  ofs << "# d\n";
  ofs << "testadstring 2\n" << endl;
  ofs.close();

  char char_array[100];

  cifstream cifs("test_cifstream_adstring.txt");
  cifs >> char_array;
  cifs.close();

  ASSERT_STREQ(char_array, "testadstring");
}
TEST_F(test_cifstream, constadstring)
{
  std::ofstream ofs("test_cifstream_adstring.txt");
  ofs << "# d\n";
  ofs << "testadstring 2\n" << endl;
  ofs.close();

  const adstring ads;

  cifstream cifs("test_cifstream_adstring.txt");
  cifs >> ads;
  cifs.close();

  ASSERT_STREQ((const char*)ads, "testadstring");
}
TEST_F(test_cifstream, line_adstring)
{
  std::ofstream ofs("test_cifstream_adstring.txt");
  ofs << "# d\n";
  ofs << "testadstring 2" << endl;
  ofs.close();

  line_adstring lads;

  cifstream cifs("test_cifstream_adstring.txt");
  cifs >> lads;
  cifs.close();

  ASSERT_STREQ((const char*)lads, "testadstring 2\n");
}
/*
TEST_F(test_cifstream, gradient_structure)
{
  gradient_structure gs;

  std::ofstream ofs("test_cifstream_adstring.txt");
  ofs << "# d\n";
  ofs << "testadstring 2" << endl;
  ofs.close();

  line_adstring lads;

  cifstream cifs("test_cifstream_adstring.txt");
  cifs >> lads;
  cifs.close();

  ASSERT_STREQ((const char*)lads, "testadstring 2\n");
}
*/
TEST_F(test_cifstream, constline_adstring)
{
  std::ofstream ofs("test_cifstream_adstring.txt");
  ofs << "# d\n";
  ofs << "testadstring 2" << endl;
  ofs.close();

  const line_adstring lads;

  cifstream cifs("test_cifstream_adstring.txt");
  cifs >> lads;
  cifs.close();

  ASSERT_STREQ((const char*)lads, "testadstring 2\n");
}
TEST_F(test_cifstream, constlonglong)
{
  std::ofstream ofs("test_cifstream_longlong.txt");
  ofs << "# d\n";
  ofs << INT_MAX << endl;
  ofs.close();

  const long long ll = -1;

  cifstream cifs("test_cifstream_longlong.txt");
  cifs >> ll;
  cifs.close();

  ASSERT_EQ(ll, INT_MAX);
}
TEST_F(test_cifstream, longlong)
{
  std::ofstream ofs("test_cifstream_longlong.txt");
  ofs << "# d\n";
  ofs << INT_MAX << endl;
  ofs.close();

  long long ll = -1;

  cifstream cifs("test_cifstream_longlong.txt");
  cifs >> ll;
  cifs.close();

  ASSERT_EQ(ll, INT_MAX);
}
TEST_F(test_cifstream, float)
{
  std::ofstream ofs("test_cifstream_float.txt");
  ofs << "# d\n";
  ofs << "3.56\n";
  ofs.close();

  float f;
  cifstream cifs("test_cifstream_float.txt");
  cifs >> f;
  cifs.close();

  ASSERT_FLOAT_EQ(3.56, f);
}
TEST_F(test_cifstream, long)
{
  std::ofstream ofs("test_cifstream_float.txt");
  ofs << "# d\n";
  ofs << "356345\n";
  ofs.close();

  long l;
  cifstream cifs("test_cifstream_float.txt");
  cifs >> l;
  cifs.close();

  ASSERT_EQ(356345, l);
}
TEST_F(test_cifstream, lvector)
{
  std::ofstream ofs("test_cifstream_float.txt");
  ofs << "# d\n";
  ofs << "356345 9445938 43948093 993859\n";
  ofs.close();

  lvector lvec;
  ASSERT_FALSE(allocated(lvec));
  lvec.allocate(1, 4);
  ASSERT_TRUE(allocated(lvec));
  cifstream cifs("test_cifstream_float.txt");
  cifs >> lvec;
  cifs.close();

  ASSERT_EQ(356345, lvec(1));
  ASSERT_EQ(9445938, lvec(2));
  ASSERT_EQ(43948093, lvec(3));
  ASSERT_EQ(993859, lvec(4));
}
TEST_F(test_cifstream, lvector2)
{
  std::ofstream ofs("test_cifstream_float.txt");
  ofs << "# d\n";
  ofs << "356345 9445938 43948093 993859\n";
  ofs.close();

  lvector lvec(1, 4);
  ASSERT_TRUE(allocated(lvec));
  cifstream cifs("test_cifstream_float.txt");
  cifs >> lvec;
  cifs.close();

  ASSERT_EQ(356345, lvec(1));
  ASSERT_EQ(9445938, lvec(2));
  ASSERT_EQ(43948093, lvec(3));
  ASSERT_EQ(993859, lvec(4));
}
