package app.android.server;

import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.os.Bundle;
//import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import app.android.server.R;

public class MessagePCViewerActivity extends Activity implements OnClickListener {
	Button sendBtn;
	static TextView tv;
	static EditText et;
	static MessageManager message;
	static RecvThread recvth;
	static TCPconnect connect;
	static Handler handler;
	
	String IP = "192.168.0.60";
	int port = 3600;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("ndk-chat");
        setContentView(R.layout.main);
        
        sendBtn = (Button) findViewById(R.id.button1);
        tv = (TextView) findViewById(R.id.textView1);
        et = (EditText) findViewById(R.id.editText1);
        sendBtn.setOnClickListener(this);
        
        handler = new Handler() {
			public void handleMessage(Message msg) {
				addMessage((String)msg.obj);
			}
		};
        
        connect = new TCPconnect(IP, port);
        connect.connect();
        
        message = new MessageManager(handler, connect);
        recvth = new RecvThread(message);
        recvth.start();
    }

	public void onClick(View v) {
		// TODO Auto-generated method stub
		// 추후 recv 한 후에 recv에서 sendPC함
		message.sendPC(et.getText().toString());
    	addMessage(et.getText().toString());
    	et.setText("");
	}
	
	public static int addMessage(String msg) {
    	if(msg!=null) {
	    	tv.setText(tv.getText() + "\n" + msg);
		}
    	return 0;
    }
}