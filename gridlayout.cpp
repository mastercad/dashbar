#include "gridlayout.h"

GridLayout::GridLayout(QWidget *parent, int max_column_count)
    : QGridLayout(parent)
{
    m_max_column_count = max_column_count;
}

GridLayout::~GridLayout()
{

}

void GridLayout::add_widget( QWidget* p_widget )
{
    int current_row = 0;
    int current_column = 0;

    while( itemAtPosition(current_row, current_column) != 0 )
    {
        if( current_column == (m_max_column_count-1) )
        {
            current_column = 0;
            ++current_row;
        }
        else
        {
            ++current_column;
        }
    }

    QGridLayout::addWidget( p_widget, current_row, current_column );
}
