// MonoGame - Copyright (C) MonoGame Foundation, Inc
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

#pragma once

#include "api_common.h"

struct MGF_RuntimeFont;

enum MGF_RuntimeFontErrorCode
{
    MGF_RuntimeFontErrorCode_None = 0,
    MGF_RuntimeFontErrorCode_InvalidArgument = 1,
    MGF_RuntimeFontErrorCode_OutOfMemory = 2,
    MGF_RuntimeFontErrorCode_AtlasCapacityExceeded = 3,
    MGF_RuntimeFontErrorCode_NoGlyphData = 4,
    MGF_RuntimeFontErrorCode_Unknown = 5
};

struct MGF_CharacterRegion
{
    mgchar Start;
    mgchar End;
};

struct MGF_Glyph
{
    mgchar Character;
    mgint Size;
    mgint PageIndex;
    mgint BoundsX;
    mgint BoundsY;
    mgint BoundsWidth;
    mgint BoundsHeight;
    mgint CroppingX;
    mgint CroppingY;
    mgint CroppingWidth;
    mgint CroppingHeight;
    mgfloat LeftSideBearing;
    mgfloat Width;
    mgfloat RightSideBearing;
};

struct MGF_PageUpdate
{
    mgint PageIndex;
    mgbyte* AtlasRgba;
    mgint AtlasWidth;
    mgint AtlasHeight;
    mgbool AtlasRebuilt;
};

MG_EXPORT mgbool MGF_BakeSpriteFont(
    mgbyte* data,
    mgint dataBytes,
    mgint size,
    MGF_CharacterRegion* characterRegions,
    mgint characterRegionCount,
    mgbyte*& atlasRgba,
    mgint& atlasWidth,
    mgint& atlasHeight,
    MGF_Glyph*& glyphs,
    mgint& glyphCount,
    mgint& lineSpacing
);

MG_EXPORT MGF_RuntimeFont* MGF_RuntimeFont_Create(
    mgbyte* data,
    mgint dataBytes
);

MG_EXPORT void MGF_RuntimeFont_Destroy(
    MGF_RuntimeFont* runtimeFont
);

MG_EXPORT mgbool MGF_RuntimeFont_EnsureGlyphs(
    MGF_RuntimeFont* runtimeFont,
    mgint size,
    MGF_CharacterRegion* characterRegions,
    mgint characterRegionCount,
    MGF_PageUpdate*& pageUpdates,
    mgint& pageUpdateCount,
    MGF_Glyph*& glyphs,
    mgint& glyphCount,
    mgint& lineSpacing
);

MG_EXPORT mgint MGF_RuntimeFont_GetLastErrorCode(MGF_RuntimeFont* runtimeFont);

MG_EXPORT const char* MGF_RuntimeFont_GetLastErrorMessage(MGF_RuntimeFont* runtimeFont);

MG_EXPORT void MGF_Free(void* resource);
