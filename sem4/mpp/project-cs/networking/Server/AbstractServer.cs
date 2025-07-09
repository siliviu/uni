using System.Net;
using System.Net.Sockets;

namespace networking.Server;

public abstract class AbstractServer {
    private TcpListener server;
    private String host;
    private int port;

    public AbstractServer(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public void Start() {
        var adr = IPAddress.Parse(host);
        var ep = new IPEndPoint(adr, port);
        server = new TcpListener(ep);
        server.Start();
        while (true) {
            Console.WriteLine("Waiting for clients ...");
            var client = server.AcceptTcpClient();
            Console.WriteLine("Client connected ...");
            ProcessRequest(client);
        }
    }

    public abstract void ProcessRequest(TcpClient client);
}