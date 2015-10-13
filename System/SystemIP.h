#ifndef SYSTEMIP_H_
#define SYSTEMIP_H_

#include <cstdlib>
#include "../Core/AppManager.h"
using namespace std;

class SystemIP
{
public:
	SystemIP(AppManager &app_man);
	~SystemIP();
	string addIP(string ip_type, string ip);
	string deleteIP(string ip);
	string assignIPToVPS(int ip_id, int vps_id);
	string listIPs();

private:
	AppManager &app_man;
};

#endif
