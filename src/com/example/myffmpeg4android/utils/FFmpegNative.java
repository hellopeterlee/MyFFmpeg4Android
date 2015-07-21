package com.example.myffmpeg4android.utils;

public class FFmpegNative {
	
	static {
		//System.loadLibrary("ffmpeg");
		System.loadLibrary("myffmpeg");
	}
	
	public native int avcodec_find_decoder(int codecID);
	public native String avcodec_version();
}
