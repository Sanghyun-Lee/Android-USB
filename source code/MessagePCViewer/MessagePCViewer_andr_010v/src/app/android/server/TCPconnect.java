package app.android.server;

import android.util.Log;

public class TCPconnect {
	private String client_IP;
	private boolean accepting;
	
	public TCPconnect() {
		System.loadLibrary("ndk-chat");
	}
	
	public int listenServer(int port) {
		Log.d("MessagePCViewer","in listenServer()");
		// closeListen();
		int ret = listen_server(port);
		Log.d("MessagePCViewer", "listen ret : " + ret);
		return ret;
	}

	public String acceptClient() {
		if(accepting || isconnect())
			return null;
		
		accepting = true;
		Log.d("MessagePCViewer","in acceptClient() start");
		client_IP = accept_client();
		accepting = false;
		if(isconnect()) {
			Log.d("MessagePCViewer","acceptClient success (IP): " + client_IP);
			return client_IP;
		}
		else {
			Log.d("MessagePCViewer","acceptClient fail");
			return null;
		}
	}
	
	public int closeListen() {
		Log.d("MessagePCViewer","in closeListen");
		closeClient();
		close_listenSocket();
		return 0;
	}
	
	public boolean closeClient() {
		if(accepting || !isconnect()) 
			return false;
		Log.d("MessagePCViewer","in closeClient");
		int ret = close_connectSocket();
		Log.d("MessagePCViewer", "close ret : " + ret);
		client_IP = null;
		return true;
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
	
	public boolean isaccepting() {
		return accepting;
	}
	
	private native int listen_server(int port);
	private native String accept_client();
	private native int send_msg(byte[] img);
	private native static String recv_msg();
	private native int close_listenSocket();
	private native int close_connectSocket();
}
