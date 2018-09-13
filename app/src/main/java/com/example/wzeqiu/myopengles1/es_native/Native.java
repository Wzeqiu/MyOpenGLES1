package com.example.wzeqiu.myopengles1.es_native;

import android.content.res.AssetManager;

public class Native {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("opengles");
    }

    public static native void InitAsseManager(AssetManager am);
    public static native void InitOpenGL();
    public static native void OnViewportChanged(float width,float height);
    public static native void RenderOneFrame();
}
