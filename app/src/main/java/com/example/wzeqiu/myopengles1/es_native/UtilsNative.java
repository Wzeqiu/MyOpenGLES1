package com.example.wzeqiu.myopengles1.es_native;

import android.content.res.AssetManager;

public class UtilsNative {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("opengles");
    }
    public static native void InitAsseManager(AssetManager am);
}
