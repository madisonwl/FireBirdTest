#include "FireBirdConsolTest.h"

#include<iostream>
#include <assert.h>

//���ݿ�����
const char* g_szDBName = "d:\\test.fdb";
//����������Ƕ��ʽΪ���ַ� ""
const char* g_szServerName = "";
//Ƕ��ʽ���û�����������FireBird��Ĭ�ϵģ������������Լ��趨��
//Ƕ��ʽû�м��ܹ���
const char* g_szUserName = "SYSDBA";
const char* g_szPassword = "masterkey";

int main()
{
	IBPP::Database db;
	db = IBPP::DatabaseFactory(g_szServerName,g_szDBName,g_szUserName,g_szPassword);
	//�������ݿ�
	db->Connect();

	IBPP::Transaction tr = IBPP::TransactionFactory(db);
	tr->Start();
	try
	{
		IBPP::Statement st = IBPP::StatementFactory(db,tr);
		//�������ݿ�
		st->ExecuteImmediate("CREATE TABLE BlobTable(""    ID INTEGER NOT NULL,""    RES BLOB)");
		//������
		st->ExecuteImmediate("CREATE GENERATOR BlobTable_ID_Gen");
		//������
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
		//����Blob��һ��100�ֽڵ��ڴ�
		{
			IBPP::Blob res = IBPP::BlobFactory(db, tr);
			res->Create();
			char buf[100];
			for (int i = 0; i < 100; i++) buf[i] = i;
			res->Write(buf, sizeof(buf));
			res->Close();
			st->Set(1, res); //��һ���ʺ�
			st->Execute();
		}
		//����Blob,һ���ַ���
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
		//��ʾSELECT�õ�������
		while(st->Fetch())
		{
			int id;
			IBPP::Blob res = IBPP::BlobFactory(db,tr);
			st->Get(1,id);
			st->Get(2,res);
			//��ʾBLOB������
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
