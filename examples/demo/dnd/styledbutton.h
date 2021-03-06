/**********************************************************************
** Copyright (C) 2005-2008 Trolltech ASA.  All rights reserved.
**
** This file is part of Qt Designer.
**
** This file may be used under the terms of the GNU General
** Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the files LICENSE.GPL2
** and LICENSE.GPL3 included in the packaging of this file.
** Alternatively you may (at your option) use any later version
** of the GNU General Public License if such license has been
** publicly approved by Trolltech ASA (or its successors, if any)
** and the KDE Free Qt Foundation.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/.
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with
** the Software.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not granted
** herein.
**
**********************************************************************/

#ifndef STYLEDBUTTON_H
#define STYLEDBUTTON_H

#include <qbutton.h>
#include <qpixmap.h>

class QColor;
class QBrush;

class StyledButton : public QButton
{
    Q_OBJECT

    Q_PROPERTY( QColor color READ color WRITE setColor )
    Q_PROPERTY( QPixmap pixmap READ pixmap WRITE setPixmap )
    Q_PROPERTY( EditorType editor READ editor WRITE setEditor )
    Q_PROPERTY( bool scale READ scale WRITE setScale )

    Q_ENUMS( EditorType )

public:
    enum EditorType { ColorEditor, PixmapEditor };

    StyledButton( QWidget* parent = 0, const char* name = 0 );
    StyledButton( const QBrush& b, QWidget* parent = 0, const char* name = 0, WFlags f = 0 );
    ~StyledButton();

    void setEditor( EditorType );
    EditorType editor() const;

    void setColor( const QColor& );
    void setPixmap( const QPixmap& );

    QPixmap* pixmap() const;
    QColor color() const;

    void setScale( bool );
    bool scale() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    virtual void onEditor();

signals:
    void changed();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
#ifndef QT_NO_DRAGANDDROP
    void dragEnterEvent ( QDragEnterEvent * );
    void dragMoveEvent ( QDragMoveEvent * );
    void dragLeaveEvent ( QDragLeaveEvent * );
    void dropEvent ( QDropEvent * );
#endif // QT_NO_DRAGANDDROP
    void drawButton( QPainter* );
    void drawButtonLabel( QPainter* );
    void resizeEvent( QResizeEvent* );
    void scalePixmap();

private:
    QPixmap* pix;
    QPixmap* spix;  // the pixmap scaled down to fit into the button
    QColor col;
    EditorType edit;
    bool s;
    QPoint pressPos;
    bool mousePressed;
};

#endif //STYLEDBUTTON_H
