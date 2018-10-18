package com.example.wzeqiu.myopengles1.es.coordinate;

import android.content.Context;
import android.content.res.Resources;
import android.opengl.GLSurfaceView;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.MotionEvent;

import com.example.wzeqiu.myopengles1.es_native.coordinate.Native;

public class ESGLSurfaceView extends GLSurfaceView {
    private float getX;
    private float getY;

    private float scrWidth;
    private float scrHeight;

    private float deviationX;
    private float deviationY;

    public ESGLSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        setRenderer(new ESRenderer());
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        Resources resources = this.getResources();
        DisplayMetrics dm = resources.getDisplayMetrics();
        float density = dm.density;
        scrWidth = dm.widthPixels;
        scrHeight = dm.heightPixels;
        Log.e("ESGLSurfaceView ", "scrWidth>>> " + scrWidth);
        Log.e("ESGLSurfaceView ", "scrHeight>>> " + scrHeight);

    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                    getX = event.getRawX();
                    getY = event.getRawY();
                break;
            case MotionEvent.ACTION_MOVE:
                Log.e("ESGLSurfaceView ", "getX>>> " + getX);
                Log.e("ESGLSurfaceView ", "getY>>> " + getY);
//                if (getX - scrWidth / 2 > 0) {
//                    deviationX = 1 - (getX - scrWidth / 2) / (scrWidth / 2);
//                } else {
//                    deviationX = getX / (scrWidth / 2);
//                }
//
//                if (scrHeight / 2 - getY > 0) {
//                    deviationY = getY / (scrHeight / 2);
//                } else {
//                    deviationY = 1 - (getY - scrHeight / 2) / (scrHeight / 2);
//                }

                deviationX=getX/event.getRawX();
                deviationY=getY/event.getRawY();

                Log.e("ESGLSurfaceView ", "deviationX>>> " + deviationX);
                Log.e("ESGLSurfaceView ", "deviationY>>> " + deviationY);
//                deviationX = (float) (Math.round(deviationX * 100)) / 100;
//                deviationY = (float) (Math.round(deviationY * 100)) / 100;
                float chanage = (float) (Math.sqrt(getX * getX + getY * getY) % 360);
                Native.CoordinateChanage(chanage, deviationX, deviationY);
//                getX = event.getRawX();
//                getY = event.getRawY();
                break;
            case MotionEvent.ACTION_UP:
                break;
        }
        return true;
    }


}
