//
// Created by parallels on 9/3/23.
//

#ifndef NETWORK_LOG_H
#define NETWORK_LOG_H

#define LOG_DEBUG_TYPE 0
#define LOG_MSG_TYPE   1
#define LOG_WARN_TYPE  2
#define LOG_ERR_TYPE   3

void yolanda_log(int severity, const char *msg);
void yolanda_logx(int severity, const char *errstr, const char *fmt, va_list ap);
void yolanda_msgx(const char *fmt, ...);

#define LOG_MSG(msg) yolanda_log(LOG_MSG_TYPE, msg)
#define LOG_ERR(msg) yolanda_log(LOG_ERR_TYPE, msg)


#endif //NETWORK_LOG_H
