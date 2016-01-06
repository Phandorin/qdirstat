/*
 *   File name: Refresher.h
 *   Summary:	Helper class to refresh a number of subtrees
 *   License:	GPL V2 - See file LICENSE for details.
 *
 *   Author:	Stefan Hundhammer <Stefan.Hundhammer@gmx.de>
 */


#ifndef Refresher_h
#define Refresher_h

#include <QObject>
#include "FileInfo.h"


namespace QDirStat
{
    /**
     * Helper class to refresh a number of subtrees:
     *
     * Store a FileInfoSet and when a signal is received (typically
     * ProcessOutput::lastProcessFinished()), trigger refreshing all stored
     * subtrees.
     *
     * Do not hold on to pointers to instances of this class since each
     * instance will destroy itself at the end of refresh(). On the other hand,
     * if the signal triggering refresh() never arrives, this object will stay
     * forever, so give it a QObject parent (so it will be destroyed when its
     * parent is destroyed) to avoid a memory leak.
     **/
    class Refresher: public QObject
    {
    public:

	/**
	 * Create a Refresher that will refresh all subtrees in 'items' it its
	 * refresh() slot.
	 *
	 * All items are assumed to belong to the same DirTree.
	 **/
	Refresher( const FileInfoSet items, QObject * parent );

	/**
	 * Return a FileInfoSet of all parents of all items of 'children'.
	 **/
	static FileInfoSet parents( const FileInfoSet children );

    public slots:

	/**
	 * Refresh all subtrees in the internal FileInfoSet.
	 * After this is done, this object will delete itself.
	 **/
	void refresh();

    protected:

	FileInfoSet _items;
    };
}	// namespace QDirStat

#endif	// Refresher_h
