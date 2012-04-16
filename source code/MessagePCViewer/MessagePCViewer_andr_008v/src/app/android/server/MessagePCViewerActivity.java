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
import org.kandroid.app.hangulkeyboard.*;

import android.view.inputmethod.InputConnection;
import android.inputmethodservice.InputMethodService;

public class MessagePCViewerActivity extends Activity {
	
	/*
	Button sendBtn;
	Button connectBtn;
	Button closeBtn;
	static LinearLayout view1;
	static TextView tv;
	static EditText et;
	*/
	
	static MessageManager message;
	
	static SendThread sendth;
	static TCPconnect connect;
	static Handler handler;
	
	static Intent intent_kakao;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("ndk-chat");
        
        setContentView(R.layout.main);
        
        /*
        view1 = (LinearLayout) findViewById(R.id.linearLayout1);
        sendBtn = (Button) findViewById(R.id.button1);
        connectBtn = (Button) findViewById(R.id.connect_btn);
        closeBtn = (Button) findViewById(R.id.close_btn);
        et = (EditText) findViewById(R.id.editText1);
        tv = (TextView) findViewById(R.id.textView1);
        
        sendBtn.setOnClickListener(this);
        connectBtn.setOnClickListener(this);
        closeBtn.setOnClickListener(this);
        */
        
        // imm = (InputMethodManager)getSystemService(INPUT_METHOD_SERVICE);
        // imm.showSoftInput(et, 0);
        // imm.hideSoftInputFromWindow(et.getWindowToken(), 0);
        // this.onKeyDown(KeyEvent.KEYCODE_BUTTON_B, new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_B));
        
        /*
        handler = new Handler() {
			public void handleMessage(Message msg) {
				insertEditText((String)msg.obj);
			}
		};
		*/
		
        // message = new MessageManager(handler, connect);
        
        // mIME = new SoftKeyboard();
        
        
        // sendth = new SendThread(message, view1.getRootView());
        
        startService(new Intent(this, MessageManager.class));
        intent_kakao = this.getPackageManager().getLaunchIntentForPackage("com.kakao.talk");
        MessagePCViewerActivity.this.startActivity(intent_kakao);
    }

    /*
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
		        	// sendth.start();
		        }
		        else {
		        	Toast.makeText(this, "연결에 실패했습니다.", Toast.LENGTH_LONG).show();
		        }
				break;
				
			case R.id.close_btn :
				// insertEditText("test");
				
				//test
				insertEditText("test");
				
				
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
	*/
	
	public static int addMessage(String msg) {
    	if(msg!=null) {
	    	//tv.setText(tv.getText() + "\n" + msg);
		}
    	return 0;
    }
	
	
	
//	public void IMEconnect() {
//		try {
//			socket = new Socket("127.0.0.1", 3700);
//			out = new BufferedOutputStream(socket.getOutputStream());
//		} catch (Exception e) {
//			// error
//			e.printStackTrace();
//		}
//	}
//	
//	public void IMEsend() {
//		String str = "테스트";
//		try {
//			out.write(str.getBytes());
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}

}