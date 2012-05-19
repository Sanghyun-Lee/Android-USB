package app.android.ltouchpad;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

public class LTouchpadActivity extends Activity{
	private FrameLayout frameTouch;
	private float x1;
	private float y1;
	private boolean isTouchMove;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        frameTouch = (FrameLayout)findViewById(R.id.frame_touch);
        frameTouch.setOnTouchListener(TouchListener);
    }
    
    public void onButtonDown(View v) {
    	switch(v.getId()) {
    	case R.id.btn_left :
    		Log.d("LTouchPad", "OnLButtonDown");
    		break;
    	case R.id.btn_right :
    		Log.d("LTouchPad", "OnRButtonDown");
    		break;
    	default :
    		break;
    	}
    }

    public OnTouchListener TouchListener = new OnTouchListener() {
    	public boolean onTouch(View v, MotionEvent event) {
    		Log.d("LTouchPad", "onTouch : " + event.getAction());
    		switch(event.getAction()) {
    		case MotionEvent.ACTION_DOWN :
    			Log.d("LTouchPad", "OnTouch : DOWN");
    			isTouchMove = false;
    			return true;
    		case MotionEvent.ACTION_MOVE :
    			float x2 = event.getX();
    			float y2 = event.getY();
    			Log.d("LTouchPad", "OnTouch : MOVE / (" + x2 +","+y2+")"
    					+ " / (x2,y2)-(x1,y1)=("+(x2-x1)+","+(y2-y1)+")");
    			x1 = x2;
    			y1 = y2;
    			isTouchMove = true;
    			return true;
    		case MotionEvent.ACTION_UP :
    			Log.d("LTouchPad", "OnTouch : UP");
    			if(!isTouchMove) {
    				// Click Event
    				Log.d("LTouchPad", "OnTouch : Click Event");
    			}
    			return true;
    		default :
    			return false;
    		}
    	}
    };
}