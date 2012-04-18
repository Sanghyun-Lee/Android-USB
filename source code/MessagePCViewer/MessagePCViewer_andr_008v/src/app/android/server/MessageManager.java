package app.android.server;

import org.kandroid.app.hangulkeyboard.SoftKeyboard;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class MessageManager extends Service {
	
	private static SoftKeyboard IME;
	private static SendThread sendth;
	private static RecvThread recvth;
	private static TCPconnect connect;
	
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
		recvth = new RecvThread(this);
	}
	
	// recv Message from Application
	public static void setConnect(TCPconnect connect) {
		MessageManager.connect = connect;
		recvth.start();
	}
	
	public static void setKeyboard(SoftKeyboard IME) {
		MessageManager.IME = IME;
	}
	
	public String recvMsg() {
		// 추후 알림 받아오는 부분으로 수정
		// sendPC(str);
		return "";
	};
	
	// send Message to PC
	public int sendPC(byte[] img) {
		if(connect!=null)
			return connect.send(img);
		else
			return -1;
	};
	
	// recv Message from PC
	public String recvPC() {
		if(connect!=null)
			return connect.recv();
		else
			return null;
	};
	
	// send Message to Application
	public int sendMsg(String str) {
		Log.i("MessageManager","in sendMsg()");
		
		if(str.equals("\\\\kakao_on")) {
			Log.i("MessageManager","call openKakao");
			openKakao();
		}
		else if(str.equals("\\\\연결 상태가 아닙니다.")) {
			Log.i("MessageManager", "not connected");
			recvth.stop();
		}
		else if(IME!=null) { // IME commit
			Log.i("MessageManager","call commit_text");
			IME.commit_text(str);
		}
		else { // IME 연결안됨
			Toast.makeText(this, "MPV키보드로 설정하세요", Toast.LENGTH_LONG).show();
			return -1;
		}
		return 0;
	}
	
	private void openKakao() {
		Intent intent_kakao = this.getPackageManager().getLaunchIntentForPackage("com.kakao.talk");
        MessageManager.this.startActivity(intent_kakao);
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
		if(connect!=null)
			connect.close();
        super.onDestroy();
    }
}
