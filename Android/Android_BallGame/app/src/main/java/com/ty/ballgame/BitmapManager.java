package com.ty.ballgame;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;

public class BitmapManager {
    public static final int cImageIndexBack = 0;
    public static final int cImageIndexBall = 2;
    public static final int cImageIndexBallDie = 3;
    public static final int cImageIndexBtnPlay = 25;
    public static final int cImageIndexBtnRank = 26;
    public static final int cImageIndexCambelC = 5;
    public static final int cImageIndexCambelL = 4;
    public static final int cImageIndexCambelR = 6;
    public static final int cImageIndexGameOver = 7;
    public static final int cImageIndexJumpNavi1 = 8;
    public static final int cImageIndexJumpNavi2 = 9;
    public static final int cImageIndexMedalBron = 10;
    public static final int cImageIndexMedalGold = 12;
    public static final int cImageIndexMedalPla = 13;
    public static final int cImageIndexMedalSil = 11;
    public static final int cImageIndexNew = 14;
    public static final int cImageIndexNum0 = 15;
    public static final int cImageIndexNum1 = 16;
    public static final int cImageIndexNum2 = 17;
    public static final int cImageIndexNum3 = 18;
    public static final int cImageIndexNum4 = 19;
    public static final int cImageIndexNum5 = 20;
    public static final int cImageIndexNum6 = 21;
    public static final int cImageIndexNum7 = 22;
    public static final int cImageIndexNum8 = 23;
    public static final int cImageIndexNum9 = 24;
    public static final int cImageIndexReadyGo = 27;
    public static final int cImageIndexSNum0 = 29;
    public static final int cImageIndexSNum1 = 30;
    public static final int cImageIndexSNum2 = 31;
    public static final int cImageIndexSNum3 = 32;
    public static final int cImageIndexSNum4 = 33;
    public static final int cImageIndexSNum5 = 34;
    public static final int cImageIndexSNum6 = 35;
    public static final int cImageIndexSNum7 = 36;
    public static final int cImageIndexSNum8 = 37;
    public static final int cImageIndexSNum9 = 38;
    public static final int cImageIndexScoreBoard = 28;
    public static final int cImageIndexSprash = 1;
    public static final int cImageIndexTTS = 40;
    public static final int cImageIndexTitle = 39;
    public static final int cResScreenHeight = 400;
    public static final int cResScreenWidth = 240;
    public static int cScreenHeight = cResScreenHeight;
    public static int cScreenWidth = cResScreenWidth;
    private static Bitmap m_bitmap = null;

    public static void setBitmap(Bitmap bitmap){
        m_bitmap = bitmap;
    }

    public static void setDisplaySize(int width, int height){
        cScreenWidth = width;
        cScreenHeight = height;
    }


    public static int GetCipher(int _iInput) {
        int iRet = 0;
        while (_iInput / 10 != 0) {
            _iInput /= 10;
            iRet++;
        }
        return iRet;
    }

    public static void DrawBitmapNumber(Canvas canvas, int iNumber) {
        int iMaxDemical = GetCipher(iNumber);
        int iCount = 0;
        while (true) {
            DrawBitmap(canvas, (iNumber % 10) + cImageIndexNum0, (float) ((120 - (((iMaxDemical + 1) * 42) / 2)) + ((iMaxDemical - iCount) * 42)), 65.0f);
            if (iNumber / 10 != 0) {
                iNumber /= 10;
                iCount++;
            } else {
                return;
            }
        }
    }

    public static void DrawBitmapSmallNumber(Canvas canvas, int iNumber, int x, int y, boolean bBest) {
        int iCount = 0;
        while (true) {
            DrawBitmap(canvas, (iNumber % 10) + cImageIndexSNum0, (float) (x - (iCount * 19)), (float) y);
            if (iNumber / 10 == 0) {
                break;
            }
            iNumber /= 10;
            iCount++;
        }
        if (bBest) {
            DrawBitmap(canvas, 14, (float) ((x - (iCount * 19)) - 32), (float) y);
        }
    }

    public static void DrawBitmap(Canvas canvas, int iImageIndex, float x, float y) {
        int iWidth = 0;
        int iHeight = 0;
        int iLeft = 0;
        int iTop = 0;
        switch (iImageIndex) {
            case cImageIndexBack :
                iLeft = 2;
                iTop = 2;
                iWidth = cResScreenWidth;
                iHeight = cResScreenHeight;
                break;
            case cImageIndexSprash:
                iLeft = 244;
                iTop = 2;
                iWidth = cResScreenWidth;
                iHeight = cResScreenHeight;
                break;
            case cImageIndexBall :
                iLeft = 483;
                iTop = 549;
                iWidth = 25;
                iHeight = 25;
                break;
            case cImageIndexBallDie :
                iLeft = 483;
                iTop = 522;
                iWidth = 25;
                iHeight = 25;
                break;
            case cImageIndexCambelL :
                iLeft = 486;
                iTop = 84;
                iWidth = 20;
                iHeight = 20;
                break;
            case cImageIndexCambelC :
                iLeft = 486;
                iTop = 62;
                iWidth = 20;
                iHeight = 20;
                break;
            case cImageIndexCambelR :
                iLeft = 486;
                iTop = 40;
                iWidth = 20;
                iHeight = 20;
                break;
            case cImageIndexGameOver :
                iLeft = 2;
                iTop = 466;
                iWidth = 174;
                iHeight = 78;
                break;
            case cImageIndexJumpNavi1 :
                iLeft = 422;
                iTop = 465;
                iWidth = 82;
                iHeight = 55;
                break;
            case cImageIndexJumpNavi2 :
                iLeft = 422;
                iTop = 404;//WalletConstants.ERROR_CODE_INVALID_PARAMETERS;
                iWidth = 82;
                iHeight = 59;
                break;
            case cImageIndexMedalBron :
                iLeft = 451;
                iTop = 602;
                iWidth = 49;
                iHeight = 38;
                break;
            case cImageIndexMedalSil :
                iLeft = 178;
                iTop = 466;
                iWidth = 49;
                iHeight = 38;
                break;
            case cImageIndexMedalGold:
                iLeft = cResScreenHeight;
                iTop = 602;
                iWidth = 49;
                iHeight = 38;
                break;
            case cImageIndexMedalPla :
                iLeft = 178;
                iTop = 506;
                iWidth = 49;
                iHeight = 40;
                break;
            case cImageIndexNew:
                iLeft = 170;
                iTop = 584;
                iWidth = 30;
                iHeight = 12;
                break;
            case cImageIndexNum0:
                iLeft = 128;
                iTop = 584;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum1:
                iLeft = 486;
                iTop = 2;
                iWidth = 22;
                iHeight = 36;
                break;
            case cImageIndexNum2 /*17*/:
                iLeft = 86;
                iTop = 584;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum3 /*18*/:
                iLeft = 44;
                iTop = 584;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum4:
                iLeft = 2;
                iTop = 584;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum5:
                iLeft = 170;
                iTop = 546;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum6 /*21*/:
                iLeft = 128;
                iTop = 546;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum7 /*22*/:
                iLeft = 86;
                iTop = 546;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum8 /*23*/:
                iLeft = 44;
                iTop = 546;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexNum9 /*24*/:
                iLeft = 2;
                iTop = 546;
                iWidth = 40;
                iHeight = 36;
                break;
            case cImageIndexBtnPlay:
                iLeft = cResScreenHeight;
                iTop = 562;
                iWidth = 81;
                iHeight = 38;
                break;
            case cImageIndexBtnRank /*26*/:
                iLeft = cResScreenHeight;
                iTop = 522;
                iWidth = 81;
                iHeight = 38;
                break;
            case cImageIndexReadyGo /*27*/:
                iLeft = 230;
                iTop = 404;//WalletConstants.ERROR_CODE_INVALID_PARAMETERS;
                iWidth = 190;
                iHeight = 82;
                break;
            case cImageIndexScoreBoard /*28*/:
                iLeft = 229;
                iTop = 500;
                iWidth = 169;
                iHeight = 107;
                break;
            case cImageIndexSNum0 /*29*/:
                iLeft = 486;
                iTop = 242;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum1 /*30*/:
                iLeft = 486;
                iTop = 259;
                iWidth = 8;
                iHeight = 15;
                break;
            case cImageIndexSNum2 /*31*/:
                iLeft = 486;
                iTop = 225;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum3:
                iLeft = 486;
                iTop = 208;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum4 /*33*/:
                iLeft = 486;
                iTop = 191;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum5 /*34*/:
                iLeft = 486;
                iTop = 174;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum6 /*35*/:
                iLeft = 486;
                iTop = 157;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum7 /*36*/:
                iLeft = 486;
                iTop = 140;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum8 /*37*/:
                iLeft = 486;
                iTop = 123;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexSNum9 /*38*/:
                iLeft = 486;
                iTop = 106;
                iWidth = 17;
                iHeight = 15;
                break;
            case cImageIndexTitle /*39*/:
                iLeft = 2;
                iTop = 406;//WalletConstants.ERROR_CODE_INVALID_PARAMETERS;
                iWidth = 226;
                iHeight = 60;
                break;
            case cImageIndexTTS /*40*/:
                iLeft = 229;
                iTop = 488;
                iWidth = 172;
                iHeight = 10;
                break;
        }
        float fFillterX = ((float) cScreenWidth) / 240.0f;
        float fFillterY = ((float) cScreenHeight) / 400.0f;
        x *= fFillterX;
        y *= fFillterY;
        Rect rcSrc = new Rect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
        RectF rcDest = new RectF(x, y, (((float) iWidth) * fFillterX) + x, (((float) iHeight) * fFillterY) + y);
        Paint paint = new Paint();
        /*
        if (m_bUserGlobalAlpha && iImageIndex == 0) {
            paint.setAlpha(m_iGlobalAlpha);
        } else {
            paint.setAlpha(iAlpha);
        }
        */
        canvas.drawBitmap(m_bitmap, rcSrc, rcDest, null);
    }

}
