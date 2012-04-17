package app.android.server;

public class RecvThread extends Thread {
	MessageManager message;
	String str;
	static String NotConnectedStr = "\\\\연결 상태가 아닙니다.";
	
	public RecvThread(MessageManager message) {
		super();
		this.message = message;
		this.str = "";
	}
	
	public void run() {
		while(true) {
			recv();
		}
	}
	
	protected int recv() {
		str = message.recvPC();
		if(str == null || str.equals("")) {
			message.sendMsg(RecvThread.NotConnectedStr);
			return -1;
		}
		else if(str.length()>0) {
			message.sendMsg(str);
			return 0;
		}
		else return -2;
	}
}
