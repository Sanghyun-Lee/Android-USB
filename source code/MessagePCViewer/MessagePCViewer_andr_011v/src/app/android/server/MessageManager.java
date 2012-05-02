/*
 * Copyright (C) 2008-2009 Google Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 * 
 * 
 * @author
 * Department of Computer Engineering, HansungUniversity, Korea.
 *    
 */

package app.android.server;

import java.util.List;

import org.kandroid.app.hangulkeyboard.SoftKeyboard;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.Toast;

public class MessageManager extends Service {
	private static int port = 3600;
	public static final String MSG_NOTCONNECTED = "\\\\Not Connected";
	public static final String MSG_OPENPACK = "\\\\OPENPACK_";
	public static final String MSG_CONTROL = "\\\\CONTROL_";
	
	private static SoftKeyboard IME;
	private static RecvThread recvth;
	private static TCPconnect connect;
	
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
		Log.d("MessagePCViewer", "MessageManager:onStart");
		// recvth ���� ��� ���� �� ������ start()
		if(recvth==null) {
			recvth = new RecvThread(this);
			recvth.start();
		}
		setConnect();
	}
	
	// connect setting
	public static boolean setConnect() {
		// Log.d("MessagePCViewer", "MessageManager:setConnect");
		// connect �� �������� �ʾ��� ��� ���� �� listen()
		if(connect==null) {
			Log.d("MessagePCViewer", "MessageManager:setConnect:no TCPconnect");
			connect = new TCPconnect();
			connect.listenServer(port);
		}
		// Log.d("MessagePCViewer", "connect:"+connect.isconnect()+" / isaccepting:"+connect.isaccepting());
		// �̹� Ŭ���̾�Ʈ�� �������̰ų�, ������ accept()���� ��� connect �ʿ� ����
		if(connect.isconnect() || connect.isaccepting())
			return false;
		// ���ο� �����忡�� accept() �� MessagePCViewer���� ����뺸  
		new Thread(new Runnable() {
			 public void run() {
				 Log.d("MessagePCViewer", "MessageManager:setConnect:notConnected");
				 String clientIP = connect.acceptClient();
				 MessagePCViewer.addClientIP(clientIP);
				 if(clientIP==null) { // accept() ���н� listen socket �� �ݰ� �ٽ� listen()
					 connect.closeListen();
					 connect.listenServer(port);
				 }
			 }
		 }).start();
		return true;
	}
	
	public static boolean closeConnect() {
		if(connect==null || !connect.isconnect())
			return false;
		connect.closeClient();
		return !connect.isconnect();
	}
	
	public static String getConnectClIP() {
		return connect.getClientIP();
	}
	
	public static void setKeyboard(SoftKeyboard IME) {
		MessageManager.IME = IME;
	}
	
	public static boolean isIMEsetted() {
		if(IME==null)
			return false;
		else
			return true;
	}
	
	// recv Message from Application
	public String recvMsg() {
		// no effect
		return "";
	};
	
	// send Message to PC
	public int sendPC(byte[] data) {
		// no effect;
		return 0;
	};
	
	// recv Message from PC
	public String recvPC() {
		if(connect!=null)
			return connect.recv();
		else
			return null;
	};
	
	// send Message to Application
	public int sendMsg(String str) {
		Log.i("MessagePCViewer","in sendMsg() : " + str);
		
		if(str.startsWith(MessageManager.MSG_OPENPACK)) {
			String pack_name = str.substring(MessageManager.MSG_OPENPACK.length());
			Log.i("MessagePCViewer","open package : " + pack_name);
			openPackage(pack_name);
		}
		else if(str.equals(MessageManager.MSG_NOTCONNECTED)) {
			// Log.i("MessagePCViewer", "not connected");			
			if(connect!=null)
				connect.closeClient();
			// ������� ���� ���¿����� 1�ʿ� �ѹ���  �������� üũ �� �����غ� ���� setConnect()
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			setConnect();
		}
		// ��ɾ� ���� (IME ����ϴ� ����)
		else if(IME!=null) {
			//Log.i("MessagePCViewer", "sendMsg(): IME use");
			// CONTROL - ����Ű / ���� / ESC ���
			if(str.startsWith(MessageManager.MSG_CONTROL)){
				char c = str.charAt(str.length()-1);
				Log.i("MessagePCViewer", "send CONTROL Message : " + c);
				switch(c) {
				case 'L' : // left
					IME.key_control(KeyEvent.KEYCODE_DPAD_LEFT); break;
				case 'R' : // right
					IME.key_control(KeyEvent.KEYCODE_DPAD_RIGHT); break;
				case 'U' : // up
					IME.key_control(KeyEvent.KEYCODE_DPAD_UP); break;
				case 'D' : // down
					IME.key_control(KeyEvent.KEYCODE_DPAD_DOWN); break;
				case 'E' : // enter
					IME.key_control(KeyEvent.KEYCODE_ENTER); break;
				case 'B' : // back
					IME.key_control(KeyEvent.KEYCODE_BACK); break;
				default :
					return -1;
				}
			}
			else { // String ������ �״�� Ű���� Input ���� �Է�
				//Log.i("MessagePCViewer","call commit_text");
				IME.commit_text(str);
			}
		}
		else { // IME ����ȵ� ��� ȯ�漳��ȭ�� �����
			Log.d("MessagePCViewer", "IME not connect");
			openSetting();
			return -1;
		}
		return 0;
	}
	
	private void openSetting() {
		openPackage("com.android.settings");
		/*// ȯ�漳��â ���� ���������� Language Setting â���� �� �� �ִ� �ڵ� ����
		intent_setting.setAction(Intent.ACTION_MAIN);
		ComponentName com = new ComponentName("com.android.settings", "com.android.settings.LanguageSettings");
		intent_setting.setComponent(com);
				this.getPackageManager().getLaunchIntentForPackage("com.android.settings.LanguageSettings");
		*/
	}
	
	private boolean openPackage(String packname) {
		Intent intent = this.getPackageManager().getLaunchIntentForPackage(packname);
		if(intent==null)
			return false;
        MessageManager.this.startActivity(intent);
        return true;
	}
	
	private String getTopPkgName() {
		ActivityManager am = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
		List<RunningTaskInfo> Info = am.getRunningTasks(1);
		ComponentName topActivity = Info.get(0).topActivity;			
		String msg = topActivity.getPackageName();
		Log.d("MessagePCViewer", "top Activity Package Name : " + msg);
		return msg;
	}	
	
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	};
	
	@Override
    public void onDestroy() { 
		Log.i("MessagePCViewer","in onDestroy");
		recvth.stop();
		recvth = null;
		connect.closeListen();
        super.onDestroy();
    }
}
