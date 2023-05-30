#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>

class Window : public QWidget
{

public:
	explicit Window(QWidget *parent = 0);

private:
	QLabel *m_label;

};

#endif // WINDOW_H