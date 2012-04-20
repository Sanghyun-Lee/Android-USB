package app.android.server;

import android.util.Log;

public class TCPconnect {
	private int port;
	private String client_IP;
	
	public TCPconnect(int port) {
		this.client_IP = null;
		this.port = port;
	}

	public String listen() {
		Log.i("TCPconnect","in connect() start");
		client_IP = listen_server(port);
		if(isconnect()) Log.i("TCPconnect","connect success");
		else Log.i("TCPconnect","connect fail");
		return client_IP;
	}
	
	public int close() {
		close_socket();
		client_IP = null;
		return 0;
	}
	
	public int send(byte[] img) {
		if(isconnect()) {
			int ret = send_msg(img);
			// byte[] test = native_test();
			// System.out.println(test);
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
		if(client_IP!=null) return true;
		else return false;
	}
	
	public String getClientIP() {
		return client_IP;
	}
	
	private native String listen_server(int port);
	private native int send_msg(byte[] img);
	private native static String recv_msg();
	private native int close_socket();
}
