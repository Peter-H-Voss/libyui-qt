/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YQSlider.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#define y2log_component "qt-ui"
#include <ycp/y2log.h>

#include "utf8.h"
#include "YUIQt.h"
#include "YQSlider.h"


#define VSPACING 2
#define	HSPACING 2
#define MARGIN   2


YQSlider::YQSlider( QWidget *		parent,
		    YWidgetOpt &	opt,
		    const YCPString &	label,
		    int 		minValue,
		    int 		maxValue,
		    int 		initialValue )

    : QWidget( parent )
    , YSlider( opt, label, minValue, maxValue, initialValue )
{
    setWidgetRep( this );

    vbox = new QVBox( this );
    vbox->setSpacing( VSPACING );
    vbox->setMargin( MARGIN );
    _qt_label = new QLabel( fromUTF8( label->value() ), vbox );
    _qt_label->setTextFormat( QLabel::PlainText );
    _qt_label->setFont( YUIQt::ui()->currentFont() );
    _qt_label->setAlignment( Qt::AlignRight );

    hbox = new QHBox( vbox );
    hbox->setSpacing( HSPACING );

    _qt_slider = new QSlider( minValue, maxValue,
			     1, // pageStep
			     initialValue,
			     QSlider::Horizontal, hbox );
    _qt_slider->setFont( YUIQt::ui()->currentFont() );

    _qt_spinbox = new QSpinBox( minValue, maxValue,
			       1, // step
			       hbox );
    _qt_spinbox->setValue( initialValue );
    _qt_spinbox->setFont( YUIQt::ui()->currentFont() );

    _qt_label->setBuddy( _qt_spinbox );

    setValue( initialValue );

    connect( _qt_spinbox, SIGNAL( valueChanged( int ) ),
	     _qt_slider,  SLOT  ( setValue    ( int ) ) );

    connect( _qt_slider, 	SIGNAL( valueChanged( int ) ),
	     _qt_spinbox, SLOT  ( setValue    ( int ) ) );

    connect( _qt_spinbox, SIGNAL( valueChanged( int ) ),
	     this,  	SLOT  ( setValueSlot( int ) ) );
}


void YQSlider::setEnabling( bool enabled )
{
    _qt_label->setEnabled  ( enabled );
    _qt_slider->setEnabled ( enabled );
    _qt_spinbox->setEnabled( enabled );
}


long YQSlider::nicesize( YUIDimension dim )
{
    if ( dim == YD_HORIZ ) return 200;
    else return vbox->sizeHint().height();
}


void YQSlider::setSize( long newWidth, long newHeight )
{
    vbox->resize( newWidth, newHeight );
    resize( newWidth, newHeight );
}

void YQSlider::setLabel( const YCPString & newLabel )
{
    _qt_label->setText( fromUTF8( newLabel->value() ) ) ;

    YSlider::setLabel( newLabel );
}


void YQSlider::setValue( int newValue )
{
    _qt_slider->setValue( newValue );
    YSlider::setValue( newValue );
}


void YQSlider::setValueSlot( int newValue )
{
    setValue( newValue );

    if ( getNotify() )
	YUIQt::ui()->returnNow( YUIInterpreter::ET_WIDGET, this );
}


bool YQSlider::setKeyboardFocus()
{
    _qt_spinbox->setFocus();

    return true;
}


#include "YQSlider.moc.cc"
