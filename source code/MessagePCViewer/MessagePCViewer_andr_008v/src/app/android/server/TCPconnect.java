package app.android.server;

import android.util.Log;

public class TCPconnect {
	private static String IP = "192.168.0.15";
	private static int port = 3600;
	private int connect_check;
	
	public TCPconnect() {
		this.connect_check = -1;
	}

	public int connect() {
		Log.i("TCPconnect","in connect() start");
		connect_check = set_ip_port(IP, port);
		if(isconnect()) Log.i("TCPconnect","connect success");
		else Log.i("TCPconnect","connect fail");
		return connect_check;
	}
	
	public int close() {
		// socket close ÇÊ¿ä
		connect_check = -1;
		return connect_check;
	}
	
	public int send(byte[] img) {
		if(isconnect()) {
			
			int ret = send_msg(img);
			byte[] test = native_test();
			System.out.println(test);
			return ret;
		}
		else
			return -1;
	}
	
	public String recv() {
		if(isconnect()) {
			return recv_msg();
		}
		else
			return null;
	}
	
	public boolean isconnect() {
		if(connect_check==0) return true;
		else return false;
	}
	
	private native int set_ip_port(String ip_addr, int port);
	private native int send_msg(byte[] img);
	private native static String recv_msg();
	
	private native byte[] native_test();
}
