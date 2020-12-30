#ifndef _SETTING_HPP_
#define _SETTING_HPP_

#include <list>
#include <string>

#include <json.hpp>
#include <bing.hpp>
#include <timer.hpp>

namespace BING
{

class Setting
{

public: 
    void Init(void);

    void Start(void);

    void NextPaper(void);

    void PrevPaper(void);

    void SetFavorites(void);

private:
    bool ScanImageDir(const std::string &dirname);

    void WriteData(const std::string &imagepath);

private:
    Bing            bing;
    /* setting json value */
    nlohmann::json  json;

    Timer           timer;
}; 

}   // endof namespace BING

#endif  // _SETTING_HPP_
