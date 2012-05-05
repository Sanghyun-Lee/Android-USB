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
	
	protected boolean recv() {
		str = message.recvFromClient();
		if(str == null || str.equals("")) {
			message.sendToAndroidapp(MessageManager.MSG_NOTCONNECTED);
			return false;
		}
		return message.sendToAndroidapp(str);
	}
}
