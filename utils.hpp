#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>

#include <json.hpp>

namespace BING
{

bool DownloadFile(const std::string &url, const std::string &savename);
nlohmann::json GetJSON(const std::string &filename);
time_t ConvertDate2Time(const std::string &date);
void SetDesktopBackground(const std::string &filepath);
std::string Int2String(int);

}   // endof namespace BING

#endif  // _UTILS_HPP_
