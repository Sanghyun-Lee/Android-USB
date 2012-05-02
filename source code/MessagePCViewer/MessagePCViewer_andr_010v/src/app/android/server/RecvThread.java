package app.android.server;

public class RecvThread extends Thread {
	MessageManager message;
	String str;
	
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
			message.sendMsg(MessageManager.MSG_NOTCONNECTED);
			return -1;
		}
		else if(str.length()>0) {
			message.sendMsg(str);
			return 0;
		}
		else return -2;
	}
}
