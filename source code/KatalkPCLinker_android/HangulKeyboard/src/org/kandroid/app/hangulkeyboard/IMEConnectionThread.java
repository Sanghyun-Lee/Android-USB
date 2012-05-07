package org.kandroid.app.hangulkeyboard;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class IMEConnectionThread extends Thread {
	private Socket socket;
	private ServerSocket serverSocket;
	private SoftKeyboard softkeyboard;
	
	public IMEConnectionThread(SoftKeyboard softkeyboard) {
		super();
		this.softkeyboard = softkeyboard;
//		StringBuilder test = new StringBuilder();
//		test.append("test");
//        softkeyboard.getCurrentInputConnection().commitText(test, test.length());
	}
	
	public void run() {
		try {
			  serverSocket = new ServerSocket(3700);
			  recvKey();
		  } catch (Exception e) {
			  e.printStackTrace();
		  }
		  while(true) {
			  try{
				  socket = serverSocket.accept();
			  }catch(IOException e) {
				  e.printStackTrace();
			  }
		  }
	}
	
	public void recvKey() {
		while(true) {
			try {
				BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
				String str = in.readLine();
				if(str==null) {
					socket.close();
					break;
				}
				else {
					StringBuilder test = new StringBuilder();
		    		test.append("test");
		            softkeyboard.getCurrentInputConnection().commitText(test, test.length());
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
