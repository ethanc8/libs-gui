/*
   NSEPSImageRep.m

   EPS image representation.

   Copyright (C) 1996 Free Software Foundation, Inc.
   
   Author:  Adam Fedor <fedor@colorado.edu>
   Date: Feb 1996
   
   This file is part of the GNUstep Application Kit Library.

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

#include <Foundation/NSData.h>
#include <AppKit/NSEPSImageRep.h>

@implementation NSEPSImageRep 

// Initializing a New Instance 
+ (id) imageRepWithData: (NSData *)epsData
{
  return [[self alloc] initWithData: epsData];
}

- (id) initWithData: (NSData *)epsData
{
  [self notImplemented: _cmd];

  _epsData = epsData;
  // Set bounds from parsed header
  //_bounds = NSMakeRect();
  return self;
}

// Getting Image Data 
- (NSRect) boundingBox
{
  return _bounds;
}

- (NSData *) EPSRepresentation
{
  return _epsData;
}

- (void) prepareGState
{
  // This is for subclasses only
}

// Drawing the Image 
- (BOOL) draw
{
  [self notImplemented: _cmd];

  [self prepareGState];

  return YES;
}

// NSCopying protocol
- (id) copyWithZone: (NSZone *)zone
{
  NSEPSImageRep *copy = [super copyWithZone: zone];

  copy->_epsData = [_epsData copyWithZone: zone];

  return copy;
}

// NSCoding protocol
- (void) encodeWithCoder: (NSCoder*)aCoder
{
  NSData *data = [self EPSRepresentation];

  [super encodeWithCoder: aCoder];
  [data encodeWithCoder: aCoder];

}

- (id) initWithCoder: (NSCoder*)aDecoder
{
  NSData	*data;

  self = [super initWithCoder: aDecoder];
  data = [aDecoder decodeObject];
  return [self initWithData: data];
}

@end
