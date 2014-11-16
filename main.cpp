#include <ctime>
#include <iostream>

using namespace std;

int main() {
    time_t t = time(0); // get time now
    struct tm * now = localtime(& t);

    return 0;
}
