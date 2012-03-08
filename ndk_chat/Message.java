package test.chat;

public class Message {
	
	public int send(String message) {
		return send_msg(message);
	}
	public static String recv() {
		return recv_msg();
	}
	public int set(String ip_addr, int port) {
		return set_ip_port(ip_addr, port);
	}
	
	private native int set_ip_port(String ip_addr, int port);
	private native int send_msg(String msg);
	private native static String recv_msg();
}