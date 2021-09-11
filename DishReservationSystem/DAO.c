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


//定义管理员信息结构体
typedef struct _Admin
{
	char* id;
	char* password;
	char* name;
	char* restname;
	char* emali;

}Admin;
//定义用户信息结构体
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
//定餐馆信息结构体
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
	char* host;//主机名称
	char* user;//用户名
	char* password;//密码
	char* database;//要链接的数据库
	unsigned int port;//端口号
	char* unixSocket;
	unsigned long clientflag;
}MysqlInstance;
MysqlInstance mysqlInstance;

MYSQL mysql;


/// <summary>
/// 初始化mysqlInstance
/// </summary>
void MysqlInit()
{
	//设置mysql连接初始
	mysqlInstance.host = "127.0.0.1";
	mysqlInstance.user = "WX";
	mysqlInstance.password = "749299";
	mysqlInstance.database = "RestaurantDatabase";
	mysqlInstance.port = 3306;
	mysqlInstance.unixSocket = NULL;
	mysqlInstance.clientflag = 0;
}

/// <summary>
/// 连接mysql
/// </summary>
void ConnectMysql()
{
	MysqlInit();
	mysql_init(&mysql);//MYSQL自带c的API,分配或者初始化一个MYSQL对象

	//尝试连接mysql如果失败打印错误信息
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
	//设置字符集
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
/// 打印Mysql连接中出现的错误
/// </summary>
void ShowErrors()
{
	printf("\n/*********错误**********/\n");
	printf("%s\n", mysql_error(&mysql));
	printf("/*********错误*********/\n\n");
}

/// <summary>
	/// 关闭mysql服务
	/// </summary>
void CloseMysql()
{
	mysql_close(&mysql);
	//关闭Mysql连接
	mysql_server_end();
	//停止Mysql服务
	printf("mysql sever已关闭\n");
}

/// <summary>
	/// 向mysql发送查询操作
	/// </summary>
	/// <param name="cmd"></param>
	/// <returns>返回一个结果集</returns>
MYSQL_RES* ExecuteQurey(char* cmd)
{
	//向MYSQL发送命令
	SendMySQLCommand(cmd);
	return mysql_store_result(&mysql);//返回查询的结果集
}

/// <summary>
/// 向mysql发送增删改操作
/// </summary>
/// <param name="cmd"></param>
/// <returns>返回受影响的行数</returns>
int ExecuteUpdate(char* cmd)
{
	SendMySQLCommand(cmd);
	return mysql_affected_rows(&mysql);//返回受影响的行数
}

/// <summary>
/// 向mysql发送命令
/// </summary>
/// <param name="cmd">传入命令</param>
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
/*********************管*理*员*管*理*******************/
/*****************************************************/

/// <summary>
/// 在用户登录时储存用户的信息
/// </summary>
/// <param name="id"></param>
void GetUserInformation(char* id)
{
	
	sprintf_s(mycmd, 1024,
		"Select * From restaurantdatabase.user WHERE id = '%s'", id);
	MYSQL_RES* res = ExecuteQurey(mycmd);
	MYSQL_ROW row = mysql_fetch_row(res);

	//储存信息到用户结构体中
	user.id = id;
	user.name = row[1];
	user.password = row[2];
	user.sex = row[3];
	user.phonenum = row[4];
	user.emali = row[5];
	user.adreess = row[6];
	user.block = row[7];


	printf("\n已获得用户信息\n");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
		user.id, user.name, user.password, user.sex, 
		user.phonenum,user.emali, user.adreess, user.block);

	CloseMysql();
}

/// <summary>
	/// 检查用户注册ID是否重复
	/// </summary>
	/// <param name="id">要注册的id</param>
	/// <param name="user">身份</param>
	/// <returns>如果重复，返回真</returns>
bool CheckID(char* id, char* user)
{
	
	sprintf_s(mycmd, 1024, "SELECT id FROM restaurantdatabase.%s where id = \"%s\"", user, id);

	//判断是否id存在
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
/// 检查用户密码，账户是否对应
/// </summary>
/// <param name="id"></param>
/// <param name="password"></param>
/// <param name="identity"></param>
/// <returns>如果账号密码匹配，返回真</returns>
bool LogIn(char* id, char* password, char* identity)
{
	
	sprintf_s(mycmd, 1024,
		"SELECT id FROM restaurantdatabase.%s "
		"WHERE id = \"%s\" AND password = \"%s\" ",
		identity, id, password);
	//核验用户Id与密码是否正确
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
/// 返回一个bool值，代表该表是否存在
/// </summary>
/// <param name="tablename">表名</param>
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
/// 进行用户注册
/// </summary>
/// <param name="id">用户ID</param>
/// <param name="adminname">用户姓名</param>
/// <param name="password">密码</param>
/// <param name="restname">餐馆名称</param>
/// <param name="email">邮箱</param>
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
/// 为餐馆创建一个以餐馆名为名的表
/// </summary>
/// <param name="restName">餐馆名</param>
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
	printf("%s建菜单表成功\n", restName);
	CloseMysql();
	
}

/// <summary>
/// 在管理员登录时储存管理员的信息
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
	printf("\n已获得用户信息\n");
	printf("%s\n%s\n%s\n%s\n%s\n\n", admin.id, admin.name, admin.password, admin.restname, admin.emali);
	CloseMysql();
}

/// <summary>
/// 在Mysql中创建一张餐馆的销售表
/// </summary>
/// <param name="restname"></param>
void CreateOrderList(char* restname)
{
	sprintf_s(mycmd, 1024,
		"CREATE TABLE `restorderlist`.`%s销售单` ("
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
	printf("%s建销售表成功\n", restname);
	CloseMysql();
}

/// <summary>
/// 在餐馆表中添加一个餐馆的信息
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
/*********************用*户*管*理**********************/
/*****************************************************/

/// <summary>
/// 向用户表中插入用户用户注册信息
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
/// 创建一个用户订单表
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
/// 向用户的订单表中插入订单信息
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
/// 获得当前时间
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
/// 生成订单编号当前时间（精确到秒）+随机四位数
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
/// 删除用户订单表
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
/// 插入购物车信息
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
/// 更新用户个人信息
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
/*********************菜*品*管*理**********************/
/*****************************************************/
typedef struct _Dish
{
	char* dishname;	//菜品名称
	char* togethers;//菜品原料
	char* taste;	//菜品口味
	float price;		//菜品价格
	int soldout;	//已售
	int rest;
	float score;//剩余	
	char* dishpath;
}Dish;

Dish dish;



/// <summary>
/// 向评论表中插入一个
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
/// 更新菜品评论
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
/// 输入用户评分，获得添加用户评分后菜品的评分
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
/// 改变餐厅表中的的菜品评分
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
/// 改变总菜单表中的菜品评分
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
/// 更新用户评论表
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
/// 更新餐馆订单的评论
/// </summary>
/// <param name="restname"></param>
/// <param name="orderid"></param>
/// <param name="score"></param>
/// <param name="comment"></param>
void UpdateCommentOfRestOrderList(char* restname, char* orderid, int score, char* comment)
{
	sprintf_s(mycmd, 1024,
		"UPDATE `restorderlist`.`%s销售单` SET `score` = '%d', `comment` = '%s' WHERE (`orderid` = '%s');",
		restname, (int)score, comment, orderid);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// 更新餐馆的售出数
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
/// 更新总菜单中的信息
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
/// 返回菜品的售出量
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
/// 获取菜品的剩余量
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
/// 更新餐馆菜单的菜品剩余
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
/// 向餐馆的订单表中加入订单
/// </summary>
/// <param name="restname"></param>
/// <param name="orderid"></param>
/// <param name="dishname"></param>
/// <param name="userid"></param>
void AddOrderToRest(char* restname, char* orderid, char* dishname,char* userid)
{
	sprintf_s(mycmd, 1024,
		"INSERT INTO `restorderlist`.`%s销售单` (`orderid`, `userid`, `dishname`) "
		"VALUES ('%s', '%s', '%s');",
		 restname, orderid, userid,dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// 检查菜品名是否存在
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
/// 检查用户输入评论有没有超过20个字符
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
/// 增加菜品
/// </summary>
/// <param name="dish">菜品信息</param>
/// <param name="restName">餐馆名</param>
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
/// 向总菜品表中的添加信息
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
/// 创建一个菜品评论表储存菜品的评论
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
/// 删除菜品
/// </summary>
/// <param name="dishname">菜品名</param>
/// <param name="restname">餐馆名</param>
void DeleteDish(char* dishname, char* restname)
{
	sprintf_s(mycmd, 1024, "DELETE FROM `restaurantdatabase`.`%s` WHERE(`dishname` = '%s')", restname, dishname);
	ExecuteUpdate(mycmd);
	CloseMysql();
}

/// <summary>
/// 删除总菜单表中的信息
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
/// 删除菜品对应的评论表
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
/// 修改菜品信息
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

//改变总菜单表的菜品信息
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