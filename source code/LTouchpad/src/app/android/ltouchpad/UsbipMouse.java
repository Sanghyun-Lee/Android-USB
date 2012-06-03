package app.android.ltouchpad;

import android.os.Message;
import android.util.Log;

public class UsbipMouse {
	private boolean connection;
	private boolean moveflag;
	private int recvSeqnum;
	private int sendSeqnum;
	
	public UsbipMouse() {
		System.loadLibrary("usb-mouse");
		moveflag =false;
	}
	
	public boolean isConnect() {
		return connection;
	}
	
	public boolean connect() {
		if(connect_usbip()<0) {
			connection = false;
			return false;
		}
		else {
			connection = true;
			return true;
		}
	}
	
	public boolean moveTouch(int x, int y) {
		int ret;
		//if(!moveflag) {
		Log.d("LTouchPad", "sendSeqnum:"+sendSeqnum+"/recvSeqnum:"+recvSeqnum);
		if(sendSeqnum <= recvSeqnum+1) {
			//moveflag = true;
			sendSeqnum = move(x, y);
			//if(ret==0) {
			if(sendSeqnum < 0) {
				Log.w("LTouchPad", "moveTouch Err : "+sendSeqnum);
				closeConnection();
				// moveflag = true;
				return false;
			}
			else {
				return true;
			}
		}
		else
			return false;
	}
	
	public boolean recvAck() {
		recvSeqnum = recv_ack();
		if(recvSeqnum<0) {
			closeConnection();
			return false;
		}
		else
			return true;
	}
	
	public int getSeqnum() {
		return recvSeqnum;
	}
	
	private void closeConnection() {
		Message msg = new Message();
		msg.obj = LTouchpadActivity.HANDLE_MSG_DISCONNECT;
		LTouchpadActivity.handler.sendMessage(msg);
		connection = false;
	}
	
	public boolean processCmd() {
		recvSeqnum = process_cmd();
		sendSeqnum = recvSeqnum;
		Log.d("LTouchPad", "sendSeqnum:"+sendSeqnum+"/recvSeqnum:"+recvSeqnum);
		if(sendSeqnum<0)
			return false;
		else
			return true;
	}
	
	public boolean btnLeft(boolean down) {
		int d=0, u=0;
		if(down)
			d=1;
		else
			u=1;
		
		sendSeqnum = btn_left(d, u);
		Log.d("LTouchPad", "sendSeqnum:"+sendSeqnum+"/recvSeqnum:"+recvSeqnum);
		if(sendSeqnum<0)
			return false;
		else
			return true;
	}
	
	public boolean btnRight(boolean down) {
		int d=0, u=0;
		if(down)
			d=1;
		else
			u=1;
		
		sendSeqnum = btn_right(d, u);
		if(sendSeqnum<0)
			return false;
		else
			return true;
	}
	
	public boolean btnScroll(boolean down) {
		int d=0, u=0;
		if(down)
			d=1;
		else
			u=1;
		
		sendSeqnum = btn_scroll(d, u);
		if(sendSeqnum<0)
			return false;
		else
			return true;
	}
	
	public boolean moveScroll(boolean down) {
		int d=0, u=0;
		if(down)
			d=1;
		else
			u=1;
		
		sendSeqnum = move_scroll(u, d);
		if(sendSeqnum<0)
			return false;
		else
			return true;
	}
	
	private native int connect_usbip();
	private native int process_cmd();
	private native int recv_ack();
	
	private native int move(int x, int y);
	private native int btn_left(int down, int up);
	private native int btn_right(int down, int up);
	private native int btn_scroll(int down, int up);
	private native int move_scroll(int up, int down);
}


