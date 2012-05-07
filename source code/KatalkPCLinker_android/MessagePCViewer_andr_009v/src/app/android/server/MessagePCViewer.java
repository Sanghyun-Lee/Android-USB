package app.android.server;

import java.net.Socket;
import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
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
	
	public static final int HandlerWhat_SETMYIP = 1;
	public static final int HandlerWhat_ADDCLIP = 2;
	
	public static Handler handler = new Handler() {
		public void handleMessage(Message msg) {
			switch(msg.what) {
			case HandlerWhat_SETMYIP :
				setMyIP((String)msg.obj); break;
			case HandlerWhat_ADDCLIP :
				addClientIP((String)msg.obj); break;
			}
		}
	};
	
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
		
		new Thread(new Runnable() {
			 public void run() {
				 String IPaddr = getMyIP();
				 Message msg = new Message();
				 msg.what = MessagePCViewer.HandlerWhat_SETMYIP;
				 msg.obj = IPaddr;
				 MessagePCViewer.handler.sendMessage(msg);
			 }
		 }).start();
		
		startService(new Intent(this, MessageManager.class));
		//String clIP = MessageManager.getConnectClIP();
		//Log.d("MessagePCViewer", "connectClIP:"+clIP);
		//if(clIP!=null) addClientIP(clIP);
        
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
    		if(!MessageManager.setConnect()) {
    			Toast.makeText(this, "이미 서버가 열려 있습니다.", Toast.LENGTH_LONG).show();
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
    		Log.d("MessagePCViewer", "in getMyIP()");
			Socket socket = new Socket("www.google.com", 80);
			Log.d("MessagePCViewer", "myIP : " + socket.getLocalAddress());
			return socket.getLocalAddress().toString();
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
    }
    
    private static void setMyIP(String IP) {
    	MessagePCViewer.myIP = IP;
    	if(ipText==null) {
    		Log.w("MessagePCViewer", "setMyIP : ipText is null");
    		return;
    	}
    	ipText.setText(myIP);
    }
    
    private static void addClientIP(String IP) {
    	if(mArrayList==null) {
    		Log.w("MessagePCViewer", "addClientIP : mArrayList is null");
    		return;
    	}
    	mArrayList.add(IP);
		mConnectAdapter.notifyDataSetChanged();
    }
}