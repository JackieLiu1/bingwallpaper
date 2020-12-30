/* coding = utf8 */

/***************************************************************
 * Author          : JackieLiu
 * Email           : <liuyun01@kylinos.com.cn>
 *
 * Created Time    : 2016年01月13日 星期三 16时10分38秒
 * Last Modified   : 2016年01月14日 星期四 14时49分00秒
 *
 * File Name       : setting.cpp
 * License         : GPLv3  CopyLeft © Kylin
 *
 * Description     :
 *
 ***************************************************************/

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>

#include <setting.hpp>
#include <define.hpp>
#include <utils.hpp>

namespace BING
{

void WriteJSON2File(const nlohmann::json &json, const std::string &conf)
{
    std::ofstream ofs(conf, std::ios::out);
    ofs << json;
}

void Setting::Init(void)
{
    std::string home = getenv("HOME");
    json = GetJSON(home + BINGWALLPAPER_CONF);
    if (json.is_null()) {
        json = nlohmann::json::parse(R"(
            {
                "startdate" : "20160101",
                "enddate"   : "20160102",
                "index"     : 0,
                "images"    : [
                ]
            }
            )");
    }
    /* clean images path */
    json["images"] = nlohmann::json::parse(R"([])");

    time_t ltime = time(NULL);
    /* download image from bing net */
    if (ConvertDate2Time(json["startdate"]) > ltime || ltime > ConvertDate2Time(json["enddate"])) {
        bing.Init();
        json["startdate"] = bing.StartDate();
        json["enddate"]   = bing.EndDate();
    }

    bool ret1 = ScanImageDir(home + BINGWALLPAPER_DATA_DIR);
    bool ret2 = ScanImageDir(home + BINGWALLPAPER_FAVOR_DIR);
    
    if (ret1 || ret2) {
        int index = json["index"];
        SetDesktopBackground(json["images"][index]["imagepath"]);
    } else {
        exit(-1);
    }

    WriteJSON2File(json, home + BINGWALLPAPER_CONF);
}

void Setting::WriteData(const std::string &imagepath)
{
    nlohmann::json jval = { {"imagepath" , ""}, {"favorites" , false} };
    jval["imagepath"] = "file://" + imagepath;
    json["images"].push_back(jval);
}

bool Setting::ScanImageDir(const std::string &dirname)
{
    bool ret = false;
    struct dirent *direntp = nullptr;

    DIR *dp = opendir(dirname.c_str());
   
    if (dp == nullptr) {
        return ret;
    }

    while ((direntp = readdir(dp)) != nullptr) {
        struct stat statbuf;

        if ((strcmp(direntp->d_name, "..") == 0) || (strcmp(direntp->d_name, ".") == 0)) {
            continue;
        }

        if (stat((dirname + "/" + direntp->d_name).c_str(), &statbuf) == -1) {
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            ScanImageDir(dirname + "/" + direntp->d_name);
        }

        if (S_ISREG(statbuf.st_mode)) {
            WriteData(dirname + "/" + direntp->d_name);
            ret = true;
        }
    }

    closedir(dp);

    return ret;
}

void Setting::Start(void)
{
    timer.setInterval(TIMER_INTERVAL);
    timer.setCallback(std::bind(&Setting::NextPaper, this));
    timer.start();
}

void Setting::NextPaper(void)
{
    unsigned int index = json["index"]; 
    
    index ++;
    if (index >= json["images"].size()) {
        index = json["index"] = 0;
    }

    SetDesktopBackground(json["images"][index]["imagepath"]);

    json["index"] = index;
}

}   // endof namespace BING
