﻿#pragma once

#include "BasicWindow.h"
#include "ui_UserLogin.h"

class UserLogin : public BasicWindow
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = Q_NULLPTR);
	~UserLogin();

private slots:
	void onLoginBtnClicked();

private:
	void initControl();
	bool connectMySql();
	bool veryfyAccountCode(bool &isAccountLogin,QString &strAccount);

private:
	Ui::UserLoginClass ui;
};
