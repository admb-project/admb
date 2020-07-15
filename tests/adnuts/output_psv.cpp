#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "\nUsage:\n\n" << argv[0] << " psv_file\n";
    exit(1);
  }

  std::ifstream ifs(argv[1], std::ios::binary);
  if (!ifs)
  {
    std::cerr << "\nError: Unable to open \'" << argv[1] << "\'\n";
    exit(1);
  }


  std::cout << "--- begin \'" << argv[1] << "\'" << std::endl;

  int n;
  ifs.read((char*)&n, sizeof(n));
  std::cout << n << std::endl;

  int nrecords = 0;

  double v;
  while (ifs)
  {
    for (int i = 0; i < n; ++i)
    {
      ifs.read((char*)&v, sizeof(v));
      std::cout << v << ' ';
    }
    std::cout << std::endl;
    ++nrecords;
  }

  ifs.close();

  std::cout << "--- end \'" << argv[1]
            << "\' nrecords " << nrecords << std::endl;

  return 0;
}
