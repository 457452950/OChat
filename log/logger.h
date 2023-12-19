#ifndef OCHAT_LOGGER_H
#define OCHAT_LOGGER_H

#define LOG_MESSAGE_PATTERN \
"[%{time yyyyMMdd h:mm:ss.zzz}][%{type}][%{pid}-%{threadid}][%{file}:%{line}]:%{message}"

void LoggerInit();

#endif // LOGGER_H
