#include "barchartplotter.h"
#include "axisbase.h"

// painters
#include "stackedbarpainter.h"
#include "columnbarpainter.h"
#include "trendpainter.h"


namespace QSint
{

// static predefined painters
static StackedBarPainter s_stackedPainter;
static ColumnBarPainter s_columnPainter;
static TrendPainter s_trendPainter;


BarChartPlotter::BarChartPlotter(QWidget *parent) :
    PlotterBase(parent),
	m_barPainter(NULL)
{
    m_axisX = new AxisBase(Qt::Horizontal, this);
    m_axisY = new AxisBase(Qt::Vertical, this);

    setBarType(Stacked);

    m_axisX->setType(AxisBase::AxisModel);

    setBarSize(-INT_MAX, INT_MAX);
    setBarScale(0.5);
    setBarOpacity(1.0);

    setZeroLinePen(QPen(Qt::white));
}


void BarChartPlotter::setBarType(BarChartType type)
{
    switch (type)
    {
    case Stacked:
        setBarPainter(&s_stackedPainter);
        break;

    case Columns:
        setBarPainter(&s_columnPainter);
        break;

    case Trend:
        setBarPainter(&s_trendPainter);
        break;

    default:
        setBarPainter(NULL);

        Q_ASSERT(false);
        break;
    }
}


void BarChartPlotter::setBarPainter(BarPainter *painter)
{
    if (painter != m_barPainter)
    {
        m_barPainter = painter;
    }
}


void BarChartPlotter::setBarSize(int min, int max)
{
    m_barsize_min = qMax(min, 0);
    m_barsize_max = qMax(min, max);
}


void BarChartPlotter::setBarScale(double scale)
{
    if (scale < 0.1)
        m_scale = 0.1;
    else
        m_scale = qMin(scale, 1.0);
}


void BarChartPlotter::setBarOpacity(double value)
{
    if (value < 0.0)
        m_opacity = 0;
    else
        m_opacity = qMin(value, 1.0);
}


void BarChartPlotter::setZeroLinePen(const QPen &pen)
{
    m_zeroLinePen = pen;
}


void BarChartPlotter::drawContent(QPainter &p)
{
    if (!m_model || !m_axisX || !m_axisY)
        return;

    int p_start, p_end;
    m_axisX->calculatePoints(p_start, p_end);

    // draw zero line
    int p_y = m_axisY->toView(0);

    p.setPen(m_zeroLinePen);
    p.drawLine(p_start, p_y, p_end, p_y);

    int count = m_model->columnCount();
    if (!count)
        return;

    int row_count = m_model->rowCount();
    if (!row_count)
        return;

    int p_offs = double(p_end - p_start) / count;

    int bar_size = p_offs * m_scale;

    if (bar_size > m_barsize_max)
        bar_size = qMin(m_barsize_max, p_offs);
    else if (bar_size < m_barsize_min)
        bar_size = qMin(m_barsize_min, p_offs);

	if (m_barPainter)
	{
		QModelIndex indexUnderMouse = m_barPainter->draw(this, mousePos(), p, count, row_count, p_start, p_offs, bar_size);
		setIndexUnderMouse(indexUnderMouse);
	}
}



} // namespace
