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

  File:	      YQPkgPatchFilterView.cc

  Author:     Stefan Hundhammer <sh@suse.de>

  Textdomain "packages-qt"

/-*/


#define y2log_component "qt-pkg"
#include <ycp/y2log.h>

#include <qcombobox.h>
#include <qlabel.h>
#include <qsplitter.h>
#include <qtabwidget.h>

#include <y2util/FSize.h>

#include "YQPkgPatchFilterView.h"
#include "YQPkgPatchList.h"
#include "YQPkgDescriptionView.h"
#include "YQPkgSelList.h"
#include "QY2LayoutUtils.h"
#include "YQi18n.h"


#define SPACING			6	// between subwidgets
#define MARGIN			4	// around the widget


YQPkgPatchFilterView::YQPkgPatchFilterView( QWidget * parent )
    : QVBox( parent )
{
    QVBox * vbox;

    _splitter			= new QSplitter( QSplitter::Vertical, this );	CHECK_PTR( _splitter 		);

    vbox			= new QVBox( _splitter );			CHECK_PTR( vbox			);
    _youPatchList		= new YQPkgPatchList( vbox );		CHECK_PTR( _youPatchList 	);

    addVSpacing( vbox, 4 );

    QHBox * hbox 		= new QHBox( vbox ); CHECK_PTR( hbox );
    hbox->setSpacing( SPACING );
    QLabel * label		= new QLabel( _( "&Show Patch Category:" ), hbox );

    _patchCategory		= new QComboBox( hbox );
    CHECK_PTR( _patchCategory );

    _patchCategory->insertItem( _( "Installable Patches" ),			0 );
    _patchCategory->insertItem( _( "Installable and Installed Patches" ),	1 );
    _patchCategory->insertItem( _( "All Patches" ),				2 );
    _patchCategory->setCurrentItem( 0 );
    _patchCategory->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed ) ); // hor/vert
    label->setBuddy( _patchCategory );

    connect( _patchCategory, SIGNAL( activated( int ) ), this, SLOT( fillPatchList() ) );
    addVSpacing( vbox, 4 );

    vbox			= new QVBox( _splitter );			CHECK_PTR( vbox			);
    addVSpacing( vbox, 8 );

    _detailsViews		= new QTabWidget( vbox );			CHECK_PTR( _detailsViews	);
    _detailsViews->setMargin( MARGIN );

    _descriptionView		= new YQPkgDescriptionView( _detailsViews );	CHECK_PTR( _descriptionView	);

    _descriptionView->setMinimumSize( 0, 0 );
    _detailsViews->addTab( _descriptionView, _( "Patch Description" ) );

    //
    // HBox for total download size
    //

    addVSpacing( vbox, 4 );
    hbox = new QHBox( vbox ); CHECK_PTR( hbox );
    addHStretch( hbox );

    new QLabel( _( "Estimated Download Size:" ) + " ", hbox );
    _totalDownloadSize		= new QLabel( FSize(0).asString().c_str(), hbox );
    CHECK_PTR( _totalDownloadSize );


    // Give the total download size a 3D look

    _totalDownloadSize->setFrameStyle( QFrame::Panel | QFrame::Sunken );
    _totalDownloadSize->setLineWidth(1);
    _totalDownloadSize->setMidLineWidth(2);


    connect( _youPatchList,	SIGNAL( selectionChanged    ( ZyppSel ) ),
	     _descriptionView,	SLOT  ( showDetailsIfVisible( ZyppSel ) ) );

    connect( _youPatchList,	SIGNAL( statusChanged() 		),
	     this,		SLOT  ( updateTotalDownloadSize() 	) );

    updateTotalDownloadSize();
}


YQPkgPatchFilterView::~YQPkgPatchFilterView()
{
    // NOP
}


void
YQPkgPatchFilterView::updateTotalDownloadSize()
{
#ifdef FIXME
    _totalDownloadSize->setText( Y2PM::youPatchManager().totalDownloadSize().asString().c_str() );
#endif
}


void
YQPkgPatchFilterView::fillPatchList()
{
    YQPkgPatchList::PatchCategory category;

    switch ( _patchCategory->currentItem() )
    {
	case 0:		category = YQPkgPatchList::InstallablePatches;			break;
	case 1:		category = YQPkgPatchList::InstallableAndInstalledPatches;		break;
	case 2:		category = YQPkgPatchList::AllPatches;				break;
	default:	category = YQPkgPatchList::InstallablePatches;			break;
    }

    _youPatchList->setPatchCategory( category );
    _youPatchList->fillList();
    _youPatchList->selectSomething();
}


QSize
YQPkgPatchFilterView::sizeHint() const
{
    return QSize( 600, 350 );
}


#include "YQPkgPatchFilterView.moc"