#pragma once

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <mysql.h>



void MysqlInit();
void ConnectMysql();
void SendMySQLCommand(char* cmd);
MYSQL_RES* ExecuteQurey(char* cmd);
int ExecuteUpdate(char* cmd);
void ShowErrors();
void CloseMysql();
char* GenerateOrderId();
char mycmd[1024];


//�������Ա��Ϣ�ṹ��
typedef struct _Admin
{
	char* id;
	char* password;
	char* name;
	char* restname;
	char* emali;

}Admin;
//�����û���Ϣ�ṹ��
typedef struct _User
{
	char* id;
	char* password;
	char* phonenum;
	char* name;
	char* emali;
	char* sex;
	char* adreess;
	char* block;
}User;
//���͹���Ϣ�ṹ��
typedef struct _RestInfo
{

	char* restname;
	float startprice;
	float sendprice;
	char* block;
	char* averageSendTime;
	int startHour;
	int startMin;
	int endHour;
	int endMin;
	int recommand;

}RestInfo;

Admin admin;
User user;
RestInfo restInfo;

typedef struct _MysqlInstance
{
	char* host;//��������
	char* user;//�û���
	char* password;//����
	char* database;//Ҫ���ӵ����ݿ�
	unsigned int port;//�˿ں�
	char* unixSocket;
	unsigned long clientflag;
}MysqlInstance;
MysqlInstance mysqlInstance;

MYSQL mysql;


/// <summary>
/// ��ʼ��mysqlInstance
/// </summary>
void MysqlInit()
{
	//����mysql���ӳ�ʼ
	mysqlInstance.host = "127.0.0.1";
	mysqlInstance.user = "WX";
	mysqlInstance.password = "749299";
	mysqlInstance.database = "RestaurantDatabase";
	mysqlInstance.port = 3306;
	mysqlInstance.unixSocket = NULL;
	mysqlInstance.clientflag = 0;
}

/// <summary>
/// ����mysql
/// </summary>
void ConnectMysql()
{
	MysqlInit();
	mysql_init(&mysql);//MYSQL�Դ�c��API,������߳�ʼ��һ��MYSQL����

	//��������mysql���ʧ�ܴ�ӡ������Ϣ
	if (!mysql_real_connect(&mysql, mysqlInstance.host, mysqlInstance.user,
		mysqlInstance.password, mysqlInstance.database, mysqlInstance.port,
		mysqlInstance.unixSocket, mysqlInstance.clientflag))
	{
		ShowErrors();
		return;
	}
	else
	{
		printf("Connect successfully\n");
	}
	//�����ַ���
	if (mysql_set_character_set(&mysql, "gbk"))
	{
		ShowErrors();
		return;
	}
	else
	{
		printf("set_character successfully\n");
	}
}

/// <summary>
/// ��ӡMysql�����г��ֵĴ���
/// </summary>
void ShowErrors()
{
	printf("\n/*********����**********/\n");
	printf("%s\n", mysql_error(&mysql));
	printf("/*********����*********/\n\n");
}

/// <summary>
	/// �ر�mysql����
	/// </summary>
void CloseMysql()
{
	mysql_close(&mysql);
	//�ر�Mysql����
	mysql_server_end();
	//ֹͣMysql����
	printf("mysql sever�ѹر�\n");
}

/// <summary>
	/// ��mysql���Ͳ�ѯ����
	/// </summary>
	/// <param name="cmd"></param>
	/// <returns>����һ�������</returns>
MYSQL_RES* ExecuteQurey(char* cmd)
{
	//��MYSQL��������
	SendMySQLCommand(cmd);
	return mysql_store_result(&mysql);//���ز�ѯ�Ľ����
}

/// <summary>
/// ��mysql������ɾ�Ĳ���
/// </summary>
/// <param name="cmd"></param>
/// <returns>������Ӱ�������</returns>
int ExecuteUpdate(char* cmd)
{
	SendMySQLCommand(cmd);
	return mysql_affected_rows(&mysql);//������Ӱ�������
}

/// <summary>
/// ��mysql��������
/// </summary>
/// <param name="cmd">��������</param>
void SendMySQLCommand(char* cmd)
{
	MysqlInit();
	ConnectMysql();
	unsigned int flag = mysql_real_query(&mysql, cmd, (unsigned int)strlen(cmd));
	if (flag)
	{
		ShowErrors();
	}
	else
	{
		printf("%s made ...\n", cmd);
	}
}




/*****************************************************/
/*********************��*��*Ա*��*��*******************/
/*****************************************************/

/// <summary>
/// ���û���¼ʱ�����û�����Ϣ
/// </summary>
/// <param name="id"></param>
void GetUserInformation(char* id)
{
	
	sprintf_s(mycmd, 1024,
		"Select * From restaurantdatabase.user WHERE id = '%s'", id);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	MYSQL_ROW row = mysql_fetch_row(res);

	//������Ϣ���û��ṹ����
	user.id = id;
	user.name = row[1];
	user.password = row[2];
	user.sex = row[3];
	user.phonenum = row[4];
	user.emali = row[5];
	user.adreess = row[6];
	user.block = row[7];


	printf("\n�ѻ���û���Ϣ\n");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
		user.id, user.name, user.password, user.sex, 
		user.phonenum,user.emali, user.adreess, user.block);

	CloseMysql();
}

/// <summary>
	/// ����û�ע��ID�Ƿ��ظ�
	/// </summary>
	/// <param name="id">Ҫע���id</param>
	/// <param name="user">���</param>
	/// <returns>����ظ���������</returns>
bool CheckID(char* id, char* user)
{
	
	sprintf_s(mycmd, 1024, "SELECT id FROM restaurantdatabase.%s where id = \"%s\"", user, id);

	//�ж��Ƿ�id����
	if (1 == mysql_num_rows(ExecuteQurey(mycmd)))
	{
		CloseMysql();
		return true;
	}
	else
	{
		CloseMysql();
		return false;
	}
}

/// <summary>
/// ����û����룬�˻��Ƿ��Ӧ
/// </summary>
/// <param name="id"></param>
/// <param name="password"></param>
/// <param name="identity"></param>
/// <returns>����˺�����ƥ�䣬������</returns>
bool LogIn(char* id, char* password, char* identity)
{
	
	sprintf_s(mycmd, 1024,
		"SELECT id FROM restaurantdatabase.%s "
		"WHERE id = \"%s\" AND password = \"%s\" ",
		identity, id, password);
	//�����û�Id�������Ƿ���ȷ
	if (1 == mysql_num_rows(ExecuteQurey(mycmd)))
	{
		CloseMysql();
		return true;
	}
	else
	{
		CloseMysql();
		return false;
	}
}

/// <summary>
/// ����һ��boolֵ������ñ��Ƿ����
/// </summary>
/// <param name="tablename">����</param>
/// <returns></returns>
bool JugdeTableExist(char* tablename,char* schema)
{
	sprintf_s(mycmd, 1024, "select * from "
		"information_schema.tables where table_schema='%s'" 
		"and table_name = '%s';" ,
		schema,tablename);
	printf("%s", mycmd);
	if (0 == mysql_num_rows(ExecuteQurey(mycmd)))
	{
		CloseMysql();
		return false;
	}
	else
	{
		CloseMysql();
		return true;
	}
}

/// <summary>
/// �����û�ע��
/// </summary>
/// <param name="id">�û�ID</param>
/// <param name="adminname">�û�����</param>
/// <param name="password">����</param>
/// <param name="restname">�͹�����</param>
/// <param name="email">����</param>
void RegisterAdmin(char* id, char* adminname, char* password, char* restname, char* email)
{
	sprintf_s(mycmd, 1024,
		"INSERT INTO restaurantdatabase.admin"
		"(id,adminname,password,restname,email)"
		"VALUES(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",
		id, adminname, password, restname, email);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// Ϊ�͹ݴ���һ���Բ͹���Ϊ���ı�
/// </summary>
/// <param name="restName">�͹���</param>
void CreateRestDishTable(char* restName)
{
	sprintf_s(mycmd, 1024,
		"CREATE TABLE `restaurantdatabase`.`%s` ("
		"`dishid` INT NOT NULL AUTO_INCREMENT,"
		"`dishname` VARCHAR(45) CHARACTER SET 'gbk' NOT NULL,"
		"`togethers` VARCHAR(45) NULL,"
		"`taste` VARCHAR(45) NULL,"
		"`price` INT NOT NULL,"
		"`soldout` INT NOT NULL DEFAULT 0,"
		"`rest` INT NOT NULL,"
		"`score` FLOAT  NULL,"
		"`create_time` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,"
		"PRIMARY KEY (`dishid`))"
		"ENGINE = InnoDB "
		"DEFAULT CHARACTER SET = gbk",
		restName);
	ExecuteUpdate(mycmd);
	printf("%s���˵���ɹ�\n", restName);
	CloseMysql();
	
}

/// <summary>
/// �ڹ���Ա��¼ʱ�������Ա����Ϣ
/// </summary>
/// <param name="id"></param>
void GetAdminInformation(char* id)
{
	sprintf_s(mycmd, 1024,
		"Select * From restaurantdatabase.admin WHERE id = '%s'", id);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	MYSQL_ROW row = mysql_fetch_row(res);
	admin.id = row[0];
	admin.name = row[1];
	admin.password = row[2];
	admin.restname = row[3];
	admin.emali = row[4];
	printf("\n�ѻ���û���Ϣ\n");
	printf("%s\n%s\n%s\n%s\n%s\n\n", admin.id, admin.name, admin.password, admin.restname, admin.emali);
	CloseMysql();
}

/// <summary>
/// ��Mysql�д���һ�Ų͹ݵ����۱�
/// </summary>
/// <param name="restname"></param>
void CreateOrderList(char* restname)
{
	sprintf_s(mycmd, 1024,
		"CREATE TABLE `restorderlist`.`%s���۵�` ("
		"`orderid` VARCHAR(45) NOT NULL,"
		"`userid` VARCHAR(45) NULL,"
		"`dishname` VARCHAR(45) NULL,"
		"`score` FLOAT NULL,"
		"`comment` VARCHAR(45) NULL,"
		"`create_time` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,"
		"PRIMARY KEY (`orderid`))"
		"ENGINE = InnoDB "
		"DEFAULT CHARACTER SET = gbk;",
		restname);
	ExecuteUpdate(mycmd);
	printf("%s�����۱�ɹ�\n", restname);
	CloseMysql();
}

/// <summary>
/// �ڲ͹ݱ������һ���͹ݵ���Ϣ
/// </summary>
/// <param name="restInfo"></param>
void RegisterRest(RestInfo restInfo)
{

	sprintf_s(mycmd, 1024,
		"INSERT INTO `restaurantdatabase`.`restinfo` "
		"( `restname`, `startprice`, `sendprice`, `blocks`,  `opentime`, `endtime`) "
		"VALUES "
		"( '%s', '%f', '%f', '%s',  '%d:%d', '%d:%d');",
		restInfo.restname, restInfo.startprice, restInfo.sendprice, 
		restInfo.block, restInfo.startHour, restInfo.startMin,
		restInfo.endHour,restInfo.endMin);
	ExecuteUpdate(mycmd);
	CloseMysql();
}


/*****************************************************/
/*********************��*��*��*��**********************/
/*****************************************************/

/// <summary>
/// ���û����в����û��û�ע����Ϣ
/// </summary>
/// <param name="id"></param>
/// <param name="username"></param>
/// <param name="password"></param>
/// <param name="sex"></param>
/// <param name="phonenum"></param>
/// <param name="email"></param>
/// <param name="adress"></param>
/// <param name="block"></param>
void RegisterUser(char* id, char* username, char* password, char* sex, char* phonenum, char* email,char* adress, char* block)
{
	sprintf_s(mycmd, 1024,
		"INSERT INTO `restaurantdatabase`.`user`"
		"(`id`, `username`, `password`, `sex`, `phonenumber`, `email`, `adress`, `block`)"
		"VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",
		id, username, password, sex, phonenum, email, adress, block);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ����һ���û�������
/// </summary>
/// <param name="userid"></param>
void CreateUserTable(char* userid)
{
	sprintf_s(mycmd, 1024,
		"CREATE TABLE `userorderlist`.`%s` ("
			"`orderid` VARCHAR(45) NOT NULL,"
			"`dishname` VARCHAR(45) NULL DEFAULT NULL,"
			"`restname` VARCHAR(45) NULL DEFAULT NULL,"
			"`score` VARCHAR(45) NULL DEFAULT NULL,"
			"`price` FLOAT NULL DEFAULT NULL,"
			"  `ispaied` INT NULL DEFAULT NULL,"
			" `comment` VARCHAR(45) NULL DEFAULT NULL,"
			"`create_time` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,"
			"PRIMARY KEY (`orderid`)) "
			"ENGINE = InnoDB "
			"DEFAULT CHARACTER SET = gbk;",
		userid);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���û��Ķ������в��붩����Ϣ
/// </summary>
/// <param name="id"></param>
/// <param name="dishname"></param>
/// <param name="restname"></param>
/// <param name="price"></param>
/// <param name="ispaid"></param>
/// <param name="orderid"></param>
void AddUserOrder(char*id,char* dishname, char* restname, float price, int ispaid,char* orderid)
{
	sprintf_s(mycmd,1024,
		"INSERT INTO `userorderlist`.`%s` "
		"(`orderid`, `dishname`, `restname`, `price`, `ispaied`) "
		"VALUES "
		"('%s', '%s', '%s', '%f', '%d');",
		id,orderid, dishname, restname, price, ispaid);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ��õ�ǰʱ��
/// </summary>
/// <returns></returns>
char* GetNowTime()
{
	time_t aclock;
	char* tmpbuf = (char*)malloc(sizeof(char) * 500);
	time(&aclock);
	strftime(tmpbuf, 15, "%Y%m%d%H%M%S", localtime(&aclock));

	return tmpbuf;
}

/// <summary>
/// ���ɶ�����ŵ�ǰʱ�䣨��ȷ���룩+�����λ��
/// </summary>
/// <returns></returns>
char* GenerateOrderId()
{
	srand((unsigned)time(NULL));
	int nrand = 1000 + rand() % 9000;
	char* id = (char*)malloc(sizeof(char) * 500);
	sprintf_s(id, 500,"%s%d", GetNowTime(), nrand);
	return id;

}


/// <summary>
/// ɾ���û�������
/// </summary>
/// <param name="userid"></param>
/// <param name="orderId"></param>
void DeleteOrder(char* userid, char* orderId)
{
	sprintf_s(mycmd, 1024, "DELETE FROM `userorderlist`.`%s` WHERE (`orderid` = '%s');", userid, orderId);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���빺�ﳵ��Ϣ
/// </summary>
/// <param name="userid"></param>
/// <param name="orderid"></param>
void BuyChartOrder(char* userid,char* orderid)
{
	sprintf_s(mycmd, 1024, 
		"UPDATE `userorderlist`.`%s` SET `ispaied` = '1' WHERE(`orderid` = '%s');", 
		userid, orderid);
	ExecuteUpdate(mycmd);
	CloseMysql();
	
}

/// <summary>
/// �����û�������Ϣ
/// </summary>
/// <param name="userid"></param>
/// <param name="username"></param>
/// <param name="sex"></param>
/// <param name="phonenumber"></param>
/// <param name="email"></param>
/// <param name="adress"></param>
/// <param name="block"></param>
void UpdateUserInfo(char* userid,char* username, char* sex, 
	char* phonenumber, char* email, char* adress,char* block)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restaurantdatabase`.`user` "
		"SET `username` = '%s', `sex` = '%s', `phonenumber` = '%s', "
		"`email` = '%s', `adress` = '%s', `block` = '%s' "
		"WHERE (`id` = '%s');",
		username, sex, phonenumber, email, adress, block, userid);
	ExecuteUpdate(mycmd);
	CloseMysql();
}




/*****************************************************/
/*********************��*Ʒ*��*��**********************/
/*****************************************************/
typedef struct _Dish
{
	char* dishname;	//��Ʒ����
	char* togethers;//��Ʒԭ��
	char* taste;	//��Ʒ��ζ
	float price;		//��Ʒ�۸�
	int soldout;	//����
	int rest;
	float score;//ʣ��	
	char* dishpath;
}Dish;

Dish dish;



/// <summary>
/// �����۱��в���һ��
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
/// <param name="comment"></param>
void AddDishComment(char* dishname, char* restname, char* comment)
{	
	sprintf_s(mycmd, 1024,
		"INSERT INTO `dishcomment`.`%scommentof%s` (`comment`) VALUES('%s');"
		, dishname, restname, comment);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���²�Ʒ����
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
/// <param name="comment"></param>
void UpdateDishComment(char* dishname, char* restname, char* comment)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `dishcomment`.`%scommentof%s` "
		"SET `comment` = '%s' "
		"WHERE (`comment` = '%s');"
		, dishname, restname, comment, comment);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// �����û����֣��������û����ֺ��Ʒ������
/// </summary>
/// <param name="score"></param>
/// <param name="dishname"></param>
/// <param name="restname"></param>
/// <returns></returns>
float GetAvgScore(int score, char* dishname, char* restname)
{
	sprintf_s(mycmd, 1024,
		"SELECT * FROM `restaurantdatabase`.`%s` WHERE dishname = '%s'",
		 restname,dishname);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	MYSQL_ROW row = mysql_fetch_row(res);
	float sellot = row[5]? atof(row[5]) : 0;
	float originscore = row[7] ? atof(row[7]) : 0;


	mysql_free_result(res);
	CloseMysql();

	return (originscore * sellot + (float)score) / (sellot + 1);
}

/// <summary>
/// �ı�������еĵĲ�Ʒ����
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
/// <param name="score"></param>
void UpdateDishScoreInRest(char* dishname, char* restname,int score)
{
	float Score = GetAvgScore(score, dishname, restname);
	sprintf_s(mycmd, 1024,
		"UPDATE `restaurantdatabase`.`%s` SET `score` = '%.2f' WHERE `dishname` = '%s';",
		restname, Score, dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// �ı��ܲ˵����еĲ�Ʒ����
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
/// <param name="score"></param>
void UpdateDishScoreInTotal(char* dishname, char* restname, int score)
{
	float Score = GetAvgScore(score, dishname, restname);
	sprintf_s(mycmd, 300,
		"UPDATE `restaurantdatabase`.`totaldish` SET `score` = '%.2lf' "
		"WHERE (`dishname` = '%s' AND `restname` = '%s');",
		Score, dishname, restname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// �����û����۱�
/// </summary>
/// <param name="userid"></param>
/// <param name="orderid"></param>
/// <param name="comment"></param>
/// <param name="score"></param>
void UpdateOrderCommentUser(char* userid,char* orderid, char* comment, int score)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `userorderlist`.`%s` SET `score` = '%.2f', `comment` = '%s' WHERE(`orderid` = '%s');",
		userid, (float)score, comment, orderid);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���²͹ݶ���������
/// </summary>
/// <param name="restname"></param>
/// <param name="orderid"></param>
/// <param name="score"></param>
/// <param name="comment"></param>
void UpdateCommentOfRestOrderList(char* restname, char* orderid, int score, char* comment)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restorderlist`.`%s���۵�` SET `score` = '%d', `comment` = '%s' WHERE (`orderid` = '%s');",
		restname, (int)score, comment, orderid);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���²͹ݵ��۳���
/// </summary>
/// <param name="restname"></param>
/// <param name="soldout"></param>
/// <param name="dishname"></param>
void UpdateSoldNumOfRestOrder(char* restname, int soldout,char* dishname)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restaurantdatabase`.`%s` SET `soldout` = '%d'" 
		"WHERE (`dishname` = '%s');",
		restname, soldout,dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// �����ܲ˵��е���Ϣ
/// </summary>
/// <param name="restname"></param>
/// <param name="soldout"></param>
/// <param name="dishname"></param>
void UpdateSoldNumOfTotalDish(char* restname, int soldout, char* dishname)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restaurantdatabase`.`totaldish` SET `sold` = '%d' "
		"WHERE (`dishname` = '%s') AND (`restname` = '%s') ;",
		soldout, restname, dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���ز�Ʒ���۳���
/// </summary>
/// <param name="restname"></param>
/// <param name="dishname"></param>
/// <returns></returns>
int GetSoldOutOfRestOrder(char* restname, char* dishname)
{
	sprintf_s(mycmd, 1024,
		"SELECT * FROM `restaurantdatabase`.`%s` WHERE dishname = '%s'",
		restname, dishname);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	MYSQL_ROW row = mysql_fetch_row(res);
	int soldout = row[5] ? atoi(row[5]) : 0;


	mysql_free_result(res);
	CloseMysql();

	return soldout;
}

/// <summary>
/// ��ȡ��Ʒ��ʣ����
/// </summary>
/// <param name="restname"></param>
/// <param name="dishname"></param>
/// <returns></returns>
int GetRestNumOfRestorder(char* restname, char* dishname)
{

	sprintf_s(mycmd, 1024,
		"SELECT * FROM `restaurantdatabase`.`%s` WHERE dishname = '%s'",
		restname, dishname);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	MYSQL_ROW row = mysql_fetch_row(res);
	int rest = row[6] ? atoi(row[6]) : 0;


	mysql_free_result(res);
	CloseMysql();

	return rest;
}

/// <summary>
/// ���²͹ݲ˵��Ĳ�Ʒʣ��
/// </summary>
/// <param name="restname"></param>
/// <param name="rest"></param>
/// <param name="dishname"></param>
void UpdateRestNumOfRestOrder(char* restname, int rest, char* dishname)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restaurantdatabase`.`%s` SET `rest` = '%d'"
		"WHERE (`dishname` = '%s');",
		restname, rest, dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ��͹ݵĶ������м��붩��
/// </summary>
/// <param name="restname"></param>
/// <param name="orderid"></param>
/// <param name="dishname"></param>
/// <param name="userid"></param>
void AddOrderToRest(char* restname, char* orderid, char* dishname,char* userid)
{
	sprintf_s(mycmd, 1024,
		"INSERT INTO `restorderlist`.`%s���۵�` (`orderid`, `userid`, `dishname`) "
		"VALUES ('%s', '%s', '%s');",
		 restname, orderid, userid,dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ����Ʒ���Ƿ����
/// </summary>
/// <param name="dishname"></param>
/// <param name="dishtable"></param>
/// <returns></returns>
bool CheckDishName(char* dishname, char* dishtable)
{
	sprintf_s(mycmd, 1024, "SELECT dishname FROM restaurantdatabase.%s where dishname = \"%s\"", dishtable, dishname);

	if (1 == mysql_num_rows(ExecuteQurey(mycmd)))
	{
		CloseMysql();
		return true;
	}
	else
	{
		CloseMysql();
		return false;
	}
}

/// <summary>
/// ����û�����������û�г���20���ַ�
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
bool CheckCommentStrNUm(char* str)
{
	int i = 0;
	int num = 0;
	while (*(str + i) != '\0') {
		num++;
		i++;
	}
	if (num >= 20) {
		return true;
	}
	else {
		return false;
	}
}



/// <summary>
/// ���Ӳ�Ʒ
/// </summary>
/// <param name="dish">��Ʒ��Ϣ</param>
/// <param name="restName">�͹���</param>
void AddDish(Dish dish, char* restName)
{
	sprintf_s(mycmd, 1024,
		"INSERT INTO `restaurantdatabase`.`%s` "
		"(`dishname`, `togethers`, `taste`, `price`, `rest`) "
		"VALUES "
		"(\'%s\', \'%s\', \'%s\', \'%f\', \'%d\')",
		restName, dish.dishname, dish.togethers, dish.taste, dish.price, dish.rest);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ���ܲ�Ʒ���е������Ϣ
/// </summary>
/// <param name="dish"></param>
/// <param name="restName"></param>
void AddTotalDish(Dish dish, char* restName)
{
	char* local;
	sprintf_s(mycmd, 1024,
		"SELECT blocks FROM restaurantdatabase.restinfo WHERE restname = '%s';",
		restName);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	local = mysql_fetch_row(res)[0];


	
	sprintf_s(mycmd, 1024,
		"INSERT INTO `restaurantdatabase`.`totaldish`"
		"(`dishname`, `restname`, `taste`, `price`, `sold`, `local`)"
			"VALUES('%s', '%s', '%s', '%f', '%d', '%s'); ",
		 dish.dishname, restName, dish.taste, dish.price, dish.soldout,local);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ����һ����Ʒ���۱����Ʒ������
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
void CreateDichCommentTable(char* dishname, char* restname)
{
	sprintf_s(mycmd, 1024,
		"CREATE TABLE `dishcomment`.`%scommentof%s` ("
		"`comment` VARCHAR(45) NULL,"
		"`create_time` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP); ",
		dishname, restname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}


/// <summary>
/// ɾ����Ʒ
/// </summary>
/// <param name="dishname">��Ʒ��</param>
/// <param name="restname">�͹���</param>
void DeleteDish(char* dishname, char* restname)
{
	sprintf_s(mycmd, 1024, "DELETE FROM `restaurantdatabase`.`%s` WHERE(`dishname` = '%s')", restname, dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ɾ���ܲ˵����е���Ϣ
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
void DeleteTotalDish(char* dishname, char* restname)
{
	sprintf_s(mycmd, 1024, "DELETE FROM `restaurantdatabase`.`totaldish` "
		"WHERE(`dishname` = '%s' AND `restname` = '%s')", dishname, restname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// ɾ����Ʒ��Ӧ�����۱�
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
void DeleteDishCommentTable(char* dishname, char* restname)
{
	sprintf_s(mycmd, 1024, "DROP TABLE dishcomment.`%scommentof%s`;"
		, dishname,restname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}


/// <summary>
/// �޸Ĳ�Ʒ��Ϣ
/// </summary>
/// <param name="dish"></param>
/// <param name="restname"></param>
void AlterMyDish(Dish dish,char* restname)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restaurantdatabase`.`%s` "
		"SET `dishname` = '%s', `togethers` = '%s', `taste` = '%s', `price` = '%d',  `rest` = '%d' "
		"WHERE (`dishname` = '%s');",
		restname, dish.dishname, dish.togethers, dish.taste, dish.price, dish.rest,dish.dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

//�ı��ܲ˵���Ĳ�Ʒ��Ϣ
void AlterTotalMyDish(Dish dish, char* restname)
{
	sprintf_s(mycmd, 500,
		"UPDATE `restaurantdatabase`.`totaldish` "
		"SET `dishname` = '%s',  `taste` = '%s', `price` = '%f',  `sold` = '%d',  `score` = '%f'"
		"WHERE (`dishname` = '%s' AND `restname` = '%s');",
		dish.dishname,  dish.taste, dish.price, dish.soldout, dish.score,dish.dishname, restname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}