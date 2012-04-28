package app.android.server;

import java.net.Socket;
import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import app.android.server.R;

public class MessagePCViewer extends Activity {
	// private static final String basicIP = "192.168.0.15"; // test ip
	private static String myIP;
	private static TextView ipText;
	private static Button BtnConnect;
	
	private static ListView connectList;
	private static ArrayList<String> mArrayList;
	private static ArrayAdapter<String> mConnectAdapter;
	
	public static Handler handler;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.main);
        
        // ipEdit = (EditText) findViewById(R.id.ip_edit);
        ipText = (TextView) findViewById(R.id.ip_text);
        BtnConnect = (Button) findViewById(R.id.connect_btn);
        
        connectList = (ListView) findViewById(R.id.listView1);
        mArrayList = new ArrayList<String>();
        mConnectAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, mArrayList);
        connectList.setAdapter(mConnectAdapter);
        connectList.setOnItemClickListener(mOnItemClick);
        
        handler = new Handler() {
			public void handleMessage(Message msg) {
				setMyIP((String)msg.obj);
			}
		};
		
		// startService(new Intent(this, MessageManager.class));
        
        new Thread(new Runnable() {
			 public void run() {
				 String IPaddr = getMyIP();
				 Message msg = new Message();
				 msg.obj = IPaddr;
				 MessagePCViewer.handler.sendMessage(msg);
			 }
		 }).start();
        
        /*// 현재 Activity 가져오기
        ActivityManager activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
		RunningTaskInfo runningTaskInfo = activityManager.getRunningTasks(1).get(0);
		String topActivityName = runningTaskInfo.topActivity.getClassName();
		*/
    }
    
    public OnItemClickListener mOnItemClick = new OnItemClickListener() {
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
		}
    	
    };

    public void mBtnClick(View v) {
    	switch(v.getId()) {
    	case R.id.connect_btn :
    		String data = MessageManager.setConnect();
    		if(data!=null) {
    			mArrayList.add(data);
    			mConnectAdapter.notifyDataSetChanged();
    			// BtnConnect.setEnabled(false);
    		}
    		else {
    			Toast.makeText(this, "이미 연결중이거나 연결오류입니다.", Toast.LENGTH_LONG).show();
    		}
    		break;
    	case R.id.close_btn :
    		MessageManager.closeConnect();
    		break;
    	default :
    		break;
    	}
    }
    
    private static String getMyIP() {
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