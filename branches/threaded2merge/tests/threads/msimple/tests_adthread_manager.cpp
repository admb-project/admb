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

  ad_comm::pthread_manager->create_all(data);
  //Need to join it
  ad_comm::pthread_manager->pthread_join_all();
  ASSERT_EQ(1, test_attach_code_value);

  delete [] data;
  data = 0;

  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager = 0;
}
