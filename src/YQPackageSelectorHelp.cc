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

  File:	      YQPackageSelectorHelp.cc
  See also:   YQPackageSelector.cc

  Author:     Stefan Hundhammer <sh@suse.de>

  Textdomain "packages-qt"

/-*/

#include <qstring.h>

#define y2log_component "qt-pkg"
#include <ycp/y2log.h>

#include "YQPackageSelector.h"
#include "YQPkgTextDialog.h"

#include "utf8.h"
#include "YQi18n.h"


#warning TODO: Make sure all files are included in POTFILES!

void
YQPackageSelector::help()
{
    // Translators: Headline for help about the package manager in general

    QString html = YQPkgTextDialog::htmlHeading( _( "The YaST2 Package Manager" ) );

    // Translators: Automatic word-wrapping.
    html += para( _( "<b>Note:</b> This is an just a short  overview."
		     " Please refer to the manual for details." ) );

    if ( _youMode )
    {
	// Help specific to YOU (YaST Online Update) mode

	html += para( _( "In this dialog you can select YOU (YaST Online Update) patches to download and install." ) );
	html += para( _( "The list on the left side contains available patches"
			 " along with the respective patch kind (security, recommended, or optional)"
			 " and the (estimated) download size." ) );
	html += para( _( "This list normally contains only those patches that are not installed on your system yet."
			 " You can change that with the <b>Include Installed Patches</b> check box below the list." ) );
	html += para( _( "The <b>Patch Description</b> field contains a longer explanation what the currently"
			 " selected patch is all about. Click on a patch in the list to view its description here." ) );
	html += para( _( "The package list on the right side shows the contents of the currently selected patch, i.e.,"
			 " the packages it contains. You cannot install or delete individual packages from a patch,"
			 " only the patch as a whole. This is intentional to avoid system inconsistencies." ) );

	// Translators: Please keep the reference to "filter views" to distinguish between "filter views" that
	// affect the amount of visible packages in the package list and "details views" (below the package list)
	// that show details about the (one) currently selected package in the package list.

	html += para( _( "In addition to \"YOU-patches\", you can also select one of the other filter views"
			 " from the <b>Filter</b> combo-box at the top left:" ) );
    }
    else // ! _youMode
    {
	// Help specific to normal (non-YOU) mode

	html += para( _( "In this dialog you can select which packages to install, update or delete."
			 " You can select individual packages or entire package \"selections\"." ) );
	html += para( _( "Click on a package's or selection's status icon to change the status"
			 " or right-click it to open a context menu." ) );
	html += para( _( "Use the <b>Check Dependencies</b> button to resolve package dependencies:"
			 " Some packages require other packages to be installed,"
			 " some packages can only be installed if certain other packages are not installed, too."
			 " This check will automatically mark required packages for installation,"
			 " and it will warn you if there are dependency conflicts." ) );
	html += para( _( "When you leave this dialog with <b>Accept</b>, this check will automatically be performed." ) );
	
	// Translators: Please keep the reference to "filter views" to distinguish between "filter views" that
	// affect the amount of visible packages in the package list and "details views" (below the package list)
	// that show details about the (one) currently selected package in the package list.

	html += para( _( "In addition to \"Selections\", you can also switch to one of the other filter views"
			 " with the <b>Filter</b> combo-box at the top left:" ) );
    }

    // Help common to all modes: Description of the various filter views
    
    html += "<ul>";

    html += listItem( para( _( "<b>Package Groups</b> shows packages by category. You can expand and collapse tree items"
			       " to refine or generalize categories. Click on any category to display the packages"
			       " in that category in the package list on the right side." ) ) +
		      para( _( " <b>Hint:</b> There is a \"zzz All\" entry at the very end of the list that will show"
			       " all packages. This may take a few seconds on slow machines." ) ) );
    
    html += listItem( para( _( "<b>Search</b> allows you to search packages that meet various criteria."
			       " This is usually the easiest way to find a package if you know its name." ) )+
		      para( _( "<b>Hint:</b> You can also use this to find out what package contains a certain library: "
			       " Search in the <b>Provides</b> RPM field." ) ) );
    
    html += listItem( para( _( "<b>Installation Summary</b> by default shows the changes to your system - what packages"
			       " will be installed, deleted, or updated." ) ) +
		      para( _( "It is generally a good idea to use <b>Check Dependencies</b> and then switch to"
			       " <b>Installation Summary</b> before clicking <b>Accept</b> - this way you can see"
			       " all changes to your system that will be performed." ) ) +
		      para( _( "You can also explicitly select what packages with what status you wish to see here;"
			       " use the check boxes at the left side." ) ) +
		      para( _( "<b>Hint:</b> You can also reverse the effect of this filter:"
			       " You can see what packages remain the same on your system. Simply check <b>Keep</b>"
			       " and uncheck everything else." ) ) );
    
    html += "</ul>";
    

    YQPkgTextDialog::showText( this, html );
}


void
YQPackageSelector::symbolHelp()
{
    // Make sure all images used here are specified in
    // helpimages_DATA in include/Makefile.am !

    // Translators: Headline for help about package status icons
    QString html = YQPkgTextDialog::htmlHeading( _( "Symbols Overview" ) );

    html += "<br>";
    html += "<table border=1>";

    html += symHelp( "noinst.xpm",
		     // Translators: Package status short (!) description
		     _( "Don't install" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is not installed, and it will not be installed." ) );

    html += symHelp( "install.xpm",
		     // Translators: Package status short (!) description
		     _( "Install" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package will be installed. It is not installed yet." ) );

    html += symHelp( "keepinstalled.xpm",
		     // Translators: Package status short (!) description
		     _( "Keep" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is already installed. Keep it untouched." ) );

    html += symHelp( "update.xpm",
		     // Translators: Package status short (!) description
		     _( "Update" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is already installed. Update it or reinstall it"
			" (if the versions are the same)." ) );

    html += symHelp( "del.xpm",
		     // Translators: Package status short (!) description
		     _( "Delete" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is already installed. Delete it." ) );

    html += symHelp( "taboo.xpm",
		     // Translators: Package status short (!) description
		     _( "Taboo" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is not installed, and I don't want it under any circumstances -"
			" in particular not because of unresolved dependencies that other packages"
			" might have or get." )
		     + " "
		     + _( "Packages set to \"taboo\" are treated as if they didn't exist on any installation media." ) );


    html += symHelp( "autoinstall.xpm",
		     // Translators: Package status short (!) description
		     _( "Auto-install" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package will be installed automatically because some other package needs it"
			" or because it is contained in a predefined software selection"
			" (e.g., \"Multimedia\", \"Development\" )." )
		     + " "
		     + _( "<b>Hint:</b> You may have to use \"taboo\" to get rid of such a package." ) );

    html += symHelp( "autoupdate.xpm",
		     // Translators: Package status short (!) description
		     _( "Auto-update" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is already installed, but some other package (or selection)"
			" needs a newer version, so it will automatically be updated." ) );

    html += symHelp( "autodel.xpm",
		     // Translators: Package status short (!) description
		     _( "Auto-delete" ),
		     // Translators: Automatic word-wrapping.
		     _( "This package is already installed, but some predefined software selection"
			"(e.g., \"Multimedia\", \"Development\" ) requires that it is deleted." ) );

    html += "/<table>";


    YQPkgTextDialog::showText( this, html );
}


QString
YQPackageSelector::symHelp( const QString & imgFileName,
			    const QString & summary,
			    const QString & explanation		)
{
    QString imgPath = HELPIMAGEDIR;
    QString html = "<tr valign=top>";
    html += "<td><img src=\"" + imgPath + "/" + imgFileName + "\"></td>"
	+ "<td>" + summary 	+ "</td>"
	+ "<td>" + explanation 	+ "</td>"
	+ "</tr>";

    return html;
}


void
YQPackageSelector::keyboardHelp()
{
    // Translators: Headline for help about "magic keys" in the package manager
    QString html = YQPkgTextDialog::htmlHeading( _( "Special Keys Overview" ) );

    // Translators: Additional hint that will be added to any of the following keyboard actions.
    // Automatic word wrapping.
    QString goto_next = "<br>" + _( "In any case, go to the next list item." );

    html += "<br>";
    html += "<table border=1>";

    html += keyHelp( "+",
		     // Translators: Keyboard action short (!) description
		     _( "Add" ),
		     // Translators: Automatic word-wrapping.
		     _( "Get this package. Install it if it isn't installed yet,"
			" update it to the latest version if it is installed "
			" and there is a newer version." )
		     + goto_next );

    html += keyHelp( "-",
		     // Translators: Keyboard action short (!) description
		     _( "Remove" ),
		     // Translators: Automatic word-wrapping.
		     _( "Get rid of this package. Mark it as \"don't install\" "
			"if it isn't installed yet, delete it if it is installed." )
		     + goto_next );

    html += keyHelp( "&gt;",
		     // Translators: Keyboard action short (!) description
		     _( "Update" ),
		     // Translators: Automatic word-wrapping.
		     _( "Update this package if it is installed and there is a newer version."
			" Ignore packages that are not installed." )
		     + goto_next );


    html += keyHelp( "&lt;",
		     // Translators: Keyboard action short (!) description
		     _( "Undo update" ),
		     // Translators: Automatic word-wrapping.
		     _( "Undo the effect of \">\" above: Set package to \"keep\""
			" if it is currently set to \"update\". Ignore all other packages." )
		     + goto_next );

    html += keyHelp( "!",
		     // Translators: Keyboard action short (!) description
		     _( "Taboo" ),
		     // Translators: Automatic word-wrapping.
		     _( "Set this package to \"taboo\" if it isn't installed:"
			" Make sure this package doesn't get installed, in particular not"
			" because of unresolved dependencies that other packages might have or get. " )
		     + " "
		     + _( "Packages set to \"taboo\" are treated as if they didn't exist on any installation media." )
		     + "<br>"
		     + goto_next );

    html += "/<table>";


    YQPkgTextDialog::showText( this, html );
}


QString
YQPackageSelector::keyHelp( const QString & key,
			    const QString & summary,
			    const QString & explanation		)
{
    QString html = "<tr valign=top>";
    html +=
	"<td><table bgcolor=#E0E0E0><tr><td align=center><b>"
	+ key
	+ "</b></td></tr></table></td>"
	+ "<td>" + summary 	+ "</td>"
	+ "<td>" + explanation 	+ "</td>"
	+ "</tr>";

    return html;
}


QString
YQPackageSelector::para( const QString & text )
{
    return "<p>" + text + "</p>";
}


QString
YQPackageSelector::listItem( const QString & text )
{
    return "<li>" + text + "</li>";
}


