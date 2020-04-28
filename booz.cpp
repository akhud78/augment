// https://www.boost.org/doc/libs/1_57_0/libs/filesystem/doc/tutorial.html
#include <iostream>
#include <iterator>
#include <algorithm>

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

#include <boost/algorithm/string.hpp>
using namespace boost::filesystem;

// ./augment -t --gtest_filter=BoozTest.*
// Reporting the size of a file
TEST(BoozTest, FileSize) {
  int size = file_size("/etc/issue");
  std::cout << size << "\n";  // size = 29993  
  ASSERT_GT(size, 10);  
}

// https://stackoverflow.com/questions/6697286/catching-exception-from-boostfilesystemis-directory
TEST(BoozTest, FileSizeException) {
  ASSERT_THROW(file_size("foo.bar"), filesystem_error);
}

// ./augment -t --gtest_filter=BoozTest.FileExistence
// Using status queries to determine file existence and type
TEST(BoozTest, FileExistence) {
  path pf("/etc/issue");
  ASSERT_TRUE(exists(pf));     // does p actually exist?
  ASSERT_TRUE(is_regular_file(pf)); // is p a regular file?
  ASSERT_FALSE(is_directory(pf));   // is p a directory?
  path pd("/etc");
  ASSERT_TRUE(exists(pd));
  ASSERT_TRUE(is_directory(pd));
}

/*
    http://www.cplusplus.com/reference/algorithm/copy/
    https://stackoverflow.com/questions/21666654/ostream-iterator-to-a-string-instead-of-cout
*/
// ./augment -t --gtest_filter=BoozTest.DirectoryIteration
// Directory iteration plus catching exceptions
TEST(BoozTest, DirectoryIteration) {
  path p;
  p = "/tmp";
  ASSERT_TRUE(exists(p) && is_directory(p));
  auto first = directory_iterator(p); 
  auto last = directory_iterator();
  auto result = std::ostream_iterator<directory_entry>(std::cout, "\n"); 
  std::copy(first, last, result); 
}

// ./augment -t --gtest_filter=BoozTest.DirectoryIterationRecursive
TEST(BoozTest, DirectoryIterationRecursive) {
  path p("/tmp");
  ASSERT_TRUE(exists(p) && is_directory(p));
  auto first = recursive_directory_iterator(p); 
  auto last = recursive_directory_iterator();
  auto result = std::ostream_iterator<directory_entry>(std::cout, "\n");
  
  try {
    std::copy(first, last, result);
  } catch(std::exception& ex) {
    // error: Permission denied" thrown in the test body.
    std::cout << ex.what() << std::endl;
  }
}

// https://www.boost.org/doc/libs/1_57_0/libs/filesystem/example/path_info.cpp
// Using path decomposition, plus sorting results
// ./augment -t --gtest_filter=BoozTest.DirectoryIterationPathDecomposition
TEST(BoozTest, DirectoryIterationPathDecomposition) {
  using namespace std;
  path p("/tmp");
  ASSERT_TRUE(exists(p) && is_directory(p));
  typedef vector<path> vec;   // store paths,
  vec v;                      // so we can sort them later
  auto first = recursive_directory_iterator(p); 
  auto last = recursive_directory_iterator();
  
  try {
    copy(first, last, back_inserter(v));
  } catch(std::exception& ex) {
    // error: Permission denied" thrown in the test body.
    std::cout << ex.what() << std::endl;
  }
  sort(v.begin(), v.end());   // sort, since directory iteration
                                // is not ordered on some file systems
  std::stringstream ss;
  int k=0;
  for (auto i : v) {
    if (k++ >= 3) break;  // only 3 files
    ss << i << "\n";        
    ss <<  "is_regular_file()------: " << is_regular_file(i) << '\n';
    ss <<  "is_directory()---------: " << is_directory(i) << '\n';
    ss <<  "decomposition:\n";
    ss <<  "  relative_path()------: " << i.relative_path() << '\n';     // "../media/lena.jpg"
    ss <<  "  parent_path()--------: " << i.parent_path() << '\n';       // "../media"
    ss <<  "  filename()-----------: " << i.filename() << '\n';          // "lena.jpg"
    ss <<  "  stem()---------------: " << i.stem() << '\n';              // "lena"
    ss <<  "  extension()----------: " << i.extension() << "\n\n";       // ".jpg"
  }
  ASSERT_TRUE(ss.str().empty() == false);
  //std::cout << ss.str();
}
  
