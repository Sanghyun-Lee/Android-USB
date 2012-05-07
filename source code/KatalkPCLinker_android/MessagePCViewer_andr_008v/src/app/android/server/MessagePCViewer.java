package app.android.server;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import app.android.server.R;

public class MessagePCViewer extends Activity {
	
	private static final String basicIP = "192.168.0.15"; // test ip
	private EditText ipEdit;
	private TextView ipText;
	
	private static TCPconnect connect;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("ndk-chat");
        
        setContentView(R.layout.main);
        
        ipEdit = (EditText) findViewById(R.id.ip_edit);
        ipText = (TextView) findViewById(R.id.ip_text);
        
        startService(new Intent(this, MessageManager.class));
        ipText.setText(basicIP);
    }

    public void mBtnClick(View v) {
    	switch(v.getId()) {
    	case R.id.ipset_btn :
    		ipText.setText(ipEdit.getText());
    		break;
    	case R.id.connect_btn :
    		connect = new TCPconnect(ipText.getText().toString());
    		connect.connect();
    		if(connect.isconnect()) {
    			Toast.makeText(this, "연결에 성공했습니다.", Toast.LENGTH_LONG).show();
    			MessageManager.setConnect(connect);
    		}
    		break;
    	case R.id.test_btn :
    		break;
    	default :
    		break;
    	}
    }
}