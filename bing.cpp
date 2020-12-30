/* coding = utf8 */

/***************************************************************
 * Author          : JackieLiu
 * Email           : <liuyun01@kylinos.com.cn>
 *
 * Created Time    : 2016年01月13日 星期三 14时36分03秒
 * Last Modified   : 2016年01月15日 星期五 17时15分34秒
 *
 * File Name       : bing.cpp
 * License         : GPLv3  CopyLeft © Kylin
 *
 * Description     :
 *
 ***************************************************************/

#include <bing.hpp>
#include <define.hpp>
#include <utils.hpp>
#include <json.hpp>

#define BING_JSON_URL   "http://www.bing.com/HPImageArchive.aspx?format=js&idx=16&n=16"
#define TMP_JSON_PATH   "/tmp/.bingwallpaper-json"

namespace BING
{

	bool Bing::Init(void)
	{
		DO_WHILE_CODE_BEGIN

		DownloadFile(BING_JSON_URL, TMP_JSON_PATH);
		nlohmann::json BingJsonValue = GetJSON(TMP_JSON_PATH)["images"];

		if (! BingJsonValue.is_array()) break;

		startdate = BingJsonValue[0]["startdate"];
		enddate   = BingJsonValue[0]["enddate"];

		for (uint32_t i = 0; i < BingJsonValue.size(); i ++) {
			std::string url = BingJsonValue[i]["url"];
			url = std::string("bing.com") + url;
			DownloadFile(url, getenv("HOME") + std::string(BINGWALLPAPER_DATA_DIR) + "/BingImage" + Int2String(i));
		}

		return true;

		DO_WHILE_CODE_END

			return false;
	}

}   // endof namespace BING
