package app.android.server;

import java.net.Socket;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import app.android.server.R;

public class MessagePCViewer extends Activity {
	// private static final String basicIP = "192.168.0.15"; // test ip
	private static int port = 3600;
	private static String myIP;
	private static TextView ipText;
	public static Handler handler;
	
	private static TCPconnect connect;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("ndk-chat");
        
        setContentView(R.layout.main);
        
        // ipEdit = (EditText) findViewById(R.id.ip_edit);
        ipText = (TextView) findViewById(R.id.ip_text);
        
        startService(new Intent(this, MessageManager.class));
        
        handler = new Handler() {
			public void handleMessage(Message msg) {
				setMyIP((String)msg.obj);
			}
		};
        
        new Thread(new Runnable() {
			 public void run() {
				 String IPaddr = getMyIP();
				 Message msg = new Message();
				 msg.obj = IPaddr;
				 MessagePCViewer.handler.sendMessage(msg);
			 }
		 }).start();
    }

    public void mBtnClick(View v) {
    	switch(v.getId()) {
    	case R.id.ipset_btn :
    		// ipText.setText(ipEdit.getText());
    		break;
    	case R.id.connect_btn :
    		connect = new TCPconnect(port);
    		connect.listen();
    		if(connect.isconnect()) {
    			Toast.makeText(this, connect.getClientIP(), Toast.LENGTH_LONG).show();
    			MessageManager.setConnect(connect);
    		}
    		else {
    			// 다시 시도
    		}
    		break;
    	case R.id.test_btn :
    		break;
    	default :
    		break;
    	}
    }
    
    public static String getMyIP() {
    	try {
			Socket socket = new Socket("www.google.com", 80);
			return socket.getLocalAddress().toString();
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
    }
    
    private static void setMyIP(String IP) {
    	MessagePCViewer.myIP = IP;
    	ipText.setText(myIP);
    }
}