/* coding = utf8 */

/***************************************************************
 * Author          : JackieLiu
 * Email           : <liuyun01@kylinos.com.cn>
 *
 * Created Time    : 2016年01月13日 星期三 15时04分47秒
 * Last Modified   : 2016年01月14日 星期四 14时59分03秒
 *
 * File Name       : main.cpp
 * License         : GPLv3  CopyLeft © Kylin
 *
 * Description     :
 *
 ***************************************************************/

#include <unistd.h>

#include <setting.hpp>

int main(int argc, char *argv[])
{
    BING::Setting *setting = new BING::Setting();
    setting->Init();
    setting->Start();

    while (1) {
        sleep(100000);
    }
}
