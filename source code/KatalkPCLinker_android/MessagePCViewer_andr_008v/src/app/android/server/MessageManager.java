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

import org.kandroid.app.hangulkeyboard.SoftKeyboard;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class MessageManager extends Service {
	
	private static SoftKeyboard IME;
	private static SendThread sendth;
	private static RecvThread recvth;
	private static TCPconnect connect;
	
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
		recvth = new RecvThread(this);
	}
	
	// recv Message from Application
	public static void setConnect(TCPconnect connect) {
		MessageManager.connect = connect;
		recvth.start();
	}
	
	public static void setKeyboard(SoftKeyboard IME) {
		MessageManager.IME = IME;
	}
	
	public String recvMsg() {
		// ���� �˸� �޾ƿ��� �κ����� ����
		// sendPC(str);
		return "";
	};
	
	// send Message to PC
	public int sendPC(byte[] img) {
		if(connect!=null)
			return connect.send(img);
		else
			return -1;
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
		Log.i("MessageManager","in sendMsg()");
		
		if(str.equals("\\\\kakao_on")) {
			Log.i("MessageManager","call openKakao");
			openKakao();
		}
		else if(str.equals("\\\\���� ���°� �ƴմϴ�.")) {
			Log.i("MessageManager", "not connected");
			recvth.stop();
		}
		else if(IME!=null) { // IME commit
			Log.i("MessageManager","call commit_text");
			IME.commit_text(str);
		}
		else { // IME ����ȵ�
			Toast.makeText(this, "MPVŰ����� �����ϼ���", Toast.LENGTH_LONG).show();
			return -1;
		}
		return 0;
	}
	
	private void openKakao() {
		Intent intent_kakao = this.getPackageManager().getLaunchIntentForPackage("com.kakao.talk");
        MessageManager.this.startActivity(intent_kakao);
	}
	
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	};
	
	@Override
    public void onDestroy() { 
		Log.i("MessageManager","in onDestroy");
		recvth.stop();
		if(connect!=null)
			connect.close();
        super.onDestroy();
    }
}
