#include "FireBirdConsolTest.h"

#include<iostream>
#include <assert.h>

//数据库名称
const char* g_szDBName = "d:\\test.fdb";
//服务器名，嵌入式为空字符 ""
const char* g_szServerName = "";
//嵌入式的用户名和密码是FireBird的默认的，服务器的是自己设定的
//嵌入式没有加密功能
const char* g_szUserName = "SYSDBA";
const char* g_szPassword = "masterkey";

int main()
{
	IBPP::Database db;
	db = IBPP::DatabaseFactory(g_szServerName,g_szDBName,g_szUserName,g_szPassword);
	//连接数据库
	db->Connect();

	IBPP::Transaction tr = IBPP::TransactionFactory(db);
	tr->Start();
	try
	{
		IBPP::Statement st = IBPP::StatementFactory(db,tr);
		//建立数据库
		st->ExecuteImmediate("CREATE TABLE BlobTable(""    ID INTEGER NOT NULL,""    RES BLOB)");
		//生成器
		st->ExecuteImmediate("CREATE GENERATOR BlobTable_ID_Gen");
		//触发器
		st->ExecuteImmediate(
			"CREATE TRIGGER BlobTable_BI_ID FOR BlobTable "
			"ACTIVE BEFORE INSERT POSITION 0 "
			"AS "
			"BEGIN "
			"    IF(NEW.ID IS NULL) THEN "
			"        NEW.ID = GEN_ID(BlobTable_ID_Gen, 1); "
			"END"
			);
		tr->CommitRetain();
		st->Prepare("INSERT INTO BlobTable(RES) VALUES(?)");
		assert(1==st->Parameters());
		//插入Blob，一块100字节的内存
		{
			IBPP::Blob res = IBPP::BlobFactory(db, tr);
			res->Create();
			char buf[100];
			for (int i = 0; i < 100; i++) buf[i] = i;
			res->Write(buf, sizeof(buf));
			res->Close();
			st->Set(1, res); //第一个问号
			st->Execute();
		}
		//插入Blob,一串字符串
		{
			st->Set(1,string("HAAHHHAHHHAH..."));
			st->Execute();
		}
		tr->Commit();
	}
	catch(IBPP::SQLException &e)
	{
		cerr <<e.what()<<endl;
		tr->Rollback();
	}
	tr->Start();
	try
	{
		IBPP::Statement st = IBPP::StatementFactory(db,tr);
		st->Execute("SELECT * FROM BlobTable");
		//显示SELECT得到的数据
		while(st->Fetch())
		{
			int id;
			IBPP::Blob res = IBPP::BlobFactory(db,tr);
			st->Get(1,id);
			st->Get(2,res);
			//显示BLOB的内容
			res->Open();
			int  size;
			res->Info(&size,NULL,NULL);
			cout<<id << "size is "<<size <<endl;
			char c;
			while(res->Read(&c,1))
			{
				cout << (int)c << ' ';
			}
			cout <<endl;
		}
		tr->Commit();
	}
	catch(IBPP::SQLException &e)
	{
		cerr << e.what() << endl;
		tr->Rollback();
	}
}
