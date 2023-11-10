#pragma once

#include <QWidget>
#include "ui_ReceiveFile.h"
#include "basicwindow.h"
class ReceiveFile : public BasicWindow
{
	Q_OBJECT

public:
	ReceiveFile(QWidget *parent = nullptr);
	~ReceiveFile();

	void setMsg(QString &msgLabel);//设置信息

signals:
	void refuseFile();//拒绝接受文件
protected slots:
	void on_okBtn_clicked();
	void on_cancelBtn_clicked();
private:
	Ui::ReceiveFile ui;
};
