package com.example.wzeqiu.myopengles1.es_native.coordinate;


public class Native {

    public static native void CoordinateInitOpenGL();

    public static native void CoordinateOnViewportChanged(float width, float height);

    public static native void CoordinateRenderOneFrame();

    public static native void CoordinateChanage(float angle, float chanageX, float chanageY);
}
