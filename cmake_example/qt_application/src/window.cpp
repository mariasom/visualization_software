#include "window.h"
#include <QPushButton>

Window::Window(QWidget *parent) : QWidget(parent)
{
	// nastavenie ve+lkosti okna
	 setFixedSize(100, 50);

	// vytvorenie QLablu
	m_label = new QLabel(this);
	m_label->setText("Hello World");
	m_label->show();
}