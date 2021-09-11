#include "Final.h"
#include "Log.h"
#include "DAO.c"
#include "AdminWindow.h"
#include <QTextCodec>
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QBuffer>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>


/// <summary>
/// 用来记录订单详情
/// </summary>
QVector<QString> info;
/// <summary>
/// 将UTF8字符串转为GBK格式
/// </summary>
/// <param name="inStr"></param>
/// <returns></returns>
QString UTF82GBK(const QString& inStr)
{
    QTextCodec* gbk = QTextCodec::codecForName("GB18030");
    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");

    QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
    return utf2gbk;
}

/// <summary>
/// 把QString类型转换为char* 类型
/// </summary>
/// <param name="qstr"></param>
/// <returns></returns>
char* QstringToChar(QString qstr)
{
    qstr = UTF82GBK(qstr);
    char* chStr = NULL;
    QByteArray ba = qstr.toLocal8Bit();
    chStr = (char*)malloc(sizeof(char) * 1000);
    memset(chStr, 0, ba.length());
    memcpy(chStr, ba.data(), ba.length());
    chStr[ba.length()] = '\0';

   
    return chStr;
}

/// <summary>
/// 返回一个布尔值用来检查字符串有没有超过指定数目
/// </summary>
/// <param name="str">待检查的字符串</param>
/// <param name="n">限制字符串长度的数目</param>
/// <param name="qstrinfo">用来提示的字符串</param>
/// <returns></returns>
bool CheckStrNUm(char* str,int n, QString qstrinfo)
{
    int i = 0;
    int num = 0;
    while (*(str + i) != '\0') {
        num++;
        i++;
    }
    if (num <= n) {
        return true;
    }
    else {
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"%1输入字数超过%2个字符，\n请减少输入字符").arg(qstrinfo, 
                QString::number(n)), QMessageBox::Ok);
        return false;
    }
}

/// <summary>
/// 返回一个bool值检查用户邮箱输入是否符合格式
/// </summary>
/// <param name="qstremail">用户输入的邮箱</param>
/// <returns></returns>
bool CheckEmailInput(QString qstremail)
{
    char* email = QstringToChar(qstremail);
    int i = 0;
    int num = 0;
    int j = 0;
    int k = 0;
    printf("管理员输入注册邮箱%s\n", email);
    while (email[i] != '\0') {
        if (email[0] == '@') {
            QMessageBox::warning(NULL, QString(u8"警告"),
                QString(u8"请输入正确格式的邮箱"), QMessageBox::Ok);
            return false;
        }
        if (num == 1 && email[i] == '.') {
            j++;
        }
        if (email[i] == '@') {
            num++;
            k = i;
        }
        i++;
    }
    if (num == 1 && j == 1 && email[i - 1] != '@' && email[i - 1] != '.' && email[k + 1] != '.') {
        printf("管理员输入注册邮箱%s经经检验无误\n", email);
        return true;
    }
    else {
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"请输入正确格式的邮箱"), QMessageBox::Ok);
        return false;
    }
}

/// <summary>
///  返回一个bool值检查用户电话输入是否符合格式
/// </summary>
/// <param name="qstrPhoneNUm"></param>
/// <returns></returns>
bool checkPhoneNumInput(QString qstrPhoneNUm)
{
    char* phoneNum = QstringToChar(qstrPhoneNUm);
    int num = 0;
    int i = 0;
    printf("用户输入电话%s\n", phoneNum);
    while (phoneNum[i] != '\0') {
        if (phoneNum[i] >= '0' && phoneNum[i] <= '9') {
            num++;
        }
        else {
            QMessageBox::warning(NULL, QString(u8"警告"),
                QString(u8"请输入数字"), QMessageBox::Ok);
            return false;
        }
        i++;
    }
    if (num == 11) {
        printf("用户输入电话%s格式无误\n", phoneNum);
        return true;
    }
    if (num > 11 || num < 11) {
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"请输入11位电话"), QMessageBox::Ok);
        return false;
    }
}

/// <summary>
/// 返回一个bool值检查用户输入要注册的id是否符合格式（字母和数字混合，超过六位）
/// </summary>
/// <param name="qstrid">用户输入的id</param>
/// <returns></returns>
bool CheckIdInput(QString qstrid)
{
    char* id = QstringToChar(qstrid);
    printf("用户输入注册id%s\n", id);
    int word = 0;
    int num = 0;
    int i = 0;
    while (id[i] != '\0') {
        if (id[i] >= '0' && id[i] <= '9') {
            num++;
            i++;
        }
        else if ((id[i] >= 'a' && id[i] <= 'z') || (id[i] >= 'A' && id[i] <= 'Z')) {
            word++;
            i++;
        }
        else {
            QMessageBox::warning(NULL, QString(u8"警告"),
                QString(u8"请输入由大小写字母和数字组成的id"), QMessageBox::Ok);
            return false;
        }
    }
    if (i < 6) {
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"请输入长度不小于6位的id"), QMessageBox::Ok);
        return false;
    }
    if (i > 10) {
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"请输入长度不大于10位的id"), QMessageBox::Ok);
        return false;
    }
    if (num == 0 || word == 0) {
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"请输入由大小写字母和数字组成的id"), QMessageBox::Ok);
        return false;
    }

    printf("用户输入注册id%s经经检验无误\n", id);
    return true;
}

/// <summary>
/// 返回一个bool值用来判断一个字符串是否是整数
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
bool isInt(const char* str)
{
    bool isNum = false;

    int index = 0;
    for (; *str != '\0'; str++, index++)
    {
        switch (*str)
        {
        case '0':case'1':case'2':case'3':case'4':case'5':
        case'6':case'7':case'8':case'9':
            isNum = true;
            break;
        case '-':case '+':
            if (index != 0)
            {
                return false;
            }
            break;
        default:
            return false;
        }
    }

    if (!isNum)
    {
        return false;
    }

    return true;
}

/// <summary>
///  返回一个bool值用来判断一个字符串是否是整数，一位、两位小数
/// </summary>
/// <param name="temp"></param>
/// <returns></returns>
bool Judgenum(char temp[]) {
    int i = 0, j = 0, num = 0;
    if (temp[0] == '.') {
        return false;
    }
    while (temp[i] != '\0') {
        if (temp[i] == '.' || (temp[i] <= '9' && temp[i] >= '0')) {
            if (temp[i] == '.') {
                j = i;
                num++;
            }

        }
        else {
            return false;
        }
        i++;
    }
    if (((i - j) <= 3 && num <= 1 && i - j > 1) || num == 0) {
        return true;
    }
    else {
        return false;
    }
}







int main(int argc, char *argv[])
{
    printf("你好a\n");    
    QApplication a(argc, argv);

    Log log;
    log.show();
    
    return a.exec();
 
}




/*---------------------------登录窗口--------------------------------*/
/// <summary>
/// 登录按钮点击事件
/// </summary>
void Log::on_logButton_clicked()
{
    int index = ui.comboBox->currentIndex();//获取当前combox的的值来确定用户选择登陆身份

    if (Log::CheckInput())//首先检查输入是否正确
    {
        switch (index)//依据用户选择，在数据库对应的表中核对用户账户ID密码
        {
        case 0:
            user.id = QstringToChar(ui.idline->text());
            user.password = QstringToChar(ui.passwordline->text());
            if (LogIn(user.id, user.password, "user"))
            {
                printf("登陆成功");
                GetUserInformation(user.id);                
                userwindow.show();
                userwindow.ShowDishRecommend();
                this->close();
            }
            else
            {
                ui.passwordline->clear();
                ui.idline->clear();
                QMessageBox::information(NULL, QString(u8"提示"), QString(u8"密码或账户请输入错误"), QMessageBox::Ok);
            }
            break;
        case 1:
            admin.id = QstringToChar(ui.idline->text());
            admin.password = QstringToChar(ui.passwordline->text());
            if (LogIn(admin.id, admin.password,"admin"))
            {

                printf("登陆成功");
                GetAdminInformation(admin.id);
                adminWindow.show();
                adminWindow.ShowDishTable(admin.restname);
                this->close();
            }
            else
            {
                ui.passwordline->clear();
                ui.idline->clear();
                QMessageBox::information(NULL, QString(u8"提示"), QString(u8"密码或账户请输入错误"), QMessageBox::Ok);
            }
            
            break;
        }
    }
    else
    {
        return;
    }
}

/// <summary>
/// 当注册按钮被点下时触发的事件
/// </summary>
void Log::on_regButton_clicked()
{

    //提示用户选择要注册的身份
    QMessageBox messageBox(QMessageBox::NoIcon,
        QString(u8"选择身份"), QString(u8"请选择您要注册身份"),
        QMessageBox::Yes | QMessageBox::No,
        NULL);


    messageBox.button(QMessageBox::Yes)->setText(QString(u8"用户"));
    messageBox.button(QMessageBox::No)->setText(QString(u8"管理员"));
    int result = messageBox.exec();//获取到用户的选择进入到相应界面

    switch (result)
    {
    case QMessageBox::Yes:
        //展现用户注册界面
        userRegister.show();

        break;
    case QMessageBox::No:

        //展现管理员注册界面
        adminRegister.show();

        break;
    }
}
/*---------------------------登录窗口--------------------------------*/





/*---------------------------管理员注册窗口--------------------------------*/
/// <summary>
/// 管理员注册事件
/// </summary>
void  AdminRegister::on_registerButton_clicked()
{
    printf("管理员注册已被点击\n");//用来打印日志
    if (!AdminRegister::CheckInput())//检查用户输入是否符合规定
    {
        return;
    }


    admin.id = QstringToChar(ui.id->text());
    admin.password = QstringToChar(ui.password->text());
    admin.name = QstringToChar(ui.name->text());
    admin.restname = QstringToChar(ui.restname->text());
    admin.emali = QstringToChar(ui.email->text());
    //把用户信息传入到admin的结构体中


    printf("\n注册输入\n");
    printf("%s\n%s\n%s\n%s\n%s\n",
        admin.id, admin.password, admin.name, admin.restname, admin.emali);//用来打印日志

    if (!CheckID(admin.id,"admin"))//检查用户输入的id有没有重复
    {
        printf("id未重复，注册成功!\n");
        RegisterAdmin(admin.id, admin.name, admin.password, admin.restname, admin.emali);
        char orderlistname[128];
        sprintf_s(orderlistname, 128, "%s销售表",admin.restname);

        if (!JugdeTableExist(orderlistname,"restorderlist"))//判断用户输入的餐馆是否已经注册
        {
            CreateOrderList(admin.restname);
        }


        on_clearButton_clicked();
        if (!JugdeTableExist(admin.restname, "restaurantdatabase"))//如果用户的餐馆未注册，进入此界面，填写详细信息
        {
            CreateRestDishTable(admin.restname);
            QMessageBox::warning(NULL, QString(u8"提示"), 
                QString(u8"检查到您的餐馆还未注册，请注册"), QMessageBox::Ok);
            resRegisterWindow.show();
            this->close();
            return;
        }


        QMessageBox::warning(NULL, QString(u8"提示"), QString(u8"注册成功"), QMessageBox::Ok);
        this->close();
    }
    else
    {
        printf("id重复，注册失败!\n");
        QMessageBox::warning(NULL, QString(u8"提示"),
            QString(u8"id重复，注册失败!"), QMessageBox::Ok);
    }
}
/*---------------------------管理员注册窗口--------------------------------*/




/*---------------------------用户注册窗口--------------------------------*/
/// <summary>
/// 用户注册事件
/// </summary>
void UserRegister::on_registerButton_clicked()
{
    printf("用户注册已被点击\n");

    if (!UserRegister::CheckInput())
    {
        return;
    }

    //获取用户输入，储存在结构体中
    user.id = QstringToChar(ui.id->text());
    user.password = QstringToChar(ui.password->text());
    user.phonenum = QstringToChar(ui.phonenum->text());
    user.emali = QstringToChar(ui.email->text());
    user.name = QstringToChar(ui.name->text());
    user.adreess = QstringToChar(ui.adress->currentText());
    user.sex = QstringToChar(ui.sexcombo->currentText());
    user.block = QstringToChar(ui.block->currentText());

    printf("\n用户注册输入信息\n");
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
        user.id, user.password, user.phonenum, user.emali, user.name, user.adreess, user.sex, user.block);

    if (!CheckID(user.id, "user"))//检查用户输入的id是否重复
    {
        printf("id未重复，注册成功!\n");

        //向数据库中插入用户信息并创建
        RegisterUser(user.id, user.name, user.password, user.sex, 
            user.phonenum, user.emali, user.adreess, user.block);
        CreateUserTable(user.id);

        //清楚输入信息
        on_clearButton_clicked();


        //提示注册成功
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"注册成功!"), QMessageBox::Ok);
        this->close();
    }
    else
    {
        //提示注册成功
        QMessageBox::warning(NULL, QString(u8"警告"),
            QString(u8"id重复，注册失败!"), QMessageBox::Ok);
        printf("id重复，注册失败!\n");
    }
}
/*---------------------------用户注册窗口--------------------------------*/






/*---------------------------管理员操作窗口--------------------------------*/

/// <summary>
/// 打印出管理员界面的菜单表
/// </summary>
/// <param name="dishTableName"></param>
void AdminWindow::ShowDishTable(char* dishTableName)
{
    //获取搜索框内容
    char* searchText = ui.lineEdit->text().isEmpty()  ? "." : QstringToChar(ui.lineEdit->text());

    //获取已经初始化的模型，用来设置tableview
    QStandardItemModel* modle = InitDishTable();//获取已经初始化的数据模型

    sprintf_s(mycmd, 1024, "SELECT *  From restaurantdatabase.%s"
        " WHERE dishname REGEXP '%s' %s ", dishTableName,searchText ,GetOrderWay());
    //依据用户选择创建查询语句
    //获取Mysql返回的结果集
    MYSQL_RES* res = ExecuteQurey(mycmd);
    MYSQL_ROW row;

    int b = 0;//记录目前已经插入到多少行
    while (row = mysql_fetch_row(res))//获取结果集中的每一列信息
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res);


        if (lengths == NULL)
        {
            ShowErrors();
        }
        else
        {
            for (int i = 1; i < (int)mysql_num_fields(res); i++)
            {
                
                QString str = QString::fromLocal8Bit(row[i] ? row[i] : "");
                modle->setItem(b, i - 1, new QStandardItem(str));//往modle插入每一列的信息
            }
        }

        b++;
    }


}

/// <summary>
/// 搜索按钮点击的事件
/// </summary>
void AdminWindow::on_searchButton_clicked()
{
    //依据搜索信息，打印菜品表
    ShowDishTable(admin.restname);
}

/// <summary>
/// 刷新按钮点击事件
/// </summary>
void AdminWindow::on_pushButton_clicked()
{
    int index = ui.tableState->currentIndex();
    switch (index)
    {
    case 0:
        //展示按钮控件
        ui.searchButton->show();
        ui.addButton->show();
        ui.alterButton->show();
        ui.lineEdit->show();
        ui.deleteButton->show();
        ui.comboBox->show();
        ShowDishTable(admin.restname);

        break;
    case 1:

        //隐藏按钮控件
        ui.searchButton->hide();
        ui.addButton->hide();
        ui.alterButton->hide();
        ui.lineEdit->hide();
        ui.deleteButton->hide();
        ui.comboBox->hide();
        ShowOrderList(admin.restname);
        break;
    }
}

/// <summary>
/// 展示餐厅的订单表
/// </summary>
/// <param name="orderlistname"></param>
void AdminWindow::ShowOrderList(char* orderlistname)
{


    QStandardItemModel* modle = InitOrderTable();//获取已经初始化的数据模型

    sprintf_s(mycmd, 500, "SELECT *  From restorderlist.%s销售单 ORDER BY create_time DESC",orderlistname);
    //依据用户选择创建查询语句
    MYSQL_RES* res = ExecuteQurey(mycmd);


    MYSQL_ROW row;
    int r = 0;
    while (row = mysql_fetch_row(res))
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res);


        if (lengths == NULL)
        {
            ShowErrors();
        }
        else
        {
            for (int i = 0; i < (int)mysql_num_fields(res); i++)
            {

                QString str = QString::fromLocal8Bit(row[i] ? row[i] : "暂未评价");
                modle->setItem(r, i, new QStandardItem(str));
                //向表的模型中插入数据
            }
        }

        r++;
    }

}
/*---------------------------管理员操作窗口--------------------------------*/





/*---------------------------餐馆注册窗口--------------------------------*/

/// <summary>
/// 用户餐馆注册窗口点击注册按钮触发的事件
/// </summary>
void RestRegisterWindow::on_regiButton_clicked()
{
    if (!CheckInput())//检查输入
    {
        return;
    }

    restInfo.restname = QstringToChar(ui.restname->text());
    restInfo.startprice = ui.startprice->text().toFloat();
    restInfo.sendprice = ui.sendprice->text().toFloat();
    restInfo.block = QstringToChar(ui.localBlock->currentText());
    restInfo.startHour = ui.startHour->text().toInt();
    restInfo.startMin = ui.startMin->text().toInt();
    restInfo.endHour = ui.endHour->text().toInt();
    restInfo.endMin = ui.endMin->text().toInt();

    RegisterRest(restInfo);//在数据库中插入餐厅的详细信息
    
    QMessageBox::warning(NULL, QString(u8"提示"), QString(u8"注册成功"), QMessageBox::Ok);
    on_clearButton_clicked();
    this->close();

    return;

}

/// <summary>
/// 检查用户输入的字符串是否超过字数限制
/// </summary>
/// <param name="qstrname">要检测的字符串</param>
/// <param name="n">限制字符字数</param>
/// <param name="qstrinfo">提示信息</param>
/// <returns>如果未超过就返回真</returns>
bool RestRegisterWindow::CheckName(QString qstrname, int n, QString qstrinfo)
{
    char* str = QstringToChar(qstrname);
    //检查字符输入是否超过限制
    if (CheckStrNUm(str, n, qstrinfo))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// <summary>
/// 检查输入字符串是否是整数
/// </summary>
/// <param name="input">输入的字符串</param>
/// <param name="tipinfo">提示信息</param>
/// <returns>如果字符串是纯整数就返回真</returns>
bool RestRegisterWindow::CheckInputIsInt(QString input, QString tipinfo)
{
    char* ch = QstringToChar(input);
    //检查输入是否是整数
    if (isInt(ch))
    {
        return true;
    }
    QMessageBox::warning(NULL, QString(u8"警告"),
        QString(u8"%1请输入整数！").arg(tipinfo), QMessageBox::Ok);
    return false;
}
/*---------------------------餐馆注册窗口--------------------------------*/






/*---------------------------修改菜品窗口--------------------------------*/

/// <summary>
/// 点击修改按钮触发的事件
/// </summary>
void AlterDish::on_alterButton_clicked()
{
    printf("修改按钮已被点击\n");//打印日志

    if (!CheckInput())//检查输入
    {
        return;
    }

    dish.dishname = QstringToChar(ui.dishname->text());
    dish.togethers = QstringToChar(ui.togethers->text());
    dish.taste = QstringToChar(ui.taste->text());
    dish.price = ui.price->text().toInt();
    dish.rest = ui.restnum->text().toInt();
    
    if (CheckDishName(dish.dishname, admin.restname))//检查菜品名称
    {
        //改变数据库中的菜品信息
        AlterMyDish(dish, admin.restname);
        AlterTotalMyDish(dish, admin.restname);
        QMessageBox::warning(NULL, QString(u8"提示"), QString(u8"修改成功"), QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::warning(NULL, QString(u8"提示"), QString(u8"未找到菜品名称"), QMessageBox::Ok);
    }
}

/// <summary>
/// 检查输入字符串字符数是否超过限制
/// </summary>
/// <param name="qstrname"></param>
/// <param name="n"></param>
/// <param name="qstrinfo"></param>
/// <returns></returns>
bool AlterDish::CheckName(QString qstrname, int n, QString qstrinfo)
{
    char* str = QstringToChar(qstrname);
    //检查输入的字符数目是否超过限制
    if (CheckStrNUm(str, n, qstrinfo))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// <summary>
/// 检查输入的剩余数量是否是整数
/// </summary>
/// <param name="rest"></param>
/// <returns></returns>
bool AlterDish::CheckRestIsInt(QString  rest)
{
    char* ch = QstringToChar(rest);
    //检查输入的价格是否整数
    if (isInt(ch))
    {
        return true;
    }
    QMessageBox::warning(NULL, QString(u8"警告"),
        QString(u8"数量请输入整数！"), QMessageBox::Ok);
    return false;
}

/// <summary>
/// 检查价格是否是整数，一位、两位小数
/// </summary>
/// <param name="price"></param>
/// <returns></returns>
bool AlterDish::CheckPriceNum(QString price)
{
    char* priceCh = QstringToChar(price);
    //检查输入的价格是否是数字
    if (Judgenum(priceCh))
        return true;
    QMessageBox::warning(NULL, QString(u8"警告"),
        QString(u8"餐品价格请输入整数、一位小数、或两位小数！"), QMessageBox::Ok);
    return false;
}
/*---------------------------修改菜品窗口--------------------------------*/






/*---------------------------删除菜品窗口--------------------------------*/

/// <summary>
/// 菜品删除按钮触发的事件
/// </summary>
void DelteDish::on_deleteButton_clicked()
{
    //首先检查输入菜品名是否存在
    if (!CheckDishName(QstringToChar(ui.lineEdit->text()), admin.restname))
    {
        QMessageBox::warning(NULL, QString(u8"提示"),
            QString(u8"未找到该菜品"), QMessageBox::Ok);
        return;
    }

    QMessageBox messageBox(QMessageBox::NoIcon,
        QString(u8"删除菜品"), QString(u8"确定删除该菜品"),
        QMessageBox::Yes | QMessageBox::No,
        NULL);
    
    messageBox.button(QMessageBox::Yes)->setText(QString(u8"确定"));
    messageBox.button(QMessageBox::No)->setText(QString(u8"返回"));
    int result = messageBox.exec();
    //根据结果进入不同选择
    switch (result)
    {
    case QMessageBox::Yes:

        //删除餐馆菜单表中的该菜信息
        DeleteDish(QstringToChar(ui.lineEdit->text()), admin.restname);
        //删除总菜单表中的该菜信息
        DeleteTotalDish(QstringToChar(ui.lineEdit->text()), admin.restname);
        //删除该菜单对应的评论表
        DeleteDishCommentTable(QstringToChar(ui.lineEdit->text()), admin.restname);


        QMessageBox::information(NULL, QString(u8"提示"),
            QString(u8"该菜品删除成功"), QMessageBox::Ok);

        on_clearButton_clicked();//清除输入
        this->close();
        return;
        break;
    case QMessageBox::No:
        return;
        break;
    }

}
/*---------------------------删除菜品窗口--------------------------------*/





/*---------------------------添加菜品窗口--------------------------------*/

/// <summary>
/// 点击增加菜品按钮触发的事件
/// </summary>
void AddDishWindow::on_addButton_clicked()
{
    if (!CheckInput())//检查输入是否正确
    {
        return;
    }
    //检查菜品信息是否已存在
    if (CheckDishName(QstringToChar(ui.dishname->text()), admin.restname))
    {
        QMessageBox::warning(NULL, QString(u8"提示"),
            QString(u8"该菜品已存在"), QMessageBox::Ok);
        return;
    }
    else
    {


        
        dish.dishname = QstringToChar(ui.dishname->text());
        dish.togethers = QstringToChar(ui.togethers->text());
        dish.taste = QstringToChar(ui.taste->text());
        dish.price = ui.price->text().toInt();
        dish.rest = ui.restnum->text().toInt();

        //向数据库中加入菜品信息
        AddDish(dish, admin.restname);
        AddTotalDish(dish, admin.restname);
        CreateDichCommentTable(dish.dishname, admin.restname);

        QMessageBox::information(NULL, QString(u8"提示"),
            QString(u8"菜品添加成功"), QMessageBox::Ok);
        on_clearButton_clicked();
        this->close();
        return;
    }


}

/// <summary>
/// 检查输入字符串字符数是否超过限制
/// </summary>
/// <param name="qstrname"></param>
/// <param name="n"></param>
/// <param name="qstrinfo"></param>
/// <returns></returns>
bool AddDishWindow::CheckName(QString qstrname, int n, QString qstrinfo)
{
    char* str = QstringToChar(qstrname);
    //检查输入字符是否超过限制
    if (CheckStrNUm(str, n, qstrinfo))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// <summary>
/// 检查输入的剩余数量是否是整数
/// </summary>
/// <param name="rest"></param>
/// <returns></returns>
bool AddDishWindow::CheckRestIsInt(QString  rest)
{
    char* ch = QstringToChar(rest);
    //检查输入的剩余数量是否是数字
    if (isInt(ch))
    {
        return true;
    }
    QMessageBox::warning(NULL, QString(u8"警告"),
        QString(u8"数量请输入整数！"), QMessageBox::Ok);
    return false;
}

/// <summary>
/// 检查价格是否是整数，一位、两位小数
/// </summary>
/// <param name="price"></param>
/// <returns></returns>
bool AddDishWindow::CheckPriceNum(QString price)
{
    char* priceCh = QstringToChar(price);

    if (Judgenum(priceCh))//判断输入的是不是数字
        return true;
    //如果输入不是数字，弹出警告
    QMessageBox::warning(NULL, QString(u8"警告"),
        QString(u8"餐品价格请输入整数、一位小数、或两位小数！"), QMessageBox::Ok);
    return false;
}
/*---------------------------添加菜品窗口--------------------------------*/






/*---------------------------用户操作窗口--------------------------------*/

/// <summary>
/// 在scrollarea中打印出推荐菜品
/// </summary>
void UserWindow::ShowDishRecommend()
{
    
    QWidget* w = new QWidget(ui.scrollArea);//定义一个新的widget
    scrollW = w;
    ui.scrollArea->setWidget(scrollW);
    QGridLayout* pLayout = new QGridLayout();//实例化一个网格化窗口

    char* searchText = ui.searchline->text().isEmpty() ? "." : QstringToChar(ui.searchline->text());
    //获取搜索框的内容
    sprintf_s(mycmd, 1024, 
        "SELECT *  From restaurantdatabase.totaldish WHERE %s REGEXP '%s' %s",
        GetSearchWay(),searchText, GetOrderWay());
    //依据用户选择创建查询语句
    MYSQL_RES* res = ExecuteQurey(mycmd);//储存MYSQL返回的结果

    QVector<QPushButton*> pbns;//记录每条菜品的PushButton组件
    QVector<QString> restNames;//记录每条菜品的餐馆名称

    MYSQL_ROW row;
    int r = 0;

    //逐行读取结果集，添加菜品显示
    while (row = mysql_fetch_row(res))
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res);


        if (lengths == NULL)
        {
            ShowErrors();
        }
        else
        {
            
            
            QGridLayout* pLayout1 = new QGridLayout();//网格布局
            QGridLayout* pLayout2 = new QGridLayout();//网格布局

            //设置菜品的图片
            QLabel* dishimage = new QLabel(this);
            dishimage->setMinimumSize(QSize(120, 90));
            dishimage->setMaximumSize(QSize(120, 90));
            dishimage->setScaledContents(true);
            dishimage->setPixmap(QPixmap(QString(u8":/image/%1.jpeg").arg(QString::fromLocal8Bit(row[9] ? row[9] : ""))));

            //设置口味标签
            QLabel* taste = new QLabel(this);
            taste->setText(QString(u8"口味：%1").arg(QString::fromLocal8Bit(row[3] ? row[3] : "")));
            taste->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

            //设置菜品名标签
            QLabel* dishname = new QLabel(this);
            dishname->setText(QString(u8"菜名：%1\n价格: %2 元\n评分：%3").arg(QString::fromLocal8Bit(row[1] ? row[1] : ""),
                QString::fromLocal8Bit(row[4] ? row[4] : ""), QString::fromLocal8Bit(row[6] ? row[6] : "")));
            dishname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));
            
            //设置餐馆名标签
            QLabel* restname = new QLabel(this);
            restname->setText(QString(u8"餐馆：%1\n位于%2").arg(QString::fromLocal8Bit(row[2] ? row[2] : ""), 
                QString::fromLocal8Bit(row[7] ? row[7] : "")));
            restNames.push_back(QString::fromLocal8Bit(row[2] ? row[2] : ""));
            restname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

            /// <summary>
            /// 将这几个label垂直排列
            /// </summary>
            pLayout2->addWidget(dishname, 1, 0);
            pLayout2->addWidget(taste, 2, 0);
            pLayout2->addWidget(restname, 3, 0);

            //设计pushButton的样式
            QPushButton* pBtn = new QPushButton(QString(u8"查看详情"));
            pBtn->setObjectName(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
            pBtn->setStyleSheet(QString(u8"background-color: rgb(85, 170, 255);color: rgb(0, 0, 255); "));
            pbns.push_back(pBtn);

            //将图片，菜品信息窗口，按钮水平排列
            pLayout1->addWidget(dishimage, 0, 0);
            pLayout1->addItem(pLayout2, 0, 1);
            pLayout1->addWidget(pBtn, 0, 2);

            //将菜品信息加入到总图层中
            pLayout->addItem(pLayout1, r, 0);
            r++;
        }
    }

    //对每一个按钮设置点击触发的事件
    for (int i = 0; i < r; i++)
    {
        
        connect(pbns[i], &QPushButton::clicked, this,[=]() {
            char* dishname = QstringToChar(pbns[i]->objectName());
            char* restname = QstringToChar(restNames[i]);
            printf("在%s中的%s",restname, dishname);
            SetDishInfo(dishname,restname);
            });
    }

    ///如果没有菜品，显示信息
    if (!r)
    {
        QLabel* tip = new QLabel(this);
        tip->setText(QString(u8"没找到商品捏"));
        tip->setStyleSheet(QString(u8"color: rgb(0, 255, 255);font: 10pt \"微软雅黑\";"));

        QLabel* dishimage = new QLabel(this);
        dishimage->setMinimumSize(QSize(300, 300));
        dishimage->setMaximumSize(QSize(300, 300));
        dishimage->setScaledContents(true);
        dishimage->setPixmap(QPixmap(QString(u8":/image/charttip.jpg")));
        pLayout->addWidget(tip, 0, 0);
        pLayout->addWidget(dishimage, 1, 0);
    }

    //释放结果集，关闭MYSQL
    mysql_free_result(res);
    CloseMysql();

    pLayout->setOriginCorner(Qt::Corner::TopLeftCorner);
    //设置scrollarea的playout
    ui.scrollArea->widget()->setLayout(pLayout);
}

/// <summary>
/// 设置菜品的详细信息
/// </summary>
/// <param name="dishname">菜品名</param>
/// <param name="restname">餐馆名</param>
void UserWindow::SetDishInfo(char* dishname,char* restname)
{

    sprintf_s(mycmd, 1024,
        "SELECT *  From restaurantdatabase.%s WHERE dishname = '%s'",
        restname,dishname);
    MYSQL_RES* res = ExecuteQurey(mycmd);
    MYSQL_ROW row = mysql_fetch_row(res);
    //获取菜品信息
    sprintf_s(mycmd, 1024,
        "SELECT *  From restaurantdatabase.totaldish "
        "WHERE restname = '%s' AND dishname = '%s'",
        restname, dishname);
    MYSQL_RES* res1 = ExecuteQurey(mycmd);
    MYSQL_ROW row1 = mysql_fetch_row(res1);

    //设置标签控件的显示
    if (row && row1)
    {
        ui.dishnamelabel->setText(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
        ui.togetherslabel->setText(QString(u8"原料：%1").arg(QString::fromLocal8Bit(row[2] ? row[2] : "")));
        ui.tastelabel->setText(QString(u8"口味：%1").arg(QString::fromLocal8Bit(row[3] ? row[3] : "")));
        ui.soldoutlabel->setText(QString(u8"已售：%1").arg(QString::fromLocal8Bit(row[5] ? row[5] : "")));
        ui.pricelabel->setText(QString(u8"价格：%1").arg(QString::fromLocal8Bit(row[4] ? row[4] : "")));
        ui.priceRecord->setText(QString(u8"%1").arg(QString::fromLocal8Bit(row[4] ? row[4] : "")));
        ui.rest->setText(QString(u8"剩余：%1").arg(QString::fromLocal8Bit(row[6] ? row[6] : "")));
        ui.label->setScaledContents(true);
        ui.label->setPixmap(QPixmap(QString(u8":/image/%1.jpeg").arg(QString::fromLocal8Bit(row1[9] ? row1[9] : ""))));
        ui.restnamelabel->setText(QString::fromLocal8Bit(restname));
    }


    mysql_free_result(res);
    mysql_free_result(res1);
    CloseMysql();
    return;
}

/// <summary>
/// 触发点击购买键的事件
/// </summary>
void UserWindow::on_purChaseButton_clicked()
{    
    //判断该菜品是否还有剩余
    if (GetRestNumOfRestorder( QstringToChar(ui.restnamelabel->text()),
        QstringToChar(ui.dishnamelabel->text())) <= 0)
    {
        QMessageBox::information(NULL, QString(u8"提示"),
            QString(u8"非常抱歉，该菜品已售空!"), QMessageBox::Ok);
        return;
    }

    QMessageBox messageBox(QMessageBox::NoIcon,
        QString(u8"确认"), QString(u8"确定购买吗"),
        QMessageBox::Yes | QMessageBox::No,
        NULL);
    messageBox.button(QMessageBox::Yes)->setText(QString(u8"确定"));
    messageBox.button(QMessageBox::No)->setText(QString(u8"取消"));
    int result = messageBox.exec();

    char* dishname = QstringToChar(ui.dishnamelabel->text());
    char* restname = QstringToChar(ui.restnamelabel->text());
    float price = ui.pricelabel->text().toInt();

    switch (result)
    {
    case QMessageBox::Yes:
    {        
        QMessageBox::information(NULL, QString(u8"提示"),
        QString(u8"购买成功，即将安排配送!"), QMessageBox::Ok);
        char* orderid = GenerateOrderId();

        //向餐厅的订单表中加入订单
        AddOrderToRest(restname, orderid, dishname,user.id);
        //向用户的订单表中加入订单
        AddUserOrder(user.id, dishname, restname, price, 1,orderid);

        //获取售出数，+1
        int soldout = GetSoldOutOfRestOrder(restname,
            dishname) + 1;

        //更新餐厅表的售出数
        UpdateSoldNumOfRestOrder(restname, soldout, dishname);

        //更新总菜单表中的售出数
        UpdateSoldNumOfTotalDish(restname, soldout, dishname);


        //获取剩余数，+1
        int rest = GetRestNumOfRestorder(restname, dishname) - 1;

        //更新菜品菜单中的剩余数目
        UpdateRestNumOfRestOrder(restname, rest, dishname);

        return;
        break;
    }
        

    case QMessageBox::No:
    {
        return;
        break;
    }
        
    }


}

/// <summary>
/// 设置添加购物车按钮点击事件
/// </summary>
void UserWindow::on_addshoppingChartButton_clicked()
{
    //判断菜品是否还有剩余
    if (GetRestNumOfRestorder(QstringToChar(ui.restnamelabel->text()),
        QstringToChar(ui.dishnamelabel->text())) <= 0)
    {
        QMessageBox::information(NULL, QString(u8"提示"),
            QString(u8"非常抱歉，该菜品已售空!"), QMessageBox::Ok);
        return;
    }

    char* dishname = QstringToChar(ui.dishnamelabel->text());
    char* restname = QstringToChar(ui.restnamelabel->text());
    char* price = QstringToChar(ui.priceRecord->text());
    char* orderid = GenerateOrderId();
    //获取菜品信息

    //向用户订单表中加入信息，用0代表还未付款，处在购物车中
    AddUserOrder(user.id, dishname, restname, atof(price), 0, orderid);

    
    QMessageBox::information(NULL, QString(u8"提示"),
        QString(u8"添加购物车成功"), QMessageBox::Ok);

}

/// <summary>
/// 打印购物车的信息
/// </summary>
void UserWindow::ShowShopChart()
{
   
    QWidget* w = new QWidget(ui.shopChart);
    scrollW = w;
    ui.shopChart->setWidget(scrollW);
    QGridLayout* pLayout = new QGridLayout();
    


    sprintf_s(mycmd, 1024,
        "SELECT *  From userorderlist.%s ",
        user.id);
    //依据用户选择创建查询语句
    MYSQL_RES* res = ExecuteQurey(mycmd);

    //储存创建的控件的信息
    QVector<QPushButton*> pbns;
    QVector<QString> orderId;
    QVector<QString> restName;
    QVector<QString> dishName;
    QVector<QCheckBox*> qcbs;

    MYSQL_ROW row;
    int r = 0;
    while (row = mysql_fetch_row(res))//逐行读取数据
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res);


        if (lengths == NULL)
        {
            ShowErrors();
        }
        else
        {
            int val = atoi(row[5]);
            if (!val)
            {
                QGridLayout* pLayout1 = new QGridLayout();//网格布局
                QGridLayout* pLayout2 = new QGridLayout();//网格布局

                sprintf_s(mycmd, 1024,
                    "SELECT *  From restaurantdatabase.totaldish "
                    "WHERE restname = '%s' AND dishname = '%s'",
                     (row[2] ? row[2] : ""),
                    (row[1] ? row[1] : ""));
                MYSQL_RES* res1 = ExecuteQurey(mycmd);
                MYSQL_ROW row1 = mysql_fetch_row(res1);

                QLabel* dishimage = new QLabel(this);
                dishimage->setMinimumSize(QSize(120, 90));
                dishimage->setMaximumSize(QSize(120, 90));
                dishimage->setScaledContents(true);
                dishimage->setPixmap(QPixmap(QPixmap(QString(u8":/image/%1.jpeg").arg(QString::fromLocal8Bit(row1[9] ? row1[9] : "")))));

                mysql_free_result(res1);
                


                QLabel* orderid = new QLabel(this);
                orderid->setText(QString(u8"订单编号：%1 ").arg(QString::fromLocal8Bit(row[0] ? row[0] : "")));
                orderid->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                QLabel* price = new QLabel(this);
                price->setText(QString(u8"价格: %1元 ").arg(QString::fromLocal8Bit(row[4] ? row[4] : "")));
                price->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                QLabel* dishname = new QLabel(this);
                dishname->setText(QString(u8"菜名 %1 ").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
                dishname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));
                dishName.push_back(QString::fromLocal8Bit(row[1] ? row[1] : ""));

                QLabel* restname = new QLabel(this);
                restname->setText(QString(u8"餐馆：%1").arg(QString::fromLocal8Bit(row[2] ? row[2] : "")));
                restname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                orderId.push_back(QString::fromLocal8Bit(row[0] ? row[0] : ""));
                restName.push_back(QString::fromLocal8Bit(row[2] ? row[2] : ""));

                //设置孙子布局，竖排
                pLayout2->addWidget(orderid, 0, 0);
                pLayout2->addWidget(dishname, 1, 0);
                pLayout2->addWidget(price, 1, 1);
                pLayout2->addWidget(restname, 2, 0);

                QPushButton* pBtn = new QPushButton(QString(u8"删除订单"));
                pBtn->setObjectName(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
                pBtn->setStyleSheet(QString(u8"background-color: rgb(85, 170, 255);color: rgb(0, 0, 255); "));
                pbns.push_back(pBtn);


                QCheckBox* qcb = new QCheckBox();
                qcb->setMaximumSize(QSize(20, 20));
                qcbs.push_back(qcb);


                /// <summary>
                /// 设置子布局横向排序
                /// </summary>
                pLayout1->addWidget(qcb, 0, 0);
                pLayout1->addWidget(dishimage, 0, 1);
                pLayout1->addItem(pLayout2, 0, 2);
                pLayout1->addWidget(pBtn, 0, 3);

                //插入总体布局中
                pLayout->addItem(pLayout1, r, 0);
                r++;
            }           
        }
    }

    /// <summary>
    /// 为自动添加的按键添加点击事件
    /// </summary>
    for (int i = 0; i < r; i++)
    {
        //设置删除信息的触发事件
        connect(pbns[i], &QPushButton::clicked, this, [=]() {
            char* orderid = QstringToChar(orderId[i]);
            DeleteOrder(user.id, orderid);
            
            });

        //设置选择框状态改变的触发事件
        connect(qcbs[i], &QCheckBox::stateChanged, this, [=]() {
            int state = qcbs[i]->checkState();
            
            if (state == Qt::Checked ) // "选中"
            {
                SelectRestName.push_back(restName[i]);
                SelectorderId.push_back(orderId[i]);
            }
            if(state == Qt::Unchecked) 
            {
                SelectorderId.removeOne(restName[i]);
                SelectorderId.removeOne(orderId[i]);
            }
            });
    }

    /// <summary>
    /// 设置购物车没有东西时的画面
    /// </summary>
    if (!r)
    {
        QLabel* tip = new QLabel(this);
        tip->setText(QString(u8"这里空空如也捏，请添加商品"));
        tip->setStyleSheet(QString(u8"color: rgb(0, 255, 255);font: 10pt \"微软雅黑\";"));
        QLabel* dishimage = new QLabel(this);
        dishimage->setMinimumSize(QSize(300, 300));
        dishimage->setMaximumSize(QSize(300, 300));
        dishimage->setScaledContents(true);
        dishimage->setPixmap(QPixmap(QString(u8":/image/searchtip.jpg")));
        pLayout->addWidget(tip, 0, 0);
        pLayout->addWidget(dishimage, 1, 0);
    }

    SelectCheckBoxsAll = qcbs;
    SelectRestName = restName;
    SelectDishName = dishName;


    mysql_free_result(res);
    CloseMysql();


    pLayout->setOriginCorner(Qt::Corner::TopLeftCorner);
    ui.shopChart->widget()->setLayout(pLayout);
}

/// <summary>
/// 设置购物车购买按钮
/// </summary>
void UserWindow::on_buyChartButton_clicked()
{
   //判断是否有所选
    if (!SelectorderId.count())
    {
        QMessageBox::warning(NULL, QString(u8"提示"),
            QString(u8"请至少选择一项"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox messageBox(QMessageBox::NoIcon,
            QString(u8"确认"), QString(u8"确定购买所选吗"),
            QMessageBox::Yes | QMessageBox::No,
            NULL);
        messageBox.button(QMessageBox::Yes)->setText(QString(u8"确定"));
        messageBox.button(QMessageBox::No)->setText(QString(u8"取消"));
        //获取用户的选择
        int result = messageBox.exec();

        switch (result)
        {
        case QMessageBox::Yes:
            for (int i = 0; i < SelectorderId.size(); i++)
            {
                //向餐馆订单表中加入订单信息
                AddOrderToRest(QstringToChar(SelectRestName[i]),
                    QstringToChar(SelectorderId[i]), QstringToChar(SelectDishName[i]),user.id);

                //去除购物车中的信息
                BuyChartOrder(user.id, QstringToChar(SelectorderId[i]));

                int soldout = GetSoldOutOfRestOrder(QstringToChar(SelectRestName[i]),
                    QstringToChar(SelectDishName[i])) + 1;

                //更新菜品中的已售数
                UpdateSoldNumOfRestOrder(QstringToChar(SelectRestName[i]),soldout,
                    QstringToChar(SelectDishName[i]));

                //更新菜品的已售数
                UpdateSoldNumOfTotalDish(QstringToChar(SelectRestName[i]), soldout,
                    QstringToChar(SelectDishName[i]));

                int rest = GetRestNumOfRestorder(QstringToChar(SelectRestName[i]),
                    QstringToChar(SelectDishName[i])) - 1;

                //更新菜品的剩余数
                UpdateRestNumOfRestOrder(QstringToChar(SelectRestName[i]), rest,
                    QstringToChar(SelectDishName[i]));

            }
            QMessageBox::information(NULL, QString(u8"提示"),
                QString(u8"购买成功"), QMessageBox::Ok);
            on_refreshButton_clicked();
            return;
            break;

        case QMessageBox::No:

            return;
            break;
        }
    }

    
}

/// <summary>
/// 设置购物车删除按钮
/// </summary>
void UserWindow::on_deleteSelect_clicked()
{
    if (!SelectorderId.count())//检查用户是否有选择
    {
        QMessageBox::warning(NULL, QString(u8"提示"),
            QString(u8"请至少选择一项"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox messageBox(QMessageBox::NoIcon,
            QString(u8"确认"), QString(u8"确定全部删除吗"),
            QMessageBox::Yes | QMessageBox::No,
            NULL);

        messageBox.button(QMessageBox::Yes)->setText(QString(u8"确定"));
        messageBox.button(QMessageBox::No)->setText(QString(u8"取消"));

        int result = messageBox.exec();//获取用户选择
        QVector<QString> SelectorderMyId;
        //根据用户选择转向不同结果
        switch (result)
        {
        case QMessageBox::Yes:
            for (int i = 0; i < SelectorderId.size(); i++)
            {                
                DeleteOrder(user.id, QstringToChar(SelectorderId[i]));
            }
            //逐项删除订单中的信息

            SelectorderId = SelectorderMyId;
            QMessageBox::information(NULL, QString(u8"提示"),
                QString(u8"删除成功"), QMessageBox::Ok);
            on_refreshButton_clicked();
            return;
            break;

        case QMessageBox::No:

            return;
            break;
        }
    }

    

}

/// <summary>
/// 展示历史订单
/// </summary>
void UserWindow::ShowHistoryOrder()
{
    //创建一个新的图层
    QWidget* w = new QWidget(ui.historyOrderList);
    scrollW = w;
    ui.historyOrderList->setWidget(scrollW);
    QGridLayout* pLayout = new QGridLayout();


    sprintf_s(mycmd, 1024,
        "SELECT *  From userorderlist.%s ",
        user.id);
    //依据用户选择创建查询语句
    MYSQL_RES* res = ExecuteQurey(mycmd);

    //QVector储存添加的组件
    QVector<QPushButton*> pbns;
    QVector<QString> orderId;
    QVector<QString> restNames;
    QVector<QString> dishNames;


    MYSQL_ROW row;
    int r = 0;
    while (row = mysql_fetch_row(res))
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res);


        if (lengths == NULL)
        {
            ShowErrors();
        }
        else
        {            
            int val = atoi(row[5]);
            if (val)
            {
                if (!row[3])
                {
                    QGridLayout* pLayout1 = new QGridLayout();//网格布局
                    QGridLayout* pLayout2 = new QGridLayout();//网格布局

                    sprintf_s(mycmd, 1024,
                        "SELECT *  From restaurantdatabase.totaldish "
                        "WHERE restname = '%s' AND dishname = '%s'",
                        (row[2] ? row[2] : ""),
                        (row[1] ? row[1] : ""));
                    //获取菜品图片信息
                    MYSQL_RES* res1 = ExecuteQurey(mycmd);
                    MYSQL_ROW row1 = mysql_fetch_row(res1);

                    //创建图片标签
                    QLabel* dishimage = new QLabel(this);
                    dishimage->setMinimumSize(QSize(120, 90));
                    dishimage->setMaximumSize(QSize(120, 90));
                    dishimage->setScaledContents(true);
                    dishimage->setPixmap(QPixmap(QPixmap(QString(u8":/image/%1.jpeg").arg(QString::fromLocal8Bit(row1[9] ? row1[9] : "")))));

                    mysql_free_result(res1);//释放res

                    //打印标签内容
                    QLabel* orderid = new QLabel(this);
                    orderid->setText(QString(u8"订单编号：%1 ").arg(QString::fromLocal8Bit(row[0] ? row[0] : "")));
                    orderid->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                    QLabel* price = new QLabel(this);
                    price->setText(QString(u8"价格: %1元 ").arg(QString::fromLocal8Bit(row[4] ? row[4] : "")));
                    price->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                    QLabel* dishname = new QLabel(this);
                    dishname->setText(QString(u8"菜名：%1 ").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
                    dishname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));
                    dishNames.push_back(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));

                    QLabel* restname = new QLabel(this);
                    restname->setText(QString(u8"餐馆：%1").arg(QString::fromLocal8Bit(row[2] ? row[2] : "")));
                    restname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));


                    orderId.push_back(QString::fromLocal8Bit(row[0] ? row[0] : ""));

                    restNames.push_back(QString(u8"%1").arg(QString::fromLocal8Bit(row[2] ? row[2] : "")));

                    //设置孙子布局，竖排
                    pLayout2->addWidget(orderid, 0, 0);
                    pLayout2->addWidget(dishname, 1, 0);
                    pLayout2->addWidget(price, 1, 1);
                    pLayout2->addWidget(restname, 1, 2);

                    QPushButton* pBtn = new QPushButton(QString(u8"评价该单"));
                    pBtn->setMaximumWidth(100);
                    pBtn->setObjectName(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
                    pBtn->setStyleSheet(QString(u8"background-color: rgb(85, 170, 255);color: rgb(0, 0, 255); "));
                    pbns.push_back(pBtn);



                    /// <summary>
                    /// 设置子布局横向排序
                    /// </summary>
                    pLayout1->addWidget(dishimage, 0, 1);
                    pLayout1->addItem(pLayout2, 0, 2);
                    pLayout1->addWidget(pBtn, 0, 3);

                    //插入总体布局中
                    pLayout->addItem(pLayout1, r, 0);
                    r++;
                }
                else
                {
                    QGridLayout* pLayout1 = new QGridLayout();//网格布局
                    QGridLayout* pLayout2 = new QGridLayout();//网格布局


                    QLabel* dishimage = new QLabel(this);
                    dishimage->setMinimumSize(QSize(120, 90));
                    dishimage->setMaximumSize(QSize(120, 90));
                    dishimage->setScaledContents(true);
                    dishimage->setPixmap(QPixmap(QString(u8":/image/鱼香肉丝.jpeg")));

                    QLabel* orderid = new QLabel(this);
                    orderid->setText(QString(u8"订单编号：%1 ").arg(QString::fromLocal8Bit(row[0] ? row[0] : "")));
                    orderid->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                    QLabel* price = new QLabel(this);
                    price->setText(QString(u8"价格: %1元 ").arg(QString::fromLocal8Bit(row[4] ? row[4] : "")));
                    price->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                    QLabel* dishname = new QLabel(this);
                    dishname->setText(QString(u8"菜名：%1 ").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
                    dishname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                    dishNames.push_back(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));

                    QLabel* restname = new QLabel(this);
                    restname->setText(QString(u8"餐馆：%1").arg(QString::fromLocal8Bit(row[2] ? row[2] : "")));
                    restname->setStyleSheet(QString(u8"color: rgb(0, 255, 255);"));

                    
                    orderId.push_back(QString::fromLocal8Bit(row[0] ? row[0] : ""));

                    restNames.push_back(QString(u8"%1").arg(QString::fromLocal8Bit(row[2] ? row[2] : "")));

                    //设置孙子布局，竖排
                    pLayout2->addWidget(orderid, 0, 0);
                    pLayout2->addWidget(dishname, 1, 0);
                    pLayout2->addWidget(price, 1, 1);
                    pLayout2->addWidget(restname, 1, 2);

                    QPushButton* pBtn = new QPushButton(QString(u8"修改评价"));
                    pBtn->setMaximumWidth(100);
                    pBtn->setObjectName(QString(u8"%1").arg(QString::fromLocal8Bit(row[1] ? row[1] : "")));
                    pBtn->setStyleSheet(QString(u8"background-color: rgb(85, 170, 255);color: rgb(0, 0, 255); "));
                    pbns.push_back(pBtn);



                    /// <summary>
                    /// 设置子布局横向排序
                    /// </summary>
                    pLayout1->addWidget(dishimage, 0, 1);
                    pLayout1->addItem(pLayout2, 0, 2);
                    pLayout1->addWidget(pBtn, 0, 3);

                    //插入总体布局中
                    pLayout->addItem(pLayout1, r, 0);
                    r++;
                }
            }
            
        }
    }

    /// <summary>
    /// 为自动添加的按键添加点击事件
    /// </summary>
    for (int i = 0; i < r; i++)
    {
        if (pbns[i]->text() == QString(u8"评价该单"))
        {
            connect(pbns[i], &QPushButton::clicked, this, [=]() {

                QVector<QString> newinfo;//临时用来储存订单信息
                newinfo.push_back(dishNames[i]);
                newinfo.push_back(restNames[i]);
                newinfo.push_back(orderId[i]);
                info = newinfo;//添加到全局变量中，方便后续储存

                addComment.show();
             });
        }
        else if (pbns[i]->text() == QString(u8"修改评价"))
        {
            connect(pbns[i], &QPushButton::clicked, this, [=]() {

                QVector<QString> newinfo;//临时用来储存订单信息
                newinfo.push_back(dishNames[i]);
                newinfo.push_back(restNames[i]);
                newinfo.push_back(orderId[i]);
                info = newinfo;//添加到全局变量中，方便后续储存

                alterCommentWindow.show();
                });
        }

        
    }

    if (!r)//设置如果订单为0的显示
    {
        QLabel* tip = new QLabel(this);
        tip->setText(QString(u8"这里空空如也捏"));
        tip->setStyleSheet(QString(u8"color: rgb(0, 255, 255);font: 10pt \"微软雅黑\";"));
        QLabel* dishimage = new QLabel(this);
        dishimage->setMinimumSize(QSize(300, 300));
        dishimage->setMaximumSize(QSize(300, 300));
        dishimage->setScaledContents(true);
        dishimage->setPixmap(QPixmap(QString(u8":/image/searchtip.jpg")));
        pLayout->addWidget(tip, 0, 0);
        pLayout->addWidget(dishimage, 1, 0);
        delete(tip);
    }

    mysql_free_result(res);//释放结果集
    CloseMysql();//关闭mysql


    pLayout->setOriginCorner(Qt::Corner::TopLeftCorner);


    ui.historyOrderList->widget()->setLayout(pLayout);//输入设置的图层
}

/// <summary>
/// 设置查看评论事件
/// </summary>
void UserWindow::on_lookCommentButton_clicked()
{
    ccw.show();//打开查看评论窗口
    //打印评论
    ccw.ShowCommentTable(QstringToChar(ui.dishnamelabel->text()), 
        QstringToChar(ui.restnamelabel->text()));

}

/// <summary>
/// 打印个人信息
/// </summary>
void UserWindow::ShowPersonInfo()
{
    //设置label组件的显示
    ui.personId->setText(QString(u8"账户ID：%1").arg(QString::fromLocal8Bit(user.id)));
    ui.personname->setText(QString(u8"昵称：%1").arg(QString::fromLocal8Bit(user.name)));
    ui.personsex->setText(QString(u8"性别：%1").arg(QString::fromLocal8Bit(user.sex)));
    ui.personphonenum->setText(QString(u8"电话号码：%1").arg(QString::fromLocal8Bit(user.phonenum)));
    ui.personemail->setText(QString(u8"邮箱：%1").arg(QString::fromLocal8Bit(user.emali)));
    ui.personadress->setText(QString(u8"住址：%1%2").arg(QString::fromLocal8Bit(user.block), 
        QString::fromLocal8Bit(user.adreess)));
}
/*---------------------------用户操作窗口--------------------------------*/





/*---------------------------评论窗口--------------------------------*/

/// <summary>
/// 设置提交评论按钮触发的事件
/// </summary>
void AddComment::on_pushButton_clicked()
{
    if (!CheckInput())
    {
        return;
    }
    //像菜品评价表中添加评价
    AddDishComment(QstringToChar(info[0]),
        QstringToChar(info[1]), QstringToChar(ui.commentEdit->toPlainText()));

    //更新餐厅中的菜品分数
    UpdateDishScoreInRest(QstringToChar(info[0]),
        QstringToChar(info[1]), ui.scorecombo->currentText().toInt());

    //更新总菜单表中的分数
    UpdateDishScoreInTotal(QstringToChar(info[0]),
        QstringToChar(info[1]), ui.scorecombo->currentText().toInt());

    //更新用户订单表中的个人评论
    UpdateOrderCommentUser(user.id, QstringToChar(info[2]),
        QstringToChar(ui.commentEdit->toPlainText()), ui.scorecombo->currentText().toInt());

    //更新餐馆订单中的用户评论
    UpdateCommentOfRestOrderList(QstringToChar(info[1]), QstringToChar(info[2]),
        ui.scorecombo->currentText().toInt(), QstringToChar(ui.commentEdit->toPlainText()));

    QMessageBox::information(NULL, QString(u8"提示"),
        QString(u8"评论成功"), QMessageBox::Ok);


    on_pushButton_2_clicked();//清楚用户输入

    this->close();
}

/// <summary>
/// 检查输入的评论是否超过字数限制
/// </summary>
/// <param name="comment"></param>
/// <param name="n"></param>
/// <param name="str"></param>
/// <returns></returns>
bool AddComment::CheckCommentInput(QString comment, int n, QString str)
{
    char* ch = QstringToChar(comment);//获取输入框中的评论，转换为char*
    //检查评论输入有无超过字符限制
    if (CheckStrNUm(ch, 30, str))
        return true;
    return false;
}
/*---------------------------评论窗口--------------------------------*/




/*---------------------------修改评论窗口--------------------------------*/

/// <summary>
/// 检查输入的评论是否超过字数限制
/// </summary>
/// <param name="comment"></param>
/// <param name="n"></param>
/// <param name="str"></param>
/// <returns></returns>
bool AlterCommentWindow::CheckCommentInput(QString comment, int n, QString str)
{
    char* ch = QstringToChar(comment);//获取输入框中的评论，转换为char*
    //检查评论输入有无超过字符限制
    if (CheckStrNUm(ch, 30, str))
        return true;
    return false;
}

/// <summary>
/// 设置修改评论按钮触发的事件
/// </summary>
void AlterCommentWindow::on_pushButton_clicked()
{
    if (!CheckInput())//检出输入是否正确
    {
        return;
    }
    //更新菜品中的评论
    UpdateDishComment(QstringToChar(info[0]),
        QstringToChar(info[1]), QstringToChar(ui.commentEdit->toPlainText()));

    //更新餐厅菜单表中的评分
    UpdateDishScoreInRest(QstringToChar(info[0]),
        QstringToChar(info[1]), ui.scorecombo->currentText().toInt());
    //更新总菜单表中的菜品评分
    UpdateDishScoreInTotal(QstringToChar(info[0]),
        QstringToChar(info[1]), ui.scorecombo->currentText().toInt());

    //更新用户评论表
    UpdateOrderCommentUser(user.id, QstringToChar(info[2]),
        QstringToChar(ui.commentEdit->toPlainText()), ui.scorecombo->currentText().toInt());

    //更新餐馆订单表用户的评论
    UpdateCommentOfRestOrderList(QstringToChar(info[1]), QstringToChar(info[2]),
        ui.scorecombo->currentText().toInt(), QstringToChar(ui.commentEdit->toPlainText()));

    QMessageBox::information(NULL, QString(u8"提示"),
        QString(u8"评论成功"), QMessageBox::Ok);

    on_pushButton_2_clicked();
    //清楚用户输入
    this->close();
}
/*---------------------------修改评论窗口--------------------------------*/






/*---------------------------查看评论窗口--------------------------------*/

/// <summary>
/// 打印出评论表
/// </summary>
/// <param name="dishname"></param>
/// <param name="restname"></param>
void CheckCommentWindow::ShowCommentTable(char* dishname, char* restname)
{   
    QStandardItemModel* modle = InitDishTable();//获取已经初始化的数据模型

    sprintf_s(mycmd, 1024, "SELECT * FROM dishcomment.%scommentof%s", 
        dishname,restname);
    //依据用户选择创建查询语句
    MYSQL_RES* res = ExecuteQurey(mycmd);
    //free(cmd);

    MYSQL_ROW row;
    int r = 0;
    while (row = mysql_fetch_row(res))//逐行读取数据，直到数据为空
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res);


        if (lengths == NULL)
        {
            ShowErrors();
        }
        else
        {
            for (int i = 0; i < (int)mysql_num_fields(res); i++)
            {

                QString str = QString::fromLocal8Bit(row[i] ? row[i] : "");
                modle->setItem(r, i , new QStandardItem(str));//向模型中差入数据
            }
        }

        r++;
    }
    mysql_free_result(res);
}
/*---------------------------查看评论窗口--------------------------------*/




/*---------------------------修改个人信息窗口--------------------------------*/

/// <summary>
/// 设置点击修改个人信息触发的事件
/// </summary>
void AlterPersonInformation::on_alterbutton_clicked()
{
    if (!CheckInput())//检查输入是都符合要求
    {
        return;
    }

    //依据用户输入更新数据库中用户的信息
    UpdateUserInfo(user.id, QstringToChar(ui.name->text()), QstringToChar(ui.sexCombo->currentText()),
        QstringToChar(ui.phone->text()), QstringToChar(ui.email->text()),
        QstringToChar(ui.adressBlock->currentText()), QstringToChar(ui.blockCombo->currentText()));

    //提示用户修改成功
    QMessageBox::information(NULL, QString(u8"提示"),
        QString(u8"修改成功"), QMessageBox::Ok);

    GetUserInformation(user.id);
    //更新本地储存的用户信息

    on_clearButton_clicked();
    //刷新界面
    this->close();
}
/*---------------------------修改个人信息窗口--------------------------------*/








/*---------------------------检查输入--------------------------------*/

/// <summary>
/// 检查用户输入id格式是否正确
/// </summary>
/// <param name="qstrPhoneNUm"></param>
/// <returns></returns>
bool UserRegister::CheckUserIdInput(QString qstrid)
{
    if (CheckIdInput(qstrid))
        return true;
    return false;
}

/// <summary>
/// 检查用户输入电话号码格式是否正确
/// </summary>
/// <param name="qstrPhoneNUm"></param>
/// <returns></returns>
bool UserRegister::CheckIdPhoneNUm(QString qstrPhoneNUm)
{
    if (checkPhoneNumInput(qstrPhoneNUm))
        return true;
    return false;
}

/// <summary>
/// 检查用户输入邮箱是否符合格式
/// </summary>
/// <param name="qstremail"></param>
/// <returns></returns>
bool UserRegister::CheckEmail(QString qstremail)
{
    if (CheckEmailInput(qstremail))
        return true;
    return false;
}

/// <summary>
/// 检查用户输入id格式是否正确
/// </summary>
/// <param name="qstrPhoneNUm"></param>
/// <returns></returns>
bool AdminRegister::CheckAdminIdInput(QString qstrid)
{
    if (CheckIdInput(qstrid))
        return true;
    return false;
}

/// <summary>
/// 检查用户输入邮箱是否符合格式
/// </summary>
/// <param name="qstremail"></param>
/// <returns></returns>
bool AdminRegister::CheckEmail(QString qstremail)
{
    if (CheckEmailInput(qstremail))
        return true;
    return false;
}

/// <summary>
/// 检查用户修改个人信息时输入字符是否超过限制字数
/// </summary>
/// <param name="qstrname"></param>
/// <param name="n"></param>
/// <returns></returns>
bool AdminRegister::CheckName(QString qstrname, int n, QString qstrinfo)
{
    char* str = QstringToChar(qstrname);
    if (CheckStrNUm(str, n,qstrinfo))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/// <summary>
/// 检查用户输入电话号码格式是否正确
/// </summary>
/// <param name="qstrPhoneNUm"></param>
/// <returns></returns>
bool AlterPersonInformation::CheckIdPhoneNUm(QString qstrPhoneNUm)
{
    if (checkPhoneNumInput(qstrPhoneNUm))
        return true;
    return false;
}

/// <summary>
/// 检查用户输入邮箱是否符合格式
/// </summary>
/// <param name="qstremail"></param>
/// <returns></returns>
bool AlterPersonInformation::CheckEmail(QString qstremail)
{
    if (CheckEmailInput(qstremail))
        return true;
    return false;
}

/// <summary>
/// 检查用户修改个人信息时输入字符是否超过限制字数
/// </summary>
/// <param name="qstrname"></param>
/// <param name="n"></param>
/// <returns></returns>
bool AlterPersonInformation::CheckNameInput(QString qstrname, int n)
{
    char* str = QstringToChar(qstrname);
    if (CheckStrNUm(str, n, QString(u8"昵称")))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*---------------------------检查输入--------------------------------*/


