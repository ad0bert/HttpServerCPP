/**
 * Name        : main.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 07.06.2016
 * Copyright   : Free to share
 * Description : Representation of all http status codes as map
 */
#ifndef _HTTP_STATUS_H
#define _HTTP_STATUS_H

#include <map>

typedef std::map<std::string, int> statusList;

static const statusList sl = {{"Continue", 100}, {"Switching Protocols", 101}, {"Processing", 102}, 
  
                              {"OK", 200}, {"Created", 201}, {"Accepted", 202},
                              {"Non-Authoritative Information", 203}, {"No Content", 204}, {"Reset Content", 205},
                              {"Partial Content", 206}, {"Multi-Status", 207}, {"Already Reported", 208},
                              {"IM Used", 226}, 
                              
                              {"Multiple Choices", 300}, {"Moved Permanently", 301}, {"Found (Moved Temporarily)", 302},
                              {"See Other", 303}, {"Not Modified", 304}, {"Use Proxy", 305},
                              {"(reserviert)", 306}, {"Temporary Redirect", 307}, {"308	Permanent Redirect", 308},
                              
                              {"Bad Request", 400}, {"Unauthorized", 401}, {"Payment Required", 402},
                              {"Forbidden", 403}, {"Not Found", 404}, {"Method Not Allowed", 405},
                              {"Not Acceptable", 406}, {"Proxy Authentication Required", 407}, {"Request Time-out", 408},
                              {"Conflict", 409}, {"Gone", 410}, {"Length Required", 411},
                              {"Precondition Failed", 412}, {"Request Entity Too Large", 413}, {"Request-URL Too Long", 414},
                              {"Unsupported Media Type", 415}, {"Requested range not satisfiable", 416}, {"Expectation Failed", 417},
                              {"I’m a teapot", 418}, {"Policy Not Fulfilled", 420}, {"Misdirected Request", 421},
                              {"Unprocessable Entity", 422}, {"Locked", 423}, {"Failed Dependency", 424},
                              {"Unordered Collection", 425}, {"Upgrade Required", 426}, {"Precondition Required", 428},
                              {"Too Many Requests", 429}, {"Request Header Fields Too Large", 431}, {"Unavailable For Legal Reasons", 451},
                              
                              {"No Response", 444}, {"The request should be retried after doing the appropriate action", 449}, 
                              
                              {"Internal Server Error", 500}, {"Not Implemented", 501}, {"Bad Gateway", 502},
                              {"Service Unavailable", 503}, {"Gateway Time-out", 504}, {"HTTP Version not supported", 505},
                              {"Variant Also Negotiates", 506}, {"Insufficient Storage", 507}, {"Loop Detected", 508},
                              {"Bandwidth Limit Exceeded", 509}, {"Not Extended", 510}, {"Network Authentication Required", 511}
  };

#endif // _HTTP_STATUS_H
