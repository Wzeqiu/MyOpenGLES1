package com.example.wzeqiu.myopengles1.activitys;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.example.wzeqiu.myopengles1.R;
import com.example.wzeqiu.myopengles1.es.shadder.ESGLSurfaceView;

public class ShadderActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new ESGLSurfaceView(this));
    }
}
