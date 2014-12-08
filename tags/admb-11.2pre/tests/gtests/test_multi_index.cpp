#include <gtest/gtest.h>
#include <fvar.hpp>

/**
class multi_index
{
   int mind;
   int maxd;
   int depth;
   ivector index;
 public:
   multi_index(int min, int max, int dim);
   ivector & operator () (void)
   {
      return index;
   }
   void operator ++(void);
   int get_depth(void)
   {
      return depth;
   }
   int get_offset(void);
   void initialize();
};
*/
class test_multi_index: public ::testing::Test {};

TEST_F(test_multi_index, constructor)
{
  multi_index mi(1, 3, 4);
  ivector& iv = mi();
  ASSERT_EQ(1, iv.indexmin());
  ASSERT_EQ(4, iv.indexmax());
  ASSERT_EQ(1, iv(1));
  ASSERT_EQ(1, iv(2));
  ASSERT_EQ(1, iv(3));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(0, mi.get_offset());
}
TEST_F(test_multi_index, operator_plusplus)
{
  multi_index mi(1, 3, 4);

  ++mi;
  ivector& iv = mi();
  ASSERT_EQ(1, iv.indexmin());
  ASSERT_EQ(4, iv.indexmax());
  ASSERT_EQ(2, iv(1));
  ASSERT_EQ(1, iv(2));
  ASSERT_EQ(1, iv(3));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(1, mi.get_offset());

  ++mi;
  ivector& iv2 = mi();
  ASSERT_EQ(1, iv2.indexmin());
  ASSERT_EQ(4, iv2.indexmax());
  ASSERT_EQ(3, iv2(1));
  ASSERT_EQ(1, iv2(2));
  ASSERT_EQ(1, iv2(3));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(2, mi.get_offset());

  mi() = 7;
  ivector& iv3 = mi();
  ASSERT_EQ(1, iv3.indexmin());
  ASSERT_EQ(4, iv3.indexmax());
  ASSERT_EQ(7, iv3(1));
  ASSERT_EQ(7, iv3(2));
  ASSERT_EQ(7, iv3(3));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(6, mi.get_offset());

  ++mi;
  ivector& iv4 = mi();
  ASSERT_EQ(1, iv4.indexmin());
  ASSERT_EQ(4, iv4.indexmax());
  ASSERT_EQ(1, iv4(1));
  ASSERT_EQ(1, iv4(2));
  ASSERT_EQ(1, iv4(3));
  ASSERT_EQ(5, mi.get_depth());
  ASSERT_EQ(0, mi.get_offset());
}
TEST_F(test_multi_index, operator_plusplus_dim)
{
  multi_index mi(1, 3, 2);

  ++mi;
  ivector& iv = mi();
  ASSERT_EQ(1, iv.indexmin());
  ASSERT_EQ(2, iv.indexmax());
  ASSERT_EQ(2, iv(1));
  ASSERT_EQ(1, iv(2));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(1, mi.get_offset());

  ++mi;
  ivector& iv2 = mi();
  ASSERT_EQ(1, iv2.indexmin());
  ASSERT_EQ(2, iv2.indexmax());
  ASSERT_EQ(3, iv2(1));
  ASSERT_EQ(1, iv2(2));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(2, mi.get_offset());

  mi() = 7;
  ivector& iv3 = mi();
  ASSERT_EQ(1, iv3.indexmin());
  ASSERT_EQ(2, iv3.indexmax());
  ASSERT_EQ(7, iv3(1));
  ASSERT_EQ(7, iv3(2));
  ASSERT_EQ(1, mi.get_depth());
  ASSERT_EQ(6, mi.get_offset());

  ++mi;
  ivector& iv4 = mi();
  ASSERT_EQ(1, iv4.indexmin());
  ASSERT_EQ(2, iv4.indexmax());
  ASSERT_EQ(1, iv4(1));
  ASSERT_EQ(1, iv4(2));
  ASSERT_EQ(3, mi.get_depth());
  ASSERT_EQ(0, mi.get_offset());
}
