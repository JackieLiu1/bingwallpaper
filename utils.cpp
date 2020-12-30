#include <curl/curl.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include <fstream>
#include <exception>

#include <utils.hpp>
#include <define.hpp>

namespace BING
{

#define CURL_BREAK_IF_NOT_OK(code)     if (code != CURLE_OK) break

	bool DownloadFile(const std::string &url, const std::string &savename)
	{
		CURL *pCurl         = curl_easy_init();
		int responseCode    = -1;
		CURLcode returnCode = CURLE_OK;

		FILE *fp = fopen(savename.c_str(), "wb+");

		DO_WHILE_CODE_BEGIN

		if (fp == nullptr)  break;
		if (!pCurl)         break;

		returnCode = curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, 10 * 1000);
		CURL_BREAK_IF_NOT_OK(returnCode);

		returnCode = curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str());
		CURL_BREAK_IF_NOT_OK(returnCode);

		returnCode = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, fp);
		CURL_BREAK_IF_NOT_OK(returnCode);

		returnCode = curl_easy_perform(pCurl);
		CURL_BREAK_IF_NOT_OK(returnCode);

		returnCode = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &responseCode);

		DO_WHILE_CODE_END


		if (fp)
			fclose(fp);

		if (pCurl)
			curl_easy_cleanup(pCurl);

		return responseCode == 200 ? true : false;
	}

	nlohmann::json GetJSON(const std::string &filename)
	{
		std::ifstream ifs(filename.c_str(), std::ifstream::in);

		try {
			return nlohmann::json::parse(ifs);
		} catch (std::exception &e) {
			/* something wrong */
			return nlohmann::json{};   
		}
	}

	time_t ConvertDate2Time(const std::string &date)
	{
		char buf[12] = {0};
		/* year */
		memcpy(buf, date.c_str(), 4);
		/* month */
		memcpy(buf + 5, date.c_str() + 4, 2);
		/* date */
		memcpy(buf + 8, date.c_str() + 6, 2);

		struct tm timeValue;
		memset(&timeValue, 0, sizeof(struct tm));
		timeValue.tm_sec  = 59;
		timeValue.tm_min  = 59;
		timeValue.tm_hour = 23;
		timeValue.tm_mday = atoi(buf + 8);
		timeValue.tm_mon  = atoi(buf + 5) - 1;
		timeValue.tm_year = atoi(buf) - 1900;

		return mktime(&timeValue);
	}

	void SetDesktopBackground(const std::string &filepath)
	{
		std::string s = std::string("gsettings set org.mate.background picture-filename ") + filepath.substr(6);
		system(s.c_str());
	}

	std::string Int2String(int value)
	{
		char buf[128] = {0};
		sprintf(buf, "%d", value);
		return buf;
	}

}   // endof namespace AUTO_BING
