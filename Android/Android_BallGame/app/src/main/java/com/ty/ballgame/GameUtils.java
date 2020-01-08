package com.ty.ballgame;

import android.app.Activity;
import android.content.Context;
import android.util.DisplayMetrics;

import java.util.Random;

public class GameUtils {

    public static int getWidth(Context context){
        DisplayMetrics displayMetrics = new DisplayMetrics();
        ((Activity)context).getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        return displayMetrics.widthPixels;
    }

    public static int getHeight(Context context){
        DisplayMetrics displayMetrics = new DisplayMetrics();
        ((Activity)context).getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        return displayMetrics.heightPixels;
    }

    public static int makeRandom(int from, int to){
        return (int)(Math.random() * (to - from + 1)) + from;
    }

}
