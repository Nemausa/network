/**
* @file timestamp.hpp
*
* @brief This message displayed in Doxygen Files index
*
* @ingroup PackageName
* (note: this needs exactly one @defgroup somewhere)
*
* @date	2021-06-20-16-36
* @author Nemausa
* @contact: tappanmorris@outlook.com
*
*/
#ifndef TIMESTAMP
#define TIMESTAMP

#include <chrono>
using namespace std::chrono;

namespace nemausa {
namespace io {

class timestamp {
public:
    timestamp();
    ~timestamp();
    void update();
    double second();
    double millsecond();
    long long microsecond();

	static time_t now_milliseconds()
	{
		return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }
private:
    time_point<high_resolution_clock> begin_;
};

} // namespace io 
} // namespace nemausa

#endif // TIMESTAMP