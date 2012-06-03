package app.android.ltouchpad;

public class RecvThread extends Thread {
	private UsbipMouse usbipMouse;
	
	public RecvThread(UsbipMouse usbipMouse) {
		super();
		this.usbipMouse = usbipMouse;
	}
	
	public void run() {
		while(true) {
			if(!usbipMouse.recvAck())
				break;
		}
	}
}