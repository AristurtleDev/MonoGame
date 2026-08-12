// MonoGame - Copyright (C) MonoGame Foundation, Inc
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

using System;
using Microsoft.Xna.Framework.Graphics;
using MonoGame.Interop;

namespace Microsoft.Xna.Framework;

public partial class GraphicsDeviceManager
{
    partial void PlatformInitialize(PresentationParameters presentationParameters)
    {
        NativeGameWindow window = _game.Window as NativeGameWindow;
        if (window == null)
            return;

        MGP_OpenGLWindowCreateInfo openGLCreateInfo = default;

        SurfaceFormat backBufferFormat = presentationParameters.BackBufferFormat;

        int rSize, gSize, bSize, aSize;
        switch (presentationParameters.BackBufferFormat)
        {
            case SurfaceFormat.Alpha8:
                rSize = 0;
                gSize = 0;
                bSize = 0;
                aSize = 8;
                break;
            case SurfaceFormat.Bgr565:
                rSize = 5;
                gSize = 6;
                bSize = 5;
                aSize = 0;
                break;
            case SurfaceFormat.Bgra4444:
                rSize = 4;
                gSize = 4;
                bSize = 4;
                aSize = 4;
                break;
            case SurfaceFormat.Bgra5551:
                rSize = 5;
                gSize = 5;
                bSize = 5;
                aSize = 1;
                break;
            case SurfaceFormat.Bgr32:
                rSize = 8;
                gSize = 8;
                bSize = 8;
                aSize = 0;
                break;
            case SurfaceFormat.Bgra32:
            case SurfaceFormat.Color:
            case SurfaceFormat.ColorSRgb:
                rSize = 8;
                gSize = 8;
                bSize = 8;
                aSize = 8;
                break;
            case SurfaceFormat.Rgba1010102:
                rSize = 10;
                gSize = 10;
                bSize = 10;
                aSize = 2;
                break;
            default:
                // Floating point backbuffers formats could be implemented
                // but they are not typically used on the backbuffer. In
                // those cases it is better to create a render target instead.
                throw new NotSupportedException();
        }

        openGLCreateInfo.RedSize = rSize;
        openGLCreateInfo.GreenSize = gSize;;
        openGLCreateInfo.BlueSize = aSize;
        openGLCreateInfo.AlphaSize = bSize;
        openGLCreateInfo.FramebufferSrgbCapable =
            backBufferFormat == SurfaceFormat.ColorSRgb ||
            backBufferFormat == SurfaceFormat.Bgr32SRgb ||
            backBufferFormat == SurfaceFormat.Bgra32SRgb ? 1 : 0;

        switch (presentationParameters.DepthStencilFormat)
        {
            case DepthFormat.None:
                openGLCreateInfo.DepthSize = 0;
                openGLCreateInfo.StencilSize = 0;
                break;
            case DepthFormat.Depth16:
                openGLCreateInfo.DepthSize = 16;
                openGLCreateInfo.StencilSize = 0;
                break;
            case DepthFormat.Depth24:
                openGLCreateInfo.DepthSize = 24;
                openGLCreateInfo.StencilSize = 0;
                break;
            case DepthFormat.Depth24Stencil8:
                openGLCreateInfo.DepthSize = 24;
                openGLCreateInfo.StencilSize = 8;
                break;
        }

        if (presentationParameters.MultiSampleCount > 0)
        {
            openGLCreateInfo.MultiSampleBuffers = 1;
            openGLCreateInfo.MultiSampleSamples = presentationParameters.MultiSampleCount;
        }

        window.CreateWindow(openGLCreateInfo);
        presentationParameters.DeviceWindowHandle = window.Handle;
    }
}
