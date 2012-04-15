package app.android.server;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import android.app.Activity;
import android.graphics.Bitmap;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.Toast;

public class SendThread extends Thread {
	private MessageManager message;
	private View view;
	private ByteArrayOutputStream stream;
	
	public SendThread(MessageManager message, View view) {
		super();
		this.message = message;
		this.view = view;
		this.stream = new ByteArrayOutputStream();
	}
	
	public void run() {
		while(true) {
			send();
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	protected int send() {
		Bitmap bm;
        view.setDrawingCacheEnabled(true);
        bm = screenshot(view);
        test_save(bm);
        byte[] test_byte = getByteArray(bm);
        int test_ret = message.sendPC(test_byte);
        return test_ret;
        
        /*
		str = message.recvPC();
		if(str == null) {
			message.sendMsg(RecvThread.NotConnectedStr);
			return -1;
		}
		else if(str.length()>0) {
			message.sendMsg(str);
			return 0;
		}
		else return -2;
		*/
	}
	
	private Bitmap screenshot(View view) {
		return view.getDrawingCache();
	}
	
	private byte[] getByteArray(Bitmap bm) {
		bm.compress(Bitmap.CompressFormat.JPEG, 100, stream);
		byte[] byteArray = stream.toByteArray();
		return byteArray;
	}
	
	private void test_save(Bitmap bm) {
		try {
			File path = new File("/sdcard/PCViewer");
			
			if(!path.isDirectory()) {
				path.mkdirs();
			}
			
			String temp = "/sdcard/PCViewer/";
			temp += "temp";
			temp += ".jpg";
			
			FileOutputStream out = new FileOutputStream(temp);
			bm.compress(Bitmap.CompressFormat.JPEG, 100, out);
			
			//sendBroadcast(new Intent(Intent.ACTION_MEDIA_MOUNTED,
			//		Uri.parse("file://"+Environment.getExternalStorageDirectory())));
			
		} catch(FileNotFoundException e) {
			//Log.d("FileNotFoundException: ", e.getMessage());
		}
	}
}
