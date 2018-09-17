package com.example.wzeqiu.myopengles1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.example.wzeqiu.myopengles1.es.ESGLSurfaceView;
import com.example.wzeqiu.myopengles1.es_native.Native;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);

        Native.InitAsseManager(getAssets());
        setContentView(new ESGLSurfaceView(this));
    }

}
