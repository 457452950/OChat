#ifndef OCHAT__COMMON_CONFIG__CONFIG_H
#define OCHAT__COMMON_CONFIG__CONFIG_H

#include <QString>

class Config {
public:
    Config();
    ~Config() = default;

    QString log_formater() const;

private:
    QString log_formater_{"[%{time yyyyMMdd h:mm:ss.zzz}][%{type}][%{pid}-%{threadid}][%{file}:%{line}]:%{message}"};
};

#endif // OCHAT__COMMON_CONFIG__CONFIG_H
