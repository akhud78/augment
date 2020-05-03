// https://www.boost.org/doc/libs/1_57_0/libs/filesystem/doc/tutorial.html
#include <iostream>
#include <iterator>
#include <algorithm>

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

// ./augment -t --gtest_filter=BoozTest.*
// Reporting the size of a file
TEST(BoozTest, FileSize) {
    int size = file_size("../media/lena.jpg");
    std::cout << size << "\n";  // size = 29993  
    ASSERT_GT(size, 10000);  
}

// https://stackoverflow.com/questions/6697286/catching-exception-from-boostfilesystemis-directory
TEST(BoozTest, FileSizeException) {
    ASSERT_THROW(file_size("foo.bar"), filesystem_error);
}


// ./augment -t --gtest_filter=BoozTest.FileExistence
// Using status queries to determine file existence and type
TEST(BoozTest, FileExistence) {
    path pf("../media/lena.jpg");
    ASSERT_TRUE(exists(pf));     // does p actually exist?
    ASSERT_TRUE(is_regular_file(pf)); // is p a regular file?
    ASSERT_FALSE(is_directory(pf));   // is p a directory?
    path pd("../media");
    ASSERT_TRUE(exists(pd));
    ASSERT_TRUE(is_directory(pd));
    
    pd = "../tmp";
    ASSERT_TRUE(is_directory(pd));
    
}

/*
    http://www.cplusplus.com/reference/algorithm/copy/
    https://stackoverflow.com/questions/21666654/ostream-iterator-to-a-string-instead-of-cout
*/

// Directory iteration plus catching exceptions
TEST(BoozTest, DirectoryIteration) {
    path p;
    p = "../media";
    //path p("../media");
    ASSERT_TRUE(exists(p) && is_directory(p));
    auto first = directory_iterator(p); 
    auto last = directory_iterator();
    auto result = std::ostream_iterator<directory_entry>(std::cout, "\n"); 
    std::copy(first, last, result); 
}

// https://www.boost.org/doc/libs/1_57_0/libs/filesystem/example/path_info.cpp
// Using path decomposition, plus sorting results
TEST(BoozTest, DirectoryIterationPathDecomposition) {
    using namespace std;
    path p("../media");
    ASSERT_TRUE(exists(p) && is_directory(p));
    typedef vector<path> vec;   // store paths,
    vec v;                      // so we can sort them later
    copy(directory_iterator(p), directory_iterator(), back_inserter(v));
    sort(v.begin(), v.end());   // sort, since directory iteration
                                // is not ordered on some file systems
    for (auto i : v) {
        cout << i << "\n";        
        cout  <<  "is_regular_file()------: " << is_regular_file(i) << '\n';
        cout  <<  "is_directory()---------: " << is_directory(i) << '\n';
        cout  <<  "decomposition:\n";
        cout  <<  "  relative_path()------: " << i.relative_path() << '\n';     // "../media/lena.jpg"
        cout  <<  "  parent_path()--------: " << i.parent_path() << '\n';       // "../media"
        cout  <<  "  filename()-----------: " << i.filename() << '\n';          // "lena.jpg"
        cout  <<  "  stem()---------------: " << i.stem() << '\n';              // "lena"
        cout  <<  "  extension()----------: " << i.extension() << "\n\n";       // ".jpg"
    }

}
  
