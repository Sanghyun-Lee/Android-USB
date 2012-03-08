package test.chat;

public class RecvThr extends Thread {
	
	public void run() {
		while(true) {
			String msg = Message.recv();
			ChatTestActivity.addMessage(msg);
		}
	}
}
