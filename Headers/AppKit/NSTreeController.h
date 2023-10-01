/*
   NSTreeController.h

   The tree controller class.

   Copyright (C) 2012 Free Software Foundation, Inc.

   Author:  Gregory Casamento <greg.casamento@gmail.com>
   Date: 2012

   This file is part of the GNUstep GUI Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; see the file COPYING.LIB.
   If not, see <http://www.gnu.org/licenses/> or write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef _GNUstep_H_NSTreeController
#define _GNUstep_H_NSTreeController

#import <AppKit/AppKitDefines.h>

#if OS_API_VERSION(MAC_OS_X_VERSION_10_4, GS_API_LATEST)
#import <AppKit/NSObjectController.h>

@class NSString;
@class NSArray;
@class NSIndexPath;
@class NSTreeNode;

APPKIT_EXPORT_CLASS
@interface NSTreeController : NSObjectController <NSCoding, NSCopying>
{
  NSString *_childrenKeyPath;
  NSString *_countKeyPath;
  NSString *_leafKeyPath;
  NSArray *_sortDescriptors;
  NSArray *_arranged_objects;
  NSMutableArray *_selection_index_paths;

  BOOL _alwaysUsesMultipleValuesMarker;
  BOOL _avoidsEmptySelection;
  BOOL _preservesSelection;
  BOOL _selectsInsertedObjects;
  BOOL _canAddChild;
  BOOL _canInsert;
  BOOL _canInsertChild;
}

/**
 * Adds the objects in the indexPaths array to the current selection.
 */
- (BOOL) addSelectionIndexPaths: (NSArray *)indexPaths;

/**
 * BOOL that indicates if the controller returns the multiple values marker when
 * multiple objects have been selected.
 */
- (BOOL) alwaysUsesMultipleValuesMarker;

/**
 * If YES, requires the content array to maintain a selection.
 */
- (BOOL) avoidsEmptySelection;

/**
 * If YES, a child can be added.
 */
- (BOOL) canAddChild;

/**
 * If YES, an object can be inserted.
 */
- (BOOL) canInsert;

/**
 * If YES, a child can be inserted.
 */
- (BOOL) canInsertChild;

/**
 * If YES, then preserve the current selection when the content changes.
 */
- (BOOL) preservesSelection;

/**
 * If YES, then when an object is inserted it is added to the selection.
 */
- (BOOL) selectsInsertedObjects;

/**
 * Makes indexPath the current selection.
 */
- (BOOL) setSelectionIndexPath: (NSIndexPath *)indexPath;

/**
 * Makes the array indexPaths the current selections.
 */
- (BOOL) setSelectionIndexPaths: (NSArray *)indexPaths;

/**
 * All objects managed by this tree controller.
 */
- (id) arrangedObjects;

/**
 * An NSArray containing all selected objects.
 */
- (NSArray*) selectedObjects;

/**
 * The index path of the first selected object.
 */
- (NSIndexPath*) selectionIndexPath;

/**
 * An array containing all of the currently selected objects.
 */
- (NSArray*) selectionIndexPaths;

/**
 * An array containing sort descriptors used to arrange content.
 */
- (NSArray*) sortDescriptors;

/**
 * Key path for children of the node.  This key must be key value
 * compliant.
 */
- (NSString*) childrenKeyPath;

/**
 * Key value path for the flag which gives the count for the children
 * of this node.  The path indicated her must be key-value compliant.
 */
- (NSString*) countKeyPath;

/**
 * Key value path for the flag which determins that this is a leaf.
 * The path indicated her must be key-value compliant.
 */
- (NSString*) leafKeyPath;

/**
 * Adds a child to the current selection using the newObject method.
 */
- (void) addChild: (id)sender;

/**
 * Adds a new objeect to the tree usin the newObject method.
 */
- (void) add: (id)sender;

/**
 * Inserts a child using the newObject method.  This method
 * will fail if canInsertChild returns NO.
 */
- (void) insertChild: (id)sender;

/**
 * Inserts and object using the newObject method at the specified indexPath.
 */
- (void) insertObject: (id)object atArrangedObjectIndexPath: (NSIndexPath *)indexPath;

/**
 * Inserts objects into arranged objects at the specified indexPaths.  These arrays are
 * expected to be parallel and have the same number of objects.
 */
- (void) insertObjects: (NSArray *)objects atArrangedObjectIndexPaths: (NSArray *)indexPaths;

/**
 * Insert an object created by newObject into arranged objects.
 */
- (void) insert: (id)sender;

/**
 * Causes the controller to re-sort and rearrange the objects.  This method
 * should be called if anything has been done that affects the list of objects
 * in the controller.
 */
- (void) rearrangeObjects;

/**
 * Removes object at the specified indexPath.
 */
- (void) removeObjectAtArrangedObjectIndexPath: (NSIndexPath *)indexPath;

/**
 * Removes objects at the specified indexPaths.
 */
- (void) removeObjectsAtArrangedObjectIndexPaths: (NSArray *)indexPaths;

/**
 * Removes selection of objects at the specified indexPaths.
 */
- (void) removeSelectionIndexPaths: (NSArray *)indexPaths;

/**
 * Remove the currently selected object
 */
- (void) remove: (id)sender;

/**
 * Sets the flag to always use multiple values marker.
 */
- (void) setAlwaysUsesMultipleValuesMarker: (BOOL)flag;

/**
 * Sets the flag to avoid empty selection.
 */
- (void) setAvoidsEmptySelection: (BOOL)flag;

/**
 * Sets the children key path.  This needs to be key-value compliant.
 */
- (void) setChildrenKeyPath: (NSString *)path;

/**
 * Sets the count key path.  This needs to be key-value compliant.
 */
- (void) setCountKeyPath: (NSString *)path;

/**
 * Sets leaf key path.  This value needs to be key-value compliant.
 */
- (void) setLeafKeyPath: (NSString *)key;

/**
 * Sets the preserves selection flag.
 */
- (void) setPreservesSelection: (BOOL)flag;

/**
 * Sets the flag that determines if objects inserted are automatically
 * selected.
 */
- (void) setSelectsInsertedObjects: (BOOL)flag;

/**
 * Sets the array of sort descriptors used when building arrangedObjects.
 */
- (void) setSortDescriptors: (NSArray *)descriptors;

#if OS_API_VERSION(MAC_OS_X_VERSION_10_5, GS_API_LATEST)
/**
 * children key path for the given NSTreeNode.
 */
- (NSString*) childrenKeyPathForNode: (NSTreeNode *)node;

/**
 * count key path for the given NSTreeNode.
 */
- (NSString*) countKeyPathForNode: (NSTreeNode *)node;

/**
 * leaf key path for the given NSTreeNode.
 */
- (NSString*) leafKeyPathForNode: (NSTreeNode *)node;

/**
 * Moves node to given indexPath
 */
- (void) moveNode: (NSTreeNode *)node toIndexPath: (NSIndexPath *)indexPath;

/**
 * Move nodes to position at startingIndexPath
 */
- (void) moveNodes: (NSArray *)nodes toIndexPath: (NSIndexPath *)startingIndexPath;

/**
 * Array containing all selected nodes
 */
- (NSArray*) selectedNodes;
#endif
@end

#endif
#endif /* _GNUstep_H_NSTreeController */
