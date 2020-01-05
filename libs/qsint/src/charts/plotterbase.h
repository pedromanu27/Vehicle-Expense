#ifndef PLOTTERBASE_H
#define PLOTTERBASE_H


#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

#include <QtCore/QAbstractItemModel>


namespace QSint
{


class AxisBase;


class TextFormatter
{
public:
	virtual QString text(const QModelIndex& index) const
	{
		return index.data().toString();
	}
};


/**
    \brief Base class for 2-dimensional plotter widgets.
    \since 0.2.1

    Class provides basic grid and background painting and user interaction handling.

    It has easy-to-use API and performs fast "native" painting (directly via QPainter).

    Class is intended to be a basic for the charting widgets supporting MVC ideology
    and using QAbstractItemModel as data source. The model is to be set via setModel() method.

    By default it is assumed that the model has 2-dimensional tabular structure.
    Each model row represents corresponding value on the X axis, with the column data values placed on Y axis.
    Axes could be accessed via axisX() and axisY() methods.
*/
class PlotterBase : public QWidget
{
    Q_OBJECT
public:
    explicit PlotterBase(QWidget *parent = 0);


    /// Sets title text.
    /// \since 0.3
    void setTitle(const QString& title);
    /// Retrieves title text.
    /// \since 0.3
    inline QString title() const { return m_title; }

    /// Sets title pen.
    /// \since 0.3
    void setTitlePen(const QPen& titlePen);
    /// Retrieves title pen.
    /// \since 0.3
    inline QPen titlePen() const { return m_titlePen; }

    /// Sets title font.
    /// \since 0.3
    void setTitleFont(const QFont& titleFont);
    /// Retrieves title font.
    /// \since 0.3
    inline QFont titleFont() const { return m_titleFont; }


    /// Sets pen of the plotter's border to \a pen.
    void setBorderPen(const QPen &pen);
    /// Retrieves plotter's border pen.
    inline const QPen& borderPen() const { return m_pen; }

    /// Sets plotter's background to \a brush.
    void setBackground(const QBrush &brush);
    /// Retrieves plotter background.
    inline const QBrush& background() const { return m_bg; }

    /// Sets font of the data item to \a font.
    void setFont(const QFont &font);
    /// Retrieves data item font.
    inline const QFont& font() const { return m_font; }

    /// Sets pen of the data item to \a pen.
    void setItemPen(const QPen &pen);
    inline const QPen& itemPen() const { return m_itemPen; }


    /// Enables/disables highlighting when mouse is over.
    /// \since 0.3
    void enableHighlight(bool on);
    /// Checks if mouse highlighting enabled.
    /// \since 0.3
    bool isHighlightEnabled() const { return m_highlight; }

    /// Sets color of the highlighted data item text to \a color.
    /// Only applied if isHighlightEnabled() returns true (see enableHighlight()).
    void setHighlightTextColor(const QColor &color);
    /// Retrieves highlighted data item text color.
    inline const QColor& highlightTextColor() const { return m_hlTextColor; }

    /// Sets pen of the highlighted data item to \a pen.
    /// Only applied if isHighlightEnabled() returns true (see enableHighlight()).
    void setHighlightPen(const QPen &pen);
    /// Retrieves highlighted data item pen.
    inline const QPen& highlightPen() const { return m_hlPen; }

    /// Sets brush of the highlighted data item to \a brush.
    /// Only applied if isHighlightEnabled() returns true (see enableHighlight()).
    void setHighlightBrush(const QBrush &brush);
    /// Retrieves highlighted data item brush.
    inline const QBrush& highlightBrush() const { return m_hlBrush; }

    /// Sets opacity of the highlighted data item to \a alpha.
    /// Value should be in ranges between 0.1 and 1.0, 1.0 is the default.
    /// Only applied if isHighlightEnabled() returns true (see enableHighlight()).
    void setHighlightAlpha(double alpha);
    /// Retrieves highlighted data item opacity.
    inline double highlightAlpha() const { return m_hlAlpha; }


    /// Sets format of the value text returned by formattedValue(). %1 replaced by value (Qt::EditRole).
    void setTextFormat(const QString& textFormat);
    /// Retrieves format of the value text used by formattedValue().
    QString textFormat() const { return m_textFormat; }

	// Sets custom text formatter for every value.
	void setTextFormatter(TextFormatter* tf) { m_textFormatter = tf; update(); }
	TextFormatter* textFormatter() const { return m_textFormatter; }

    /// Enables/disables showing of the values (when not highlighted).
    /// \since 0.3
    void showValuesAlways(bool on);
    /// Checks if showing of the values (when not highlighted) enabled.
    /// \since 0.3
    bool valuesAlwaysShown() const { return m_valuesAlwaysShown; }

    /// Enables (\a set=true, the default) or disables (\a set=false) painter's antialiasing.
    inline void setAntiAliasing(bool set) { m_antiAliasing = set;}


    /// Retrieves X axis object.
    inline AxisBase* axisX() const { return m_axisX; }
    /// Retrieves Y axis object.
    inline AxisBase* axisY() const { return m_axisY; }


    /// Sets data model to \a model.
    void setModel(QAbstractItemModel *model);
    /// Retrieves active data model or NULL if not set.
    inline QAbstractItemModel* model() const { return m_model; }


    /// Retrieves data rectangle (excluding margins and axes).
    virtual QRect dataRect() const;

    /// Retrieves current mouse cursor position in local coordinates.
    const QPoint& mousePos() const { return m_mousePos; }
    /// Retrieves current mouse cursor position in global coordinates.
    QPoint globalMousePos() const { return mapToGlobal(m_mousePos); }

    /// Retrieves highlighted data model index, or invalid QModelIndex if nothing highlighted.
    const QModelIndex& highlightedIndex() const { return m_indexUnderMouse; }

Q_SIGNALS:
    /// Emitted when the data item at \a index has been entered by the mouse cursor.
    /// If \a index is invalid that means entering the space without data.
    void entered(const QModelIndex& index);
    /// Emitted when the mouse button has been pressed over the data item at \a index.
    void pressed(const QModelIndex& index);
    /// Emitted when the mouse button has been clicked over the data item at \a index.
    void clicked(const QModelIndex& index);
    /// Emitted when the mouse button has been double clicked over the data item at \a index.
    void doubleClicked(const QModelIndex& index);

protected Q_SLOTS:
    void scheduleUpdate();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void leaveEvent(QEvent *event);

    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    /// Draws default background of the plotter.
    virtual void drawBackground(QPainter &p);
    /// Draws default foreground of the plotter.
    virtual void drawForeground(QPainter &p);
    /// Draws title of the plotter.
    /// \since 0.3
    virtual void drawTitle(QPainter &p);
    /// Draws axes of the plotter.
    virtual void drawAxes(QPainter &p);
    /// Draws content of the plotter.
    virtual void drawContent(QPainter &p) = 0;

	virtual QString formattedValue(double value, const QModelIndex& index) const;

    void setIndexUnderMouse(const QModelIndex& index);

    AxisBase *m_axisX;
    AxisBase *m_axisY;

    QAbstractItemModel *m_model;

    QBrush m_bg;
    QPen m_pen;

    QPen m_itemPen;
    QFont m_font;

    QColor m_hlTextColor;
    QPen m_hlPen;
    QBrush m_hlBrush;
    double m_hlAlpha;
    bool m_highlight;

    QString m_textFormat;
	TextFormatter *m_textFormatter;
    bool m_valuesAlwaysShown;

    QString m_title;
    QFont m_titleFont;
    QPen m_titlePen;

    QPixmap m_buffer;
    bool m_repaint;
    bool m_antiAliasing;

    QPoint m_mousePos;
    QModelIndex m_indexUnderMouse;
    QModelIndex m_indexClick;
};


} // namespace

#endif // PLOTTERBASE_H
