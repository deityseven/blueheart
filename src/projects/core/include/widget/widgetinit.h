#ifndef WIDGETINIT_H
#define WIDGETINIT_H

class WidgetInit
{
public:
	virtual void init() = 0;
	virtual void connectSignal() = 0;
};

#endif