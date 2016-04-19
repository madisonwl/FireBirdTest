#pragma once
#include"../ibpp-core/ibpp.h"
#include <windowsx.h>

#define  IBPP_WINDOWS


using namespace std;

IBPP::Database db;      //数据库实例
IBPP::Transaction tr;   //事务：Transaction实例，进行事务管理
IBPP::Statement st;     //Statement实例，用于执行SQL指令