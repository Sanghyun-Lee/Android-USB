package app.android.server;

import java.net.Socket;
import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import app.android.server.R;

public class MessagePCViewer extends Activity {
	
	private static String myIP;
	private static TextView ipText;
	private static Button BtnServer;
	private static ListView connectList;
	private static ArrayList<String> mArrayList = new ArrayList<String>();
	private static ArrayAdapter<String> mConnectAdapter;
	
	public static final int HandlerWhat_SETMYIP = 1;
	public static final int HandlerWhat_SETCONNECTRESULT = 2;
	private static final String STR_ServerOn = "����On";
	private static final String STR_ServerOff = "����Off";
	
	// ���ν����� ���� �����忡�� UI����� Handler ȣ��
	public static Handler handler = new Handler() {
		public void handleMessage(Message msg) {
			// � UI�� ������ ������ Message�� ��Ƽ� ��� ��
			switch(msg.what) {
			case HandlerWhat_SETMYIP :
				setMyIP((String)msg.obj); break;
			case HandlerWhat_SETCONNECTRESULT :
				setConnectResult((String)msg.obj); break;
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
        BtnServer = (Button) findViewById(R.id.server_btn);
        
        connectList = (ListView) findViewById(R.id.listView1);
        mConnectAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, mArrayList);
        connectList.setAdapter(mConnectAdapter);
        connectList.setOnItemClickListener(mOnItemClick);
		
        resetMyIP();
		startService(new Intent(this, MessageManager.class));
		
		//String clIP = MessageManager.getConnectClIP();
		//Log.d("MessagePCViewer", "connectClIP:"+clIP);
		//if(clIP!=null) addClientIP(clIP);
    }
    
    public OnItemClickListener mOnItemClick = new OnItemClickListener() {
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
		}
    	
    };

    public void mBtnClick(View v) {
    	switch(v.getId()) {
    	// ��ư ��Ȳ�� ���� ����/���� ó�� �ʿ�
    	
    	// stopService(new Intent(this, MessageManager.class));
    	case R.id.server_btn :
    		if(BtnServer.getText().equals(STR_ServerOn)) {
    			if(!MessageManager.setConnect()) {
        			Toast.makeText(this, "�̹� ������ ���� �ֽ��ϴ�.", Toast.LENGTH_LONG).show();
        			return;
        		}
    			else {
    				// ����On ��û ����
    				BtnServer.setEnabled(false);
    				// ���� ����On ����/���н� ó���� ���� �ʿ�
    			}
    		}
    		else {
    			// �����ư ��Ȳ�� ��
    		}
    		break;
    	case R.id.close_btn :
    		MessageManager.closeConnect();
    		break;
    	default :
    		break;
    	}
    }
    
    private static void resetMyIP() {
    	new Thread(new Runnable() {
			 public void run() {
				 String IPaddr = "";
				 try {
			    		Log.d("MessagePCViewer", "in getMyIP()");
						Socket socket = new Socket("www.google.com", 80);
						Log.d("MessagePCViewer", "myIP : " + socket.getLocalAddress());
						IPaddr = socket.getLocalAddress().toString();
				 } catch (Exception e) {
					 e.printStackTrace();
					 return;
				 }
				 if(IPaddr==null || IPaddr.equals(""))
					 return;
				 Message msg = new Message();
				 msg.what = MessagePCViewer.HandlerWhat_SETMYIP;
				 msg.obj = IPaddr;
				 MessagePCViewer.handler.sendMessage(msg);
			 }
		 }).start();
    }
    
    private static void setMyIP(String IP) {
    	MessagePCViewer.myIP = IP;
    	if(ipText==null) {
    		Log.w("MessagePCViewer", "setMyIP : ipText is null");
    		return;
    	}
    	ipText.setText(myIP);
    }
    
    // ����� Client IP �߰�
    public static void addClientIP(String IP) {
    	Message msg = new Message();
		msg.what = MessagePCViewer.HandlerWhat_SETCONNECTRESULT;
		msg.obj = IP;
		MessagePCViewer.handler.sendMessage(msg);
    }
    
    // mConnectAdapter ���ΰ�ħ
    private static void setConnectResult(String IP) {
    	if(IP!=null) { // connect success
    		mArrayList.add(IP);
    	}
    	if(BtnServer!=null && mConnectAdapter!=null) {
    		BtnServer.setEnabled(true);
    		if(IP!=null) { // connect success
    			BtnServer.setText(STR_ServerOff);
    			mConnectAdapter.notifyDataSetChanged();
    		}
    	}
    }
}