package app.android.server;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class MyServiceReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		Log.d("MessagePCViewer", "on BroadcastReceive");
		if(intent.getAction().equals(Intent.ACTION_BOOT_COMPLETED))
			Log.d("MessagePCViewer", "on Receive ACTION_BOOT_COMPLETED");
		// 부팅시 자동 시작하는 서비스 구현중
		// context.startService(new Intent(context, MessageManager.class));
	}

}
