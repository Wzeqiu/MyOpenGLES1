package com.example.wzeqiu.myopengles1.es_native.textures;


public class Native {
    
    public static native void TextureInitOpenGL();

    public static native void TextureOnViewportChanged(float width, float height);

    public static native void TextureRenderOneFrame();
}
