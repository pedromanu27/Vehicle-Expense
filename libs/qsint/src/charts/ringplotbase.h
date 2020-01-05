#ifndef RINGPLOTBASE_H
#define RINGPLOTBASE_H


#include "plotterbase.h"


namespace QSint
{


class RingPlotBase : public PlotterBase
{
public:
    RingPlotBase(QWidget *parent = 0);

    /// Sets margins between the widget borders and piechart to \a margin (default is 3).
    void setMargin(int margin);
    /// Retrieves current value of the margins between the widget borders and piechart.
    inline int margin() const { return m_margin; }

    /// Enables/disables showing of negative values.
    /// \since 0.3
    void enableNegatives(bool on = true);
    /// Checks if negative values allowed (see enableNegatives()).
    /// \since 0.3
    inline bool negativesAllowed() const { return m_showNegatives; }

protected:
    virtual void drawRing(QPainter &p, const QPoint &center, int ring, int radius1, int radius2, bool checkHighlight, double mouseAngle);

    virtual void drawSegment(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted) = 0;

    virtual void drawValue(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted) = 0;

protected:
    int m_margin;

    bool m_showNegatives;
};


}

#endif // RINGPLOTBASE_H
