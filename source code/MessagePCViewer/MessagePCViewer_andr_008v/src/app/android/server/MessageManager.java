package app.android.server;

import org.kandroid.app.hangulkeyboard.SoftKeyboard;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class MessageManager extends Service {
	TCPconnect connect;
	static RecvThread recvth;
	static SoftKeyboard IME;
	// Handler handler;
	
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
		
		System.loadLibrary("ndk-chat");
		
		connect = new TCPconnect();
		connect.connect();
		if(connect.isconnect()) {
			Toast.makeText(this, "연결에 성공했습니다.", Toast.LENGTH_LONG).show();
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
		// 추후 알림 받아오는 부분으로 수정
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
		Log.i("MessageManager","in sendMsg()");
		
		if(IME!=null) {
			if(str.equals("\\\\kakao_on")) {
				Log.i("MessageManager","call openKakao");
				openKakao();
			}
			else if(str.equals("\\\\연결 상태가 아닙니다.")) {
				Log.i("MessageManager", "not connected");
				recvth.stop();
			}
			else {
				Log.i("MessageManager","call commit_text");
				IME.commit_text(str);
			}
			return 0;
		}
		else {
			Toast.makeText(this, "MPV키보드로 설정하세요", Toast.LENGTH_LONG).show();
			return -1;
		}
	}
	
	private void openKakao() {
		Intent intent_kakao = this.getPackageManager().getLaunchIntentForPackage("com.kakao.talk");
        MessageManager.this.startActivity(intent_kakao);
	}
	
	public static void SetKeyboard(SoftKeyboard IME) {
		MessageManager.IME = IME;
	}
	
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	};
	
	@Override
    public void onDestroy() { 
		Log.i("MessageManager","in onDestroy");
		recvth.stop();
		connect.close();
        super.onDestroy();
    }
}
