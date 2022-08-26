#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include <QGridLayout>

class GridLayout : public QGridLayout
{
public:
    GridLayout(QWidget *parent, int max_column_count);
    ~GridLayout();

    void add_widget(QWidget* p_widget);

private:
    int m_max_column_count;
};

#endif // GRIDLAYOUT_H
