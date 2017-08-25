#pragma once

#define CURLOGGERWRITE(pLogger, format , ...) \
	if(pLogger) \
		pLogger->write(__FILE__ , __LINE__ , pLogger->get_level(), format , ##__VA_ARGS__);	


#define CURLOGGERWRITEWITHLV(pLogger, lv, format , ...) \
    if(pLogger) \
        pLogger->write(__FILE__ , __LINE__ , lv, format , ##__VA_ARGS__);	