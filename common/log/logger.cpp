#include "logger.h"

#include <QtLogging>

#include "../config/client_setting.h"

void LoggerInit()
{
    qSetMessagePattern(SETTING->config.log_formater());
}
