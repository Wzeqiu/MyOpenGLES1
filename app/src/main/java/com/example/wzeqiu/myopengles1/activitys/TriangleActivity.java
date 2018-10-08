package com.example.wzeqiu.myopengles1.activitys;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.example.wzeqiu.myopengles1.es.triangle.ESGLSurfaceView;

public class TriangleActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new ESGLSurfaceView(this));
    }
}
