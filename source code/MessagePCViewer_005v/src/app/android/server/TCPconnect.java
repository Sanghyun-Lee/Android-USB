package app.android.server;


public class TCPconnect {
	private String IP;
	private int port;
	
	public TCPconnect(String IP, int port) {
		this.IP = IP;
		this.port = port;
	}

	public int connect() {
		return set_ip_port(IP, port);
	}
	
	public int send(String str) {
		return send_msg(str);
	}
	
	public String recv() {
		return recv_msg();
	}
	
	private native int set_ip_port(String ip_addr, int port);
	private native int send_msg(String msg);
	private native static String recv_msg();
}
