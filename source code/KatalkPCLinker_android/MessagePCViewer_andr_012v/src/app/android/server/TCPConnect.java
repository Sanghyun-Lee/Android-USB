package app.android.server;

import android.util.Log;

public class TCPConnect {
	private String clientIP;
	private boolean accepting;
	private boolean listenRet;
	
	// native Methods
	private native int listen_server(int port);
	private native String accept_client();
	private native int send_msg(byte[] img);
	private native static String recv_msg();
	private native int close_listenSocket();
	private native int close_connectSocket();
	
	public TCPConnect() {
		System.loadLibrary("ndk-chat");
	}
	
	public int listenServer(int port) {
		Log.d("MessagePCViewer","in listenServer()");
		if(listenRet) {
			closeListen();
		}
		int ret = listen_server(port);
		if(ret==0) {
			listenRet = true;
		}
		else listenRet = false;
		Log.d("MessagePCViewer", "listen ret : " + ret);
		return ret;
	}

	public String acceptClient() {
		if(!listenRet || accepting || isconnect()) {
			return null;
		}
		
		accepting = true;
		Log.d("MessagePCViewer","in acceptClient() start");
		clientIP = accept_client();
		accepting = false;
		if(isconnect()) {
			Log.d("MessagePCViewer","acceptClient success (IP): " + clientIP);
			return clientIP;
		}
		else {
			Log.d("MessagePCViewer","acceptClient fail");
			return null;
		}
	}
	
	public int closeListen() {
		Log.d("MessagePCViewer","in closeListen");
		closeClient();
		int ret = close_listenSocket();
		Log.d("MessagePCViewer", "close listen ret : " + ret);
		listenRet = false;
		return 0;
	}
	
	public boolean closeClient() {
		if(!listenRet || !isconnect()) { 
			return false;
		}
		Log.d("MessagePCViewer","in closeClient");
		int ret = close_connectSocket();
		Log.d("MessagePCViewer", "close client ret : " + ret);
		clientIP = null;
		return true;
	}
	
	public int send(byte[] img) {
		// no effect
		return 0;
	}
	
	public String recv() {
		if(isconnect()) {
			return recv_msg();
		}
		else
			return null;
	}
	
	public boolean isconnect() {
		if(clientIP!=null) {
			return true;
		}
		else return false;
	}
	
	public String getClientIP() {
		return clientIP;
	}
	
	public boolean isaccepting() {
		return accepting;
	}
	
	public boolean islistening() {
		return listenRet;
	}
}
