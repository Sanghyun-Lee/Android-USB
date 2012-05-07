package app.android.server;

import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.app.Instrumentation;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import app.android.server.R;
import app.android.IME.*;

import android.view.inputmethod.InputConnection;
import android.inputmethodservice.InputMethodService;

public class MessagePCViewerActivity extends Activity implements OnClickListener {
	
	Button sendBtn;
	Button connectBtn;
	Button closeBtn;
	static TextView tv;
	static EditText et;
	static LinearLayout view1;
	
	static MessageManager message;
	static RecvThread recvth;
	static SendThread sendth;
	static TCPconnect connect;
	static Handler handler;
	// private Intent intent_kakao;
	
	static SoftKeyboard mIME;
	
	// static InputMethodManager imm;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("ndk-chat");
        setContentView(R.layout.main);
        
        view1 = (LinearLayout) findViewById(R.id.linearLayout1);
        sendBtn = (Button) findViewById(R.id.button1);
        connectBtn = (Button) findViewById(R.id.connect_btn);
        closeBtn = (Button) findViewById(R.id.close_btn);
        tv = (TextView) findViewById(R.id.textView1);
        et = (EditText) findViewById(R.id.editText1);
        sendBtn.setOnClickListener(this);
        connectBtn.setOnClickListener(this);
        closeBtn.setOnClickListener(this);
        
        // imm = (InputMethodManager)getSystemService(INPUT_METHOD_SERVICE);
        // imm.showSoftInput(et, 0);
        // imm.hideSoftInputFromWindow(et.getWindowToken(), 0);
        // this.onKeyDown(KeyEvent.KEYCODE_BUTTON_B, new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_B));
        
        handler = new Handler() {
			public void handleMessage(Message msg) {
				insertEditText((String)msg.obj);
			}
		};
		
		connect = new TCPconnect();
        message = new MessageManager(handler, connect);
        
        mIME = new SoftKeyboard();

        /*
        intent_kakao = this.getPackageManager().getLaunchIntentForPackage("com.kakao.talk");
        MessagePCViewerActivity.this.startActivity(intent_kakao);
        */
        
        recvth = new RecvThread(message);
        sendth = new SendThread(message, view1.getRootView());
    }

	public void onClick(View v) {
		// TODO Auto-generated method stub
		// 추후 recv 한 후에 recv에서 sendPC함
		
		switch(v.getId()) {
			case R.id.button1 :
				// message.sendPC(et.getText().toString());
		    	addMessage(et.getText().toString());
		    	et.setText("");
				break;
		
			case R.id.connect_btn :
				connect.connect();
		        if(connect.isconnect()) {
		        	Toast.makeText(this, "연결에 성공했습니다.", Toast.LENGTH_LONG).show();
		        	recvth.start();
		        	sendth.start();
		        }
		        else {
		        	Toast.makeText(this, "연결에 실패했습니다.", Toast.LENGTH_LONG).show();
		        }
				break;
				
			case R.id.close_btn :
				// insertEditText("test");
				
				//test
				mIME.set_text("test");
				mIME.commit_text();
				
				// getCurrentInputConnection();
				// et.onKeyDown(KeyEvent.KEYCODE_B, new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_0));
				
				//test t = new test();
				//t.button_on();
				// InputMethodService.sendDownUpKeyEvents(KeyEvent.KEYCODE_F);
				
				// close connect
				// recvth.stop();
				
				break;
		}
	}
	
	public static int addMessage(String msg) {
    	if(msg!=null) {
	    	tv.setText(tv.getText() + "\n" + msg);
		}
    	return 0;
    }
	
	public static int insertEditText(String msg) {
		
		new Thread(new Runnable() {
			 public void run() {
				//test
					mIME.set_text("test");
					mIME.commit_text();
				 // new Instrumentation().sendKeyDownUpSync(KeyEvent.KEYCODE_G);
				 //KeyEvent ke = new KeyEvent(0, "dd", 0, 0);
				 //new Instrumentation().sendKeyDownUpSync(ke.getKeyCode());
			 }
		 }).start();
		return 0;
	}
	
}

class test extends InputMethodService {
	InputConnection ic;
	void InputMethodService() {
	}
	
	/*
	public void button_on() {
		ic = getCurrentInputConnection();
		long eventTime = SystemClock.uptimeMillis();
		ic.sendKeyEvent(new KeyEvent(eventTime, eventTime,
		    KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_BUTTON_A, 0, 0, 0, 0,
		    KeyEvent.FLAG_SOFT_KEYBOARD|KeyEvent.FLAG_KEEP_TOUCH_MODE));
		ic.sendKeyEvent(new KeyEvent(SystemClock.uptimeMillis(), eventTime,
		    KeyEvent.ACTION_UP, KeyEvent.KEYCODE_BUTTON_A, 0, 0, 0, 0,
		    KeyEvent.FLAG_SOFT_KEYBOARD|KeyEvent.FLAG_KEEP_TOUCH_MODE));
	}
	*/
}