#ifndef _BING_HPP_
#define _BING_HPP_

#include <string>

namespace BING
{

class Bing 
{
public:
    bool Init(void);

    std::string StartDate(void)
    {
        return startdate;
    }

    std::string EndDate(void)
    {
        return enddate;
    }

private:
    /* bing images start time */
    std::string  startdate;
    /* bing images end time */
    std::string  enddate;
};

}   // endof namespace BING

#endif  // _BING_HPP_
