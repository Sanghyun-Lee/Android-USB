package app.android.server;

import android.util.Log;

public class TCPconnect {
	private String client_IP;
	
	TCPconnect() {
		System.loadLibrary("ndk-chat");
	}
	
	public int bindServer(int port) {
		return listen_server(port);
	}

	public String listenClient() {
		Log.i("MessagePCViewer","in connect() start");
		client_IP = accept_client();
		if(isconnect()) Log.i("MessagePCViewer","connect success (IP): " + client_IP);
		else Log.i("MessagePCViewer","connect fail");
		return client_IP;
	}
	
	public int closeListen() {
		closeClient();
		close_listenSocket();
		return 0;
	}
	
	public int closeClient() {
		close_connectSocket();
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
	
	private native int listen_server(int port);
	private native String accept_client();
	private native int send_msg(byte[] img);
	private native static String recv_msg();
	private native int close_listenSocket();
	private native int close_connectSocket();
}
