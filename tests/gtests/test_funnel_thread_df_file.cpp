#include <thread>
#include <chrono>
#include <gtest/gtest.h>
#include <fvar.hpp>

class funnel_thread_df_file: public ::testing::Test {};

TEST_F(funnel_thread_df_file, default_constructor)
{
  DF_FILE df;
  ASSERT_STREQ(df.cmpdif_file_name, "cmpdiff.tmp");
  ASSERT_TRUE(df.file_ptr != -1);
  ASSERT_EQ(df.toffset, 0);
  ASSERT_EQ(df.offset, 0);
}
TEST_F(funnel_thread_df_file, size_constructor)
{
  DF_FILE df(sizeof(double));
  ASSERT_STREQ(df.cmpdif_file_name, "cmpdiff.tmp");
  ASSERT_TRUE(df.file_ptr != -1);
  ASSERT_EQ(df.toffset, 0);
  ASSERT_EQ(df.offset, 0);
}
TEST_F(funnel_thread_df_file, size_id_constructor)
{
  DF_FILE df(sizeof(double), 1);
  ASSERT_STREQ(df.cmpdif_file_name, "cmpdiff1.tmp");
  ASSERT_TRUE(df.file_ptr != -1);
  ASSERT_EQ(df.toffset, 0);
  ASSERT_EQ(df.offset, 0);
}
TEST_F(funnel_thread_df_file, two_instances)
{
  DF_FILE df(sizeof(double));
  DF_FILE df2(sizeof(double));
  ASSERT_TRUE(df.file_ptr != -1);
  ASSERT_TRUE(df2.file_ptr != -1);

  double v = 4.5;
  df.fwrite(v);
  df2.fwrite(v);
}
TEST_F(funnel_thread_df_file, check_write)
{
  DF_FILE df(sizeof(double));

  double v = 4.5;
  df.fwrite(v);

  ASSERT_EQ(df.toffset, sizeof(double));
  ASSERT_EQ(df.offset, df.toffset);

  double v2 = 0.0;

  memcpy(&v2, df.buff, sizeof(double));

  ASSERT_DOUBLE_EQ(v, v2);
}
TEST_F(funnel_thread_df_file, check_2xwrite)
{
  DF_FILE df(sizeof(double));

  double v1 = 4.5;
  df.fwrite(v1);
  double v2 = 3.5;
  df.fwrite(v2);

  ASSERT_EQ(df.toffset, sizeof(double));
  ASSERT_EQ(df.offset, df.toffset);

  double expectedv1 = 0.0;
  char buffer[sizeof(double)];
  lseek(df.file_ptr, 0, SEEK_SET);
  read(df.file_ptr, &buffer, sizeof(double));
  memcpy(&expectedv1, buffer, sizeof(double));

  char buffer2[sizeof(OFF_T)];
  read(df.file_ptr, &buffer2, sizeof(OFF_T));
  OFF_T pos;
  memcpy(&pos, buffer2, sizeof(OFF_T));
  ASSERT_EQ(pos, sizeof(double));

  double expectedv2 = 0.0;
  memcpy(&expectedv2, df.buff, sizeof(double));

  ASSERT_DOUBLE_EQ(v1, expectedv1);
  ASSERT_DOUBLE_EQ(v2, expectedv2);
}
TEST_F(funnel_thread_df_file, check_3xwrite)
{
  DF_FILE df(sizeof(double));

  double v0 = 2.5;
  df.fwrite(v0);
  double v1 = 4.5;
  df.fwrite(v1);
  double v2 = 3.5;
  df.fwrite(v2);

  ASSERT_EQ(df.toffset, sizeof(double));
  ASSERT_EQ(df.offset, df.toffset);

  char buffer[sizeof(double)];
  char buffer2[sizeof(OFF_T)];
  lseek(df.file_ptr, 0, SEEK_SET);

  double _v0 = 0.0;
  read(df.file_ptr, &buffer, sizeof(double));
  memcpy(&_v0, buffer, sizeof(double));
  ASSERT_DOUBLE_EQ(v0, _v0);

  OFF_T _v0offset = 0.0;
  read(df.file_ptr, &buffer2, sizeof(OFF_T));
  memcpy(&_v0offset, buffer2, sizeof(OFF_T));
  ASSERT_EQ(sizeof(double), _v0offset);

  double _v1 = 0.0;
  read(df.file_ptr, &buffer, sizeof(double));
  memcpy(&_v1, buffer, sizeof(double));
  ASSERT_DOUBLE_EQ(v1, _v1);

  OFF_T _v1offset = 0.0;
  read(df.file_ptr, &buffer2, sizeof(OFF_T));
  memcpy(&_v1offset, buffer2, sizeof(OFF_T));
  ASSERT_EQ(sizeof(double), _v1offset);

  double _v2 = 0.0;
  memcpy(&_v2, df.buff, sizeof(double));
  ASSERT_DOUBLE_EQ(v2, _v2);
}
TEST_F(funnel_thread_df_file, double_write_read)
{
  DF_FILE df(sizeof(double));

  double v = 4.5;
  df.fwrite(v);

  ASSERT_EQ(df.toffset, sizeof(double));

  double v2 = 0;
  df.fread(v2);

  ASSERT_EQ(df.toffset, 0);
  ASSERT_DOUBLE_EQ(v, v2);
}
TEST_F(funnel_thread_df_file, single)
{
  std::thread t([]()
  {
    DF_FILE df(sizeof(double));

    double v = 4.5;
    df.fwrite(v);

    ASSERT_EQ(df.toffset, sizeof(double));

    double v2 = 0;
    df.fread(v2);

    ASSERT_EQ(df.toffset, 0);
    ASSERT_DOUBLE_EQ(v, v2);
  });
  t.join();
}
TEST_F(funnel_thread_df_file, multple)
{
  std::srand(std::time(nullptr));
  auto f = [](const int id)
  {
    int random0 = std::rand() % 3;
    int random1 = std::rand() % 5;
    int random2 = std::rand() % 2;

    std::this_thread::sleep_for (std::chrono::seconds(random0));

    DF_FILE df(sizeof(double), id);

    double v = 4.5;
    for (int i = id; i >= 0; --i)
    {
      df.fwrite(v + i);
      cout << id  << " a: " << (v + i) << endl;
    }

    std::this_thread::sleep_for (std::chrono::seconds(random1));

    ASSERT_EQ(df.toffset, sizeof(double));

    for (int i = 0; i <= id; ++i)
    {
      double v2 = 0;
      df.fread(v2);
      cout << id << " b: " << v2 << endl;
      ASSERT_DOUBLE_EQ(v + i, v2);
    }

    std::this_thread::sleep_for (std::chrono::seconds(random2));

    ASSERT_EQ(df.toffset, 0);
    cout << id << endl;
  };

  std::thread t0(f, 0);
  std::thread t2(f, 2);
  std::thread t4(f, 4);
  std::thread t6(f, 6);
  std::thread t8(f, 8);
  std::thread t1(f, 1);
  std::thread t3(f, 3);
  std::thread t5(f, 5);
  std::thread t7(f, 7);
  std::thread t9(f, 9);

  t0.join();
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
}
TEST_F(funnel_thread_df_file, grad_stack)
{
  gradient_structure::CMPDIF_BUFFER_SIZE = sizeof(double);
  std::srand(std::time(nullptr));
  auto f = [](const int id)
  {
    int random0 = std::rand() % 3;
    int random1 = std::rand() % 5;
    int random2 = std::rand() % 2;

    std::this_thread::sleep_for (std::chrono::seconds(random0));

    grad_stack gs(100, sizeof(double), 0, id);

    double v = 4.5;
    for (int i = id; i >= 0; --i)
    {
      gs.fp->fwrite(v + i);
      cout << id  << " a: " << (v + i) << endl;
    }

    std::this_thread::sleep_for (std::chrono::seconds(random1));

    //ASSERT_EQ(gs.fp->toffset, sizeof(double));

    for (int i = 0; i <= id; ++i)
    {
      double v2 = 0;
      gs.fp->fread(v2);
      cout << id << " b: " << v2 << endl;
      //ASSERT_DOUBLE_EQ(v + i, v2);
    }

    std::this_thread::sleep_for (std::chrono::seconds(random2));

    ASSERT_EQ(gs.fp->toffset, 0);
    cout << id << endl;
  };

  std::thread t0(f, 0);
  std::thread t2(f, 2);
  std::thread t4(f, 4);
  std::thread t6(f, 6);
  std::thread t8(f, 8);
  std::thread t1(f, 1);
  std::thread t3(f, 3);
  std::thread t5(f, 5);
  std::thread t7(f, 7);
  std::thread t9(f, 9);

  t0.join();
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
}
TEST_F(funnel_thread_df_file, grad_stack_sequence)
{
  gradient_structure::CMPDIF_BUFFER_SIZE = sizeof(double);
  std::srand(std::time(nullptr));
  auto f = [](const int id)
  {
    int random0 = std::rand() % 3;
    int random1 = std::rand() % 5;
    int random2 = std::rand() % 2;

    std::this_thread::sleep_for (std::chrono::seconds(random0));

    grad_stack gs(100, sizeof(double), 0, id);

    double v = 4.5;
    for (int i = id; i >= 0; --i)
    {
      gs.fp->fwrite(v + i);
      cout << id  << " a: " << (v + i) << endl;
    }

    std::this_thread::sleep_for (std::chrono::seconds(random1));

    ASSERT_EQ(gs.fp->toffset, sizeof(double));

    for (int i = 0; i <= id; ++i)
    {
      double v2 = 0;
      gs.fp->fread(v2);
      cout << id << " b: " << v2 << endl;
      ASSERT_DOUBLE_EQ(v + i, v2);
    }

    std::this_thread::sleep_for (std::chrono::seconds(random2));

    ASSERT_EQ(gs.fp->toffset, 0);
    cout << id << endl;
  };

  f(0);
  f(2);
  f(4);
  f(6);
  f(8);
  f(1);
  f(3);
  f(5);
  f(7);
  f(9);
}
