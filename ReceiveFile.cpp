#include "ReceiveFile.h"
#include <qfiledialog.h>
#include <qmessagebox.h>

extern QString gfileName;
extern QString gfileData;

ReceiveFile::ReceiveFile(QWidget *parent):BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时进行资源回收
	initTitleBar();
	setTitleBarTitle("", ":/Resources/MainWindow/qqlogoclassic.png");
	loadStyleSheet("ReceiveFile");//加载样式
	this->move(100, 400);
	connect(_titleBar,&TitleBar::signalButtonCloseClicked,this, &ReceiveFile::refuseFile);

}

ReceiveFile::~ReceiveFile()
{}

void ReceiveFile::setMsg(QString & msgLabel)
{
	ui.label->setText(msgLabel);
}

void ReceiveFile::on_okBtn_clicked()
{
	this->close();
	//获取要保存的文件目录
	QString filenamePath = QFileDialog::getExistingDirectory(//获取存在的路径
		nullptr,
		QStringLiteral("文件保存路径"),
		"../"
	);
	QString filePath = filenamePath + "/" + gfileName;
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::information(nullptr,
			QStringLiteral("提示"),
			QStringLiteral("保存文件失败!"));
		//return;
	}
	else
	{
		file.write(gfileData.toUtf8());
		file.close();
		QMessageBox::information(nullptr,
			QStringLiteral("提示"),
			QStringLiteral("保存文件成功!"));
	}
}

void ReceiveFile::on_cancelBtn_clicked()
{
	emit refuseFile();
	this->close();
}
