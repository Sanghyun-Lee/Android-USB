package app.android.server;

import android.os.Handler;
import android.os.Message;

public class MessageManager {
	TCPconnect connect;
	Handler handler;
	
	public MessageManager(Handler handler, TCPconnect connect) {
		this.handler = handler;
		this.connect = connect;
	}
	
	// recv Message from Application
	public String recvMsg() {
		// 추후 알림 받아오는 부분으로 수정
		// sendPC(str);
		return "";
	};
	
	// send Message to PC
	public int sendPC(String str) {
		return connect.send(str);
	};
	
	// recv Message from PC
	public String recvPC() {
		return connect.recv();
	};
	
	// send Message to Application
	public int sendMsg(String str) {
		Message msg = new Message();
		msg.obj = str;
		handler.sendMessage(msg);
		
		return 0;
	};
	
}
