#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adthread.h>
#include <string>

class tests_adthread_manager: public ::testing::Test {};

TEST_F(tests_adthread_manager, constructor)
{
  int nthread = 1;
  int ngroups = 1;
  ivector ng(1, ngroups);
  // number of threads in group 1
  ng(1)=nthread;
  // create instance of pthread_manager class 
  // third argument is number of bytes in the transfer buffer
  ad_comm::pthread_manager = new adpthread_manager(ngroups, ng, 32005);
  if (ad_comm::pthread_manager == 0)
  {
    FAIL();
  }
  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}

static int test_attach_code_value = 0;
void* test_attach_code(void* ptr)
{
  test_attach_code_value = 1;
  return ptr;
}
TEST_F(tests_adthread_manager, attach_code)
{
  int nthread = 1;
  int ngroups = 1;
  ivector ng(1, ngroups);
  // number of threads in group 1
  ng(1)=nthread;
  // create instance of pthread_manager class 
  // third argument is number of bytes in the transfer buffer
  ad_comm::pthread_manager = new adpthread_manager(ngroups, ng, 32005);
  if (ad_comm::pthread_manager == 0)
  {
    FAIL();
  }

  ASSERT_EQ(0, test_attach_code_value);
  ad_comm::pthread_manager->attach_code(test_attach_code);
  ASSERT_EQ(0, test_attach_code_value);

  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}
TEST_F(tests_adthread_manager, create_all)
{
  int nthread = 1;
  int ngroups = 1;
  ivector ng(1, ngroups);
  // number of threads in group 1
  ng(1)=nthread;
  // create instance of pthread_manager class 
  // third argument is number of bytes in the transfer buffer
  ad_comm::pthread_manager = new adpthread_manager(ngroups, ng, 32005);
  if (ad_comm::pthread_manager == 0)
  {
    FAIL();
  }

  ASSERT_EQ(0, test_attach_code_value);
  ad_comm::pthread_manager->attach_code(test_attach_code);
  ASSERT_EQ(0, test_attach_code_value);

  new_thread_data* data = new new_thread_data[nthread + 1];
  for (int i = 1; i <= nthread; i++)
  {
    data[i].thread_no = i;
  }

  //This starts thread after a unknown delay
  ad_comm::pthread_manager->create_all(data);
  //ASSERT_EQ(0, test_attach_code_value);

  //Need to join it
  ad_comm::pthread_manager->pthread_join_all();
  ASSERT_EQ(1, test_attach_code_value);

  delete [] data;
  data = 0;

  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}
static int test_attach_code_value_5threads = 0;
pthread_mutex_t test_attach_code_value_5threads_mutex = PTHREAD_MUTEX_INITIALIZER;
void* test_attach_code_5threads(void* ptr)
{
  pthread_mutex_lock(&test_attach_code_value_5threads_mutex);
  test_attach_code_value_5threads++;
  pthread_mutex_unlock(&test_attach_code_value_5threads_mutex);
  return ptr;
}
TEST_F(tests_adthread_manager, create_all_5threads)
{
  int nthread = 5;
  int ngroups = 1;
  ivector ng(1, ngroups);
  // number of threads in group 1
  ng(1)=nthread;
  // create instance of pthread_manager class 
  // third argument is number of bytes in the transfer buffer
  ad_comm::pthread_manager = new adpthread_manager(ngroups, ng, 32005);
  if (ad_comm::pthread_manager == 0)
  {
    FAIL();
  }

  ASSERT_EQ(0, test_attach_code_value_5threads);
  ad_comm::pthread_manager->attach_code(test_attach_code_5threads);
  ASSERT_EQ(0, test_attach_code_value_5threads);

  new_thread_data* data = new new_thread_data[nthread + 1];
  for (int i = 1; i <= nthread; i++)
  {
    data[i].thread_no = i;
  }

  //This starts thread after a unknown delay
  ad_comm::pthread_manager->create_all(data);
  //ASSERT_EQ(0, test_attach_code_value_5threads);

  //Need to join it
  ad_comm::pthread_manager->pthread_join_all();
  ASSERT_EQ(5, test_attach_code_value_5threads);

  delete [] data;
  data = 0;

  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}
static int lflag = 0;
pthread_mutex_t lflag_mutex = PTHREAD_MUTEX_INITIALIZER;
void* test_read_lock_buffer(void* ptr)
{
  //gradient_structure gs(30000000);
  //ad_comm::pthread_manager->write_lock_buffer(0);
  //ad_comm::pthread_manager->write_unlock_buffer(0);
  pthread_mutex_lock(&lflag_mutex);
  lflag++;
  pthread_mutex_unlock(&lflag_mutex);
  return ptr;
}
TEST_F(tests_adthread_manager, read_lock_buffer)
{
  const int nthread = 5;
  const int ngroups = 1;
  ivector ng(1, ngroups);
  // number of threads in group 1
  ng(1)=nthread;
  // create instance of pthread_manager class 
  // third argument is number of bytes in the transfer buffer
  ad_comm::pthread_manager = new adpthread_manager(ngroups, ng, 32005);
  if (ad_comm::pthread_manager == 0)
  {
    FAIL();
  }

  ad_comm::pthread_manager->attach_code(test_read_lock_buffer);

  new_thread_data data[nthread + 1];
  for (int i = 0; i <= nthread; i++)
  {
    data[i].thread_no = i;
  }

/*
  for (int i = 1; i <= nthread; i++)
  {
    ad_comm::pthread_manager->write_lock_buffer(i);
    ad_comm::pthread_manager->send_int(1, i);
    ad_comm::pthread_manager->write_unlock_buffer(i);
  }
*/

  ASSERT_EQ(0, lflag);
  //This starts thread after a unknown delay
  ad_comm::pthread_manager->create_all(&data);
  //Need to join it
  ad_comm::pthread_manager->pthread_join_all();
  ASSERT_EQ(5, lflag);

  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}
void* test_cwrite_lock_buffer(void* ptr)
{
  new_thread_data* tptr = (new_thread_data*)ptr;
  int i = tptr->thread_no;
cout << "Thread: " << i << endl;
  ad_comm::pthread_manager->cwrite_lock_buffer(i);
cout << "UNThread: " << i << endl;
  lflag--;
  return ptr;
}
/*
TEST_F(tests_adthread_manager, cwrite_lock_buffer)
{
  const int nthread = 5;
  const int ngroups = 1;
  ivector ng(1, ngroups);
  // number of threads in group 1
  ng(1)=nthread;
  // create instance of pthread_manager class 
  // third argument is number of bytes in the transfer buffer
  ad_comm::pthread_manager = new adpthread_manager(ngroups, ng, 32005);
  if (ad_comm::pthread_manager == 0)
  {
    FAIL();
  }

  ad_comm::pthread_manager->attach_code(test_cwrite_lock_buffer);

  new_thread_data data[nthread + 1];
  for (int i = 0; i <= nthread; i++)
  {
    data[i].thread_no = i;
  }

  lflag = 0;
  for (int i = 1; i <= nthread; i++)
  {
    ad_comm::pthread_manager->cwrite_lock_buffer(i);
    lflag++;
    ad_comm::pthread_manager->cwrite_unlock_buffer(i);
  }
  ASSERT_EQ(5, lflag);

  //This starts thread after a unknown delay
  ad_comm::pthread_manager->create_all(&data);
  ASSERT_EQ(5, lflag);
  cout << __func__ << ':' << __LINE__ << endl;
  sleep(1);
  cout << __func__ << ':' << __LINE__ << endl;
  for (int i = 1; i <= nthread; i++)
  {
  cout << __func__ << ':' << __LINE__ << endl;
    ad_comm::pthread_manager->cwrite_unlock_buffer(i);
  cout << __func__ << ':' << __LINE__ << endl;
  }
  cout << __func__ << ':' << __LINE__ << endl;
  ad_comm::pthread_manager->pthread_join_all();
  cout << __func__ << ':' << __LINE__ << endl;
  //Need to join it
  ASSERT_EQ(0, lflag);

  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}
*/
class tests_adthread_buffer: public ::testing::Test {};
TEST_F(tests_adthread_buffer, constructor)
{
  adthread_buffer b;
}
TEST_F(tests_adthread_buffer, copy_constructor)
{
  adthread_buffer a;
  adthread_buffer b(a);
}
int count = 0;
void* testlock(void* ptr)
{
  adthread_buffer* a = (adthread_buffer*)ptr;
  count++;
  a->lock();
  count++;
  return ptr;
}
void* testunlock(void* ptr)
{
  adthread_buffer* a = (adthread_buffer*)ptr;
  a->unlock();
  return ptr;
}
TEST_F(tests_adthread_buffer, read_lock_buffer)
{
  adthread_buffer a;
  pthread_t ptlock;
  pthread_t ptunlock;

  count = 0;
  ASSERT_EQ(0, count);
  pthread_create(&ptlock, NULL, &testlock, &a);
  pthread_create(&ptunlock, NULL, &testunlock, &a);
  pthread_join(ptlock, NULL);
  pthread_join(ptunlock, NULL);
  ASSERT_EQ(2, count);
}
TEST_F(tests_adthread_buffer, read_lock_buffer2)
{
  adthread_buffer a;
  pthread_t ptlock;

  count = 0;
  ASSERT_EQ(0, count);
  pthread_create(&ptlock, NULL, &testlock, &a);
  ASSERT_EQ(false, a.islocked());
  while (!a.islocked())
  {
    sleep(1);
  }
  ASSERT_EQ(true, a.islocked());
  a.unlock();
  pthread_join(ptlock, NULL);
  ASSERT_EQ(2, count);
}
TEST_F(tests_adthread_buffer, int_binary_to_stdstring)
{
  const size_t sizeofint = sizeof(int);

  std::string str;
  int value = 123789;
  char* ptr = (char*)&value;
  str.append(ptr, sizeofint);
  int expected = 0;
  char* ptr2 = (char*)&expected;
  memcpy(ptr2, str.c_str(), sizeofint);
  ASSERT_EQ(expected, value);

  int value2 = 456321;
  ptr = (char*)&value2;
  str.append(ptr, sizeofint);
  const char* ptr3 = str.c_str();
  memcpy(ptr2, &ptr3[sizeofint], sizeofint);
  ASSERT_EQ(expected, value2);
}
TEST_F(tests_adthread_buffer, double_binary_to_stdstring)
{
  const size_t sizeofdouble = sizeof(double);

  std::string str;
  double value = 123789.456321;
  char* ptr = (char*)&value;
  str.append(ptr, sizeofdouble);
  double expected = 0;
  char* ptr2 = (char*)&expected;
  memcpy(ptr2, str.c_str(), sizeofdouble);
  ASSERT_EQ(expected, value);

  double value2 = 456321.123789;
  ptr = (char*)&value2;
  str.append(ptr, sizeofdouble);
  const char* ptr3 = str.c_str();
  memcpy(ptr2, &ptr3[sizeofdouble], sizeofdouble);
  ASSERT_EQ(expected, value2);
}
TEST_F(tests_adthread_buffer, push_pop_int)
{
  adthread_buffer a;
  const int value = 123789;
  a.push(value);
  int expected = 0;
  a.pop(expected);
  ASSERT_EQ(expected, value);
}
TEST_F(tests_adthread_buffer, push_pop_int_3x)
{
  adthread_buffer a;

  const int expected1 = 123789;
  a.push(expected1);
  const int expected2 = 72891;
  a.push(expected2);
  const int expected3 = 789123;
  a.push(expected3);

  int value3 = 0;
  a.pop(value3);
  ASSERT_EQ(expected3, value3);

  int value2 = 0;
  a.pop(value2);
  ASSERT_EQ(expected2, value2);

  int value1 = 0;
  a.pop(value1);
  ASSERT_EQ(expected1, value1);
}
TEST_F(tests_adthread_buffer, push_pop_double)
{
  adthread_buffer a;
  const double expected = 123789.9876;
  a.push(expected);
  double value = 0;
  a.pop(value);
  ASSERT_EQ(expected, value);
}
TEST_F(tests_adthread_buffer, push_pop_double_3x)
{
  adthread_buffer a;

  const double expected1 = 123789.45;
  a.push(expected1);
  const double expected2 = 72891.221;
  a.push(expected2);
  const double expected3 = 789123.101;
  a.push(expected3);

  double value3 = 0;
  a.pop(value3);
  ASSERT_EQ(expected3, value3);

  double value2 = 0;
  a.pop(value2);
  ASSERT_EQ(expected2, value2);

  double value1 = 0;
  a.pop(value1);
  ASSERT_EQ(expected1, value1);
}
TEST_F(tests_adthread_buffer, push_pop_chararray)
{
  adthread_buffer a;
  const char* expected = "123789.9876\0";
  a.push(expected);
  char* value = new char[strlen(expected) + 1];
  a.pop(value);
  value[strlen(expected)] = '\0';
  ASSERT_STREQ(expected, value);
  delete value;
  value = 0;
}
TEST_F(tests_adthread_buffer, push_pop_chararray_3x)
{
  adthread_buffer a;
  const char* expected1 = "123789.9876\0";
  a.push(expected1);
  const char* expected2 = "72891.221\0";
  a.push(expected2);
  const char* expected3 = "789123.101\0";
  a.push(expected3);

  char* value3 = new char[strlen(expected3) + 1];
  a.pop(value3);
  value3[strlen(expected3)] = '\0';
  ASSERT_STREQ(expected3, value3);
  delete value3;
  value3 = 0;

  char* value2 = new char[strlen(expected2) + 1];
  a.pop(value2);
  value2[strlen(expected2)] = '\0';
  ASSERT_STREQ(expected2, value2);
  delete value2;
  value2 = 0;

  char* value1 = new char[strlen(expected1) + 1];
  a.pop(value1);
  value1[strlen(expected1)] = '\0';
  ASSERT_STREQ(expected1, value1);
  delete value1;
  value1 = 0;
}
class tests_adthread: public ::testing::Test {};
TEST_F(tests_adthread, constructor)
{
  adthread t;
}
TEST_F(tests_adthread, create)
{
  adthread t;
  t.create();
}
