#include <qmath.h>

#include "piechart.h"


namespace QSint
{


PieChart::PieChart(QWidget *parent) :
    RingPlotBase(parent)
{
    m_index = 0;
}


void PieChart::setActiveIndex(int index)
{
    if (m_index == index)
        return;

    m_index = 0;

    scheduleUpdate();

    if (!m_model)
        return;

    if (index >= 0 && index < m_model->columnCount())
        m_index = index;
}


void PieChart::setActiveIndex(const QModelIndex &index)
{
    if (index.isValid())
        setActiveIndex(index.column());
}


void PieChart::drawContent(QPainter &p)
{
    QRect dr(dataRect());

    int w = dr.width() - m_margin*2;
    int h = dr.height() - m_margin*2;

    int wh = qMin(w,h);
    int wh2 = wh / 2;

    int dx2 = (w - wh) / 2;
    int dy2 = dr.top() + (h - wh) / 2;

    QRect pieRect = QRect(dx2+m_margin, dy2+m_margin, wh, wh);

    p.drawEllipse(pieRect);

    if (!m_model)
        return;

    int row_count = m_model->rowCount();
    if (!row_count)
        return;

    int count = m_model->columnCount();
    if (!count)
        return;

    if (m_index < 0 || m_index >= count)
        return;

    // check if need to draw highlight
    bool checkHighlight = false;
    double mouseAngle = 0;

    // check if we're inside piechart at all
    if (!m_mousePos.isNull() && pieRect.contains(m_mousePos))
    {
        // Determine the distance from the center point of the pie chart.
        double cx = m_mousePos.x() - dx2 - wh2;
        double cy = dy2 + wh2 - m_mousePos.y();
        double dr = pow(pow(cx, 2) + pow(cy, 2), 0.5);
        if (!(dr == 0 || dr > wh2)){
            // Determine the angle of the point.
            mouseAngle = (180 / M_PI) * acos(cx/dr);
            if (cy < 0)
                mouseAngle = 360 - mouseAngle;

            checkHighlight = true;
        }
    }

    // draw pie chart
    p.setFont(m_font);

    int r1 = wh2;
    int r2 = wh2;
    drawRing(p, pieRect.center(), m_index, r1, r2, checkHighlight, mouseAngle);
}


void PieChart::drawSegment(QPainter &p, const QRect& pieRect,
                           const QModelIndex &index, double /*value*/,
                           double angle1, double angle2,
                           bool isHighlighted)
{
    int r = index.row();

    if (isHighlighted)
    {
        p.setPen(m_hlPen);
        p.setBrush(m_hlBrush);

        p.drawPie(pieRect, int(angle1*16), int(angle2*16));
    }
    else
    {
        p.setPen(m_itemPen);

        QBrush brush(qvariant_cast<QBrush>(m_model->headerData(r, Qt::Vertical, Qt::BackgroundRole)));
        p.setBrush(brush);

        p.drawPie(pieRect, int(angle1*16), int(angle2*16));
    }
}


void PieChart::drawValue(QPainter &p, const QRect& pieRect,
                           const QModelIndex &index, double value,
                           double angle1, double angle2,
                           bool isHighlighted)
{
    // text (angle CCW in radians)
    double cr = pieRect.height()/4 + pieRect.height()/8;
    double textAngle = (360 - angle1 - angle2/2) * M_PI / 180;
    double tx = cr * cos(textAngle) + pieRect.center().x();
    double ty = cr * sin(textAngle) + pieRect.center().y();

    if (isHighlighted)
    {
        p.setPen(QPen(m_hlTextColor));
    }
    else
    {
        QPen pen(qvariant_cast<QColor>(m_model->headerData(index.row(), Qt::Vertical, Qt::ForegroundRole)));
        p.setPen(pen);
    }

	p.drawText(tx, ty, formattedValue(value, index));
}


}
