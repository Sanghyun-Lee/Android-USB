package app.android.server;

import android.app.Instrumentation;
import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.view.KeyEvent;
import android.widget.Toast;

public class MessageManager extends Service {
	private static String keymsg;
	TCPconnect connect;
	static RecvThread recvth;
	// Handler handler;
	
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
		connect = new TCPconnect();
		connect.connect();
		if(connect.isconnect()) {
			Toast.makeText(this, "���ῡ �����߽��ϴ�.", Toast.LENGTH_LONG).show();
			recvth = new RecvThread(this);
			recvth.start();
		}
	}
	
	/*
	public MessageManager(Handler handler, TCPconnect connect) {
		this.handler = handler;
		this.connect = connect;
	}
	*/
	
	// recv Message from Application
	public String recvMsg() {
		// ���� �˸� �޾ƿ��� �κ����� ����
		// sendPC(str);
		return "";
	};
	
	// send Message to PC
	public int sendPC(byte[] img) {
		return connect.send(img);
	};
	
	// recv Message from PC
	public String recvPC() {
		return connect.recv();
	};
	
	// send Message to Application
	public int sendMsg(String str) {
		Message msg = new Message();
		msg.obj = str;
		insertEditText(msg.toString());
		
		return 0;
	}

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	};
	
	public static int insertEditText(String msg) {
		keymsg = msg;
		new Thread(new Runnable() {
			 public void run() {
				//test
					// mIME.set_text("test");
					// mIME.commit_text();
				 new Instrumentation().sendKeyDownUpSync(KeyEvent.KEYCODE_0);
				 //KeyEvent ke = new KeyEvent(0, "dd", 0, 0);
				 //new Instrumentation().sendKeyDownUpSync(ke.getKeyCode());
			 }
		 }).start();
		return 0;
	}	
	
	public static String pullMessage() {
		String msg = keymsg;
		keymsg = "";
		return msg;
	}
	
}
