#include "qsettinguserform.h"
#include "ui_qsettinguserform.h"
#include "DataDef.h"
#include "qmainscreen.h"
#include <QMessageBox>

QSettingUserForm::QSettingUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSettingUserForm),
    pdataquery(NULL),
    strtable("user"),
    m_strexpress("")
{
    ui->setupUi(this);
    m_ptc =  QTextCodec::codecForName("UTF-8");
    InitOCX();
    InitSings();

    linstname.clear();
    linstvalues.clear();
    pdataquery = new QDatabasequery();
    pdataquery->SetTableName("/opt/Hanon/hanon");
    pdataquery->opendatabase();
    pdataquery->GetValues(strtable, linstvalues, 1);
    pdataquery->GetValues(strtable, linstname, 4);
    pdataquery->cloesdatabase();
    settableview(linstvalues, linstname);

}

QSettingUserForm::~QSettingUserForm()
{
    delete ui;
}

void QSettingUserForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#QSettingUserForm{image:url(:/images/bk/bk_net.png)}""QSettingUserForm{background-color:transparent;}");

    ui->label_usertitle->setGeometry(28,7,111,36);
    ui->label_usertitle->setText(m_ptc->toUnicode("用户设置"));
    ui->label_usertitle->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    //bt
    ui->pb_settinguser_pgup->setFlat(true);
    //ui->pb_settinguser_pgup->setFocusPolicy(Qt::NoFocus);
    ui->pb_settinguser_pgup->setGeometry(136,600,108,44);
    ui->pb_settinguser_pgup->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgup_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgup_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgup_press.png);}");
    ui->pb_settinguser_pgup->hide();

    ui->pb_settinguser_pgdn->setFlat(true);
    //ui->pb_settinguser_pgdn->setFocusPolicy(Qt::NoFocus);
    ui->pb_settinguser_pgdn->setGeometry(263,600,108,44);
    ui->pb_settinguser_pgdn->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgdn_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgdn_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgdn_press.png);}");
    ui->pb_settinguser_pgdn->hide();

    ui->pb_settinguser_change->setFlat(true);
    //ui->pb_settinguser_change->setFocusPolicy(Qt::NoFocus);
    //ui->pb_settinguser_delete->setGeometry(390,604,108,44);
    ui->pb_settinguser_change->setGeometry(60,600,108,44);
    //ui->pb_settinguser_change->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_delete_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_delete_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_delete_press.png);}");
    ui->pb_settinguser_change->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pici_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pici_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pici_press.png);}");


    ui->pb_settinguser_delete->setFlat(true);
    //ui->pb_settinguser_delete->setFocusPolicy(Qt::NoFocus);
    //ui->pb_settinguser_delete->setGeometry(390,604,108,44);
    ui->pb_settinguser_delete->setGeometry(266,600,108,44);
    ui->pb_settinguser_delete->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_delete_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_delete_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_delete_press.png);}");

    ui->pb_settinguser_add->setFlat(true);
    //ui->pb_settinguser_add->setFocusPolicy(Qt::NoFocus);
    //ui->pb_settinguser_add->setGeometry(517,604,108,44);
    ui->pb_settinguser_add->setGeometry(493,600,108,44);
    ui->pb_settinguser_add->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_add_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_add_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_add_press.png);}");

    ui->pb_settinguser_save->setFlat(true);
    //ui->pb_settinguser_save->setFocusPolicy(Qt::NoFocus);
    //ui->pb_settinguser_save->setGeometry(644,604,108,44);
    ui->pb_settinguser_save->setGeometry(704,600,108,44);
    ui->pb_settinguser_save->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_save_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_save_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_save_press.png);}");

    //
    ui->le_settinguser_name->setGeometry(564,72,291, 35);
    ui->le_settinguser_name->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    //ui->le_settinguser_name->setEnabled(false);

    ui->le_settinguser_passwd->setGeometry(564,131,291, 35);
    ui->le_settinguser_passwd->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->le_settinguser_passwd->setEchoMode (QLineEdit::Password);
    //ui->le_settinguser_passwd->setEnabled(false);

    ui->le_settinguser_passwdcomfire->setGeometry(564,190,291, 35);
    ui->le_settinguser_passwdcomfire->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    ui->le_settinguser_passwdcomfire->setEchoMode (QLineEdit::Password);
    //ui->le_settinguser_passwdcomfire->setEnabled(false);

    ui->le_settinguser_people->setGeometry(564,249,291, 35);
    ui->le_settinguser_people->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    //ui->le_settinguser_people->hide();

    //ui->le_settinguser_time->setGeometry(564,311,287, 31);
    ui->le_settinguser_time->setGeometry(564,249,291, 35);
    ui->le_settinguser_time->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    //ui->le_settinguser_time->setEnabled(false);

    //ui->cb_settinguser_quanxian->setGeometry(564,370,287, 31);
    ui->cb_settinguser_quanxian->setGeometry(564,311,286, 30);
    ui->cb_settinguser_quanxian->setStyleSheet("QComboBox{border:1px solid gray;}"
      "QComboBox QAbstractItemView::item{height:50px;}"
      "QComboBox::down-arrow{image:url(:/images/bt/arrowdownBo.png);}"
      "QComboBox::drop-down{border:0px;}");
    ui->cb_settinguser_quanxian->setView(new QListView());

    ui->cb_settinguser_quanxian->addItem(m_ptc->toUnicode("管理员"));
    ui->cb_settinguser_quanxian->addItem(m_ptc->toUnicode("主管"));
    ui->cb_settinguser_quanxian->addItem(m_ptc->toUnicode("用户"));
    //ui->cb_settinguser_quanxian->setEnabled(false);


    //ui->le_settinguser_note->setGeometry(564,429,287, 31);
    ui->le_settinguser_note->setGeometry(564,370,291, 35);
    ui->le_settinguser_note->setStyleSheet("QLineEdit{background-color:transparent;}""QLineEdit{background-image: url(:/images/bt/ed_line_big.png);font-size:17px}");
    //ui->le_settinguser_note->setEnabled(false);

    setOCXEnable(false);
    ui->lb_settinguser_name->setGeometry(469, 73, 100, 30);
    ui->lb_settinguser_name->setText(m_ptc->toUnicode("用户名:"));
    ui->lb_settinguser_name->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    ui->lb_settinguser_passwd->setGeometry(469, 132, 100, 30);
    ui->lb_settinguser_passwd->setText(m_ptc->toUnicode("密码:"));
    ui->lb_settinguser_passwd->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settinguser_passwdcomfrie->setGeometry(469, 191, 100, 30);
    ui->lb_settinguser_passwdcomfrie->setText(m_ptc->toUnicode("确认密码:"));
    ui->lb_settinguser_passwdcomfrie->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    ui->lb_settinguser_people->setGeometry(469, 250, 100, 30);
    ui->lb_settinguser_people->setText(m_ptc->toUnicode("创建人:"));
    ui->lb_settinguser_people->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");
    ui->lb_settinguser_people->hide();

    //ui->lb_settinguser_time->setGeometry(469, 309, 100, 30);
    ui->lb_settinguser_time->setGeometry(469, 250, 100, 30);
    ui->lb_settinguser_time->setText(m_ptc->toUnicode("创建时间:"));
    ui->lb_settinguser_time->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    //ui->lb_settinguser_quanxian->setGeometry(469, 368, 100, 30);
    ui->lb_settinguser_quanxian->setGeometry(469, 309, 100, 30);
    ui->lb_settinguser_quanxian->setText(m_ptc->toUnicode("权限:"));
    ui->lb_settinguser_quanxian->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    //ui->lb_settinguser_note->setGeometry(469, 427, 100, 30);
    ui->lb_settinguser_note->setGeometry(469, 368, 100, 30);
    ui->lb_settinguser_note->setText(m_ptc->toUnicode("备注:"));
    ui->lb_settinguser_note->setStyleSheet("QLabel{background-color:transparent;font-size:17px}");

    m_ItemModel = new QStandardItemModel(this);
    m_ItemModel->setColumnCount(2);
    m_ItemModel->setRowCount(60);
    m_ItemModel->setHorizontalHeaderLabels(QStringList() /*<< m_ptc->toUnicode("默认登入") */<< m_ptc->toUnicode("用户名") << m_ptc->toUnicode("权限"));

    ui->tb_settinguser_list->setGeometry(14, 68, 388, 491);
    ui->tb_settinguser_list->setStyleSheet("QTableView::item{background-color:rgb(255,255,255)}""QTableView::item{selection-background-color:rgb(232,232,232)}");
    ui->tb_settinguser_list->verticalHeader()->hide();
    //ui->tb_pici_param->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tb_pici_param->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_settinguser_list->setFrameShape(QFrame::NoFrame);
    ui->tb_settinguser_list->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_settinguser_list->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    ui->tb_settinguser_list->setModel(m_ItemModel);
    ui->tb_settinguser_list->setSelectionBehavior(QAbstractItemView::SelectRows);
#ifdef _MIPS_LINUX_ENV_
    ui->tb_settinguser_list->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_settinguser_list->horizontalHeader()->setStretchLastSection(true);
#else
    ui->tb_settinguser_list->horizontalHeader()->setStretchLastSection(true);
    ui->tb_settinguser_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

    ReadOnlyDelegate *preadonlydelegate = new ReadOnlyDelegate(this);
    //TestDelegate *pTestDelegate = new TestDelegate(this);
    //IDDelegate *pIDdelegate = new IDDelegate(this);
    //re *preadonlydelegate = new (this);
    ui->tb_settinguser_list->setItemDelegateForColumn(0, preadonlydelegate);
    ui->tb_settinguser_list->setItemDelegateForColumn(1, preadonlydelegate);
   //ui->tb_settinguser_list->setItemDelegateForColumn(2, preadonlydelegate);
    ui->le_settinguser_time->setText(GetDate());
}

void QSettingUserForm::InitSings()
{

}

QString QSettingUserForm::GetDate()
{
    QDateTime dt = QDateTime::currentDateTime();

    return dt.toString("yyyy-MM-dd   ddd");
}

void QSettingUserForm::cleardata()
{
    ui->le_settinguser_name->clear();
    ui->le_settinguser_passwd->clear();
    ui->le_settinguser_passwdcomfire->clear();
    ui->le_settinguser_time->setText(GetDate());
    ui->le_settinguser_note->clear();
    ui->cb_settinguser_quanxian->setCurrentIndex(0);
}

int QSettingUserForm::GetUserLevel(QString strName)
{
    QString strname = "mingcheng";
    linstvalues.clear();
    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strname, strName, 8);
        pdataquery->cloesdatabase();
    }
    return linstvalues.at(4).toInt();
}

void QSettingUserForm::settableview(QStringList &strdata, QStringList &strdata1)
{
    int index = 0;
    int index1 = 0;
    int i = 0;
    int iii = 0;
    if(strdata.isEmpty() || strdata1.isEmpty())
    {
        return;
    }

    index = strdata.size();
    index1 = strdata1.size();

    while (i != index){
        QModelIndex mindex;
        mindex = m_ItemModel->index(i, 0,QModelIndex());
        m_ItemModel->setData(mindex, strdata.at(i));
        i++;
    }




    while (iii != index1){
        QModelIndex mindex;
        mindex = m_ItemModel->index(iii, 1,QModelIndex());
        if(0 == strdata1.at(iii).toInt())
        {
            m_ItemModel->setData(mindex,m_ptc->toUnicode("管理员"));
        }
        else if(1 == strdata1.at(iii).toInt())
        {
            m_ItemModel->setData(mindex,m_ptc->toUnicode("主管"));
        }
        else
        {
            m_ItemModel->setData(mindex,m_ptc->toUnicode("用户"));
        }

        iii++;
    }

    for(int ii = index; ii < 60; ii++)
    {
        QModelIndex mindex = m_ItemModel->index(ii, 0,QModelIndex());
        m_ItemModel->setData(mindex, "");
    }

    for(int iiii = index; iiii < 60; iiii++)
    {
        QModelIndex mindex = m_ItemModel->index(iiii, 1,QModelIndex());
        m_ItemModel->setData(mindex, "");
    }
}

 void QSettingUserForm::setOCXEnable(bool bFlag)
{
     ui->le_settinguser_name->setEnabled(bFlag);
     ui->le_settinguser_passwd->setEnabled(bFlag);
     ui->le_settinguser_passwdcomfire->setEnabled(bFlag);
     ui->le_settinguser_time->setEnabled(bFlag);
     ui->cb_settinguser_quanxian->setEnabled(bFlag);
     ui->le_settinguser_note->setEnabled(bFlag);
}

bool QSettingUserForm::checkUserName(QString strName)
{

   int iRow = m_ItemModel->rowCount();
   for(int i = 0; i < iRow; i++)
   {
        QString strTemp = m_ItemModel->index(i,0).data().toString();
        if(strTemp == strName)
        {
            return false;
        }
   }

    return true;
}

void QSettingUserForm::on_pb_settinguser_save_clicked()
{
    QString strName = "";
    QString strpasswd = "";
    QString strpasswdcf = "";
    QString strAddUser = "";
    QString strTime = "";
    QString strlevel ="";
    QString strnote = "";


    if((false == ui->le_settinguser_name->isEnabled()) || (false == ui->le_settinguser_passwd->isEnabled()) || (false == ui->le_settinguser_passwdcomfire->isEnabled()) || (false == ui->le_settinguser_time->isEnabled()) || (false == ui->le_settinguser_note->isEnabled()) || (false == ui->cb_settinguser_quanxian->isEnabled()))
    {
        return;
    }

    QMainScreen *p = (QMainScreen *) this->parent();
    QString str =  p->GetUserName();

    if((0 != GetUserLevel(str)))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }

    strName = ui->le_settinguser_name->text();

    if(false == checkUserName(strName))
    {
        //if(false == m_bfromChange)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户名重复"), QMessageBox::Ok);
            return;
        }
    }


    if(strName.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户名不能为空"), QMessageBox::Ok);
        return;
    }

    strpasswd = ui->le_settinguser_passwd->text();
    strpasswdcf = ui->le_settinguser_passwdcomfire->text();

    if(strpasswd.isEmpty() || strpasswdcf.isEmpty())
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("密码不能为空"), QMessageBox::Ok);
        return;
    }

    if(strpasswd != strpasswdcf)
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("密码不一致"), QMessageBox::Ok);
        return;
    }

    strTime = ui->le_settinguser_time->text();

    if(0 == ui->cb_settinguser_quanxian->currentIndex())
    {
        strlevel = "0"; //admin
    }
    else if(1 == ui->cb_settinguser_quanxian->currentIndex())
    {
        strlevel = "1"; //master
    }
    else
    {
        strlevel = "2"; //user
    }

    strnote = ui->le_settinguser_note->text();

    if(true == pdataquery->opendatabase())
    {

        if(linstvalues.size() >= 59)
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("数据超出范围"), QMessageBox::Ok);
            return;
        }

        linstname.clear();
        linstvalues.clear();

        //linstname.append(m_ptc->toUnicode("id"));
        linstname.append(m_ptc->toUnicode("mingcheng"));
        linstname.append(m_ptc->toUnicode("mima"));
        linstname.append(m_ptc->toUnicode("time"));
        linstname.append(m_ptc->toUnicode("level"));
        linstname.append(m_ptc->toUnicode("note"));
        linstname.append(m_ptc->toUnicode("image"));
        linstname.append(m_ptc->toUnicode("backimage"));
/*
        int index =  pdataquery->GetSize(strtable);
        QString strIndex = QString::number(index + 1);
        linstvalues.append(strIndex);
*/
        linstvalues.append(strName);
        linstvalues.append(strpasswd);
        linstvalues.append(strTime);
        linstvalues.append(strlevel);
        linstvalues.append(strnote);
        linstvalues.append(m_ptc->toUnicode("0"));
        linstvalues.append(m_ptc->toUnicode("1"));

        pdataquery->insert(strtable, linstname, linstvalues);

        linstname.clear();
        linstvalues.clear();
        pdataquery->GetValues(strtable, linstvalues, 1);
        pdataquery->GetValues(strtable, linstname, 4);
        pdataquery->cloesdatabase();
        settableview(linstvalues, linstname);
    }
    setOCXEnable(false);
}

void QSettingUserForm::on_pb_settinguser_add_clicked()
{
    setOCXEnable(true);
    cleardata();
}

void QSettingUserForm::on_pb_settinguser_delete_clicked()
{
    if(m_strexpress == "")
    {
        return;
    }

    QMainScreen *p = (QMainScreen *) this->parent();
    QString str =  p->GetUserName();

    if((1 == GetUserLevel(str))||(2 == GetUserLevel(str)))
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("用户权限不足"), QMessageBox::Ok);
        return;
    }

    if(m_strexpress == str)
    {
        QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("不能删除自己"), QMessageBox::Ok);
        return;
    }

    if((0 == GetUserLevel(m_strexpress))&&(0 == GetUserLevel(str)))
    {
        if(m_strexpress == "admin")
        {
            QMessageBox::warning(this, m_ptc->toUnicode(""), m_ptc->toUnicode("不能删除admin"), QMessageBox::Ok);
            return;
        }
    }

    if(true == pdataquery->opendatabase())
    {
        QString strname = "mingcheng";
        pdataquery->del(strtable,strname, m_strexpress);
        linstname.clear();
        linstvalues.clear();
        pdataquery->GetValues(strtable, linstvalues, 1);
        pdataquery->GetValues(strtable, linstname, 4);
        pdataquery->cloesdatabase();
        settableview(linstvalues, linstname);
    }
    cleardata();
}

void QSettingUserForm::on_tb_settinguser_list_doubleClicked(const QModelIndex &index)
{
/*
    m_strexpress =  m_ItemModel->index(index.row(),0).data().toString();

    if(m_strexpress == "")
    {
        return;
    }
    QString strname = "mingcheng";
    linstvalues.clear();

    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetoneValues(strtable, linstvalues, strname, m_strexpress, 8);
        pdataquery->cloesdatabase();
    }

    ui->le_settinguser_name->setText(linstvalues.at(1));
    ui->le_settinguser_passwd->setText(linstvalues.at(2));
    ui->le_settinguser_passwdcomfire->setText(linstvalues.at(2));
    ui->le_settinguser_time->setText(linstvalues.at(3));
    ui->le_settinguser_note->setText(linstvalues.at(5));
    ui->cb_settinguser_quanxian->setCurrentIndex(linstvalues.at(4).toInt());
    setOCXEnable(true);
    */
}

void QSettingUserForm::on_tb_settinguser_list_clicked(const QModelIndex &index)
{

   m_strexpress =  m_ItemModel->index(index.row(),0).data().toString();

   if(m_strexpress == "")
   {
       cleardata();
       return;
   }
   QString strname = "mingcheng";
   linstvalues.clear();

   if(true == pdataquery->opendatabase())
   {
       pdataquery->GetoneValues(strtable, linstvalues, strname, m_strexpress, 8);
       pdataquery->cloesdatabase();
   }

   m_bfromChange = false;
   ui->le_settinguser_name->setText(linstvalues.at(1));
   ui->le_settinguser_passwd->setText(linstvalues.at(2));
   ui->le_settinguser_passwdcomfire->setText(linstvalues.at(2));
   ui->le_settinguser_time->setText(linstvalues.at(3));
   ui->le_settinguser_note->setText(linstvalues.at(5));
   ui->cb_settinguser_quanxian->setCurrentIndex(linstvalues.at(4).toInt());

}

void QSettingUserForm::on_pb_settinguser_change_clicked()
{
    if(m_strexpress == "")
    {
        cleardata();
        setOCXEnable(false);
        m_bfromChange = false;
        return;
    }
    setOCXEnable(true);
    m_bfromChange = true;
}