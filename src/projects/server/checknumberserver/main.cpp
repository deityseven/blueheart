#include "httpserver.h"
#include <configfile/config_file.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	system("chcp 65001");
	
	ConfigFile cf("./config/network.json");
	cf.beginSection("CheckNumberServer");

	if(cf.hasKey("host") && cf.hasKey("port"))
	{
		HttpServer hs(cf.value("host").toString(), cf.value("port").toInt());
		cf.endSection();
		hs.run();
	}
	else
	{
		printf("config/network.json hasn't host or port...\n");
	}
	
	return 0;
}

