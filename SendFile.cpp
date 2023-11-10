#include "SendFile.h"
#include "TalkWindowShell.h"
#include "WindowManager.h"
#include <QFileDialog>
#include <QMessageBox>

SendFile::SendFile(QWidget *parent)
	: BasicWindow(parent)
	,m_filePath("")//文件路径初始为空
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时进行资源回收
	initTitleBar();
	setTitleBarTitle("", ":/Resources/MainWindow/qqlogoclassic.png");
	loadStyleSheet("SendFile");//加载样式
	this->move(100, 400);

	TalkWindowShell* talkWindowShell = WindowManager::getInstance()->getTalkWindowShell();
	connect(this, &SendFile::sendFileClicked, 
			talkWindowShell, &TalkWindowShell::updateSendTcpMsg);
}

SendFile::~SendFile()
{
}

void SendFile::on_openBtn_clicked()
{
	m_filePath = QFileDialog::getOpenFileName(
		this,
		QString::fromLocal8Bit("选择文件"),
		"../",
		QString::fromLocal8Bit("发送(*.txt);;发送( *.doc);;发送(*.html)\
			;;过滤文件(*.txt *.doc *.html);;所有文件(*.*);;")
	);
	ui.lineEdit->setText(m_filePath);
}

void SendFile::on_sendBtn_clicked()
{
	if (!m_filePath.isEmpty())
	{
		QFile file(m_filePath);
		if (file.open(QIODevice::ReadOnly))
		{
			int msgType = 2;
			QString str = file.readAll();
			
			//文件名称
			QFileInfo fileInfo(m_filePath);
			QString fileName = fileInfo.fileName();

			emit sendFileClicked(str, msgType, fileName);
			file.close();
		}
		else//文件读取失败
		{
			QMessageBox::information(this,
				QStringLiteral("提示"),
				QString::fromLocal8Bit("发送文件:%1失败！").arg(m_filePath));
			this->close();
			return;
		}

		m_filePath = "";
		this->close();
	}
}
