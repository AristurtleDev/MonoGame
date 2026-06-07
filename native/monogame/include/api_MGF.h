// MonoGame - Copyright (C) MonoGame Foundation, Inc
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

#pragma once

#include "api_common.h"

// Opaque runtime font handle used by incremental glyph baking API.
struct MGF_RuntimeFont;

// Stable result codes returned by the explicit runtime font contract.
enum MGF_ResultCode
{
    MGF_ResultCode_Success = 0,
    MGF_ResultCode_InvalidArgument = 1,
    MGF_ResultCode_InvalidFontData = 2,
    MGF_ResultCode_OutOfMemory = 3,
    MGF_ResultCode_BackendInitializationFailed = 4,
    MGF_ResultCode_FontSizeSetupFailed = 5,
    MGF_ResultCode_GlyphLoadFailed = 6,
    MGF_ResultCode_GlyphRenderFailed = 7,
    MGF_ResultCode_UnsupportedGlyphBitmapFormat = 8,
    MGF_ResultCode_AtlasCapacityExceeded = 9,
    MGF_ResultCode_NoGlyphData = 10,
    MGF_ResultCode_InternalError = 11
};


// Inclusive Unicode character range.
struct MGF_CharacterRegion
{
    mgchar Start;
    mgchar End;
};

// Glyph metrics and atlas placement returned to managed code.
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

// Atlas data returned for each page touched by the current runtime glyph update.
struct MGF_PageUpdate
{
    mgint PageIndex;
    mgbyte* AtlasRgba;
    mgint AtlasWidth;
    mgint AtlasHeight;
    mgbool AtlasRebuilt;
};

/**
 * Bakes a traditional SpriteFont atlas in one call
 *
 * This is a convenience wrapper over the runtime font API for callers that only need a single
 * atlas page.  On success `atlasRgba` and `glyphs` are newly allocated buffers owned by the
 * caller and must be released with MGF_Free.  The function fails if the requested glyph set would
 * require more than one atlas page.
 *
 * @param data Pointer to the font file bytes.
 * @param dataBytes Number of bytes available at `data`.
 * @param size Requested glyph height in pixels. Must be greater than zero.
 * @param characterRegions Inclusive character ranges to bake.
 * @param characterRegionCount Number of entries in `characterRegions`.
 * @param atlasRgba Receives a tightly packed RGBA atlas buffer on success.
 * @param atlasWidth Receives the atlas width in pixels.
 * @param atlasHeight Receives the atlas height in pixels.
 * @param glyphs Receives the baked glyph metrics on success.
 * @param glyphCount Receives the number of entries written to `glyphs`.
 * @param lineSpacing Receives the font line spacing in pixels for `size`.
 * @return `MGF_ResultCode_Success` when the font data was valid and the baked glyph set fit
 * within one atlas page.
 */
MG_EXPORT MGF_ResultCode MGF_BakeSpriteFont(
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

/**
 * Creates a runtime font handle for incremental glyph baking.
 *
 * The function copies the provided font bytes so the caller may release the original buffer after
 * this call returns.  The returned handle must be destroyed with MGF_RuntimeFont_Destroy.
 *
 * @param data Pointer to the font file bytes.
 * @param dataBytes Number of byte available in `data`.
 * @param runtimeFont Receives a fully initialized runtime font handle on success.
 * @return `MGF_ResultCode_Success` on success; otherwise returns  non-success result and leaves
 * `runtimeFont` as `nullptr`.
 */
MG_EXPORT MGF_ResultCode MGF_RuntimeFont_Create(
    mgbyte* data,
    mgint dataBytes,
    MGF_RuntimeFont*& runtimeFont
);

// Releases a handle created by MGF_RuntimeFont_Create. Passing `nullptr` is allowed.
MG_EXPORT void MGF_RuntimeFont_Destroy(
    MGF_RuntimeFont* runtimeFont
);

/**
 * Ensures that the requested characters exist in the runtime atlas for a given size.
 *
 * Duplicate and overlapping character regions are merged before glyph generation.  On success,
 * `pageUpdates` points to the atlas pages touched by this call and `glyphs` points to the full
 * baked glyph set currently owned by `runtimeFont`.  Those pointers remain valid until the next
 * call that mutates `runtimeFont` or until MGF_RuntimeFont_Destroy is called.
 *
 * @param runtimeFont Runtime font handle created by MGF_RuntimeFont_Create.
 * @param size Requested glyph height in pixels. Must be greater than zero.
 * @param characterRegions Inclusive character ranges to bake.
 * @param characterRegionCount Number of entries in `characterRegions`.
 * @param pageUpdates Receives the touched atlas pages for this call.
 * @param glyphs Receives the complete glyph table currently cached by `runtimeFont`.
 * @param glyphCount Receives the number of entries written to `glyphs`.
 * @param lineSpacing Receives the font line spacing in pixels for `size`.
 * @return `MGF_Result_Code_Success` when the glyph request completed successfully;
 * otherwise returns a non-success result and leaves all output data clear.
 */
MG_EXPORT MGF_ResultCode MGF_RuntimeFont_EnsureGlyphs(
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

// Releases buffers returned by MGF_BakeSpriteFont.  Passing `nullptr` is allowed.
MG_EXPORT void MGF_Free(void* resource);
