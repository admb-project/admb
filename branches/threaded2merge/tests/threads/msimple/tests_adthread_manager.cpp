#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adthread.h>

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
