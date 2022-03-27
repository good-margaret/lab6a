#include <iostream>
#include <fstream>
#include <ctime>

#define TIME_TEST(testCode, message) { \
clock_t start_time = clock(); \
testCode \
clock_t end_time = clock();\
clock_t code_time = end_time - start_time; \
std::clog << message << ": " \
<< (double) code_time / CLOCKS_PER_SEC << std::endl; \
}

int main() {
    std::setvbuf(stdout, nullptr, _IOFBF, 1000000);

    const char *filename = "tmp.txt";
    std::ofstream file(filename);

    TIME_TEST ({
                   for (int i = 0; i < 1000000; i++)
                       file << 'a' << std::endl;
               }, " Often buffer reset ");

    TIME_TEST ({
                   for (int i = 0; i < 1000000; i++)
                       file << 'a' << '\n';
               }, " Buffer opt");

    file.close();
    std::remove(filename);

    return 0;
}