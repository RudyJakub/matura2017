#include <iostream>
#include <ctime>
#include <string>

int daysBetween(std::string date1, std::string date2) {
    std::cout << date1.substr(5,2) << std::endl;
    int difference = 0;
    struct std::tm a = {0,0,0,24,5,104}; /* June 24, 2004 */
    struct std::tm b = {0,0,0,5,6,104}; /* July 5, 2004 */
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
    {
        difference = std::difftime(y, x) / (60 * 60 * 24);
        std::cout << std::ctime(&x);
        std::cout << std::ctime(&y);
        std::cout << "difference = " << difference << " days" << std::endl;
    }
    return difference;
}

int main()
{
    // yyyy-mm-dd
    std::cout << daysBetween("2011-06-21", "2017-01-01") << std::endl;
}