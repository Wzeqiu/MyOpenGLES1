package com.example.wzeqiu.myopengles1.es_native.triangle;


public class Native {

    public static native void TriangleInitOpenGL();

    public static native void TriangleOnViewportChanged(float width, float height);

    public static native void TriangleRenderOneFrame();
}
