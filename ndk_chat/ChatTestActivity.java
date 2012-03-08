package test.chat;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class ChatTestActivity extends Activity implements OnClickListener {
	Button sendBtn;
	static TextView tv;
	static EditText et;
	Message msg;
	RecvThr recvThread;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("ndk-chat");
        setContentView(R.layout.main);
        
        sendBtn = (Button) findViewById(R.id.button1);
        tv = (TextView) findViewById(R.id.textView1);
        et = (EditText) findViewById(R.id.editText1);
        msg = new Message();
        msg.set("223.194.156.28", 3600);
        recvThread = new RecvThr();
        recvThread.start();
        
        sendBtn.setOnClickListener(this);
    }
    
    public void onClick(View v) {
    	msg.send(et.getText().toString());
    	addMessage(et.getText().toString());
    	et.setText("");
    }
    
    public static void addMessage(String msg) {
    	if(msg!=null) {
    		String str = tv.getText() + "\n" + msg;
	    	tv.setText(str);
		}
    }
}