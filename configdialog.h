#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>
#include <QAbstractButton>

namespace Ui {
	class configDialog;
}

class configDialog : public QDialog {
	Q_OBJECT
public:
	configDialog(QWidget *parent = 0);
	~configDialog();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::configDialog *m_ui;
	void SaveSettings();

private slots:
	void on_btn_NotesPath_clicked();
	void on_buttonBox_clicked(QAbstractButton* button);

signals:
	void pathChanged();
};

#endif // CONFIGDIALOG_H
