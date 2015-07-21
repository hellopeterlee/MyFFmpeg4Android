package com.example.myffmpeg4android;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import com.example.myffmpeg4android.utils.FFmpegNative;


public class MainActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        TextView tv = (TextView)this.findViewById(R.id.textview_hello);
		
		FFmpegNative ffmpeg = new FFmpegNative();
		int codecID = 28;
		
		int res = ffmpeg.avcodec_find_decoder(codecID);
		
		if (res ==0) {
			tv.setText("Success!" + ffmpeg.avcodec_version());
		}
		else {
			tv.setText("Failed!"+ ffmpeg.avcodec_version());
		}
    }
}
