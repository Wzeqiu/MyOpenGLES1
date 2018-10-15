package com.example.wzeqiu.myopengles1.activitys;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.example.wzeqiu.myopengles1.es.position_change.ESGLSurfaceView;

public class PositionChanageActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new ESGLSurfaceView(this));
    }
}
