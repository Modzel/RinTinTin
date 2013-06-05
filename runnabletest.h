#ifndef RUNNABLETEST_H
#define RUNNABLETEST_H

#include <QRunnable>

class runnableTest : public QRunnable
{
    Q_OBJECT
public:
    explicit runnableTest(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // RUNNABLETEST_H
