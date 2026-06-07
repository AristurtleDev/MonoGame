// MonoGame - Copyright (C) MonoGame Foundation, Inc
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

using System.Runtime.InteropServices;

namespace MonoGame.Interop;

[MGHandle]
internal readonly struct MGF_RuntimeFont
{
}

internal enum MGF_ResultCode
{
    Success = 0,
    InvalidArgument = 1,
    InvalidFontData = 2,
    OutOfMemory = 3,
    BackendInitializationFailed = 4,
    FontSizeSetupFailed = 5,
    GlyphLoadFailed = 6,
    GlyphRenderFailed = 7,
    UnsupportedGlyphBitmapFormat = 8,
    AtlasCapacityExceeded = 9,
    NoGlyphData = 10,
    InternalError = 11
}

[StructLayout(LayoutKind.Sequential)]
internal struct MGF_CharacterRegion
{
    public char Start;
    public char End;
}

[StructLayout(LayoutKind.Sequential)]
internal struct MGF_Glyph
{
    public char Character;
    public int Size;
    public int PageIndex;
    public int BoundsX;
    public int BoundsY;
    public int BoundsWidth;
    public int BoundsHeight;
    public int CroppingX;
    public int CroppingY;
    public int CroppingWidth;
    public int CroppingHeight;
    public float LeftSideBearing;
    public float Width;
    public float RightSideBearing;
}

[StructLayout(LayoutKind.Sequential)]
internal unsafe struct MGF_PageUpdate
{
    public int PageIndex;
    public byte* AtlasRgba;
    public int AtlasWidth;
    public int AtlasHeight;
    [MarshalAs(UnmanagedType.U1)]
    public bool AtlasRebuilt;
}

internal static unsafe class MGF
{
    [DllImport(MGP.MonoGameNativeDLL, EntryPoint = "MGF_RuntimeFont_Create", ExactSpelling = true)]
    public static extern MGF_ResultCode RuntimeFont_Create(byte* data, int dataBytes, out MGF_RuntimeFont* runtimeFont);

    [DllImport(MGP.MonoGameNativeDLL, EntryPoint = "MGF_RuntimeFont_Destroy", ExactSpelling = true)]
    public static extern void RuntimeFont_Destroy(MGF_RuntimeFont* runtimeFont);

    [DllImport(MGP.MonoGameNativeDLL, EntryPoint = "MGF_RuntimeFont_EnsureGlyphs", ExactSpelling = true)]
    public static extern MGF_ResultCode RuntimeFont_EnsureGlyphs(MGF_RuntimeFont* runtimeFont,
                                                                 int size,
                                                                 MGF_CharacterRegion* characterRegions,
                                                                 int characterRegionCount,
                                                                 out MGF_PageUpdate* pageUpdates,
                                                                 out int pageUpdateCount,
                                                                 out MGF_Glyph* glyphs,
                                                                 out int glyphCount,
                                                                 out int lineSpacing);

    [DllImport(MGP.MonoGameNativeDLL, EntryPoint = "MGF_BakeSpriteFont", ExactSpelling = true)]
    public static extern MGF_ResultCode BakeSpriteFont(byte* data,
                                                       int dataBytes,
                                                       int size,
                                                       MGF_CharacterRegion* characterRegions,
                                                       int characterRegionCount,
                                                       out byte* atlasRgba,
                                                       out int atlasWidth,
                                                       out int atlasHeight,
                                                       out MGF_Glyph* glyphs,
                                                       out int glyphCount,
                                                       out int lineSpacing);

    [DllImport(MGP.MonoGameNativeDLL, EntryPoint = "MGF_Free", ExactSpelling = true)]
    public static extern void Free(void* resource);
}
