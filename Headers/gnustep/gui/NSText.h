/* 
   NSText.h

   The text object

   Copyright (C) 1996 Free Software Foundation, Inc.

   Author:  Scott Christley <scottc@net-community.com>
   Date: 1996
   Author:  Felipe A. Rodriguez <far@ix.netcom.com>
   Date: July 1998
   Author:  Daniel B�hringer <boehring@biomed.ruhr-uni-bochum.de>
   Date: August 1998
  
   This file is part of the GNUstep GUI Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/ 

#ifndef _GNUstep_H_NSText
#define _GNUstep_H_NSText

#include <AppKit/NSView.h>
#include <AppKit/NSSpellProtocol.h>
#include <Foundation/NSRange.h>
#include <AppKit/NSAttributedString.h>

@class NSString;
@class NSData;
@class NSNotification;
@class NSColor;
@class NSFont;

typedef enum _NSTextAlignment {
	NSLeftTextAlignment,
	NSRightTextAlignment,
	NSCenterTextAlignment,
	NSJustifiedTextAlignment,
	NSNaturalTextAlignment
} NSTextAlignment;

enum {
	NSIllegalTextMovement	= 0,
	NSReturnTextMovement	= 0x10,
	NSTabTextMovement	 	= 0x11,
	NSBacktabTextMovement	= 0x12,
	NSLeftTextMovement	 = 0x13,
	NSRightTextMovement	 = 0x14,
	NSUpTextMovement	 = 0x15,
	NSDownTextMovement	 = 0x16
};	 	

// these definitions should migrate to NSTextView when implemented

typedef enum _NSSelectionGranularity
{	NSSelectByCharacter = 0,
    NSSelectByWord = 1,
    NSSelectByParagraph = 2,
} NSSelectionGranularity;

typedef enum _NSSelectionAffinity
{	NSSelectionAffinityUpstream = 0,
    NSSelectionAffinityDownstream = 1,
} NSSelectionAffinity;


@interface NSText : NSView <NSChangeSpelling,NSIgnoreMisspelledWords,NSCoding>
{											
	id delegate;
	unsigned int alignment;
	BOOL is_editable;
	BOOL is_rich_text;
	BOOL is_selectable;
	BOOL imports_graphics;
	BOOL uses_font_panel;
	BOOL is_horizontally_resizable;
	BOOL is_vertically_resizable;
	BOOL is_ruler_visible;
	BOOL is_field_editor;
	BOOL draws_background;
	NSColor *background_color;
	NSColor *text_color;
	NSFont *default_font;
	NSRange selected_range;
	
	void *be_text_reserved;						// Reserved for back-end use

	NSSize	minSize, maxSize;					// added for Daniel B�hringer
	// content
	NSMutableString *plainContent;
	NSMutableAttributedString *rtfContent;
	NSCharacterSet *selectionWordGranularitySet; 	
	NSCharacterSet *selectionParagraphGranularitySet;

	id lineLayoutInformation;
	NSMutableDictionary *typingAttributes; 
	float currentCursorX;	// column-stable cursor up/down
	BOOL displayDisabled;
	int spellCheckerDocumentTag;
}


// GNU utility methods
// return value is guaranteed to be a NSAttributedString even if data contains only NSString
+(NSAttributedString*) attributedStringForData:(NSData*) aData;
+(NSData*) dataForAttributedString:(NSAttributedString*) aString;

+(NSString*) newlineString;	// GNU extension (override it if you want other characters treated as newline characters)

//
// Getting and Setting Contents (low level: no selection handling, relayout or display)
//
-(void) replaceRange:(NSRange)range withAttributedString:(NSAttributedString*)attrString;	// GNU extension
-(void) replaceRange:(NSRange)range withString:(NSString*) aString;
-(void) replaceRange:(NSRange)range withRTF:(NSData *)rtfData;
-(void) replaceRange:(NSRange)range withRTFD:(NSData *)rtfdData;
-(NSData*) RTFDFromRange:(NSRange)range;
-(NSData*) RTFFromRange:(NSRange)range;
-(void) setString:(NSString *)string;
-(void) setText:(NSString *)string;	// old fashioned
-(void) setText:(NSString*) aString range:(NSRange) aRange;		// old fashioned
-(NSString*) string;
-(NSString*) text;				// old fashioned

-(unsigned) textLength;			// GNU extension


//
// Managing Global Characteristics
//
- (NSTextAlignment)alignment;
- (BOOL)drawsBackground;
- (BOOL)importsGraphics;
- (BOOL)isEditable;
- (BOOL)isRichText;
- (BOOL)isSelectable;
- (void)setAlignment:(NSTextAlignment)mode;
- (void)setDrawsBackground:(BOOL)flag;
- (void)setEditable:(BOOL)flag;
- (void)setImportsGraphics:(BOOL)flag;
- (void)setRichText:(BOOL)flag;
- (void)setSelectable:(BOOL)flag;

//
// Managing Font and Color
//
- (NSColor *)backgroundColor;
- (void)changeFont:(id)sender;
- (NSFont *)font;
- (void)setBackgroundColor:(NSColor *)color;
-(void) setTextColor:(NSColor *)color range:(NSRange)range;
- (void)setColor:(NSColor *)color ofRange:(NSRange)range;
- (void)setFont:(NSFont *)obj;
- (void)setFont:(NSFont *)font ofRange:(NSRange)range;
- (void)setTextColor:(NSColor *)color;
- (void)setUsesFontPanel:(BOOL)flag;
- (NSColor *)textColor;
- (BOOL)usesFontPanel;

//
// Managing the Selection
//
- (NSRange)selectedRange;
- (void)setSelectedRange:(NSRange)range;

//
// Sizing the Frame Rectangle
//
- (BOOL)isHorizontallyResizable;
- (BOOL)isVerticallyResizable;
- (NSSize)maxSize;
- (NSSize)minSize;
- (void)setHorizontallyResizable:(BOOL)flag;
- (void)setMaxSize:(NSSize)newMaxSize;
- (void)setMinSize:(NSSize)newMinSize;
- (void)setVerticallyResizable:(BOOL)flag;
- (void)sizeToFit;

//
// Responding to Editing Commands
//
- (void)alignCenter:(id)sender;
- (void)alignLeft:(id)sender;
- (void)alignRight:(id)sender;
- (void)copy:(id)sender;
- (void)copyFont:(id)sender;
- (void)copyRuler:(id)sender;
- (void)cut:(id)sender;
- (void)delete:(id)sender;
- (void)paste:(id)sender;
- (void)pasteFont:(id)sender;
- (void)pasteRuler:(id)sender;
- (void)selectAll:(id)sender;
- (void)subscript:(id)sender;
- (void)superscript:(id)sender;
- (void)underline:(id)sender;
- (void)unscript:(id)sender;

//
// Managing the Ruler
//
- (BOOL)isRulerVisible;
- (void)toggleRuler:(id)sender;

//
// Spelling
//
-(void) checkSpelling:(id)sender;
-(void) showGuessPanel:(id)sender;

//
// Scrolling
//
- (void)scrollRangeToVisible:(NSRange)range;

//
// Reading and Writing RTFD Files
//
-(BOOL) readRTFDFromFile:(NSString *)path;
-(BOOL) writeRTFDToFile:(NSString *)path atomically:(BOOL)flag;

//
// Managing the Field Editor
//
- (BOOL)isFieldEditor;
- (void)setFieldEditor:(BOOL)flag;

//
// Managing the Delegate
//
- delegate;
-(void) setDelegate:anObject;


//
// NSCoding protocol
//
- (void)encodeWithCoder:aCoder;
- initWithCoder:aDecoder;

//
// NSChangeSpelling protocol
//
- (void) changeSpelling:(id)sender;

//
// NSIgnoreMisspelledWords protocol
//
- (void)ignoreSpelling:(id)sender;

//
// these NSTextView methods are here only informally (GNU extensions)
//
-(int) spellCheckerDocumentTag;

-(void) insertText:insertString;	// argument may be of class NSString or NSAttributedString (if isRichText)
-(NSMutableDictionary*) typingAttributes;
-(void) setTypingAttributes:(NSDictionary *)attrs;


-(BOOL) shouldDrawInsertionPoint;
-(void) drawInsertionPointInRect:(NSRect)rect color:(NSColor *)color turnedOn:(BOOL)flag;

-(NSArray*) acceptableDragTypes;
-(void) updateDragTypeRegistration;

-(NSRange) selectionRangeForProposedRange:(NSRange)proposedCharRange granularity:(NSSelectionGranularity)granularity; // override if you want special cursor behaviour

//
// these NSLayoutManager- like methods are here only informally (GNU extensions)
//

-(unsigned) characterIndexForPoint:(NSPoint)point;
-(NSRect) rectForCharacterIndex:(unsigned) index;
-(NSRect) boundingRectForLineRange:(NSRange)lineRange;
-(NSRange) characterRangeForBoundingRect:(NSRect)bounds;
-(NSRange) lineRangeForRect:(NSRect) aRect;

//
// these are implementation specific (GNU extensions)
//
-(int) rebuildLineLayoutInformationStartingAtLine:(int) aLine;	// returns count of lines actually updated (e.g. drawing optimization)
-(int) rebuildPlainLineLayoutInformationStartingAtLine:(int) aLine delta:(int) insertionDelta actualLine:(int) insertionLine;	// override for special layout of plain text
-(int) rebuildRichLineLayoutInformationStartingAtLine:(int) aLine delta:(int) insertionDelta actualLine:(int) insertionLine;	// ditto for rich text

-(int) lineLayoutIndexForCharacterIndex:(unsigned) anIndex;		// return value is identical to the real line number (plus counted newline characters)
-(void) redisplayForLineRange:(NSRange) redrawLineRange;
-(void) drawRichLinesInLineRange:(NSRange) aRange;	// low level, override but never invoke (use redisplayForLineRange:)
-(void) drawPlainLinesInLineRange:(NSRange) aRange;	// low level, override but never invoke (use redisplayForLineRange:)

//
// various GNU extensions
//

-(void) setSelectionWordGranularitySet:(NSCharacterSet*) aSet;
-(void) setSelectionParagraphGranularitySet:(NSCharacterSet*) aSet;

//
// private (never invoke, never subclass)
//

-(void) drawRectNoSelection:(NSRect)rect;
-(int) rebuildPlainLineLayoutInformationStartingAtLine:(int) aLine;	// low level never invoke (use rebuildLineLayoutInformationStartingAtLine:)
-(int) rebuildRichLineLayoutInformationStartingAtLine:(int) aLine;	//  ditto

@end

/* Notifications */
extern NSString *NSTextDidBeginEditingNotification;
extern NSString *NSTextDidEndEditingNotification;
extern NSString *NSTextDidChangeNotification;

@interface NSObject(NSTextDelegate)
- (BOOL)textShouldBeginEditing:(NSText *)textObject; /* YES means do it */
- (BOOL)textShouldEndEditing:(NSText *)textObject; /* YES means do it */
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification; /* Any keyDown or paste which changes the contents causes this */
@end

#endif // _GNUstep_H_NSText
