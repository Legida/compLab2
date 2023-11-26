#ifndef BUTTON_ADAPTER
#define BUTTON_ADAPTER

#include <QObject>

class QmlAdapter : public QObject
{
    Q_OBJECT
public:

    Q_SIGNAL void saveClicked(QString str);
};

#endif //BUTTON_ADAPTER
