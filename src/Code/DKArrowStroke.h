///**********************************************************************************************************************************
///  DKArrowStroke.h
///  DrawKit ©2005-2008 Apptree.net
///
///  Created by graham on 20/03/2007.
///
///	 This software is released subject to licensing conditions as detailed in DRAWKIT-LICENSING.TXT, which must accompany this source file. 
///
///**********************************************************************************************************************************

#import "DKStroke.h"


// arrow head kinds - each end can be specified independently:

typedef enum
{
	kDKArrowHeadNone					= 0,
	kDKArrowHeadStandard				= 1,
	kDKArrowHeadInflected				= 2,
	kDKArrowHeadRound					= 3,
	kDKArrowHeadSingleFeather			= 4,
	kDKArrowHeadDoubleFeather			= 5,
	kDKArrowHeadTripleFeather			= 6,
	kDKArrowHeadDimensionLine			= 7,
	kDKArrowHeadDimensionLineAndBar		= 8,
	kDKArrowHeadSquare					= 9,
	kDKArrowHeadDiamond					= 10
}
DKArrowHeadKind;


// positioning of dimension label, or none:

typedef enum
{
	kDKDimensionNone					= 0,
	kDKDimensionPlaceAboveLine			= 1,
	kDKDimensionPlaceInLine				= 2,
	kDKDimensionPlaceBelowLine			= 3
}
DKDimensioningLineOptions;

// dimension kind - sets additional embellishments on the dimension text:

typedef enum
{
	kDKDimensionLinear					= 0,
	kDKDimensionDiameter				= 1,
	kDKDimensionRadius					= 2,
	kDKDimensionAngle					= 3
}
DKDimensionTextKind;

// tolerance options:

typedef enum
{
	kDKDimensionToleranceNotShown		= 0,
	kDKDimensionToleranceShown			= 1
}
DKDimensionToleranceOption;

// the class:

@interface DKArrowStroke : DKStroke <NSCoding, NSCopying>
{
@private
	DKArrowHeadKind				mArrowHeadAtStart;
	DKArrowHeadKind				mArrowHeadAtEnd;
	CGFloat						m_arrowLength;
	CGFloat						m_arrowWidth;
	DKDimensioningLineOptions	mDimensionOptions;
	NSNumberFormatter*			m_dims_formatter;
	NSColor*					m_outlineColour;
	CGFloat						m_outlineWidth;
	DKDimensionTextKind			mDimTextKind;
	DKDimensionToleranceOption	mDimToleranceOptions;
}

+ (void)						setDimensioningLineTextAttributes:(NSDictionary*) attrs;
+ (NSDictionary*)				dimensioningLineTextAttributes;
+ (DKArrowStroke*)				standardDimensioningLine;
+ (NSNumberFormatter*)			defaultDimensionLineFormatter;

// head kind at each end

- (void)						setArrowHeadAtStart:(DKArrowHeadKind) kind;
- (void)						setArrowHeadAtEnd:(DKArrowHeadKind) kind;
- (DKArrowHeadKind)				arrowHeadAtStart;
- (DKArrowHeadKind)				arrowHeadAtEnd;

// head widths and lengths (some head kinds may set these also)

- (void)						setArrowHeadWidth:(CGFloat) width;
- (CGFloat)						arrowHeadWidth;
- (void)						setArrowHeadLength:(CGFloat) length;
- (CGFloat)						arrowHeadLength;

- (void)						standardArrowForStrokeWidth:(CGFloat) sw;

#ifdef DRAWKIT_DEPRECATED
- (void)						setOutlineColour:(NSColor*) colour width:(CGFloat) width;
#endif

- (void)						setOutlineColour:(NSColor*) colour;
- (NSColor*)					outlineColour;
- (void)						setOutlineWidth:(CGFloat) width;
- (CGFloat)						outlineWidth;

- (NSImage*)					arrowSwatchImageWithSize:(NSSize) size strokeWidth:(CGFloat) width;
- (NSImage*)					standardArrowSwatchImage;

- (NSBezierPath*)				arrowPathFromOriginalPath:(NSBezierPath*) inPath fromObject:(id) obj;

// dimensioning lines:

- (void)						setFormatter:(NSNumberFormatter*) fmt;
- (NSNumberFormatter*)			formatter;
- (void)						setFormat:(NSString*) format;

- (void)						setDimensioningLineOptions:(DKDimensioningLineOptions) dimOps;
- (DKDimensioningLineOptions)	dimensioningLineOptions;

- (NSAttributedString*)			dimensionTextForObject:(id) obj;
- (CGFloat)						widthOfDimensionTextForObject:(id) obj;
- (NSString*)					toleranceTextForObject:(id) object;

- (void)						setDimensionTextKind:(DKDimensionTextKind) kind;
- (DKDimensionTextKind)			dimensionTextKind;

- (void)						setDimensionToleranceOption:(DKDimensionToleranceOption) option;
- (DKDimensionToleranceOption)	dimensionToleranceOption;

- (void)						setTextAttributes:(NSDictionary*) dict;
- (NSDictionary*)				textAttributes;
- (void)						setFont:(NSFont*) font;
- (NSFont*)						font;

@end

// informal protocol for requesting dimension information from an object. If it does not respond, the rasterizer infers the values from the path length and
// its internal values.

@interface NSObject (DKArrowSrokeDimensioning)

- (NSDictionary*)				dimensionValuesForArrowStroke:(DKArrowStroke*) arrowStroke;

@end


#define			kDKStandardArrowSwatchImageSize		(NSMakeSize( 80.0, 9.0 ))
#define			kDKStandardArrowSwatchStrokeWidth	3.0

extern NSString*				kDKPositiveToleranceKey;
extern NSString*				kDKNegativeToleranceKey;
extern NSString*				kDKDimensionValueKey;
extern NSString*				kDKDimensionUnitsKey;

/*

DKArrowStroke is a rasterizer that implements arrowheads on the ends of paths. The heads are drawn by filling the
arrowhead using the same colour as the stroke, thus seamlessly blending the head into the path. Where multiple
strokes are used, the resulting effect should be correct when angles are kept the same and lengths are calculated
from the stroke width.

*/
